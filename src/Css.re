module Types = Css_Types;
open Types;

include Css_Colors;

type rule =
  | D(string, string) // Declaration
  | S(string, list(rule)) // Selector
  | PseudoClass(string, list(rule))
  | PseudoClassParam(string, string, list(rule));

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

  let rec ruleToDict = (dict, rule) => {
    switch (rule) {
    | D(name, value) when name == "content" =>
      dict->Js.Dict.set(name, Js.Json.string(value == "" ? "\"\"" : value))
    | D(name, value) => dict->Js.Dict.set(name, Js.Json.string(value))
    | S(name, ruleset) => dict->Js.Dict.set(name, makeJson(ruleset))
    | PseudoClass(name, ruleset) =>
      dict->Js.Dict.set(":" ++ name, makeJson(ruleset))
    | PseudoClassParam(name, param, ruleset) =>
      dict->Js.Dict.set(
        ":" ++ name ++ "(" ++ param ++ ")",
        makeJson(ruleset),
      )
    };
    dict;
  }

  and makeJson = rules =>
    rules->Belt.List.reduce(Js.Dict.empty(), ruleToDict)->Js.Json.object_;

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

module Converter = {
  let string_of_percent =
    fun
    | #Percentage.t as p => Percentage.toString(p);

  let string_of_hsl = (h, s, l) =>
    "hsl("
    ++ Angle.toString(h)
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
    ++ Angle.toString(h)
    ++ ", "
    ++ string_of_percent(s)
    ++ ", "
    ++ string_of_percent(l)
    ++ ", "
    ++ string_of_alpha(a)
    ++ ")";

  let string_of_stops = stops =>
    stops
    ->Belt.List.map(((l, c)) =>
        Color.toString(c) ++ " " ++ Length.toString(l)
      )
    ->join(", ");

  let string_of_time = t => Js.Int.toString(t) ++ "ms";

