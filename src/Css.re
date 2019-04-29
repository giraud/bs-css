include Css_Colors;

type rule = [
  | `selector(string, list(rule))
  | `declaration(string, string)
  | `animation(string)
  | `transition(string)
  | `shadow(string)
  | `textShadow(string)
];

type selector = [ | `selector(string, list(rule))];
type declaration = [ | `declaration(string, string)];

module Emotion = {
  type stylename = string;
  type cache;
  [@bs.module "emotion"] external _make: Js.Json.t => stylename = "css";
  [@bs.module "emotion"] external cache: cache = "";
  [@bs.module "emotion"] external injectGlobal: Js.Json.t => unit = "";
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
    | `shadow(value) => ("boxShadow", Js.Json.string(value))
    | `textShadow(value) => ("textShadow", Js.Json.string(value))
    | `transition(value) => ("transition", Js.Json.string(value))
    | `animation(value) => ("animation", Js.Json.string(value))
    }

  and makeJson = rules =>
    List.map(ruleToJs, rules)->Js.Dict.fromList->Js.Json.object_;

  let make = rules => rules->makeJson->_make;
};

let toJson = Emotion.makeJson;
let style = Emotion.make;

let join = (separator, strings) => {
  let rec run = (acc, strings) =>
    switch (strings) {
    | [] => acc
    | [x] => acc ++ x
    | [x, ...xs] => run(acc ++ x ++ separator, xs)
    };
  run("", strings);
};

let string_of_float = Js.Float.toString;
let string_of_int = Js.Int.toString;

module Converter = {
  let string_of_angle =
    fun
    | `deg(x) => string_of_float(x) ++ "deg"
    | `rad(x) => string_of_float(x) ++ "rad"
    | `grad(x) => string_of_float(x) ++ "grad"
    | `turn(x) => string_of_float(x) ++ "turn";

  let string_of_rgb = (r, g, b) =>
    "rgb("
    ++ string_of_int(r)
    ++ ", "
    ++ string_of_int(g)
    ++ ", "
    ++ string_of_int(b)
    ++ ")";

  let string_of_rgba = (r, g, b, a) =>
    "rgba("
    ++ string_of_int(r)
    ++ ", "
    ++ string_of_int(g)
    ++ ", "
    ++ string_of_int(b)
    ++ ", "
    ++ string_of_float(a)
    ++ ")";

  let string_of_hsl = (h, s, l) =>
    "hsl("
    ++ string_of_int(h)
    ++ ", "
    ++ string_of_int(s)
    ++ "%, "
    ++ string_of_int(l)
    ++ "%"
    ++ ")";

  let string_of_hsla = (h, s, l, a) =>
    "hsla("
    ++ string_of_int(h)
    ++ ", "
    ++ string_of_int(s)
    ++ "%, "
    ++ string_of_int(l)
    ++ "%, "
    ++ string_of_float(a)
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
    |> List.map(((i, c)) =>
         join(" ", [string_of_color(c), string_of_int(i) ++ "%"])
       )
    |> join(", ");

  let string_of_linearGradient = (angle, stops) =>
    "linear-gradient("
    ++ string_of_angle(angle)
    ++ ", "
    ++ string_of_stops(stops)
    ++ ")";

  let string_of_repeatingLinearGradient = (angle, stops) =>
    "repeating-linear-gradient("
    ++ string_of_angle(angle)
    ++ ", "
    ++ string_of_stops(stops)
    ++ ")";

  let rec string_of_length =
    fun
    | `calc(`add, a, b) =>
      "calc(" ++ string_of_length(a) ++ " + " ++ string_of_length(b) ++ ")"
    | `calc(`sub, a, b) =>
      "calc(" ++ string_of_length(a) ++ " - " ++ string_of_length(b) ++ ")"
    | `ch(x) => string_of_float(x) ++ "ch"
    | `cm(x) => string_of_float(x) ++ "cm"
    | `em(x) => string_of_float(x) ++ "em"
    | `ex(x) => string_of_float(x) ++ "ex"
    | `mm(x) => string_of_float(x) ++ "mm"
    | `percent(x) => string_of_float(x) ++ "%"
    | `pt(x) => string_of_int(x) ++ "pt"
    | `px(x) => string_of_int(x) ++ "px"
    | `pxFloat(x) => string_of_float(x) ++ "px"
    | `rem(x) => string_of_float(x) ++ "rem"
    | `vh(x) => string_of_float(x) ++ "vh"
    | `vmax(x) => string_of_float(x) ++ "vmax"
    | `vmin(x) => string_of_float(x) ++ "vmin"
    | `vw(x) => string_of_float(x) ++ "vw"
    | `zero => "0";

  let string_of_translate3d = (x, y, z) =>
    "translate3d("
    ++ string_of_length(x)
    ++ ", "
    ++ string_of_length(y)
    ++ ", "
    ++ string_of_length(z)
    ++ ")";

  let string_of_scale = (x, y) =>
    "scale(" ++ string_of_float(x) ++ ", " ++ string_of_float(y) ++ ")";

  let string_of_time = t => string_of_int(t) ++ "ms";

  let string_of_overflow =
    fun
    | `auto => "auto"
    | `scroll => "scroll"
    | `hidden => "hidden"
    | `visible => "visible";

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
      ++ join(
           ", ",
           [string_of_int(r), string_of_int(g), string_of_int(b)],
         )
      ++ ")"
    | `rgba(r, g, b, a) =>
      "rgba("
      ++ join(
           ", ",
           [
             string_of_int(r),
             string_of_int(g),
             string_of_int(b),
             string_of_float(a),
           ],
         )
      ++ ")"
    | `hsl(h, s, l) =>
      "hsl("
      ++ join(
           ", ",
           [
             string_of_int(h),
             string_of_int(s) ++ "%",
             string_of_int(l) ++ "%",
           ],
         )
      ++ ")"
    | `hsla(h, s, l, a) =>
      "hsla("
      ++ join(
           ", ",
           [
             string_of_int(h),
             string_of_int(s) ++ "%",
             string_of_int(l) ++ "%",
             string_of_float(a),
           ],
         )
      ++ ")"
    | `hex(s) => "#" ++ s
    | `transparent => "transparent"
    | `currentColor => "currentColor"
    | `linearGradient(angle, stops) =>
      "linear-gradient("
      ++ string_of_angle(angle)
      ++ ", "
      ++ string_of_stops(stops)
      ++ ")"
    | `repeatingLinearGradient(angle, stops) =>
      "repeating-linear-gradient("
      ++ string_of_angle(angle)
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
    | `num(n) => string_of_int(n)
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

  let string_of_fontStyle =
    fun
    | `normal => "normal"
    | `italic => "italic"
    | `oblique => "oblique"
    | `initial => "initial"
    | `inherit_ => "inherit"
    | `unset => "unset";

  let string_of_flex =
    fun
    | `auto => "auto"
    | `initial => "initial"
    | `none => "none"
    | `num(n) => string_of_float(n);
  let string_of_flexBasis =
    fun
    | `calc(`add, a, b) =>
      "calc(" ++ string_of_length(a) ++ " + " ++ string_of_length(b) ++ ")"
    | `calc(`sub, a, b) =>
      "calc(" ++ string_of_length(a) ++ " - " ++ string_of_length(b) ++ ")"
    | `ch(x) => string_of_float(x) ++ "ch"
    | `cm(x) => string_of_float(x) ++ "cm"
    | `em(x) => string_of_float(x) ++ "em"
    | `ex(x) => string_of_float(x) ++ "ex"
    | `mm(x) => string_of_float(x) ++ "mm"
    | `percent(x) => string_of_float(x) ++ "%"
    | `pt(x) => string_of_int(x) ++ "pt"
    | `px(x) => string_of_int(x) ++ "px"
    | `pxFloat(x) => string_of_float(x) ++ "px"
    | `rem(x) => string_of_float(x) ++ "rem"
    | `vh(x) => string_of_float(x) ++ "vh"
    | `vmax(x) => string_of_float(x) ++ "vmax"
    | `vmin(x) => string_of_float(x) ++ "vmin"
    | `vw(x) => string_of_float(x) ++ "vw"
    | `zero => "0"
    | `auto => "auto"
    | `fill => "fill"
    | `content => "content"
    | `maxContent => "max-content"
    | `minContent => "min-content"
    | `fitContent => "fit-content";
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

type animation = string;

let keyframes = frames => {
  let addStop = (dict, (stop, rules)) => {
    Js.Dict.set(dict, string_of_int(stop) ++ "%", Emotion.makeJson(rules));
    dict;
  };
  Emotion.makeKeyFrames @@ List.fold_left(addStop, Js.Dict.empty(), frames);
};

let d = (property, value) => `declaration((property, value));

