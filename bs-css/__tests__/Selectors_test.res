open Jest
open EmptyCssImpl.Legacy

let ruleSelector = display(block)
let ruleJson = {"display": "block"}
let toBe = (e, x) => Jest.toBe(e, x->Js.Json.stringifyAny)
let expect = x =>
  Jest.expect(toJson(list{x})->Js.Json.stringifyAny) /* simple rule for more readable tests */

describe("Pseudo classes", () => {
  test("test selectors that have no parameters", () => {
    expect(active(list{ruleSelector}))->toBe({":active": ruleJson})
    expect(checked(list{ruleSelector}))->toBe({":checked": ruleJson})
    expect(default(list{ruleSelector}))->toBe({":default": ruleJson})
    expect(defined(list{ruleSelector}))->toBe({":defined": ruleJson})
    expect(disabled(list{ruleSelector}))->toBe({":disabled": ruleJson})
    expect(empty(list{ruleSelector}))->toBe({":empty": ruleJson})
    expect(enabled(list{ruleSelector}))->toBe({":enabled": ruleJson})
    expect(first(list{ruleSelector}))->toBe({":first": ruleJson})
    expect(firstChild(list{ruleSelector}))->toBe({":first-child": ruleJson})
    expect(firstOfType(list{ruleSelector}))->toBe({":first-of-type": ruleJson})
    expect(focus(list{ruleSelector}))->toBe({":focus": ruleJson})
    expect(focusVisible(list{ruleSelector}))->toBe({":focus-visible": ruleJson})
    expect(focusWithin(list{ruleSelector}))->toBe({":focus-within": ruleJson})
    expect(hover(list{ruleSelector}))->toBe({":hover": ruleJson})
    expect(indeterminate(list{ruleSelector}))->toBe({":indeterminate": ruleJson})
    expect(inRange(list{ruleSelector}))->toBe({":in-range": ruleJson})
    expect(invalid(list{ruleSelector}))->toBe({":invalid": ruleJson})
    expect(lastChild(list{ruleSelector}))->toBe({":last-child": ruleJson})
    expect(lastOfType(list{ruleSelector}))->toBe({":last-of-type": ruleJson})
    expect(link(list{ruleSelector}))->toBe({":link": ruleJson})
    expect(onlyChild(list{ruleSelector}))->toBe({":only-child": ruleJson})
    expect(onlyOfType(list{ruleSelector}))->toBe({":only-of-type": ruleJson})
    expect(optional(list{ruleSelector}))->toBe({":optional": ruleJson})
    expect(outOfRange(list{ruleSelector}))->toBe({":out-of-range": ruleJson})
    expect(readOnly(list{ruleSelector}))->toBe({":read-only": ruleJson})
    expect(readWrite(list{ruleSelector}))->toBe({":read-write": ruleJson})
    expect(required(list{ruleSelector}))->toBe({":required": ruleJson})
    expect(root(list{ruleSelector}))->toBe({":root": ruleJson})
    expect(scope(list{ruleSelector}))->toBe({":scope": ruleJson})
    expect(target(list{ruleSelector}))->toBe({":target": ruleJson})
    expect(valid(list{ruleSelector}))->toBe({":valid": ruleJson})
    expect(visited(list{ruleSelector}))->toBe({":visited": ruleJson})
  })

  test("test host", () => {
    expect(host(list{ruleSelector}))->toBe({":host": ruleJson})
    expect(host(~selector=".special-custom-element", list{ruleSelector}))->toBe({
      ":host(.special-custom-element)": ruleJson,
    })
  })

  test("test not", () => expect(not_("p", list{ruleSelector}))->toBe({":not(p)": ruleJson}))

  test("test nth-child", () => {
    expect(nthChild(#odd, list{ruleSelector}))->toBe({":nth-child(odd)": ruleJson})
    expect(nthChild(#even, list{ruleSelector}))->toBe({":nth-child(even)": ruleJson})
    expect(nthChild(#n(2), list{ruleSelector}))->toBe({":nth-child(2n)": ruleJson})
    expect(nthChild(#add((3, 4)), list{ruleSelector}))->toBe({":nth-child(3n+4)": ruleJson})
  })

  test("test nth-last-child", () => {
    expect(nthLastChild(#odd, list{ruleSelector}))->toBe({":nth-last-child(odd)": ruleJson})
    expect(nthLastChild(#even, list{ruleSelector}))->toBe({":nth-last-child(even)": ruleJson})
    expect(nthLastChild(#n(2), list{ruleSelector}))->toBe({":nth-last-child(2n)": ruleJson})
    expect(nthLastChild(#add((3, 4)), list{ruleSelector}))->toBe({
      ":nth-last-child(3n+4)": ruleJson,
    })
  })

  test("test nth-last-of-type", () => {
    expect(nthLastOfType(#odd, list{ruleSelector}))->toBe({":nth-last-of-type(odd)": ruleJson})
    expect(nthLastOfType(#even, list{ruleSelector}))->toBe({":nth-last-of-type(even)": ruleJson})
    expect(nthLastOfType(#n(2), list{ruleSelector}))->toBe({":nth-last-of-type(2n)": ruleJson})
    expect(nthLastOfType(#add((3, 4)), list{ruleSelector}))->toBe({
      ":nth-last-of-type(3n+4)": ruleJson,
    })
  })

  test("test nth-of-type", () => {
    expect(nthOfType(#odd, list{ruleSelector}))->toBe({":nth-of-type(odd)": ruleJson})
    expect(nthOfType(#even, list{ruleSelector}))->toBe({":nth-of-type(even)": ruleJson})
    expect(nthOfType(#n(2), list{ruleSelector}))->toBe({":nth-of-type(2n)": ruleJson})
    expect(nthOfType(#add((3, 4)), list{ruleSelector}))->toBe({":nth-of-type(3n+4)": ruleJson})
  })
})

describe("Pseudo classes", () =>
  test("test selectors that have no parameters", () => {
    expect(after(list{ruleSelector}))->toBe({"::after": ruleJson})
    expect(before(list{ruleSelector}))->toBe({"::before": ruleJson})
    expect(firstLetter(list{ruleSelector}))->toBe({"::first-letter": ruleJson})
    expect(firstLine(list{ruleSelector}))->toBe({"::first-line": ruleJson})
    expect(placeholder(list{ruleSelector}))->toBe({"::placeholder": ruleJson})
    expect(selection(list{ruleSelector}))->toBe({"::selection": ruleJson})
  })
)

describe("Combinators", () =>
  test("test selectors", () => {
    expect(child("li", list{ruleSelector}))->toBe({" > li": ruleJson})
    expect(children(list{ruleSelector}))->toBe({" > *": ruleJson})
    expect(siblings(list{ruleSelector}))->toBe({" ~ ": ruleJson})
    expect(directSibling(list{ruleSelector}))->toBe({" + ": ruleJson})
  })
)
