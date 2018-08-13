type rule = [
  | `selector(string, list(rule))
  | `declaration(string, string)
  | `animation(string)
  | `transition(string)
  | `shadow(string)
];

let empty: list(rule);
let merge: list(list(rule)) => list(rule);
let style: list(rule) => string;

let global: (string, list(rule)) => unit;
let important: rule => rule;
let label: string => rule;

/********************************************************
 ************************ VALUES ************************
 ********************************************************/
type angle = [ | `deg(int) | `rad(float) | `grad(float) | `turn(float)];

let deg: int => [> | `deg(int)];
let rad: float => [> | `rad(float)];
let grad: float => [> | `grad(float)];
let turn: float => [> | `turn(float)];

type color = [
  | `rgb(int, int, int)
  | `rgba(int, int, int, float)
  | `hsl(int, int, int)
  | `hsla(int, int, int, float)
  | `transparent
  | `hex(string)
  | `currentColor
];

let rgb: (int, int, int) => [> | `rgb(int, int, int)];
let rgba: (int, int, int, float) => [> | `rgba(int, int, int, float)];
let hsl: (int, int, int) => [> | `hsl(int, int, int)];
let hsla: (int, int, int, float) => [> | `hsla(int, int, int, float)];
let hex: string => [> | `hex(string)];
let transparent: [> | `transparent];
let currentColor: [> | `currentColor];

type gradient = [
  | `linearGradient(angle, list((int, color)))
  | `repeatingLinearGradient(angle, list((int, color)))
  | `radialGradient(list((int, color)))
  | `repeatingRadialGradient(list((int, color)))
];

let linearGradient: (angle, list((int, color))) => [> | `linearGradient(angle, list((int, color)))];
let repeatingLinearGradient:
  (angle, list((int, color))) => [> | `repeatingLinearGradient(angle, list((int, color)))];
let radialGradient: list((int, color)) => [> | `radialGradient(list((int, color)))];
let repeatingRadialGradient: list((int, color)) => [> | `repeatingRadialGradient(list((int, color)))];

let aliceblue: [> | `hex(string)];
let antiquewhite: [> | `hex(string)];
let aqua: [> | `hex(string)];
let aquamarine: [> | `hex(string)];
let azure: [> | `hex(string)];
let beige: [> | `hex(string)];
let bisque: [> | `hex(string)];
let black: [> | `hex(string)];
let blanchedalmond: [> | `hex(string)];
let blue: [> | `hex(string)];
let blueviolet: [> | `hex(string)];
let brown: [> | `hex(string)];
let burlywood: [> | `hex(string)];
let cadetblue: [> | `hex(string)];
let chartreuse: [> | `hex(string)];
let chocolate: [> | `hex(string)];
let coral: [> | `hex(string)];
let cornflowerblue: [> | `hex(string)];
let cornsilk: [> | `hex(string)];
let crimson: [> | `hex(string)];
let cyan: [> | `hex(string)];
let darkblue: [> | `hex(string)];
let darkcyan: [> | `hex(string)];
let darkgoldenrod: [> | `hex(string)];
let darkgray: [> | `hex(string)];
let darkgrey: [> | `hex(string)];
let darkgreen: [> | `hex(string)];
let darkkhaki: [> | `hex(string)];
let darkmagenta: [> | `hex(string)];
let darkolivegreen: [> | `hex(string)];
let darkorange: [> | `hex(string)];
let darkorchid: [> | `hex(string)];
let darkred: [> | `hex(string)];
let darksalmon: [> | `hex(string)];
let darkseagreen: [> | `hex(string)];
let darkslateblue: [> | `hex(string)];
let darkslategray: [> | `hex(string)];
let darkslategrey: [> | `hex(string)];
let darkturquoise: [> | `hex(string)];
let darkviolet: [> | `hex(string)];
let deeppink: [> | `hex(string)];
let deepskyblue: [> | `hex(string)];
let dimgray: [> | `hex(string)];
let dimgrey: [> | `hex(string)];
let dodgerblue: [> | `hex(string)];
let firebrick: [> | `hex(string)];
let floralwhite: [> | `hex(string)];
let forestgreen: [> | `hex(string)];
let fuchsia: [> | `hex(string)];
let gainsboro: [> | `hex(string)];
let ghostwhite: [> | `hex(string)];
let gold: [> | `hex(string)];
let goldenrod: [> | `hex(string)];
let gray: [> | `hex(string)];
let grey: [> | `hex(string)];
let green: [> | `hex(string)];
let greenyellow: [> | `hex(string)];
let honeydew: [> | `hex(string)];
let hotpink: [> | `hex(string)];
let indianred: [> | `hex(string)];
let indigo: [> | `hex(string)];
let ivory: [> | `hex(string)];
let khaki: [> | `hex(string)];
let lavender: [> | `hex(string)];
let lavenderblush: [> | `hex(string)];
let lawngreen: [> | `hex(string)];
let lemonchiffon: [> | `hex(string)];
let lightblue: [> | `hex(string)];
let lightcoral: [> | `hex(string)];
let lightcyan: [> | `hex(string)];
let lightgoldenrodyellow: [> | `hex(string)];
let lightgray: [> | `hex(string)];
let lightgrey: [> | `hex(string)];
let lightgreen: [> | `hex(string)];
let lightpink: [> | `hex(string)];
let lightsalmon: [> | `hex(string)];
let lightseagreen: [> | `hex(string)];
let lightskyblue: [> | `hex(string)];
let lightslategray: [> | `hex(string)];
let lightslategrey: [> | `hex(string)];
let lightsteelblue: [> | `hex(string)];
let lightyellow: [> | `hex(string)];
let lime: [> | `hex(string)];
let limegreen: [> | `hex(string)];
let linen: [> | `hex(string)];
let magenta: [> | `hex(string)];
let maroon: [> | `hex(string)];
let mediumaquamarine: [> | `hex(string)];
let mediumblue: [> | `hex(string)];
let mediumorchid: [> | `hex(string)];
let mediumpurple: [> | `hex(string)];
let mediumseagreen: [> | `hex(string)];
let mediumslateblue: [> | `hex(string)];
let mediumspringgreen: [> | `hex(string)];
let mediumturquoise: [> | `hex(string)];
let mediumvioletred: [> | `hex(string)];
let midnightblue: [> | `hex(string)];
let mintcream: [> | `hex(string)];
let mistyrose: [> | `hex(string)];
let moccasin: [> | `hex(string)];
let navajowhite: [> | `hex(string)];
let navy: [> | `hex(string)];
let oldlace: [> | `hex(string)];
let olive: [> | `hex(string)];
let olivedrab: [> | `hex(string)];
let orange: [> | `hex(string)];
let orangered: [> | `hex(string)];
let orchid: [> | `hex(string)];
let palegoldenrod: [> | `hex(string)];
let palegreen: [> | `hex(string)];
let paleturquoise: [> | `hex(string)];
let palevioletred: [> | `hex(string)];
let papayawhip: [> | `hex(string)];
let peachpuff: [> | `hex(string)];
let peru: [> | `hex(string)];
let pink: [> | `hex(string)];
let plum: [> | `hex(string)];
let powderblue: [> | `hex(string)];
let purple: [> | `hex(string)];
let rebeccapurple: [> | `hex(string)];
let red: [> | `hex(string)];
let rosybrown: [> | `hex(string)];
let royalblue: [> | `hex(string)];
let saddlebrown: [> | `hex(string)];
let salmon: [> | `hex(string)];
let sandybrown: [> | `hex(string)];
let seagreen: [> | `hex(string)];
let seashell: [> | `hex(string)];
let sienna: [> | `hex(string)];
let silver: [> | `hex(string)];
let skyblue: [> | `hex(string)];
let slateblue: [> | `hex(string)];
let slategray: [> | `hex(string)];
let slategrey: [> | `hex(string)];
let snow: [> | `hex(string)];
let springgreen: [> | `hex(string)];
let steelblue: [> | `hex(string)];
let tan: [> | `hex(string)];
let teal: [> | `hex(string)];
let thistle: [> | `hex(string)];
let tomato: [> | `hex(string)];
let turquoise: [> | `hex(string)];
let violet: [> | `hex(string)];
let wheat: [> | `hex(string)];
let white: [> | `hex(string)];
let whitesmoke: [> | `hex(string)];
let yellow: [> | `hex(string)];
let yellowgreen: [> | `hex(string)];

type length = [
  | `calc([ | `add | `sub], length, length)
  | `ch(float)
  | `cm(float)
  | `em(float)
  | `ex(float)
  | `mm(float)
  | `percent(float)
  | `pt(int)
  | `px(int)
  | `rem(float)
  | `vh(float)
  | `vmin(float)
  | `vmax(float)
  | `vw(float)
  | `zero
];

