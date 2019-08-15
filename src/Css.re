include Css_Colors;
module Types = Css_Types;

type rule = [
  | `selector(string, list(rule))
  | `declaration(string, string)
];

type selector = [ | `selector(string, list(rule))];
type declaration = [ | `declaration(string, string)];

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
    | `declaration(name, value) when name == "content" => (
        name,
        Js.Json.string(value == "" ? "\"\"" : value),
      )
    | `declaration(name, value) => (name, Js.Json.string(value))
    | `selector(name, ruleset) => (name, makeJson(ruleset))
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

  let string_of_translate3d = (x, y, z) =>
    "translate3d("
    ++ Types.Length.toString(x)
    ++ ", "
    ++ Types.Length.toString(y)
    ++ ", "
    ++ Types.Length.toString(z)
    ++ ")";

  let string_of_scale = (x, y) =>
    "scale(" ++ Js.Float.toString(x) ++ ", " ++ Js.Float.toString(y) ++ ")";

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

  let string_of_cursor = x =>
    switch (x) {
    | `auto => "auto"
    | `default => "default"
    | `none => "none"
    | `contextMenu => "context-menu"
    | `help => "help"
    | `pointer => "pointer"
    | `progress => "progress"
    | `wait => "wait"
    | `cell => "cell"
    | `crosshair => "crosshair"
    | `text => "text"
    | `verticalText => "vertical-text"
    | `alias => "alias"
    | `copy => "copy"
    | `move => "move"
    | `noDrop => "no-drop"
    | `notAllowed => "not-allowed"
    | `grab => "grab"
    | `grabbing => "grabbing"
    | `allScroll => "all-scroll"
    | `colResize => "col-resize"
    | `rowResize => "row-resize"
    | `nResize => "n-resize"
    | `eResize => "e-resize"
    | `sResize => "s-resize"
    | `wResize => "w-resize"
    | `neResize => "ne-resize"
    | `nwResize => "nw-resize"
    | `seResize => "se-resize"
    | `swResize => "sw-resize"
    | `ewResize => "ew-resize"
    | `nsResize => "ns-resize"
    | `neswResize => "nesw-resize"
    | `nwseResize => "nwse-resize"
    | `zoomIn => "zoom-in"
    | `zoomOut => "zoom-out"
    };

  let string_of_fontWeight = x =>
    switch (x) {
    | `num(n) => Js.Int.toString(n)
    | `thin => "100"
    | `extraLight => "200"
    | `light => "300"
    | `normal => "400"
    | `medium => "500"
    | `semiBold => "600"
    | `bold => "700"
    | `extraBold => "800"
    | `black => "900"
    | `lighter => "lighter"
    | `bolder => "bolder"
    | `initial => "initial"
    | `inherit_ => "inherit"
    | `unset => "unset"
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
  | `declaration(name, value) => `declaration((name, value ++ " !important"))
  | _ => v
  };

let label = label => `declaration(("label", label));

/* Properties */

let bottom = x =>
  `declaration((
    "bottom",
    switch (x) {
    | #Types.Length.t as l => Types.Length.toString(l)
    | #Types.Cascading.t as c => Types.Cascading.toString(c)
    },
  ));

let direction = x =>
  `declaration((
    "direction",
    switch (x) {
    | #Types.Direction.t as d => Types.Direction.toString(d)
    | #Types.Cascading.t as c => Types.Cascading.toString(c)
    },
  ));

let fontFamily = x => `declaration(("fontFamily", x));

let fontSize = x =>
  `declaration((
    "fontSize",
    switch (x) {
    | #Types.Length.t as l => Types.Length.toString(l)
    | #Types.Cascading.t as c => Types.Cascading.toString(c)
    },
  ));

let fontStyle = x =>
  `declaration((
    "fontStyle",
    switch (x) {
    | #Types.FontStyle.t as f => Types.FontStyle.toString(f)
    | #Types.Cascading.t as c => Types.Cascading.toString(c)
    },
  ));

let fontVariant = x =>
  `declaration((
    "fontVariant",
    switch (x) {
    | #Types.FontVariant.t as f => Types.FontVariant.toString(f)
    | #Types.Cascading.t as c => Types.Cascading.toString(c)
    },
  ));

let gridAutoFlow = x =>
  `declaration((
    "gridAutoFlow",
    switch (x) {
    | #Types.GridAutoFlow.t as f => Types.GridAutoFlow.toString(f)
    | #Types.Cascading.t as c => Types.Cascading.toString(c)
    },
  ));

