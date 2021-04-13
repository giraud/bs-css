open Jest;
open Expect;
open EmptyCssImpl.Legacy;

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

describe("strokeDasharray", () => {
  test("test values", () =>
    expect(
      (
        r(SVG.strokeDasharray(`dasharray([1->px, 2->px, 3->px, 4->px]))),
        r(
          SVG.strokeDasharray(
            `dasharray([1.->pct, 2.->pct, 3.->pct, 4.->pct]),
          ),
        ),
        r(
          SVG.strokeDasharray(`dasharray([1->px, 2.->pct, 3->px, 4.->pct])),
        ),
        r(
          SVG.strokeDasharray(`dasharray([1.->pct, 2->px, 3.->pct, 4->px])),
        ),
        r(SVG.strokeDasharray(`none)),
      )
      ->Js.Json.stringifyAny,
    )
    |> toBeJson((
         {"strokeDasharray": "1px 2px 3px 4px"},
         {"strokeDasharray": "1% 2% 3% 4%"},
         {"strokeDasharray": "1px 2% 3px 4%"},
         {"strokeDasharray": "1% 2px 3% 4px"},
         {"strokeDasharray": "none"},
       ))
  )
});
