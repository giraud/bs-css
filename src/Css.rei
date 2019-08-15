module Types = Css_Types;

type rule = [
  | `selector(string, list(rule))
  | `declaration(string, string)
];

type cache;

let empty: list(rule);
let merge: list(string) => string;
let style: list(rule) => string;
let toJson: list(rule) => Js.Json.t;
let cache: cache;

let global: (string, list(rule)) => unit;
let insertRule: string => unit;

let important: rule => rule;
let label: string => rule;

/* ********
 Properties
 ********** */

let bottom: [ Types.Length.t | Types.Cascading.t] => rule;
let direction: [< Types.Direction.t | Types.Cascading.t] => rule;
let fontFamily: string => rule;
let fontSize: [ Types.Length.t | Types.Cascading.t] => rule;
let fontStyle: [ Types.FontStyle.t | Types.Cascading.t] => rule;
let fontVariant: [ Types.FontVariant.t | Types.Cascading.t] => rule;
let gridAutoFlow: [ Types.GridAutoFlow.t | Types.Cascading.t] => rule;
let gridColumn: (int, int) => rule;
let gridColumnEnd: int => rule;
let gridColumnGap: Types.Length.t => rule;
let gridColumnStart: int => rule;
let gridRow: (int, int) => rule;
let gridRowEnd: int => rule;
let gridRowGap: Types.Length.t => rule;
let gridRowStart: int => rule;
let gridGap: Types.Length.t => rule;
let left: [ Types.Length.t | Types.Cascading.t] => rule;
let margin: [ Types.Length.t | Types.Margin.t] => rule;
let margin2:
  (
    ~v: [ Types.Length.t | Types.Margin.t],
    ~h: [ Types.Length.t | Types.Margin.t]
  ) =>
  rule;
let margin3:
  (
    ~top: [ Types.Length.t | Types.Margin.t],
    ~h: [ Types.Length.t | Types.Margin.t],
    ~bottom: [ Types.Length.t | Types.Margin.t]
  ) =>
  rule;
let margin4:
  (
    ~top: [ Types.Length.t | Types.Margin.t],
    ~right: [ Types.Length.t | Types.Margin.t],
    ~bottom: [ Types.Length.t | Types.Margin.t],
    ~left: [ Types.Length.t | Types.Margin.t]
  ) =>
  rule;
let marginLeft: [ Types.Length.t | Types.Margin.t] => rule;
let marginRight: [ Types.Length.t | Types.Margin.t] => rule;
let marginTop: [ Types.Length.t | Types.Margin.t] => rule;
let marginBottom: [ Types.Length.t | Types.Margin.t] => rule;
let overflow: [ Types.Overflow.t] => rule;
let overflowX: [ Types.Overflow.t] => rule;
let overflowY: [ Types.Overflow.t] => rule;
let padding: Types.Length.t => rule;
let padding2: (~v: Types.Length.t, ~h: Types.Length.t) => rule;
let padding3:
  (~top: Types.Length.t, ~h: Types.Length.t, ~bottom: Types.Length.t) => rule;
let padding4:
  (
    ~top: Types.Length.t,
    ~right: Types.Length.t,
    ~bottom: Types.Length.t,
    ~left: Types.Length.t
  ) =>
  rule;
let paddingLeft: Types.Length.t => rule;
let paddingRight: Types.Length.t => rule;
let paddingTop: Types.Length.t => rule;
let paddingBottom: Types.Length.t => rule;
let position: [ Types.Position.t | Types.Cascading.t] => rule;
let resize: [ Types.Resize.t | Types.Cascading.t] => rule;
let right: [ Types.Length.t | Types.Cascading.t] => rule;
let top: [ Types.Length.t | Types.Cascading.t] => rule;
let unsafe: (string, string) => rule;
let verticalAlign:
  [ Types.VerticalAlign.t | Types.Length.t | Types.Cascading.t] => rule;
let zIndex: int => rule;

/* *************************************
 Type aliases for backward compatibility
 *************************************** */

type cascading = Types.Cascading.t;
type angle = Types.Angle.t;
type fontStyle = Types.FontStyle.t;
type length = Types.Length.t;

/* **************************************************
 Constructor aliases, for ease of use.
 Refer to the equivalent function in the type module.
 **************************************************** */

let initial: [> Types.Cascading.t];
let inherit_: [> Types.Cascading.t];
let unset: [> Types.Cascading.t];