let gridColumn = (start, end') =>
  `declaration((
    "gridColumn",
    Js.Int.toString(start) ++ " / " ++ Js.Int.toString(end'),
  ));

let gridColumnGap = n =>
  `declaration(("gridColumnGap", Types.Length.toString(n)));

let gridColumnStart = n =>
  `declaration(("gridColumnStart", Js.Int.toString(n)));

let gridColumnEnd = n => `declaration(("gridColumnEnd", Js.Int.toString(n)));

let gridRow = (start, end') =>
  `declaration((
    "gridRow",
    Js.Int.toString(start) ++ " / " ++ Js.Int.toString(end'),
  ));

let gridGap = n => `declaration(("gridGap", Types.Length.toString(n)));

let gridRowGap = n => `declaration(("gridRowGap", Types.Length.toString(n)));

let gridRowEnd = n => `declaration(("gridRowEnd", Js.Int.toString(n)));

let gridRowStart = n => `declaration(("gridRowStart", Js.Int.toString(n)));

let left = x =>
  `declaration((
    "left",
    switch (x) {
    | #Types.Length.t as l => Types.Length.toString(l)
    | #Types.Cascading.t as c => Types.Cascading.toString(c)
    },
  ));

let marginToString = x =>
  switch (x) {
  | #Types.Length.t as l => Types.Length.toString(l)
  | #Types.Margin.t as m => Types.Margin.toString(m)
  };

let margin = x => `declaration(("margin", marginToString(x)));
let margin2 = (~v, ~h) =>
  `declaration(("margin", marginToString(v) ++ " " ++ marginToString(h)));
let margin3 = (~top, ~h, ~bottom) =>
  `declaration((
    "margin",
    marginToString(top)
    ++ " "
    ++ marginToString(h)
    ++ " "
    ++ marginToString(bottom),
  ));
let margin4 = (~top, ~right, ~bottom, ~left) =>
  `declaration((
    "margin",
    marginToString(top)
    ++ " "
    ++ marginToString(right)
    ++ " "
    ++ marginToString(bottom)
    ++ " "
    ++ marginToString(left),
  ));
let marginLeft = x => `declaration(("marginLeft", marginToString(x)));
let marginRight = x => `declaration(("marginRight", marginToString(x)));
let marginTop = x => `declaration(("marginTop", marginToString(x)));
let marginBottom = x => `declaration(("marginBottom", marginToString(x)));

let overflow = x => `declaration(("overflow", Types.Overflow.toString(x)));
let overflowX = x => `declaration(("overflowX", Types.Overflow.toString(x)));
let overflowY = x => `declaration(("overflowY", Types.Overflow.toString(x)));

let padding = x => `declaration(("padding", Types.Length.toString(x)));
let padding2 = (~v, ~h) =>
  `declaration((
    "padding",
    Types.Length.toString(v) ++ " " ++ Types.Length.toString(h),
  ));
let padding3 = (~top, ~h, ~bottom) =>
  `declaration((
    "padding",
    Types.Length.toString(top)
    ++ " "
    ++ Types.Length.toString(h)
    ++ " "
    ++ Types.Length.toString(bottom),
  ));
let padding4 = (~top, ~right, ~bottom, ~left) =>
  `declaration((
    "padding",
    Types.Length.toString(top)
    ++ " "
    ++ Types.Length.toString(right)
    ++ " "
    ++ Types.Length.toString(bottom)
    ++ " "
    ++ Types.Length.toString(left),
  ));

let paddingBottom = x =>
  `declaration(("paddingBottom", Types.Length.toString(x)));

let paddingLeft = x =>
  `declaration(("paddingLeft", Types.Length.toString(x)));

let paddingRight = x =>
  `declaration(("paddingRight", Types.Length.toString(x)));

let paddingTop = x => `declaration(("paddingTop", Types.Length.toString(x)));

let position = x =>
  `declaration((
    "position",
    switch (x) {
    | #Types.Position.t as p => Types.Position.toString(p)
    | #Types.Cascading.t as c => Types.Cascading.toString(c)
    },
  ));

let resize = x =>
  `declaration((
    "resize",
    switch (x) {
    | #Types.Resize.t as r => Types.Resize.toString(r)
    | #Types.Cascading.t as c => Types.Cascading.toString(c)
    },
  ));

let right = x =>
  `declaration((
    "right",
    switch (x) {
    | #Types.Length.t as l => Types.Length.toString(l)
    | #Types.Cascading.t as c => Types.Cascading.toString(c)
    },
  ));

let top = x =>
  `declaration((
    "top",
    switch (x) {
    | #Types.Length.t as l => Types.Length.toString(l)
    | #Types.Cascading.t as c => Types.Cascading.toString(c)
    },
  ));

let unsafe = (property, value) => `declaration((property, value));

let verticalAlign = x =>
  `declaration((
    "verticalAlign",
    switch (x) {
    | #Types.VerticalAlign.t as v => Types.VerticalAlign.toString(v)
    | #Types.Length.t as l => Types.Length.toString(l)
    | #Types.Cascading.t as c => Types.Cascading.toString(c)
    },
  ));

let zIndex = x => `declaration(("zIndex", Js.Int.toString(x)));

/* Type aliasing */

type cascading = Types.Cascading.t;
type length = Types.Length.t;
type angle = Types.Angle.t;
type fontStyle = Types.FontStyle.t;

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
  `declaration((
    "display",
    switch (x) {
    | `unset => "unset"
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
    },
  ));

