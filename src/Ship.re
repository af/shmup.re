open Input;
module C = Canvas;

let size = 20;
let noseLength = size / 2;
let wingLength = size / 2;
let tailLength = size / 4;
let color = "white";

let draw = fun ctx (x, y) => {
  C.strokeStyle ctx color;
  C.beginPath ctx;
  C.moveTo ctx x (y + tailLength);
  C.lineTo ctx (x + wingLength) (y + noseLength);
  C.lineTo ctx x (y - noseLength);      /* Front end of the ship */
  C.lineTo ctx (x - wingLength) (y + noseLength);
  C.lineTo ctx x (y + tailLength);
  C.stroke ctx;
};

/* TODO: update non-position ship state here */
let tick = fun state cmds => {
  List.fold_left (fun (x, y) cmd => {
    switch cmd {
    | ShipUp => (x, y - 1);
    | ShipDown => (x, y + 1);
    | ShipLeft => (x - 1, y);
    | ShipRight => (x + 1, y);
    | _ => (x, y);
    };
  }) state cmds
};
