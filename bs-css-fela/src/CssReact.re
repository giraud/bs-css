module RendererProvider = {
  [@bs.module "react-fela"] [@react.component]
  external make:
    (~renderer: Css.renderer, ~children: React.element) => React.element =
    "RendererProvider";
};

type css = (. Js.Json.t) => string;
type theme;

type felaHook = {
  renderer: Css.renderer,
  css,
  theme,
};

[@bs.module "react-fela"] external useFela: unit => felaHook = "useFela";