let flex = x => `declaration(("flex", string_of_flex(x)));
let flex3 = (~grow, ~shrink, ~basis) =>
  `declaration((
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
  ));
let flexGrow = x => `declaration(("flexGrow", Js.Float.toString(x)));
let flexShrink = x => `declaration(("flexShrink", Js.Float.toString(x)));
let flexBasis = x =>
  `declaration((
    "flexBasis",
    switch (x) {
    | #Types.FlexBasis.t as b => Types.FlexBasis.toString(b)
    | #Types.Length.t as l => Types.Length.toString(l)
    },
  ));

let flexDirection = x =>
  `declaration((
    "flexDirection",
    switch (x) {
    | `row => "row"
    | `column => "column"
    | `rowReverse => "row-reverse"
    | `columnReverse => "column-reverse"
    },
  ));

let flexWrap = x =>
  `declaration((
    "flexWrap",
    switch (x) {
    | `nowrap => "nowrap"
    | `wrap => "wrap"
    | `wrapReverse => "wrap-reverse"
    },
  ));

let order = x => `declaration(("order", Js.Int.toString(x)));

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

let width = x => `declaration(("width", string_of_dimension(x)));
let height = x => `declaration(("height", string_of_dimension(x)));
let minWidth = x => `declaration(("minWidth", string_of_dimension(x)));
let maxWidth = x => `declaration(("maxWidth", string_of_dimension(x)));
let minHeight = x => `declaration(("minHeight", string_of_dimension(x)));
let maxHeight = x => `declaration(("maxHeight", string_of_dimension(x)));

type repeatValue = [ | `autoFill | `autoFit | `num(int)];
let repeatValueToJs =
  fun
  | `autoFill => "auto-fill"
  | `autoFit => "auto-fit"
  | `num(x) => x->Js.Int.toString;

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
    "repeat(" ++ n->repeatValueToJs ++ ", " ++ string_of_dimension(x) ++ ")"
  | `minmax(a, b) =>
    "minmax(" ++ string_of_minmax(a) ++ "," ++ string_of_minmax(b) ++ ")";

let string_of_dimensions = dimensions =>
  dimensions |> List.map(gridLengthToJs) |> String.concat(" ");

let gridTemplateColumns = dimensions =>
  `declaration(("gridTemplateColumns", string_of_dimensions(dimensions)));

let gridTemplateRows = dimensions =>
  `declaration(("gridTemplateRows", string_of_dimensions(dimensions)));

let gridAutoColumns = dimensions =>
  `declaration(("gridAutoColumns", string_of_dimension(dimensions)));

let gridAutoRows = dimensions =>
  `declaration(("gridAutoRows", string_of_dimension(dimensions)));

