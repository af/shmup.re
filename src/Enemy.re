module C = Canvas;
module V = Vector;

type t = {
  position: (float, float),
  velocity: (float, float),
  diedAt: option float,
  rotation: float  /* radians */
};
let _PI = 3.14159;
let rotationSpeed = 0.01;

let tick state => {
  let (x, y) = state.position;
  let (vx, vy) = state.velocity;
  let position = (x +. vx, y +. vy);
  let rotation = state.rotation +. rotationSpeed;
  {...state, rotation, position};
};

let size = 20.;
let halfSize = size /. 2.;

let draw ctx {position: (x, y), rotation, diedAt} => {
  let color = switch diedAt {
  | Some _ => "red"
  | None => "white"
  };
  C.save ctx;
  C.strokeStyle ctx color;
  C.translate ctx x y;
  C.rotate ctx (_PI /. 4. -. rotation);
  C.strokeRect ctx (-1. *. halfSize) (-1. *. halfSize) size size;
  C.rotate ctx (_PI /. 4. -. rotation);
  C.strokeRect ctx (-1. *. halfSize) (-1. *. halfSize) size size;
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

let checkBullets bullets enemies => {
  List.map (fun enemy => {
    let {position: (x, y)} = enemy;
    let w = size /. 2.;
    let isDead = List.fold_left (fun acc (bx, by) => {
      acc || ((bx < x +. w) && (bx > x -. w)) && (by < y +. w) && (by > y -. w);
    }) false bullets;

    isDead
      ? {...enemy, diedAt: Some (Js.Date.now ())}
      : enemy;
  }) enemies
}
