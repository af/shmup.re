module C = Canvas;
module V = Vector;

type t = {
  position: (float, float),
  velocity: (float, float),
  bullets: list (float, float)
};

let initialState = {
  position: (300., 500.),
  velocity: (0., 0.),
  bullets: []
};

let bulletSpeed = 18.;
let maxSpeed = 7.;  /* max # of pixels moved per tick */
let maxThrust = 10.; /* maximum impact of holding a key down */
let size = 20.;
let noseLength = size /. 2.;
let wingWidth = size /. 2.;
let tailLength = size /. 4.;
let color = "white";

let drawBullets ctx {bullets} => {
  List.iter (fun (x, y) => {
    C.fillRect ctx x y 2. 4.;
  }) bullets;
};

let draw = fun ctx state => {
  let {position: (x, y), velocity: (vx, vy)} = state;
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
  };

  drawBullets ctx state;
};

let ticksToThrust = fun n => {
  min maxThrust (float_of_int n);
};

let tick = fun state cmds => {
  let stateFromInputs = List.fold_left (fun state cmd => {
    module I = Input;
    let {velocity: (vx, vy), position: (x, y)} = state;
    switch cmd {
    | I.ShipUp n =>     {...state, velocity: (vx, vy -. ticksToThrust n)};
    | I.ShipDown n =>   {...state, velocity: (vx, vy +. ticksToThrust n)};
    | I.ShipLeft n =>   {...state, velocity: (vx -. ticksToThrust n, vy)};
    | I.ShipRight n =>  {...state, velocity: (vx +. ticksToThrust n, vy)};
    | I.ShipShoot =>    {...state, bullets: (List.append state.bullets [(x, y)])};
    };
  }) state cmds;

  let bullets = List.map (fun (x, y) => (x, y -. bulletSpeed)) stateFromInputs.bullets;

  let applyFriction = V.scale 0.9;
  let (vx, vy) = stateFromInputs.velocity |> applyFriction |> V.limitMagnitide maxSpeed;
  let (x,y) = state.position;
  let position = (x +. vx, y +. vy);
  {bullets, velocity: (vx, vy), position};
};
