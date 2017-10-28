/* Simple utilities for dealing with (x, y) float vectors */
let worldWidth = 500.;

let worldHeight = 700.;

let limitMagnitide = (maxMag, (vx, vy)) => {
  let magnitude = sqrt(vx *. vx +. vy *. vy);
  if (magnitude > maxMag) {
    let scale = maxMag /. magnitude;
    (vx *. scale, vy *. scale)
  } else {
    (vx, vy)
  }
};

let scale = (coeff, (vx, vy)) => (vx *. coeff, vy *. coeff);
