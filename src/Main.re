module ReasonJs = ReasonJs;

module V = Vector;

module Canvas = ReasonJs.Canvas2d;

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
  mutable enemies: list(Enemy.t),
  mutable score: int,
  startTime: float
};

let gameState = {
  phase: TitleScreen,
  ship: Ship.initialState,
  enemies: [],
  score: 0,
  startTime: Js.Date.now()
};

let setupDraw = (canvas) => {
  let ctx = ReasonJs.CanvasElement.getContext2d(canvas) |> Ui.init;
  let rec render = (_) => {
    let now = Js.Date.now();
    let elapsedTime = now -. gameState.startTime;
    Canvas.clearRect(ctx, ~x=0., ~y=0., ~w=V.worldWidth, ~h=V.worldHeight);
    StarField.draw(ctx, ~zDepth=0.6, elapsedTime);
    StarField.draw(ctx, ~offset=(100., 200.), elapsedTime);
    List.iter(Enemy.draw(ctx), gameState.enemies);
    switch gameState.phase {
    | TitleScreen => Ui.drawTitle(ctx)
    | Level =>
      Ship.draw(ctx, gameState.ship);
      Ui.drawScores(gameState.score, ctx)
    | GameOver => Ui.drawGameOver(gameState.score, ctx)
    };
    ReasonJs.requestAnimationFrame(render)
  };
  let _ = ReasonJs.requestAnimationFrame(render);
  ()
};

let gameLoop = () => {
  let onEnemKilled = () => gameState.score = gameState.score + 1;
  let cmds = Input.sample();
  gameState.phase = (
    switch gameState.phase {
    | Level =>
      gameState.enemies =
        List.map(Enemy.tick, gameState.enemies)
        |> Enemy.cull(V.worldWidth, V.worldHeight)
        |> Enemy.managePopulation(gameState.startTime)
        |> Enemy.checkBullets(gameState.ship.bullets, onEnemKilled);
      gameState.ship = Ship.tick(gameState.ship, cmds);
      let died = Enemy.checkShip(gameState.ship.position, gameState.enemies);
      died ? GameOver : Level
    | GameOver =>
      gameState.enemies = List.map(Enemy.tick, gameState.enemies);
      GameOver
    | TitleScreen => TitleScreen
    }
  )
};

let startOnAnyKey = () =>
  ReasonJs.Dom.(
    DocumentRe.addEventListener(
      "keydown",
      (_) =>
        switch gameState.phase {
        | TitleScreen => gameState.phase = Level
        | GameOver
        | Level => ()
        },
      document
    )
  );

let init = () => {
  open ReasonJs.Dom;
  let canvasEl = DocumentRe.querySelector("canvas", document);
  switch canvasEl {
  | Some(canv) => setupDraw(canv)
  | None => Js.log("couldnt get canvas")
  };
  Input.bindListeners();
  startOnAnyKey();
  Js.Global.setInterval(gameLoop, 33)
};

init();
