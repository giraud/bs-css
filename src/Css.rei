type css = string;

type rule;

type color;

type cssunit;

type keyframes;

type transform;

type angle;

let unsafeValue: string => 'a;

let rad: float => angle;

let grad: float => angle;

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

let ex: float => cssunit;

let ch: float => cssunit;

let vh: float => cssunit;

let vw: float => cssunit;

let vmin: float => cssunit;

let vmax: float => cssunit;

let cm: float => cssunit;

let mm: float => cssunit;

let q: float => cssunit;

let inch: float => cssunit;

let pc: float => cssunit;

let zero: cssunit;

let auto: cssunit;

/* color */
let rgb: (int, int, int) => color;

let rgba: (int, int, int, float) => color;

let hsl: (angle, int, int) => color;

let hsla: (angle, int, int, float) => color;

let hex: string => color;

let currentColor: color;

let transparent: color;

let aliceblue: color;

let antiquewhite: color;

let aqua: color;

let aquamarine: color;

let azure: color;

let beige: color;

let bisque: color;

let black: color;

let blanchedalmond: color;

let blue: color;

let blueviolet: color;

let brown: color;

let burlywood: color;

let cadetblue: color;

let chartreuse: color;

let chocolate: color;

let coral: color;

let cornflowerblue: color;

let cornsilk: color;

let crimson: color;

let cyan: color;

let darkblue: color;

let darkcyan: color;

let darkgoldenrod: color;

let darkgray: color;

let darkgrey: color;

let darkgreen: color;

let darkkhaki: color;

let darkmagenta: color;

let darkolivegreen: color;

let darkorange: color;

let darkorchid: color;

let darkred: color;

let darksalmon: color;

let darkseagreen: color;

let darkslateblue: color;

let darkslategray: color;

let darkslategrey: color;

let darkturquoise: color;

let darkviolet: color;

let deeppink: color;

let deepskyblue: color;

let dimgray: color;

let dimgrey: color;

let dodgerblue: color;

let firebrick: color;

let floralwhite: color;

let forestgreen: color;

let fuchsia: color;

let gainsboro: color;

let ghostwhite: color;

let gold: color;

let goldenrod: color;

let gray: color;

let grey: color;

let green: color;

let greenyellow: color;

let honeydew: color;

let hotpink: color;

let indianred: color;

let indigo: color;

let ivory: color;

let khaki: color;

let lavender: color;

let lavenderblush: color;

let lawngreen: color;

let lemonchiffon: color;

let lightblue: color;

let lightcoral: color;

let lightcyan: color;

let lightgoldenrodyellow: color;

let lightgray: color;

let lightgrey: color;

let lightgreen: color;

let lightpink: color;

let lightsalmon: color;

let lightseagreen: color;

let lightskyblue: color;

let lightslategray: color;

let lightslategrey: color;

let lightsteelblue: color;

let lightyellow: color;

let lime: color;

let limegreen: color;

let linen: color;

let magenta: color;

let maroon: color;

let mediumaquamarine: color;

let mediumblue: color;

let mediumorchid: color;

let mediumpurple: color;

let mediumseagreen: color;

let mediumslateblue: color;

let mediumspringgreen: color;

let mediumturquoise: color;

let mediumvioletred: color;

let midnightblue: color;

let mintcream: color;

let mistyrose: color;

let moccasin: color;

let navajowhite: color;

let navy: color;

let oldlace: color;

let olive: color;

let olivedrab: color;

let orange: color;

let orangered: color;

let orchid: color;

let palegoldenrod: color;

let palegreen: color;

let paleturquoise: color;

let palevioletred: color;

let papayawhip: color;

let peachpuff: color;

let peru: color;

let pink: color;

let plum: color;

let powderblue: color;

let purple: color;

let red: color;

let rosybrown: color;

let royalblue: color;

let saddlebrown: color;

let salmon: color;

let sandybrown: color;

let seagreen: color;

let seashell: color;

let sienna: color;

let silver: color;

let skyblue: color;

let slateblue: color;

let slategray: color;

let slategrey: color;

let snow: color;

let springgreen: color;

let steelblue: color;

let tan: color;

let teal: color;

let thistle: color;

let tomato: color;

let turquoise: color;

let violet: color;

let wheat: color;

let white: color;

let whitesmoke: color;

let yellow: color;

let yellowgreen: color;

/* image */
type direction =
  | Angle(angle)
  | ToTop
  | ToBottom
  | ToLeft
  | ToRight
  | ToTopLeft
  | ToTopRight
  | ToBottomLeft
  | ToBottomRight;

type verticalPosition =
  | Top
  | FromTop(cssunit)
  | Center
  | Bottom
  | FromBottom(cssunit);

type horizontalPosition =
  | Left
  | FromLeft(cssunit)
  | Center
  | Right
  | FromRight(cssunit);

type shape =
  | Circle
  | Ellipse;

type extent =
  | ClosestSide
  | ClosestCorner
  | FarthestSide
  | FarthestCorner;

type colorStop = (color, cssunit);