let string_of_align =
  fun
  | `baseline => "baseline"
  | `flexStart => "flex-start"
  | `flexEnd => "flex-end"
  | `center => "center"
  | `auto => "auto"
  | `stretch => "stretch";
let alignItems = x => `declaration(("alignItems", string_of_align(x)));
let alignSelf = x => `declaration(("alignSelf", string_of_align(x)));

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
  `declaration(("justifyContent", string_of_justify(x)));
let justifySelf = x => `declaration(("justifySelf", string_of_justify(x)));
let alignContent = x => `declaration(("alignContent", string_of_justify(x)));

let boxSizing = x =>
  `declaration((
    "boxSizing",
    switch (x) {
    | `contentBox => "content-box"
    | `borderBox => "border-box"
    | `initial => "initial"
    | `inherit_ => "inherit"
    | `unset => "unset"
    },
  ));

let float = x =>
  `declaration((
    "float",
    switch (x) {
    | `left => "left"
    | `right => "right"
    | `none => "none"
    },
  ));

let clear = x =>
  `declaration((
    "clear",
    switch (x) {
    | `left => "left"
    | `right => "right"
    | `both => "both"
    },
  ));

let contentRule = x => `declaration(("content", {j|"$x"|j}));

let columnCount = x =>
  `declaration((
    "columnCount",
    switch (x) {
    | `auto => "auto"
    | `count(v) => Js.Int.toString(v)
    | `initial => "initial"
    | `inherit_ => "inherit"
    | `unset => "unset"
    },
  ));

let objectFit = x =>
  `declaration((
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
  ));

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
  `declaration((
    "filter",
    x |> List.map(string_of_filter) |> joinLast(" "),
  ));
/**
 * Style
 */

let backfaceVisibility = x =>
  `declaration(("backfaceVisibility", string_of_visibility(x)));

let visibility = x => `declaration(("visibility", string_of_visibility(x)));

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
  `declaration((
    "boxShadow",
    switch (x) {
    | #Shadow.t as s => Shadow.toString(s)
    | #Types.Cascading.t as c => Types.Cascading.toString(c)
    },
  ));

let boxShadows = x =>
  `declaration(("boxShadow", x->Belt.List.map(Shadow.toString)->join(",")));

let string_of_borderstyle =
  fun
  | `solid => "solid"
  | `dashed => "dashed"
  | `dotted => "dotted"
  | `none => "none";

let border = (px, style, color) =>
  `declaration((
    "border",
    Types.Length.toString(px)
    ++ " "
    ++ string_of_borderstyle(style)
    ++ " "
    ++ string_of_color(color),
  ));
let borderWidth = x =>
  `declaration(("borderWidth", Types.Length.toString(x)));
let borderStyle = x =>
  `declaration(("borderStyle", string_of_borderstyle(x)));
let borderColor = x => `declaration(("borderColor", string_of_color(x)));

let borderLeft = (px, style, color) =>
  `declaration((
    "borderLeft",
    Types.Length.toString(px)
    ++ " "
    ++ string_of_borderstyle(style)
    ++ " "
    ++ string_of_color(color),
  ));
let borderLeftWidth = x =>
  `declaration(("borderLeftWidth", Types.Length.toString(x)));
let borderLeftStyle = x =>
  `declaration(("borderLeftStyle", string_of_borderstyle(x)));
let borderLeftColor = x =>
  `declaration(("borderLeftColor", string_of_color(x)));

let borderRight = (px, style, color) =>
  `declaration((
    "borderRight",
    Types.Length.toString(px)
    ++ " "
    ++ string_of_borderstyle(style)
    ++ " "
    ++ string_of_color(color),
  ));

let borderRightWidth = x =>
  `declaration(("borderRightWidth", Types.Length.toString(x)));
let borderRightColor = x =>
  `declaration(("borderRightColor", string_of_color(x)));
let borderRightStyle = x =>
  `declaration(("borderRightStyle", string_of_borderstyle(x)));
let borderTop = (px, style, color) =>
  `declaration((
    "borderTop",
    Types.Length.toString(px)
    ++ " "
    ++ string_of_borderstyle(style)
    ++ " "
    ++ string_of_color(color),
  ));

let borderTopWidth = x =>
  `declaration(("borderTopWidth", Types.Length.toString(x)));
let borderTopStyle = x =>
  `declaration(("borderTopStyle", string_of_borderstyle(x)));
let borderTopColor = x =>
  `declaration(("borderTopColor", string_of_color(x)));

let borderBottom = (px, style, color) =>
  `declaration((
    "borderBottom",
    Types.Length.toString(px)
    ++ " "
    ++ string_of_borderstyle(style)
    ++ " "
    ++ string_of_color(color),
  ));
let borderBottomWidth = x =>
  `declaration(("borderBottomWidth", Types.Length.toString(x)));
let borderBottomStyle = x =>
  `declaration(("borderBottomStyle", string_of_borderstyle(x)));
let borderBottomColor = x =>
  `declaration(("borderBottomColor", string_of_color(x)));

let borderRadius = i =>
  `declaration(("borderRadius", Types.Length.toString(i)));
let borderTopLeftRadius = i =>
  `declaration(("borderTopLeftRadius", Types.Length.toString(i)));
let borderTopRightRadius = i =>
  `declaration(("borderTopRightRadius", Types.Length.toString(i)));
let borderBottomLeftRadius = i =>
  `declaration(("borderBottomLeftRadius", Types.Length.toString(i)));
let borderBottomRightRadius = i =>
  `declaration(("borderBottomRightRadius", Types.Length.toString(i)));

let tableLayout = x =>
  `declaration((
    "tableLayout",
    switch (x) {
    | `auto => "auto"
    | `fixed => "fixed"
    },
  ));

let borderCollapse = x =>
  `declaration((
    "borderCollapse",
    switch (x) {
    | `collapse => "collapse"
    | `separate => "separate"
    },
  ));

let borderSpacing = i =>
  `declaration(("borderSpacing", Types.Length.toString(i)));

let background = x => `declaration(("background", string_of_background(x)));
let backgrounds = bg =>
  `declaration((
    "background",
    bg |> List.map(string_of_background) |> joinLast(", "),
  ));
let backgroundColor = x =>
  `declaration(("backgroundColor", string_of_color(x)));
let backgroundImage = x =>
  `declaration((
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
  ));

let backgroundAttachment = x =>
  `declaration((
    "backgroundAttachment",
    switch (x) {
    | `scroll => "scroll"
    | `fixed => "fixed"
    | `local => "local"
    },
  ));

let backgroundClip = x =>
  `declaration((
    "backgroundClip",
    switch (x) {
    | `borderBox => "border-box"
    | `contentBox => "content-box"
    | `paddingBox => "padding-box"
    },
  ));

