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

module RepeatValue = {
  type t = [ | `autoFill | `autoFit | `num(int)];

  let toString =
    fun
    | `autoFill => "auto-fill"
    | `autoFit => "auto-fit"
    | `num(x) => Js.Int.toString(x);
};

module ListStyleType = {
  type t = [
    | `disc
    | `circle
    | `square
    | `decimal
    | `lowerAlpha
    | `upperAlpha
    | `lowerGreek
    | `lowerLatin
    | `upperLatin
    | `lowerRoman
    | `upperRoman
    | `none
  ];

  let toString =
    fun
    | `disc => "disc"
    | `circle => "circle"
    | `square => "square"
    | `decimal => "decimal"
    | `lowerAlpha => "lower-alpha"
    | `upperAlpha => "upper-alpha"
    | `lowerGreek => "lower-greek"
    | `lowerLatin => "lower-latin"
    | `upperLatin => "upper-latin"
    | `lowerRoman => "lower-roman"
    | `upperRoman => "upper-roman"
    | `none => "none";
};

module OutlineStyle = {
  type t = [
    | `none
    | `hidden
    | `dotted
    | `dashed
    | `solid
    | `double
    | `groove
    | `ridge
    | `inset
    | `outset
  ];

  let toString =
    fun
    | `none => "none"
    | `hidden => "hidden"
    | `dotted => "dotted"
    | `dashed => "dashed"
    | `solid => "solid"
    | `double => "double"
    | `groove => "grove"
    | `ridge => "ridge"
    | `inset => "inset"
    | `outset => "outset";
};

module FontWeight = {
  type t = [
    | `num(int)
    | `thin
    | `extraLight
    | `light
    | `normal
    | `medium
    | `semiBold
    | `bold
    | `extraBold
    | `black
    | `lighter
    | `bolder
  ];

  let toString = x =>
    switch (x) {
    | `num(n) => Js.Int.toString(n)
    | `thin => "100"
    | `extraLight => "200"
    | `light => "300"
    | `normal => "400"
    | `medium => "500"
    | `semiBold => "600"
    | `bold => "700"
    | `extraBold => "800"
    | `black => "900"
    | `lighter => "lighter"
    | `bolder => "bolder"
    };
};

module Transform = {
  type t = [
    | `translate(Length.t, Length.t)
    | `translate3d(Length.t, Length.t, Length.t)
    | `translateX(Length.t)
    | `translateY(Length.t)
    | `translateZ(Length.t)
    | `scale(float, float)
    | `scale3d(float, float, float)
    | `scaleX(float)
    | `scaleY(float)
    | `scaleZ(float)
    | `rotate(Angle.t)
    | `rotate3d(float, float, float, Angle.t)
    | `rotateX(Angle.t)
    | `rotateY(Angle.t)
    | `rotateZ(Angle.t)
    | `skew(Angle.t, Angle.t)
    | `skewX(Angle.t)
    | `skewY(Angle.t)
    | `perspective(int)
  ];

  let string_of_scale = (x, y) =>
    "scale(" ++ Js.Float.toString(x) ++ ", " ++ Js.Float.toString(y) ++ ")";

  let string_of_translate3d = (x, y, z) =>
    "translate3d("
    ++ Length.toString(x)
    ++ ", "
    ++ Length.toString(y)
    ++ ", "
    ++ Length.toString(z)
    ++ ")";

  let toString =
    fun
    | `translate(x, y) =>
      "translate(" ++ Length.toString(x) ++ ", " ++ Length.toString(y) ++ ")"
    | `translate3d(x, y, z) => string_of_translate3d(x, y, z)
    | `translateX(x) => "translateX(" ++ Length.toString(x) ++ ")"
    | `translateY(y) => "translateY(" ++ Length.toString(y) ++ ")"
    | `translateZ(z) => "translateZ(" ++ Length.toString(z) ++ ")"
    | `scale(x, y) => string_of_scale(x, y)
    | `scale3d(x, y, z) =>
      "scale3d("
      ++ Js.Float.toString(x)
      ++ ", "
      ++ Js.Float.toString(y)
      ++ ", "
      ++ Js.Float.toString(z)
      ++ ")"
    | `scaleX(x) => "scaleX(" ++ Js.Float.toString(x) ++ ")"
    | `scaleY(y) => "scaleY(" ++ Js.Float.toString(y) ++ ")"
    | `scaleZ(z) => "scaleZ(" ++ Js.Float.toString(z) ++ ")"
    | `rotate(a) => "rotate(" ++ Angle.toString(a) ++ ")"
    | `rotate3d(x, y, z, a) =>
      "rotate3d("
      ++ Js.Float.toString(x)
      ++ ", "
      ++ Js.Float.toString(y)
      ++ ", "
      ++ Js.Float.toString(z)
      ++ ", "
      ++ Angle.toString(a)
      ++ ")"
    | `rotateX(a) => "rotateX(" ++ Angle.toString(a) ++ ")"
    | `rotateY(a) => "rotateY(" ++ Angle.toString(a) ++ ")"
    | `rotateZ(a) => "rotateZ(" ++ Angle.toString(a) ++ ")"
    | `skew(x, y) =>
      "skew(" ++ Angle.toString(x) ++ ", " ++ Angle.toString(y) ++ ")"
    | `skewX(a) => "skewX(" ++ Angle.toString(a) ++ ")"
    | `skewY(a) => "skewY(" ++ Angle.toString(a) ++ ")"
    | `perspective(x) => "perspective(" ++ Js.Int.toString(x) ++ ")";
};

module AnimationDirection = {
  type t = [ | `normal | `reverse | `alternate | `alternateReverse];