let important = v =>
  switch (v) {
  | `declaration(name, value) => `declaration((name, value ++ " !important"))
  | _ => v
  };

let label = label => `declaration(("label", label));

/********************************************************
 ************************ VALUES ************************
 ********************************************************/
type cascading = [ | `initial | `inherit_ | `unset];

let initial = `initial;
let inherit_ = `inherit_;
let unset = `unset;

let rtl = `rtl;
let ltr = `ltr;

type angle = [ | `deg(float) | `rad(float) | `grad(float) | `turn(float)];

let deg = x => `deg(x);
let rad = x => `rad(x);
let grad = x => `grad(x);
let turn = x => `turn(x);

type color = [
  | `rgb(int, int, int)
  | `rgba(int, int, int, float)
  | `hsl(int, int, int)
  | `hsla(int, int, int, float)
  | `hex(string)
  | `transparent
  | `currentColor
];

let rgb = (r, g, b) => `rgb((r, g, b));
let rgba = (r, g, b, a) => `rgba((r, g, b, a));
let hsl = (h, s, l) => `hsl((h, s, l));
let hsla = (h, s, l, a) => `hsla((h, s, l, a));
let hex = x => `hex(x);

let currentColor = `currentColor;

type gradient = [
  | `linearGradient(angle, list((int, color)))
  | `repeatingLinearGradient(angle, list((int, color)))
  | `radialGradient(list((int, color)))
  | `repeatingRadialGradient(list((int, color)))
];

let linearGradient = (angle, stops) => `linearGradient((angle, stops));

let repeatingLinearGradient = (angle, stops) =>
  `repeatingLinearGradient((angle, stops));

let radialGradient = stops => `radialGradient(stops);

let repeatingRadialGradient = stops => `repeatingRadialGradient(stops);