let ch: float => [> | `ch(float)];
let cm: float => [> | `cm(float)];
let em: float => [> | `em(float)];
let ex: float => [> | `ex(float)];
let mm: float => [> | `mm(float)];
let pt: int => [> | `pt(int)];
let px: int => [> | `px(int)];
let pxFloat: float => [> | `pxFloat(float)];
let rem: float => [> | `rem(float)];
let vh: float => [> | `vh(float)];
let vmin: float => [> | `vmin(float)];
let vmax: float => [> | `vmax(float)];
let zero: [> | `zero];

let deg: float => Types.Angle.t;
let rad: float => Types.Angle.t;
let grad: float => Types.Angle.t;
let turn: float => Types.Angle.t;

let ltr: [> Types.Direction.t];
let rtl: [> Types.Direction.t];

let absolute: [> Types.Position.t];
let relative: [> Types.Position.t];
let static: [> Types.Position.t];
let fixed: [> | `fixed];
let sticky: [> Types.Position.t];

let horizontal: [> Types.Resize.t];
let vertical: [> Types.Resize.t];

let smallCaps: [> Types.FontVariant.t];

/* let normal: [> | Types.FontStyle.t]*/
let italic: [> Types.FontStyle.t];
let oblique: [> Types.FontStyle.t];

let hidden: [> | `hidden];
let visible: [> | `visible];
let scroll: [> | `scroll];
let auto: [> | `auto];

/********************************************************
 ************************ VALUES ************************
 ********************************************************/

type color = [
  | `rgb(int, int, int)
  | `rgba(int, int, int, float)
  | `hsl(Types.Angle.t, [ | `percent(float)], [ | `percent(float)])
  | `hsla(
      Types.Angle.t,
      [ | `percent(float)],
      [ | `percent(float)],
      [ | `num(float) | `percent(float)],
    )
  | `transparent
  | `hex(string)
  | `currentColor
];

let rgb: (int, int, int) => [> | `rgb(int, int, int)];
let rgba: (int, int, int, float) => [> | `rgba(int, int, int, float)];
let hsl:
  (Types.Angle.t, float, float) =>
  [> | `hsl(Types.Angle.t, [> | `percent(float)], [> | `percent(float)])];
let hsla:
  (Types.Angle.t, float, float, [ | `num(float) | `percent(float)]) =>
  [>
    | `hsla(
        Types.Angle.t,
        [> | `percent(float)],
        [> | `percent(float)],
        [ | `num(float) | `percent(float)],
      )
  ];
let hex: string => [> | `hex(string)];
let transparent: [> | `transparent];
let currentColor: [> | `currentColor];

module Shadow: {
  type value('a);
  type box;
  type text;

  type t('a) = [ | `shadow(value('a)) | `none];

  let box:
    (
      ~x: Types.Length.t=?,
      ~y: Types.Length.t=?,
      ~blur: Types.Length.t=?,
      ~spread: Types.Length.t=?,
      ~inset: bool=?,
      color
    ) =>
    [> t(box)];

  let text:
    (
      ~x: Types.Length.t=?,
      ~y: Types.Length.t=?,
      ~blur: Types.Length.t=?,
      color
    ) =>
    [> t(text)];

  let toString: t('a) => string;
};

type gradient = [
  | `linearGradient(Types.Angle.t, list((Types.Length.t, color)))
  | `repeatingLinearGradient(Types.Angle.t, list((Types.Length.t, color)))
  | `radialGradient(list((Types.Length.t, color)))
  | `repeatingRadialGradient(list((Types.Length.t, color)))
];

let linearGradient:
  (Types.Angle.t, list((Types.Length.t, color))) =>
  [> | `linearGradient(Types.Angle.t, list((Types.Length.t, color)))];
let repeatingLinearGradient:
  (Types.Angle.t, list((Types.Length.t, color))) =>
  [>
    | `repeatingLinearGradient(Types.Angle.t, list((Types.Length.t, color)))
  ];
let radialGradient:
  list((Types.Length.t, color)) =>
  [> | `radialGradient(list((Types.Length.t, color)))];
let repeatingRadialGradient:
  list((Types.Length.t, color)) =>
  [> | `repeatingRadialGradient(list((Types.Length.t, color)))];

type repeatValue = [ | `autoFill | `autoFit | `num(int)];
type minmax = [
  | `fr(float)
  | `minContent
  | `maxContent
  | `auto
  | Types.Length.t
];
type trackLength = [
  Types.Length.t
  | `fr(float)
  | `minContent
  | `maxContent
  | `minmax(minmax, minmax)
];
type gridLength = [ trackLength | `repeat(repeatValue, trackLength)];

let fr: float => [> | `fr(float)];
let pct: float => [> | `percent(float)];
let vw: float => [> | `vw(float)];

