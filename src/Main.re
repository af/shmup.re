open ReasonJs.Dom;
module C = Canvas;
module StarField = StarField;
module Ship = Ship;

type gameState = {
  mutable shipPosition: (int, int),
  startTime: float
};
let gameState = {
  startTime: Js.Date.now (),
  shipPosition: (300, 500)
};

let setupDraw = fun canvas => {
  let ctx = C.CanvasElement.getContext canvas "2d";
  let rec render = fun () => {
    let now = Js.Date.now ();
    let runTime = now -. gameState.startTime;

    C.clearRect ctx 0 0 C.width C.height;
    StarField.draw ctx (0, 0) 2 runTime;
    StarField.draw ctx (100, 200) 1 runTime;
    Ship.draw ctx gameState.shipPosition;
    ReasonJs.requestAnimationFrame render;
  };
  let _ = ReasonJs.requestAnimationFrame render;
};

/* External hack to get at KeyboardEventRe.key */
external eventKey : 'a => string = "key" [@@bs.get];

let keyboardListener = fun evt => {
  /*Js.log evt;*/
  /*Js.log (eventKey evt);*/
  EventRe.preventDefault evt;
  let (x, y) = gameState.shipPosition;
  gameState.shipPosition = switch (eventKey evt) {
  | "ArrowLeft" => (x - 2, y);
  | "ArrowRight" => (x + 2, y);
  | "ArrowUp" => (x, y - 2);
  | "ArrowDown" => (x, y + 2);
  | _ => gameState.shipPosition;
  };
};
DocumentRe.addEventListener "keydown" keyboardListener document;

let canvasEl = DocumentRe.querySelector "canvas" document;
switch canvasEl {
| Some canv => setupDraw canv
| None => Js.log "couldnt get canvas"
};
Js.log ("Hi from bucklescript!");
