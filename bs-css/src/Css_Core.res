module type CssImplementationIntf = {
  type styleEncoding
  type renderer // some implementations might need a renderer

  let injectRaw: (. string /* css */) => unit
  let renderRaw: (. renderer, string /* css */) => unit

  let injectRules: (. string /* selector */, Js.Json.t) => unit
  let renderRules: (. renderer, string /* selector */, Js.Json.t) => unit

  let make: (. Js.Json.t) => styleEncoding
  let mergeStyles: (. array<styleEncoding>) => styleEncoding

  let makeKeyframes: (. Js.Dict.t<Js.Json.t>) => string /* animationName */
  let renderKeyframes: (. renderer, Js.Dict.t<Js.Json.t>) => string /* animationName */
}
