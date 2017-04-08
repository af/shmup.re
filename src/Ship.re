open Canvas;

let size = 20;

let draw = fun ctx {x, y} => {
  strokeStyle ctx "white";
  beginPath ctx;
  moveTo ctx x (y + size / 4);
  lineTo ctx (x + size / 2) (y + size / 2);
  lineTo ctx x (y - size / 2);
  lineTo ctx (x - size / 2) (y + size / 2);
  lineTo ctx x (y + size / 4);
  stroke ctx;
};
