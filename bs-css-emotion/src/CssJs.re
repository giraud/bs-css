include Css_Js_Core;
include Css_Colors;

include Css_Js_Core.Make({
  type styleEncoding = string;
  type renderer = Js.Json.t; // not relevant

  [@bs.module "emotion"]
  external injectRaw: (. string) => unit = "injectGlobal";
  let renderRaw = (. _, css) => injectRaw(. css);

  [@bs.module "emotion"]
  external injectRawRules: (. Js.Json.t) => unit = "injectGlobal";

  let injectRules =
    (. selector, rules) =>
      injectRawRules(.
        Js.Dict.fromArray([|(selector, rules)|])->Js.Json.object_,
      );
  let renderRules =
    (. _, selector, rules) =>
      injectRawRules(.
        Js.Dict.fromArray([|(selector, rules)|])->Js.Json.object_,
      );

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
  insertRule(.
    Css_Js_Core.fontFace(
      ~fontFamily,
      ~src,
      ~fontStyle?,
      ~fontWeight?,
      ~fontDisplay?,
      (),
    ),
  );
  fontFamily;
};
