open ReasonJs.Dom;
open Canvas;
module StarField = StarField;
module Ship = Ship;

let width = 800;
let height = 600;

type gameState = {
  mutable shipPosition: point,
  mutable startTime: float
};
let gameState = {
  startTime: Js.Date.now (),
  shipPosition: {x: 300, y: 500}
};

let setupDraw = fun canvas => {
  let ctx = CanvasElement.getContext canvas "2d";
  let rec render = fun () => {
    let now = Js.Date.now ();
    let runTime = now -. gameState.startTime;

    clearRect ctx 0 0 width height;
    StarField.draw (0, 0) 2 ctx runTime;
    StarField.draw (100, 200) 1 ctx runTime;
    Ship.draw ctx gameState.shipPosition;
    ReasonJs.requestAnimationFrame render;
  };
  let _ = ReasonJs.requestAnimationFrame render;
};


let canvasEl = DocumentRe.querySelector "canvas" document;
switch canvasEl {
| Some canv => setupDraw canv
| None => Js.log "couldnt get canvas"
};
Js.log ("Hi from bucklescript!");
