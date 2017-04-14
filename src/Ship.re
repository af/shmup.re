module Input = Input;
module C = Canvas;

let maxSpeed = 7;  /* max # of pixels moved per tick */
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
  /* Determine how quickly to move the ship based on a cmd's magnitude */
  let delta = fun cmdMagnitude => {
    min maxSpeed (cmdMagnitude / 2);
  };

  List.fold_left (fun (x, y) cmd => {
    switch cmd {
    | Input.ShipUp n => (x, y - (delta n));
    | Input.ShipDown n => (x, y + (delta n));
    | Input.ShipLeft n => (x - (delta n), y);
    | Input.ShipRight n => (x + (delta n), y);
    | Input.ShipShoot => (x, y);
    };
  }) state cmds
};
