open ReasonJs.Dom;
open Canvas;

let width = 800;
let height = 600;
let ms_interval = 100;

let stars = [|
  (100, 100),
  (150, 190),
  (350, 210),
  (550, 390),
  (600, 10)
|];

type gameState = {
  mutable time: int
};
let gameState = {time: 0};

let drawStarField = fun offset speed ctx t => {
  let (offsetX, offsetY) = offset;
  fillStyle ctx "white";
  Array.iter (fun (baseX, baseY) => {
    let x = baseX + offsetX;
    let y = (baseY + offsetY + speed * t) mod height;
    let size = 2;
    fillRect ctx x y size size;
  }) stars;
};

let setupDraw = fun canvas => {
  let ctx = CanvasElement.getContext canvas "2d";
  let _ = Js_global.setInterval (fun () => {
    gameState.time = gameState.time + 1;
    clearRect ctx 0 0 width height;
    drawStarField (0, 0) 2 ctx gameState.time;
    drawStarField (100, 200) 1 ctx gameState.time;
  }) ms_interval;
};


let canvasEl = DocumentRe.querySelector "canvas" document;
switch canvasEl {
| Some canv => setupDraw canv
| None => Js.log "couldnt get canvas"
};
Js.log ("Hi from bucklescript!");