type gradient;

let linearGradient: (direction, list(colorStop)) => gradient;

let radialGradient:
  (shape, verticalPosition, horizontalPosition, extent, list(colorStop)) =>
  gradient;

let repeatingLinearGradient: (direction, list(colorStop)) => gradient;

let repeatingRadialGradient:
  (shape, verticalPosition, horizontalPosition, extent, list(colorStop)) =>
  gradient;

type image =
  | Url(string)
  | Gradient(gradient)
  | Element(string);

/* CSS RULES */
let label: string => rule;

let unsafe: (string, 'a) => rule;


type visibility =
  | Visible
  | Hidden;

let visibility: visibility => rule;

let opacity: float => rule;

type listStyleType =
  | Disc
  | Circle
  | Square
  | Decimal
  | DecimalLeadingZero
  | LowerRoman
  | UpperRoman
  | LowerGreek
  | LowerLatin
  | UpperLatin
  | Armenian
  | Georgian
  | LowerAlpha
  | UpperAlpha
  | None;

let listStyleType: listStyleType => rule;

type listStyleImage =
  | None
  | Url(string);

let listStyleImage: listStyleImage => rule;

type listStylePosition =
  | Inside
  | Outside;

let listStylePopsition: listStylePosition => rule;

/* BACKGROUND */
let backgroundImage: string => rule;

let backgroundGradient: gradient => rule;

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

type fontVariant =
  | Normal
  | SmallCaps;

let fontVariant: fontVariant => rule;

type textDecoration =
  | None
  | Underline(color)
  | UnderlineWavy(color);

[@deprecated "Use the individual textDecoration properties instead"]
let textDecoration: textDecoration => rule;

type textDecorationLineValue =
  | Underline
  | Overline
  | LineThrough;

type textDecorationLine =
  | None
  | Values(list(textDecorationLineValue));

let textDecorationLine: textDecorationLine => rule;

type textDecorationStyle =
  | Solid
  | Double
  | Dotted
  | Dashed
  | Wavy;

let textDecorationStyle: textDecorationStyle => rule;

let textDecorationColor: color => rule;

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

type textOverflow =
  | Clip
  | Ellipsis;

let textOverflow: textOverflow => rule;

type overflowWrap =
  | Normal
  | BreakWord;

let overflowWrap: overflowWrap => rule;

let wordWrap: overflowWrap => rule;

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

let margin2: (~v: cssunit, ~h: cssunit) => rule;

let margin3: (~top: cssunit, ~h: cssunit, ~bottom: cssunit) => rule;

let margin4:
  (~top: cssunit, ~right: cssunit, ~bottom: cssunit, ~left: cssunit) => rule;

let marginLeft: cssunit => rule;

let marginRight: cssunit => rule;

let marginTop: cssunit => rule;

let marginBottom: cssunit => rule;

let padding: cssunit => rule;

let padding2: (~v: cssunit, ~h: cssunit) => rule;

let padding3: (~top: cssunit, ~h: cssunit, ~bottom: cssunit) => rule;

let padding4:
  (~top: cssunit, ~right: cssunit, ~bottom: cssunit, ~left: cssunit) => rule;

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

let shadow:
  (~x: int=?, ~y: int=?, ~blur: int=?, ~spread: int=?, color) => shadow;

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
  (
    ~delay: int=?,
    ~duration: int=?,
    ~timingFunction: timingFunction=?,
    string
  ) =>
  rule;

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

type whiteSpace =
  | Normal
  | Nowrap
  | Pre
  | PreWrap
  | PreLine;

let whiteSpace: whiteSpace => rule;

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

let before: list(rule) => rule;

let after: list(rule) => rule;

let firstChild: list(rule) => rule;

let firstOfType: list(rule) => rule;

let lastChild: list(rule) => rule;

let lastOfType: list(rule) => rule;

let children: list(rule) => rule;

let media: (string, list(rule)) => rule;

/* MISC */
type cursor =
  | Auto
  | Default
  | None
  | ContextMenu
  | Help
  | Pointer
  | Progress
  | Wait
  | Cell
  | Crosshair
  | Text
  | VerticalText
  | Alias
  | Copy
  | Move
  | NoDrop
  | NotAllowed
  | AllScroll
  | ColResize
  | RowResize
  | NResize
  | EResize
  | SResize
  | WResize
  | NEResize
  | NWResize
  | SEResize
  | SWResize
  | EWResize
  | NSResize
  | NESWResize
  | NWSEResize
  | ZoomIn
  | ZoomOut
  | Grab
  | Grabbing
  | Custom(string);

let cursor: cursor => rule;

let outline: (cssunit, borderStyle, color) => rule;

let outlineStyle: borderStyle => rule;

let outlineOffset: cssunit => rule;

let outlineWidth: cssunit => rule;

let outlineColor: color => rule;

module SVG: {
  let fill: color => rule;
  let fillOpacity: float => rule;
  let stroke: color => rule;
  let strokeWidth: cssunit => rule;
  let strokeOpacity: float => rule;
};