type gridLength = [ length | `fr(float) | `minContent | `maxContent];

let ch: float => [> | `ch(float)];
let cm: float => [> | `cm(float)];
let em: float => [> | `em(float)];
let ex: float => [> | `ex(float)];
let fr: float => [> | `fr(float)];
let mm: float => [> | `mm(float)];
let pct: float => [> | `percent(float)];
let pt: int => [> | `pt(int)];
let px: int => [> | `px(int)];
let rem: float => [> | `rem(float)];
let vh: float => [> | `vh(float)];
let vmax: float => [> | `vmax(float)];
let vmin: float => [> | `vmin(float)];
let vw: float => [> | `vw(float)];
let zero: [> | `zero];

module Calc: {
  let (-): (length, length) => [> length];
  let (+): (length, length) => [> length];
};

let size: (length, length) => [> | `size(length, length)];

let solid: [> | `solid];
let dotted: [> | `dotted];
let dashed: [> | `dashed];

let localUrl: string => [> | `localUrl(string)];
let url: string => [> | `url(string)];

let none: [> | `none];
let auto: [> | `auto];
let hidden: [> | `hidden];
let visible: [> | `visible];
let local: [> | `local];
let scroll: [> | `scroll];

let paddingBox: [> | `paddingBox];
let borderBox: [> | `borderBox];
let contentBox: [> | `contentBox];

let noRepeat: [> | `noRepeat];
let repeat: [> | `repeat];
let repeatX: [> | `repeatX];
let repeatY: [> | `repeatY];
let contain: [> | `contain];
let cover: [> | `cover];

let row: [> | `row];
let rowReverse: [> | `rowReverse];
let column: [> | `column];
let columnReverse: [> | `columnReverse];
let wrap: [> | `wrap];
let nowrap: [> | `nowrap];
let wrapReverse: [> | `wrapReverse];

