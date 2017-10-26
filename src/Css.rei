type css = string;

type rule;

type color;

type cssunit;

type animation;

type transform;

type angle;

let rad: angle;

let deg: angle;

let turn: angle;

let style: list rule => css;

let global: string => list rule => unit;

let keyframes: list (string, list rule) => animation;

let merge: list css => css;

let empty: css;

/* units */
let px: cssunit;

let pct: cssunit;

let rem: cssunit;

let vh: cssunit;

let vw: cssunit;

/* color */
let rgb: int => int => int => color;

let rgba: int => int => int => float => color;

let hex: string => color;

let white: color;

let black: color;

/* CSS RULES */
let unsafe: string => string => rule;

/* BACKGROUND */
let backgroundImage: string => rule;

type backgroundAttachment =
  | Scroll
  | Fixed
  | Local
  | Initial;

let backgroundAttachment: backgroundAttachment => rule;

let backgroundColor: color => rule;

type backgroundPosition =
  | Top
  | Bottom
  | Left
  | Right
  | Center;

let backgroundPosition: backgroundPosition => rule;

type backgroundRepeat =
  | RepeatX
  | RepeatY
  | Repeat
  | Space
  | Round
  | NoRepeat;

let backgroundRepeat: backgroundRepeat => rule;

type background =
  | None
  | Color color
  | Image string;

let background: background => rule;

/* TEXT */
let color: color => rule;

let fontFamily: string => rule;

let fontSize: float => cssunit => rule;

type fontStyle =
  | Normal
  | Italic
  | Oblique;

let fontStyle: fontStyle => rule;

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

let fontWeight: fontWeight => rule;

type textDecoration =
  | None
  | Underline color
  | UnderlineWavy color;

let textDecoration: textDecoration => rule;

type textAlign =
  | Auto
  | Left
  | Right
  | Center
  | Justify;

let textAlign: textAlign => rule;

let textIndent: float => cssunit => rule;

let textShadow: float => cssunit => float => cssunit => color => rule;

type textTransform =
  | None
  | Uppercase
  | Lowercase
  | Capitalize
  | FullWidth;

let textTransform: textTransform => rule;

let letterSpacing: float => cssunit => rule;

let lineHeight: float => cssunit => rule;

/* BORDER */
type borderStyle =
  | None
  | Hidden
  | Solid
  | Dotted
  | Dashed
  | Double;

let border: float => cssunit => borderStyle => color => rule;

let borderTop: float => cssunit => borderStyle => color => rule;

let borderBottom: float => cssunit => borderStyle => color => rule;

let borderLeft: float => cssunit => borderStyle => color => rule;

let borderRight: float => cssunit => borderStyle => color => rule;

let borderWidth: float => cssunit => rule;

let borderTopWidth: float => cssunit => rule;

let borderBottomWidth: float => cssunit => rule;

let borderLeftWidth: float => cssunit => rule;

let borderRightWidth: float => cssunit => rule;

let borderStyle: borderStyle => rule;

let borderTopStyle: borderStyle => rule;

let borderBottomStyle: borderStyle => rule;

let borderLeftStyle: borderStyle => rule;

let borderRightStyle: borderStyle => rule;

let borderColor: color => rule;

let borderTopColor: color => rule;

let borderBottomColor: color => rule;

let borderLeftColor: color => rule;

let borderRightColor: color => rule;

let borderRadius: float => cssunit => rule;

let borderTopLeftRadius: float => cssunit => rule;

let borderTopRightRadius: float => cssunit => rule;

let borderBottomLeftRadius: float => cssunit => rule;

let borderBottomRightRadius: float => cssunit => rule;

/* LAYOUT */
let width: float => cssunit => rule;

let minWidth: float => cssunit => rule;

let maxWidth: float => cssunit => rule;

let height: float => cssunit => rule;

let minHeight: float => cssunit => rule;