  let string_of_background = bg =>
    switch (bg) {
    | `none => "none"
    | `url(url) => "url(" ++ url ++ ")"
    | `rgb(r, g, b) =>
      "rgb("
      ++ Js.Int.toString(r)
      ++ ", "
      ++ Js.Int.toString(g)
      ++ ", "
      ++ Js.Int.toString(b)
      ++ ")"
    | `rgba(r, g, b, a) =>
      "rgba("
      ++ Js.Int.toString(r)
      ++ ", "
      ++ Js.Int.toString(g)
      ++ ", "
      ++ Js.Int.toString(b)
      ++ ", "
      ++ Js.Float.toString(a)
      ++ ")"
    | `hsl(h, s, l) => string_of_hsl(h, s, l)
    | `hsla(h, s, l, a) => string_of_hsla(h, s, l, a)
    | `hex(s) => "#" ++ s
    | `transparent => "transparent"
    | `currentColor => "currentColor"
    | `linearGradient(angle, stops) =>
      "linear-gradient("
      ++ Angle.toString(angle)
      ++ ", "
      ++ string_of_stops(stops)
      ++ ")"
    | `repeatingLinearGradient(angle, stops) =>
      "repeating-linear-gradient("
      ++ Angle.toString(angle)
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
  | D(name, value) => D(name, value ++ " !important")
  | _ => v
  };

let label = label => D("label", label);

/* Properties */

let alignContent = x =>
  D(
    "alignContent",
    switch (x) {
    | #AlignContent.t as ac => AlignContent.toString(ac)
    | #NormalAlignment.t as na => NormalAlignment.toString(na)
    | #BaselineAlignment.t as ba => BaselineAlignment.toString(ba)
    | #DistributedAlignment.t as da => DistributedAlignment.toString(da)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let alignItems = x =>
  D(
    "alignItems",
    switch (x) {
    | #AlignItems.t as ai => AlignItems.toString(ai)
    | #PositionalAlignment.t as pa => PositionalAlignment.toString(pa)
    | #BaselineAlignment.t as ba => BaselineAlignment.toString(ba)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let alignSelf = x =>
  D(
    "alignSelf",
    switch (x) {
    | #AlignSelf.t as a => AlignSelf.toString(a)
    | #PositionalAlignment.t as pa => PositionalAlignment.toString(pa)
    | #BaselineAlignment.t as ba => BaselineAlignment.toString(ba)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let animationDelay = x => D("animationDelay", string_of_time(x));

let animationDirection = x =>
  D("animationDirection", AnimationDirection.toString(x));

let animationDuration = x => D("animationDuration", string_of_time(x));

let animationFillMode = x =>
  D("animationFillMode", AnimationFillMode.toString(x));

let animationIterationCount = x =>
  D("animationIterationCount", AnimationIterationCount.toString(x));

let animationPlayState = x =>
  D("animationPlayState", AnimationPlayState.toString(x));

let animationTimingFunction = x =>
  D("animationTimingFunction", TimingFunction.toString(x));

let backfaceVisibility = x =>
  D(
    "backfaceVisibility",
    switch (x) {
    | #BackfaceVisibility.t as bv => BackfaceVisibility.toString(bv)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let backgroundAttachment = x =>
  D(
    "backgroundAttachment",
    switch (x) {
    | #BackgroundAttachment.t as ba => BackgroundAttachment.toString(ba)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let backgroundColor = x => D("backgroundColor", Color.toString(x));

let backgroundClip = x =>
  D(
    "backgroundClip",
    switch (x) {
    | #BackgroundClip.t as bc => BackgroundClip.toString(bc)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let backgroundImage = x =>
  D(
    "backgroundImage",
    switch (x) {
    | #BackgroundImage.t as bi => BackgroundImage.toString(bi)
    | #Url.t as u => Url.toString(u)
    | #Gradient.t as g => Gradient.toString(g)
    },
  );

let backgroundOrigin = x =>
  D(
    "backgroundOrigin",
    switch (x) {
    | #BackgroundOrigin.t as bo => BackgroundOrigin.toString(bo)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let backgroundPosition = (x, y) =>
  D("backgroundPosition", Length.toString(x) ++ " " ++ Length.toString(y));

let backgroundRepeat = x =>
  D(
    "backgroundRepeat",
    switch (x) {
    | #BackgroundRepeat.t as br => BackgroundRepeat.toString(br)
    | `hv(#BackgroundRepeat.horizontal as h, #BackgroundRepeat.vertical as v) =>
      BackgroundRepeat.toString(h) ++ " " ++ BackgroundRepeat.toString(v)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let borderBottomColor = x => D("borderBottomColor", Color.toString(x));

let borderBottomLeftRadius = x =>
  D("borderBottomLeftRadius", Length.toString(x));

let borderBottomRightRadius = x =>
  D("borderBottomRightRadius", Length.toString(x));

let borderBottomWidth = x => D("borderBottomWidth", Length.toString(x));

let borderCollapse = x =>
  D(
    "borderCollapse",
    switch (x) {
    | #BorderCollapse.t as bc => BorderCollapse.toString(bc)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let borderColor = x => D("borderColor", Color.toString(x));

let borderLeftColor = x => D("borderLeftColor", Color.toString(x));

let borderLeftWidth = x => D("borderLeftWidth", Length.toString(x));

let borderSpacing = x => D("borderSpacing", Length.toString(x));

let borderRadius = x => D("borderRadius", Length.toString(x));

let borderRightColor = x => D("borderRightColor", Color.toString(x));

let borderRightWidth = x => D("borderRightWidth", Length.toString(x));

let borderTopColor = x => D("borderTopColor", Color.toString(x));

let borderTopLeftRadius = x => D("borderTopLeftRadius", Length.toString(x));

let borderTopRightRadius = x =>
  D("borderTopRightRadius", Length.toString(x));

let borderTopWidth = x => D("borderTopWidth", Length.toString(x));

let borderWidth = x => D("borderWidth", Length.toString(x));

let bottom = x =>
  D(
    "bottom",
    switch (x) {
    | #Length.t as l => Length.toString(l)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let boxSizing = x =>
  D(
    "boxSizing",
    switch (x) {
    | #BoxSizing.t as bs => BoxSizing.toString(bs)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let clear = x =>
  D(
    "clear",
    switch (x) {
    | #Clear.t as cl => Clear.toString(cl)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let clipPath = x =>
  D(
    "clipPath",
    switch (x) {
    | #ClipPath.t as cp => ClipPath.toString(cp)
    | #Url.t as u => Url.toString(u)
    | #GeometyBox.t as gb => GeometyBox.toString(gb)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let color = x => D("color", Color.toString(x));

let columnCount = x =>
  D(
    "columnCount",
    switch (x) {
    | #ColumnCount.t as cc => ColumnCount.toString(cc)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let contentRule = x => D("content", {j|"$x"|j});

let cursor = x => D("cursor", Cursor.toString(x));

let direction = x =>
  D(
    "direction",
    switch (x) {
    | #Direction.t as d => Direction.toString(d)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let display = x =>
  D(
    "display",
    switch (x) {
    | #DisplayOutside.t as o => DisplayOutside.toString(o)
    | #DisplayInside.t as i => DisplayInside.toString(i)
    | #DisplayListItem.t as l => DisplayListItem.toString(l)
    | #DisplayInternal.t as i' => DisplayInternal.toString(i')
    | #DisplayBox.t as b => DisplayBox.toString(b)
    | #DisplayLegacy.t as l' => DisplayLegacy.toString(l')
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let flexDirection = x =>
  D(
    "flexDirection",
    switch (x) {
    | #FlexDirection.t as fd => FlexDirection.toString(fd)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let flexGrow = x => D("flexGrow", Js.Float.toString(x));

let flexShrink = x => D("flexShrink", Js.Float.toString(x));

let flexWrap = x =>
  D(
    "flexWrap",
    switch (x) {
    | #FlexWrap.t as fw => FlexWrap.toString(fw)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let float = x =>
  D(
    "float",
    switch (x) {
    | #Float.t as f => Float.toString(f)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let fontFamily = x => D("fontFamily", x);

let fontSize = x =>
  D(
    "fontSize",
    switch (x) {
    | #Length.t as l => Length.toString(l)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let fontStyle = x =>
  D(
    "fontStyle",
    switch (x) {
    | #FontStyle.t as f => FontStyle.toString(f)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let fontVariant = x =>
  D(
    "fontVariant",
    switch (x) {
    | #FontVariant.t as f => FontVariant.toString(f)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let fontWeight = x =>
  D(
    "fontWeight",
    switch (x) {
    | #FontWeight.t as f => FontWeight.toString(f)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let gridAutoFlow = x =>
  D(
    "gridAutoFlow",
    switch (x) {
    | #GridAutoFlow.t as f => GridAutoFlow.toString(f)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let gridColumn = (start, end') =>
  D("gridColumn", Js.Int.toString(start) ++ " / " ++ Js.Int.toString(end'));

let gridColumnGap = x =>
  D(
    "gridColumnGap",
    switch (x) {
    | #GridColumnGap.t as gcg => GridColumnGap.toString(gcg)
    | #Percentage.t as p => Percentage.toString(p)
    | #Length.t as l => Length.toString(l)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let gridColumnStart = n => D("gridColumnStart", Js.Int.toString(n));

let gridColumnEnd = n => D("gridColumnEnd", Js.Int.toString(n));

let gridRow = (start, end') =>
  D("gridRow", Js.Int.toString(start) ++ " / " ++ Js.Int.toString(end'));

let gridGap = x =>
  D(
    "gridGap",
    switch (x) {
    | #Percentage.t as p => Percentage.toString(p)
    | #Length.t as l => Length.toString(l)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let gridRowGap = x =>
  D(
    "gridRowGap",
    switch (x) {
    | #Percentage.t as p => Percentage.toString(p)
    | #Length.t as l => Length.toString(l)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let gridRowEnd = n => D("gridRowEnd", Js.Int.toString(n));

let gridRowStart = n => D("gridRowStart", Js.Int.toString(n));

let height = x =>
  D(
    "height",
    switch (x) {
    | #Height.t as h => Height.toString(h)
    | #Percentage.t as p => Percentage.toString(p)
    | #Length.t as l => Length.toString(l)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let justifyContent = x =>
  D(
    "justifyContent",
    switch (x) {
    | #PositionalAlignment.t as pa => PositionalAlignment.toString(pa)
    | #NormalAlignment.t as na => NormalAlignment.toString(na)
    | #DistributedAlignment.t as da => DistributedAlignment.toString(da)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let left = x =>
  D(
    "left",
    switch (x) {
    | #Length.t as l => Length.toString(l)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let letterSpacing = x =>
  D(
    "letterSpacing",
    switch (x) {
    | #LetterSpacing.t as s => LetterSpacing.toString(s)
    | #Length.t as l => Length.toString(l)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let lineHeight = x =>
  D(
    "lineHeight",
    switch (x) {
    | #LineHeight.t as h => LineHeight.toString(h)
    | #Length.t as l => Length.toString(l)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let listStyleType = x =>
  D(
    "listStyleType",
    switch (x) {
    | #ListStyleType.t as lsp => ListStyleType.toString(lsp)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let listStylePosition = x =>
  D(
    "listStylePosition",
    switch (x) {
    | #ListStylePosition.t as lsp => ListStylePosition.toString(lsp)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let marginToString = x =>
  switch (x) {
  | #Length.t as l => Length.toString(l)
  | #Margin.t as m => Margin.toString(m)
  };

let margin = x => D("margin", marginToString(x));
let margin2 = (~v, ~h) =>
  D("margin", marginToString(v) ++ " " ++ marginToString(h));
let margin3 = (~top, ~h, ~bottom) =>
  D(
    "margin",
    marginToString(top)
    ++ " "
    ++ marginToString(h)
    ++ " "
    ++ marginToString(bottom),
  );
let margin4 = (~top, ~right, ~bottom, ~left) =>
  D(
    "margin",
    marginToString(top)
    ++ " "
    ++ marginToString(right)
    ++ " "
    ++ marginToString(bottom)
    ++ " "
    ++ marginToString(left),
  );
let marginLeft = x => D("marginLeft", marginToString(x));
let marginRight = x => D("marginRight", marginToString(x));
let marginTop = x => D("marginTop", marginToString(x));
let marginBottom = x => D("marginBottom", marginToString(x));

let maxHeight = x =>
  D(
    "maxHeight",
    switch (x) {
    | #MaxHeight.t as mh => MaxHeight.toString(mh)
    | #Percentage.t as p => Percentage.toString(p)
    | #Length.t as l => Length.toString(l)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let maxWidth = x =>
  D(
    "maxWidth",
    switch (x) {
    | #MaxWidth.t as mw => MaxWidth.toString(mw)
    | #Percentage.t as p => Percentage.toString(p)
    | #Length.t as l => Length.toString(l)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let minHeight = x =>
  D(
    "minHeight",
    switch (x) {
    | #Height.t as h => Height.toString(h)
    | #Percentage.t as p => Percentage.toString(p)
    | #Length.t as l => Length.toString(l)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let minWidth = x =>
  D(
    "minWidth",
    switch (x) {
    | #Width.t as w => Width.toString(w)
    | #Percentage.t as p => Percentage.toString(p)
    | #Length.t as l => Length.toString(l)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let objectFit = x =>
  D(
    "objectFit",
    switch (x) {
    | #ObjectFit.t as o => ObjectFit.toString(o)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let opacity = x => D("opacity", Js.Float.toString(x));

let outline = (size, style, color) =>
  D(
    "outline",
    Length.toString(size)
    ++ " "
    ++ OutlineStyle.toString(style)
    ++ " "
    ++ Color.toString(color),
  );
let outlineColor = x => D("outlineColor", Color.toString(x));
let outlineOffset = x => D("outlineOffset", Length.toString(x));
let outlineStyle = x => D("outlineStyle", OutlineStyle.toString(x));
let outlineWidth = x => D("outlineWidth", Length.toString(x));

let overflow = x => D("overflow", Overflow.toString(x));
let overflowX = x => D("overflowX", Overflow.toString(x));
let overflowY = x => D("overflowY", Overflow.toString(x));

let overflowWrap = x =>
  D(
    "overflowWrap",
    switch (x) {
    | #OverflowWrap.t as ow => OverflowWrap.toString(ow)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let padding = x => D("padding", Length.toString(x));
let padding2 = (~v, ~h) =>
  D("padding", Length.toString(v) ++ " " ++ Length.toString(h));
let padding3 = (~top, ~h, ~bottom) =>
  D(
    "padding",
    Length.toString(top)
    ++ " "
    ++ Length.toString(h)
    ++ " "
    ++ Length.toString(bottom),
  );
let padding4 = (~top, ~right, ~bottom, ~left) =>
  D(
    "padding",
    Length.toString(top)
    ++ " "
    ++ Length.toString(right)
    ++ " "
    ++ Length.toString(bottom)
    ++ " "
    ++ Length.toString(left),
  );

let paddingBottom = x => D("paddingBottom", Length.toString(x));

let paddingLeft = x => D("paddingLeft", Length.toString(x));

let paddingRight = x => D("paddingRight", Length.toString(x));

let paddingTop = x => D("paddingTop", Length.toString(x));

let perspective = x =>
  D(
    "perspective",
    switch (x) {
    | #Perspective.t as p => Perspective.toString(p)
    | #Length.t as l => Length.toString(l)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let perspectiveOrigin = (x, y) =>
  D(
    "perspectiveOrigin",
    (
      switch (x) {
      | #Perspective.t as p => Perspective.toString(p)
      | #Length.t as l => Length.toString(l)
      }
    )
    ++ " "
    ++ (
      switch (y) {
      | #Perspective.t as p => Perspective.toString(p)
      | #Length.t as l => Length.toString(l)
      }
    ),
  );

let pointerEvents = x =>
  D(
    "pointerEvents",
    switch (x) {
    | #PointerEvents.t as p => PointerEvents.toString(p)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let position = x =>
  D(
    "position",
    switch (x) {
    | #Position.t as p => Position.toString(p)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let justifySelf = x =>
  D(
    "justifySelf",
    switch (x) {
    | #JustifySelf.t as j => JustifySelf.toString(j)
    | #PositionalAlignment.t as pa => PositionalAlignment.toString(pa)
    | #BaselineAlignment.t as ba => BaselineAlignment.toString(ba)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let resize = x =>
  D(
    "resize",
    switch (x) {
    | #Resize.t as r => Resize.toString(r)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let right = x =>
  D(
    "right",
    switch (x) {
    | #Length.t as l => Length.toString(l)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let tableLayout = x =>
  D(
    "tableLayout",
    switch (x) {
    | #TableLayout.t as tl => TableLayout.toString(tl)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let textAlign = x =>
  D(
    "textAlign",
    switch (x) {
    | #TextAlign.t as ta => TextAlign.toString(ta)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let textDecorationColor = x =>
  D(
    "textDecorationColor",
    switch (x) {
    | #Color.t as co => Color.toString(co)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let textDecorationLine = x =>
  D(
    "textDecorationLine",
    switch (x) {
    | #TextDecorationLine.t as tdl => TextDecorationLine.toString(tdl)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let textDecorationStyle = x =>
  D(
    "textDecorationStyle",
    switch (x) {
    | #TextDecorationStyle.t as tds => TextDecorationStyle.toString(tds)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let textIndent = x =>
  D(
    "textIndent",
    switch (x) {
    | #Percentage.t as p => Percentage.toString(p)
    | #Length.t as l => Length.toString(l)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let textOverflow = x =>
  D(
    "textOverflow",
    switch (x) {
    | #TextOverflow.t as txo => TextOverflow.toString(txo)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let textTransform = x =>
  D(
    "textTransform",
    switch (x) {
    | #TextTransform.t as tt => TextTransform.toString(tt)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let top = x =>
  D(
    "top",
    switch (x) {
    | #Length.t as l => Length.toString(l)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let transform = x => D("transform", Transform.toString(x));

let transforms = x =>
  D("transform", x->Belt.List.map(Transform.toString)->join(" "));

let transformOrigin = (x, y) =>
  D("transformOrigin", Length.toString(x) ++ " " ++ Length.toString(y));

let transformOrigin3d = (x, y, z) =>
  D(
    "transformOrigin",
    Length.toString(x)
    ++ " "
    ++ Length.toString(y)
    ++ " "
    ++ Length.toString(z)
    ++ " ",
  );

let unsafe = (property, value) => D(property, value);

let userSelect = x =>
  D(
    "userSelect",
    switch (x) {
    | #UserSelect.t as us => UserSelect.toString(us)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let verticalAlign = x =>
  D(
    "verticalAlign",
    switch (x) {
    | #VerticalAlign.t as v => VerticalAlign.toString(v)
    | #Length.t as l => Length.toString(l)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let visibility = x =>
  D(
    "visibility",
    switch (x) {
    | #Visibility.t as v => Visibility.toString(v)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let width = x =>
  D(
    "width",
    switch (x) {
    | #Width.t as w => Width.toString(w)
    | #Percentage.t as p => Percentage.toString(p)
    | #Length.t as l => Length.toString(l)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let whiteSpace = x =>
  D(
    "whiteSpace",
    switch (x) {
    | #WhiteSpace.t as w => WhiteSpace.toString(w)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let wordBreak = x =>
  D(
    "wordBreak",
    switch (x) {
    | #WordBreak.t as w => WordBreak.toString(w)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let wordSpacing = x =>
  D(
    "wordSpacing",
    switch (x) {
    | #WordSpacing.t as w => WordSpacing.toString(w)
    | #Percentage.t as p => Percentage.toString(p)
    | #Length.t as l => Length.toString(l)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let wordWrap = overflowWrap;

let zIndex = x => D("zIndex", Js.Int.toString(x));

/* Selectors */

let media = (query, rules) => S("@media " ++ query, rules);
let selector = (selector, rules) => S(selector, rules);
let pseudoClass = (selector, rules) => PseudoClass(selector, rules);

let active = pseudoClass("active");
let checked = pseudoClass("checked");
let default = pseudoClass("default");
let defined = pseudoClass("defined");
let disabled = pseudoClass("disabled");
let empty = pseudoClass("empty");
let enabled = pseudoClass("enabled");
let first = pseudoClass("first");
let firstChild = pseudoClass("first-child");
let firstOfType = pseudoClass("first-of-type");
let focus = pseudoClass("focus");
let focusWithin = pseudoClass("focus-within");
let host = (~selector=?, rules) =>
  switch (selector) {
  | None => PseudoClass("host", rules)
  | Some(s) => PseudoClassParam("host", s, rules)
  };
let hover = pseudoClass("hover");
let indeterminate = pseudoClass("indeterminate");
let inRange = pseudoClass("in-range");
let invalid = pseudoClass("invalid");
let lang = (code, rules) => PseudoClassParam("lang", code, rules);
let lastChild = pseudoClass("last-child");
let lastOfType = pseudoClass("last-of-type");
//let left = selector(":left");
let link = pseudoClass("link");
let not_ = (selector, rules) => PseudoClassParam("not", selector, rules);
module Nth = {
  type t = [ | `odd | `even | `n(int) | `add(int, int)];
  let toString =
    fun
    | `odd => "odd"
    | `even => "even"
    | `n(x) => Js.Int.toString(x) ++ "n"
    | `add(x, y) => Js.Int.toString(x) ++ "n+" ++ Js.Int.toString(y);
};
let nthChild = (x, rules) =>
  PseudoClassParam("nth-child", Nth.toString(x), rules);
let nthLastChild = (x, rules) =>
  PseudoClassParam("nth-last-child", Nth.toString(x), rules);
let nthLastOfType = (x, rules) =>
  PseudoClassParam("nth-last-of-type", Nth.toString(x), rules);
let nthOfType = (x, rules) =>
  PseudoClassParam("nth-of-type", Nth.toString(x), rules);
let onlyChild = pseudoClass("only-child");
let onlyOfType = pseudoClass("only-of-type");
let optional = pseudoClass("optional");
let outOfRange = pseudoClass("out-of-range");
let readOnly = pseudoClass("read-only");
let readWrite = pseudoClass("read-write");
let required = pseudoClass("required");
//let right = selector(":right");
let root = pseudoClass("root");
let scope = pseudoClass("scope");
let target = pseudoClass("target");
let valid = pseudoClass("valid");
let visited = pseudoClass("visited");

let after = selector("::after");
let before = selector("::before");
let children = selector(" > *");
let directSibling = selector(" + ");
let noContent = selector(":empty");
let anyLink = selector(":any-link");
let siblings = selector(" ~ ");
let firstLine = selector("::first-line");
let firstLetter = selector("::first-letter");
let selection = selector("::selection");
let placeholder = selector("::placeholder");

/* Type aliasing */

type angle = Angle.t;
type animationDirection = AnimationDirection.t;
type animationFillMode = AnimationFillMode.t;
type animationIterationCount = AnimationIterationCount.t;
type animationPlayState = AnimationPlayState.t;
type cascading = Cascading.t;
type color = Color.t;
type fontStyle = FontStyle.t;
type fontWeight = FontWeight.t;
type length = Length.t;
type listStyleType = ListStyleType.t;
type repeatValue = RepeatValue.t;
type outlineStyle = OutlineStyle.t;
type transform = Transform.t;
type gradient = Types.Gradient.t;

/* Constructor aliases */

let initial = Cascading.initial;
let inherit_ = Cascading.inherit_;
let unset = Cascading.unset;

let pct = Percentage.pct;

let ch = Length.ch;
let cm = Length.cm;
let em = Length.em;
let ex = Length.ex;
let mm = Length.mm;
let pt = Length.pt;
let px = Length.px;
let pxFloat = Length.pxFloat;
let rem = Length.rem;
let vh = Length.vh;
let vmin = Length.vmin;
let vmax = Length.vmax;
let zero = Length.zero;

let deg = Angle.deg;
let rad = Angle.rad;
let grad = Angle.grad;
let turn = Angle.turn;

let ltr = Direction.ltr;
let rtl = Direction.rtl;

let absolute = Position.absolute;
let relative = Position.relative;
let static = Position.static;
let fixed = `fixed;
let sticky = Position.sticky;

//let none = Resize.none;
//let both = Resize.both;
let horizontal = Resize.horizontal;
let vertical = Resize.vertical;
//let block = Resize.block;
//let inline = Resize.inline;

let smallCaps = FontVariant.smallCaps;

//let normal = `normal;
let italic = FontStyle.italic;
let oblique = FontStyle.oblique;

let hidden = `hidden;
let visible = `visible;
let scroll = `scroll;
let auto = `auto;

let rgb = Color.rgb;
let rgba = Color.rgba;
let hsl = Color.hsl;
let hsla = Color.hsla;
let hex = Color.hex;
let currentColor = Color.currentColor;
let transparent = Color.transparent;

let linear = TimingFunction.linear;
let ease = TimingFunction.ease;
let easeIn = TimingFunction.easeIn;
let easeInOut = TimingFunction.easeInOut;
let easeOut = TimingFunction.easeOut;
let stepStart = TimingFunction.stepStart;
let stepEnd = TimingFunction.stepEnd;
let steps = TimingFunction.steps;
let cubicBezier = TimingFunction.cubicBezier;

let marginBox = GeometyBox.marginBox;
//let borderBox = GeometyBox.borderBox;
//let paddingBox = GeometyBox.paddingBox;
//let contentBox = GeometyBox.contentBox;
let fillBox = GeometyBox.fillBox;
let strokeBox = GeometyBox.strokeBox;
let viewBox = GeometyBox.viewBox;

let translate = Transform.translate;
let translate3d = Transform.translate3d;
let translateX = Transform.translateX;
let translateY = Transform.translateY;
let translateZ = Transform.translateZ;
let scaleX = Transform.scaleX;
let scaleY = Transform.scaleY;
let scaleZ = Transform.scaleZ;
let rotateX = Transform.rotateX;
let rotateY = Transform.rotateY;
let rotateZ = Transform.rotateZ;
let scale = Transform.scale;
let scale3d = Transform.scale3d;
let skew = Transform.skew;
let skewX = Transform.skewX;
let skewY = Transform.skewY;

let linearGradient = Gradient.linearGradient;
let repeatingLinearGradient = Gradient.repeatingLinearGradient;
let radialGradient = Gradient.radialGradient;
let repeatingRadialGradient = Gradient.repeatingRadialGradient;

/********************************************************
 ********************************************************
 ********************************************************/

let vw = x => `vw(x);
let fr = x => `fr(x);

module Calc = {
  let (-) = (a, b) => `calc((`sub, a, b));
  let (+) = (a, b) => `calc((`add, a, b));
};
let size = (x, y) => `size((x, y));

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
let dashed = `dashed;
let dotted = `dotted;
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

let local = `local;
let localUrl = x => `localUrl(x);
let none = `none;
let noRepeat = `noRepeat;
let space = `space;
let nowrap = `nowrap;
let paddingBox = `paddingBox;
let paused = `paused;
let repeat = `repeat;
let minmax = `minmax;
let repeatX = `repeatX;
let repeatY = `repeatY;
let rotate = a => `rotate(a);
let rotate3d = (x, y, z, a) => `rotate3d((x, y, z, a));
let row = `row;
let rowReverse = `rowReverse;
let running = `running;
let solid = `solid;
let spaceAround = `spaceAround;
let spaceBetween = `spaceBetween;
let spaceEvenly = `spaceEvenly;
let stretch = `stretch;
let text = `text;
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

let flex = x => D("flex", string_of_flex(x));
let flex3 = (~grow, ~shrink, ~basis) =>
  D(
    "flex",
    Js.Float.toString(grow)
    ++ " "
    ++ Js.Float.toString(shrink)
    ++ " "
    ++ (
      switch (basis) {
      | #FlexBasis.t as b => FlexBasis.toString(b)
      | #Length.t as l => Length.toString(l)
      }
    ),
  );
let flexBasis = x =>
  D(
    "flexBasis",
    switch (x) {
    | #FlexBasis.t as b => FlexBasis.toString(b)
    | #Length.t as l => Length.toString(l)
    },
  );

let order = x => D("order", Js.Int.toString(x));

let string_of_minmax =
  fun
  | `auto => "auto"
  | `calc(`add, a, b) =>
    "calc(" ++ Length.toString(a) ++ " + " ++ Length.toString(b) ++ ")"
  | `calc(`sub, a, b) =>
    "calc(" ++ Length.toString(a) ++ " - " ++ Length.toString(b) ++ ")"
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
  | `inch(x) => Js.Float.toString(x) ++ "in"
  | `pc(x) => Js.Float.toString(x) ++ "pc"
  | `zero => "0"
  | `minContent => "min-content"
  | `maxContent => "max-content";

let string_of_dimension =
  fun
  | `auto => "auto"
  | `none => "none"
  | `calc(`add, a, b) =>
    "calc(" ++ Length.toString(a) ++ " + " ++ Length.toString(b) ++ ")"
  | `calc(`sub, a, b) =>
    "calc(" ++ Length.toString(a) ++ " - " ++ Length.toString(b) ++ ")"
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
  | `inch(x) => Js.Float.toString(x) ++ "in"
  | `pc(x) => Js.Float.toString(x) ++ "pc"
  | `zero => "0"
  | `fitContent => "fit-content"
  | `minContent => "min-content"
  | `maxContent => "max-content"
  | `minmax(a, b) =>
    "minmax(" ++ string_of_minmax(a) ++ "," ++ string_of_minmax(b) ++ ")";

type minmax = [ | `fr(float) | `minContent | `maxContent | `auto | Length.t];

type trackLength = [
  Length.t
  | `fr(float)
  | `minContent
  | `maxContent
  | `minmax(minmax, minmax)
];
type gridLength = [ trackLength | `repeat(RepeatValue.t, trackLength)];

let gridLengthToJs =
  fun
  | `auto => "auto"
  | `calc(`add, a, b) =>
    "calc(" ++ Length.toString(a) ++ " + " ++ Length.toString(b) ++ ")"
  | `calc(`sub, a, b) =>
    "calc(" ++ Length.toString(a) ++ " - " ++ Length.toString(b) ++ ")"
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
  | `inch(x) => Js.Float.toString(x) ++ "in"
  | `pc(x) => Js.Float.toString(x) ++ "pc"
  | `vmax(x) => Js.Float.toString(x) ++ "vmax"
  | `vmin(x) => Js.Float.toString(x) ++ "vmin"
  | `vw(x) => Js.Float.toString(x) ++ "vw"
  | `fr(x) => Js.Float.toString(x) ++ "fr"
  | `zero => "0"
  | `minContent => "min-content"
  | `maxContent => "max-content"
  | `repeat(n, x) =>
    "repeat("
    ++ RepeatValue.toString(n)
    ++ ", "
    ++ string_of_dimension(x)
    ++ ")"
  | `minmax(a, b) =>
    "minmax(" ++ string_of_minmax(a) ++ "," ++ string_of_minmax(b) ++ ")";

let string_of_dimensions = dimensions =>
  dimensions |> List.map(gridLengthToJs) |> String.concat(" ");

let gridTemplateColumns = dimensions =>
  D("gridTemplateColumns", string_of_dimensions(dimensions));

let gridTemplateRows = dimensions =>
  D("gridTemplateRows", string_of_dimensions(dimensions));

let gridAutoColumns = dimensions =>
  D("gridAutoColumns", string_of_dimension(dimensions));

let gridAutoRows = dimensions =>
  D("gridAutoRows", string_of_dimension(dimensions));

let gridArea = s =>
  D(
    "gridArea",
    switch (s) {
    | #GridArea.t as t => GridArea.toString(t)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let gridArea2 = (s, s2) =>
  D("gridArea", GridArea.toString(s) ++ " / " ++ GridArea.toString(s2));

let gridArea3 = (s, s2, s3) =>
  D(
    "gridArea",
    GridArea.toString(s)
    ++ " / "
    ++ GridArea.toString(s2)
    ++ " / "
    ++ GridArea.toString(s3),
  );

let gridArea4 = (s, s2, s3, s4) =>
  D(
    "gridArea",
    GridArea.toString(s)
    ++ " / "
    ++ GridArea.toString(s2)
    ++ " / "
    ++ GridArea.toString(s3)
    ++ " / "
    ++ GridArea.toString(s4),
  );

let gridTemplateAreas = l =>
  D(
    "gridTemplateAreas",
    switch (l) {
    | #GridTemplateAreas.t as t => GridTemplateAreas.toString(t)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

type filter = [
  | `blur(Length.t)
  | `brightness(float)
  | `contrast(float)
  | `dropShadow(Length.t, Length.t, Length.t, Color.t)
  | `grayscale(float)
  | `hueRotate(angle)
  | `invert(float)
  | `opacity(float)
  | `saturate(float)
  | `sepia(float)
  | `url(string)
  | `none
  | Cascading.t
];

let string_of_filter =
  fun
  | `blur(v) => "blur(" ++ Length.toString(v) ++ ")"
  | `brightness(v) => "brightness(" ++ Js.Float.toString(v) ++ "%)"
  | `contrast(v) => "contrast(" ++ Js.Float.toString(v) ++ "%)"
  | `dropShadow(a, b, c, d) =>
    "drop-shadow("
    ++ Length.toString(a)
    ++ " "
    ++ Length.toString(b)
    ++ " "
    ++ Length.toString(c)
    ++ " "
    ++ Color.toString(d)
    ++ ")"
  | `grayscale(v) => "grayscale(" ++ Js.Float.toString(v) ++ "%)"
  | `hueRotate(v) => "hue-rotate(" ++ Angle.toString(v) ++ ")"
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
  D("filter", x->Belt.List.map(string_of_filter)->join(" "));

module Shadow = {
  type value('a) = string;
  type box;
  type text;
  type t('a) = [ | `shadow(value('a)) | `none];

  let box = (~x=zero, ~y=zero, ~blur=zero, ~spread=zero, ~inset=false, color) =>
    `shadow(
      Length.toString(x)
      ++ " "
      ++ Length.toString(y)
      ++ " "
      ++ Length.toString(blur)
      ++ " "
      ++ Length.toString(spread)
      ++ " "
      ++ Color.toString(color)
      ++ (inset ? " inset" : ""),
    );

  let text = (~x=zero, ~y=zero, ~blur=zero, color) =>
    `shadow(
      Length.toString(x)
      ++ " "
      ++ Length.toString(y)
      ++ " "
      ++ Length.toString(blur)
      ++ " "
      ++ Color.toString(color),
    );

  let toString: t('a) => string =
    fun
    | `shadow(x) => x
    | `none => "none";
};

let boxShadow = x =>
  D(
    "boxShadow",
    switch (x) {
    | #Shadow.t as s => Shadow.toString(s)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let boxShadows = x =>
  D("boxShadow", x->Belt.List.map(Shadow.toString)->join(", "));

let string_of_borderstyle =
  fun
  | #BorderStyle.t as b => BorderStyle.toString(b)
  | #Cascading.t as c => Cascading.toString(c);

let border = (px, style, color) =>
  D(
    "border",
    Length.toString(px)
    ++ " "
    ++ string_of_borderstyle(style)
    ++ " "
    ++ Color.toString(color),
  );
let borderStyle = x => D("borderStyle", string_of_borderstyle(x));

let borderLeft = (px, style, color) =>
  D(
    "borderLeft",
    Length.toString(px)
    ++ " "
    ++ string_of_borderstyle(style)
    ++ " "
    ++ Color.toString(color),
  );
let borderLeftStyle = x => D("borderLeftStyle", string_of_borderstyle(x));

let borderRight = (px, style, color) =>
  D(
    "borderRight",
    Length.toString(px)
    ++ " "
    ++ string_of_borderstyle(style)
    ++ " "
    ++ Color.toString(color),
  );

let borderRightStyle = x => D("borderRightStyle", string_of_borderstyle(x));
let borderTop = (px, style, color) =>
  D(
    "borderTop",
    Length.toString(px)
    ++ " "
    ++ string_of_borderstyle(style)
    ++ " "
    ++ Color.toString(color),
  );

let borderTopStyle = x => D("borderTopStyle", string_of_borderstyle(x));

let borderBottom = (px, style, color) =>
  D(
    "borderBottom",
    Length.toString(px)
    ++ " "
    ++ string_of_borderstyle(style)
    ++ " "
    ++ Color.toString(color),
  );

let borderBottomStyle = x =>
  D("borderBottomStyle", string_of_borderstyle(x));

let background = x => D("background", string_of_background(x));
let backgrounds = bg =>
  D("background", bg->Belt.List.map(string_of_background)->join(", "));

let backgroundSize = x =>
  D(
    "backgroundSize",
    switch (x) {
    | `size(x, y) => Length.toString(x) ++ " " ++ Length.toString(y)
    | `auto => "auto"
    | `cover => "cover"
    | `contain => "contain"
    },
  );

let string_of_listStyleImage =
  fun
  | `none => "none"
  | `url(url) => "url(" ++ url ++ ")";

let listStyle = (style, pos, img) =>
  D(
    "listStyle",
    ListStyleType.toString(style)
    ++ " "
    ++ ListStylePosition.toString(pos)
    ++ " "
    ++ string_of_listStyleImage(img),
  );

let listStyleImage = x => D("listStyleImage", string_of_listStyleImage(x));

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

let fontFace = (~fontFamily, ~src, ~fontStyle=?, ~fontWeight=?, ()) => {
  let fontStyle =
    Js.Option.map((. value) => FontStyle.toString(value), fontStyle);
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
        | #FontWeight.t as f => FontWeight.toString(f)
        | #Cascading.t as c => Cascading.toString(c)
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

let textDecoration = x =>
  D(
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

let textShadow = x =>
  D(
    "textShadow",
    switch (x) {
    | #Shadow.t as s => Shadow.toString(s)
    | #Cascading.t as c => Cascading.toString(c)
    },
  );

let textShadows = x =>
  D("textShadow", x->Belt.List.map(Shadow.toString)->join(", "));

let transformStyle = x =>
  D(
    "transformStyle",
    switch (x) {
    | `preserve3d => "preserve-3d"
    | `flat => "flat"
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
      ++ TimingFunction.toString(timingFunction)
      ++ " "
      ++ string_of_time(delay)
      ++ " "
      ++ property,
    );

  let toString =
    fun
    | `value(v) => v;
};

let transitionValue = x => D("transition", Transition.toString(x));

let transitionList = x =>
  D("transition", x->Belt.List.map(Transition.toString)->join(", "));
let transitions = transitionList;

let transition = (~duration=?, ~delay=?, ~timingFunction=?, property) =>
  transitionValue(
    Transition.shorthand(~duration?, ~delay?, ~timingFunction?, property),
  );

let transitionDelay = i => D("transitionDelay", string_of_time(i));

let transitionDuration = i => D("transitionDuration", string_of_time(i));

let transitionTimingFunction = x =>
  D("transitionTimingFunction", TimingFunction.toString(x));

let transitionProperty = x => D("transitionProperty", x);

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
      ++ TimingFunction.toString(timingFunction)
      ++ " "
      ++ string_of_time(delay)
      ++ " "
      ++ AnimationIterationCount.toString(iterationCount)
      ++ " "
      ++ AnimationDirection.toString(direction)
      ++ " "
      ++ AnimationFillMode.toString(fillMode)
      ++ " "
      ++ AnimationPlayState.toString(playState),
    );

  let toString =
    fun
    | `value(v) => v;
};

let animationValue = x => D("animation", Animation.toString(x));

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
  D("animation", x->Belt.List.map(Animation.toString)->join(", "));

let animationName = x => D("animationName", x);

/**
 * SVG
 */
module SVG = {
  let fill = x => D("fill", Color.toString(x));
  let fillOpacity = opacity => D("fillOpacity", Js.Float.toString(opacity));
  let fillRule = x =>
    D(
      "fillRule",
      switch (x) {
      | `evenodd => "evenodd"
      | `nonzero => "nonzero"
      },
    );
  let stroke = x => D("stroke", Color.toString(x));
  let strokeWidth = x => D("strokeWidth", Length.toString(x));
  let strokeOpacity = opacity =>
    D("strokeOpacity", Js.Float.toString(opacity));
  let strokeMiterlimit = x => D("strokeMiterlimit", Js.Float.toString(x));
  let strokeLinecap = x =>
    D(
      "strokeLinecap",
      switch (x) {
      | `butt => "butt"
      | `round => "round"
      | `square => "square"
      },
    );

  let strokeLinejoin = x =>
    D(
      "strokeLinejoin",
      switch (x) {
      | `miter => "miter"
      | `round => "round"
      | `bevel => "bevel"
      },
    );
  let stopColor = x => D("stopColor", Color.toString(x));
  let stopOpacity = x => D("stopOpacity", Js.Float.toString(x));
};
