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
        r(color(hsl(deg(7.), 8., 9.))),
        r(color(hsla(deg(10.), 11., 12., `num(0.5)))),
        r(color(hsla(rad(4.7), 11., 12., pct(50.)))),
        r(color(transparent)),
        r(color(hex("FFF"))),
        r(color(currentColor)),
      )
      ->Js.Json.stringifyAny,
    )
    |> toBeJson((
         {"color": "rgb(1, 2, 3)"},
         {"color": "rgba(4, 5, 6, 0.3)"},
         {"color": "hsl(7deg, 8%, 9%)"},
         {"color": "hsla(10deg, 11%, 12%, 0.5)"},
         {"color": "hsla(4.7rad, 11%, 12%, 50%)"},
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
        r(Css.filter([`grayscale(10.), `hueRotate(`deg(180.))])),
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

describe("Angle", () =>
  test("test values", () =>
    expect(
      (
        r(transform(rotate(deg(1.)))),
        r(transform(rotate(rad(6.28)))),
        r(transform(rotate(grad(38.8)))),
        r(transform(rotate(turn(0.25)))),
      )
      ->Js.Json.stringifyAny,
    )
    |> toBeJson((
         {"transform": "rotate(1deg)"},
         {"transform": "rotate(6.28rad)"},
         {"transform": "rotate(38.8grad)"},
         {"transform": "rotate(0.25turn)"},
       ))
  )
);

describe("Direction", () =>
  test("test values", () =>
    expect(
      (
        r(Css.direction(`ltr)),
        r(Css.direction(ltr)),
        r(Css.direction(rtl)),
        r(Css.direction(inherit_)),
        r(Css.direction(unset)),
        r(Css.direction(initial)),
      )
      ->Js.Json.stringifyAny,
    )
    |> toBeJson((
         {"direction": "ltr"},
         {"direction": "ltr"},
         {"direction": "rtl"},
         {"direction": "inherit"},
         {"direction": "unset"},
         {"direction": "initial"},
       ))
  )
);

describe("Resize", () =>
  test("test values", () =>
    expect(
      (
        r(Css.resize(none)),
        r(Css.resize(both)),
        r(Css.resize(horizontal)),
        r(Css.resize(vertical)),
        r(Css.resize(block)),
        r(Css.resize(inline)),
        r(Css.resize(inherit_)),
        r(Css.resize(unset)),
        r(Css.resize(initial)),
      )
      ->Js.Json.stringifyAny,
    )
    |> toBeJson((
         {"resize": "none"},
         {"resize": "both"},
         {"resize": "horizontal"},
         {"resize": "vertical"},
         {"resize": "block"},
         {"resize": "inline"},
         {"resize": "inherit"},
         {"resize": "unset"},
         {"resize": "initial"},
       ))
  )
);

describe("Gradient background", () =>
  test("test values", () =>
    expect(
      (
        r(
          background(
            linearGradient(deg(45.), [(zero, red), (pct(100.), blue)]),
          ),
        ),
        r(
          background(
            repeatingLinearGradient(
              deg(45.),
              [(zero, red), (px(10), blue)],
            ),
          ),
        ),
        r(background(radialGradient([(zero, red), (pct(100.), blue)]))),
        r(
          background(
            repeatingRadialGradient([
              (zero, red),
              (Calc.(pct(20.) + px(5)), blue),
            ]),
          ),
        ),
      )
      ->Js.Json.stringifyAny,
    )
    |> toBeJson((
         {"background": "linear-gradient(45deg, #FF0000 0, #0000FF 100%)"},
         {
           "background": "repeating-linear-gradient(45deg, #FF0000 0, #0000FF 10px)",
         },
         {"background": "radial-gradient(#FF0000 0, #0000FF 100%)"},
         {
           "background": "repeating-radial-gradient(#FF0000 0, #0000FF calc(20% + 5px))",
         },
       ))
  )
);

describe("Position", () => {
  test("should use length", () =>
    expect(
      (
        r(Css.top(px(10))),
        r(Css.right(rem(1.))),
        r(Css.bottom(pct(20.))),
        r(Css.left(vh(4.))),
      )
      ->Js.Json.stringifyAny,
    )
    |> toBeJson((
         {"top": "10px"},
         {"right": "1rem"},
         {"bottom": "20%"},
         {"left": "4vh"},
       ))
  );
  test("should allow cascading", () =>
    expect(
      (
        r(Css.top(initial)),
        r(Css.right(inherit_)),
        r(Css.bottom(unset)),
        r(Css.left(initial)),
      )
      ->Js.Json.stringifyAny,
    )
    |> toBeJson((
         {"top": "initial"},
         {"right": "inherit"},
         {"bottom": "unset"},
         {"left": "initial"},
       ))
  );
});

describe("object-fit", () =>
  test("test values", () =>
    expect(
      (
        r(Css.objectFit(`fill)),
        r(Css.objectFit(`contain)),
        r(Css.objectFit(`cover)),
        r(Css.objectFit(`none)),
        r(Css.objectFit(`scaleDown)),
        r(Css.objectFit(`inherit_)),
        r(Css.objectFit(`initial)),
        r(Css.objectFit(`unset)),
      )
      ->Js.Json.stringifyAny,
    )
    |> toBeJson((
         {"objectFit": "fill"},
         {"objectFit": "contain"},
         {"objectFit": "cover"},
         {"objectFit": "none"},
         {"objectFit": "scale-down"},
         {"objectFit": "inherit"},
         {"objectFit": "initial"},
         {"objectFit": "unset"},
       ))
  )
);

describe("box-shadow", () => {
  test("should allow single or list definition", () =>
    expect(
      (
        r(Css.boxShadow(Css.green)),
        r(
          Css.boxShadows([
            Css.boxShadow(Css.yellow),
            Css.boxShadow(Css.red),
          ]),
        ),
      )
      ->Js.Json.stringifyAny,
    )
    |> toBeJson((
         {"boxShadow": "0 0 0 0 #008000"},
         {"boxShadow": "0 0 0 0 #FFFF00,0 0 0 0 #FF0000"},
       ))
  );

  test("should use options when present", () =>
    expect(
      (
        r(Css.boxShadow(~x=Css.px(1), ~y=Css.px(2), Css.red)),
        r(Css.boxShadow(~inset=true, Css.red)),
      )
      ->Js.Json.stringifyAny,
    )
    |> toBeJson((
         {"boxShadow": "1px 2px 0 0 #FF0000"},
         {"boxShadow": "0 0 0 0 #FF0000 inset"},
       ))
  );
});

describe("text-shadow", () => {
  test("should allow single or list definition", () =>
    expect(
      (
        r(Css.textShadow(Css.green)),
        r(
          Css.textShadows([
            Css.textShadow(Css.yellow),
            Css.textShadow(Css.red),
          ]),
        ),
      )
      ->Js.Json.stringifyAny,
    )
    |> toBeJson((
         {"textShadow": "0 0 0 #008000"},
         {"textShadow": "0 0 0 #FFFF00,0 0 0 #FF0000"},
       ))
  );

  test("should use options when present", () =>
    expect(
      (
        r(Css.textShadow(~x=Css.px(1), ~y=Css.px(2), Css.red)),
        r(Css.textShadow(~blur=Css.vh(1.), Css.red)),
      )
      ->Js.Json.stringifyAny,
    )
    |> toBeJson((
         {"textShadow": "1px 2px 0 #FF0000"},
         {"textShadow": "0 0 1vh #FF0000"},
       ))
  );
});
