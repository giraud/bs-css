type css = string;

type rule =
  | Property(string, string)
  | Selector(string, list(rule));

type angle = string;

module Glamor = {
  [@bs.module "glamor"] external make : Js.Json.t => css = "css";
  [@bs.scope "css"] [@bs.module "glamor"]
  external makeGlobal : (string, Js.Json.t) => unit = "global";
  [@bs.scope "css"] [@bs.module "glamor"]
  external makeKeyFrames : Js.Dict.t(Js.Json.t) => string = "keyframes";
  let merge: list(string) => string = [%bs.raw
    {|
      function (styles) {
          const glamor = require('glamor');
          return glamor.css.apply(glamor, styles)
      }
  |}
  ];
};

let rec makeDict = ruleset => {
  let toJs = rule =>
    switch rule {
    | Property(name, value) => (name, Js.Json.string(value))
    | Selector(name, ruleset) => (name, makeDict(ruleset))
    };
  ruleset |> List.map(toJs) |> Js.Dict.fromList |> Js.Json.object_;
};

let join = (sep, strings) => {
  let rec j = acc =>
    fun
    | [] => acc
    | [x] => acc ++ x
    | [x, y, ...strings] => j(acc ++ x ++ sep, [y, ...strings]);
  j("", strings);
};

let intProp = (name, v) => Property(name, string_of_int(v));

let stringProp = (name, v) => Property(name, v);

let style = rules => makeDict(rules) |> Glamor.make;

let global = (selector, rules) =>
  makeDict(rules) |> Glamor.makeGlobal(selector);

let keyframes = keyframes =>
  keyframes
  |> List.map(((k, ruleset)) => (k, makeDict(ruleset)))
  |> Js.Dict.fromList
  |> Glamor.makeKeyFrames;

let merge = Glamor.merge;

let empty = style([]);

let important = v =>
  switch v {
  | Property(name, value) => Property(name, value ++ " !important")
  | _ => v
  };


/*********
 * COLORS
 **********/
type color = string;

let rgb = (r, g, b) => {j|rgb($r, $g, $b)|j};

let rgba = (r, g, b, a) => {j|rgba($r, $g, $b, $a)|j};

let hsl = (h, s, l) => {j|hsl($h, $s%, $l%)|j};

let hsla = (h, s, l, a) => {j|hsl($h, $s%, $l%, $a)|j};

let currentColor = "currentColor";

let transparent = "transparent";

let aliceblue = "aliceblue";

let antiquewhite = "antiquewhite";

let aqua = "aqua";

let aquamarine = "aquamarine";

let azure = "azure";

let beige = "beige";

let bisque = "bisque";

let black = "black";

let blanchedalmond = "blanchedalmond";

let blue = "blue";

let blueviolet = "blueviolet";

let brown = "brown";

let burlywood = "burlywood";

let cadetblue = "cadetblue";

let chartreuse = "chartreuse";

let chocolate = "chocolate";

let coral = "coral";

let cornflowerblue = "cornflowerblue";

let cornsilk = "cornsilk";

let crimson = "crimson";

let cyan = "cyan";

let darkblue = "darkblue";

let darkcyan = "darkcyan";

let darkgoldenrod = "darkgoldenrod";

let darkgray = "darkgray";

let darkgrey = "darkgrey";

let darkgreen = "darkgreen";

let darkkhaki = "darkkhaki";

let darkmagenta = "darkmagenta";

let darkolivegreen = "darkolivegreen";

let darkorange = "darkorange";

let darkorchid = "darkorchid";

let darkred = "darkred";

let darksalmon = "darksalmon";

let darkseagreen = "darkseagreen";

let darkslateblue = "darkslateblue";

let darkslategray = "darkslategray";

let darkslategrey = "darkslategrey";

let darkturquoise = "darkturquoise";

let darkviolet = "darkviolet";

let deeppink = "deeppink";

let deepskyblue = "deepskyblue";

let dimgray = "dimgray";

let dimgrey = "dimgrey";

let dodgerblue = "dodgerblue";

let firebrick = "firebrick";

let floralwhite = "floralwhite";

let forestgreen = "forestgreen";

let fuchsia = "fuchsia";

let gainsboro = "gainsboro";

let ghostwhite = "ghostwhite";

let gold = "gold";

let goldenrod = "goldenrod";

let gray = "gray";

let grey = "grey";

let green = "green";

let greenyellow = "greenyellow";

let honeydew = "honeydew";

let hotpink = "hotpink";

let indianred = "indianred";

let indigo = "indigo";

let ivory = "ivory";

let khaki = "khaki";

let lavender = "lavender";

