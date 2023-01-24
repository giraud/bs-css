module CssForTest = {
  include EmptyCssImpl.Legacy
}

open CssForTest
let describe = Jest.describe
let test = Jest.test
let toBe = (e, x) => Jest.toBe(e, x->Js.Json.stringifyAny)
let expect = x =>
  Jest.expect(toJson(list{x})->Js.Json.stringifyAny) /* simple rule for more readable tests */

describe("Var", () => {
  test("test usage (limited)", () => {
    expect(color(var("foo")))->toBe({"color": "var(--foo)"})
    expect(marginTop(var("--bar")))->toBe({"marginTop": "var(--bar)"})
  })

  test("test usage with default (limited)", () => {
    expect(textDecoration(varDefault("foo", "default")))->toBe({
      "textDecoration": "var(--foo,default)",
    })
    expect(alignItems(varDefault("--bar", "default")))->toBe({"alignItems": "var(--bar,default)"})
  })
})

describe("Color style", () =>
  test("test values", () => {
    expect(color(rgb(1, 2, 3)))->toBe({"color": "rgb(1, 2, 3)"})
    expect(color(rgba(4, 5, 6, #num(0.3))))->toBe({"color": "rgba(4, 5, 6, 0.3)"})
    expect(color(hsl(deg(7.), pct(8.), pct(9.))))->toBe({"color": "hsl(7deg, 8%, 9%)"})
    expect(color(hsla(deg(10.), pct(11.), pct(12.), #num(0.5))))->toBe({
      "color": "hsla(10deg, 11%, 12%, 0.5)",
    })
    expect(color(hsla(rad(4.7), pct(11.), pct(12.), pct(50.))))->toBe({
      "color": "hsla(4.7rad, 11%, 12%, 50%)",
    })
    expect(color(transparent))->toBe({"color": "transparent"})
    expect(color(hex("FFF")))->toBe({"color": "#FFF"})
    expect(color(currentColor))->toBe({"color": "currentColor"})
  })
)

describe("Label", () => {
  test("test value", () => expect(label("a"))->toBe({"label": "a"}))
})

describe("Filter", () =>
  test("test values", () => {
    expect(filter(list{#opacity(10.), #invert(20.)}))->toBe({"filter": "opacity(10%) invert(20%)"})
    expect(filter(list{#blur(#px(20)), #brightness(20.)}))->toBe({
      "filter": "blur(20px) brightness(20%)",
    })
    expect(
      filter(list{#contrast(30.), #dropShadow((#px(5), #px(6), #px(7), #rgb((255, 0, 0))))}),
    )->toBe({
      "filter": "contrast(30%) drop-shadow(5px 6px 7px rgb(255, 0, 0))",
    })
    expect(filter(list{#grayscale(10.), #hueRotate(#deg(180.))}))->toBe({
      "filter": "grayscale(10%) hue-rotate(180deg)",
    })
    expect(filter(list{#saturate(10.), #sepia(100.)}))->toBe({
      "filter": "saturate(10%) sepia(100%)",
    })
    expect(filter(list{#none}))->toBe({"filter": "none"})
    expect(filter(list{#inherit_}))->toBe({"filter": "inherit"})
    expect(filter(list{#initial}))->toBe({"filter": "initial"})
    expect(filter(list{#unset}))->toBe({"filter": "unset"})
    expect(filter(list{#url("myUrl")}))->toBe({"filter": "url(myUrl)"})
  })
)

describe("Angle", () =>
  test("test values", () => {
    expect(transform(rotate(deg(1.))))->toBe({"transform": "rotate(1deg)"})
    expect(transform(rotate(rad(6.28))))->toBe({"transform": "rotate(6.28rad)"})
    expect(transform(rotate(grad(38.8))))->toBe({"transform": "rotate(38.8grad)"})
    expect(transform(rotate(turn(0.25))))->toBe({"transform": "rotate(0.25turn)"})
  })
)

describe("Direction", () =>
  test("test values", () => {
    expect(direction(#ltr))->toBe({"direction": "ltr"})
    expect(direction(ltr))->toBe({"direction": "ltr"})
    expect(direction(rtl))->toBe({"direction": "rtl"})
    expect(direction(inherit_))->toBe({"direction": "inherit"})
    expect(direction(unset))->toBe({"direction": "unset"})
    expect(direction(initial))->toBe({"direction": "initial"})
  })
)

describe("Resize", () =>
  test("test values", () => {
    expect(resize(none))->toBe({"resize": "none"})
    expect(resize(both))->toBe({"resize": "both"})
    expect(resize(horizontal))->toBe({"resize": "horizontal"})
    expect(resize(vertical))->toBe({"resize": "vertical"})
    expect(resize(block))->toBe({"resize": "block"})
    expect(resize(inline))->toBe({"resize": "inline"})
    expect(resize(inherit_))->toBe({"resize": "inherit"})
    expect(resize(unset))->toBe({"resize": "unset"})
    expect(resize(initial))->toBe({"resize": "initial"})
  })
)

describe("Backdrop filter", () =>
  test("test values", () => {
    expect(backdropFilter(list{#none}))->toBe({"backdropFilter": "none"})
    expect(backdropFilter(list{#blur(#px(10)), #brightness(#percent(42.0))}))->toBe({
      "backdropFilter": "blur(10px), brightness(42%)",
    })
    expect(backdropFilter(list{#contrast(#num(10)), #dropShadow(#percent(0.5))}))->toBe({
      "backdropFilter": "contrast(10), drop-shadow(0.5%)",
    })
    expect(backdropFilter(list{#grayscale(#percent(99.9)), #hueRotate(#deg(90.0))}))->toBe({
      "backdropFilter": "grayscale(99.9%), hue-rotate(90deg)",
    })
    expect(backdropFilter(list{#invert(#num(30)), #opacity(#percent(10.0))}))->toBe({
      "backdropFilter": "invert(30), opacity(10%)",
    })
    expect(backdropFilter(list{#saturate(#num(30)), #sepia(#percent(10.0))}))->toBe({
      "backdropFilter": "saturate(30), sepia(10%)",
    })
  })
)

describe("Gradient background", () =>
  test("test values", () => {
    expect(background(linearGradient(deg(45.), [(zero, red), (pct(100.), blue)])))->toBe({
      "background": "linear-gradient(45deg, #FF0000 0, #0000FF 100%)",
    })
    expect(background(repeatingLinearGradient(deg(45.), [(zero, red), (px(10), blue)])))->toBe({
      "background": "repeating-linear-gradient(45deg, #FF0000 0, #0000FF 10px)",
    })
    expect(background(radialGradient([(zero, red), (pct(100.), blue)])))->toBe({
      "background": "radial-gradient(#FF0000 0, #0000FF 100%)",
    })
    open Calc
    expect(background(repeatingRadialGradient([(zero, red), (pct(20.) + px(5), blue)])))->toBe({
      "background": "repeating-radial-gradient(#FF0000 0, #0000FF calc(20% + 5px))",
    })
    expect(background(conicGradient(deg(45.), [(zero, red), (pct(100.), blue)])))->toBe({
      "background": "conic-gradient(from 45deg, #FF0000 0, #0000FF 100%)",
    })
  })
)

describe("Position", () => {
  test("should use length", () => {
    expect(top(px(10)))->toBe({"top": "10px"})
    expect(right(rem(1.)))->toBe({"right": "1rem"})
    expect(bottom(pct(20.)))->toBe({"bottom": "20%"})
    expect(left(vh(4.)))->toBe({"left": "4vh"})
  })

  test("should allow cascading", () => {
    expect(top(initial))->toBe({"top": "initial"})
    expect(right(inherit_))->toBe({"right": "inherit"})
    expect(bottom(unset))->toBe({"bottom": "unset"})
    expect(left(initial))->toBe({"left": "initial"})
  })
})

describe("isolation", () => {
  test("test values", () => {
    expect(isolation(auto))->toBe({"isolation": "auto"})
    expect(isolation(isolate))->toBe({"isolation": "isolate"})
    expect(isolation(inherit_))->toBe({"isolation": "inherit"})
    expect(isolation(initial))->toBe({"isolation": "initial"})
    expect(isolation(unset))->toBe({"isolation": "unset"})
  })
})

describe("object-fit", () =>
  test("test values", () => {
    expect(objectFit(#fill))->toBe({"objectFit": "fill"})
    expect(objectFit(#contain))->toBe({"objectFit": "contain"})
    expect(objectFit(#cover))->toBe({"objectFit": "cover"})
    expect(objectFit(#none))->toBe({"objectFit": "none"})
    expect(objectFit(#scaleDown))->toBe({"objectFit": "scale-down"})
    expect(objectFit(#inherit_))->toBe({"objectFit": "inherit"})
    expect(objectFit(#initial))->toBe({"objectFit": "initial"})
    expect(objectFit(#unset))->toBe({"objectFit": "unset"})
  })
)

describe("box-shadow", () => {
  test("should allow single or list definition", () => {
    expect(boxShadow(Shadow.box(green)))->toBe({"boxShadow": "0 0 0 0 #008000"})
    expect(boxShadows(list{Shadow.box(yellow), Shadow.box(red)}))->toBe({
      "boxShadow": "0 0 0 0 #FFFF00, 0 0 0 0 #FF0000",
    })
  })

  test("should use options when present", () => {
    expect(boxShadow(Shadow.box(~x=px(1), ~y=px(2), red)))->toBe({
      "boxShadow": "1px 2px 0 0 #FF0000",
    })
    expect(boxShadow(Shadow.box(~inset=true, red)))->toBe({"boxShadow": "0 0 0 0 #FF0000 inset"})
  })

  test("should allow special values", () => {
    expect(boxShadow(none))->toBe({"boxShadow": "none"})
    expect(boxShadow(inherit_))->toBe({"boxShadow": "inherit"})
    expect(boxShadow(initial))->toBe({"boxShadow": "initial"})
    expect(boxShadow(unset))->toBe({"boxShadow": "unset"})
    expect(important(boxShadow(none)))->toBe({"boxShadow": "none !important"})
  })
})

describe("text-shadow", () => {
  test("should allow single or list definition", () => {
    expect(textShadow(Shadow.text(green)))->toBe({"textShadow": "0 0 0 #008000"})
    expect(textShadows(list{Shadow.text(yellow), Shadow.text(red)}))->toBe({
      "textShadow": "0 0 0 #FFFF00, 0 0 0 #FF0000",
    })
  })

  test("should use options when present", () => {
    expect(textShadow(Shadow.text(~x=px(1), ~y=px(2), red)))->toBe({
      "textShadow": "1px 2px 0 #FF0000",
    })
    expect(textShadow(Shadow.text(~blur=vh(1.), red)))->toBe({"textShadow": "0 0 1vh #FF0000"})
  })

  test("should allow special values", () => {
    expect(textShadow(none))->toBe({"textShadow": "none"})
    expect(textShadow(inherit_))->toBe({"textShadow": "inherit"})
    expect(textShadow(initial))->toBe({"textShadow": "initial"})
    expect(textShadow(unset))->toBe({"textShadow": "unset"})
    expect(important(textShadow(none)))->toBe({"textShadow": "none !important"})
  })
})

describe("transitions", () => {
  test("should allow single or list definition", () => {
    expect(transition("transform"))->toBe({"transition": "0ms ease 0ms transform"})
    expect(transitions(list{Transition.shorthand("height"), Transition.shorthand("top")}))->toBe({
      "transition": "0ms ease 0ms height, 0ms ease 0ms top",
    })
  })

  test("should use options when present", () =>
    expect(transition(~duration=#ms(3.), ~delay=#ms(4.), ~timingFunction=easeOut, "top"))->toBe({
      "transition": "3ms ease-out 4ms top",
    })
  )
})

external toAnimationName: string => animationName = "%identity"

describe("animation", () => {
  test("should allow single or list definition", () => {
    expect(animation(toAnimationName("a")))->toBe({
      "animation": "a 0ms ease 0ms 1 normal none running",
    })
    expect(
      animations(list{
        Animation.shorthand(toAnimationName("a1")),
        Animation.shorthand(toAnimationName("a2")),
      }),
    )->toBe({
      "animation": "a1 0ms ease 0ms 1 normal none running, a2 0ms ease 0ms 1 normal none running",
    })
  })

  test("should use options when present", () =>
    expect(
      animation(
        ~duration=#ms(300.),
        ~delay=#ms(400.),
        ~direction=reverse,
        ~timingFunction=linear,
        ~fillMode=forwards,
        ~playState=running,
        ~iterationCount=infinite,
        toAnimationName("a"),
      ),
    )->toBe({
      "animation": "a 300ms linear 400ms infinite reverse forwards running",
    })
  )
})

describe("Word spacing", () =>
  test("test values", () => {
    expect(wordSpacing(#normal))->toBe({"wordSpacing": "normal"})
    expect(wordSpacing(vh(1.)))->toBe({"wordSpacing": "1vh"})
    expect(wordSpacing(pct(50.)))->toBe({"wordSpacing": "50%"})
    expect(wordSpacing(inherit_))->toBe({"wordSpacing": "inherit"})
  })
)

describe("gridTemplateAreas", () => {
  test("takes acceptable types & cascades", () => {
    expect(gridTemplateAreas(#none))->toBe({"gridTemplateAreas": "none"})
    expect(gridTemplateAreas(#areas(["a"])))->toBe({"gridTemplateAreas": "'a'"})
    expect(gridTemplateAreas(#inherit_))->toBe({"gridTemplateAreas": "inherit"})
    expect(gridTemplateAreas(#initial))->toBe({"gridTemplateAreas": "initial"})
    expect(gridTemplateAreas(#unset))->toBe({"gridTemplateAreas": "unset"})
  })

  test("successfully combines list", () => {
    expect(gridTemplateAreas(#areas(["a a a", "b b b"])))->toBe({
      "gridTemplateAreas": "'a a a' 'b b b'",
    })
  })
})

describe("GridArea", () => {
  test("gridArea takes values & cascades", () => {
    expect(gridArea(#auto))->toBe({"gridArea": "auto"})
    expect(gridArea(#ident("a")))->toBe({"gridArea": "a"})
    expect(gridArea(#num(1)))->toBe({"gridArea": "1"})
    expect(gridArea(#numIdent((1, "a"))))->toBe({"gridArea": "1 a"})
    expect(gridArea(#span(#num(1))))->toBe({"gridArea": "span 1"})
    expect(gridArea(#span(#ident("a"))))->toBe({"gridArea": "span a"})
    expect(gridArea(#inherit_))->toBe({"gridArea": "inherit"})
    expect(gridArea(#initial))->toBe({"gridArea": "initial"})
    expect(gridArea(#unset))->toBe({"gridArea": "unset"})
  })

  test("multi-arg functions add in slashes", () => {
    expect(gridArea2(#auto, #num(1)))->toBe({"gridArea": "auto / 1"})
    expect(gridArea3(#ident("a"), #numIdent((1, "a")), #auto))->toBe({"gridArea": "a / 1 a / auto"})
    expect(gridArea4(#num(5), #span(#num(16)), #span(#ident("b")), #auto))->toBe({
      "gridArea": "5 / span 16 / span b / auto",
    })
  })
})

describe("gridTemplateColumns", () => {
  test("concatenates list", () =>
    expect(gridTemplateColumns(list{#fr(1.), #px(100), #auto}))->toBe({
      "gridTemplateColumns": "1fr 100px auto",
    })
  )

  test("unfolds repeats", () => {
    expect(gridTemplateColumns(list{#repeat((#num(4), #fr(1.)))}))->toBe({
      "gridTemplateColumns": "repeat(4, 1fr)",
    })
    expect(gridTemplateColumns(list{#repeat((#num(4), #auto))}))->toBe({
      "gridTemplateColumns": "repeat(4, auto)",
    })
    expect(gridTemplateColumns(list{#repeat((#num(4), #minContent))}))->toBe({
      "gridTemplateColumns": "repeat(4, min-content)",
    })
    expect(gridTemplateColumns(list{#repeat((#num(4), #maxContent))}))->toBe({
      "gridTemplateColumns": "repeat(4, max-content)",
    })
    expect(gridTemplateColumns(list{#repeat((#num(4), #minmax((#px(100), #fr(1.)))))}))->toBe({
      "gridTemplateColumns": "repeat(4, minmax(100px,1fr))",
    })
  })
})

describe("backgroundPosition", () => {
  test("test single values", () => {
    expect(backgroundPosition(#left))->toBe({"backgroundPosition": "left"})
    expect(backgroundPosition(#right))->toBe({"backgroundPosition": "right"})
    expect(backgroundPosition(#top))->toBe({"backgroundPosition": "top"})
    expect(backgroundPosition(#bottom))->toBe({"backgroundPosition": "bottom"})
    expect(backgroundPosition(center))->toBe({"backgroundPosition": "center"})
    expect(backgroundPosition(pct(50.)))->toBe({"backgroundPosition": "50%"})
    expect(backgroundPosition(initial))->toBe({"backgroundPosition": "initial"})
    expect(backgroundPosition(inherit_))->toBe({"backgroundPosition": "inherit"})
    expect(backgroundPosition(unset))->toBe({"backgroundPosition": "unset"})
  })

  test("test two values", () => {
    expect(backgroundPosition(#hv((#left, center))))->toBe({"backgroundPosition": "left center"})
    expect(backgroundPosition(#hv((#right, pct(50.)))))->toBe({"backgroundPosition": "right 50%"})
    expect(backgroundPosition(#hv((pct(50.), #top))))->toBe({"backgroundPosition": "50% top"})
    expect(backgroundPosition(#hv((pct(50.), pct(50.)))))->toBe({"backgroundPosition": "50% 50%"})
  })

  test("test multiple positions", () =>
    expect(backgroundPositions(list{#hv((px(0), px(0))), center}))->toBe({
      "backgroundPosition": "0px 0px, center",
    })
  )

  test("test edge offsets values", () =>
    expect(backgroundPosition4(~y=#top, ~offsetY=px(10), ~x=#right, ~offsetX=px(50)))->toBe({
      "backgroundPosition": "right 50px top 10px",
    })
  )
})

describe("backgroundRepeat", () => {
  test("test single values", () => {
    expect(backgroundRepeat(repeatX))->toBe({"backgroundRepeat": "repeat-x"})
    expect(backgroundRepeat(repeatY))->toBe({"backgroundRepeat": "repeat-y"})
    expect(backgroundRepeat(repeat))->toBe({"backgroundRepeat": "repeat"})
    expect(backgroundRepeat(space))->toBe({"backgroundRepeat": "space"})
    expect(backgroundRepeat(round))->toBe({"backgroundRepeat": "round"})
    expect(backgroundRepeat(noRepeat))->toBe({"backgroundRepeat": "no-repeat"})
    expect(backgroundRepeat(inherit_))->toBe({"backgroundRepeat": "inherit"})
  })

  test("test two values", () => {
    expect(backgroundRepeat(#hv((repeat, space))))->toBe({"backgroundRepeat": "repeat space"})
    expect(backgroundRepeat(#hv((repeat, repeat))))->toBe({"backgroundRepeat": "repeat repeat"})
    expect(backgroundRepeat(#hv((round, space))))->toBe({"backgroundRepeat": "round space"})
    expect(backgroundRepeat(#hv((noRepeat, round))))->toBe({"backgroundRepeat": "no-repeat round"})
  })
})

describe("backgroundImage", () =>
  test("test values", () => {
    expect(backgroundImage(none))->toBe({"backgroundImage": "none"})
    expect(backgroundImage(url("x")))->toBe({"backgroundImage": "url(x)"})
    expect(backgroundImage(linearGradient(deg(5.), [(pct(10.), red)])))->toBe({
      "backgroundImage": "linear-gradient(5deg, #FF0000 10%)",
    })
    expect(backgroundImage(repeatingLinearGradient(rad(6.), [(pct(20.), black)])))->toBe({
      "backgroundImage": "repeating-linear-gradient(6rad, #000000 20%)",
    })
    expect(backgroundImage(radialGradient([(pct(30.), yellow)])))->toBe({
      "backgroundImage": "radial-gradient(#FFFF00 30%)",
    })
    expect(backgroundImage(repeatingRadialGradient([(pct(30.), yellow)])))->toBe({
      "backgroundImage": "repeating-radial-gradient(#FFFF00 30%)",
    })
  })
)

describe("background shorthand", () =>
  test("test values", () => {
    expect(background(rgb(1, 2, 3)))->toBe({"background": "rgb(1, 2, 3)"})
    expect(background(url("x")))->toBe({"background": "url(x)"})
    expect(background(linearGradient(deg(5.), [(pct(10.), red)])))->toBe({
      "background": "linear-gradient(5deg, #FF0000 10%)",
    })
    expect(background(none))->toBe({"background": "none"})
  })
)

describe("clipPath", () =>
  test("test values", () => {
    expect(clipPath(none))->toBe({"clipPath": "none"})
    expect(clipPath(url("x")))->toBe({"clipPath": "url(x)"})
    expect(clipPath(marginBox))->toBe({"clipPath": "margin-box"})
    expect(clipPath(borderBox))->toBe({"clipPath": "border-box"})
    expect(clipPath(paddingBox))->toBe({"clipPath": "padding-box"})
    expect(clipPath(contentBox))->toBe({"clipPath": "content-box"})
    expect(clipPath(fillBox))->toBe({"clipPath": "fill-box"})
    expect(clipPath(strokeBox))->toBe({"clipPath": "stroke-box"})
    expect(clipPath(viewBox))->toBe({"clipPath": "view-box"})
    expect(clipPath(inherit_))->toBe({"clipPath": "inherit"})
    expect(clipPath(initial))->toBe({"clipPath": "initial"})
    expect(clipPath(unset))->toBe({"clipPath": "unset"})
  })
)

describe("columnGap", () =>
  test("test values", () => {
    expect(columnGap(normal))->toBe({"columnGap": "normal"})
    expect(columnGap(px(3)))->toBe({"columnGap": "3px"})
    expect(columnGap(em(2.5)))->toBe({"columnGap": "2.5em"})
    expect(columnGap(pct(3.)))->toBe({"columnGap": "3%"})
    expect(columnGap(inherit_))->toBe({"columnGap": "inherit"})
    expect(columnGap(initial))->toBe({"columnGap": "initial"})
    expect(columnGap(unset))->toBe({"columnGap": "unset"})
  })
)

describe("columnWidth", () =>
  test("test values", () => {
    expect(columnWidth(auto))->toBe({"columnWidth": "auto"})
    expect(columnWidth(px(120)))->toBe({"columnWidth": "120px"})
    expect(columnWidth(rem(6.)))->toBe({"columnWidth": "6rem"})
    expect(columnWidth(ch(18.)))->toBe({"columnWidth": "18ch"})
    expect(columnWidth(inherit_))->toBe({"columnWidth": "inherit"})
    expect(columnWidth(initial))->toBe({"columnWidth": "initial"})
    expect(columnWidth(unset))->toBe({"columnWidth": "unset"})
  })
)

describe("rowGap", () =>
  test("test values", () => {
    expect(rowGap(normal))->toBe({"rowGap": "normal"})
    expect(rowGap(px(3)))->toBe({"rowGap": "3px"})
    expect(rowGap(em(2.5)))->toBe({"rowGap": "2.5em"})
    expect(rowGap(pct(3.)))->toBe({"rowGap": "3%"})
    expect(rowGap(inherit_))->toBe({"rowGap": "inherit"})
    expect(rowGap(initial))->toBe({"rowGap": "initial"})
    expect(rowGap(unset))->toBe({"rowGap": "unset"})
  })
)

describe("gap", () => {
  test("test values single prop", () => {
    expect(gap(normal))->toBe({"gap": "normal"})
    expect(gap(px(3)))->toBe({"gap": "3px"})
    expect(gap(em(2.5)))->toBe({"gap": "2.5em"})
    expect(gap(pct(3.)))->toBe({"gap": "3%"})
    expect(gap(inherit_))->toBe({"gap": "inherit"})
    expect(gap(initial))->toBe({"gap": "initial"})
    expect(gap(unset))->toBe({"gap": "unset"})
  })

  test("test values two props", () => {
    expect(gap2(~rowGap=normal, ~columnGap=normal))->toBe({"gap": "normal normal"})
    expect(gap2(~rowGap=px(3), ~columnGap=px(3)))->toBe({"gap": "3px 3px"})
    expect(gap2(~rowGap=em(2.5), ~columnGap=em(2.5)))->toBe({"gap": "2.5em 2.5em"})
    expect(gap2(~rowGap=pct(3.), ~columnGap=pct(3.)))->toBe({"gap": "3% 3%"})
    expect(gap2(~rowGap=inherit_, ~columnGap=inherit_))->toBe({"gap": "inherit inherit"})
    expect(gap2(~rowGap=initial, ~columnGap=initial))->toBe({"gap": "initial initial"})
    expect(gap2(~rowGap=unset, ~columnGap=unset))->toBe({"gap": "unset unset"})
  })
})

describe("cursor", () =>
  test("test values", () => {
    //let auto: [> Types.Cursor.t];
    //let default: [> Types.Cursor.t];
    //let none: [> Types.Cursor.t];
    expect(cursor(contextMenu))->toBe({"cursor": "context-menu"})
    expect(cursor(help))->toBe({"cursor": "help"})
    expect(cursor(pointer))->toBe({"cursor": "pointer"})
    expect(cursor(progress))->toBe({"cursor": "progress"})
    expect(cursor(wait))->toBe({"cursor": "wait"})
    expect(cursor(cell))->toBe({"cursor": "cell"})
    expect(cursor(crosshair))->toBe({"cursor": "crosshair"})
    expect(cursor(text))->toBe({"cursor": "text"})
    expect(cursor(verticalText))->toBe({"cursor": "vertical-text"})
    expect(cursor(alias))->toBe({"cursor": "alias"})
    expect(cursor(copy))->toBe({"cursor": "copy"})
    expect(cursor(move))->toBe({"cursor": "move"})
    expect(cursor(noDrop))->toBe({"cursor": "no-drop"})
    expect(cursor(notAllowed))->toBe({"cursor": "not-allowed"})
    expect(cursor(grab))->toBe({"cursor": "grab"})
    expect(cursor(grabbing))->toBe({"cursor": "grabbing"})
    expect(cursor(allScroll))->toBe({"cursor": "all-scroll"})
    expect(cursor(colResize))->toBe({"cursor": "col-resize"})
    expect(cursor(rowResize))->toBe({"cursor": "row-resize"})
    expect(cursor(nResize))->toBe({"cursor": "n-resize"})
    expect(cursor(eResize))->toBe({"cursor": "e-resize"})
    expect(cursor(sResize))->toBe({"cursor": "s-resize"})
    expect(cursor(wResize))->toBe({"cursor": "w-resize"})
    expect(cursor(neResize))->toBe({"cursor": "ne-resize"})
    expect(cursor(nwResize))->toBe({"cursor": "nw-resize"})
    expect(cursor(seResize))->toBe({"cursor": "se-resize"})
    expect(cursor(swResize))->toBe({"cursor": "sw-resize"})
    expect(cursor(ewResize))->toBe({"cursor": "ew-resize"})
    expect(cursor(nsResize))->toBe({"cursor": "ns-resize"})
    expect(cursor(neswResize))->toBe({"cursor": "nesw-resize"})
    expect(cursor(nwseResize))->toBe({"cursor": "nwse-resize"})
    expect(cursor(zoomIn))->toBe({"cursor": "zoom-in"})
    expect(cursor(zoomOut))->toBe({"cursor": "zoom-out"})
  })
)

describe("counter", () => {
  test("test reset", () => {
    expect(counterReset(none))->toBe({"counterReset": "none"})
    expect(counterReset(#reset(("foo", 2))))->toBe({"counterReset": "foo 2"})
    expect(counterReset(var("bar")))->toBe({"counterReset": "var(--bar)"})
  })

  test("test set", () => {
    expect(counterSet(none))->toBe({"counterSet": "none"})
    expect(counterSet(#set(("foo", 2))))->toBe({"counterSet": "foo 2"})
    expect(counterSet(var("bar")))->toBe({"counterSet": "var(--bar)"})
  })

  test("test increment", () => {
    expect(counterIncrement(none))->toBe({"counterIncrement": "none"})
    expect(counterIncrement(#increment(("foo", 2))))->toBe({"counterIncrement": "foo 2"})
    expect(counterIncrement(var("bar")))->toBe({"counterIncrement": "var(--bar)"})
  })
})
