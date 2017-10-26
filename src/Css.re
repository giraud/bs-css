type css = string;

type rule =
  | Property string string
  | Selector string (list rule);

type color = string;

type cssunit = string;

type angle = string;

type animation = string;

type transform = string;

module Glamor = {
  external make : Js.Json.t => css = "css" [@@bs.module "glamor"];
  external makeGlobal : string => Js.Json.t => unit =
    "global" [@@bs.scope "css"] [@@bs.module "glamor"];
  external makeKeyFrames : Js.Dict.t Js.Json.t => string =
    "keyframes" [@@bs.scope "css"] [@@bs.module "glamor"];
  let merge: list string => string = [%bs.raw
    {|
      function (styles) {
          const glamor = require('glamor');
          return glamor.css.apply(glamor, styles)
      }
  |}
  ];
};

let rec makeDict ruleset => {
  let toJs rule =>
    switch rule {
    | Property name value => (name, Js.Json.string value)
    | Selector name ruleset => (name, makeDict ruleset)
    };
  ruleset |> List.map toJs |> Js.Dict.fromList |> Js.Json.object_
};

let join sep strings => {
  let rec j acc =>
    fun
    | [] => acc
    | [x] => acc ^ x
    | [x, y, ...strings] => j (acc ^ x ^ sep) [y, ...strings];
  j "" strings
};

let unitToString v u => string_of_float v ^ "0" ^ u;

let unitProp name v u => Property name (unitToString v u);

let intProp name v => Property name (string_of_int v);

let floatProp name v => Property name {j|$v|j};

let stringProp name v => Property name v;

let style rules => makeDict rules |> Glamor.make;

let global selector rules => makeDict rules |> Glamor.makeGlobal selector;

let keyframes keyframes =>
  keyframes
  |> List.map (fun (k, ruleset) => (k, makeDict ruleset))
  |> Js.Dict.fromList
  |> Glamor.makeKeyFrames;

let merge = Glamor.merge;

let empty = style [];

/* colors */
let rgb r g b => {j|rgb($r, $g, $b)|j};

let rgba r g b a => {j|rgba($r, $g, $b, $a)|j};

let white = "white";

let black = "black";

let hex v => "#" ^ v;

/* Css units */
let px = "px";

let pct = "%";

let rem = "rem";

let vh = "vh";

let vw = "vw";

/* ANGLE */
let rad = "rad";

let deg = "deg";

let turn = "turn";

/* RULES */
let unsafe name value => Property name value;

/* BACKGROUND */
let backgroundImage url => Property "backgroundImage" ("url(" ^ url ^ ")");

type backgroundAttachment =
  | Scroll
  | Fixed
  | Local
  | Initial;

let backgroundAttachment v =>
  Property
    "backgroundAttachment"
    (
      switch v {
      | Scroll => "scroll"
      | Fixed => "fixed"
      | Local => "local"
      | Initial => "initial"
      }
    );

let backgroundColor = stringProp "backgroundColor";

type backgroundPosition =
  | Top
  | Bottom
  | Left
  | Right
  | Center;

let backgroundPosition v =>
  Property
    "backgroundPosition"
    (
      switch v {
      | Top => "top"
      | Bottom => "bottom"
      | Left => "left"
      | Right => "right"
      | Center => "center"
      }
    );

type backgroundRepeat =
  | RepeatX
  | RepeatY
  | Repeat
  | Space
  | Round
  | NoRepeat;

let backgroundRepeat v =>
  Property
    "backgroundRepeat"
    (
      switch v {
      | RepeatX => "repeat-x"
      | RepeatY => "repeat-y"
      | Repeat => "repeat"
      | Space => "space"
      | Round => "round"
      | NoRepeat => "no-repeat"
      }
    );

/* TEXT */
let color = stringProp "color";

let fontFamily = stringProp "fontFamily";

let fontSize = unitProp "fontSize";

type fontStyle =
  | Normal
  | Italic
  | Oblique;

let fontStyle v =>
  Property
    "fontStyle"
    (
      switch v {
      | Normal => "normal"
      | Italic => "italic"
      | Oblique => "oblique"
      }
    );

