open Jest
open EmptyCssImpl.Legacy

let toBeJson = (e, x) => toBe(e, x->Js.Json.stringifyAny)
let r = x => toJson(list{x})->Js.Json.stringifyAny /* simple rule for more readable tests */

describe("Fill", () =>
  test("test values", () => {
    expect(r(SVG.fill(hex("FF0044"))))->toBeJson({"fill": "#FF0044"})
    expect(r(SVG.fill(url("#mydef"))))->toBeJson({"fill": "url(#mydef)"})
    expect(r(SVG.fill(#contextFill)))->toBeJson({"fill": "context-fill"})
    expect(r(SVG.fill(#contextStroke)))->toBeJson({"fill": "context-stroke"})
    expect(r(SVG.fill(#none)))->toBeJson({"fill": "none"})
  })
)
