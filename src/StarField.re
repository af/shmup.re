module V = Vector;
module Canvas = ReasonJs.Canvas2d;

let stars = [|
  (100., 100.),
  (150., 290.),
  (190., 540.),
  (350., 210.),
  (550., 390.),
  (600., 10.)
|];

/* 0 < zDepth < 1, with a higher value representing a larger distance from the ship */
let draw = fun ctx offset::(offsetX, offsetY)=(0.,0.) ::zDepth=0.2 runTime => {
  Canvas.fillStyle ctx ("rgba(255,255,255," ^ (string_of_float (1.0 -. zDepth)) ^ ")");
  Array.iter (fun (baseX, baseY) => {
    let speed = 0.03 *. runTime /. zDepth;
    let x = baseX +. offsetX;
    let y = mod_float (baseY +. offsetY +. speed) Vector.worldHeight;
    let starSize = 2.;
    ctx |> Canvas.fillRect ::x ::y w::starSize h::starSize;
  }) stars;
};
