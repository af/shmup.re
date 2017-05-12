module C = Canvas;
open ReasonJs.Canvas2d;
module HiScore = HiScore;

let initialHiScore = HiScore.get ();

let init ctx => {
  font ctx "28px Joystix, monospace";
  textAlign ctx "center";
  ctx;
};

let drawTitle ctx => {
  font ctx "40px Joystix, monospace";
  ctx |> fillText "shmup.re" x::(C.width /. 2.) y::(C.height /. 2.);
  font ctx "20px Joystix, monospace";
  ctx |> fillText "Use arrow and space keys" x::(C.width /. 2.) y::(C.height /. 2. +. 40.);
  ctx |> fillText "Hit any key to start" x::(C.width /. 2.) y::(C.height /. 2. +. 80.);
};

let drawScores score ::hi=0 ctx => {
  let hiScore = max hi initialHiScore;
  textAlign ctx "right";
  ctx |> fillText ("hi:" ^ string_of_int hiScore) x::(C.width -. 20.) y::40.;
  textAlign ctx "center";
  ctx |> fillText (string_of_int score) x::(C.width /. 2.) y::40.;
};

let drawGameOver score ctx => {
  HiScore.set score;
  drawScores score hi::score ctx;
  ctx |> fillText "Game Over" x::(C.width /. 2.) y::(C.height /. 2.);
}
