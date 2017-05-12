let color = "white";
let speed = 18.;

let draw ctx (x, y) => {
  open ReasonJs.Canvas2d;
  fillStyle ctx color;
  ctx |> fillRect ::x ::y w::2. h::4.;
};

let tick (x, y) => {
  (x, y -. speed)
};

let isVisible (_, y) => (y > 0.);
