module Types = Css_Types;

type rule;

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
      Types.Color.t
    ) =>
    [> t(box)];

  let text:
    (
      ~x: Types.Length.t=?,
      ~y: Types.Length.t=?,
      ~blur: Types.Length.t=?,
      Types.Color.t
    ) =>
    [> t(text)];

  let toString: t('a) => string;
};

/* ********
 Properties
 ********** */

/** If nothing works, use this - unsafe - escape hatch */
let unsafe: (string, string) => rule;

let animationDelay: int => rule;

let animationDirection: Types.AnimationDirection.t => rule;

let animationDuration: int => rule;

let animationFillMode: Types.AnimationFillMode.t => rule;

let animationIterationCount: Types.AnimationIterationCount.t => rule;

let animationPlayState: Types.AnimationPlayState.t => rule;

let animationTimingFunction: Types.TimingFunction.t => rule;

let backgroundColor: Types.Color.t => rule;

let backgroundPosition: ([ Types.Length.t], [ Types.Length.t]) => rule;

let borderBottom:
  (
    Types.Length.t,
    [ Types.BorderStyle.t | Types.Cascading.t],
    Types.Color.t
  ) =>
  rule;

let borderBottomColor: Types.Color.t => rule;

let borderBottomLeftRadius: Types.Length.t => rule;

let borderBottomRightRadius: Types.Length.t => rule;

let borderBottomStyle: [ Types.BorderStyle.t | Types.Cascading.t] => rule;

let borderBottomWidth: Types.Length.t => rule;

let borderColor: Types.Color.t => rule;

let borderLeft:
  (
    Types.Length.t,
    [ Types.BorderStyle.t | Types.Cascading.t],
    Types.Color.t
  ) =>
  rule;

let borderLeftColor: Types.Color.t => rule;

let borderLeftStyle: [ Types.BorderStyle.t | Types.Cascading.t] => rule;

let borderLeftWidth: Types.Length.t => rule;

let borderRight:
  (
    Types.Length.t,
    [ Types.BorderStyle.t | Types.Cascading.t],
    Types.Color.t
  ) =>
  rule;

let borderRightColor: Types.Color.t => rule;

let borderRightStyle: [ Types.BorderStyle.t | Types.Cascading.t] => rule;

let borderRightWidth: Types.Length.t => rule;

let borderRadius: Types.Length.t => rule;

let borderSpacing: Types.Length.t => rule;

let borderTopColor: Types.Color.t => rule;

let borderTopLeftRadius: Types.Length.t => rule;

let borderTopRightRadius: Types.Length.t => rule;

let borderTopStyle: [ Types.BorderStyle.t | Types.Cascading.t] => rule;

let borderTopWidth: Types.Length.t => rule;

let borderWidth: Types.Length.t => rule;

let bottom: [ Types.Length.t | Types.Cascading.t] => rule;

let boxShadow: [ Shadow.t(Shadow.box) | Types.Cascading.t] => rule;

let boxShadows: list([ Shadow.t(Shadow.box)]) => rule;

let color: Types.Color.t => rule;

let contentRule: string => rule;

let cursor: Types.Cursor.t => rule;

/**
 The direction CSS property sets the direction of text, table columns, and horizontal overflow.
 Use rtl for languages written from right to left (like Hebrew or Arabic),
 and ltr for those written from left to right (like English and most other languages).
 */
let direction: [ Types.Direction.t | Types.Cascading.t] => rule;

/**
 The display CSS property sets whether an element is treated as a block or inline element
 and the layout used for its children, such as grid or flex.
 */
let display:
  [
    Types.DisplayOutside.t
    | Types.DisplayInside.t
    | Types.DisplayListItem.t
    | Types.DisplayInternal.t
    | Types.DisplayBox.t
    | Types.DisplayLegacy.t
    | Types.Cascading.t
  ] =>
  rule;

let flexGrow: float => rule;

let flexShrink: float => rule;

let fontFamily: string => rule;

let fontSize: [ Types.Length.t | Types.Cascading.t] => rule;

let fontStyle: [ Types.FontStyle.t | Types.Cascading.t] => rule;

/**
 The font-variant CSS property is a shorthand for the longhand properties font-variant-caps, font-variant-numeric,
 font-variant-alternates, font-variant-ligatures, and font-variant-east-asian.
 You can also set the CSS Level 2 (Revision 1) values of font-variant, (that is, normal or small-caps),
 by using the font shorthand
 */
