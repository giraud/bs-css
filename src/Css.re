include Css_Colors;
module Types = Css_Types;

type rule =
  | Selector(string, list(rule))
  | Declaration(string, string);

module Emotion = {
  type stylename = string;
  type cache;
  [@bs.module "emotion"] external _make: Js.Json.t => stylename = "css";
  [@bs.module "emotion"] external cache: cache = "cache";
  [@bs.module "emotion"]
  external injectGlobal: Js.Json.t => unit = "injectGlobal";
  [@bs.module "emotion"]
  external rawInjectGlobal: string => unit = "injectGlobal";
  [@bs.module "emotion"]
  external makeKeyFrames: Js.Dict.t(Js.Json.t) => string = "keyframes";
  [@bs.module "emotion"] external cx: array(stylename) => stylename = "cx";
  let mergeStyles: list(stylename) => stylename =
    stylenames => stylenames |> Array.of_list |> cx;

  let rec ruleToJs = rule =>
    switch (rule) {
    | Declaration(name, value) when name == "content" => (
        name,
        Js.Json.string(value == "" ? "\"\"" : value),
      )
    | Declaration(name, value) => (name, Js.Json.string(value))
    | Selector(name, ruleset) => (name, makeJson(ruleset))
    }

  and makeJson = rules =>
    List.map(ruleToJs, rules)->Js.Dict.fromList->Js.Json.object_;

  let make = rules => rules->makeJson->_make;
};

let toJson = Emotion.makeJson;
let style = Emotion.make;

let join = (strings, separator) => {
  let rec run = (strings, acc) =>
    switch (strings) {
    | [] => acc
    | [x] => acc ++ x
    | [x, ...xs] => run(xs, acc ++ x ++ separator)
    };
  run(strings, "");
};
let joinLast = (separator, strings) => {
  let rec run = (acc, strings) =>
    switch (strings) {
    | [] => acc
    | [x] => acc ++ x
    | [x, ...xs] => run(acc ++ x ++ separator, xs)
    };
  run("", strings);
};

module Converter = {
  let string_of_rgb = (r, g, b) =>
    "rgb("
    ++ Js.Int.toString(r)
    ++ ", "
    ++ Js.Int.toString(g)
    ++ ", "
    ++ Js.Int.toString(b)
    ++ ")";

  let string_of_rgba = (r, g, b, a) =>
    "rgba("
    ++ Js.Int.toString(r)
    ++ ", "
    ++ Js.Int.toString(g)
    ++ ", "
    ++ Js.Int.toString(b)
    ++ ", "
    ++ Js.Float.toString(a)
    ++ ")";

  let string_of_percent =
    fun
    | `percent(x) => Js.Float.toString(x) ++ "%";

  let string_of_hsl = (h, s, l) =>
    "hsl("
    ++ Types.Angle.toString(h)
    ++ ", "
    ++ string_of_percent(s)
    ++ ", "
    ++ string_of_percent(l)
    ++ ")";

  let string_of_alpha =
    fun
    | `num(f) => Js.Float.toString(f)
    | `percent(p) => Js.Float.toString(p) ++ "%";

  let string_of_hsla = (h, s, l, a) =>
    "hsla("
    ++ Types.Angle.toString(h)
    ++ ", "
    ++ string_of_percent(s)
    ++ ", "
    ++ string_of_percent(l)
    ++ ", "
    ++ string_of_alpha(a)
    ++ ")";

  let string_of_color =
    fun
    | `rgb(r, g, b) => string_of_rgb(r, g, b)
    | `rgba(r, g, b, a) => string_of_rgba(r, g, b, a)
    | `hsl(h, s, l) => string_of_hsl(h, s, l)
    | `hsla(h, s, l, a) => string_of_hsla(h, s, l, a)
    | `hex(s) => "#" ++ s
    | `transparent => "transparent"
    | `currentColor => "currentColor";

  let string_of_stops = stops =>
    stops
    |> List.map(((l, c)) =>
         joinLast(" ", [string_of_color(c), Types.Length.toString(l)])
       )
    |> joinLast(", ");

  let string_of_linearGradient = (angle, stops) =>
    "linear-gradient("
    ++ Types.Angle.toString(angle)
    ++ ", "
    ++ string_of_stops(stops)
    ++ ")";

  let string_of_repeatingLinearGradient = (angle, stops) =>
    "repeating-linear-gradient("
    ++ Types.Angle.toString(angle)
    ++ ", "
    ++ string_of_stops(stops)
    ++ ")";

  let string_of_time = t => Js.Int.toString(t) ++ "ms";

  let string_of_visibility =
    fun
    | `hidden => "hidden"
    | `visible => "visible";

