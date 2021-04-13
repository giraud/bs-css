include Css_Js_Core;
include Css_Colors;

type renderer;

include Css_Js_Core.Make({
  type styleEncoding = Js.Json.t;
  type nonrec renderer = renderer;
  exception NotImplemented;

  [@bs.send]
  external renderStaticString: (renderer, string) => unit = "renderStatic";

  let injectRaw = (. _css) => raise(NotImplemented);
  let renderRaw = (. renderer, css) => renderStaticString(renderer, css);

  [@bs.send]
  external renderStatic: (renderer, Js.Json.t, string) => unit =
    "renderStatic";

  let injectRules = (. _selector, _rules) => raise(NotImplemented);
  let renderRules =
    (. renderer, selector, rules: Js.Json.t) =>
      renderStatic(renderer, rules, selector);
  let make = (. rules) => rules; // no transformation

  [@bs.module "fela"]
  external mergeStyles: (. array(styleEncoding)) => styleEncoding =
    "combineRules";

  [@bs.send]
  external felaRenderKeyframes:
    (renderer, (. 'a) => Js.Dict.t(Js.Json.t), Js.Json.t) => string =
    "renderKeyframe";

  let makeKeyframes = (. _) => raise(NotImplemented);

  let renderKeyframes =
    (. renderer, frames) =>
      renderer->felaRenderKeyframes(
        (. _props) => frames,
        Js.Json.object_(Js.Dict.empty()),
      );
});

[@bs.module "fela"]
external createRenderer: unit => renderer = "createRenderer";