let backgroundOrigin = x =>
  `declaration((
    "backgroundOrigin",
    switch (x) {
    | `borderBox => "border-box"
    | `contentBox => "content-box"
    | `paddingBox => "padding-box"
    },
  ));

let backgroundPosition = (x, y) =>
  `declaration((
    "backgroundPosition",
    Types.Length.toString(x) ++ " " ++ Types.Length.toString(y),
  ));

let backgroundRepeat = x =>
  `declaration((
    "backgroundRepeat",
    switch (x) {
    | `repeat => "repeat"
    | `noRepeat => "no-repeat"
    | `repeatX => "repeat-x"
    | `repeatY => "repeat-y"
    },
  ));

let backgroundSize = x =>
  `declaration((
    "backgroundSize",
    switch (x) {
    | `size(x, y) =>
      Types.Length.toString(x) ++ " " ++ Types.Length.toString(y)
    | `auto => "auto"
    | `cover => "cover"
    | `contain => "contain"
    },
  ));

let cursor = x => `declaration(("cursor", string_of_cursor(x)));

let clipPath = x =>
  `declaration((
    "clipPath",
    switch (x) {
    | `url(url) => "url(" ++ url ++ ")"
    },
  ));

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

let string_of_listStyleType =
  fun
  | `disc => "disc"
  | `circle => "circle"
  | `square => "square"
  | `decimal => "decimal"
  | `lowerAlpha => "lower-alpha"
  | `upperAlpha => "upper-alpha"
  | `lowerGreek => "lower-greek"
  | `lowerLatin => "lower-latin"
  | `upperLatin => "upper-latin"
  | `lowerRoman => "lower-roman"
  | `upperRoman => "upper-roman"
  | `none => "none";

let string_of_listStylePosition =
  fun
  | `inside => "inside"
  | `outside => "outside";

