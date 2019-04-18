open Jest;
open Expect;
open Css;

let toBeJson = x => Expect.toBe(x->Js.Json.stringifyAny);
let r = x => toJson([x]); /* simple rule for more readable tests */

describe("Color style", () =>
  test("test values", () =>
    expect(
      (
        r(color(rgb(1, 2, 3))),
        r(color(rgba(4, 5, 6, 0.3))),
        r(color(hsl(7, 8, 9))),
        r(color(hsla(10, 11, 12, 0.5))),
        r(color(transparent)),
        r(color(hex("FFF"))),
        r(color(currentColor)),
      )
      ->Js.Json.stringifyAny,
    )
    |> toBeJson((
         {"color": "rgb(1, 2, 3)"},
         {"color": "rgba(4, 5, 6, 0.3)"},
         {"color": "hsl(7, 8%, 9%)"},
         {"color": "hsla(10, 11%, 12%, 0.5)"},
         {"color": "transparent"},
         {"color": "#FFF"},
         {"color": "currentColor"},
       ))
  )
);

describe("Label", () => {
  test("test value", () =>
    expect(r(label("a"))->Js.Json.stringifyAny) |> toBeJson({"label": "a"})
  );
  test("test classname", () =>
    expect(style([label("theName")])) |> toContainString("theName")
  );
});

describe("Filter", () =>
  test("test values", () =>
    expect(
      (
        r(Css.filter([`opacity(10.), `invert(20.)])),
        r(Css.filter([`blur(`px(20)), `brightness(20.)])),
        r(
          Css.filter([
            `contrast(30.),
            `dropShadow((`px(5), `px(6), `px(7), `rgb((255, 0, 0)))),
          ]),
        ),
        r(Css.filter([`grayscale(10.), `hueRotate(`deg(180))])),
        r(Css.filter([`saturate(10.), `sepia(100.)])),
        r(Css.filter([`none])),
        r(Css.filter([`inherit_])),
        r(Css.filter([`initial])),
        r(Css.filter([`unset])),
        r(Css.filter([`url("myurl")])),
      )
      ->Js.Json.stringifyAny,
    )
    |> toBeJson((
         {"filter": "opacity(10%) invert(20%)"},
         {"filter": "blur(20px) brightness(20%)"},
         {"filter": "contrast(30%) drop-shadow(5px 6px 7px rgb(255, 0, 0))"},
         {"filter": "grayscale(10%) hue-rotate(180deg)"},
         {"filter": "saturate(10%) sepia(100%)"},
         {"filter": "none"},
         {"filter": "inherit"},
         {"filter": "initial"},
         {"filter": "unset"},
         {"filter": "url(myurl)"},
       ))
  )
);