let flexBox: [> | `flex];
let grid: [> | `grid];
let inlineGrid: [> | `inlineGrid];
let block: [> | `block];
let inline: [> | `inline];
let inlineBlock: [> | `inlineBlock];
let inlineFlex: [> | `inlineFlex];

let absolute: [> | `absolute];
let relative: [> | `relative];
let static: [> | `static];
let fixed: [> | `fixed];
let sticky: [> | `sticky];

let flexStart: [> | `flexStart];
let flexEnd: [> | `flexEnd];
let center: [> | `center];
let stretch: [> | `stretch];
let spaceBetween: [> | `spaceBetween];
let spaceAround: [> | `spaceAround];
let baseline: [> | `baseline];

let forwards: [> | `forwards];
let backwards: [> | `backwards];
let both: [> | `both];
let infinite: [> | `infinite];
let count: int => [> | `count(int)];
let paused: [> | `paused];
let running: [> | `running];

let inside: [> | `inside];
let outside: [> | `outside];

let translate: (length, length) => [> | `translate(length, length)];
let translate3d: (length, length, length) => [> | `translate3d(length, length, length)];
let translateX: length => [> | `translateX(length)];
let translateY: length => [> | `translateY(length)];
let translateZ: length => [> | `translateZ(length)];
let scale: (float, float) => [> | `scale(float, float)];
let scale3d: (float, float, float) => [> | `scale3d(float, float, float)];
let scaleX: float => [> | `scaleX(float)];
let scaleY: float => [> | `scaleY(float)];
let scaleZ: float => [> | `scaleZ(float)];
let rotate: angle => [> | `rotate(angle)];
let rotate3d: (float, float, float, angle) => [> | `rotate3d(float, float, float, angle)];
let rotateX: angle => [> | `rotateX(angle)];
let rotateY: angle => [> | `rotateY(angle)];
let rotateZ: angle => [> | `rotateZ(angle)];
let skew: (angle, angle) => [> | `skew(angle, angle)];
let skewX: angle => [> | `skewX(angle)];
let skewY: angle => [> | `skewY(angle)];