  let string_of_background = bg =>
    switch (bg) {
    | `none => "none"
    | `url(url) => "url(" ++ url ++ ")"
    | `rgb(r, g, b) =>
      "rgb("
      ++ joinLast(
           ", ",
           [Js.Int.toString(r), Js.Int.toString(g), Js.Int.toString(b)],
         )
      ++ ")"
    | `rgba(r, g, b, a) =>
      "rgba("
      ++ joinLast(
           ", ",
           [
             Js.Int.toString(r),
             Js.Int.toString(g),
             Js.Int.toString(b),
             Js.Float.toString(a),
           ],
         )
      ++ ")"
    | `hsl(h, s, l) => string_of_hsl(h, s, l)
    | `hsla(h, s, l, a) => string_of_hsla(h, s, l, a)
    | `hex(s) => "#" ++ s
    | `transparent => "transparent"
    | `currentColor => "currentColor"
    | `linearGradient(angle, stops) =>
      "linear-gradient("
      ++ Types.Angle.toString(angle)
      ++ ", "
      ++ string_of_stops(stops)
      ++ ")"
    | `repeatingLinearGradient(angle, stops) =>
      "repeating-linear-gradient("
      ++ Types.Angle.toString(angle)
      ++ ", "
      ++ string_of_stops(stops)
      ++ ")"
    | `radialGradient(stops) =>
      "radial-gradient(" ++ string_of_stops(stops) ++ ")"
    | `repeatingRadialGradient(stops) =>
      "repeating-radial-gradient(" ++ string_of_stops(stops) ++ ")"
    };

  let string_of_flex =
    fun
    | `auto => "auto"
    | `initial => "initial"
    | `none => "none"
    | `num(n) => Js.Float.toString(n);
};
include Converter;

type cache = Emotion.cache;

let empty = [];
let cache = Emotion.cache;
let merge = Emotion.mergeStyles;
let global = (selector, rules: list(rule)) =>
  Emotion.injectGlobal(
    [(selector, Emotion.makeJson(rules))]
    ->Js.Dict.fromList
    ->Js.Json.object_,
  );

let insertRule = raw => Emotion.rawInjectGlobal(raw);

type animationName = string;

let keyframes = frames => {
  let addStop = (dict, (stop, rules)) => {
    Js.Dict.set(
      dict,
      Js.Int.toString(stop) ++ "%",
      Emotion.makeJson(rules),
    );
    dict;
  };
  Emotion.makeKeyFrames @@ List.fold_left(addStop, Js.Dict.empty(), frames);
};

let important = v =>
  switch (v) {
  | Declaration(name, value) => Declaration(name, value ++ " !important")
  | _ => v
  };

let label = label => Declaration("label", label);

/* Properties */

let bottom = x =>
  Declaration(
    "bottom",
    switch (x) {
    | #Types.Length.t as l => Types.Length.toString(l)
    | #Types.Cascading.t as c => Types.Cascading.toString(c)
    },
  );

let cursor = x => Declaration("cursor", Types.Cursor.toString(x));

let direction = x =>
  Declaration(
    "direction",
    switch (x) {
    | #Types.Direction.t as d => Types.Direction.toString(d)
    | #Types.Cascading.t as c => Types.Cascading.toString(c)
    },
  );

let fontFamily = x => Declaration("fontFamily", x);

let fontSize = x =>
  Declaration(
    "fontSize",
    switch (x) {
    | #Types.Length.t as l => Types.Length.toString(l)
    | #Types.Cascading.t as c => Types.Cascading.toString(c)
    },
  );

let fontStyle = x =>
  Declaration(
    "fontStyle",
    switch (x) {
    | #Types.FontStyle.t as f => Types.FontStyle.toString(f)
    | #Types.Cascading.t as c => Types.Cascading.toString(c)
    },
  );

let fontVariant = x =>
  Declaration(
    "fontVariant",
    switch (x) {
    | #Types.FontVariant.t as f => Types.FontVariant.toString(f)
    | #Types.Cascading.t as c => Types.Cascading.toString(c)
    },
  );

let gridAutoFlow = x =>
  Declaration(
    "gridAutoFlow",
    switch (x) {
    | #Types.GridAutoFlow.t as f => Types.GridAutoFlow.toString(f)
    | #Types.Cascading.t as c => Types.Cascading.toString(c)
    },
  );

let gridColumn = (start, end') =>
  Declaration(
    "gridColumn",
    Js.Int.toString(start) ++ " / " ++ Js.Int.toString(end'),
  );

let gridColumnGap = n =>
  Declaration("gridColumnGap", Types.Length.toString(n));

let gridColumnStart = n =>
  Declaration("gridColumnStart", Js.Int.toString(n));

let gridColumnEnd = n => Declaration("gridColumnEnd", Js.Int.toString(n));

let gridRow = (start, end') =>
  Declaration(
    "gridRow",
    Js.Int.toString(start) ++ " / " ++ Js.Int.toString(end'),
  );

let gridGap = n => Declaration("gridGap", Types.Length.toString(n));

let gridRowGap = n => Declaration("gridRowGap", Types.Length.toString(n));

let gridRowEnd = n => Declaration("gridRowEnd", Js.Int.toString(n));

let gridRowStart = n => Declaration("gridRowStart", Js.Int.toString(n));

let left = x =>
  Declaration(
    "left",
    switch (x) {
    | #Types.Length.t as l => Types.Length.toString(l)
    | #Types.Cascading.t as c => Types.Cascading.toString(c)
    },
  );

let marginToString = x =>
  switch (x) {
  | #Types.Length.t as l => Types.Length.toString(l)
  | #Types.Margin.t as m => Types.Margin.toString(m)
  };

let margin = x => Declaration("margin", marginToString(x));
let margin2 = (~v, ~h) =>
  Declaration("margin", marginToString(v) ++ " " ++ marginToString(h));
let margin3 = (~top, ~h, ~bottom) =>
  Declaration(
    "margin",
    marginToString(top)
    ++ " "
    ++ marginToString(h)
    ++ " "
    ++ marginToString(bottom),
  );
let margin4 = (~top, ~right, ~bottom, ~left) =>
  Declaration(
    "margin",
    marginToString(top)
    ++ " "
    ++ marginToString(right)
    ++ " "
    ++ marginToString(bottom)
    ++ " "
    ++ marginToString(left),
  );
let marginLeft = x => Declaration("marginLeft", marginToString(x));
let marginRight = x => Declaration("marginRight", marginToString(x));
let marginTop = x => Declaration("marginTop", marginToString(x));
let marginBottom = x => Declaration("marginBottom", marginToString(x));

let overflow = x => Declaration("overflow", Types.Overflow.toString(x));
let overflowX = x => Declaration("overflowX", Types.Overflow.toString(x));
let overflowY = x => Declaration("overflowY", Types.Overflow.toString(x));

let padding = x => Declaration("padding", Types.Length.toString(x));
let padding2 = (~v, ~h) =>
  Declaration(
    "padding",
    Types.Length.toString(v) ++ " " ++ Types.Length.toString(h),
  );
let padding3 = (~top, ~h, ~bottom) =>
  Declaration(
    "padding",
    Types.Length.toString(top)
    ++ " "
    ++ Types.Length.toString(h)
    ++ " "
    ++ Types.Length.toString(bottom),
  );
let padding4 = (~top, ~right, ~bottom, ~left) =>
  Declaration(
    "padding",
    Types.Length.toString(top)
    ++ " "
    ++ Types.Length.toString(right)
    ++ " "
    ++ Types.Length.toString(bottom)
    ++ " "
    ++ Types.Length.toString(left),
  );

let paddingBottom = x =>
  Declaration("paddingBottom", Types.Length.toString(x));

let paddingLeft = x => Declaration("paddingLeft", Types.Length.toString(x));

let paddingRight = x =>
  Declaration("paddingRight", Types.Length.toString(x));

let paddingTop = x => Declaration("paddingTop", Types.Length.toString(x));

let position = x =>
  Declaration(
    "position",
    switch (x) {
    | #Types.Position.t as p => Types.Position.toString(p)
    | #Types.Cascading.t as c => Types.Cascading.toString(c)
    },
  );

let resize = x =>
  Declaration(
    "resize",
    switch (x) {
    | #Types.Resize.t as r => Types.Resize.toString(r)
    | #Types.Cascading.t as c => Types.Cascading.toString(c)
    },
  );

let right = x =>
  Declaration(
    "right",
    switch (x) {
    | #Types.Length.t as l => Types.Length.toString(l)
    | #Types.Cascading.t as c => Types.Cascading.toString(c)
    },
  );

let top = x =>
  Declaration(
    "top",
    switch (x) {
    | #Types.Length.t as l => Types.Length.toString(l)
    | #Types.Cascading.t as c => Types.Cascading.toString(c)
    },
  );

let unsafe = (property, value) => Declaration(property, value);

let verticalAlign = x =>
  Declaration(
    "verticalAlign",
    switch (x) {
    | #Types.VerticalAlign.t as v => Types.VerticalAlign.toString(v)
    | #Types.Length.t as l => Types.Length.toString(l)
    | #Types.Cascading.t as c => Types.Cascading.toString(c)
    },
  );

let zIndex = x => Declaration("zIndex", Js.Int.toString(x));

/* Type aliasing */

type cascading = Types.Cascading.t;
type length = Types.Length.t;
type angle = Types.Angle.t;
type fontStyle = Types.FontStyle.t;
type repeatValue = Types.RepeatValue.t;
type listStyleType = Types.ListStyleType.t;
type outlineStyle = Types.OutlineStyle.t;
type fontWeight = Types.FontWeight.t;
type transform = Types.Transform.t;
type animationDirection = Types.AnimationDirection.t;
type animationFillMode = Types.AnimationFillMode.t;
type animationIterationCount = Types.AnimationIterationCount.t;
type animationPlayState = Types.AnimationPlayState.t;

/* Constructor aliases */

let initial = Types.Cascading.initial;
let inherit_ = Types.Cascading.inherit_;
let unset = Types.Cascading.unset;

let ch = Types.Length.ch;
let cm = Types.Length.cm;
let em = Types.Length.em;
let ex = Types.Length.ex;
let mm = Types.Length.mm;
let pt = Types.Length.pt;
let px = Types.Length.px;
let pxFloat = Types.Length.pxFloat;
let rem = Types.Length.rem;
let vh = Types.Length.vh;
let vmin = Types.Length.vmin;
let vmax = Types.Length.vmax;
let zero = Types.Length.zero;

let deg = Types.Angle.deg;
let rad = Types.Angle.rad;
let grad = Types.Angle.grad;
let turn = Types.Angle.turn;

let ltr = Types.Direction.ltr;
let rtl = Types.Direction.rtl;

let absolute = Types.Position.absolute;
let relative = Types.Position.relative;
let static = Types.Position.static;
let fixed = `fixed;
let sticky = Types.Position.sticky;

//let none = Types.Resize.none;
//let both = Types.Resize.both;
let horizontal = Types.Resize.horizontal;
let vertical = Types.Resize.vertical;
//let block = Types.Resize.block;
//let inline = Types.Resize.inline;

let smallCaps = Types.FontVariant.smallCaps;

//let normal = `normal;
let italic = Types.FontStyle.italic;
let oblique = Types.FontStyle.oblique;

let hidden = `hidden;
let visible = `visible;
let scroll = `scroll;
let auto = `auto;

/********************************************************
 ************************ VALUES ************************
 ********************************************************/

let pct = x => `percent(x);

type color = [
  | `rgb(int, int, int)
  | `rgba(int, int, int, float)
  | `hsl(angle, [ | `percent(float)], [ | `percent(float)])
  | `hsla(
      angle,
      [ | `percent(float)],
      [ | `percent(float)],
      [ | `num(float) | `percent(float)],
    )
  | `hex(string)
  | `transparent
  | `currentColor
];

let rgb = (r, g, b) => `rgb((r, g, b));
let rgba = (r, g, b, a) => `rgba((r, g, b, a));
let hsl = (h, s, l) => `hsl((h, pct(s), pct(l)));
let hsla = (h, s, l, a) => `hsla((h, pct(s), pct(l), a));
let hex = x => `hex(x);

let currentColor = `currentColor;

type gradient = [
  | `linearGradient(angle, list((length, color)))
  | `repeatingLinearGradient(angle, list((length, color)))
  | `radialGradient(list((length, color)))
  | `repeatingRadialGradient(list((length, color)))
];

let linearGradient = (angle, stops) => `linearGradient((angle, stops));

let repeatingLinearGradient = (angle, stops) =>
  `repeatingLinearGradient((angle, stops));

let radialGradient = stops => `radialGradient(stops);

let repeatingRadialGradient = stops => `repeatingRadialGradient(stops);

/**
 * Units
 */

let vw = x => `vw(x);
let fr = x => `fr(x);

module Calc = {
  let (-) = (a, b) => `calc((`sub, a, b));
  let (+) = (a, b) => `calc((`add, a, b));
};
let size = (x, y) => `size((x, y));

/**
 * Misc
 */

let all = `all;
let backwards = `backwards;
let baseline = `baseline;
let block = `block;
let borderBox = `borderBox;
let both = `both;
let center = `center;
let column = `column;
let columnReverse = `columnReverse;
let contain = `contain;
let contentBox = `contentBox;
let count = x => `count(x);
let cover = `cover;
let cubicBesier = (a, b, c, d) => `cubicBezier((a, b, c, d));
let dashed = `dashed;
let dotted = `dotted;
let ease = `ease;
let easeIn = `easeIn;
let easeInOut = `easeInOut;
let easeOut = `easeOut;
let flexBox = `flex;
let grid = `grid;
let inlineGrid = `inlineGrid;
let flexEnd = `flexEnd;
let flexStart = `flexStart;
let forwards = `forwards;
let infinite = `infinite;