/**
 * Units
 */

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
  | `pxFloat(float)
  | `rem(float)
  | `vh(float)
  | `vmax(float)
  | `vmin(float)
  | `vw(float)
  | `zero
];

let string_of_length_cascading =
  fun
  | `calc(`add, a, b) =>
    "calc(" ++ string_of_length(a) ++ " + " ++ string_of_length(b) ++ ")"
  | `calc(`sub, a, b) =>
    "calc(" ++ string_of_length(a) ++ " - " ++ string_of_length(b) ++ ")"
  | `ch(x) => string_of_float(x) ++ "ch"
  | `cm(x) => string_of_float(x) ++ "cm"
  | `em(x) => string_of_float(x) ++ "em"
  | `ex(x) => string_of_float(x) ++ "ex"
  | `mm(x) => string_of_float(x) ++ "mm"
  | `percent(x) => string_of_float(x) ++ "%"
  | `pt(x) => string_of_int(x) ++ "pt"
  | `px(x) => string_of_int(x) ++ "px"
  | `pxFloat(x) => string_of_float(x) ++ "px"
  | `rem(x) => string_of_float(x) ++ "rem"
  | `vh(x) => string_of_float(x) ++ "vh"
  | `vmax(x) => string_of_float(x) ++ "vmax"
  | `vmin(x) => string_of_float(x) ++ "vmin"
  | `vw(x) => string_of_float(x) ++ "vw"
  | `zero => "0"
  | `initial => "initial"
  | `inherit_ => "inherit"
  | `unset => "unset";

let ch = x => `ch(x);
let cm = x => `cm(x);
let em = x => `em(x);
let ex = x => `ex(x);
let fr = x => `fr(x);
let mm = x => `mm(x);
let pct = x => `percent(x);
let pt = x => `pt(x);
let px = x => `px(x);
let pxFloat = x => `pxFloat(x);
let rem = x => `rem(x);
let vh = x => `vh(x);
let vmax = x => `vmax(x);
let vmin = x => `vmin(x);
let vw = x => `vw(x);
let zero = `zero;

module Calc = {
  let (-) = (a, b) => `calc((`sub, a, b));
  let (+) = (a, b) => `calc((`add, a, b));
};
let size = (x, y) => `size((x, y));

let resize = x =>
  d(
    "resize",
    switch (x) {
    | `none => "none"
    | `both => "both"
    | `horizontal => "horizontal"
    | `vertical => "vertical"
    | `block => "block"
    | `inline => "inline"
    | `initial => "initial"
    | `inherit_ => "inherit"
    | `unset => "unset"
    },
  );

let horizontal = `horizontal;
let vertical = `vertical;

/**
 * Misc
 */

let absolute = `absolute;
let all = `all;
let auto = `auto;
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
let fixed = `fixed;
let flexBox = `flex;
let grid = `grid;
let inlineGrid = `inlineGrid;
let flexEnd = `flexEnd;
let flexStart = `flexStart;
let forwards = `forwards;
let hidden = `hidden;
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
let relative = `relative;
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
let scroll = `scroll;
let skew = (x, y) => `skew((x, y));
let skewX = a => `skewX(a);
let skewY = a => `skewY(a);
let solid = `solid;
let spaceAround = `spaceAround;
let spaceBetween = `spaceBetween;
let spaceEvenly = `spaceEvenly;
let static = `static;
let stepEnd = `stepEnd;
let steps = (i, dir) => `steps((i, dir));
let stepStart = `stepStart;
let sticky = `sticky;
let stretch = `stretch;
let text = `text;
let translate = (x, y) => `translate((x, y));
let translate3d = (x, y, z) => `translate3d((x, y, z));
let translateX = x => `translateX(x);
let translateY = y => `translateY(y);
let translateZ = z => `translateZ(z);
let url = x => `url(x);
let visible = `visible;
let wrap = `wrap;
let wrapReverse = `wrapReverse;

let inside = `inside;
let outside = `outside;

let italic = `italic;
let oblique = `oblique;

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

let unsafe = d;

/**
 * Layout
 */

let display = x =>
  d(
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
  );

let position = x =>
  d(
    "position",
    switch (x) {
    | `absolute => "absolute"
    | `static => "static"
    | `fixed => "fixed"
    | `relative => "relative"
    | `sticky => "sticky"
    | `initial => "initial"
    | `inherit_ => "inherit"
    | `unset => "unset"
    },
  );

let top = x => d("top", string_of_length(x));
let bottom = x => d("bottom", string_of_length(x));
let left = x => d("left", string_of_length(x));
let right = x => d("right", string_of_length(x));

let flex = x => d("flex", string_of_flex(x));
let flex3 = (~grow, ~shrink, ~basis) =>
  d(
    "flex",
    string_of_float(grow)
    ++ " "
    ++ string_of_float(shrink)
    ++ " "
    ++ string_of_flexBasis(basis),
  );
let flexGrow = x => d("flexGrow", string_of_float(x));
let flexShrink = x => d("flexShrink", string_of_float(x));
let flexBasis = x => d("flexBasis", string_of_flexBasis(x));

let flexDirection = x =>
  d(
    "flexDirection",
    switch (x) {
    | `row => "row"
    | `column => "column"
    | `rowReverse => "row-reverse"
    | `columnReverse => "column-reverse"
    },
  );

let flexWrap = x =>
  d(
    "flexWrap",
    switch (x) {
    | `nowrap => "nowrap"
    | `wrap => "wrap"
    | `wrapReverse => "wrap-reverse"
    },
  );

let order = x => d("order", string_of_int(x));

let string_of_margin =
  fun
  | `calc(`add, a, b) =>
    "calc(" ++ string_of_length(a) ++ " + " ++ string_of_length(b) ++ ")"
  | `calc(`sub, a, b) =>
    "calc(" ++ string_of_length(a) ++ " - " ++ string_of_length(b) ++ ")"
  | `ch(x) => string_of_float(x) ++ "ch"
  | `cm(x) => string_of_float(x) ++ "cm"
  | `em(x) => string_of_float(x) ++ "em"
  | `ex(x) => string_of_float(x) ++ "ex"
  | `mm(x) => string_of_float(x) ++ "mm"
  | `percent(x) => string_of_float(x) ++ "%"
  | `pt(x) => string_of_int(x) ++ "pt"
  | `px(x) => string_of_int(x) ++ "px"
  | `pxFloat(x) => string_of_float(x) ++ "px"
  | `rem(x) => string_of_float(x) ++ "rem"
  | `vh(x) => string_of_float(x) ++ "vh"
  | `vmax(x) => string_of_float(x) ++ "vmax"
  | `vmin(x) => string_of_float(x) ++ "vmin"
  | `vw(x) => string_of_float(x) ++ "vw"
  | `zero => "0"
  | `auto => "auto";

let margin = x => d("margin", string_of_margin(x));
let margin2 = (~v, ~h) =>
  d("margin", string_of_margin(v) ++ " " ++ string_of_margin(h));
let margin3 = (~top, ~h, ~bottom) =>
  d(
    "margin",
    string_of_margin(top)
    ++ " "
    ++ string_of_margin(h)
    ++ " "
    ++ string_of_margin(bottom),
  );
let margin4 = (~top, ~right, ~bottom, ~left) =>
  d(
    "margin",
    string_of_margin(top)
    ++ " "
    ++ string_of_margin(right)
    ++ " "
    ++ string_of_margin(bottom)
    ++ " "
    ++ string_of_margin(left),
  );
let marginLeft = x => d("marginLeft", string_of_margin(x));
let marginRight = x => d("marginRight", string_of_margin(x));
let marginTop = x => d("marginTop", string_of_margin(x));
let marginBottom = x => d("marginBottom", string_of_margin(x));

let padding = x => d("padding", string_of_length(x));
let padding2 = (~v, ~h) =>
  d("padding", string_of_length(v) ++ " " ++ string_of_length(h));
let padding3 = (~top, ~h, ~bottom) =>
  d(
    "padding",
    string_of_length(top)
    ++ " "
    ++ string_of_length(h)
    ++ " "
    ++ string_of_length(bottom),
  );
let padding4 = (~top, ~right, ~bottom, ~left) =>
  d(
    "padding",
    string_of_length(top)
    ++ " "
    ++ string_of_length(right)
    ++ " "
    ++ string_of_length(bottom)
    ++ " "
    ++ string_of_length(left),
  );
let paddingLeft = x => d("paddingLeft", string_of_length(x));
let paddingRight = x => d("paddingRight", string_of_length(x));
let paddingTop = x => d("paddingTop", string_of_length(x));
let paddingBottom = x => d("paddingBottom", string_of_length(x));

let string_of_minmax =
  fun
  | `auto => "auto"
  | `calc(`add, a, b) =>
    "calc(" ++ string_of_length(a) ++ " + " ++ string_of_length(b) ++ ")"
  | `calc(`sub, a, b) =>
    "calc(" ++ string_of_length(a) ++ " - " ++ string_of_length(b) ++ ")"
  | `ch(x) => string_of_float(x) ++ "ch"
  | `cm(x) => string_of_float(x) ++ "cm"
  | `em(x) => string_of_float(x) ++ "em"
  | `ex(x) => string_of_float(x) ++ "ex"
  | `mm(x) => string_of_float(x) ++ "mm"
  | `percent(x) => string_of_float(x) ++ "%"
  | `pt(x) => string_of_int(x) ++ "pt"
  | `px(x) => string_of_int(x) ++ "px"
  | `pxFloat(x) => string_of_float(x) ++ "px"
  | `rem(x) => string_of_float(x) ++ "rem"
  | `vh(x) => string_of_float(x) ++ "vh"
  | `vmax(x) => string_of_float(x) ++ "vmax"
  | `vmin(x) => string_of_float(x) ++ "vmin"
  | `vw(x) => string_of_float(x) ++ "vw"
  | `fr(x) => string_of_float(x) ++ "fr"
  | `zero => "0"
  | `minContent => "min-content"
  | `maxContent => "max-content";

let string_of_dimension =
  fun
  | `auto => "auto"
  | `none => "none"
  | `calc(`add, a, b) =>
    "calc(" ++ string_of_length(a) ++ " + " ++ string_of_length(b) ++ ")"
  | `calc(`sub, a, b) =>
    "calc(" ++ string_of_length(a) ++ " - " ++ string_of_length(b) ++ ")"
  | `ch(x) => string_of_float(x) ++ "ch"
  | `cm(x) => string_of_float(x) ++ "cm"
  | `em(x) => string_of_float(x) ++ "em"
  | `ex(x) => string_of_float(x) ++ "ex"
  | `mm(x) => string_of_float(x) ++ "mm"
  | `percent(x) => string_of_float(x) ++ "%"
  | `pt(x) => string_of_int(x) ++ "pt"
  | `px(x) => string_of_int(x) ++ "px"
  | `pxFloat(x) => string_of_float(x) ++ "px"
  | `rem(x) => string_of_float(x) ++ "rem"
  | `vh(x) => string_of_float(x) ++ "vh"
  | `vmax(x) => string_of_float(x) ++ "vmax"
  | `vmin(x) => string_of_float(x) ++ "vmin"
  | `vw(x) => string_of_float(x) ++ "vw"
  | `fr(x) => string_of_float(x) ++ "fr"
  | `zero => "0"
  | `minContent => "min-content"
  | `maxContent => "max-content"
  | `minmax(a, b) =>
    "minmax(" ++ string_of_minmax(a) ++ "," ++ string_of_minmax(b) ++ ")";

let width = x => d("width", string_of_dimension(x));
let height = x => d("height", string_of_dimension(x));
let minWidth = x => d("minWidth", string_of_dimension(x));
let maxWidth = x => d("maxWidth", string_of_dimension(x));
let minHeight = x => d("minHeight", string_of_dimension(x));
let maxHeight = x => d("maxHeight", string_of_dimension(x));

type gridAutoDirection = [
  | `column
  | `row
  | `columnDense
  | `rowDense
  | `initial
  | cascading
];

let gridAutoDirectionToJs =
  fun
  | `column => "column"
  | `row => "row"
  | `columnDense => "column dense"
  | `rowDense => "row dense"
  | `initial => "initial"
  | `inherit_ => "inherit"
  | `unset => "unset";

let gridAutoFlow = direction =>
  d("gridAutoFlow", gridAutoDirectionToJs(direction));

type repeatValue = [ | `autoFill | `autoFit | `num(int)];
let repeatValueToJs =
  fun
  | `autoFill => "auto-fill"
  | `autoFit => "auto-fit"
  | `num(x) => x->string_of_int;

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
    "calc(" ++ string_of_length(a) ++ " + " ++ string_of_length(b) ++ ")"
  | `calc(`sub, a, b) =>
    "calc(" ++ string_of_length(a) ++ " - " ++ string_of_length(b) ++ ")"
  | `ch(x) => string_of_float(x) ++ "ch"
  | `cm(x) => string_of_float(x) ++ "cm"
  | `em(x) => string_of_float(x) ++ "em"
  | `ex(x) => string_of_float(x) ++ "ex"
  | `mm(x) => string_of_float(x) ++ "mm"
  | `percent(x) => string_of_float(x) ++ "%"
  | `pt(x) => string_of_int(x) ++ "pt"
  | `px(x) => string_of_int(x) ++ "px"
  | `pxFloat(x) => string_of_float(x) ++ "px"
  | `rem(x) => string_of_float(x) ++ "rem"
  | `vh(x) => string_of_float(x) ++ "vh"
  | `vmax(x) => string_of_float(x) ++ "vmax"
  | `vmin(x) => string_of_float(x) ++ "vmin"
  | `vw(x) => string_of_float(x) ++ "vw"
  | `fr(x) => string_of_float(x) ++ "fr"
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
  d("gridTemplateColumns", string_of_dimensions(dimensions));

let gridTemplateRows = dimensions =>
  d("gridTemplateRows", string_of_dimensions(dimensions));

let gridAutoColumns = dimensions =>
  d("gridAutoColumns", string_of_dimension(dimensions));

let gridAutoRows = dimensions =>
  d("gridAutoRows", string_of_dimension(dimensions));

let gridColumn = (start, end') =>
  d("gridColumn", string_of_int(start) ++ " / " ++ string_of_int(end'));

let gridRow = (start, end') =>
  d("gridRow", string_of_int(start) ++ " / " ++ string_of_int(end'));
let gridColumnStart = n => d("gridColumnStart", string_of_int(n));
let gridColumnEnd = n => d("gridColumnEnd", string_of_int(n));
let gridRowStart = n => d("gridRowStart", string_of_int(n));
let gridRowEnd = n => d("gridRowEnd", string_of_int(n));
let gridColumnGap = n => d("gridColumnGap", string_of_length(n));
let gridRowGap = n => d("gridRowGap", string_of_length(n));
let gridGap = n => d("gridGap", string_of_length(n));

let string_of_align =
  fun
  | `baseline => "baseline"
  | `flexStart => "flex-start"
  | `flexEnd => "flex-end"
  | `center => "center"
  | `auto => "auto"
  | `stretch => "stretch";
let alignItems = x => d("alignItems", string_of_align(x));
let alignSelf = x => d("alignSelf", string_of_align(x));

let string_of_justify =
  fun
  | `flexStart => "flex-start"
  | `flexEnd => "flex-end"
  | `center => "center"
  | `spaceAround => "space-around"
  | `spaceBetween => "space-between"
  | `spaceEvenly => "space-evenly"
  | `stretch => "stretch";
let justifyContent = x => d("justifyContent", string_of_justify(x));
let justifySelf = x => d("justifySelf", string_of_justify(x));
let alignContent = x => d("alignContent", string_of_justify(x));

let boxSizing = x =>
  d(
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
  d(
    "float",
    switch (x) {
    | `left => "left"
    | `right => "right"
    | `none => "none"
    },
  );

let clear = x =>
  d(
    "clear",
    switch (x) {
    | `left => "left"
    | `right => "right"
    | `both => "both"
    },
  );

let overflow = x => d("overflow", string_of_overflow(x));
let overflowX = x => d("overflowX", string_of_overflow(x));
let overflowY = x => d("overflowY", string_of_overflow(x));

let zIndex = x => d("zIndex", string_of_int(x));

let contentRule = x => d("content", {j|"$x"|j});

let columnCount = x =>
  d(
    "columnCount",
    switch (x) {
    | `auto => "auto"
    | `count(v) => string_of_int(v)
    | `initial => "initial"
    | `inherit_ => "inherit"
    | `unset => "unset"
    },
  );

let direction = x =>
  d(
    "direction",
    switch (x) {
    | `ltr => "ltr"
    | `rtl => "rtl"
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
  | `blur(v) => "blur(" ++ string_of_length(v) ++ ")"
  | `brightness(v) => "brightness(" ++ string_of_float(v) ++ "%)"
  | `contrast(v) => "contrast(" ++ string_of_float(v) ++ "%)"
  | `dropShadow(a, b, c, d) =>
    "drop-shadow("
    ++ string_of_length(a)
    ++ " "
    ++ string_of_length(b)
    ++ " "
    ++ string_of_length(c)
    ++ " "
    ++ Converter.string_of_color(d)
    ++ ")"
  | `grayscale(v) => "grayscale(" ++ string_of_float(v) ++ "%)"
  | `hueRotate(v) => "hue-rotate(" ++ Converter.string_of_angle(v) ++ ")"
  | `invert(v) => "invert(" ++ string_of_float(v) ++ "%)"
  | `opacity(v) => "opacity(" ++ string_of_float(v) ++ "%)"
  | `saturate(v) => "saturate(" ++ string_of_float(v) ++ "%)"
  | `sepia(v) => "sepia(" ++ string_of_float(v) ++ "%)"
  | `url(v) => "url(" ++ v ++ ")"
  | `initial => "initial"
  | `inherit_ => "inherit"
  | `unset => "unset"
  | `none => "none";

let filter = x => d("filter", x |> List.map(string_of_filter) |> join(" "));
/**
 * Style
 */

let backfaceVisibility = x =>
  d("backfaceVisibility", string_of_visibility(x));

let visibility = x => d("visibility", string_of_visibility(x));

let boxShadow =
    (~x=zero, ~y=zero, ~blur=zero, ~spread=zero, ~inset=false, color) =>
  `shadow(
    string_of_length(x)
    ++ " "
    ++ string_of_length(y)
    ++ " "
    ++ string_of_length(blur)
    ++ " "
    ++ string_of_length(spread)
    ++ " "
    ++ string_of_color(color)
    ++ " "
    ++ (inset ? "inset" : ""),
  );

let string_of_shadow =
  fun
  | `shadow(s) => s;
let boxShadows = shadows =>
  d("boxShadow", shadows |> List.map(string_of_shadow) |> join(", "));

let string_of_borderstyle =
  fun
  | `solid => "solid"
  | `dashed => "dashed"
  | `dotted => "dotted"
  | `none => "none";

let border = (px, style, color) =>
  d(
    "border",
    string_of_length(px)
    ++ " "
    ++ string_of_borderstyle(style)
    ++ " "
    ++ string_of_color(color),
  );
let borderWidth = x => d("borderWidth", string_of_length(x));
let borderStyle = x => d("borderStyle", string_of_borderstyle(x));
let borderColor = x => d("borderColor", string_of_color(x));

let borderLeft = (px, style, color) =>
  d(
    "borderLeft",
    string_of_length(px)
    ++ " "
    ++ string_of_borderstyle(style)
    ++ " "
    ++ string_of_color(color),
  );
let borderLeftWidth = x => d("borderLeftWidth", string_of_length(x));
let borderLeftStyle = x => d("borderLeftStyle", string_of_borderstyle(x));
let borderLeftColor = x => d("borderLeftColor", string_of_color(x));

let borderRight = (px, style, color) =>
  d(
    "borderRight",
    string_of_length(px)
    ++ " "
    ++ string_of_borderstyle(style)
    ++ " "
    ++ string_of_color(color),
  );

let borderRightWidth = x => d("borderRightWidth", string_of_length(x));
let borderRightColor = x => d("borderRightColor", string_of_color(x));
let borderRightStyle = x => d("borderRightStyle", string_of_borderstyle(x));
let borderTop = (px, style, color) =>
  d(
    "borderTop",
    string_of_length(px)
    ++ " "
    ++ string_of_borderstyle(style)
    ++ " "
    ++ string_of_color(color),
  );

let borderTopWidth = x => d("borderTopWidth", string_of_length(x));
let borderTopStyle = x => d("borderTopStyle", string_of_borderstyle(x));
let borderTopColor = x => d("borderTopColor", string_of_color(x));

let borderBottom = (px, style, color) =>
  d(
    "borderBottom",
    string_of_length(px)
    ++ " "
    ++ string_of_borderstyle(style)
    ++ " "
    ++ string_of_color(color),
  );
let borderBottomWidth = x => d("borderBottomWidth", string_of_length(x));
let borderBottomStyle = x =>
  d("borderBottomStyle", string_of_borderstyle(x));
let borderBottomColor = x => d("borderBottomColor", string_of_color(x));

let borderRadius = i => d("borderRadius", string_of_length(i));
let borderTopLeftRadius = i => d("borderTopLeftRadius", string_of_length(i));
let borderTopRightRadius = i =>
  d("borderTopRightRadius", string_of_length(i));
let borderBottomLeftRadius = i =>
  d("borderBottomLeftRadius", string_of_length(i));
let borderBottomRightRadius = i =>
  d("borderBottomRightRadius", string_of_length(i));

let tableLayout = x =>
  d(
    "tableLayout",
    switch (x) {
    | `auto => "auto"
    | `fixed => "fixed"
    },
  );

let borderCollapse = x =>
  d(
    "borderCollapse",
    switch (x) {
    | `collapse => "collapse"
    | `separate => "separate"
    },
  );

let borderSpacing = i => d("borderSpacing", string_of_length(i));

let background = x => d("background", string_of_background(x));
let backgrounds = bg =>
  d("background", bg |> List.map(string_of_background) |> join(", "));
let backgroundColor = x => d("backgroundColor", string_of_color(x));
let backgroundImage = x =>
  d(
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
  d(
    "backgroundAttachment",
    switch (x) {
    | `scroll => "scroll"
    | `fixed => "fixed"
    | `local => "local"
    },
  );

let backgroundClip = x =>
  d(
    "backgroundClip",
    switch (x) {
    | `borderBox => "border-box"
    | `contentBox => "content-box"
    | `paddingBox => "padding-box"
    },
  );

let backgroundOrigin = x =>
  d(
    "backgroundOrigin",
    switch (x) {
    | `borderBox => "border-box"
    | `contentBox => "content-box"
    | `paddingBox => "padding-box"
    },
  );

let backgroundPosition = (x, y) =>
  d(
    "backgroundPosition",
    string_of_length(x) ++ " " ++ string_of_length(y),
  );

let backgroundRepeat = x =>
  d(
    "backgroundRepeat",
    switch (x) {
    | `repeat => "repeat"
    | `noRepeat => "no-repeat"
    | `repeatX => "repeat-x"
    | `repeatY => "repeat-y"
    },
  );

let backgroundSize = x =>
  d(
    "backgroundSize",
    switch (x) {
    | `size(x, y) => string_of_length(x) ++ " " ++ string_of_length(y)
    | `auto => "auto"
    | `cover => "cover"
    | `contain => "contain"
    },
  );

let cursor = x => d("cursor", string_of_cursor(x));

let clipPath = x =>
  d(
    "clipPath",
    switch (x) {
    | `url(url) => "url(" ++ url ++ ")"
    },
  );

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
  d(
    "listStyle",
    string_of_listStyleType(style)
    ++ " "
    ++ string_of_listStylePosition(pos)
    ++ " "
    ++ string_of_listStyleImage(img),
  );

let listStyleType = x => d("listStyleType", string_of_listStyleType(x));

let listStylePosition = x =>
  d("listStylePosition", string_of_listStylePosition(x));

let listStyleImage = x => d("listStyleImage", string_of_listStyleImage(x));

let opacity = x => d("opacity", string_of_float(x));

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
  d(
    "outline",
    string_of_length(size)
    ++ " "
    ++ string_of_outlineStyle(style)
    ++ " "
    ++ string_of_color(color),
  );

let outlineStyle = x => d("outlineStyle", string_of_outlineStyle(x));

let outlineWidth = x => d("outlineWidth", string_of_length(x));

let outlineColor = x => d("outlineColor", string_of_color(x));

let outlineOffset = x => d("outlineOffset", string_of_length(x));

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
type fontStyle = [ | `normal | `italic | `oblique];

let thin = `thin;
let extraLight = `extraLight;
let light = `light;
let medium = `medium;
let semiBold = `semiBold;
let bold = `bold;
let extraBold = `extraBold;
let lighter = `lighter;
let bolder = `bolder;

let color = x => d("color", string_of_color(x));

let fontFamily = x => d("fontFamily", x);

let fontSize = x => d("fontSize", string_of_length_cascading(x));

let fontVariant = x =>
  d(
    "fontVariant",
    switch (x) {
    | `normal => "normal"
    | `smallCaps => "small-caps"
    | `initial => "initial"
    | `inherit_ => "inherit"
    | `unset => "unset"
    },
  );

let fontStyle = x => d("fontStyle", string_of_fontStyle(x));
let fontWeight = x => d("fontWeight", string_of_fontWeight(x));

let fontFace = (~fontFamily, ~src, ~fontStyle=?, ~fontWeight=?, ()) => {
  let fontStyle =
    Js.Option.map((. value) => string_of_fontStyle(value), fontStyle);
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
  d(
    "lineHeight",
    switch (x) {
    | `normal => "normal"
    | `abs(x) => string_of_float(x)
    | `calc(`add, a, b) =>
      "calc(" ++ string_of_length(a) ++ " + " ++ string_of_length(b) ++ ")"
    | `calc(`sub, a, b) =>
      "calc(" ++ string_of_length(a) ++ " - " ++ string_of_length(b) ++ ")"
    | `ch(x) => string_of_float(x) ++ "ch"
    | `cm(x) => string_of_float(x) ++ "cm"
    | `em(x) => string_of_float(x) ++ "em"
    | `ex(x) => string_of_float(x) ++ "ex"
    | `mm(x) => string_of_float(x) ++ "mm"
    | `percent(x) => string_of_float(x) ++ "%"
    | `pt(x) => string_of_int(x) ++ "pt"
    | `px(x) => string_of_int(x) ++ "px"
    | `pxFloat(x) => string_of_float(x) ++ "px"
    | `rem(x) => string_of_float(x) ++ "rem"
    | `vh(x) => string_of_float(x) ++ "vh"
    | `vmax(x) => string_of_float(x) ++ "vmax"
    | `vmin(x) => string_of_float(x) ++ "vmin"
    | `vw(x) => string_of_float(x) ++ "vw"
    | `auto => "auto"
    | `zero => "0"
    | `initial => "initial"
    | `inherit_ => "inherit"
    | `unset => "unset"
    },
  );

let letterSpacing = x =>
  d(
    "letterSpacing",
    switch (x) {
    | `normal => "normal"
    | `calc(`add, a, b) =>
      "calc(" ++ string_of_length(a) ++ " + " ++ string_of_length(b) ++ ")"
    | `calc(`sub, a, b) =>
      "calc(" ++ string_of_length(a) ++ " - " ++ string_of_length(b) ++ ")"
    | `ch(x) => string_of_float(x) ++ "ch"
    | `cm(x) => string_of_float(x) ++ "cm"
    | `em(x) => string_of_float(x) ++ "em"
    | `ex(x) => string_of_float(x) ++ "ex"
    | `mm(x) => string_of_float(x) ++ "mm"
    | `percent(x) => string_of_float(x) ++ "%"
    | `pt(x) => string_of_int(x) ++ "pt"
    | `px(x) => string_of_int(x) ++ "px"
    | `pxFloat(x) => string_of_float(x) ++ "px"
    | `rem(x) => string_of_float(x) ++ "rem"
    | `vh(x) => string_of_float(x) ++ "vh"
    | `vmax(x) => string_of_float(x) ++ "vmax"
    | `vmin(x) => string_of_float(x) ++ "vmin"
    | `vw(x) => string_of_float(x) ++ "vw"
    | `auto => "auto"
    | `zero => "0"
    | `initial => "initial"
    | `inherit_ => "inherit"
    | `unset => "unset"
    },
  );

let textAlign = x =>
  d(
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
  d(
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

let textDecorationColor = x => d("textDecorationColor", string_of_color(x));

let textDecorationStyle = x =>
  d(
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

let textIndent = x => d("textIndent", string_of_length(x));

let textOverflow = x =>
  d(
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

let textShadow = (~x=zero, ~y=zero, ~blur=zero, color) =>
  `textShadow(
    string_of_length(x)
    ++ " "
    ++ string_of_length(y)
    ++ " "
    ++ string_of_length(blur)
    ++ " "
    ++ string_of_color(color),
  );

let string_of_textShadow =
  fun
  | `textShadow(s) => s;
let textShadows = textShadows =>
  d(
    "textShadow",
    textShadows |> List.map(string_of_textShadow) |> join(", "),
  );

let textTransform = x =>
  d(
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
  d(
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

let verticalAlign = x =>
  d(
    "verticalAlign",
    switch (x) {
    | `baseline => "baseline"
    | `sub => "sub"
    | `super => "super"
    | `top => "top"
    | `textTop => "text-top"
    | `middle => "middle"
    | `bottom => "bottom"
    | `textBottom => "text-bottom"
    | `calc(`add, a, b) =>
      "calc(" ++ string_of_length(a) ++ " + " ++ string_of_length(b) ++ ")"
    | `calc(`sub, a, b) =>
      "calc(" ++ string_of_length(a) ++ " - " ++ string_of_length(b) ++ ")"
    | `ch(x) => string_of_float(x) ++ "ch"
    | `cm(x) => string_of_float(x) ++ "cm"
    | `em(x) => string_of_float(x) ++ "em"
    | `ex(x) => string_of_float(x) ++ "ex"
    | `mm(x) => string_of_float(x) ++ "mm"
    | `percent(x) => string_of_float(x) ++ "%"
    | `pt(x) => string_of_int(x) ++ "pt"
    | `px(x) => string_of_int(x) ++ "px"
    | `pxFloat(x) => string_of_float(x) ++ "px"
    | `rem(x) => string_of_float(x) ++ "rem"
    | `vh(x) => string_of_float(x) ++ "vh"
    | `vmax(x) => string_of_float(x) ++ "vmax"
    | `vmin(x) => string_of_float(x) ++ "vmin"
    | `vw(x) => string_of_float(x) ++ "vw"
    | `auto => "auto"
    | `zero => "0"
    | `initial => "initial"
    | `inherit_ => "inherit"
    | `unset => "unset"
    },
  );

let whiteSpace = x =>
  d(
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
  d(
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
  d(
    "wordSpacing",
    switch (x) {
    | `normal => "normal"
    | `calc(`add, a, b) =>
      "calc(" ++ string_of_length(a) ++ " + " ++ string_of_length(b) ++ ")"
    | `calc(`sub, a, b) =>
      "calc(" ++ string_of_length(a) ++ " - " ++ string_of_length(b) ++ ")"
    | `ch(x) => string_of_float(x) ++ "ch"
    | `cm(x) => string_of_float(x) ++ "cm"
    | `em(x) => string_of_float(x) ++ "em"
    | `ex(x) => string_of_float(x) ++ "ex"
    | `mm(x) => string_of_float(x) ++ "mm"
    | `percent(x) => string_of_float(x) ++ "%"
    | `pt(x) => string_of_int(x) ++ "pt"
    | `px(x) => string_of_int(x) ++ "px"
    | `pxFloat(x) => string_of_float(x) ++ "px"
    | `rem(x) => string_of_float(x) ++ "rem"
    | `vh(x) => string_of_float(x) ++ "vh"
    | `vmax(x) => string_of_float(x) ++ "vmax"
    | `vmin(x) => string_of_float(x) ++ "vmin"
    | `vw(x) => string_of_float(x) ++ "vw"
    | `auto => "auto"
    | `zero => "0"
    | `initial => "initial"
    | `inherit_ => "inherit"
    | `unset => "unset"
    },
  );

let wordWrap = x =>
  d(
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

let pointerEvents = x => d("pointerEvents", string_of_pointerEvents(x));

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
    "translate(" ++ string_of_length(x) ++ ", " ++ string_of_length(y) ++ ")"
  | `translate3d(x, y, z) => string_of_translate3d(x, y, z)
  | `translateX(x) => "translateX(" ++ string_of_length(x) ++ ")"
  | `translateY(y) => "translateY(" ++ string_of_length(y) ++ ")"
  | `translateZ(z) => "translateZ(" ++ string_of_length(z) ++ ")"
  | `scale(x, y) => string_of_scale(x, y)
  | `scale3d(x, y, z) =>
    "scale3d("
    ++ string_of_float(x)
    ++ ", "
    ++ string_of_float(y)
    ++ ", "
    ++ string_of_float(z)
    ++ ")"
  | `scaleX(x) => "scaleX(" ++ string_of_float(x) ++ ")"
  | `scaleY(y) => "scaleY(" ++ string_of_float(y) ++ ")"
  | `scaleZ(z) => "scaleZ(" ++ string_of_float(z) ++ ")"
  | `rotate(a) => "rotate(" ++ string_of_angle(a) ++ ")"
  | `rotate3d(x, y, z, a) =>
    "rotate3d("
    ++ string_of_float(x)
    ++ ", "
    ++ string_of_float(y)
    ++ ", "
    ++ string_of_float(z)
    ++ ", "
    ++ string_of_angle(a)
    ++ ")"
  | `rotateX(a) => "rotateX(" ++ string_of_angle(a) ++ ")"
  | `rotateY(a) => "rotateY(" ++ string_of_angle(a) ++ ")"
  | `rotateZ(a) => "rotateZ(" ++ string_of_angle(a) ++ ")"
  | `skew(x, y) =>
    "skew(" ++ string_of_angle(x) ++ ", " ++ string_of_angle(y) ++ ")"
  | `skewX(a) => "skewX(" ++ string_of_angle(a) ++ ")"
  | `skewY(a) => "skewY(" ++ string_of_angle(a) ++ ")"
  | `perspective(x) => "perspective(" ++ string_of_int(x) ++ ")";

let transform = x => d("transform", string_of_transform(x));

let transforms = xs =>
  d("transform", xs |> List.map(string_of_transform) |> join(" "));

let transformOrigin = (x, y) =>
  d("transformOrigin", string_of_length(x) ++ " " ++ string_of_length(y));

let transformOrigin3d = (x, y, z) =>
  d(
    "transformOrigin",
    string_of_length(x)
    ++ " "
    ++ string_of_length(y)
    ++ " "
    ++ string_of_length(z)
    ++ " ",
  );

let transformStyle = x =>
  d(
    "transformStyle",
    switch (x) {
    | `preserve3d => "preserve-3d"
    | `flat => "flat"
    },
  );

let perspective = x =>
  d(
    "perspective",
    switch (x) {
    | `none => "none"
    | `calc(`add, a, b) =>
      "calc(" ++ string_of_length(a) ++ " + " ++ string_of_length(b) ++ ")"
    | `calc(`sub, a, b) =>
      "calc(" ++ string_of_length(a) ++ " - " ++ string_of_length(b) ++ ")"
    | `ch(x) => string_of_float(x) ++ "ch"
    | `cm(x) => string_of_float(x) ++ "cm"
    | `em(x) => string_of_float(x) ++ "em"
    | `ex(x) => string_of_float(x) ++ "ex"
    | `mm(x) => string_of_float(x) ++ "mm"
    | `percent(x) => string_of_float(x) ++ "%"
    | `pt(x) => string_of_int(x) ++ "pt"
    | `px(x) => string_of_int(x) ++ "px"
    | `pxFloat(x) => string_of_float(x) ++ "px"
    | `rem(x) => string_of_float(x) ++ "rem"
    | `vh(x) => string_of_float(x) ++ "vh"
    | `vmax(x) => string_of_float(x) ++ "vmax"
    | `vmin(x) => string_of_float(x) ++ "vmin"
    | `vw(x) => string_of_float(x) ++ "vw"
    | `zero => "0"
    },
  );

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

let string_of_timingFunction =
  fun
  | `linear => "linear"
  | `ease => "ease"
  | `easeIn => "ease-out"
  | `easeOut => "ease-out"
  | `easeInOut => "ease-in-out"
  | `stepStart => "step-start"
  | `stepEnd => "step-end"
  | `steps(i, `start) => "steps(" ++ string_of_int(i) ++ ", start)"
  | `steps(i, `end_) => "steps(" ++ string_of_int(i) ++ ", end)"
  | `cubicBezier(a, b, c, d) =>
    "cubic-bezier("
    ++ string_of_float(a)
    ++ ", "
    ++ string_of_float(b)
    ++ ", "
    ++ string_of_float(c)
    ++ ", "
    ++ string_of_float(d)
    ++ ")";

let transition = (~duration=0, ~delay=0, ~timingFunction=`ease, property) =>
  `transition(
    string_of_time(duration)
    ++ " "
    ++ string_of_timingFunction(timingFunction)
    ++ " "
    ++ string_of_time(delay)
    ++ " "
    ++ property,
  );

let transitions = xs =>
  d(
    "transition",
    xs
    |> List.map(
         fun
         | `transition(s) => s,
       )
    |> join(", "),
  );

let transitionDelay = i => d("transitionDelay", string_of_time(i));

let transitionDuration = i => d("transitionDuration", string_of_time(i));

let transitionTimingFunction = x =>
  d("transitionTimingFunction", string_of_timingFunction(x));

let transitionProperty = x => d("transitionProperty", x);

let perspectiveOrigin = (x, y) =>
  d("perspectiveOrigin", string_of_length(x) ++ " " ++ string_of_length(y));

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
  | `count(x) => string_of_int(x);

type animationPlayState = [ | `paused | `running];

let string_of_animationPlayState =
  fun
  | `paused => "paused"
  | `running => "running";

let animation =
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
  `animation(
    name
    ++ " "
    ++ string_of_time(duration)
    ++ " "
    ++ string_of_timingFunction(timingFunction)
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

let string_of_animation =
  fun
  | `animation(s) => s;
let animations = xs =>
  d("animation", xs |> List.map(string_of_animation) |> join(", "));

let animationDelay = x => d("animationDelay", string_of_time(x));
let animationDirection = x =>
  d("animationDirection", string_of_animationDirection(x));
let animationDuration = x => d("animationDuration", string_of_time(x));
let animationFillMode = x =>
  d("animationFillMode", string_of_animationFillMode(x));
let animationIterationCount = x =>
  d("animationIterationCount", string_of_animationIterationCount(x));
let animationName = x => d("animationName", x);
let animationPlayState = x =>
  d("animationPlayState", string_of_animationPlayState(x));
let animationTimingFunction = x =>
  d("animationTimingFunction", string_of_timingFunction(x));

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
  let fill = color => d("fill", string_of_color(color));
  let fillOpacity = opacity => d("fillOpacity", string_of_float(opacity));
  let fillRule = x =>
    d(
      "fillRule",
      switch (x) {
      | `evenodd => "evenodd"
      | `nonzero => "nonzero"
      },
    );
  let stroke = color => d("stroke", string_of_color(color));
  let strokeWidth = length => d("strokeWidth", string_of_length(length));
  let strokeOpacity = opacity =>
    d("strokeOpacity", string_of_float(opacity));
  let strokeMiterlimit = x => d("strokeMiterlimit", string_of_float(x));
  let strokeLinecap = x =>
    d(
      "strokeLinecap",
      switch (x) {
      | `butt => "butt"
      | `round => "round"
      | `square => "square"
      },
    );

  let strokeLinejoin = x =>
    d(
      "strokeLinejoin",
      switch (x) {
      | `miter => "miter"
      | `round => "round"
      | `bevel => "bevel"
      },
    );
  let stopColor = c => d("stopColor", string_of_color(c));
  let stopOpacity = o => d("stopOpacity", string_of_float(o));
};
