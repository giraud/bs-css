include Css_Legacy_Core;
include Css_Colors;

include Css_Legacy_Core.Make({
  [@bs.module "@emotion/css"]
  external mergeStyles: (. array(string)) => string = "cx";

  [@bs.module "@emotion/css"] external make: (. Js.Json.t) => string = "css";

  [@bs.module "@emotion/css"]
  external injectRule: (. Js.Json.t) => unit = "injectGlobal";

  [@bs.module "@emotion/css"]
  external injectRaw: (. string) => unit = "injectGlobal";

  [@bs.module "@emotion/react"]
  external makeKeyFrames: (. Js.Dict.t(Js.Json.t)) => string = "keyframes";
});

type cache;

[@bs.module "@emotion/cache"] external cache: cache = "cache";

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
