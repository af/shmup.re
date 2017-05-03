open ReasonJs.Storage;

let _KEY = "hiScore";

let get () => {
  let score = localStorage |> getItem _KEY;
  switch score {
  | Some x => int_of_string x
  | None => 0
  };
};

let set score => {
  let currentHi = get ();
  (score > currentHi)
    ? localStorage |> setItem _KEY (string_of_int score)
    : ();
}
