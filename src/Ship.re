module C = Canvas;

type t = {
  position: (int, int),
  velocity: (int, int)
};

let initialState = {
  position: (300, 500),
  velocity: (0, 0)
};

let maxSpeed = 7;  /* max # of pixels moved per tick */
let size = 20;
let noseLength = size / 2;
let wingWidth = size / 2;
let tailLength = size / 4;
let color = "white";

let draw = fun ctx {position: (x, y), velocity: (vx, _)} => {
  let w = wingWidth - (abs (vx / 2)); /* narrower wings when moving to side ("tilting") */
  C.strokeStyle ctx color;
  C.beginPath ctx;
  C.moveTo ctx x (y + tailLength);
  C.lineTo ctx (x + w) (y + noseLength);
  C.lineTo ctx x (y - noseLength);      /* Front end of the ship */
  C.lineTo ctx (x - w) (y + noseLength);
  C.lineTo ctx x (y + tailLength);
  C.stroke ctx;
};

/* TODO: support diagonal movement */
/* TODO: update velocity state */
let tick = fun state cmds => {
  /* Determine how quickly to move the ship based on a cmd's magnitude */
  let delta = fun cmdMagnitude => {
    min maxSpeed (cmdMagnitude / 2);
  };

  List.fold_left (fun {position: (x, y)} cmd => {
    module I = Input;
    let newPos = switch cmd {
    | I.ShipUp n => (x, y - (delta n));
    | I.ShipDown n => (x, y + (delta n));
    | I.ShipLeft n => (x - (delta n), y);
    | I.ShipRight n => (x + (delta n), y);
    | I.ShipShoot => (x, y);
    };
    {...state, position: newPos};
  }) state cmds
};
