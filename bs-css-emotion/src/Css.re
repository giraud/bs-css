include Css_Legacy_Core;
include Css_Colors;

include Css_Legacy_Core.Make({
  type styleEncoding = string;
  type renderer = Js.Json.t; // not relevant

  [@bs.module "emotion"]
  external injectRaw: (. string) => unit = "injectGlobal";
  let renderRaw = (. _, css) => injectRaw(. css);

  [@bs.module "emotion"]
  external injectRawRules: (. Js.Json.t) => unit = "injectGlobal";

  let injectRules = (. _: string, rules) => injectRawRules(. rules);
  let renderRules = (. _, _: string, rules) => injectRawRules(. rules);

  [@bs.module "emotion"]
  external mergeStyles: (. array(styleEncoding)) => styleEncoding = "cx";

  [@bs.module "emotion"] external make: (. Js.Json.t) => styleEncoding = "css";

  [@bs.module "emotion"]
  external makeAnimation: (. Js.Dict.t(Js.Json.t)) => string = "keyframes";

  let makeKeyframes = (. frames) => makeAnimation(. frames);
  let renderKeyframes = (. _, frames) => makeAnimation(. frames);
});

type cache;

[@bs.module "emotion"] external cache: cache = "cache";

let fontFace =
    (~fontFamily, ~src, ~fontStyle=?, ~fontWeight=?, ~fontDisplay=?, ()) => {
  let asString =
    Css_Legacy_Core.fontFace(
      ~fontFamily,
      ~src,
      ~fontStyle?,
      ~fontWeight?,
      ~fontDisplay?,
      (),
    );
  insertRule(asString);
  fontFamily;
};