let italic: [> | `italic];
let oblique: [> | `oblique];

let underline: [> | `underline];
let overline: [> | `overline];
let lineThrough: [> | `lineThough];

let clip: [> | `clip];
let ellipsis: [> | `ellipsis];

let wavy: [> | `wavy];
let double: [> | `double];

let uppercase: [> | `uppercase];
let lowercase: [> | `lowercase];
let capitalize: [> | `capitalize];

let sub: [> | `sub];
let super: [> | `super];
let textTop: [> | `textTop];
let textBottom: [> | `textBottom];
let middle: [> | `middle];

let normal: [> | `normal];

let breakAll: [> | `breakAll];
let keepAll: [> | `keepAll];
let breakWord: [> | `breakWord];

let reverse: [> | `reverse];
let alternate: [> | `alternate];
let alternateReverse: [> | `alternateReverse];

let fill: [> | `fill];
let content: [> | `content];
let maxContent: [> | `maxContent];
let minContent: [> | `minContent];
let fitContent: [> | `fitContent];

let all: [> | `all];
let text: [> | `text];

let linear: [> | `linear];
let ease: [> | `ease];
let easeIn: [> | `easeIn];
let easeOut: [> | `easeOut];
let easeInOut: [> | `easeInOut];
let stepStart: [> | `stepStart];
let stepEnd: [> | `stepEnd];
let steps: (int, [ | `start | `end_]) => [> | `steps(int, [ | `start | `end_])];
let cubicBesier: (float, float, float, float) => [> | `cubicBezier(float, float, float, float)];

let round: [> | `round];
let miter: [> | `miter];
let bevel: [> | `bevel];
let butt: [> | `butt];
let square: [> | `square];

/********************************************************
 ******************** PROPERTIES ************************
 ********************************************************/

let unsafe: (string, string) => rule;

/**
 * Layout
*/

let display: [ | `flex | `block | `inline | `inlineBlock | `none | `inlineFlex | `grid | `inlineGrid] => rule;
let position: [ | `absolute | `relative | `static | `fixed | `sticky] => rule;

let top: [ length] => rule;
let bottom: [ length] => rule;
let left: [ length] => rule;
let right: [ length] => rule;

let flex: int => rule;
let flexGrow: int => rule;
let flexShrink: int => rule;
let flexBasis: [ length | `auto | `fill | `content | `maxContent | `minContent | `fitContent] => rule;

let flexDirection: [ | `row | `column | `rowReverse | `columnReverse] => rule;
let flexWrap: [ | `wrap | `nowrap | `wrapReverse] => rule;
let order: int => rule;

let gridTemplateColumns: list([ gridLength | `auto]) => rule;
let gridTemplateRows: list([ gridLength | `auto]) => rule;
let gridAutoRows: [ length | `auto] => rule;
let gridColumn: (int, int) => rule;
let gridRow: (int, int) => rule;
let gridColumnStart: int => rule;
let gridColumnEnd: int => rule;
let gridRowStart: int => rule;
let gridRowEnd: int => rule;
let gridColumnGap: length => rule;
let gridRowGap: length => rule;
let gridGap: length => rule;

let width: [ length | `auto] => rule;
let minWidth: [ length | `auto] => rule;
let maxWidth: [ length | `auto] => rule;
let height: [ length | `auto] => rule;
let minHeight: [ length | `auto] => rule;
let maxHeight: [ length | `auto] => rule;

let margin: [ length | `auto] => rule;
let margin2: (~v: [ length | `auto], ~h: [ length | `auto]) => rule;
let margin3: (~top: [ length | `auto], ~h: [ length | `auto], ~bottom: [ length | `auto]) => rule;
let margin4:
  (~top: [ length | `auto], ~right: [ length | `auto], ~bottom: [ length | `auto], ~left: [ length | `auto]) => rule;