let inline = `inline;
let block = `block;
let contents = `contents;
let flexBox = `flex;
let grid = `grid;
let inlineBlock = `inlineBlock;
let inlineFlex = `inlineFlex;
let inlineGrid = `inlineGrid;
let inlineTable = `inlineTable;
let listItem = `listItem;
let runIn = `runIn;
let table = `table;
let tableCaption = `tableCaption;
let tableColumnGroup = `tableColumnGroup;
let tableHeaderGroup = `tableHeaderGroup;
let tableFooterGroup = `tableFooterGroup;
let tableRowGroup = `tableRowGroup;
let tableCell = `tableCell;
let tableColumn = `tableColumn;
let tableRow = `tableRow;

let linear = `linear;
let local = `local;
let localUrl = x => `localUrl(x);
let none = `none;
let noRepeat = `noRepeat;
let nowrap = `nowrap;
let paddingBox = `paddingBox;
let paused = `paused;
let repeat = `repeat;
let minmax = `minmax;
let repeatX = `repeatX;
let repeatY = `repeatY;
let rotate = a => `rotate(a);
let rotate3d = (x, y, z, a) => `rotate3d((x, y, z, a));
let rotateX = a => `rotateX(a);
let rotateY = a => `rotateY(a);
let rotateZ = a => `rotateZ(a);
let row = `row;
let rowReverse = `rowReverse;
let running = `running;
let scale = (x, y) => `scale((x, y));
let scale3d = (x, y, z) => `scale3d((x, y, z));
let scaleX = x => `scaleX(x);
let scaleY = x => `scaleY(x);
let scaleZ = x => `scaleZ(x);
let skew = (x, y) => `skew((x, y));
let skewX = a => `skewX(a);
let skewY = a => `skewY(a);
let solid = `solid;
let spaceAround = `spaceAround;
let spaceBetween = `spaceBetween;
let spaceEvenly = `spaceEvenly;
let stepEnd = `stepEnd;
let steps = (i, dir) => `steps((i, dir));
let stepStart = `stepStart;
let stretch = `stretch;
let text = `text;
let translate = (x, y) => `translate((x, y));
let translate3d = (x, y, z) => `translate3d((x, y, z));
let translateX = x => `translateX(x);
let translateY = y => `translateY(y);
let translateZ = z => `translateZ(z);
let url = x => `url(x);
let wrap = `wrap;
let wrapReverse = `wrapReverse;

let inside = `inside;
let outside = `outside;

let underline = `underline;
let overline = `overline;
let lineThrough = `lineThrough;
let clip = `clip;
let ellipsis = `ellipsis;

let wavy = `wavy;
let double = `double;

let uppercase = `uppercase;
let lowercase = `lowercase;
let capitalize = `capitalize;

let sub = `sub;
let super = `super;
let textTop = `textTop;
let textBottom = `textBottom;
let middle = `middle;

let normal = `normal;

let breakAll = `breakAll;
let keepAll = `keepAll;
let breakWord = `breakWord;

let reverse = `reverse;
let alternate = `alternate;
let alternateReverse = `alternateReverse;

let fill = `fill;
let content = `content;
let maxContent = `maxContent;
let minContent = `minContent;
let fitContent = `fitContent;

let round = `round;
let miter = `miter;
let bevel = `bevel;
let butt = `butt;
let square = `square;

/********************************************************
 ******************** PROPERTIES ************************
 ********************************************************/

/**
 * Layout
 */

let display = x =>
  Declaration(
    "display",
    switch (x) {
    | `inline => "inline"
    | `block => "block"
    | `contents => "contents"
    | `flex => "flex"
    | `grid => "grid"
    | `inlineBlock => "inline-block"
    | `inlineFlex => "inline-flex"
    | `inlineGrid => "inline-grid"
    | `inlineTable => "inline-table"
    | `listItem => "list-item"
    | `runIn => "run-in"
    | `table => "table"
    | `tableCaption => "table-caption"
    | `tableColumnGroup => "table-column-group"
    | `tableHeaderGroup => "table-header-group"
    | `tableFooterGroup => "table-footer-group"
    | `tableRowGroup => "table-row-group"
    | `tableCell => "table-cell"
    | `tableColumn => "table-column"
    | `tableRow => "table-row"
    | `none => "none"
    | `initial => "initial"
    | `inherit_ => "inherit"
    | `unset => "unset"
    },
  );

let flex = x => Declaration("flex", string_of_flex(x));
let flex3 = (~grow, ~shrink, ~basis) =>
  Declaration(
    "flex",
    Js.Float.toString(grow)
    ++ " "
    ++ Js.Float.toString(shrink)
    ++ " "
    ++ (
      switch (basis) {
      | #Types.FlexBasis.t as b => Types.FlexBasis.toString(b)
      | #Types.Length.t as l => Types.Length.toString(l)
      }
    ),
  );
let flexGrow = x => Declaration("flexGrow", Js.Float.toString(x));
let flexShrink = x => Declaration("flexShrink", Js.Float.toString(x));
let flexBasis = x =>
  Declaration(
    "flexBasis",
    switch (x) {
    | #Types.FlexBasis.t as b => Types.FlexBasis.toString(b)
    | #Types.Length.t as l => Types.Length.toString(l)
    },
  );

let flexDirection = x =>
  Declaration(
    "flexDirection",
    switch (x) {
    | `row => "row"
    | `column => "column"
    | `rowReverse => "row-reverse"
    | `columnReverse => "column-reverse"
    },
  );

let flexWrap = x =>
  Declaration(
    "flexWrap",
    switch (x) {
    | `nowrap => "nowrap"
    | `wrap => "wrap"
    | `wrapReverse => "wrap-reverse"
    },
  );

