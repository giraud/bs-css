include Css_Js_Core
include Css_Colors

include Css_Js_Core.Make({
  type styleEncoding = string
  type renderer = Js.Json.t // not relevant

  @module("@emotion/css")
  external injectRaw: (. string) => unit = "injectGlobal"
  let renderRaw = (. _, css) => injectRaw(. css)

  @module("@emotion/css")
  external injectRawRules: (. Js.Json.t) => unit = "injectGlobal"

  let injectRules = (. selector, rules) =>
    injectRawRules(. Js.Dict.fromArray([(selector, rules)])->Js.Json.object_)
  let renderRules = (. _, selector, rules) =>
    injectRawRules(. Js.Dict.fromArray([(selector, rules)])->Js.Json.object_)

  @module("@emotion/css")
  external mergeStyles: (. array<styleEncoding>) => styleEncoding = "cx"

  @module("@emotion/css") external make: (. Js.Json.t) => styleEncoding = "css"

  @module("@emotion/css")
  external makeAnimation: (. Js.Dict.t<Js.Json.t>) => string = "keyframes"

  let makeKeyframes = (. frames) => makeAnimation(. frames)
  let renderKeyframes = (. _, frames) => makeAnimation(. frames)
})

type cache

@module("@emotion/cache") external cache: cache = "cache"

let fontFace = (~fontFamily, ~src, ~fontStyle=?, ~fontWeight=?, ~fontDisplay=?, ()) => {
  insertRule(.
    Css_Js_Core.fontFace(~fontFamily, ~src, ~fontStyle?, ~fontWeight?, ~fontDisplay?, ()),
  )
  fontFamily
}
