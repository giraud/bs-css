module CssForTest = {
  include Css_Core;
  include Css_Core.Make({
    exception NotImplemented;

    let mergeStyles = (. _) => raise(NotImplemented);
    let make = (. _) => raise(NotImplemented);
    let injectRule = (. _) => raise(NotImplemented);
    let injectRaw = (. _) => raise(NotImplemented);
    let makeKeyFrames = (. _) => raise(NotImplemented);
  });
};

open Jest;
open Expect;
open CssForTest;

let toBeJson = x => Expect.toBe(x->Js.Json.stringifyAny);
let r = x => toJson([x]); /* simple rule for more readable tests */

describe("Fill", () =>
  test("test values", () =>
    expect(
      (
        r(SVG.fill(hex("FF0044"))),
        r(SVG.fill(url("#mydef"))),
        r(SVG.fill(`contextFill)),
        r(SVG.fill(`contextStroke)),
        r(SVG.fill(`none)),
      )
      ->Js.Json.stringifyAny,
    )
    |> toBeJson((
         {"fill": "#FF0044"},
         {"fill": "url(#mydef)"},
         {"fill": "context-fill"},
         {"fill": "context-stroke"},
         {"fill": "none"},
       ))
  )
);