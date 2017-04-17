/* Simple utilities for dealing with (x, y) float vectors */

let limitMagnitide = fun maxMag (vx, vy) => {
  let magnitude = sqrt (vx *. vx +. vy *. vy);
  if (magnitude > maxMag) {
    let scale = maxMag /. magnitude;
    (vx *. scale, vy *. scale);
  } else {
    (vx, vy);
  }
};

let scale = fun coeff (vx, vy) => {
  (vx *. coeff, vy *. coeff);
};
