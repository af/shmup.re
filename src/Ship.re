module C = Canvas;

type t = {
  position: (float, float),
  velocity: (float, float)
};

let initialState = {
  position: (300., 500.),
  velocity: (0., 0.)
};

let maxSpeed = 6.;  /* max # of pixels moved per tick */
let size = 20.;
let noseLength = size /. 2.;
let wingWidth = size /. 2.;
let tailLength = size /. 4.;
let color = "white";

let draw = fun ctx {position: (x, y), velocity: (vx, vy)} => {
  let w = wingWidth -. (abs_float (vx /. 3.)); /* narrower wings when moving to side ("tilting") */
  C.strokeStyle ctx color;
  C.beginPath ctx;
  C.moveTo ctx x (y +. tailLength);
  C.lineTo ctx (x +. w) (y +. noseLength);
  C.lineTo ctx x (y -. noseLength);      /* Front end of the ship */
  C.lineTo ctx (x -. w) (y +. noseLength);
  C.closePath ctx;
  C.stroke ctx;

  /* Draw booster if ship is moving up */
  if (vy <= -1.5) {
    let boosterLength = -. vy *. 2.;
    C.beginPath ctx;
    C.moveTo ctx x (y +. noseLength);
    C.lineTo ctx (x +. 3.) (y +. noseLength +. 2.);
    C.lineTo ctx x (y +. noseLength +. boosterLength);
    C.lineTo ctx (x -. 3.) (y +. noseLength +. 2.);
    C.closePath ctx;
    C.stroke ctx;
  }
};

let limitMagnitide = fun maxMag (vx, vy) => {
  let magnitude = sqrt (vx *. vx +. vy *. vy);
  if (magnitude > maxMag) {
    let scale = maxMag /. magnitude;
    (vx *. scale, vy *. scale);
  } else {
    (vx, vy);
  }
};

let applyFriction = fun coeff (vx, vy) => {
  (vx *. coeff, vy *. coeff);
};


/* TODO: support diagonal movement */
let tick = fun state cmds => {
  let {velocity} = List.fold_left (fun state cmd => {
    module I = Input;
    let {velocity: (vx, vy)} = state;
    let newVel = switch cmd {
    | I.ShipUp n => (vx, vy -. float_of_int n);
    | I.ShipDown n => (vx, vy +. float_of_int n);
    | I.ShipLeft n => (vx -. float_of_int n, vy);
    | I.ShipRight n => (vx +. float_of_int n, vy);
    | I.ShipShoot => (vx, vy);
    };
    {...state, velocity: newVel};
  }) state cmds;

  let (x,y) = state.position;
  let (vx, vy) = velocity |> applyFriction 0.9 |> limitMagnitide maxSpeed;
  let position = (x +. vx, y +. vy);
  {velocity: (vx, vy), position};
};
