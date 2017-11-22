type css = string;

type rule;

type color;

type cssunit;

type keyframes;

type transform;

type angle;

let rad: float => angle;

let deg: float => angle;

let turn: float => angle;

let style: list(rule) => css;

let global: (string, list(rule)) => unit;

let keyframes: list((string, list(rule))) => keyframes;

let merge: list(css) => css;

let empty: css;

let important: rule => rule;

/* units */
let px: int => cssunit;

let pct: float => cssunit;

let rem: float => cssunit;

let em: float => cssunit;

let vh: float => cssunit;

let vw: float => cssunit;

let cm: float => cssunit;

let mm: float => cssunit;

let zero: cssunit;

/* color */
let rgb: (int, int, int) => color;

let rgba: (int, int, int, float) => color;

let hex: string => color;

let white: color;

let black: color;

/* CSS RULES */
let unsafe: (string, string) => rule;

type visibility =
  | Visible
  | Hidden;

let visibility: visibility => rule;

let opacity: float => rule;

/* BACKGROUND */
let backgroundImage: string => rule;

type backgroundAttachment =
  | Scroll
  | Fixed
  | Local
  | Initial;

let backgroundAttachment: backgroundAttachment => rule;

let backgroundColor: color => rule;

type backgroundSize =
  | Cover
  | Contain
  | Width(cssunit)
  | Height(cssunit)
  | Custom(cssunit, cssunit);

let backgroundSize: backgroundSize => rule;

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
  | Color(color)
  | Image(string);

let background: background => rule;

/* TEXT */
let color: color => rule;

let fontFamily: string => rule;

let fontSize: cssunit => rule;

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
  | Underline(color)
  | UnderlineWavy(color);

let textDecoration: textDecoration => rule;

type textAlign =
  | Auto
  | Left
  | Right
  | Center
  | Justify;

let textAlign: textAlign => rule;

let textIndent: cssunit => rule;

let textShadow: (cssunit, cssunit, color) => rule;

type textTransform =
  | None
  | Uppercase
  | Lowercase
  | Capitalize
  | FullWidth;

let textTransform: textTransform => rule;

let letterSpacing: cssunit => rule;

let lineHeight: cssunit => rule;

/* BORDER */
type borderStyle =
  | None
  | Hidden
  | Solid
  | Dotted
  | Dashed
  | Double;

let border: (cssunit, borderStyle, color) => rule;

let borderTop: (cssunit, borderStyle, color) => rule;

let borderBottom: (cssunit, borderStyle, color) => rule;

let borderLeft: (cssunit, borderStyle, color) => rule;

let borderRight: (cssunit, borderStyle, color) => rule;

let borderWidth: cssunit => rule;

let borderTopWidth: cssunit => rule;

let borderBottomWidth: cssunit => rule;

let borderLeftWidth: cssunit => rule;

let borderRightWidth: cssunit => rule;

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

let borderRadius: cssunit => rule;

let borderTopLeftRadius: cssunit => rule;

let borderTopRightRadius: cssunit => rule;

let borderBottomLeftRadius: cssunit => rule;

let borderBottomRightRadius: cssunit => rule;

/* LAYOUT */
let width: cssunit => rule;

let minWidth: cssunit => rule;

let maxWidth: cssunit => rule;

let height: cssunit => rule;

let minHeight: cssunit => rule;

let maxHeight: cssunit => rule;

let left: cssunit => rule;

let right: cssunit => rule;

let top: cssunit => rule;

let bottom: cssunit => rule;

let margin: cssunit => rule;

let marginLeft: cssunit => rule;

let marginRight: cssunit => rule;

let marginTop: cssunit => rule;

let marginBottom: cssunit => rule;

let padding: cssunit => rule;

let paddingLeft: cssunit => rule;

let paddingRight: cssunit => rule;

let paddingTop: cssunit => rule;

let paddingBottom: cssunit => rule;

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

type boxSizing =
  | BorderBox
  | ContentBox;

let boxSizing: boxSizing => rule;

type overflow =
  | Visible
  | Hidden
  | Scroll
  | Auto;

let overflow: overflow => rule;

let overflowX: overflow => rule;

let overflowY: overflow => rule;

let zIndex: int => rule;

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

let shadow: (~x: int=?, ~y: int=?, ~blur: int=?, ~spread: int=?, color) => shadow;

let boxShadow: shadow => rule;

let boxShadows: list(shadow) => rule;

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

type animationIterationCount =
  | Infinite
  | Iterate(int);

let animationIterationCount: animationIterationCount => rule;

let animationName: keyframes => rule;

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
  | CubicBezier(float, float, float, float)
  | Steps(int, animationSteps)
  | Frames(int);

let animationTimingFunction: timingFunction => rule;

/* TRANSITION */
let transitionDelay: int => rule;

let transitionDuration: int => rule;

let transitionTimingFunction: timingFunction => rule;

let transitionProperty: string => rule;

let transition:
  (~delay: int=?, ~duration: int=?, ~timingFunction: timingFunction=?, string) => rule;

/* TRANSFORM */
let transform: transform => rule;

let transforms: list(transform) => rule;

let translate: (cssunit, cssunit) => transform;

let translateX: cssunit => transform;

let translateY: cssunit => transform;

let scale: (float, float) => transform;

let scaleX: float => transform;

let scaleY: float => transform;

let rotate: angle => transform;

let skew: (angle, angle) => transform;

let skewX: angle => transform;

let skewY: angle => transform;

let translate3d: (cssunit, cssunit, cssunit) => transform;

let translateZ: cssunit => transform;

let scale3d: (float, float, float) => transform;

let scaleZ: float => transform;

let rotateX: angle => transform;

let rotateY: angle => transform;

let rotateZ: angle => transform;

let perspective: cssunit => rule;

let selector: (string, list(rule)) => rule;

/* PSEUDO CLASSES */
let link: list(rule) => rule;

let disabled: list(rule) => rule;

let required: list(rule) => rule;

let readOnly: list(rule) => rule;

let focus: list(rule) => rule;

let visited: list(rule) => rule;

let active: list(rule) => rule;

let hover: list(rule) => rule;

let firstChild: list(rule) => rule;

let firstOfType: list(rule) => rule;

let lastChild: list(rule) => rule;

let lastOfType: list(rule) => rule;

let children: list(rule) => rule;

let media: (string, list(rule)) => rule;

/* MISC */
type cursor =
  | Auto
  | Pointer
  | Custom(string);

let cursor: cursor => rule;

let outline: (cssunit, borderStyle, color) => rule;

let outlineStyle: borderStyle => rule;

let outlineOffset: cssunit => rule;

let outlineWidth: cssunit => rule;

let outlineColor: color => rule;