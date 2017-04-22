type ctx;

let width = 800.;
let height = 600.;

module CanvasElement = {
  external getContext : Dom.element => string => ctx = "" [@@bs.send];
  external setWidth : Dom.element => float => unit = "length" [@@bs.set];
};

external strokeStyle : ctx => string => unit = "strokeStyle" [@@bs.set];
external fillStyle : ctx => string => unit = "fillStyle" [@@bs.set];

external fillRect : ctx => float => float => float => float => unit = "fillRect" [@@bs.send];
external strokeRect : ctx => float => float => float => float => unit = "strokeRect" [@@bs.send];
external clearRect : ctx => float => float => float => float => unit = "clearRect" [@@bs.send];

external save : ctx => unit = "save" [@@bs.send];
external restore : ctx => unit = "restore" [@@bs.send];
external translate : ctx => float => float => unit = "translate" [@@bs.send];
external rotate : ctx => float => unit = "rotate" [@@bs.send];

external beginPath : ctx => unit = "beginPath" [@@bs.send];
external closePath : ctx => unit = "closePath" [@@bs.send];
external moveTo : ctx => float => float => unit = "moveTo" [@@bs.send];
external lineTo : ctx => float => float => unit = "lineTo" [@@bs.send];
external stroke : ctx => unit = "stroke" [@@bs.send];
external fill : ctx => unit = "fill" [@@bs.send];
external arcTo : ctx => float => float => float => float => float => unit = "arcTo" [@@bs.send];