let marginLeft: [ length | `auto] => rule;
let marginRight: [ length | `auto] => rule;
let marginTop: [ length | `auto] => rule;
let marginBottom: [ length | `auto] => rule;

let padding: length => rule;
let padding2: (~v: length, ~h: length) => rule;
let padding3: (~top: length, ~h: length, ~bottom: length) => rule;
let padding4: (~top: length, ~right: length, ~bottom: length, ~left: length) => rule;
let paddingLeft: length => rule;
let paddingRight: length => rule;
let paddingTop: length => rule;
let paddingBottom: length => rule;

let alignContent: [ | `stretch | `flexStart | `center | `flexEnd | `spaceBetween | `spaceAround] => rule;
let alignItems: [ | `stretch | `flexStart | `center | `flexEnd | `baseline] => rule;
let alignSelf: [ | `stretch | `flexStart | `center | `flexEnd | `baseline | `auto] => rule;
let justifyContent: [ | `flexStart | `center | `flexEnd | `spaceBetween | `spaceAround | `stretch] => rule;

let boxSizing: [ | `borderBox | `contentBox] => rule;

let float: [ | `left | `right | `none] => rule;
let clear: [ | `left | `right | `both] => rule;

let overflow: [ | `hidden | `visible | `scroll | `auto] => rule;
let overflowX: [ | `hidden | `visible | `scroll | `auto] => rule;
let overflowY: [ | `hidden | `visible | `scroll | `auto] => rule;

let zIndex: int => rule;

/**
 * Style
 */
let backfaceVisibility: [ | `visible | `hidden] => rule;
let visibility: [ | `visible | `hidden] => rule;

let border: (length, [ | `solid | `dashed | `dotted | `none], [ color]) => rule;
let borderWidth: length => rule;
let borderStyle: [ | `solid | `dashed | `dotted | `none] => rule;
let borderColor: color => rule;

let borderTop: (length, [ | `solid | `dashed | `dotted | `none], [ color]) => rule;
let borderTopWidth: length => rule;
let borderTopStyle: [ | `solid | `dashed | `dotted | `none] => rule;
let borderTopColor: color => rule;
let borderBottom: (length, [ | `solid | `dashed | `dotted | `none], [ color]) => rule;
let borderBottomWidth: length => rule;
let borderBottomStyle: [ | `solid | `dashed | `dotted | `none] => rule;
let borderBottomColor: color => rule;
let borderLeft: (length, [ | `solid | `dashed | `dotted | `none], [ color]) => rule;
let borderLeftWidth: length => rule;
let borderLeftStyle: [ | `solid | `dashed | `dotted | `none] => rule;
let borderLeftColor: color => rule;
let borderRight: (length, [ | `solid | `dashed | `dotted], [ color]) => rule;
let borderRightWidth: length => rule;
let borderRightStyle: [ | `solid | `dashed | `dotted | `none] => rule;
let borderRightColor: color => rule;

let borderRadius: length => rule;
let borderTopLeftRadius: length => rule;
let borderTopRightRadius: length => rule;
let borderBottomLeftRadius: length => rule;
let borderBottomRightRadius: length => rule;

let tableLayout: [ | `auto | `fixed] => rule;
let borderCollapse: [ | `separate | `collapse] => rule;
let borderSpacing: length => rule;

let boxShadow:
  (~x: length=?, ~y: length=?, ~blur: length=?, ~spread: length=?, ~inset: bool=?, color) => [> | `shadow(string)];
let boxShadows: list([ | `shadow(string)]) => rule;

