open Jest;
open EmptyCssImpl.Legacy;

let toBeJson = (e, x) => toBe(e, x->Js.Json.stringifyAny);
let r = x => toJson([x])->Js.Json.stringifyAny; /* simple rule for more readable tests */

describe("Fill", () =>
  test("test values", () => {
    expect(r(SVG.fill(hex("FF0044"))))->toBeJson({"fill": "#FF0044"});
    expect(r(SVG.fill(url("#mydef"))))->toBeJson({"fill": "url(#mydef)"});
    expect(r(SVG.fill(`contextFill)))->toBeJson({"fill": "context-fill"});
    expect(r(SVG.fill(`contextStroke)))
    ->toBeJson({"fill": "context-stroke"});
    expect(r(SVG.fill(`none)))->toBeJson({"fill": "none"});
  })
);
/*
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
 */
