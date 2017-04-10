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
