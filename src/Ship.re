open Canvas;    /* Needed to get access to point type (?) */
module C = Canvas;

let size = 20;

let draw = fun ctx {x, y} => {
  let noseLength = size / 2;
  let wingLength = size / 2;
  let tailLength = size / 4;

  C.strokeStyle ctx "white";
  C.beginPath ctx;
  C.moveTo ctx x (y + tailLength);
  C.lineTo ctx (x + wingLength) (y + noseLength);
  C.lineTo ctx x (y - noseLength);
  C.lineTo ctx (x - wingLength) (y + noseLength);
  C.lineTo ctx x (y + tailLength);
  C.stroke ctx;
};
