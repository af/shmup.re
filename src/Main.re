module C = Canvas;
module StarField = StarField;
module Ship = Ship;
module Enemy = Enemy;
module Input = Input;
module Ui = Ui;


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
  let ctx = C.CanvasElement.get2dContext canvas |> Ui.init;

  let rec render = fun () => {
    let now = Js.Date.now ();
    let elapsedTime = now -. gameState.startTime;

    C.clearRect ctx 0. 0. C.width C.height;
    StarField.draw ctx zDepth::0.6 elapsedTime;
    StarField.draw ctx offset::(100., 200.) elapsedTime;
    List.iter (Enemy.draw ctx) gameState.enemies;

    switch (gameState.phase) {
    | TitleScreen => Ui.drawTitle ctx;
    | Level =>
      Ship.draw ctx gameState.ship;
      Ui.drawScore gameState.score ctx;
    | GameOver => Ui.drawGameOver gameState.score ctx;
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