let string_of_listStyleImage =
  fun
  | `none => "none"
  | `url(url) => "url(" ++ url ++ ")";

let listStyle = (style, pos, img) =>
  `declaration((
    "listStyle",
    string_of_listStyleType(style)
    ++ " "
    ++ string_of_listStylePosition(pos)
    ++ " "
    ++ string_of_listStyleImage(img),
  ));

let listStyleType = x =>
  `declaration(("listStyleType", string_of_listStyleType(x)));

let listStylePosition = x =>
  `declaration(("listStylePosition", string_of_listStylePosition(x)));

let listStyleImage = x =>
  `declaration(("listStyleImage", string_of_listStyleImage(x)));

let opacity = x => `declaration(("opacity", Js.Float.toString(x)));

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

let string_of_outlineStyle =
  fun
  | `none => "none"
  | `hidden => "hidden"
  | `dotted => "dotted"
  | `dashed => "dashed"
  | `solid => "solid"
  | `double => "double"
  | `groove => "grove"
  | `ridge => "ridge"
  | `inset => "inset"
  | `outset => "outset";

let outline = (size, style, color) =>
  `declaration((
    "outline",
    Types.Length.toString(size)
    ++ " "
    ++ string_of_outlineStyle(style)
    ++ " "
    ++ string_of_color(color),
  ));

let outlineStyle = x =>
  `declaration(("outlineStyle", string_of_outlineStyle(x)));

let outlineWidth = x =>
  `declaration(("outlineWidth", Types.Length.toString(x)));

let outlineColor = x => `declaration(("outlineColor", string_of_color(x)));

let outlineOffset = x =>
  `declaration(("outlineOffset", Types.Length.toString(x)));

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

let thin = `thin;
let extraLight = `extraLight;
let light = `light;
let medium = `medium;
let semiBold = `semiBold;
let bold = `bold;
let extraBold = `extraBold;
let lighter = `lighter;
let bolder = `bolder;

let color = x => `declaration(("color", string_of_color(x)));

let fontWeight = x => `declaration(("fontWeight", string_of_fontWeight(x)));

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
      "font-weight: " ++ string_of_fontWeight(w)
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
  `declaration((
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
  ));

let letterSpacing = x =>
  `declaration((
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
  ));

let textAlign = x =>
  `declaration((
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
  ));

let textDecoration = x =>
  `declaration((
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
  ));

let textDecorationColor = x =>
  `declaration(("textDecorationColor", string_of_color(x)));

let textDecorationStyle = x =>
  `declaration((
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
  ));

let textIndent = x => `declaration(("textIndent", Types.Length.toString(x)));

let textOverflow = x =>
  `declaration((
    "textOverflow",
    switch (x) {
    | `clip => "clip"
    | `ellipsis => "ellipsis"
    | `string(s) => s
    | `initial => "initial"
    | `inherit_ => "inherit"
    | `unset => "unset"
    },
  ));

let textShadow = x =>
  `declaration((
    "textShadow",
    switch (x) {
    | #Shadow.t as s => Shadow.toString(s)
    | #Types.Cascading.t as c => Types.Cascading.toString(c)
    },
  ));

let textShadows = x =>
  `declaration((
    "textShadow",
    x->Belt.List.map(Shadow.toString)->join(","),
  ));

let textTransform = x =>
  `declaration((
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
  ));

let userSelect = x =>
  `declaration((
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
  ));

let whiteSpace = x =>
  `declaration((
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
  ));

let wordBreak = x =>
  `declaration((
    "wordBreak",
    switch (x) {
    | `breakAll => "break-all"
    | `keepAll => "keep-all"
    | `normal => "normal"
    | `initial => "initial"
    | `inherit_ => "inherit"
    | `unset => "unset"
    },
  ));

let wordSpacing = x =>
  `declaration((
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
  ));

let wordWrap = x =>
  `declaration((
    "wordWrap",
    switch (x) {
    | `normal => "normal"
    | `breakWord => "break-word"
    | `initial => "initial"
    | `inherit_ => "inherit"
    | `unset => "unset"
    },
  ));

let string_of_pointerEvents =
  fun
  | `auto => "auto"
  | `none => "none";

