open ReasonJs.Dom;
open Canvas;

let drawAStupidBox = fun canvas x y => {
  let ctx = CanvasElement.getContext canvas "2d";
  fillStyle ctx "white";
  fillRect ctx x y 10 10;
};


let canvas = DocumentRe.querySelector "canvas" document;
switch canvas {
| Some x => drawAStupidBox x 20 50
| None => Js.log "couldnt get canvas"
};
Js.log ("Hi from bucklescript!");
