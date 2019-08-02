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
    | `rtl => "rtl"
    | _ => "";
};

module Position = {
  type t = [ | `absolute | `relative | `static | `fixed | `sticky];

  let toString =
    fun
    | `absolute => "absolute"
    | `relative => "relative"
    | `static => "static"
    | `fixed => "fixed"
    | `sticky => "sticky"
    | _ => "";
};
