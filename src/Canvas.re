type ctx;

let width = 800.;
let height = 600.;

module CanvasElement = {
  external getContext : Dom.element => string => ctx = "" [@@bs.send];
};

external strokeStyle : ctx => string => unit = "strokeStyle" [@@bs.set];
external fillStyle : ctx => string => unit = "fillStyle" [@@bs.set];

external fillRect : ctx => float => float => float => float => unit = "fillRect" [@@bs.send];
external clearRect : ctx => float => float => float => float => unit = "clearRect" [@@bs.send];

external beginPath : ctx => unit = "beginPath" [@@bs.send];
external moveTo : ctx => float => float => unit = "moveTo" [@@bs.send];
external lineTo : ctx => float => float => unit = "lineTo" [@@bs.send];
external stroke : ctx => unit = "stroke" [@@bs.send];
