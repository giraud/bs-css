// Docs copied from MDN

module Cascading: {
  type t = [ | `initial | `inherit_ | `unset];

  let initial: t;
  let inherit_: t;
  let unset: t;

  let toString: t => string;
};

module Angle: {
  /**
   The angle CSS data type represents an angle value expressed in degrees, gradians, radians, or turns.
   It is used, for example, in <gradient>s and in some transform functions.
   */
  type t = [ | `deg(float) | `rad(float) | `grad(float) | `turn(float)];

  let deg: float => t;
  let rad: float => t;
  let grad: float => t;
  let turn: float => t;

  let toString: t => string;
};

module Direction: {
  /**
   The direction CSS property sets the direction of text, table columns, and horizontal overflow.
   Use rtl for languages written from right to left (like Hebrew or Arabic),
   and ltr for those written from left to right (like English and most other languages).
   */
  type t = [ | `ltr | `rtl];

  /** Text and other elements go from left to right. This is the default value. */
  let ltr: t;
  /** Text and other elements go from right to left. */
  let rtl: t;

  let toString: t => string;
};