let lavenderblush = "lavenderblush";

let lawngreen = "lawngreen";

let lemonchiffon = "lemonchiffon";

let lightblue = "lightblue";

let lightcoral = "lightcoral";

let lightcyan = "lightcyan";

let lightgoldenrodyellow = "lightgoldenrodyellow";

let lightgray = "lightgray";

let lightgrey = "lightgrey";

let lightgreen = "lightgreen";

let lightpink = "lightpink";

let lightsalmon = "lightsalmon";

let lightseagreen = "lightseagreen";

let lightskyblue = "lightskyblue";

let lightslategray = "lightslategray";

let lightslategrey = "lightslategrey";

let lightsteelblue = "lightsteelblue";

let lightyellow = "lightyellow";

let lime = "lime";

let limegreen = "limegreen";

let linen = "linen";

let magenta = "magenta";

let maroon = "maroon";

let mediumaquamarine = "mediumaquamarine";

let mediumblue = "mediumblue";

let mediumorchid = "mediumorchid";

let mediumpurple = "mediumpurple";

let mediumseagreen = "mediumseagreen";

let mediumslateblue = "mediumslateblue";

let mediumspringgreen = "mediumspringgreen";

let mediumturquoise = "mediumturquoise";

let mediumvioletred = "mediumvioletred";

let midnightblue = "midnightblue";

let mintcream = "mintcream";

let mistyrose = "mistyrose";

let moccasin = "moccasin";

let navajowhite = "navajowhite";

let navy = "navy";

let oldlace = "oldlace";

let olive = "olive";

let olivedrab = "olivedrab";

let orange = "orange";

let orangered = "orangered";

let orchid = "orchid";

let palegoldenrod = "palegoldenrod";

let palegreen = "palegreen";

let paleturquoise = "paleturquoise";

let palevioletred = "palevioletred";

let papayawhip = "papayawhip";

let peachpuff = "peachpuff";

let peru = "peru";

let pink = "pink";

let plum = "plum";

let powderblue = "powderblue";

let purple = "purple";

let red = "red";

let rosybrown = "rosybrown";

let royalblue = "royalblue";

let saddlebrown = "saddlebrown";

let salmon = "salmon";

let sandybrown = "sandybrown";

let seagreen = "seagreen";

let seashell = "seashell";

let sienna = "sienna";

let silver = "silver";

let skyblue = "skyblue";

let slateblue = "slateblue";

let slategray = "slategray";

let slategrey = "slategrey";

let snow = "snow";

let springgreen = "springgreen";

let steelblue = "steelblue";

let tan = "tan";

let teal = "teal";

let thistle = "thistle";

let tomato = "tomato";

let turquoise = "turquoise";

let violet = "violet";

let wheat = "wheat";

let white = "white";

let whitesmoke = "whitesmoke";

let yellow = "yellow";

let yellowgreen = "yellowgreen";

let hex = v => "#" ++ v;


/*********
 * UNITS
 **********/
type cssunit = string;

let px = i => {j|$(i)px|j};

let pct = i => {j|$(i)%|j};

let rem = i => {j|$(i)rem|j};

let em = i => {j|$(i)em|j};

let cm = i => {j|$(i)cm|j};

let mm = i => {j|$(i)mm|j};

let vh = i => {j|$(i)vh|j};

let vw = i => {j|$(i)vw|j};

let zero = "0";

let auto = "auto";


/*********
 * ANGLE
 **********/
let rad = i => {j|$(i)rad|j};

let deg = i => {j|$(i)deg|j};

let turn = i => {j|$(i)turn|j};


/*********
 * CSS RULES
 **********/
let unsafe = (name, value) => Property(name, Obj.magic(value));

type visibility =
  | Visible
  | Hidden;

let visibility = v =>
  Property(
    "visibility",
    switch v {
    | Hidden => "hidden"
    | Visible => "visible"
    }
  );

let opacity = v => Property("opacity", {j|$v|j});

/* BACKGROUND */
let backgroundImage = url => Property("backgroundImage", "url(" ++ url ++ ")");

type backgroundAttachment =
  | Scroll
  | Fixed
  | Local
  | Initial;

let backgroundAttachment = v =>
  Property(
    "backgroundAttachment",
    switch v {
    | Scroll => "scroll"
    | Fixed => "fixed"
    | Local => "local"
    | Initial => "initial"
    }
  );

let backgroundColor = stringProp("backgroundColor");

type backgroundSize =
  | Cover
  | Contain
  | Width(cssunit)
  | Height(cssunit)
  | Custom(cssunit, cssunit);

