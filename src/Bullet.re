module C = Canvas;

let color = "white";
let speed = 18.;

let draw ctx (x, y) => {
  C.fillStyle ctx color;
  C.fillRect ctx x y 2. 4.;
};

let tick (x, y) => {
  (x, y -. speed)
};

let isVisible (_, y) => (y > 0.);