let pointerEvents = x =>
  `declaration(("pointerEvents", string_of_pointerEvents(x)));

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

let string_of_transform =
  fun
  | `translate(x, y) =>
    "translate("
    ++ Types.Length.toString(x)
    ++ ", "
    ++ Types.Length.toString(y)
    ++ ")"
  | `translate3d(x, y, z) => string_of_translate3d(x, y, z)
  | `translateX(x) => "translateX(" ++ Types.Length.toString(x) ++ ")"
  | `translateY(y) => "translateY(" ++ Types.Length.toString(y) ++ ")"
  | `translateZ(z) => "translateZ(" ++ Types.Length.toString(z) ++ ")"
  | `scale(x, y) => string_of_scale(x, y)
  | `scale3d(x, y, z) =>
    "scale3d("
    ++ Js.Float.toString(x)
    ++ ", "
    ++ Js.Float.toString(y)
    ++ ", "
    ++ Js.Float.toString(z)
    ++ ")"
  | `scaleX(x) => "scaleX(" ++ Js.Float.toString(x) ++ ")"
  | `scaleY(y) => "scaleY(" ++ Js.Float.toString(y) ++ ")"
  | `scaleZ(z) => "scaleZ(" ++ Js.Float.toString(z) ++ ")"
  | `rotate(a) => "rotate(" ++ Types.Angle.toString(a) ++ ")"
  | `rotate3d(x, y, z, a) =>
    "rotate3d("
    ++ Js.Float.toString(x)
    ++ ", "
    ++ Js.Float.toString(y)
    ++ ", "
    ++ Js.Float.toString(z)
    ++ ", "
    ++ Types.Angle.toString(a)
    ++ ")"
  | `rotateX(a) => "rotateX(" ++ Types.Angle.toString(a) ++ ")"
  | `rotateY(a) => "rotateY(" ++ Types.Angle.toString(a) ++ ")"
  | `rotateZ(a) => "rotateZ(" ++ Types.Angle.toString(a) ++ ")"
  | `skew(x, y) =>
    "skew("
    ++ Types.Angle.toString(x)
    ++ ", "
    ++ Types.Angle.toString(y)
    ++ ")"
  | `skewX(a) => "skewX(" ++ Types.Angle.toString(a) ++ ")"
  | `skewY(a) => "skewY(" ++ Types.Angle.toString(a) ++ ")"
  | `perspective(x) => "perspective(" ++ Js.Int.toString(x) ++ ")";

let transform = x => `declaration(("transform", string_of_transform(x)));

let transforms = xs =>
  `declaration((
    "transform",
    xs |> List.map(string_of_transform) |> joinLast(" "),
  ));

let transformOrigin = (x, y) =>
  `declaration((
    "transformOrigin",
    Types.Length.toString(x) ++ " " ++ Types.Length.toString(y),
  ));

let transformOrigin3d = (x, y, z) =>
  `declaration((
    "transformOrigin",
    Types.Length.toString(x)
    ++ " "
    ++ Types.Length.toString(y)
    ++ " "
    ++ Types.Length.toString(z)
    ++ " ",
  ));

let transformStyle = x =>
  `declaration((
    "transformStyle",
    switch (x) {
    | `preserve3d => "preserve-3d"
    | `flat => "flat"
    },
  ));

let perspective = x =>
  `declaration((
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
  ));

/**
* Transition
*/
module Transition = {
  type t = [ | `value(string)];

  let shorthand = (~duration=0, ~delay=0, ~timingFunction=`ease, property) =>
    `value(
      string_of_time(duration)
      ++ " "
      ++ timingFunction->Types.TimingFunction.toString
      ++ " "
      ++ string_of_time(delay)
      ++ " "
      ++ property,
    );

  let toString =
    fun
    | `value(v) => v;
};

let transitionValue = x =>
  `declaration(("transition", x->Transition.toString));

let transitionList = x =>
  `declaration((
    "transition",
    x->Belt.List.map(Transition.toString)->join(", "),
  ));
let transitions = transitionList;

let transition = (~duration=?, ~delay=?, ~timingFunction=?, property) =>
  transitionValue(
    Transition.shorthand(~duration?, ~delay?, ~timingFunction?, property),
  );

let transitionDelay = i =>
  `declaration(("transitionDelay", string_of_time(i)));

let transitionDuration = i =>
  `declaration(("transitionDuration", string_of_time(i)));