let fontVariant: [ Types.FontVariant.t | Types.Cascading.t] => rule;

let fontWeight: [ Types.FontWeight.t | Types.Cascading.t] => rule;

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

/**
 The letter-spacing CSS property sets the spacing behavior between text characters
 */
let letterSpacing:
  [ Types.LetterSpacing.t | Types.Length.t | Types.Cascading.t] => rule;

/**
 The line-height CSS property sets the height of a line box. It's commonly used to set the distance between lines of text.
 On block-level elements, it specifies the minimum height of line boxes within the element.
 On non-replaced inline elements, it specifies the height that is used to calculate line box height.
 */
let lineHeight:
  [ Types.LineHeight.t | Types.Length.t | Types.Cascading.t] => rule;

let listStyleType: Types.ListStyleType.t => rule;

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

let opacity: float => rule;

let order: int => rule;

let outline: (Types.Length.t, Types.OutlineStyle.t, Types.Color.t) => rule;

let outlineColor: Types.Color.t => rule;

let outlineOffset: Types.Length.t => rule;

let outlineStyle: Types.OutlineStyle.t => rule;

let outlineWidth: Types.Length.t => rule;

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

let perspectiveOrigin: (Types.Length.t, Types.Length.t) => rule;

/**
 The pointer-events CSS property sets under what circumstances (if any) a particular graphic element can become the target of pointer events.
 */
let pointerEvents: [ Types.PointerEvents.t | Types.Cascading.t] => rule;

/**
 The position CSS property sets how an element is positioned in a document.
 The top, right, bottom, and left properties determine the final location of positioned elements.
 */
let position: [ Types.Position.t | Types.Cascading.t] => rule;

/**
 The resize CSS property sets whether an element is resizable, and if so,
 in which directions.
 */
let resize: [ Types.Resize.t | Types.Cascading.t] => rule;

let right: [ Types.Length.t | Types.Cascading.t] => rule;

let textDecorationColor: Types.Color.t => rule;

let textIndent: Types.Length.t => rule;

let top: [ Types.Length.t | Types.Cascading.t] => rule;

let transform: Types.Transform.t => rule;

let transforms: list(Types.Transform.t) => rule;

let transformOrigin: (Types.Length.t, Types.Length.t) => rule;

let transitionDelay: int => rule;

let transitionDuration: int => rule;

let transitionProperty: string => rule;

let transitionTimingFunction: Types.TimingFunction.t => rule;

/**
 The vertical-align CSS property sets vertical alignment of an inline or table-cell box.
 */
let verticalAlign:
  [ Types.VerticalAlign.t | Types.Length.t | Types.Cascading.t] => rule;

/**
 The word-spacing CSS property sets the length of space between words and between tags
 */
let wordSpacing:
  [
    Types.WordSpacing.t
    | Types.Length.t
    | Types.Percentage.t
    | Types.Cascading.t
  ] =>
  rule;

/**
 The z-index CSS property sets the z-order of a positioned element and its descendants or flex items.
 Overlapping elements with a larger z-index cover those with a smaller one
 */
let zIndex: int => rule;

/* *******
 selectors
 ********* */

let selector: (string, list(rule)) => rule;
let media: (string, list(rule)) => rule;

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

/* *************************************
 Type aliases for backward compatibility
 *************************************** */

type angle = Types.Angle.t;
type animationDirection = Types.AnimationDirection.t;
type animationFillMode = Types.AnimationFillMode.t;
type animationIterationCount = Types.AnimationIterationCount.t;
type animationPlayState = Types.AnimationPlayState.t;
type cascading = Types.Cascading.t;
type color = Types.Color.t;
type fontStyle = Types.FontStyle.t;
type fontWeight = Types.FontWeight.t;
type length = Types.Length.t;
type listStyleType = Types.ListStyleType.t;
type repeatValue = Types.RepeatValue.t;
type outlineStyle = Types.OutlineStyle.t;
type transform = Types.Transform.t;

/* **************************************************
 Constructor aliases, for ease of use.
 Refer to the equivalent function in the type module.
 **************************************************** */

let initial: [> Types.Cascading.t];
let inherit_: [> Types.Cascading.t];
let unset: [> Types.Cascading.t];

let pct: float => [> Types.Percentage.t];

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