  let toString =
    fun
    | `normal => "normal"
    | `reverse => "reverse"
    | `alternate => "alternate"
    | `alternateReverse => "alternate-reverse";
};

module AnimationFillMode = {
  type t = [ | `none | `forwards | `backwards | `both];

  let toString =
    fun
    | `none => "none"
    | `forwards => "forwards"
    | `backwards => "backwards"
    | `both => "both";
};

module AnimationIterationCount = {
  type t = [ | `infinite | `count(int)];

  let toString =
    fun
    | `infinite => "infinite"
    | `count(x) => Js.Int.toString(x);
};

module AnimationPlayState = {
  type t = [ | `paused | `running];

  let toString =
    fun
    | `paused => "paused"
    | `running => "running";
};

module Cursor = {
  type t = [
    | `auto
    | `default
    | `none
    | `contextMenu
    | `help
    | `pointer
    | `progress
    | `wait
    | `cell
    | `crosshair
    | `text
    | `verticalText
    | `alias
    | `copy
    | `move
    | `noDrop
    | `notAllowed
    | `grab
    | `grabbing
    | `allScroll
    | `colResize
    | `rowResize
    | `nResize
    | `eResize
    | `sResize
    | `wResize
    | `neResize
    | `nwResize
    | `seResize
    | `swResize
    | `ewResize
    | `nsResize
    | `neswResize
    | `nwseResize
    | `zoomIn
    | `zoomOut
  ];

  let toString = x =>
    switch (x) {
    | `auto => "auto"
    | `default => "default"
    | `none => "none"
    | `contextMenu => "context-menu"
    | `help => "help"
    | `pointer => "pointer"
    | `progress => "progress"
    | `wait => "wait"
    | `cell => "cell"
    | `crosshair => "crosshair"
    | `text => "text"
    | `verticalText => "vertical-text"
    | `alias => "alias"
    | `copy => "copy"
    | `move => "move"
    | `noDrop => "no-drop"
    | `notAllowed => "not-allowed"
    | `grab => "grab"
    | `grabbing => "grabbing"
    | `allScroll => "all-scroll"
    | `colResize => "col-resize"
    | `rowResize => "row-resize"
    | `nResize => "n-resize"
    | `eResize => "e-resize"
    | `sResize => "s-resize"
    | `wResize => "w-resize"
    | `neResize => "ne-resize"
    | `nwResize => "nw-resize"
    | `seResize => "se-resize"
    | `swResize => "sw-resize"
    | `ewResize => "ew-resize"
    | `nsResize => "ns-resize"
    | `neswResize => "nesw-resize"
    | `nwseResize => "nwse-resize"
    | `zoomIn => "zoom-in"
    | `zoomOut => "zoom-out"
    };
};