module Calc: {
  let (-): (Types.Length.t, Types.Length.t) => [> Types.Length.t];
  let (+): (Types.Length.t, Types.Length.t) => [> Types.Length.t];
};

let size:
  (Types.Length.t, Types.Length.t) =>
  [> | `size(Types.Length.t, Types.Length.t)];

let solid: [> | `solid];
let dotted: [> | `dotted];
let dashed: [> | `dashed];

let localUrl: string => [> | `localUrl(string)];
let url: string => [> | `url(string)];

let none: [> | `none];
let local: [> | `local];

let paddingBox: [> | `paddingBox];
let borderBox: [> | `borderBox];
let contentBox: [> | `contentBox];

let noRepeat: [> | `noRepeat];
let repeat: [> | `repeat];
let minmax: [> | `minmax];
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

let inline: [> | `inline];
let block: [> | `block];
let contents: [> | `contents];
let flexBox: [> | `flex];
let grid: [> | `grid];
let inlineBlock: [> | `inlineBlock];
let inlineFlex: [> | `inlineFlex];
let inlineGrid: [> | `inlineGrid];
let inlineTable: [> | `inlineTable];
let listItem: [> | `listItem];
let runIn: [> | `runIn];
let table: [> | `table];
let tableCaption: [> | `tableCaption];
let tableColumnGroup: [> | `tableColumnGroup];
let tableHeaderGroup: [> | `tableHeaderGroup];
let tableFooterGroup: [> | `tableFooterGroup];
let tableRowGroup: [> | `tableRowGroup];
let tableCell: [> | `tableCell];
let tableColumn: [> | `tableColumn];
let tableRow: [> | `tableRow];

let flexStart: [> | `flexStart];
let flexEnd: [> | `flexEnd];
let center: [> | `center];
let stretch: [> | `stretch];
let spaceBetween: [> | `spaceBetween];
let spaceAround: [> | `spaceAround];
let spaceEvenly: [> | `spaceEvenly];
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

let translate:
  (Types.Length.t, Types.Length.t) =>
  [> | `translate(Types.Length.t, Types.Length.t)];
let translate3d:
  (Types.Length.t, Types.Length.t, Types.Length.t) =>
  [> | `translate3d(Types.Length.t, Types.Length.t, Types.Length.t)];
let translateX: Types.Length.t => [> | `translateX(Types.Length.t)];
let translateY: Types.Length.t => [> | `translateY(Types.Length.t)];
let translateZ: Types.Length.t => [> | `translateZ(Types.Length.t)];
let scale: (float, float) => [> | `scale(float, float)];
let scale3d: (float, float, float) => [> | `scale3d(float, float, float)];
let scaleX: float => [> | `scaleX(float)];
let scaleY: float => [> | `scaleY(float)];
let scaleZ: float => [> | `scaleZ(float)];
let rotate: Types.Angle.t => [> | `rotate(Types.Angle.t)];
let rotate3d:
  (float, float, float, Types.Angle.t) =>
  [> | `rotate3d(float, float, float, Types.Angle.t)];
let rotateX: Types.Angle.t => [> | `rotateX(Types.Angle.t)];
let rotateY: Types.Angle.t => [> | `rotateY(Types.Angle.t)];
let rotateZ: Types.Angle.t => [> | `rotateZ(Types.Angle.t)];
let skew:
  (Types.Angle.t, Types.Angle.t) => [> | `skew(Types.Angle.t, Types.Angle.t)];
let skewX: Types.Angle.t => [> | `skewX(Types.Angle.t)];
let skewY: Types.Angle.t => [> | `skewY(Types.Angle.t)];

let underline: [> | `underline];
let overline: [> | `overline];
let lineThrough: [> | `lineThrough];

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
let steps:
  (int, [ | `start | `end_]) => [> | `steps(int, [ | `start | `end_])];
let cubicBesier:
  (float, float, float, float) =>
  [> | `cubicBezier(float, float, float, float)];

