module C = Canvas;
module StarField = StarField;
module Ship = Ship;
module Enemy = Enemy;
module Input = Input;


type gamePhase =
  | TitleScreen
  | Level
  | GameOver;

type state = {
  mutable phase: gamePhase,
  mutable ship: Ship.t,
  mutable enemies: list Enemy.t,
  mutable score: int,
  startTime: float
};
let gameState = {
  phase: TitleScreen,
  ship: Ship.initialState,
  enemies: [],
  score: 0,
  startTime: Js.Date.now ()
};

let setupDraw = fun canvas => {
  let ctx = C.CanvasElement.get2dContext canvas;
  C.font ctx "40px Joystix, monospace";
  C.textAlign ctx "center";

  let rec render = fun () => {
    let now = Js.Date.now ();
    let runTime = now -. gameState.startTime;

    C.clearRect ctx 0. 0. C.width C.height;
    StarField.draw ctx zDepth::0.6 runTime;
    StarField.draw ctx offset::(100., 200.) runTime;
    List.iter (Enemy.draw ctx) gameState.enemies;

    switch (gameState.phase) {
    | TitleScreen =>
      C.fillText ctx "shmup.re" (C.width /. 2.) (C.height /. 2.);
      C.fillText ctx "Hit any key to start" (C.width /. 2.) (C.height /. 2. +. 60.);
    | Level =>
      Ship.draw ctx gameState.ship;
      C.fillText ctx (string_of_int gameState.score) (C.width /. 2.) 40.;
    | GameOver => C.fillText ctx "Game Over" (C.width /. 2.) (C.height /. 2.);
    };

    ReasonJs.requestAnimationFrame render;
  };
  let _ = ReasonJs.requestAnimationFrame render;
};

let gameLoop = fun () => {
  /* TODO: don't update ship & collision checks if game is over */
  let cmds = Input.sample ();
  let onEnemKilled = fun () => gameState.score = gameState.score + 1;
  gameState.ship = Ship.tick gameState.ship cmds;
  gameState.enemies = List.map Enemy.tick gameState.enemies
                      |> Enemy.cull C.width C.height
                      |> Enemy.managePopulation gameState.startTime
                      |> Enemy.checkBullets gameState.ship.bullets onEnemKilled;
  let died = Enemy.checkShip gameState.ship.position gameState.enemies;
  gameState.phase = switch (gameState.phase, died) {
  | (Level, false) => Level;
  | (_, true) | (GameOver, _) => GameOver;
  | _ => TitleScreen;
  };
};

let startOnAnyKey () => {
  open ReasonJs.Dom;
  DocumentRe.addEventListener "keydown" (fun _ => {
    switch gameState.phase {
    | TitleScreen => gameState.phase = Level;
    | _ => ()
    }
  }) document;
};

let init = fun () => {
  open ReasonJs.Dom;
  let canvasEl = DocumentRe.querySelector "canvas" document;
  switch canvasEl {
  | Some canv => setupDraw canv
  | None => Js.log "couldnt get canvas"
  };

  Input.bindListeners ();
  startOnAnyKey ();
  Js.Global.setInterval gameLoop 33;
};

init ();