let backgroundSize = v =>
  Property(
    "backgroundSize",
    switch v {
    | Cover => "cover"
    | Contain => "contain"
    | Width(v) => v
    | Height(v) => "auto " ++ v
    | Custom(v, h) => v ++ " " ++ h
    }
  );

type backgroundPosition =
  | Top
  | Bottom
  | Left
  | Right
  | Center;

let backgroundPosition = v =>
  Property(
    "backgroundPosition",
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

let backgroundRepeat = v =>
  Property(
    "backgroundRepeat",
    switch v {
    | RepeatX => "repeat-x"
    | RepeatY => "repeat-y"
    | Repeat => "repeat"
    | Space => "space"
    | Round => "round"
    | NoRepeat => "no-repeat"
    }
  );

type background =
  | None
  | Color(color)
  | Image(string);

let background = v =>
  Property(
    "background",
    switch v {
    | None => "none"
    | Color(color) => color
    | Image(url) => {j|url($url)|j}
    }
  );

/* TEXT */
let color = stringProp("color");

let fontFamily = stringProp("fontFamily");

let fontSize = stringProp("fontSize");

type fontStyle =
  | Normal
  | Italic
  | Oblique;

let fontStyle = v =>
  Property(
    "fontStyle",
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

let fontWeight = v =>
  Property(
    "fontWeight",
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

let textShadow = (x, y, color) =>
  Property("textShadow", {j|$(x) $(y) $(color)|j});

let textIndent = stringProp("textIndent");

type textAlign =
  | Auto
  | Left
  | Right
  | Center
  | Justify;

let textAlign = v =>
  Property(
    "textAlign",
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
  | Underline(color)
  | UnderlineWavy(color);

let textDecoration = v =>
  Property(
    "textDecoration",
    switch v {
    | None => "none"
    | Underline(color) => "underline " ++ color
    | UnderlineWavy(color) => "underline wavy " ++ color
    }
  );

type textTransform =
  | None
  | Uppercase
  | Lowercase
  | Capitalize
  | FullWidth;

let textTransform = v =>
  Property(
    "textTransform",
    switch v {
    | None => "none"
    | Uppercase => "uppercase"
    | Lowercase => "lowercase"
    | Capitalize => "capitalize"
    | FullWidth => "full-width"
    }
  );

let lineHeight = stringProp("lineHeight");

let letterSpacing = stringProp("letterSpacing");

/* BORDER */
type borderStyle =
  | None
  | Hidden
  | Solid
  | Dotted
  | Dashed
  | Double;

let borderStyleToString = s =>
  switch s {
  | None => "none"
  | Hidden => "hidden"
  | Solid => "solid"
  | Dotted => "dotted"
  | Dashed => "dashed"
  | Double => "double"
  };

let borderProp = (name, width, style, color) => {
  let styleString = borderStyleToString(style);
  Property(name, {j|$(width) $(styleString) $(color) |j});
};

let border = borderProp("border");

let borderTop = borderProp("borderTop");

let borderBottom = borderProp("borderBottom");

let borderLeft = borderProp("borderLeft");

let borderRight = borderProp("borderRight");

let borderWidth = stringProp("borderWidth");

let borderTopWidth = stringProp("borderTopWidth");

let borderBottomWidth = stringProp("borderBottomWidth");

let borderLeftWidth = stringProp("borderLeftWidth");

let borderRightWidth = stringProp("borderRightWidth");

let borderStyle = style => Property("borderStyle", borderStyleToString(style));

let borderTopStyle = style =>
  Property("borderTopStyle", borderStyleToString(style));

let borderBottomStyle = style =>
  Property("borderBottomStyle", borderStyleToString(style));

let borderLeftStyle = style =>
  Property("borderLeftStyle", borderStyleToString(style));

let borderRightStyle = style =>
  Property("borderRightStyle", borderStyleToString(style));

let borderColor = color => Property("borderColor", color);

let borderTopColor = color => Property("borderTopColor", color);

let borderBottomColor = color => Property("borderBottomColor", color);

let borderLeftColor = color => Property("borderLeftColor", color);

let borderRightColor = color => Property("borderRightColor", color);

let borderRadius = stringProp("borderRadius");

let borderTopRightRadius = stringProp("borderTopRightRadius");

let borderTopLeftRadius = stringProp("borderTopLeftRadius");

let borderBottomRightRadius = stringProp("borderBottomRightRadius");

let borderBottomLeftRadius = stringProp("borderBottomLeftRadius");

/* LAYOUT */
let width = stringProp("width");

let minWidth = stringProp("minWidth");

let maxWidth = stringProp("maxWidth");

let height = stringProp("height");

let minHeight = stringProp("minHeight");

let maxHeight = stringProp("maxHeight");

let left = stringProp("left");

let right = stringProp("right");

let top = stringProp("top");

let bottom = stringProp("bottom");

let margin = stringProp("margin");

let marginLeft = stringProp("marginLeft");

let marginRight = stringProp("marginRight");

let marginTop = stringProp("marginTop");

let marginBottom = stringProp("marginBottom");

let padding = stringProp("padding");

let paddingLeft = stringProp("paddingLeft");

let paddingRight = stringProp("paddingRight");

let paddingTop = stringProp("paddingTop");

let paddingBottom = stringProp("paddingBottom");

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

let display = v =>
  Property(
    "display",
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

let position = v =>
  Property(
    "position",
    switch v {
    | Static => "static"
    | Relative => "relative"
    | Absolute => "absolute"
    | Fixed => "fixed"
    | Sticky => "sticky"
    }
  );

type boxSizing =
  | BorderBox
  | ContentBox;

let boxSizing = v =>
  Property(
    "boxSizing",
    switch v {
    | BorderBox => "border-box"
    | ContentBox => "content-box"
    }
  );

type overflow =
  | Visible
  | Hidden
  | Scroll
  | Auto;

let overflow = o =>
  Property(
    "overflow",
    switch o {
    | Visible => "visible"
    | Hidden => "hidden"
    | Auto => "auto"
    | Scroll => "scroll"
    }
  );

let overflowX = o =>
  Property(
    "overflowX",
    switch o {
    | Visible => "visible"
    | Hidden => "hidden"
    | Auto => "auto"
    | Scroll => "scroll"
    }
  );

let overflowY = o =>
  Property(
    "overflowY",
    switch o {
    | Visible => "visible"
    | Hidden => "hidden"
    | Auto => "auto"
    | Scroll => "scroll"
    }
  );

let zIndex = intProp("zIndex");

/* FLEXBOX */
let flex = intProp("flex");

let flexBasis = intProp("flexBasis");

let flexGrow = intProp("flexGrow");

let flexShrink = intProp("flexShrink");

let flexFlow = intProp("flexFlow");

let order = intProp("order");

type flexDirection =
  | Row
  | RowReverse
  | Column
  | ColumnReverse;

let flexDirection = v =>
  Property(
    "flexDirection",
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

let flexWrap = v =>
  Property(
    "flexWrap",
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

let justifyToString = v =>
  switch v {
  | FlexStart => "flex-start"
  | FlexEnd => "flex-end"
  | Center => "center"
  | Stretch => "stretch"
  | SpaceAround => "space-around"
  | SpaceBetween => "space-between"
  };

let alignContent = v => Property("alignContent", justifyToString(v));

type alignment =
  | FlexStart
  | FlexEnd
  | Center
  | Stretch
  | Baseline;

let alignmentToString = v =>
  switch v {
  | FlexStart => "flex-start"
  | FlexEnd => "flex-end"
  | Center => "center"
  | Stretch => "stretch"
  | Baseline => "baseline"
  };

let alignItems = v => Property("alignItems", alignmentToString(v));

let alignSelf = v => Property("alignSelf", alignmentToString(v));

let justifyContent = v => Property("justifyContent", justifyToString(v));

/* SHADOW */
type shadow = string;

let shadow = (~x=0, ~y=0, ~blur=0, ~spread=0, color) => {j|$(x)px $(y)px $(blur)px $(spread)px $color|j};

let boxShadow = stringProp("boxShadow");

let boxShadows = shadows => Property("boxShadow", join(", ", shadows));

/* ANIMATION */
type keyframes = string;

let animationName = stringProp("animationName");

let animationDuration = ms =>
  Property("animationDuration", string_of_int(ms) ++ "ms");

let animationDelay = ms =>
  Property("animationDelay", string_of_int(ms) ++ "ms");

type animationDirection =
  | Normal
  | Reverse
  | Alternate
  | AlternateReverse;

let animationDirection = v =>
  Property(
    "animationDirection",
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

let animationFillMode = v =>
  Property(
    "animationFillMode",
    switch v {
    | None => "none"
    | Forwards => "forwards"
    | Backwards => "backwards"
    | Both => "both"
    }
  );

type animationIterationCount =
  | Infinite
  | Iterate(int);

let animationIterationCount = v =>
  Property(
    "animationIterationCount",
    switch v {
    | Infinite => "infinite"
    | Iterate(v) => string_of_int(v)
    }
  );

type animationPlayState =
  | Paused
  | Running;

let animationPlayState = v =>
  Property(
    "animationPlayState",
    switch v {
    | Paused => "paused"
    | Running => "running"
    }
  );

type animationSteps =
  | Start
  | End;

let animationStepsToString = s =>
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
  | CubicBezier(float, float, float, float)
  | Steps(int, animationSteps)
  | Frames(int);

let timingFunctionToString = v =>
  switch v {
  | Ease => "ease"
  | EaseIn => "ease-in"
  | EaseOut => "ease-out"
  | EaseInOut => "ease-in-out"
  | Linear => "linear"
  | StepStart => "step-start"
  | StepEnd => "step-end"
  | CubicBezier(x1, y1, x2, y2) => {j|cubic-bezier($x1, $y1, $x2, $y2)|j}
  | Steps(i, s) =>
    "steps(" ++ string_of_int(i) ++ ", " ++ animationStepsToString(s) ++ ")"
  | Frames(i) => {j|frames($i)|j}
  };

let animationTimingFunction = v =>
  Property("animationTimingFunction", timingFunctionToString(v));

/* TRANSITION */
let transitionDelay = intProp("transitionDelay");

let transitionDuration = intProp("transitionDuration");

let transitionProperty = stringProp("transitionProperty");

let transitionTimingFunction = v =>
  Property(
    "transitionTimingFunction",
    switch v {
    | Ease => "ease"
    | EaseIn => "ease-in"
    | EaseOut => "ease-out"
    | EaseInOut => "ease-in-out"
    | Linear => "linear"
    | StepStart => "step-start"
    | StepEnd => "step-end"
    | CubicBezier(x1, y1, x2, y2) => {j|cubic-bezier($x1, $y1, $x2, $y2)|j}
    | Steps(i, s) =>
      "steps(" ++ string_of_int(i) ++ ", " ++ animationStepsToString(s) ++ ")"
    | Frames(i) => {j|frames($i)|j}
    }
  );

let transition = (~delay=0, ~duration=0, ~timingFunction=Ease, name) => {
  let func = timingFunctionToString(timingFunction);
  Property("transition", {j|$name $(duration)ms $func $(delay)ms|j});
};

/* TRANSFORM */
type transform = string;

let transform = stringProp("transform");

let transforms = transforms => Property("transform", join(" ", transforms));

let translate = (x, y) => {j|translate($x, $y)|j};

let translateX = x => {j|translateX($x)|j};

let translateY = y => {j|translateY($y)|j};

let translateZ = z => {j|translateZ($z)|j};

let translate3d = (x, y, z) => {j|translate($x $y, $z)|j};

let scale = (x, y) => {j|scale($x, $y)|j};

let scale3d = (x, y, z) => {j|scale3d($x, $y, $z)|j};

let scaleX = x => {j|scaleX($x)|j};

let scaleY = y => {j|scaleY($y)|j};

let scaleZ = y => {j|scaleZ($y)|j};

let rotate = a => {j|rotate($a)|j};

let rotateX = a => {j|rotateX($a)|j};

let rotateY = a => {j|rotateY($a)|j};

let rotateZ = a => {j|rotateZ($a)|j};

let skew = (ax, ay) => {j|skew($ax, $ay|j};

let skewX = a => {j|skewX($a|j};

let skewY = a => {j|skewY($a|j};

let perspective = stringProp("perspective");

/* PSEUDO CLASSES */
let selector = (name, rules) => Selector(name, rules);

let hover = selector(":hover");

let before = selector("::before");

let after = selector("::after");

let disabled = selector(":disabled");

let required = selector(":required");

let readOnly = selector(":readOnly");

let focus = selector(":focus");

let active = selector(":active");

let visited = selector(":visited");

let link = selector(":link");

let firstChild = selector(":firstChild");

let firstOfType = selector(":firstOfType");

let lastChild = selector(":lastChild");

let lastOfType = selector(":lastOfType");

let children = selector(" > *");

/* MEDIA */
let media = (query, rules) => Selector("@media " ++ query, rules);

/* MISC */
type cursor =
  | Auto
  | Pointer
  | Custom(string);

let cursor = v =>
  Property(
    "cursor",
    switch v {
    | Auto => "auto"
    | Pointer => "pointer"
    | Custom(cur) => cur
    }
  );

let outline = (width, style, color) => {
  let outlineStyle = borderStyleToString(style);
  Property("outline", {j|$width $outlineStyle $color|j});
};

let outlineStyle = v => Property("outlineStyle", borderStyleToString(v));

let outlineOffset = stringProp("outlineOffset");

let outlineWidth = stringProp("outlineWidth");

let outlineColor = stringProp("outlineColor");