type fontWeight =
  | Normal
  | Bold
  | W100
  | W200
  | W300
  | W400
  | W500
  | W600
  | W700
  | W800
  | W900;

let fontWeight v =>
  Property
    "fontWeight"
    (
      switch v {
      | Normal => "normal"
      | Bold => "bold"
      | W100 => "100"
      | W200 => "200"
      | W300 => "300"
      | W400 => "400"
      | W500 => "500"
      | W600 => "600"
      | W700 => "700"
      | W800 => "800"
      | W900 => "900"
      }
    );

let textShadow vx ux vy uy color =>
  Property "textShadow" (unitToString vx ux ^ " " ^ unitToString vy uy ^ " " ^ color);

let textIndent = unitProp "textIndent";

type textAlign =
  | Auto
  | Left
  | Right
  | Center
  | Justify;

let textAlign v =>
  Property
    "textAlign"
    (
      switch v {
      | Auto => "auto"
      | Left => "left"
      | Right => "right"
      | Center => "center"
      | Justify => "justify"
      }
    );

type textDecoration =
  | None
  | Underline color
  | UnderlineWavy color;

let textDecoration v =>
  Property
    "textDecoration"
    (
      switch v {
      | None => "none"
      | Underline color => "underline " ^ color
      | UnderlineWavy color => "underline wavy " ^ color
      }
    );

type textTransform =
  | None
  | Uppercase
  | Lowercase
  | Capitalize
  | FullWidth;

let textTransform v =>
  Property
    "textTransform"
    (
      switch v {
      | None => "none"
      | Uppercase => "uppercase"
      | Lowercase => "lowercase"
      | Capitalize => "capitalize"
      | FullWidth => "full-width"
      }
    );

let lineHeight = unitProp "lineHeight";

let letterSpacing = unitProp "letterSpacing";

/* BORDER */
type borderStyle =
  | None
  | Hidden
  | Solid
  | Dotted
  | Dashed
  | Double;

let borderStyleToString s =>
  switch s {
  | None => "none"
  | Hidden => "hidden"
  | Solid => "solid"
  | Dotted => "dotted"
  | Dashed => "dashed"
  | Double => "double"
  };

let borderProp name width unit style color =>
  Property name (unitToString width unit ^ " " ^ borderStyleToString style ^ " " ^ color);

let border = borderProp "border";

let borderTop = borderProp "borderTop";

let borderBottom = borderProp "borderBottom";

let borderLeft = borderProp "borderLeft";

let borderRight = borderProp "borderRight";

let borderWidth = unitProp "borderWidth";

let borderTopWidth = unitProp "borderTopWidth";

let borderBottomWidth = unitProp "borderBottomWidth";

let borderLeftWidth = unitProp "borderLeftWidth";

let borderRightWidth = unitProp "borderRightWidth";

let borderStyle style => Property "borderStyle" (borderStyleToString style);

let borderTopStyle style => Property "borderTopStyle" (borderStyleToString style);

let borderBottomStyle style => Property "borderBottomStyle" (borderStyleToString style);

let borderLeftStyle style => Property "borderLeftStyle" (borderStyleToString style);

let borderRightStyle style => Property "borderRightStyle" (borderStyleToString style);

let borderColor color => Property "borderColor" color;

let borderTopColor color => Property "borderTopColor" color;

let borderBottomColor color => Property "borderBottomColor" color;

let borderLeftColor color => Property "borderLeftColor" color;

let borderRightColor color => Property "borderRightColor" color;

let borderRadius = unitProp "borderRadius";

let borderTopRightRadius = unitProp "borderTopRightRadius";

let borderTopLeftRadius = unitProp "borderTopLeftRadius";

let borderBottomRightRadius = unitProp "borderBottomRightRadius";

let borderBottomLeftRadius = unitProp "borderBottomLeftRadius";

/* LAYOUT */
let width = unitProp "width";

let minWidth = unitProp "minWidth";

let maxWidth = unitProp "maxWidth";

