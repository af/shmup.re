module C = Canvas;

let init ctx => {
  C.font ctx "28px Joystix, monospace";
  C.textAlign ctx "center";
  ctx;
};

let drawTitle ctx => {
  C.font ctx "40px Joystix, monospace";
  C.fillText ctx "shmup.re" (C.width /. 2.) (C.height /. 2.);
  C.font ctx "20px Joystix, monospace";
  C.fillText ctx "Use arrow and space keys" (C.width /. 2.) (C.height /. 2. +. 40.);
  C.fillText ctx "Hit any key to start" (C.width /. 2.) (C.height /. 2. +. 80.);
};

let drawScore score ctx => {
  C.fillText ctx (string_of_int score) (C.width /. 2.) 40.;
};

let drawGameOver score ctx => {
  drawScore score ctx;
  C.fillText ctx "Game Over" (C.width /. 2.) (C.height /. 2.);
}
