module C = Canvas;
module V = Vector;

type t = {
  position: (float, float),
  velocity: (float, float),
  rotation: float  /* radians */
};
let _PI = 3.14159;
let rotationSpeed = 0.01;

let spawn (x, y) => {
  /* FIXME: placeholder */
  let xVel = (Js.Math.random ()) -. 0.5;
  {position: (x, y), velocity: (xVel, 1.), rotation: 0.};
};

let tick state => {
  let (x, y) = state.position;
  let (vx, vy) = state.velocity;
  let position = (x +. vx, y +. vy);
  let rotation = state.rotation +. rotationSpeed;
  {...state, rotation, position};
};

let size = 20.;
let halfSize = size /. 2.;

let draw ctx {position: (x, y), rotation} => {
  C.save ctx;
  C.translate ctx x y;
  C.rotate ctx (_PI /. 4. -. rotation);
  C.strokeRect ctx (-1. *. halfSize) (-1. *. halfSize) size size;
  C.rotate ctx (_PI /. 4. -. rotation);
  C.strokeRect ctx (-1. *. halfSize) (-1. *. halfSize) size size;
  C.restore ctx;
};
