module Cascading = {
  type t = [ | `initial | `inherit_ | `unset];

  let initial = `initial;
  let inherit_ = `inherit_;
  let unset = `unset;

  let toString =
    fun
    | `initial => "initial"
    | `inherit_ => "inherit"
    | `unset => "unset";
};

module Length = {
  type t = [
    | `calc([ | `add | `sub], t, t)
    | `ch(float)
    | `cm(float)
    | `em(float)
    | `ex(float)
    | `mm(float)
    | `percent(float)
    | `pt(int)
    | `px(int)
    | `pxFloat(float)
    | `rem(float)
    | `vh(float)
    | `vmin(float)
    | `vmax(float)
    | `vw(float)
    | `zero
  ];

  let ch = x => `ch(x);
  let cm = x => `cm(x);
  let em = x => `em(x);
  let ex = x => `ex(x);
  let mm = x => `mm(x);
  let pt = x => `pt(x);
  let px = x => `px(x);
  let pxFloat = x => `pxFloat(x);
  let rem = x => `rem(x);
  let vh = x => `vh(x);
  let vmin = x => `vmin(x);
  let vmax = x => `vmax(x);
  let zero = `zero;

  let rec toString =
    fun
    | `calc(`add, a, b) =>
      "calc(" ++ toString(a) ++ " + " ++ toString(b) ++ ")"
    | `calc(`sub, a, b) =>
      "calc(" ++ toString(a) ++ " - " ++ toString(b) ++ ")"
    | `ch(x) => Js.Float.toString(x) ++ "ch"
    | `cm(x) => Js.Float.toString(x) ++ "cm"
    | `em(x) => Js.Float.toString(x) ++ "em"
    | `ex(x) => Js.Float.toString(x) ++ "ex"
    | `mm(x) => Js.Float.toString(x) ++ "mm"
    | `percent(x) => Js.Float.toString(x) ++ "%"
    | `pt(x) => Js.Int.toString(x) ++ "pt"
    | `px(x) => Js.Int.toString(x) ++ "px"
    | `pxFloat(x) => Js.Float.toString(x) ++ "px"
    | `rem(x) => Js.Float.toString(x) ++ "rem"
    | `vh(x) => Js.Float.toString(x) ++ "vh"
    | `vmax(x) => Js.Float.toString(x) ++ "vmax"
    | `vmin(x) => Js.Float.toString(x) ++ "vmin"
    | `vw(x) => Js.Float.toString(x) ++ "vw"
    | `zero => "0";
};

module Angle = {
  type t = [ | `deg(float) | `rad(float) | `grad(float) | `turn(float)];

  let deg = (x: float) => `deg(x);
  let rad = (x: float) => `rad(x);
  let grad = (x: float) => `grad(x);
  let turn = (x: float) => `turn(x);

  let toString =
    fun
    | `deg(x) => Js.Float.toString(x) ++ "deg"
    | `rad(x) => Js.Float.toString(x) ++ "rad"
    | `grad(x) => Js.Float.toString(x) ++ "grad"
    | `turn(x) => Js.Float.toString(x) ++ "turn";
};

module Direction = {
  type t = [ | `ltr | `rtl];

  let ltr = `ltr;
  let rtl = `rtl;

  let toString =
    fun
    | `ltr => "ltr"
    | `rtl => "rtl";
};

module Position = {
  type t = [ | `absolute | `relative | `static | `fixed | `sticky];

  let absolute = `absolute;
  let relative = `relative;
  let static = `static;
  let fixed = `fixed;
  let sticky = `sticky;

  let toString =
    fun
    | `absolute => "absolute"
    | `relative => "relative"
    | `static => "static"
    | `fixed => "fixed"
    | `sticky => "sticky";
};

module Resize = {
  type t = [ | `none | `both | `horizontal | `vertical | `block | `inline];

  let none = `none;
  let both = `both;
  let horizontal = `horizontal;
  let vertical = `vertical;
  let block = `block;
  let inline = `inline;

  let toString =
    fun
    | `none => "none"
    | `both => "both"
    | `horizontal => "horizontal"
    | `vertical => "vertical"
    | `block => "block"
    | `inline => "inline";
};

module FontVariant = {
  type t = [ | `normal | `smallCaps];

  let normal = `normal;
  let smallCaps = `smallCaps;

  let toString =
    fun
    | `normal => "normal"
    | `smallCaps => "smallCaps";
};

module FontStyle = {
  type t = [ | `normal | `italic | `oblique];

  let normal = `normal;
  let italic = `italic;
  let oblique = `oblique;

  let toString =
    fun
    | `normal => "normal"
    | `italic => "italic"
    | `oblique => "oblique";
};

module FlexBasis = {
  type t = [
    | `auto
    | `fill
    | `content
    | `maxContent
    | `minContent
    | `fitContent
  ];

  let fill = `fill;
  let content = `content;
  let maxContent = `maxContent;
  let minContent = `minContent;
  let fitContent = `fitContent;

  let toString =
    fun
    | `auto => "auto"
    | `fill => "fill"
    | `content => "content"
    | `maxContent => "max-content"
    | `minContent => "min-content"
    | `fitContent => "fit-content";
};

module Overflow = {
  type t = [ | `hidden | `visible | `scroll | `auto];

  let hidden = `hidden;
  let visible = `visible;
  let scroll = `scroll;
  let auto = `auto;

  let toString =
    fun
    | `hidden => "hidden"
    | `visible => "visible"
    | `scroll => "scroll"
    | `auto => "auto";
};

module Margin = {
  type t = [ | `auto];

  let auto = `auto;

  let toString =
    fun
    | `auto => "auto";
};

module GridAutoFlow = {
  type t = [ | `column | `row | `columnDense | `rowDense];

  let toString =
    fun
    | `column => "column"
    | `row => "row"
    | `columnDense => "column dense"
    | `rowDense => "row dense";
};

module VerticalAlign = {
  type t = [
    | `baseline
    | `sub
    | `super
    | `top
    | `textTop
    | `middle
    | `bottom
    | `textBottom
  ];

  let toString =
    fun
    | `baseline => "baseline"
    | `sub => "sub"
    | `super => "super"
    | `top => "top"
    | `textTop => "text-top"
    | `middle => "middle"
    | `bottom => "bottom"
    | `textBottom => "text-bottom";
};

module TimingFunction = {
  type t = [
    | `linear
    | `ease
    | `easeIn
    | `easeOut
    | `easeInOut
    | `stepStart
    | `stepEnd
    | `steps(int, [ | `start | `end_])
    | `cubicBezier(float, float, float, float)
  ];

  let toString =
    fun
    | `linear => "linear"
    | `ease => "ease"
    | `easeIn => "ease-out"
    | `easeOut => "ease-out"
    | `easeInOut => "ease-in-out"
    | `stepStart => "step-start"
    | `stepEnd => "step-end"
    | `steps(i, `start) => "steps(" ++ Js.Int.toString(i) ++ ", start)"
    | `steps(i, `end_) => "steps(" ++ Js.Int.toString(i) ++ ", end)"
    | `cubicBezier(a, b, c, d) =>
      "cubic-bezier("
      ++ Js.Float.toString(a)
      ++ ", "
      ++ Js.Float.toString(b)
      ++ ", "
      ++ Js.Float.toString(c)
      ++ ", "
      ++ Js.Float.toString(d)
      ++ ")";
};
