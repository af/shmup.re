module C = Canvas;

let stars = [|
  (100, 100),
  (150, 290),
  (190, 540),
  (350, 210),
  (550, 390),
  (600, 10)
|];

let draw = fun ctx offset::(offsetX, offsetY)=(0,0) ::speed=1 runTime => {
  C.fillStyle ctx "white";
  Array.iter (fun (baseX, baseY) => {
    let timeFactor = (int_of_float runTime) / 20;
    let x = baseX + offsetX;
    let y = (baseY + offsetY + speed * timeFactor) mod C.height;
    let starSize = 2;
    C.fillRect ctx x y starSize starSize;
  }) stars;
};
