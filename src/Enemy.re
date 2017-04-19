module C = Canvas;
module V = Vector;

type t = (float, float);
let _PI = 3.14159;

let spawn () => {
  /* FIXME: placeholder */
  (100., 100.);
};

let tick (x, y) => {
  (x +. 1., y +. 1.);
};

let size = 20.;
let halfSize = size /. 2.;

let draw ctx state => {
  let (x, y) = state;
  C.save ctx;
  C.translate ctx x y;
  C.strokeRect ctx (-1. *. halfSize) (-1. *. halfSize) size size;
  C.rotate ctx (_PI /. 4.);
  C.strokeRect ctx (-1. *. halfSize) (-1. *. halfSize) size size;
  C.restore ctx;
};
