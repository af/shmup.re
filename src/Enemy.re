module Canvas = ReasonJs.Canvas2d;

module V = Vector;

type t = {
  position: (float, float),
  velocity: (float, float),
  diedAt: option(float),
  rotation: float /* radians */
};

let _PI = Js.Math._PI;

let rotationSpeed = 0.01;

let deathAnimationDuration = 1500.;

let tick = (state) => {
  let (x, y) = state.position;
  let (vx, vy) = state.velocity;
  let position = (x +. vx, y +. vy);
  let rotation = state.rotation +. rotationSpeed;
  {...state, rotation, position}
};

let size = 20.;

let halfSize = size /. 2.;

/*
 * Draw enemy explosion
 * Assumes the context has been translated so 0,0 is the enemy's position
 */
let drawExplosion = (ctx, deathTime, now) => {
  let radius = 3.0 +. 0.1 *. (now -. deathTime);
  let numParticles = 8;
  for (particleIdx in 0 to numParticles) {
    let theta = float_of_int(particleIdx) *. (_PI /. 4.);
    let distance = radius *. Js.Math.sin(float_of_int(particleIdx) +. deathTime);
    let size = 0.002 *. (deathAnimationDuration -. (now -. deathTime));
    let (x, y) = (distance *. Js.Math.sin(theta), distance *. Js.Math.cos(theta));
    ctx |> Canvas.fillRect(~x, ~y, ~w=size, ~h=size)
  }
};

let draw = (ctx, {position: (x, y), rotation, diedAt}) => {
  let now = Js.Date.now();
  ctx |> Canvas.save;
  Canvas.strokeStyle(ctx, "white");
  ctx |> Canvas.translate(~x, ~y);
  switch diedAt {
  | Some(deathTime) when now > deathTime +. deathAnimationDuration => ()
  | Some(deathTime) => drawExplosion(ctx, deathTime, now)
  | None =>
    ctx |> Canvas.rotate(_PI /. 4. -. rotation);
    ctx |> Canvas.strokeRect(~x=(-1.) *. halfSize, ~y=(-1.) *. halfSize, ~w=size, ~h=size);
    ctx |> Canvas.rotate(_PI /. 4. -. rotation);
    ctx |> Canvas.strokeRect(~x=(-1.) *. halfSize, ~y=(-1.) *. halfSize, ~w=size, ~h=size)
  };
  ctx |> Canvas.restore
};

let cull = (_, height, enemies) =>
  List.filter(({position: (_, y)}) => y < height +. size, enemies);

let spawnNew = (stage) => {
  let (x, y) = (V.worldWidth *. Js.Math.random(), (-20.));
  let xVel = Js.Math.random() -. 0.4;
  let yVel = float_of_int(stage) *. Js.Math.random() +. 2.;
  {position: (x, y), velocity: (xVel, yVel), rotation: 0., diedAt: None}
};

/* Spawn a new enemy every few ticks
 * Enemies become more numerous as the game progresses
 */
let managePopulation = (startTime, enemies) => {
  let timeSinceStart = int_of_float(Js.Date.now() -. startTime);
  let stage = timeSinceStart / 6000;
  let shouldSpawn = timeSinceStart mod max(20 - stage, 2) === 0;
  shouldSpawn ? List.append(enemies, [spawnNew(stage)]) : enemies
};

/* Check collision of two circles */
let collides = ((x1, y1), r1, (x2, y2), r2) => {
  let dist = sqrt((x1 -. x2) ** 2. +. (y1 -. y2) ** 2.);
  dist < r1 +. r2
};

let checkBullets = (bullets, onEnemKilled, enemies) =>
  List.map(
    (enemy) => {
      let {diedAt, position: (x, y)} = enemy;
      let r = size /. 2.;
      let justDied =
        List.fold_left(
          (acc, (bx, by, _)) => acc || collides((x, y), r, (bx, by), 1.),
          false,
          bullets
        );
      switch (diedAt, justDied) {
      | (None, true) =>
        onEnemKilled();
        {...enemy, diedAt: Some(Js.Date.now())}
      | (None, false) => enemy
      | (Some(_), _) => enemy
      }
    },
    enemies
  );

let checkShip = ((shipX, shipY), enemies) => {
  let r = size /. 2.;
  List.fold_left(
    (shipAlreadyDead, enemy) => {
      let {diedAt, position: (ex, ey)} = enemy;
      switch (shipAlreadyDead, diedAt) {
      | (true, _) => true
      | (_, Some(_)) => false
      | (_, None) => collides((ex, ey), r, (shipX, shipY), 5.)
      }
    },
    false,
    enemies
  )
};
