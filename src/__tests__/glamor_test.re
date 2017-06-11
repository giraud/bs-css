open Jest;

open Expect;

open Glamor;

/*
  We only test that a CSS spec is translated to *something* (not an empty string) without errors.
  TODO: Check that it's translated to the correct CSS.
*/

let check result => expect result |> not_ |> toBe "";

describe
  "Glamor"
  (fun _ => {
    test "takes a single CSS property" (fun _ => check (
      css [
        fontFamily "Arial"
      ]
    ));

    test "takes multiple properties" (fun _ => check (
      css [
        fontFamily "Arial",
        fontSize "12pt"
      ]
    ));

    test "takes an empty property list" (fun _ => check (
      css []
    ));

    test "takes selectors" (fun _ => check (
      css [
        Selector "@media (min-width: 300px)" [
          color "blue"
        ]
      ]
    ));

    test "takes nested selectors" (fun _ => check (
      css [
        Selector "@media (min-width: 300px)" [
          color "blue",
          Selector "@media (max-width: 500px)" [
            color "red"
          ]
        ]
      ]
    ));
  });
