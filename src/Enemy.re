module C = Canvas;
module V = Vector;

type t = {
  position: (float, float),
  velocity: (float, float),
  diedAt: option float,
  rotation: float  /* radians */
};
let _PI = Js.Math._PI;
let rotationSpeed = 0.01;
let deathAnimationDuration = 1500.;

let tick state => {
  let (x, y) = state.position;
  let (vx, vy) = state.velocity;
  let position = (x +. vx, y +. vy);
  let rotation = state.rotation +. rotationSpeed;
  {...state, rotation, position};
};

let size = 20.;
let halfSize = size /. 2.;

/*
 * Draw enemy explosion
 * Assumes the context has been translated so 0,0 is the enemy's position
 */
let drawExplosion ctx deathTime now => {
  let radius = 0.1 *. (now -. deathTime);
  let numParticles = 8;
  for particleIdx in 0 to numParticles {
    let theta = (float_of_int particleIdx) *. (_PI /. 4.);
    let distance = radius *. Js.Math.sin (float_of_int particleIdx);
    let size = 0.002 *. (deathAnimationDuration -. (now -. deathTime));
    let (x, y) = (distance *. Js.Math.sin theta, distance *. Js.Math.cos theta);
    C.strokeRect ctx x y size size;
  }
};

let draw ctx {position: (x, y), rotation, diedAt} => {
  let now = Js.Date.now ();

  C.save ctx;
  C.strokeStyle ctx "white";
  C.translate ctx x y;
  C.rotate ctx (_PI /. 4. -. rotation);
  switch diedAt {
  | Some deathTime when (now > deathTime +. deathAnimationDuration) => ();
  | Some deathTime => drawExplosion ctx deathTime now;
  | None =>
    C.strokeRect ctx (-1. *. halfSize) (-1. *. halfSize) size size;
    C.rotate ctx (_PI /. 4. -. rotation);
    C.strokeRect ctx (-1. *. halfSize) (-1. *. halfSize) size size;
  };
  C.restore ctx;
};

let cull _ height enemies => {
  List.filter (fun {position: (_, y)} => y < (height +. size)) enemies;
};


let spawnNew (x, y) => {
  let xVel = (Js.Math.random ()) -. 0.5;
  {position: (x, y), velocity: (xVel, 1.), rotation: 0., diedAt: None};
};

/* Spawn a new enemy every few ticks */
let managePopulation startTime enemies => {
  let timeDelta = int_of_float (Js.Date.now () -. startTime);
  let shouldSpawn = (timeDelta mod 20 === 0);
  shouldSpawn
    ? List.append enemies [spawnNew (C.width *. Js.Math.random (), -20.)]
    : enemies;
};


/* Check collision of two squares */
/* TODO: add w2 to give second entity a size (currently fixed at 1x1) */
let collides (x1, y1) w1 (x2, y2) => {
  (x2 < x1 +. w1) && (x2 > x1 -. w1) && (y2 < y1 +. w1) && (y2 > y1 -. w1);
};

let checkBullets bullets enemies => {
  List.map (fun enemy => {
    let {diedAt, position: (x, y)} = enemy;
    let w = size /. 2.;
    let justDied = List.fold_left (fun acc (bx, by) => {
      acc || collides (x, y) w (bx, by)
    }) false bullets;

    switch (diedAt, justDied) {
    | (None, true) => {...enemy, diedAt: Some (Js.Date.now ())}
    | (None, false) => enemy
    | (Some _, _) => enemy
    }
  }) enemies
};

/* FIXME: this simplistic collision detection treats the ship as if it's only 1px x 1px */
let checkShip (shipX, shipY) enemies => {
  let w = size /. 2.;
  List.fold_left (fun acc {diedAt, position: (ex, ey)} => {
    switch diedAt {
    | Some _ => false;
    | None => acc || collides (ex, ey) w (shipX, shipY);
    }
  }) false enemies;
}