let rgb: (int, int, int) => [> Types.Color.t];
let rgba: (int, int, int, float) => [> Types.Color.t];
let hsl: (Types.Angle.t, float, float) => [> Types.Color.t];
let hsla:
  (Types.Angle.t, float, float, [ | `num(float) | `percent(float)]) =>
  [> Types.Color.t];
let hex: string => [> Types.Color.t];
let transparent: [> Types.Color.t];
let currentColor: [> Types.Color.t];

/********************************************************
 ************************ VALUES ************************
 ********************************************************/

type gradient = [
  | `linearGradient(Types.Angle.t, list((Types.Length.t, Types.Color.t)))
  | `repeatingLinearGradient(
      Types.Angle.t,
      list((Types.Length.t, Types.Color.t)),
    )
  | `radialGradient(list((Types.Length.t, Types.Color.t)))
  | `repeatingRadialGradient(list((Types.Length.t, Types.Color.t)))
];

let linearGradient:
  (Types.Angle.t, list((Types.Length.t, Types.Color.t))) =>
  [>
    | `linearGradient(Types.Angle.t, list((Types.Length.t, Types.Color.t)))
  ];
let repeatingLinearGradient:
  (Types.Angle.t, list((Types.Length.t, Types.Color.t))) =>
  [>
    | `repeatingLinearGradient(
        Types.Angle.t,
        list((Types.Length.t, Types.Color.t)),
      )
  ];
let radialGradient:
  list((Types.Length.t, Types.Color.t)) =>
  [> | `radialGradient(list((Types.Length.t, Types.Color.t)))];
let repeatingRadialGradient:
  list((Types.Length.t, Types.Color.t)) =>
  [> | `repeatingRadialGradient(list((Types.Length.t, Types.Color.t)))];

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
type gridLength = [ trackLength | `repeat(Types.RepeatValue.t, trackLength)];

let fr: float => [> | `fr(float)];
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

let flex: [ | `auto | `initial | `none | `num(float)] => rule;
let flex3:
  (
    ~grow: float,
    ~shrink: float,
    ~basis: [ Types.Length.t | Types.FlexBasis.t]
  ) =>
  rule;
let flexBasis: [ Types.FlexBasis.t | Types.Length.t] => rule;

let flexDirection: [ | `row | `column | `rowReverse | `columnReverse] => rule;
let flexWrap: [ | `wrap | `nowrap | `wrapReverse] => rule;

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

let columnCount: [ | `auto | `count(int) | Types.Cascading.t] => rule;

let objectFit:
  [ | `fill | `contain | `cover | `none | `scaleDown | Types.Cascading.t] =>
  rule;

/**
 * Style
 */
let backfaceVisibility: [ | `visible | `hidden] => rule;
let visibility: [ | `visible | `hidden] => rule;

let border:
  (
    Types.Length.t,
    [ Types.BorderStyle.t | Types.Cascading.t],
    Types.Color.t
  ) =>
  rule;
let borderStyle: [ Types.BorderStyle.t | Types.Cascading.t] => rule;

let borderTop:
  (
    Types.Length.t,
    [ Types.BorderStyle.t | Types.Cascading.t],
    Types.Color.t
  ) =>
  rule;

let tableLayout: [ | `auto | `fixed] => rule;
let borderCollapse: [ | `separate | `collapse] => rule;

let background: [ Types.Color.t | `url(string) | gradient | `none] => rule;
let backgrounds:
  list([ Types.Color.t | `url(string) | gradient | `none]) => rule;
let backgroundImage: [ | `url(string) | gradient | `none] => rule;
let backgroundAttachment: [ | `scroll | `fixed | `local] => rule;
let backgroundClip: [ | `borderBox | `contentBox | `paddingBox] => rule;
let backgroundOrigin: [ | `borderBox | `contentBox | `paddingBox] => rule;
let backgroundRepeat: [ | `repeat | `noRepeat | `repeatX | `repeatY] => rule;
let backgroundSize:
  [ | `size(Types.Length.t, Types.Length.t) | `auto | `cover | `contain] =>
  rule;

let clipPath: [ | `url(string)] => rule;

let listStyle:
  (
    Types.ListStyleType.t,
    [ | `inside | `outside],
    [ | `none | `url(string)]
  ) =>
  rule;
let listStylePosition: [ | `inside | `outside] => rule;
let listStyleImage: [ | `none | `url(string)] => rule;

