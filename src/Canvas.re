type ctx;

module CanvasElement = {
  external getContext : Dom.element => string => ctx = "" [@@bs.send];
};

external fillStyle : ctx => string => unit = "fillStyle" [@@bs.set];
external fillRect : ctx => int => int => int => int => unit = "fillRect" [@@bs.send];
external clearRect : ctx => int => int => int => int => unit = "clearRect" [@@bs.send];