let maxHeight: float => cssunit => rule;

let left: float => cssunit => rule;

let right: float => cssunit => rule;

let top: float => cssunit => rule;

let bottom: float => cssunit => rule;

let margin: float => cssunit => rule;

let marginLeft: float => cssunit => rule;

let marginRight: float => cssunit => rule;

let marginTop: float => cssunit => rule;

let marginBottom: float => cssunit => rule;

let padding: float => cssunit => rule;

let paddingLeft: float => cssunit => rule;

let paddingRight: float => cssunit => rule;

let paddingTop: float => cssunit => rule;

let paddingBottom: float => cssunit => rule;

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

let display: display => rule;

type position =
  | Static
  | Relative
  | Absolute
  | Fixed
  | Sticky;

let position: position => rule;

/* FLEXBOX */
let flex: int => rule;

type flexDirection =
  | Row
  | RowReverse
  | Column
  | ColumnReverse;

let flexDirection: flexDirection => rule;

let flexBasis: int => rule;

let flexFlow: int => rule;

let flexGrow: int => rule;

let flexShrink: int => rule;

type flexWrap =
  | Wrap
  | NoWrap;

let flexWrap: flexWrap => rule;

type justify =
  | FlexStart
  | FlexEnd
  | Center
  | Stretch
  | SpaceAround
  | SpaceBetween;

let alignContent: justify => rule;

type alignment =
  | FlexStart
  | FlexEnd
  | Center
  | Stretch
  | Baseline;

let alignItems: alignment => rule;

let alignSelf: alignment => rule;

let justifyContent: justify => rule;

let order: int => rule;

/* SHADOW */
type shadow;

let shadow: x::int? => y::int? => blur::int? => spread::int? => color => shadow;

let boxShadow: shadow => rule;

let boxShadows: list shadow => rule;

/* ANIMATION */
let animationDuration: int => rule;

let animationDelay: int => rule;

type animationDirection =
  | Normal
  | Reverse
  | Alternate
  | AlternateReverse;

let animationDirection: animationDirection => rule;

type animationFillMode =
  | None
  | Forwards
  | Backwards
  | Both;

let animationFillMode: animationFillMode => rule;

let animationIterationCount: int => rule;

let animationName: animation => rule;

type animationPlayState =
  | Paused
  | Running;

let animationPlayState: animationPlayState => rule;

type animationSteps =
  | Start
  | End;

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

let animationTimingFunction: timingFunction => rule;

/* TRANSITION */
let transitionDelay: int => rule;

let transitionDuration: int => rule;

let transitionTimingFunction: timingFunction => rule;

let transitionProperty: string => rule;

/* TRANSFORM */
let transform: transform => rule;

let transforms: list transform => rule;

let translate: float => cssunit => float => cssunit => transform;

let translateX: float => cssunit => transform;

let translateY: float => cssunit => transform;

let scale: float => float => transform;

let scaleX: float => transform;

let scaleY: float => transform;

let rotate: float => angle => transform;

let skew: float => angle => float => angle => transform;

let skewX: float => angle => transform;

let skewY: float => angle => transform;

let translate3d: float => cssunit => float => cssunit => float => cssunit => transform;

let translateZ: float => cssunit => transform;

let scale3d: float => float => float => transform;

let scaleZ: float => transform;

let rotateX: float => angle => transform;

let rotateY: float => angle => transform;

let rotateZ: float => angle => transform;

let perspective: float => cssunit => rule;

/* PSEUDO CLASSES */
let link: list rule => rule;

let disabled: list rule => rule;

let required: list rule => rule;

let readOnly: list rule => rule;

let focus: list rule => rule;

let visited: list rule => rule;

let active: list rule => rule;

let hover: list rule => rule;

let firstChild: list rule => rule;

let firstOfType: list rule => rule;

let lastChild: list rule => rule;

let lastOfType: list rule => rule;

let media: string => list rule => rule;