let background: [ color | `url(string) | gradient | `none] => rule;
let backgroundColor: [ color] => rule;
let backgroundImage: [ | `url(string) | gradient | `none] => rule;
let backgroundAttachment: [ | `scroll | `fixed | `local] => rule;
let backgroundClip: [ | `borderBox | `contentBox | `paddingBox] => rule;
let backgroundOrigin: [ | `borderBox | `contentBox | `paddingBox] => rule;
let backgroundPosition: ([ length], [ length]) => rule;
let backgroundRepeat: [ | `repeat | `noRepeat | `repeatX | `repeatY] => rule;
let backgroundSize: [ | `size(length, length) | `auto | `cover | `contain] => rule;

let cursor:
  [
    | `pointer
    | `alias
    | `allScroll
    | `auto
    | `cell
    | `contextMenu
    | `default
    | `none
    | `crosshair
    | `copy
    | `grab
    | `grabbing
    | `help
    | `move
    | `notAllowed
    | `progress
    | `text
    | `wait
    | `zoomIn
    | `zoomOut
  ] =>
  rule;

let clipPath: [ | `url(string)] => rule;

type listStyleType = [
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
let listStyle: (listStyleType, [ | `inside | `outside], [ | `none | `url(string)]) => rule;
let listStyleType: listStyleType => rule;
let listStylePosition: [ | `inside | `outside] => rule;
let listStyleImage: [ | `none | `url(string)] => rule;

let opacity: float => rule;

type outlineStyle = [ | `none | `hidden | `dotted | `dashed | `solid | `double | `groove | `ridge | `inset | `outset];
let outline: (length, outlineStyle, color) => rule;
let outlineStyle: outlineStyle => rule;
let outlineWidth: length => rule;
let outlineColor: color => rule;
let outlineOffset: length => rule;

let pointerEvents: [ | `auto | `none] => rule;

/**
 * Text
 */

type fontStyle = [ | `italic | `normal | `oblique];

let color: color => rule;
let fontFamily: string => rule;
let fontFace:
  (
    ~fontFamily: string,
    ~src: list([< | `localUrl(string) | `url(string)]),
    ~fontStyle: fontStyle=?,
    ~fontWeight: int=?,
    unit
  ) =>
  string;
let fontSize: length => rule;
let fontVariant: [ | `normal | `smallCaps] => rule;
let fontStyle: fontStyle => rule;
let fontWeight: int => rule;
let letterSpacing: [ | `normal | length] => rule;
let lineHeight: [ | `normal | `abs(float) | length] => rule;
let textAlign: [ | `left | `center | `right | `justify] => rule;
let textDecoration: [ | `none | `underline | `overline | `lineThrough] => rule;
let textDecorationColor: color => rule;
let textDecorationStyle: [ | `wavy | `solid | `dotted | `dashed | `double] => rule;
let textIndent: length => rule;
let textOverflow: [ | `clip | `ellipsis | `string(string)] => rule;
let textShadow: (~x: length=?, ~y: length=?, ~blur: length=?, color) => rule;
let textTransform: [ | `uppercase | `lowercase | `capitalize | `none] => rule;
let userSelect: [ | `auto | `all | `text | `none] => rule;
let verticalAlign: [ | `baseline | length | `sub | `super | `top | `textTop | `middle | `bottom | `textBottom] => rule;
let whiteSpace: [ | `normal | `nowrap | `pre | `preLine | `preWrap] => rule;
let wordBreak: [ | `breakAll | `keepAll | `normal] => rule;
let wordSpacing: [ | `normal | length] => rule;
let wordWrap: [ | `normal | `breakWord] => rule;

/**
 * Transform
 */

type transform = [
  | `translate(length, length)
  | `translate3d(length, length, length)
  | `translateX(length)
  | `translateY(length)
  | `translateZ(length)
  | `scale(float, float)
  | `scale3d(float, float, float)
  | `scaleX(float)
  | `scaleY(float)
  | `scaleZ(float)
  | `rotate(angle)
  | `rotate3d(float, float, float, angle)
  | `rotateX(angle)
  | `rotateY(angle)
  | `rotateZ(angle)
  | `skew(angle, angle)
  | `skewX(angle)
  | `skewY(angle)
  | `perspective(int)
];

let transform: transform => rule;
let transforms: list(transform) => rule;
let transformOrigin: (length, length) => rule;
let transformOrigin3d: (length, length, length) => rule;
let transformStyle: [ | `preserve3d | `flat] => rule;
let perspective: [ | `none | length] => rule;
let perspectiveOrigin: (length, length) => rule;

/**
  * Transition
  */
type timingFunction = [
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
let transition:
  (~duration: int=?, ~delay: int=?, ~timingFunction: timingFunction=?, string) => [> | `transition(string)];
let transitions: list([ | `transition(string)]) => rule;
let transitionDelay: int => rule;
let transitionDuration: int => rule;
let transitionTimingFunction: timingFunction => rule;
let transitionProperty: string => rule;

/**
 * Animation
 */

type animation;
let keyframes: list((int, list(rule))) => animation;

type animationDirection = [ | `normal | `reverse | `alternate | `alternateReverse];

type animationFillMode = [ | `none | `forwards | `backwards | `both];
type animationIterationCount = [ | `infinite | `count(int)];
type animationPlayState = [ | `paused | `running];

let animation:
  (
    ~duration: int=?,
    ~delay: int=?,
    ~direction: animationDirection=?,
    ~timingFunction: timingFunction=?,
    ~fillMode: animationFillMode=?,
    ~playState: animationPlayState=?,
    ~iterationCount: animationIterationCount=?,
    animation
  ) =>
  [> | `animation(string)];
let animations: list([ | `animation(string)]) => rule;

let animationDelay: int => rule;
let animationDirection: animationDirection => rule;
let animationDuration: int => rule;
let animationFillMode: animationFillMode => rule;
let animationIterationCount: [ | `infinite | `count(int)] => rule;
let animationName: animation => rule;
let animationPlayState: [ | `paused | `running] => rule;
let animationTimingFunction: timingFunction => rule;

/**
 * selectors
 */
let selector: (string, list(rule)) => rule;
let active: list(rule) => rule;
let after: list(rule) => rule;
let before: list(rule) => rule;
let checked: list(rule) => rule;
let children: list(rule) => rule;
let directSibling: list(rule) => rule;
let disabled: list(rule) => rule;
let firstChild: list(rule) => rule;
let firstOfType: list(rule) => rule;
let focus: list(rule) => rule;
let hover: list(rule) => rule;
let lastChild: list(rule) => rule;
let lastOfType: list(rule) => rule;
let link: list(rule) => rule;
let readOnly: list(rule) => rule;
let required: list(rule) => rule;
let visited: list(rule) => rule;
let enabled: list(rule) => rule;
let noContent: list(rule) => rule;
let default: list(rule) => rule;
let anyLink: list(rule) => rule;
let onlyChild: list(rule) => rule;
let onlyOfType: list(rule) => rule;
let optional: list(rule) => rule;
let invalid: list(rule) => rule;
let outOfRange: list(rule) => rule;
let siblings: list(rule) => rule;
let target: list(rule) => rule;
let firstLine: list(rule) => rule;
let firstLetter: list(rule) => rule;
let selection: list(rule) => rule;
let placeholder: list(rule) => rule;

let media: (string, list(rule)) => rule;

/**
 * SVG
 */

module SVG: {
  let fill: color => rule;
  let fillRule: [ | `nonzero | `evenodd] => rule;
  let fillOpacity: float => rule;
  let stroke: color => rule;
  let strokeLinecap: [ | `butt | `round | `square] => rule;
  let strokeLinejoin: [ | `miter | `round | `bevel] => rule;
  let strokeMiterlimit: float => rule;
  let strokeWidth: length => rule;
  let strokeOpacity: float => rule;
  let stopColor: color => rule;
  let stopOpacity: float => rule;
};