let order = x => Declaration("order", Js.Int.toString(x));

let string_of_minmax =
  fun
  | `auto => "auto"
  | `calc(`add, a, b) =>
    "calc("
    ++ Types.Length.toString(a)
    ++ " + "
    ++ Types.Length.toString(b)
    ++ ")"
  | `calc(`sub, a, b) =>
    "calc("
    ++ Types.Length.toString(a)
    ++ " - "
    ++ Types.Length.toString(b)
    ++ ")"
  | `ch(x) => Js.Float.toString(x) ++ "ch"
  | `cm(x) => Js.Float.toString(x) ++ "cm"
  | `em(x) => Js.Float.toString(x) ++ "em"
  | `ex(x) => Js.Float.toString(x) ++ "ex"
  | `mm(x) => Js.Float.toString(x) ++ "mm"
  | `percent(x) => Js.Float.toString(x) ++ "%"
  | `pt(x) => Js.Int.toString(x) ++ "pt"
  | `px(x) => Js.Int.toString(x) ++ "px"
  | `pxFloat(x) => Js.Float.toString(x) ++ "px"
  | `rem(x) => Js.Float.toString(x) ++ "rem"
  | `vh(x) => Js.Float.toString(x) ++ "vh"
  | `vmax(x) => Js.Float.toString(x) ++ "vmax"
  | `vmin(x) => Js.Float.toString(x) ++ "vmin"
  | `vw(x) => Js.Float.toString(x) ++ "vw"
  | `fr(x) => Js.Float.toString(x) ++ "fr"
  | `zero => "0"
  | `minContent => "min-content"
  | `maxContent => "max-content";

let string_of_dimension =
  fun
  | `auto => "auto"
  | `none => "none"
  | `calc(`add, a, b) =>
    "calc("
    ++ Types.Length.toString(a)
    ++ " + "
    ++ Types.Length.toString(b)
    ++ ")"
  | `calc(`sub, a, b) =>
    "calc("
    ++ Types.Length.toString(a)
    ++ " - "
    ++ Types.Length.toString(b)
    ++ ")"
  | `ch(x) => Js.Float.toString(x) ++ "ch"
  | `cm(x) => Js.Float.toString(x) ++ "cm"
  | `em(x) => Js.Float.toString(x) ++ "em"
  | `ex(x) => Js.Float.toString(x) ++ "ex"
  | `mm(x) => Js.Float.toString(x) ++ "mm"
  | `percent(x) => Js.Float.toString(x) ++ "%"
  | `pt(x) => Js.Int.toString(x) ++ "pt"
  | `px(x) => Js.Int.toString(x) ++ "px"
  | `pxFloat(x) => Js.Float.toString(x) ++ "px"
  | `rem(x) => Js.Float.toString(x) ++ "rem"
  | `vh(x) => Js.Float.toString(x) ++ "vh"
  | `vmax(x) => Js.Float.toString(x) ++ "vmax"
  | `vmin(x) => Js.Float.toString(x) ++ "vmin"
  | `vw(x) => Js.Float.toString(x) ++ "vw"
  | `fr(x) => Js.Float.toString(x) ++ "fr"
  | `zero => "0"
  | `fitContent => "fit-content"
  | `minContent => "min-content"
  | `maxContent => "max-content"
  | `minmax(a, b) =>
    "minmax(" ++ string_of_minmax(a) ++ "," ++ string_of_minmax(b) ++ ")";

let width = x => Declaration("width", string_of_dimension(x));
let height = x => Declaration("height", string_of_dimension(x));
let minWidth = x => Declaration("minWidth", string_of_dimension(x));
let maxWidth = x => Declaration("maxWidth", string_of_dimension(x));
let minHeight = x => Declaration("minHeight", string_of_dimension(x));
let maxHeight = x => Declaration("maxHeight", string_of_dimension(x));

type minmax = [ | `fr(float) | `minContent | `maxContent | `auto | length];

type trackLength = [
  length
  | `fr(float)
  | `minContent
  | `maxContent
  | `minmax(minmax, minmax)
];
type gridLength = [ trackLength | `repeat(repeatValue, trackLength)];

let gridLengthToJs =
  fun
  | `auto => "auto"
  | `calc(`add, a, b) =>
    "calc("
    ++ Types.Length.toString(a)
    ++ " + "
    ++ Types.Length.toString(b)
    ++ ")"
  | `calc(`sub, a, b) =>
    "calc("
    ++ Types.Length.toString(a)
    ++ " - "
    ++ Types.Length.toString(b)
    ++ ")"
  | `ch(x) => Js.Float.toString(x) ++ "ch"
  | `cm(x) => Js.Float.toString(x) ++ "cm"
  | `em(x) => Js.Float.toString(x) ++ "em"
  | `ex(x) => Js.Float.toString(x) ++ "ex"
  | `mm(x) => Js.Float.toString(x) ++ "mm"
  | `percent(x) => Js.Float.toString(x) ++ "%"
  | `pt(x) => Js.Int.toString(x) ++ "pt"
  | `px(x) => Js.Int.toString(x) ++ "px"
  | `pxFloat(x) => Js.Float.toString(x) ++ "px"
  | `rem(x) => Js.Float.toString(x) ++ "rem"
  | `vh(x) => Js.Float.toString(x) ++ "vh"
  | `vmax(x) => Js.Float.toString(x) ++ "vmax"
  | `vmin(x) => Js.Float.toString(x) ++ "vmin"
  | `vw(x) => Js.Float.toString(x) ++ "vw"
  | `fr(x) => Js.Float.toString(x) ++ "fr"
  | `zero => "0"
  | `minContent => "min-content"
  | `maxContent => "max-content"
  | `repeat(n, x) =>
    "repeat("
    ++ Types.RepeatValue.toString(n)
    ++ ", "
    ++ string_of_dimension(x)
    ++ ")"
  | `minmax(a, b) =>
    "minmax(" ++ string_of_minmax(a) ++ "," ++ string_of_minmax(b) ++ ")";

let string_of_dimensions = dimensions =>
  dimensions |> List.map(gridLengthToJs) |> String.concat(" ");

let gridTemplateColumns = dimensions =>
  Declaration("gridTemplateColumns", string_of_dimensions(dimensions));

let gridTemplateRows = dimensions =>
  Declaration("gridTemplateRows", string_of_dimensions(dimensions));

let gridAutoColumns = dimensions =>
  Declaration("gridAutoColumns", string_of_dimension(dimensions));

let gridAutoRows = dimensions =>
  Declaration("gridAutoRows", string_of_dimension(dimensions));

let string_of_align =
  fun
  | `baseline => "baseline"
  | `flexStart => "flex-start"
  | `flexEnd => "flex-end"
  | `center => "center"
  | `auto => "auto"
  | `stretch => "stretch";
let alignItems = x => Declaration("alignItems", string_of_align(x));
let alignSelf = x => Declaration("alignSelf", string_of_align(x));

let string_of_justify =
  fun
  | `flexStart => "flex-start"
  | `flexEnd => "flex-end"
  | `center => "center"
  | `spaceAround => "space-around"
  | `spaceBetween => "space-between"
  | `spaceEvenly => "space-evenly"
  | `stretch => "stretch";
let justifyContent = x =>
  Declaration("justifyContent", string_of_justify(x));
let justifySelf = x => Declaration("justifySelf", string_of_justify(x));
let alignContent = x => Declaration("alignContent", string_of_justify(x));

let boxSizing = x =>
  Declaration(
    "boxSizing",
    switch (x) {
    | `contentBox => "content-box"
    | `borderBox => "border-box"
    | `initial => "initial"
    | `inherit_ => "inherit"
    | `unset => "unset"
    },
  );

let float = x =>
  Declaration(
    "float",
    switch (x) {
    | `left => "left"
    | `right => "right"
    | `none => "none"
    },
  );

let clear = x =>
  Declaration(
    "clear",
    switch (x) {
    | `left => "left"
    | `right => "right"
    | `both => "both"
    },
  );

let contentRule = x => Declaration("content", {j|"$x"|j});

let columnCount = x =>
  Declaration(
    "columnCount",
    switch (x) {
    | `auto => "auto"
    | `count(v) => Js.Int.toString(v)
    | `initial => "initial"
    | `inherit_ => "inherit"
    | `unset => "unset"
    },
  );

let objectFit = x =>
  Declaration(
    "objectFit",
    switch (x) {
    | `fill => "fill"
    | `contain => "contain"
    | `cover => "cover"
    | `none => "none"
    | `scaleDown => "scale-down"
    | `initial => "initial"
    | `inherit_ => "inherit"
    | `unset => "unset"
    },
  );

type filter = [
  | `blur(length)
  | `brightness(float)
  | `contrast(float)
  | `dropShadow(length, length, length, color)
  | `grayscale(float)
  | `hueRotate(angle)
  | `invert(float)
  | `opacity(float)
  | `saturate(float)
  | `sepia(float)
  | `url(string)
  | `none
  | cascading
];

let string_of_filter =
  fun
  | `blur(v) => "blur(" ++ Types.Length.toString(v) ++ ")"
  | `brightness(v) => "brightness(" ++ Js.Float.toString(v) ++ "%)"
  | `contrast(v) => "contrast(" ++ Js.Float.toString(v) ++ "%)"
  | `dropShadow(a, b, c, d) =>
    "drop-shadow("
    ++ Types.Length.toString(a)
    ++ " "
    ++ Types.Length.toString(b)
    ++ " "
    ++ Types.Length.toString(c)
    ++ " "
    ++ Converter.string_of_color(d)
    ++ ")"
  | `grayscale(v) => "grayscale(" ++ Js.Float.toString(v) ++ "%)"
  | `hueRotate(v) => "hue-rotate(" ++ Types.Angle.toString(v) ++ ")"
  | `invert(v) => "invert(" ++ Js.Float.toString(v) ++ "%)"
  | `opacity(v) => "opacity(" ++ Js.Float.toString(v) ++ "%)"
  | `saturate(v) => "saturate(" ++ Js.Float.toString(v) ++ "%)"
  | `sepia(v) => "sepia(" ++ Js.Float.toString(v) ++ "%)"
  | `url(v) => "url(" ++ v ++ ")"
  | `initial => "initial"
  | `inherit_ => "inherit"
  | `unset => "unset"
  | `none => "none";

let filter = x =>
  Declaration("filter", x->Belt.List.map(string_of_filter)->join(" "));
/**
 * Style
 */

let backfaceVisibility = x =>
  Declaration("backfaceVisibility", string_of_visibility(x));

let visibility = x => Declaration("visibility", string_of_visibility(x));

module Shadow = {
  type value('a) = string;
  type box;
  type text;
  type t('a) = [ | `shadow(value('a)) | `none];

  let box = (~x=zero, ~y=zero, ~blur=zero, ~spread=zero, ~inset=false, color) =>
    `shadow(
      Types.Length.toString(x)
      ++ " "
      ++ Types.Length.toString(y)
      ++ " "
      ++ Types.Length.toString(blur)
      ++ " "
      ++ Types.Length.toString(spread)
      ++ " "
      ++ string_of_color(color)
      ++ (inset ? " inset" : ""),
    );

  let text = (~x=zero, ~y=zero, ~blur=zero, color) =>
    `shadow(
      Types.Length.toString(x)
      ++ " "
      ++ Types.Length.toString(y)
      ++ " "
      ++ Types.Length.toString(blur)
      ++ " "
      ++ string_of_color(color),
    );

  let toString: t('a) => string =
    fun
    | `shadow(x) => x
    | `none => "none";
};

let boxShadow = x =>
  Declaration(
    "boxShadow",
    switch (x) {
    | #Shadow.t as s => Shadow.toString(s)
    | #Types.Cascading.t as c => Types.Cascading.toString(c)
    },
  );

let boxShadows = x =>
  Declaration("boxShadow", x->Belt.List.map(Shadow.toString)->join(","));

let string_of_borderstyle =
  fun
  | `solid => "solid"
  | `dashed => "dashed"
  | `dotted => "dotted"
  | `none => "none";

let border = (px, style, color) =>
  Declaration(
    "border",
    Types.Length.toString(px)
    ++ " "
    ++ string_of_borderstyle(style)
    ++ " "
    ++ string_of_color(color),
  );
let borderWidth = x => Declaration("borderWidth", Types.Length.toString(x));
let borderStyle = x => Declaration("borderStyle", string_of_borderstyle(x));
let borderColor = x => Declaration("borderColor", string_of_color(x));

let borderLeft = (px, style, color) =>
  Declaration(
    "borderLeft",
    Types.Length.toString(px)
    ++ " "
    ++ string_of_borderstyle(style)
    ++ " "
    ++ string_of_color(color),
  );
let borderLeftWidth = x =>
  Declaration("borderLeftWidth", Types.Length.toString(x));
let borderLeftStyle = x =>
  Declaration("borderLeftStyle", string_of_borderstyle(x));
let borderLeftColor = x =>
  Declaration("borderLeftColor", string_of_color(x));

let borderRight = (px, style, color) =>
  Declaration(
    "borderRight",
    Types.Length.toString(px)
    ++ " "
    ++ string_of_borderstyle(style)
    ++ " "
    ++ string_of_color(color),
  );

let borderRightWidth = x =>
  Declaration("borderRightWidth", Types.Length.toString(x));
let borderRightColor = x =>
  Declaration("borderRightColor", string_of_color(x));
let borderRightStyle = x =>
  Declaration("borderRightStyle", string_of_borderstyle(x));
let borderTop = (px, style, color) =>
  Declaration(
    "borderTop",
    Types.Length.toString(px)
    ++ " "
    ++ string_of_borderstyle(style)
    ++ " "
    ++ string_of_color(color),
  );

let borderTopWidth = x =>
  Declaration("borderTopWidth", Types.Length.toString(x));
let borderTopStyle = x =>
  Declaration("borderTopStyle", string_of_borderstyle(x));
let borderTopColor = x => Declaration("borderTopColor", string_of_color(x));

let borderBottom = (px, style, color) =>
  Declaration(
    "borderBottom",
    Types.Length.toString(px)
    ++ " "
    ++ string_of_borderstyle(style)
    ++ " "
    ++ string_of_color(color),
  );
let borderBottomWidth = x =>
  Declaration("borderBottomWidth", Types.Length.toString(x));
let borderBottomStyle = x =>
  Declaration("borderBottomStyle", string_of_borderstyle(x));
let borderBottomColor = x =>
  Declaration("borderBottomColor", string_of_color(x));

let borderRadius = i =>
  Declaration("borderRadius", Types.Length.toString(i));
let borderTopLeftRadius = i =>
  Declaration("borderTopLeftRadius", Types.Length.toString(i));
let borderTopRightRadius = i =>
  Declaration("borderTopRightRadius", Types.Length.toString(i));
let borderBottomLeftRadius = i =>
  Declaration("borderBottomLeftRadius", Types.Length.toString(i));
let borderBottomRightRadius = i =>
  Declaration("borderBottomRightRadius", Types.Length.toString(i));

let tableLayout = x =>
  Declaration(
    "tableLayout",
    switch (x) {
    | `auto => "auto"
    | `fixed => "fixed"
    },
  );

let borderCollapse = x =>
  Declaration(
    "borderCollapse",
    switch (x) {
    | `collapse => "collapse"
    | `separate => "separate"
    },
  );

let borderSpacing = i =>
  Declaration("borderSpacing", Types.Length.toString(i));

let background = x => Declaration("background", string_of_background(x));
let backgrounds = bg =>
  Declaration(
    "background",
    bg->Belt.List.map(string_of_background)->join(", "),
  );
let backgroundColor = x =>
  Declaration("backgroundColor", string_of_color(x));
let backgroundImage = x =>
  Declaration(
    "backgroundImage",
    switch (x) {
    | `none => "none"
    | `url(url) => "url(" ++ url ++ ")"
    | `linearGradient(angle, stops) => string_of_linearGradient(angle, stops)
    | `repeatingLinearGradient(angle, stops) =>
      string_of_repeatingLinearGradient(angle, stops)
    | `radialGradient(stops) =>
      "radial-gradient(" ++ string_of_stops(stops) ++ ")"
    | `repeatingRadialGradient(stops) =>
      "repeating-radial-gradient(" ++ string_of_stops(stops) ++ ")"
    },
  );

let backgroundAttachment = x =>
  Declaration(
    "backgroundAttachment",
    switch (x) {
    | `scroll => "scroll"
    | `fixed => "fixed"
    | `local => "local"
    },
  );

let backgroundClip = x =>
  Declaration(
    "backgroundClip",
    switch (x) {
    | `borderBox => "border-box"
    | `contentBox => "content-box"
    | `paddingBox => "padding-box"
    },
  );

let backgroundOrigin = x =>
  Declaration(
    "backgroundOrigin",
    switch (x) {
    | `borderBox => "border-box"
    | `contentBox => "content-box"
    | `paddingBox => "padding-box"
    },
  );

let backgroundPosition = (x, y) =>
  Declaration(
    "backgroundPosition",
    Types.Length.toString(x) ++ " " ++ Types.Length.toString(y),
  );

let backgroundRepeat = x =>
  Declaration(
    "backgroundRepeat",
    switch (x) {
    | `repeat => "repeat"
    | `noRepeat => "no-repeat"
    | `repeatX => "repeat-x"
    | `repeatY => "repeat-y"
    },
  );

let backgroundSize = x =>
  Declaration(
    "backgroundSize",
    switch (x) {
    | `size(x, y) =>
      Types.Length.toString(x) ++ " " ++ Types.Length.toString(y)
    | `auto => "auto"
    | `cover => "cover"
    | `contain => "contain"
    },
  );

let clipPath = x =>
  Declaration(
    "clipPath",
    switch (x) {
    | `url(url) => "url(" ++ url ++ ")"
    },
  );

let string_of_listStylePosition =
  fun
  | `inside => "inside"
  | `outside => "outside";

let string_of_listStyleImage =
  fun
  | `none => "none"
  | `url(url) => "url(" ++ url ++ ")";

let listStyle = (style, pos, img) =>
  Declaration(
    "listStyle",
    Types.ListStyleType.toString(style)
    ++ " "
    ++ string_of_listStylePosition(pos)
    ++ " "
    ++ string_of_listStyleImage(img),
  );

let listStyleType = x =>
  Declaration("listStyleType", Types.ListStyleType.toString(x));

let listStylePosition = x =>
  Declaration("listStylePosition", string_of_listStylePosition(x));

let listStyleImage = x =>
  Declaration("listStyleImage", string_of_listStyleImage(x));

let opacity = x => Declaration("opacity", Js.Float.toString(x));

let outline = (size, style, color) =>
  Declaration(
    "outline",
    Types.Length.toString(size)
    ++ " "
    ++ Types.OutlineStyle.toString(style)
    ++ " "
    ++ string_of_color(color),
  );

let outlineStyle = x =>
  Declaration("outlineStyle", Types.OutlineStyle.toString(x));

let outlineWidth = x =>
  Declaration("outlineWidth", Types.Length.toString(x));

let outlineColor = x => Declaration("outlineColor", string_of_color(x));

let outlineOffset = x =>
  Declaration("outlineOffset", Types.Length.toString(x));

/**
 * Text
 */

let thin = `thin;
let extraLight = `extraLight;
let light = `light;
let medium = `medium;
let semiBold = `semiBold;
let bold = `bold;
let extraBold = `extraBold;
let lighter = `lighter;
let bolder = `bolder;

let color = x => Declaration("color", string_of_color(x));

let fontWeight = x =>
  Declaration(
    "fontWeight",
    switch (x) {
    | #Types.FontWeight.t as f => Types.FontWeight.toString(f)
    | #Types.Cascading.t as c => Types.Cascading.toString(c)
    },
  );

let fontFace = (~fontFamily, ~src, ~fontStyle=?, ~fontWeight=?, ()) => {
  let fontStyle =
    Js.Option.map((. value) => Types.FontStyle.toString(value), fontStyle);
  let src =
    src
    |> List.map(
         fun
         | `localUrl(value) => {j|local("$(value)")|j}
         | `url(value) => {j|url("$(value)")|j},
       )
    |> String.concat(", ");

  let fontStyle =
    Belt.Option.mapWithDefault(fontStyle, "", s => "font-style: " ++ s);
  let fontWeight =
    Belt.Option.mapWithDefault(fontWeight, "", w =>
      "font-weight: "
      ++ (
        switch (w) {
        | #Types.FontWeight.t as f => Types.FontWeight.toString(f)
        | #Types.Cascading.t as c => Types.Cascading.toString(c)
        }
      )
    );
  let asString = {j|@font-face {
    font-family: $fontFamily;
    src: $src;
    $(fontStyle);
    $(fontWeight);
}|j};

  Emotion.rawInjectGlobal(asString);

  fontFamily;
};

let lineHeight = x =>
  Declaration(
    "lineHeight",
    switch (x) {
    | `normal => "normal"
    | `abs(x) => Js.Float.toString(x)
    | `calc(`add, a, b) =>
      "calc("
      ++ Types.Length.toString(a)
      ++ " + "
      ++ Types.Length.toString(b)
      ++ ")"
    | `calc(`sub, a, b) =>
      "calc("
      ++ Types.Length.toString(a)
      ++ " - "
      ++ Types.Length.toString(b)
      ++ ")"
    | `ch(x) => Js.Float.toString(x) ++ "ch"
    | `cm(x) => Js.Float.toString(x) ++ "cm"
    | `em(x) => Js.Float.toString(x) ++ "em"
    | `ex(x) => Js.Float.toString(x) ++ "ex"
    | `mm(x) => Js.Float.toString(x) ++ "mm"
    | `percent(x) => Js.Float.toString(x) ++ "%"
    | `pt(x) => Js.Int.toString(x) ++ "pt"
    | `px(x) => Js.Int.toString(x) ++ "px"
    | `pxFloat(x) => Js.Float.toString(x) ++ "px"
    | `rem(x) => Js.Float.toString(x) ++ "rem"
    | `vh(x) => Js.Float.toString(x) ++ "vh"
    | `vmax(x) => Js.Float.toString(x) ++ "vmax"
    | `vmin(x) => Js.Float.toString(x) ++ "vmin"
    | `vw(x) => Js.Float.toString(x) ++ "vw"
    | `auto => "auto"
    | `zero => "0"
    | `initial => "initial"
    | `inherit_ => "inherit"
    | `unset => "unset"
    },
  );

let letterSpacing = x =>
  Declaration(
    "letterSpacing",
    switch (x) {
    | `normal => "normal"
    | `calc(`add, a, b) =>
      "calc("
      ++ Types.Length.toString(a)
      ++ " + "
      ++ Types.Length.toString(b)
      ++ ")"
    | `calc(`sub, a, b) =>
      "calc("
      ++ Types.Length.toString(a)
      ++ " - "
      ++ Types.Length.toString(b)
      ++ ")"
    | `ch(x) => Js.Float.toString(x) ++ "ch"
    | `cm(x) => Js.Float.toString(x) ++ "cm"
    | `em(x) => Js.Float.toString(x) ++ "em"
    | `ex(x) => Js.Float.toString(x) ++ "ex"
    | `mm(x) => Js.Float.toString(x) ++ "mm"
    | `percent(x) => Js.Float.toString(x) ++ "%"
    | `pt(x) => Js.Int.toString(x) ++ "pt"
    | `px(x) => Js.Int.toString(x) ++ "px"
    | `pxFloat(x) => Js.Float.toString(x) ++ "px"
    | `rem(x) => Js.Float.toString(x) ++ "rem"
    | `vh(x) => Js.Float.toString(x) ++ "vh"
    | `vmax(x) => Js.Float.toString(x) ++ "vmax"
    | `vmin(x) => Js.Float.toString(x) ++ "vmin"
    | `vw(x) => Js.Float.toString(x) ++ "vw"
    | `auto => "auto"
    | `zero => "0"
    | `initial => "initial"
    | `inherit_ => "inherit"
    | `unset => "unset"
    },
  );

let textAlign = x =>
  Declaration(
    "textAlign",
    switch (x) {
    | `left => "left"
    | `right => "right"
    | `center => "center"
    | `justify => "justify"
    | `initial => "initial"
    | `inherit_ => "inherit"
    | `unset => "unset"
    },
  );

let textDecoration = x =>
  Declaration(
    "textDecoration",
    switch (x) {
    | `none => "none"
    | `underline => "underline"
    | `overline => "overline"
    | `lineThrough => "line-through"
    | `initial => "initial"
    | `inherit_ => "inherit"
    | `unset => "unset"
    },
  );

let textDecorationColor = x =>
  Declaration("textDecorationColor", string_of_color(x));

let textDecorationStyle = x =>
  Declaration(
    "textDecorationStyle",
    switch (x) {
    | `wavy => "wavy"
    | `solid => "solid"
    | `double => "double"
    | `dotted => "dotted"
    | `dashed => "dashed"
    | `initial => "initial"
    | `inherit_ => "inherit"
    | `unset => "unset"
    },
  );

let textIndent = x => Declaration("textIndent", Types.Length.toString(x));

let textOverflow = x =>
  Declaration(
    "textOverflow",
    switch (x) {
    | `clip => "clip"
    | `ellipsis => "ellipsis"
    | `string(s) => s
    | `initial => "initial"
    | `inherit_ => "inherit"
    | `unset => "unset"
    },
  );

let textShadow = x =>
  Declaration(
    "textShadow",
    switch (x) {
    | #Shadow.t as s => Shadow.toString(s)
    | #Types.Cascading.t as c => Types.Cascading.toString(c)
    },
  );

let textShadows = x =>
  Declaration("textShadow", x->Belt.List.map(Shadow.toString)->join(","));

let textTransform = x =>
  Declaration(
    "textTransform",
    switch (x) {
    | `uppercase => "uppercase"
    | `lowercase => "lowercase"
    | `capitalize => "capitalize"
    | `none => "none"
    | `initial => "initial"
    | `inherit_ => "inherit"
    | `unset => "unset"
    },
  );

let userSelect = x =>
  Declaration(
    "userSelect",
    switch (x) {
    | `auto => "auto"
    | `all => "all"
    | `text => "text"
    | `none => "none"
    | `initial => "initial"
    | `inherit_ => "inherit"
    | `unset => "unset"
    },
  );

let whiteSpace = x =>
  Declaration(
    "whiteSpace",
    switch (x) {
    | `normal => "normal"
    | `nowrap => "nowrap"
    | `pre => "pre"
    | `preLine => "pre-line"
    | `preWrap => "pre-wrap"
    | `initial => "initial"
    | `inherit_ => "inherit"
    | `unset => "unset"
    },
  );

let wordBreak = x =>
  Declaration(
    "wordBreak",
    switch (x) {
    | `breakAll => "break-all"
    | `keepAll => "keep-all"
    | `normal => "normal"
    | `initial => "initial"
    | `inherit_ => "inherit"
    | `unset => "unset"
    },
  );

let wordSpacing = x =>
  Declaration(
    "wordSpacing",
    switch (x) {
    | `normal => "normal"
    | `calc(`add, a, b) =>
      "calc("
      ++ Types.Length.toString(a)
      ++ " + "
      ++ Types.Length.toString(b)
      ++ ")"
    | `calc(`sub, a, b) =>
      "calc("
      ++ Types.Length.toString(a)
      ++ " - "
      ++ Types.Length.toString(b)
      ++ ")"
    | `ch(x) => Js.Float.toString(x) ++ "ch"
    | `cm(x) => Js.Float.toString(x) ++ "cm"
    | `em(x) => Js.Float.toString(x) ++ "em"
    | `ex(x) => Js.Float.toString(x) ++ "ex"
    | `mm(x) => Js.Float.toString(x) ++ "mm"
    | `percent(x) => Js.Float.toString(x) ++ "%"
    | `pt(x) => Js.Int.toString(x) ++ "pt"
    | `px(x) => Js.Int.toString(x) ++ "px"
    | `pxFloat(x) => Js.Float.toString(x) ++ "px"
    | `rem(x) => Js.Float.toString(x) ++ "rem"
    | `vh(x) => Js.Float.toString(x) ++ "vh"
    | `vmax(x) => Js.Float.toString(x) ++ "vmax"
    | `vmin(x) => Js.Float.toString(x) ++ "vmin"
    | `vw(x) => Js.Float.toString(x) ++ "vw"
    | `auto => "auto"
    | `zero => "0"
    | `initial => "initial"
    | `inherit_ => "inherit"
    | `unset => "unset"
    },
  );

let wordWrap = x =>
  Declaration(
    "wordWrap",
    switch (x) {
    | `normal => "normal"
    | `breakWord => "break-word"
    | `initial => "initial"
    | `inherit_ => "inherit"
    | `unset => "unset"
    },
  );

let string_of_pointerEvents =
  fun
  | `auto => "auto"
  | `none => "none";

let pointerEvents = x =>
  Declaration("pointerEvents", string_of_pointerEvents(x));

/**
 * Transform
 */

let transform = x => Declaration("transform", Types.Transform.toString(x));

let transforms = xs =>
  Declaration(
    "transform",
    xs->Belt.List.map(Types.Transform.toString)->join(" "),
  );

let transformOrigin = (x, y) =>
  Declaration(
    "transformOrigin",
    Types.Length.toString(x) ++ " " ++ Types.Length.toString(y),
  );

let transformOrigin3d = (x, y, z) =>
  Declaration(
    "transformOrigin",
    Types.Length.toString(x)
    ++ " "
    ++ Types.Length.toString(y)
    ++ " "
    ++ Types.Length.toString(z)
    ++ " ",
  );

let transformStyle = x =>
  Declaration(
    "transformStyle",
    switch (x) {
    | `preserve3d => "preserve-3d"
    | `flat => "flat"
    },
  );

let perspective = x =>
  Declaration(
    "perspective",
    switch (x) {
    | `none => "none"
    | `calc(`add, a, b) =>
      "calc("
      ++ Types.Length.toString(a)
      ++ " + "
      ++ Types.Length.toString(b)
      ++ ")"
    | `calc(`sub, a, b) =>
      "calc("
      ++ Types.Length.toString(a)
      ++ " - "
      ++ Types.Length.toString(b)
      ++ ")"
    | `ch(x) => Js.Float.toString(x) ++ "ch"
    | `cm(x) => Js.Float.toString(x) ++ "cm"
    | `em(x) => Js.Float.toString(x) ++ "em"
    | `ex(x) => Js.Float.toString(x) ++ "ex"
    | `mm(x) => Js.Float.toString(x) ++ "mm"
    | `percent(x) => Js.Float.toString(x) ++ "%"
    | `pt(x) => Js.Int.toString(x) ++ "pt"
    | `px(x) => Js.Int.toString(x) ++ "px"
    | `pxFloat(x) => Js.Float.toString(x) ++ "px"
    | `rem(x) => Js.Float.toString(x) ++ "rem"
    | `vh(x) => Js.Float.toString(x) ++ "vh"
    | `vmax(x) => Js.Float.toString(x) ++ "vmax"
    | `vmin(x) => Js.Float.toString(x) ++ "vmin"
    | `vw(x) => Js.Float.toString(x) ++ "vw"
    | `zero => "0"
    },
  );

/**
* Transition
*/
module Transition = {
  type t = [ | `value(string)];

  let shorthand = (~duration=0, ~delay=0, ~timingFunction=`ease, property) =>
    `value(
      string_of_time(duration)
      ++ " "
      ++ Types.TimingFunction.toString(timingFunction)
      ++ " "
      ++ string_of_time(delay)
      ++ " "
      ++ property,
    );

  let toString =
    fun
    | `value(v) => v;
};

let transitionValue = x => Declaration("transition", Transition.toString(x));

let transitionList = x =>
  Declaration(
    "transition",
    x->Belt.List.map(Transition.toString)->join(", "),
  );
let transitions = transitionList;

let transition = (~duration=?, ~delay=?, ~timingFunction=?, property) =>
  transitionValue(
    Transition.shorthand(~duration?, ~delay?, ~timingFunction?, property),
  );

let transitionDelay = i => Declaration("transitionDelay", string_of_time(i));

let transitionDuration = i =>
  Declaration("transitionDuration", string_of_time(i));

let transitionTimingFunction = x =>
  Declaration("transitionTimingFunction", Types.TimingFunction.toString(x));

let transitionProperty = x => Declaration("transitionProperty", x);

let perspectiveOrigin = (x, y) =>
  Declaration(
    "perspectiveOrigin",
    Types.Length.toString(x) ++ " " ++ Types.Length.toString(y),
  );

/**
 * Animation
 */
module Animation = {
  type t = [ | `value(string)];

  let shorthand =
      (
        ~duration=0,
        ~delay=0,
        ~direction=`normal,
        ~timingFunction=`ease,
        ~fillMode=`none,
        ~playState=`running,
        ~iterationCount=`count(1),
        name,
      ) =>
    `value(
      name
      ++ " "
      ++ string_of_time(duration)
      ++ " "
      ++ Types.TimingFunction.toString(timingFunction)
      ++ " "
      ++ string_of_time(delay)
      ++ " "
      ++ Types.AnimationIterationCount.toString(iterationCount)
      ++ " "
      ++ Types.AnimationDirection.toString(direction)
      ++ " "
      ++ Types.AnimationFillMode.toString(fillMode)
      ++ " "
      ++ Types.AnimationPlayState.toString(playState),
    );

  let toString =
    fun
    | `value(v) => v;
};

let animationValue = x => Declaration("animation", Animation.toString(x));

let animation =
    (
      ~duration=?,
      ~delay=?,
      ~direction=?,
      ~timingFunction=?,
      ~fillMode=?,
      ~playState=?,
      ~iterationCount=?,
      name,
    ) =>
  animationValue(
    Animation.shorthand(
      ~duration?,
      ~delay?,
      ~direction?,
      ~timingFunction?,
      ~fillMode?,
      ~playState?,
      ~iterationCount?,
      name,
    ),
  );

let animations = x =>
  Declaration(
    "animation",
    x->Belt.List.map(Animation.toString)->join(", "),
  );

let animationDelay = x => Declaration("animationDelay", string_of_time(x));
let animationDirection = x =>
  Declaration("animationDirection", Types.AnimationDirection.toString(x));
let animationDuration = x =>
  Declaration("animationDuration", string_of_time(x));
let animationFillMode = x =>
  Declaration("animationFillMode", Types.AnimationFillMode.toString(x));
let animationIterationCount = x =>
  Declaration(
    "animationIterationCount",
    Types.AnimationIterationCount.toString(x),
  );
let animationName = x => Declaration("animationName", x);
let animationPlayState = x =>
  Declaration("animationPlayState", Types.AnimationPlayState.toString(x));
let animationTimingFunction = x =>
  Declaration("animationTimingFunction", Types.TimingFunction.toString(x));

/**
 * Selectors
 */

let selector = (selector, rules) => Selector(selector, rules);

/* MEDIA */

let active = selector(":active");
let after = selector("::after");
let before = selector("::before");
let checked = selector(":checked");
let children = selector(" > *");
let directSibling = selector(" + ");
let disabled = selector(":disabled");
let firstChild = selector(":first-child");
let firstOfType = selector(":first-of-type");
let focus = selector(":focus");
let hover = selector(":hover");
let lastChild = selector(":last-child");
let lastOfType = selector(":last-of-type");
let link = selector(":link");
let readOnly = selector(":read-only");
let required = selector(":required");
let visited = selector(":visited");
let enabled = selector(":enabled");
let noContent = selector(":empty");
let default = selector(":default");
let anyLink = selector(":any-link");
let onlyChild = selector(":only-child");
let onlyOfType = selector(":only-of-type");
let optional = selector(":optional");
let invalid = selector(":invalid");
let outOfRange = selector(":out-of-range");
let siblings = selector(" ~ ");
let target = selector(":target");
let firstLine = selector("::first-line");
let firstLetter = selector("::first-letter");
let selection = selector("::selection");
let placeholder = selector("::placeholder");

let media = (query, rules) => Selector("@media " ++ query, rules);

/**
 * SVG
 */
module SVG = {
  let fill = color => Declaration("fill", string_of_color(color));
  let fillOpacity = opacity =>
    Declaration("fillOpacity", Js.Float.toString(opacity));
  let fillRule = x =>
    Declaration(
      "fillRule",
      switch (x) {
      | `evenodd => "evenodd"
      | `nonzero => "nonzero"
      },
    );
  let stroke = color => Declaration("stroke", string_of_color(color));
  let strokeWidth = length =>
    Declaration("strokeWidth", Types.Length.toString(length));
  let strokeOpacity = opacity =>
    Declaration("strokeOpacity", Js.Float.toString(opacity));
  let strokeMiterlimit = x =>
    Declaration("strokeMiterlimit", Js.Float.toString(x));
  let strokeLinecap = x =>
    Declaration(
      "strokeLinecap",
      switch (x) {
      | `butt => "butt"
      | `round => "round"
      | `square => "square"
      },
    );

  let strokeLinejoin = x =>
    Declaration(
      "strokeLinejoin",
      switch (x) {
      | `miter => "miter"
      | `round => "round"
      | `bevel => "bevel"
      },
    );
  let stopColor = c => Declaration("stopColor", string_of_color(c));
  let stopOpacity = o => Declaration("stopOpacity", Js.Float.toString(o));
};