let height = unitProp "height";

let minHeight = unitProp "minHeight";

let maxHeight = unitProp "maxHeight";

let left = unitProp "left";

let right = unitProp "right";

let top = unitProp "top";

let bottom = unitProp "bottom";

let margin = unitProp "margin";

let marginLeft = unitProp "marginLeft";

let marginRight = unitProp "marginRight";

let marginTop = unitProp "marginTop";

let marginBottom = unitProp "marginBottom";

let padding = unitProp "padding";

let paddingLeft = unitProp "paddingLeft";

let paddingRight = unitProp "paddingRight";

let paddingTop = unitProp "paddingTop";

let paddingBottom = unitProp "paddingBottom";

type display =
  | Block
  | None
  | Inline
  | Flex
  | Grid
  | Subgrid
  | Contents
  | Table
  | TableRow
  | TableCell
  | TableColumn
  | InlineBlock
  | InlineTable
  | InlineFlex
  | InlineGrid;

let display v =>
  Property
    "display"
    (
      switch v {
      | Block => "block"
      | None => "none"
      | Inline => "inline"
      | Flex => "flex"
      | Grid => "grid"
      | Subgrid => "subgrid"
      | Contents => "contents"
      | Table => "table"
      | TableRow => "table-row"
      | TableCell => "table-cell"
      | TableColumn => "table-column"
      | InlineBlock => "inline-block"
      | InlineTable => "inline-table"
      | InlineFlex => "inline-flex"
      | InlineGrid => "inline-grid"
      }
    );

type position =
  | Static
  | Relative
  | Absolute
  | Fixed
  | Sticky;

let position v =>
  Property
    "position"
    (
      switch v {
      | Static => "static"
      | Relative => "relative"
      | Absolute => "absolute"
      | Fixed => "fixed"
      | Sticky => "sticky"
      }
    );

/* FLEXBOX */
let flex = intProp "flex";

let flexBasis = intProp "flexBasis";

let flexGrow = intProp "flexGrow";

let flexShrink = intProp "flexShrink";

let flexFlow = intProp "flexFlow";

let order = intProp "order";

type flexDirection =
  | Row
  | RowReverse
  | Column
  | ColumnReverse;

let flexDirection v =>
  Property
    "flexDirection"
    (
      switch v {
      | Row => "row"
      | RowReverse => "row-reverse"
      | Column => "column"
      | ColumnReverse => "column-reverse"
      }
    );

type flexWrap =
  | Wrap
  | NoWrap;

let flexWrap v =>
  Property
    "flexWrap"
    (
      switch v {
      | Wrap => "wrap"
      | NoWrap => "no-wrap"
      }
    );

type justify =
  | FlexStart
  | FlexEnd
  | Center
  | Stretch
  | SpaceAround
  | SpaceBetween;

let justifyToString v =>
  switch v {
  | FlexStart => "flex-start"
  | FlexEnd => "flex-end"
  | Center => "center"
  | Stretch => "stretch"
  | SpaceAround => "space-around"
  | SpaceBetween => "space-between"
  };

let alignContent v => Property "alignContent" (justifyToString v);

type alignment =
  | FlexStart
  | FlexEnd
  | Center
  | Stretch
  | Baseline;

let alignmentToString v =>
  switch v {
  | FlexStart => "flex-start"
  | FlexEnd => "flex-end"
  | Center => "center"
  | Stretch => "stretch"
  | Baseline => "baseline"
  };

let alignItems v => Property "alignItems" (alignmentToString v);

let alignSelf v => Property "alignSelf" (alignmentToString v);

let justifyContent v => Property "justifyContent" (justifyToString v);

/* SHADOW */
let boxShadow x xunit y yunit blur blurunit spread spreadunit color =>
  Property "boxShadow" {j|$x$xunit $y$yunit $blur$blurunit $spread$spreadunit $color|j};

/* ANIMATION */
let animationName = stringProp "animationName";

let animationDuration ms => Property "animationDuration" (string_of_int ms ^ "ms");

