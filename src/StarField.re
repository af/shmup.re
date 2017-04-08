open Canvas;

/* TODO: remove this duplication */
let width = 800;
let height = 600;

let stars = [|
  (100, 100),
  (150, 190),
  (350, 210),
  (550, 390),
  (600, 10)
|];

let draw = fun offset speed ctx runTime => {
  let (offsetX, offsetY) = offset;
  fillStyle ctx "white";
  Array.iter (fun (baseX, baseY) => {
    let timeFactor = (int_of_float runTime) / 20;
    let x = baseX + offsetX;
    let y = (baseY + offsetY + speed * timeFactor) mod height;
    let size = 2;
    fillRect ctx x y size size;
  }) stars;
};
