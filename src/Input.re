external eventKey : 'a => string = "key" [@@bs.get];

let withDefault fallback input =>
  switch input {
  | None => fallback
  | Some x => x
  };

type cmd =
  | ShipUp int
  | ShipDown int
  | ShipLeft int
  | ShipRight int
  | ShipShoot;

type keyState = {
  mutable left: option int,
  mutable right: option int,
  mutable up: option int,
  mutable down: option int,
  mutable space: bool
};

let currentState = {left: None, right: None, up: None, down: None, space: false};

let keydownListener evt => {
  EventRe.preventDefault evt;
  switch (eventKey evt) {
  | "ArrowLeft" => currentState.left = Some (withDefault 1 currentState.left)
  | "ArrowRight" => currentState.right = Some (withDefault 1 currentState.right)
  | "ArrowUp" => currentState.up = Some (withDefault 1 currentState.up)
  | "ArrowDown" => currentState.down = Some (withDefault 1 currentState.down)
  | " " => currentState.space = true
  | _ => ()
  }
};

let keyupListener evt =>
  switch (eventKey evt) {
  | "ArrowLeft" => currentState.left = None
  | "ArrowRight" => currentState.right = None
  | "ArrowUp" => currentState.up = None
  | "ArrowDown" => currentState.down = None
  | " " => currentState.space = false
  | _ => ()
  };

let bindListeners () => {
  open ReasonJs.Dom;
  DocumentRe.addEventListener "keydown" (fun evt => keydownListener evt) document;
  DocumentRe.addEventListener "keyup" (fun evt => keyupListener evt) document
};

let sample () => {
  switch currentState {
  | {up: Some n} => currentState.up = Some (n + 1)
  | {down: Some n} => currentState.down = Some (n + 1)
  | _ => ()
  };
  switch currentState {
  | {left: Some n} => currentState.left = Some (n + 1)
  | {right: Some n} => currentState.right = Some (n + 1)
  | _ => ()
  };
  let spaceList = currentState.space ? [ShipShoot] : [];
  let xCmdList =
    switch currentState {
    | {left: Some n, right: None} => [ShipLeft n]
    | {right: Some n, left: None} => [ShipRight n]
    | _ => []
    };
  let yCmdList =
    switch currentState {
    | {up: Some n, down: None} => [ShipUp n]
    | {down: Some n, up: None} => [ShipDown n]
    | _ => []
    };
  List.concat [xCmdList, yCmdList, spaceList]
};
