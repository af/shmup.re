open ReasonJs.Dom;

/* External hack to get at KeyboardEventRe.key */
external eventKey : 'a => string = "key" [@@bs.get];

type cmd =
| ShipUp
| ShipDown
| ShipLeft
| ShipRight
| ShipShoot;

type keyState = {
  mutable left: bool,
  mutable right: bool,
  mutable up: bool,
  mutable down: bool
};
let currentState = {
  left: false,
  right: false,
  up: false,
  down: false
};
/* TODO: track input state here, and return real cmds from sample() */

let keydownListener = fun evt => {
  EventRe.preventDefault evt;
  switch (eventKey evt) {
  | "ArrowLeft" => currentState.left = true;
  | "ArrowRight" => currentState.right = true;
  | "ArrowUp" => currentState.up = true;
  | "ArrowDown" => currentState.down = true;
  | _ => ();
  };
};

let keyupListener = fun evt => {
  switch (eventKey evt) {
  | "ArrowLeft" => currentState.left = false;
  | "ArrowRight" => currentState.right = false;
  | "ArrowUp" => currentState.up = false;
  | "ArrowDown" => currentState.down = false;
  | _ => ();
  };
};

let bindListeners = fun () => {
  DocumentRe.addEventListener "keydown" (fun evt => (keydownListener evt)) document;
  DocumentRe.addEventListener "keyup" (fun evt => (keyupListener evt)) document;
};

/* Return a list of commands based on the current state of inputs */
let sample = fun () => {
  /* TODO: real implementation */
  Js.log(currentState);
  switch currentState {
  | {left: true, _} => [ShipLeft];
  | {right: true, _} => [ShipRight];
  | {up: true, _} => [ShipUp];
  | {down: true, _} => [ShipDown];
  | _ => [];
  };
};
