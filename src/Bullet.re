let color = "white";
let speed = 18.;
let maxCount = 15;
let angleRange = Js.Math._PI /. 20.;


let draw ctx (x, y, _) => {
  open ReasonJs.Canvas2d;
  fillStyle ctx color;
  ctx |> fillRect ::x ::y w::2. h::4.;
};

let tick (x, y, angle) => {
  let dx = speed *. Js.Math.sin angle;
  let dy = speed *. Js.Math.cos angle;
  (x +. dx, y -. dy, angle)
};

let isVisible (_, y, _) => (y > 0.);

let tryToShoot bullets (x, y) => {
  let angle = (Js.Math.random () *. angleRange) -. (angleRange /. 2.);
  (List.length bullets >= maxCount)
    ? bullets
    : List.append bullets [(x, y, angle)];
};
