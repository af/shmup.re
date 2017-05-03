module C = Canvas;
module HiScore = HiScore;

let initialHiScore = HiScore.get ();

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

let drawScores score ::hi=0 ctx => {
  let hiScore = max hi initialHiScore;
  C.textAlign ctx "right";
  C.fillText ctx ("hi:" ^ string_of_int hiScore) (C.width -. 20.) 40.;
  C.textAlign ctx "center";
  C.fillText ctx (string_of_int score) (C.width /. 2.) 40.;
};

let drawGameOver score ctx => {
  HiScore.set score;
  drawScores score hi::score ctx;
  C.fillText ctx "Game Over" (C.width /. 2.) (C.height /. 2.);
}