let animationDelay ms => Property "animationDelay" (string_of_int ms ^ "ms");

type animationDirection =
  | Normal
  | Reverse
  | Alternate
  | AlternateReverse;

let animationDirection v =>
  Property
    "animationDirection"
    (
      switch v {
      | Normal => "normal"
      | Reverse => "reverse"
      | Alternate => "alternate"
      | AlternateReverse => "alternate-reverse"
      }
    );

type animationFillMode =
  | None
  | Forwards
  | Backwards
  | Both;

let animationFillMode v =>
  Property
    "animationFillMode"
    (
      switch v {
      | None => "none"
      | Forwards => "backwards"
      | Backwards => "forwards"
      | Both => "both"
      }
    );

let animationIterationCount = intProp "animationIterationCount";

type animationPlayState =
  | Paused
  | Running;

let animationPlayState v =>
  Property
    "animationPlayState"
    (
      switch v {
      | Paused => "paused"
      | Running => "running"
      }
    );

type animationSteps =
  | Start
  | End;

let animationStepsToString s =>
  switch s {
  | Start => "start"
  | End => "end"
  };

type timingFunction =
  | Ease
  | EaseIn
  | EaseOut
  | EaseInOut
  | Linear
  | StepStart
  | StepEnd
  | CubicBezier float float float float
  | Steps int animationSteps
  | Frames int;

let animationTimingFunction v =>
  Property
    "animationTimingFunction"
    (
      switch v {
      | Ease => "ease"
      | EaseIn => "ease-in"
      | EaseOut => "ease-out"
      | EaseInOut => "ease-in-out"
      | Linear => "linear"
      | StepStart => "step-start"
      | StepEnd => "step-end"
      | CubicBezier x1 y1 x2 y2 => {j|cubic-bezier($x1, $y1, $x2, $y2)|j}
      | Steps i s => "steps(" ^ string_of_int i ^ ", " ^ animationStepsToString s ^ ")"
      | Frames i => {j|frames($i)|j}
      }
    );

/* TRANSITION */
let transitionDelay = intProp "transitionDelay";

let transitionDuration = intProp "transitionDuration";

let transitionProperty = stringProp "transitionProperty";

let transitionTimingFunction v =>
  Property
    "transitionTimingFunction"
    (
      switch v {
      | Ease => "ease"
      | EaseIn => "ease-in"
      | EaseOut => "ease-out"
      | EaseInOut => "ease-in-out"
      | Linear => "linear"
      | StepStart => "step-start"
      | StepEnd => "step-end"
      | CubicBezier x1 y1 x2 y2 => {j|cubic-bezier($x1, $y1, $x2, $y2)|j}
      | Steps i s => "steps(" ^ string_of_int i ^ ", " ^ animationStepsToString s ^ ")"
      | Frames i => {j|frames($i)|j}
      }
    );

/* TRANSFORM */
let transform = stringProp "transform";

let transforms transforms => Property "transform" (join " " transforms);

let translate vx ux vy uy => {j|translate($vx$ux, $vy$uy)|j};

let translateX v u => {j|translateX($v$u)|j};

let translateY v u => {j|translateY($v$u)|j};

let translateZ v u => {j|translateZ($v$u)|j};

let translate3d vx ux vy uy vz uz => {j|translate($vx$ux, $vy$uy, $vz$uz)|j};

let scale x y => {j|scale($x, $y)|j};

let scale3d x y z => {j|scale3d($x, $y, $z)|j};

let scaleX x => {j|scaleX($x)|j};

let scaleY y => {j|scaleY($y)|j};

let scaleZ y => {j|scaleZ($y)|j};

let rotate v a => {j|rotate($v$a)|j};

let rotateX v a => {j|rotateX($v$a)|j};

let rotateY v a => {j|rotateY($v$a)|j};

let rotateZ v a => {j|rotateZ($v$a)|j};

let skew vx ax vy ay => {j|skew($vx$ax, $vy$ay|j};

let skewX v a => {j|skewX($v$a|j};

let skewY v a => {j|skewY($v$a|j};

let perspective = unitProp "perspective";