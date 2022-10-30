exception NotImplemented

module New = {
  include Css_Colors
  include Css_Js_Core
  include Css_Js_Core.Make({
    type styleEncoding = string
    type renderer = Js.Json.t

    let injectRaw = (. _) => raise(NotImplemented)
    let renderRaw = (. _, _) => raise(NotImplemented)
    let injectRules = (. _, _) => raise(NotImplemented)
    let renderRules = (. _, _, _) => raise(NotImplemented)
    let make = (. _) => raise(NotImplemented)
    let mergeStyles = (. _) => raise(NotImplemented)
    let makeKeyframes = (. _) => raise(NotImplemented)
    let renderKeyframes = (. _, _) => raise(NotImplemented)
  })
}

module Legacy = {
  include Css_Colors
  include Css_Legacy_Core
  include Css_Legacy_Core.Make({
    type styleEncoding = string
    type renderer = Js.Json.t

    let injectRaw = (. _) => raise(NotImplemented)
    let renderRaw = (. _, _) => raise(NotImplemented)
    let injectRules = (. _, _) => raise(NotImplemented)
    let renderRules = (. _, _, _) => raise(NotImplemented)
    let make = (. _) => raise(NotImplemented)
    let mergeStyles = (. _) => raise(NotImplemented)
    let makeKeyframes = (. _) => raise(NotImplemented)
    let renderKeyframes = (. _, _) => raise(NotImplemented)
  })
}
