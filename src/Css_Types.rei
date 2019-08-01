// Docs copied from MDN

module Cascading: {
  type t = [ | `initial | `inherit_ | `unset];

  let initial: t;
  let inherit_: t;
  let unset: t;
};

/**
 The angle CSS data type represents an angle value expressed in degrees, gradians, radians, or turns.
 It is used, for example, in <gradient>s and in some transform functions.
 */
module Angle: {
  type t = [ | `deg(float) | `rad(float) | `grad(float) | `turn(float)];

  let deg: float => t;
  let rad: float => t;
  let grad: float => t;
  let turn: float => t;

  let toString: t => string;
};
