include Css_Js_Core
include Css_Colors

type renderer

include Css_Js_Core.Make({
  type styleEncoding = Js.Json.t
  type renderer = renderer
  exception NotImplemented

  @send
  external renderStaticString: (renderer, string) => unit = "renderStatic"

  let injectRaw = (. _css) => raise(NotImplemented)
  let renderRaw = (. renderer, css) => renderStaticString(renderer, css)

  @send
  external renderStatic: (renderer, Js.Json.t, string) => unit = "renderStatic"

  let injectRules = (. _selector, _rules) => raise(NotImplemented)
  let renderRules = (. renderer, selector, rules: Js.Json.t) =>
    renderStatic(renderer, rules, selector)
  let make = (. rules) => rules

  @module("fela")
  external // no transformation

  mergeStyles: (. array<styleEncoding>) => styleEncoding = "combineRules"

  @send
  external felaRenderKeyframes: (renderer, (. 'a) => Js.Dict.t<Js.Json.t>, Js.Json.t) => string =
    "renderKeyframe"

  let makeKeyframes = (. _) => raise(NotImplemented)

  let renderKeyframes = (. renderer, frames) =>
    renderer->felaRenderKeyframes((. _props) => frames, Js.Json.object_(Js.Dict.empty()))
})

@module("fela")
external createRenderer: unit => renderer = "createRenderer"