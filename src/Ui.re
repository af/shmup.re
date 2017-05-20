module V = Vector;
open ReasonJs.Canvas2d;
module HiScore = HiScore;

let (width, height) = (V.worldWidth, V.worldHeight);
let (halfWidth, halfHeight) = (width /. 2., height /. 2.);
let initialHiScore = HiScore.get ();

let init ctx => {
  font ctx "28px Joystix, monospace";
  textAlign ctx "center";
  ctx;
};

let drawTitle ctx => {
  font ctx "40px Joystix, monospace";
  ctx |> fillText "shmup.re" x::halfWidth y::halfHeight;
  font ctx "20px Joystix, monospace";
  ctx |> fillText "A retro shooter in ReasonML" x::halfWidth y::(halfHeight +. 40.);
  ctx |> fillText "Use the arrow and space keys" x::halfWidth y::(halfHeight +. 80.);
};

let drawScores score ::hi=0 ctx => {
  let hiScore = max hi initialHiScore;
  textAlign ctx "right";
  ctx |> fillText ("hi:" ^ string_of_int hiScore) x::(width -. 20.) y::40.;
  textAlign ctx "center";
  ctx |> fillText (string_of_int score) x::halfWidth y::40.;
};

let drawGameOver score ctx => {
  HiScore.set score;
  drawScores score hi::score ctx;
  ctx |> fillText "Game Over" x::halfWidth y::halfHeight;
}
