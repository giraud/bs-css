include Css_Legacy_Core
include Css_Colors

include Css_Legacy_Core.Make({
  type styleEncoding = string
  type renderer = Js.Json.t // not relevant

  @module("@emotion/css")
  external injectRaw: (. string) => unit = "injectGlobal"
  let renderRaw = (. _, css) => injectRaw(. css)

  @module("@emotion/css")
  external injectRawRules: (. Js.Json.t) => unit = "injectGlobal"

  let injectRules = (. _: string, rules) => injectRawRules(. rules)
  let renderRules = (. _, _: string, rules) => injectRawRules(. rules)

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
  let asString = Css_Legacy_Core.fontFace(
    ~fontFamily,
    ~src,
    ~fontStyle?,
    ~fontWeight?,
    ~fontDisplay?,
    (),
  )
  insertRule(asString)
  fontFamily
}
