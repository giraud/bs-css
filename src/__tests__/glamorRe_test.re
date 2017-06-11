open Jest;

open Expect;

open GlamorRe;

/*
  We only test that a CSS spec is translated to *something* (not an empty string) without errors.
  TODO: Check that it's translated to the correct CSS.
*/

let check result => expect result |> not_ |> toBe "";

describe
  "Glamor"
  (fun _ => test "takes a single CSS property" (fun _ => check (css [fontFamily "Arial"])));
