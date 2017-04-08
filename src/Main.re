open ReasonJs.Dom;
module C = Canvas;
module StarField = StarField;
module Ship = Ship;

type gameState = {
  mutable shipPosition: C.point,
  mutable startTime: float
};
let gameState = {
  startTime: Js.Date.now (),
  shipPosition: {x: 300, y: 500}
};

let setupDraw = fun canvas => {
  let ctx = C.CanvasElement.getContext canvas "2d";
  let rec render = fun () => {
    let now = Js.Date.now ();
    let runTime = now -. gameState.startTime;

    C.clearRect ctx 0 0 C.width C.height;
    StarField.draw ctx {x: 0, y: 0} 2 runTime;
    StarField.draw ctx {x: 100, y: 200} 1 runTime;
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