let transitionTimingFunction = x =>
  `declaration((
    "transitionTimingFunction",
    x->Types.TimingFunction.toString,
  ));

let transitionProperty = x => `declaration(("transitionProperty", x));

let perspectiveOrigin = (x, y) =>
  `declaration((
    "perspectiveOrigin",
    Types.Length.toString(x) ++ " " ++ Types.Length.toString(y),
  ));

/**
 * Animation
 */

type animationDirection = [
  | `normal
  | `reverse
  | `alternate
  | `alternateReverse
];

let string_of_animationDirection =
  fun
  | `normal => "normal"
  | `reverse => "reverse"
  | `alternate => "alternate"
  | `alternateReverse => "alternate-reverse";

type animationFillMode = [ | `none | `forwards | `backwards | `both];

let string_of_animationFillMode =
  fun
  | `none => "none"
  | `forwards => "forwards"
  | `backwards => "backwards"
  | `both => "both";

type animationIterationCount = [ | `infinite | `count(int)];

let string_of_animationIterationCount =
  fun
  | `infinite => "infinite"
  | `count(x) => Js.Int.toString(x);

type animationPlayState = [ | `paused | `running];

let string_of_animationPlayState =
  fun
  | `paused => "paused"
  | `running => "running";

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
      ++ timingFunction->Types.TimingFunction.toString
      ++ " "
      ++ string_of_time(delay)
      ++ " "
      ++ string_of_animationIterationCount(iterationCount)
      ++ " "
      ++ string_of_animationDirection(direction)
      ++ " "
      ++ string_of_animationFillMode(fillMode)
      ++ " "
      ++ string_of_animationPlayState(playState),
    );

  let toString =
    fun
    | `value(v) => v;
};

let animationValue = x => `declaration(("animation", x->Animation.toString));

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
  `declaration((
    "animation",
    x->Belt.List.map(Animation.toString)->join(", "),
  ));

let animationDelay = x =>
  `declaration(("animationDelay", string_of_time(x)));
let animationDirection = x =>
  `declaration(("animationDirection", string_of_animationDirection(x)));
let animationDuration = x =>
  `declaration(("animationDuration", string_of_time(x)));
let animationFillMode = x =>
  `declaration(("animationFillMode", string_of_animationFillMode(x)));
let animationIterationCount = x =>
  `declaration((
    "animationIterationCount",
    string_of_animationIterationCount(x),
  ));
let animationName = x => `declaration(("animationName", x));
let animationPlayState = x =>
  `declaration(("animationPlayState", string_of_animationPlayState(x)));
let animationTimingFunction = x =>
  `declaration(("animationTimingFunction", x->Types.TimingFunction.toString));

/**
 * Selectors
 */

let selector = (selector, rules) => `selector((selector, rules));

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

let media = (query, rules) => `selector(("@media " ++ query, rules));

/**
 * SVG
 */
module SVG = {
  let fill = color => `declaration(("fill", string_of_color(color)));
  let fillOpacity = opacity =>
    `declaration(("fillOpacity", Js.Float.toString(opacity)));
  let fillRule = x =>
    `declaration((
      "fillRule",
      switch (x) {
      | `evenodd => "evenodd"
      | `nonzero => "nonzero"
      },
    ));
  let stroke = color => `declaration(("stroke", string_of_color(color)));
  let strokeWidth = length =>
    `declaration(("strokeWidth", Types.Length.toString(length)));
  let strokeOpacity = opacity =>
    `declaration(("strokeOpacity", Js.Float.toString(opacity)));
  let strokeMiterlimit = x =>
    `declaration(("strokeMiterlimit", Js.Float.toString(x)));
  let strokeLinecap = x =>
    `declaration((
      "strokeLinecap",
      switch (x) {
      | `butt => "butt"
      | `round => "round"
      | `square => "square"
      },
    ));

  let strokeLinejoin = x =>
    `declaration((
      "strokeLinejoin",
      switch (x) {
      | `miter => "miter"
      | `round => "round"
      | `bevel => "bevel"
      },
    ));
  let stopColor = c => `declaration(("stopColor", string_of_color(c)));
  let stopOpacity = o => `declaration(("stopOpacity", Js.Float.toString(o)));
};
