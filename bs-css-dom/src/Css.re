include Css_Legacy_Core;
include Css_Colors;

include Css_Legacy_Core.Make({
  type styleEncoding = ReactDOM.Style.t;
  type renderer = Js.Json.t; // not relevant
  exception NotImplemented;

  external unsafeJsonCast: Js.Json.t => styleEncoding = "%identity";
  external unsafeJsCast: Js.t('a) => styleEncoding = "%identity";

  let injectRaw = (. _) => raise(NotImplemented);
  let renderRaw = (. _, _) => raise(NotImplemented);

  let injectRules = (. _, _) => raise(NotImplemented);
  let renderRules = (. _, _, _) => raise(NotImplemented);

  let mergeStyles =
    (. styles) =>
      Belt.Array.reduce(styles, Js.Obj.empty(), (acc, item) =>
        Js.Obj.assign(acc, Obj.magic(item))
      )
      ->unsafeJsCast;

  let make = (. props) => props->unsafeJsonCast;

  let makeKeyframes = (. _) => raise(NotImplemented);
  let renderKeyframes = (. _, _) => raise(NotImplemented);
});
