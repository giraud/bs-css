module Cascading = {
  type t = [ | `initial | `inherit_ | `unset];

  let initial = `initial;
  let inherit_ = `inherit_;
  let unset = `unset;

  let toString =
    fun
    | `initial => "initial"
    | `inherit_ => "inherit"
    | `unset => "unset"
    | _ => "";
  let toString2 =
    fun
    | `initial => "initial"
    | `inherit_ => "inherit"
    | `unset => "unset";
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