type filter = [
  | `blur(Types.Length.t)
  | `brightness(float)
  | `contrast(float)
  | `dropShadow(Types.Length.t, Types.Length.t, Types.Length.t, Types.Color.t)
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

let thin: [> | `thin];
let extraLight: [> | `extraLight];
let light: [> | `light];
let medium: [> | `medium];
let semiBold: [> | `semiBold];
let bold: [> | `bold];
let extraBold: [> | `extraBold];
let lighter: [> | `lighter];
let bolder: [> | `bolder];

let fontFace:
  (
    ~fontFamily: string,
    ~src: list([< | `localUrl(string) | `url(string)]),
    ~fontStyle: fontStyle=?,
    ~fontWeight: [ fontWeight | Types.Cascading.t]=?,
    unit
  ) =>
  string;
let textAlign:
  [ | `left | `center | `right | `justify | Types.Cascading.t] => rule;
let textDecoration:
  [ | `none | `underline | `overline | `lineThrough | Types.Cascading.t] =>
  rule;
let textDecorationStyle:
  [ | `wavy | `solid | `dotted | `dashed | `double | Types.Cascading.t] => rule;
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
let wordWrap: [ | `normal | `breakWord | Types.Cascading.t] => rule;

/**
 * Transform
 */

let transformOrigin3d:
  (Types.Length.t, Types.Length.t, Types.Length.t) => rule;
let transformStyle: [ | `preserve3d | `flat] => rule;
let perspective:
  [ Types.Perspective.t | Types.Length.t | Types.Cascading.t] => rule;

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

/**
 * Animation
 */

type animationName;
let keyframes: list((int, list(rule))) => animationName;

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

let animationName: animationName => rule;

/**
 * SVG
 */

module SVG: {
  let fill: Types.Color.t => rule;
  let fillRule: [ | `nonzero | `evenodd] => rule;
  let fillOpacity: float => rule;
  let stroke: Types.Color.t => rule;
  let strokeLinecap: [ | `butt | `round | `square] => rule;
  let strokeLinejoin: [ | `miter | `round | `bevel] => rule;
  let strokeMiterlimit: float => rule;
  let strokeWidth: Types.Length.t => rule;
  let strokeOpacity: float => rule;
  let stopColor: Types.Color.t => rule;
  let stopOpacity: float => rule;
};

/* ****
 Colors
 ****** */

let aliceblue: [> Types.Color.t];
let antiquewhite: [> Types.Color.t];
let aqua: [> Types.Color.t];
let aquamarine: [> Types.Color.t];
let azure: [> Types.Color.t];
let beige: [> Types.Color.t];
let bisque: [> Types.Color.t];
let black: [> Types.Color.t];
let blanchedalmond: [> Types.Color.t];
let blue: [> Types.Color.t];
let blueviolet: [> Types.Color.t];
let brown: [> Types.Color.t];
let burlywood: [> Types.Color.t];
let cadetblue: [> Types.Color.t];
let chartreuse: [> Types.Color.t];
let chocolate: [> Types.Color.t];
let coral: [> Types.Color.t];
let cornflowerblue: [> Types.Color.t];
let cornsilk: [> Types.Color.t];
let crimson: [> Types.Color.t];
let cyan: [> Types.Color.t];
let darkblue: [> Types.Color.t];
let darkcyan: [> Types.Color.t];
let darkgoldenrod: [> Types.Color.t];
let darkgray: [> Types.Color.t];
let darkgrey: [> Types.Color.t];
let darkgreen: [> Types.Color.t];
let darkkhaki: [> Types.Color.t];
let darkmagenta: [> Types.Color.t];
let darkolivegreen: [> Types.Color.t];
let darkorange: [> Types.Color.t];
let darkorchid: [> Types.Color.t];
let darkred: [> Types.Color.t];
let darksalmon: [> Types.Color.t];
let darkseagreen: [> Types.Color.t];
let darkslateblue: [> Types.Color.t];
let darkslategray: [> Types.Color.t];
let darkslategrey: [> Types.Color.t];
let darkturquoise: [> Types.Color.t];
let darkviolet: [> Types.Color.t];
let deeppink: [> Types.Color.t];
let deepskyblue: [> Types.Color.t];
let dimgray: [> Types.Color.t];
let dimgrey: [> Types.Color.t];
let dodgerblue: [> Types.Color.t];
let firebrick: [> Types.Color.t];
let floralwhite: [> Types.Color.t];
let forestgreen: [> Types.Color.t];
let fuchsia: [> Types.Color.t];
let gainsboro: [> Types.Color.t];
let ghostwhite: [> Types.Color.t];
let gold: [> Types.Color.t];
let goldenrod: [> Types.Color.t];
let gray: [> Types.Color.t];
let grey: [> Types.Color.t];
let green: [> Types.Color.t];
let greenyellow: [> Types.Color.t];
let honeydew: [> Types.Color.t];
let hotpink: [> Types.Color.t];
let indianred: [> Types.Color.t];
let indigo: [> Types.Color.t];
let ivory: [> Types.Color.t];
let khaki: [> Types.Color.t];
let lavender: [> Types.Color.t];
let lavenderblush: [> Types.Color.t];
let lawngreen: [> Types.Color.t];
let lemonchiffon: [> Types.Color.t];
let lightblue: [> Types.Color.t];
let lightcoral: [> Types.Color.t];
let lightcyan: [> Types.Color.t];
let lightgoldenrodyellow: [> Types.Color.t];
let lightgray: [> Types.Color.t];
let lightgrey: [> Types.Color.t];
let lightgreen: [> Types.Color.t];
let lightpink: [> Types.Color.t];
let lightsalmon: [> Types.Color.t];
let lightseagreen: [> Types.Color.t];
let lightskyblue: [> Types.Color.t];
let lightslategray: [> Types.Color.t];
let lightslategrey: [> Types.Color.t];
let lightsteelblue: [> Types.Color.t];
let lightyellow: [> Types.Color.t];
let lime: [> Types.Color.t];
let limegreen: [> Types.Color.t];
let linen: [> Types.Color.t];
let magenta: [> Types.Color.t];
let maroon: [> Types.Color.t];
let mediumaquamarine: [> Types.Color.t];
let mediumblue: [> Types.Color.t];
let mediumorchid: [> Types.Color.t];
let mediumpurple: [> Types.Color.t];
let mediumseagreen: [> Types.Color.t];
let mediumslateblue: [> Types.Color.t];
let mediumspringgreen: [> Types.Color.t];
let mediumturquoise: [> Types.Color.t];
let mediumvioletred: [> Types.Color.t];
let midnightblue: [> Types.Color.t];
let mintcream: [> Types.Color.t];
let mistyrose: [> Types.Color.t];
let moccasin: [> Types.Color.t];
let navajowhite: [> Types.Color.t];
let navy: [> Types.Color.t];
let oldlace: [> Types.Color.t];
let olive: [> Types.Color.t];
let olivedrab: [> Types.Color.t];
let orange: [> Types.Color.t];
let orangered: [> Types.Color.t];
let orchid: [> Types.Color.t];
let palegoldenrod: [> Types.Color.t];
let palegreen: [> Types.Color.t];
let paleturquoise: [> Types.Color.t];
let palevioletred: [> Types.Color.t];
let papayawhip: [> Types.Color.t];
let peachpuff: [> Types.Color.t];
let peru: [> Types.Color.t];
let pink: [> Types.Color.t];
let plum: [> Types.Color.t];
let powderblue: [> Types.Color.t];
let purple: [> Types.Color.t];
let rebeccapurple: [> Types.Color.t];
let red: [> Types.Color.t];
let rosybrown: [> Types.Color.t];
let royalblue: [> Types.Color.t];
let saddlebrown: [> Types.Color.t];
let salmon: [> Types.Color.t];
let sandybrown: [> Types.Color.t];
let seagreen: [> Types.Color.t];
let seashell: [> Types.Color.t];
let sienna: [> Types.Color.t];
let silver: [> Types.Color.t];
let skyblue: [> Types.Color.t];
let slateblue: [> Types.Color.t];
let slategray: [> Types.Color.t];
let slategrey: [> Types.Color.t];
let snow: [> Types.Color.t];
let springgreen: [> Types.Color.t];
let steelblue: [> Types.Color.t];
let tan: [> Types.Color.t];
let teal: [> Types.Color.t];
let thistle: [> Types.Color.t];
let tomato: [> Types.Color.t];
let turquoise: [> Types.Color.t];
let violet: [> Types.Color.t];
let wheat: [> Types.Color.t];
let white: [> Types.Color.t];
let whitesmoke: [> Types.Color.t];
let yellow: [> Types.Color.t];
let yellowgreen: [> Types.Color.t];