let round: [> | `round];
let miter: [> | `miter];
let bevel: [> | `bevel];
let butt: [> | `butt];
let square: [> | `square];

/********************************************************
 ******************** PROPERTIES ************************
 ********************************************************/

/**
 * Layout
*/

let display:
  [
    | `inline
    | `block
    | `contents
    | `flex
    | `grid
    | `inlineBlock
    | `inlineFlex
    | `inlineGrid
    | `inlineTable
    | `listItem
    | `runIn
    | `table
    | `tableCaption
    | `tableColumnGroup
    | `tableHeaderGroup
    | `tableFooterGroup
    | `tableRowGroup
    | `tableCell
    | `tableColumn
    | `tableRow
    | `none
    | Types.Cascading.t
  ] =>
  rule;

let flex: [ | `auto | `initial | `none | `num(float)] => rule;
let flex3:
  (
    ~grow: float,
    ~shrink: float,
    ~basis: [ Types.Length.t | Types.FlexBasis.t]
  ) =>
  rule;
let flexGrow: float => rule;
let flexShrink: float => rule;
let flexBasis: [ Types.Length.t | Types.FlexBasis.t] => rule;

let flexDirection: [ | `row | `column | `rowReverse | `columnReverse] => rule;
let flexWrap: [ | `wrap | `nowrap | `wrapReverse] => rule;
let order: int => rule;

let gridTemplateColumns: list([ gridLength | `auto]) => rule;
let gridTemplateRows: list([ gridLength | `auto]) => rule;
let gridAutoColumns: [ Types.Length.t | `auto] => rule;
let gridAutoRows: [ Types.Length.t | `auto] => rule;

let width: [ Types.Length.t | `auto | `fitContent] => rule;
let height: [ Types.Length.t | `auto] => rule;
let minWidth: [ Types.Length.t | `auto] => rule;
let maxWidth: [ Types.Length.t | `none] => rule;
let minHeight: [ Types.Length.t | `auto] => rule;
let maxHeight: [ Types.Length.t | `none] => rule;

let alignContent:
  [
    | `stretch
    | `flexStart
    | `center
    | `flexEnd
    | `spaceBetween
    | `spaceAround
    | `spaceEvenly
  ] =>
  rule;
let alignItems:
  [ | `stretch | `flexStart | `center | `flexEnd | `baseline] => rule;
let alignSelf:
  [ | `stretch | `flexStart | `center | `flexEnd | `baseline | `auto] => rule;
let justifySelf: [ | `flexStart | `center | `flexEnd | `stretch] => rule;
let justifyContent:
  [
    | `flexStart
    | `center
    | `flexEnd
    | `spaceBetween
    | `spaceAround
    | `spaceEvenly
    | `stretch
  ] =>
  rule;

let boxSizing: [ | `borderBox | `contentBox | Types.Cascading.t] => rule;

let float: [ | `left | `right | `none] => rule;
let clear: [ | `left | `right | `both] => rule;

let contentRule: string => rule;

let columnCount: [ | `auto | `count(int) | Types.Cascading.t] => rule;

let objectFit:
  [ | `fill | `contain | `cover | `none | `scaleDown | cascading] => rule;

/**
 * Style
 */
let backfaceVisibility: [ | `visible | `hidden] => rule;
let visibility: [ | `visible | `hidden] => rule;

let border:
  (Types.Length.t, [ | `solid | `dashed | `dotted | `none], [ color]) => rule;
let borderWidth: Types.Length.t => rule;
let borderStyle: [ | `solid | `dashed | `dotted | `none] => rule;
let borderColor: color => rule;

let borderTop:
  (Types.Length.t, [ | `solid | `dashed | `dotted | `none], [ color]) => rule;
let borderTopWidth: Types.Length.t => rule;
let borderTopStyle: [ | `solid | `dashed | `dotted | `none] => rule;
let borderTopColor: color => rule;
let borderBottom:
  (Types.Length.t, [ | `solid | `dashed | `dotted | `none], [ color]) => rule;
let borderBottomWidth: Types.Length.t => rule;
let borderBottomStyle: [ | `solid | `dashed | `dotted | `none] => rule;
let borderBottomColor: color => rule;
let borderLeft:
  (Types.Length.t, [ | `solid | `dashed | `dotted | `none], [ color]) => rule;
let borderLeftWidth: Types.Length.t => rule;
let borderLeftStyle: [ | `solid | `dashed | `dotted | `none] => rule;
let borderLeftColor: color => rule;
let borderRight:
  (Types.Length.t, [ | `solid | `dashed | `dotted], [ color]) => rule;
let borderRightWidth: Types.Length.t => rule;
let borderRightStyle: [ | `solid | `dashed | `dotted | `none] => rule;
let borderRightColor: color => rule;

let borderRadius: Types.Length.t => rule;
let borderTopLeftRadius: Types.Length.t => rule;
let borderTopRightRadius: Types.Length.t => rule;
let borderBottomLeftRadius: Types.Length.t => rule;
let borderBottomRightRadius: Types.Length.t => rule;

let tableLayout: [ | `auto | `fixed] => rule;
let borderCollapse: [ | `separate | `collapse] => rule;
let borderSpacing: Types.Length.t => rule;

let boxShadow: [ Shadow.t(Shadow.box) | Types.Cascading.t] => rule;
let boxShadows: list([ Shadow.t(Shadow.box)]) => rule;

let background: [ color | `url(string) | gradient | `none] => rule;
let backgrounds: list([ color | `url(string) | gradient | `none]) => rule;
let backgroundColor: [ color] => rule;
let backgroundImage: [ | `url(string) | gradient | `none] => rule;
let backgroundAttachment: [ | `scroll | `fixed | `local] => rule;
let backgroundClip: [ | `borderBox | `contentBox | `paddingBox] => rule;
let backgroundOrigin: [ | `borderBox | `contentBox | `paddingBox] => rule;
let backgroundPosition: ([ Types.Length.t], [ Types.Length.t]) => rule;
let backgroundRepeat: [ | `repeat | `noRepeat | `repeatX | `repeatY] => rule;
let backgroundSize:
  [ | `size(Types.Length.t, Types.Length.t) | `auto | `cover | `contain] =>
  rule;

let cursor:
  [
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
let listStyle:
  (listStyleType, [ | `inside | `outside], [ | `none | `url(string)]) => rule;
let listStyleType: listStyleType => rule;
let listStylePosition: [ | `inside | `outside] => rule;
let listStyleImage: [ | `none | `url(string)] => rule;

let opacity: float => rule;

type outlineStyle = [
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
let outline: (Types.Length.t, outlineStyle, color) => rule;
let outlineStyle: outlineStyle => rule;
let outlineWidth: Types.Length.t => rule;
let outlineColor: color => rule;
let outlineOffset: Types.Length.t => rule;

let pointerEvents: [ | `auto | `none] => rule;

type filter = [
  | `blur(Types.Length.t)
  | `brightness(float)
  | `contrast(float)
  | `dropShadow(Types.Length.t, Types.Length.t, Types.Length.t, color)
  | `grayscale(float)
  | `hueRotate(Types.Angle.t)
  | `invert(float)
  | `opacity(float)
  | `saturate(float)
  | `sepia(float)
  | `url(string)
  | `none
  | Types.Cascading.t
];

let filter: list(filter) => rule;

/**
 * Text
 */

/* see https://developer.mozilla.org/en-US/docs/Web/CSS/font-weight#Common_weight_name_mapping */
type fontWeight = [
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

let thin: [> | `thin];
let extraLight: [> | `extraLight];
let light: [> | `light];
let medium: [> | `medium];
let semiBold: [> | `semiBold];
let bold: [> | `bold];
let extraBold: [> | `extraBold];
let lighter: [> | `lighter];
let bolder: [> | `bolder];

let color: color => rule;
let fontFace:
  (
    ~fontFamily: string,
    ~src: list([< | `localUrl(string) | `url(string)]),
    ~fontStyle: fontStyle=?,
    ~fontWeight: [ fontWeight | Types.Cascading.t]=?,
    unit
  ) =>
  string;
let fontWeight: [ fontWeight | Types.Cascading.t] => rule;
let letterSpacing: [ | `normal | Types.Length.t | Types.Cascading.t] => rule;
let lineHeight:
  [ | `normal | `abs(float) | Types.Length.t | Types.Cascading.t] => rule;
let textAlign:
  [ | `left | `center | `right | `justify | Types.Cascading.t] => rule;
let textDecoration:
  [ | `none | `underline | `overline | `lineThrough | Types.Cascading.t] =>
  rule;
let textDecorationColor: color => rule;
let textDecorationStyle:
  [ | `wavy | `solid | `dotted | `dashed | `double | Types.Cascading.t] => rule;
let textIndent: Types.Length.t => rule;
let textOverflow:
  [ | `clip | `ellipsis | `string(string) | Types.Cascading.t] => rule;

let textShadow: [ Shadow.t(Shadow.text) | Types.Cascading.t] => rule;
let textShadows: list([ Shadow.t(Shadow.text)]) => rule;

let textTransform:
  [ | `uppercase | `lowercase | `capitalize | `none | Types.Cascading.t] =>
  rule;
let userSelect: [ | `auto | `all | `text | `none | Types.Cascading.t] => rule;
let whiteSpace:
  [ | `normal | `nowrap | `pre | `preLine | `preWrap | Types.Cascading.t] =>
  rule;
let wordBreak: [ | `breakAll | `keepAll | `normal | Types.Cascading.t] => rule;
let wordSpacing: [ | `normal | Types.Length.t | Types.Cascading.t] => rule;
let wordWrap: [ | `normal | `breakWord | Types.Cascading.t] => rule;

/**
 * Transform
 */

type transform = [
  | `translate(Types.Length.t, Types.Length.t)
  | `translate3d(Types.Length.t, Types.Length.t, Types.Length.t)
  | `translateX(Types.Length.t)
  | `translateY(Types.Length.t)
  | `translateZ(Types.Length.t)
  | `scale(float, float)
  | `scale3d(float, float, float)
  | `scaleX(float)
  | `scaleY(float)
  | `scaleZ(float)
  | `rotate(Types.Angle.t)
  | `rotate3d(float, float, float, Types.Angle.t)
  | `rotateX(Types.Angle.t)
  | `rotateY(Types.Angle.t)
  | `rotateZ(Types.Angle.t)
  | `skew(Types.Angle.t, Types.Angle.t)
  | `skewX(Types.Angle.t)
  | `skewY(Types.Angle.t)
  | `perspective(int)
];

let transform: transform => rule;
let transforms: list(transform) => rule;
let transformOrigin: (Types.Length.t, Types.Length.t) => rule;
let transformOrigin3d:
  (Types.Length.t, Types.Length.t, Types.Length.t) => rule;
let transformStyle: [ | `preserve3d | `flat] => rule;
let perspective: [ | `none | Types.Length.t] => rule;
let perspectiveOrigin: (Types.Length.t, Types.Length.t) => rule;

/**
  * Transition
  */

module Transition: {
  type t = [ | `value(string)];

  let shorthand:
    (
      ~duration: int=?,
      ~delay: int=?,
      ~timingFunction: Types.TimingFunction.t=?,
      string
    ) =>
    [> t];

  let toString: t => string;
};

let transitionValue: Transition.t => rule;
let transitionList: list([ Transition.t]) => rule;

let transition:
  (
    ~duration: int=?,
    ~delay: int=?,
    ~timingFunction: Types.TimingFunction.t=?,
    string
  ) =>
  rule;
let transitions: list([ Transition.t]) => rule;

let transitionDelay: int => rule;
let transitionDuration: int => rule;
let transitionTimingFunction: Types.TimingFunction.t => rule;
let transitionProperty: string => rule;

/**
 * Animation
 */

type animationName;
let keyframes: list((int, list(rule))) => animationName;

type animationDirection = [
  | `normal
  | `reverse
  | `alternate
  | `alternateReverse
];

type animationFillMode = [ | `none | `forwards | `backwards | `both];
type animationIterationCount = [ | `infinite | `count(int)];
type animationPlayState = [ | `paused | `running];

module Animation: {
  type t = [ | `value(string)];

  let shorthand:
    (
      ~duration: int=?,
      ~delay: int=?,
      ~direction: animationDirection=?,
      ~timingFunction: Types.TimingFunction.t=?,
      ~fillMode: animationFillMode=?,
      ~playState: animationPlayState=?,
      ~iterationCount: animationIterationCount=?,
      animationName
    ) =>
    [> t];

  let toString: t => string;
};

let animationValue: Animation.t => rule;
let animation:
  (
    ~duration: int=?,
    ~delay: int=?,
    ~direction: animationDirection=?,
    ~timingFunction: Types.TimingFunction.t=?,
    ~fillMode: animationFillMode=?,
    ~playState: animationPlayState=?,
    ~iterationCount: animationIterationCount=?,
    animationName
  ) =>
  rule;
let animations: list([ Animation.t]) => rule;

let animationDelay: int => rule;
let animationDirection: animationDirection => rule;
let animationDuration: int => rule;
let animationFillMode: animationFillMode => rule;
let animationIterationCount: [ | `infinite | `count(int)] => rule;
let animationName: animationName => rule;
let animationPlayState: [ | `paused | `running] => rule;
let animationTimingFunction: Types.TimingFunction.t => rule;

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
  let strokeWidth: Types.Length.t => rule;
  let strokeOpacity: float => rule;
  let stopColor: color => rule;
  let stopOpacity: float => rule;
};

/* ****
 Colors
 ****** */

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
