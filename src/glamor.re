type styleObj;

external makeCSS : styleObj => string = "css" [@@bs.module "glamor"];

external makeGlobalCSS : string => styleObj => unit =
  "global" [@@bs.scope "css"] [@@bs.module "glamor"];

external makeKeyFrames : Js.Dict.t styleObj => string =
  "keyframes" [@@bs.scope "css"] [@@bs.module "glamor"];

let merge: list string => string = [%bs.raw
  {|
    function (styles) {
        const glamor = require('glamor');
        return glamor.css.apply(glamor, styles)
    }
|}
];

let addObjToStyles: styleObj => string => styleObj => styleObj = [%bs.raw
  {|
        function (obj, key, value) {
            var newObj = {};
            newObj[key] = value;
            return Object.assign({}, obj, newObj);
        }
    |}
];

let addStringToStyles: styleObj => string => string => styleObj = [%bs.raw
  {|
        function (obj, key, value) {
            var newObj = {};
            newObj[key] = value;
            return Object.assign({}, obj, newObj);
        }
    |}
];

let createEmptyObj: unit => styleObj = [%bs.raw
  {|
            function () {
                return {};
            }
    |}
];

let emptyObj = createEmptyObj ();

type declaration =
  | Nothing
  | Property string string
  | Selector string declarations
and declarations = list declaration;

let rec addDeclaration obj (decl: declaration) =>
  switch decl {
  | Nothing => obj
  | Property name value => addStringToStyles obj name value
  | Selector sel decls => addObjToStyles obj sel (declarationsToObj decls)
  }
and declarationsToObj decls => List.fold_left addDeclaration emptyObj decls;

let css decls => makeCSS (declarationsToObj decls);

let global selector declarations => makeGlobalCSS selector (declarationsToObj declarations);

let keyframes frames =>
  makeKeyFrames (frames |> List.map (fun (k, v) => (k, declarationsToObj v)) |> Js.Dict.fromList);

let empty = css [];

let unitToString unit =>
  switch unit {
  | `px => "px"
  | `pct => "%"
  | `rem => "rem"
  | `em => "em"
  | `vh => "vh"
  | `vw => "vw"
  | `cm => "cm"
  | `mm => "mm"
  | `pt => "pt"
  };

type cssUnit = [ | `px | `pct | `pct | `rem | `rem | `em | `em | `vh | `pt];

let from_float v => string_of_float v ^ "0";

let propertyWithUnit name unit::(unit: cssUnit)=`px v =>
  Property name (from_float v ^ unitToString unit);

/*
   ==============
   CSS properties
   ==============
 */
let azimouth v => Property "azimouth" v;

let background v => Property "background" v;

let backgroundAttachment v => Property "backgroundAttachment" v;

let backgroundColor v => Property "backgroundColor" v;

let backgroundImage v => Property "backgroundImage" v;

let backgroundPosition v => Property "backgroundPosition" v;

let backgroundRepeat v => Property "backgroundRepeat" v;

let border v => Property "border" v;

let borderCollapse v => Property "borderCollapse" v;

let borderColor v => Property "borderColor" v;

let borderSpacing v => Property "borderSpacing" v;

let borderStyle v => Property "borderStyle" v;

let borderTop v => Property "borderTop" v;

let borderRight v => Property "borderRight" v;

let borderBottom v => Property "borderBottom" v;

let borderLeft v => Property "borderLeft" v;

let borderTopColor v => Property "borderTopColor" v;

let borderRightColor v => Property "borderRightColor" v;

let borderBottomColor v => Property "borderBottomColor" v;

let borderLeftColor v => Property "borderLeftColor" v;

let borderTopStyle v => Property "borderTopStyle" v;

let borderRightStyle v => Property "borderRightStyle" v;

let borderBottomStyle v => Property "borderBottomStyle" v;

let borderLeftStyle v => Property "borderLeftStyle" v;

let borderTopWidth = propertyWithUnit "borderTopWidth";

let borderRightWidth = propertyWithUnit "borderRightWidth";

let borderBottomWidth = propertyWithUnit "borderBottomWidth";

let borderLeftWidth = propertyWithUnit "borderLeftWidth";

let borderWidth = propertyWithUnit "borderWidth";

let bottom = propertyWithUnit "bottom";

let captionSide v => Property "captionSide" v;

let clear v => Property "clear" v;

let clip v => Property "clip" v;

let color v => Property "color" v;

let content v => Property "content" v;

let counterIncrement v => Property "counterIncrement" v;

let counterReset v => Property "counterReset" v;

let cue v => Property "cue" v;

let cueAfter v => Property "cueAfter" v;

let cueBefore v => Property "cueBefore" v;

let cursor v => Property "cursor" v;

let direction v => Property "direction" v;

let display v =>
  Property
    "display"
    (
      switch v {
      | `block => "block"
      | `none => "none"
      | `inline => "inline"
      | `flex => "flex"
      | `grid => "grid"
      | `subgrid => "subgrid"
      | `contents => "contents"
      | `table => "table"
      | `tableRow => "table-row"
      | `tableCell => "table-cell"
      | `tableColumn => "table-column"
      | `inlineBlock => "inline-block"
      | `inlineTable => "inline-table"
      | `inlineFlex => "inline-flex"
      | `inlineGrid => "inline-grid"
      }
    );

let elevation v => Property "elevation" v;

let emptyCells v => Property "emptyCells" v;

let cssFloat v => Property "float" v;

let filter v => Property "filter" v;

let font v => Property "font" v;

let fontFamily v => Property "fontFamily" v;

let fontSize = propertyWithUnit "fontSize";

let fontSizeAdjust v => Property "fontSizeAdjust" v;

let fontStretch v => Property "fontStretch" v;

let fontStyle v => Property "fontStyle" v;

let fontVariant v => Property "fontVariant" v;

let fontWeight v =>
  Property
    "fontWeight"
    (
      switch v {
      | `normal => "normal"
      | `bold => "bold"
      | `_100 => "100"
      | `_200 => "200"
      | `_300 => "300"
      | `_400 => "400"
      | `_500 => "500"
      | `_600 => "600"
      | `_700 => "700"
      | `_800 => "800"
      | `_900 => "900"
      }
    );

let height = propertyWithUnit "height";

let left = propertyWithUnit "left";

let letterSpacing v => Property "letterSpacing" v;

let lineHeight v => Property "lineHeight" (from_float v);

let listStyle v => Property "listStyle" v;

let listStyleImage v => Property "listStyleImage" v;

let listStylePosition v => Property "listStylePosition" v;

let listStyleType v => Property "listStyleType" v;

let margin = propertyWithUnit "margin";

let marginTop = propertyWithUnit "marginTop";

let marginRight = propertyWithUnit "marginRight";

let marginBottom = propertyWithUnit "marginBottom";

let marginLeft = propertyWithUnit "marginLeft";

let markerOffset v => Property "markerOffset" v;

let marks v => Property "marks" v;

let maxHeight = propertyWithUnit "maxHeight";

let maxWidth = propertyWithUnit "maxWidth";

let minHeight = propertyWithUnit "minHeight";

let minWidth = propertyWithUnit "minWidth";

let orphans v => Property "orphans" v;

let outline v => Property "outline" v;

let outlineColor v => Property "outlineColor" v;

let outlineStyle v => Property "outlineStyle" v;

let outlineWidth v => Property "outlineWidth" v;

let overflow v =>
  Property
    "overflow"
    (
      switch v {
      | `auto => "auto"
      | `visible => "visible"
      | `hidden => "hidden"
      | `scroll => "scroll"
      }
    );

let overflowY v =>
  Property
    "overflowY"
    (
      switch v {
      | `auto => "auto"
      | `visible => "visible"
      | `hidden => "hidden"
      | `scroll => "scroll"
      }
    );

let overflowX v =>
  Property
    "overflowX"
    (
      switch v {
      | `auto => "auto"
      | `visible => "visible"
      | `hidden => "hidden"
      | `scroll => "scroll"
      }
    );

let padding = propertyWithUnit "padding";

let paddingTop = propertyWithUnit "paddingTop";

let paddingRight = propertyWithUnit "paddingRight";

let paddingBottom = propertyWithUnit "paddingBottom";

let paddingLeft = propertyWithUnit "paddingLeft";

let page v => Property "page" v;

let pageBreakAfter v => Property "pageBreakAfter" v;

let pageBreakBefore v => Property "pageBreakBefore" v;

let pageBreakInside v => Property "pageBreakInside" v;

let pause v => Property "pause" v;

let pauseAfter v => Property "pauseAfter" v;

let pauseBefore v => Property "pauseBefore" v;

let pitch v => Property "pitch" v;

let pitchRange v => Property "pitchRange" v;

let playDuring v => Property "playDuring" v;

let position v =>
  Property
    "position"
    (
      switch v {
      | `static => "static"
      | `relative => "relative"
      | `absolute => "absolute"
      | `fixed => "fixed"
      | `sticky => "sticky"
      }
    );

let quotes v => Property "quotes" v;

let richness v => Property "richness" v;

let right v => Property "right" (from_float v ^ "px");

let rightPct v => Property "right" (from_float v ^ "%");

let rightRem v => Property "right" (from_float v ^ "rem");

let size v => Property "size" v;

let speak v => Property "speak" v;

let speakHeader v => Property "speakHeader" v;

let speakNumeral v => Property "speakNumeral" v;

let speakPunctuation v => Property "speakPunctuation" v;

let speechRate v => Property "speechRate" v;

let stress v => Property "stress" v;

let tableLayout v => Property "tableLayout" v;

let textAlign v =>
  Property
    "textAlign"
    (
      switch v {
      | `auto => "auto"
      | `left => "left"
      | `right => "right"
      | `center => "center"
      | `justify => "justify"
      }
    );

let textDecoration v => Property "textDecoration" v;

let textIndent v => Property "textIndent" v;

let textShadow v => Property "textShadow" v;

let textTransform v => Property "textTransform" v;

let top = propertyWithUnit "top";

let unicodeBidi v => Property "unicodeBidi" v;

let verticalAlign v => Property "verticalAlign" v;

let visibility v => Property "visibility" v;

let voiceFamily v => Property "voiceFamily" v;

let volume v => Property "volume" v;

let whiteSpace v =>
  Property
    "whiteSpace"
    (
      switch v {
      | `normal => "normal"
      | `nowrap => "nowrap"
      | `pre => "pre"
      | `pre_wrap => "pre-wrap"
      | `pre_line => "preLine"
      }
    );

let widows v => Property "widows" v;

let width = propertyWithUnit "width";

let wordSpacing v => Property "wordSpacing" v;

let zIndex v => Property "zIndex" (string_of_int v);

/* Below properties based on https://www.w3.org/Style/CSS/all-properties */
/* Color Level 3 - REC */
let opacity v => Property "opacity" (from_float v);

/* Backgrounds and Borders Level 3 - CR */
/* backgroundRepeat - already defined by CSS2Properties */
/* backgroundAttachment - already defined by CSS2Properties */
let backgroundOrigin v => Property "backgroundOrigin" v;

let backgroundSize v => Property "backgroundSize" v;

let backgroundClip v => Property "backgroundClip" v;

let borderRadius v => Property "borderRadius" (string_of_int v);

let borderTopLeftRadius v => Property "borderTopLeftRadius" (string_of_int v);

let borderTopRightRadius v => Property "borderTopRightRadius" (string_of_int v);

let borderBottomLeftRadius v => Property "borderBottomLeftRadius" (string_of_int v);

let borderBottomRightRadius v => Property "borderBottomRightRadius" (string_of_int v);

let borderImage v => Property "borderImage" v;

let borderImageSource v => Property "borderImageSource" v;

let borderImageSlice v => Property "borderImageSlice" v;

let borderImageWidth v => Property "borderImageWidth" v;

let borderImageOutset v => Property "borderImageOutset" v;

let borderImageRepeat v => Property "borderImageRepeat" v;

let boxShadow v => Property "boxShadow" v;

/* Multi-column Layout - CR */
let columns v => Property "columns" v;

let columnCount v => Property "columnCount" v;

let columnFill v => Property "columnFill" v;

let columnGap v => Property "columnGap" v;

let columnRule v => Property "columnRule" v;

let columnRuleColor v => Property "columnRuleColor" v;

let columnRuleStyle v => Property "columnRuleStyle" v;

let columnRuleWidth v => Property "columnRuleWidth" v;

let columnSpan v => Property "columnSpan" v;

let columnWidth v => Property "columnWidth" v;

let breakAfter v => Property "breakAfter" v;

let breakBefore v => Property "breakBefore" v;

let breakInside v => Property "breakInside" v;

/* Speech - CR */
let rest v => Property "rest" v;

let restAfter v => Property "restAfter" v;

let restBefore v => Property "restBefore" v;

let speakAs v => Property "speakAs" v;

let voiceBalance v => Property "voiceBalance" v;

let voiceDuration v => Property "voiceDuration" v;

let voicePitch v => Property "voicePitch" v;

let voiceRange v => Property "voiceRange" v;

let voiceRate v => Property "voiceRate" v;

let voiceStress v => Property "voiceStress" v;

let voiceVolume v => Property "voiceVolume" v;

/* Image Values and Replaced Content Level 3 - CR */
let objectFit v => Property "objectFit" v;

let objectPosition v => Property "objectPosition" v;

let imageResolution v => Property "imageResolution" v;

let imageOrientation v => Property "imageOrientation" v;

/* Flexible Box Layout - CR */
let alignContent v =>
  Property
    "alignContent"
    (
      switch v {
      | `flexStart => "flex-start"
      | `flexEnd => "flex-end"
      | `center => "center"
      | `stretch => "stretch"
      | `spaceAround => "space-around"
      | `spaceBetween => "space-between"
      }
    );

let alignItems v =>
  Property
    "alignItems"
    (
      switch v {
      | `flexStart => "flex-start"
      | `flexEnd => "flex-end"
      | `center => "center"
      | `stretch => "stretch"
      | `baseline => "baseline"
      }
    );

let alignSelf v =>
  Property
    "alignSelf"
    (
      switch v {
      | `flexStart => "flex-start"
      | `flexEnd => "flex-end"
      | `center => "center"
      | `stretch => "stretch"
      | `baseline => "baseline"
      }
    );

let flex v => Property "flex" (string_of_int v);

let flexBasis v => Property "flexBasis" (string_of_int v);

let flexDirection v =>
  Property
    "flexDirection"
    (
      switch v {
      | `row => "row"
      | `rowReverse => "row-reverse"
      | `column => "column"
      | `columnReverse => "column-reverse"
      }
    );

let flexFlow v => Property "flexFlow" (string_of_int v);

let flexGrow v => Property "flexGrow" (string_of_int v);

let flexShrink v => Property "flexShrink" (string_of_int v);

let flexWrap v =>
  Property
    "flexWrap"
    (
      switch v {
      | `wrap => "wrap"
      | `nowrap => "nowrap"
      }
    );

let justifyContent v =>
  Property
    "justifyContent"
    (
      switch v {
      | `flexStart => "flex-start"
      | `flexEnd => "flex-end"
      | `center => "center"
      | `stretch => "stretch"
      | `spaceAround => "space-around"
      | `spaceBetween => "space-between"
      }
    );

let order v => Property "order" v;

/* Text Decoration Level 3 - CR */
/* textDecoration - already defined by CSS2Properties */
let textDecorationColor v => Property "textDecorationColor" v;

let textDecorationLine v => Property "textDecorationLine" v;

let textDecorationSkip v => Property "textDecorationSkip" v;

let textDecorationStyle v => Property "textDecorationStyle" v;

let textEmphasis v => Property "textEmphasis" v;

let textEmphasisColor v => Property "textEmphasisColor" v;

let textEmphasisPosition v => Property "textEmphasisPosition" v;

let textEmphasisStyle v => Property "textEmphasisStyle" v;

/* textShadow - already defined by CSS2Properties */
let textUnderlinePosition v => Property "textUnderlinePosition" v;

/* Fonts Level 3 - CR */
let fontFeatureSettings v => Property "fontFeatureSettings" v;

let fontKerning v => Property "fontKerning" v;

let fontLanguageOverride v => Property "fontLanguageOverride" v;

/* fontSizeAdjust - already defined by CSS2Properties */
/* fontStretch - already defined by CSS2Properties */
let fontSynthesis v => Property "fontSynthesis" v;

let forntVariantAlternates v => Property "forntVariantAlternates" v;

let fontVariantCaps v => Property "fontVariantCaps" v;

let fontVariantEastAsian v => Property "fontVariantEastAsian" v;

let fontVariantLigatures v => Property "fontVariantLigatures" v;

let fontVariantNumeric v => Property "fontVariantNumeric" v;

let fontVariantPosition v => Property "fontVariantPosition" v;

/* Cascading and Inheritance Level 3 - CR */
let all v => Property "all" v;

/* Writing Modes Level 3 - CR */
let glyphOrientationVertical v => Property "glyphOrientationVertical" v;

let textCombineUpright v => Property "textCombineUpright" v;

let textOrientation v => Property "textOrientation" v;

let writingMode v => Property "writingMode" v;

/* Shapes Level 1 - CR */
let shapeImageThreshold v => Property "shapeImageThreshold" v;

let shapeMargin v => Property "shapeMargin" v;

let shapeOutside v => Property "shapeOutside" v;

/* Masking Level 1 - CR */
let clipPath v => Property "clipPath" v;

let clipRule v => Property "clipRule" v;

let mask v => Property "mask" v;

let maskBorder v => Property "maskBorder" v;

let maskBorderMode v => Property "maskBorderMode" v;

let maskBorderOutset v => Property "maskBorderOutset" v;

let maskBorderRepeat v => Property "maskBorderRepeat" v;

let maskBorderSlice v => Property "maskBorderSlice" v;

let maskBorderSource v => Property "maskBorderSource" v;

let maskBorderWidth v => Property "maskBorderWidth" v;

let maskClip v => Property "maskClip" v;

let maskComposite v => Property "maskComposite" v;

let maskImage v => Property "maskImage" v;

let maskMode v => Property "maskMode" v;

let maskOrigin v => Property "maskOrigin" v;

let maskPosition v => Property "maskPosition" v;

let maskRepeat v => Property "maskRepeat" v;

let maskSize v => Property "maskSize" v;

let maskType v => Property "maskType" v;

/* Compositing and Blending Level 1 - CR */
let backgroundBlendMode v => Property "backgroundBlendMode" v;

let isolation v => Property "isolation" v;

let mixBlendMode v => Property "mixBlendMode" v;

/* Fragmentation Level 3 - CR */
let boxDecorationBreak v => Property "boxDecorationBreak" v;

/* breakAfter - already defined by Multi-column Layout */
/* breakBefore - already defined by Multi-column Layout */
/* breakInside - already defined by Multi-column Layout */
/* Basic User Interface Level 3 - CR */
let boxSizing v =>
  Property
    "boxSizing"
    (
      switch v {
      | `content_box => "content-box"
      | `border_box => "border-box"
      }
    );

let caretColor v => Property "caretColor" v;

let navDown v => Property "navDown" v;

let navLeft v => Property "navLeft" v;

let navRight v => Property "navRight" v;

let navUp v => Property "navUp" v;

let outlineOffset v => Property "outlineOffset" v;

let resize v => Property "resize" v;

let textOverflow v => Property "textOverflow" v;

/* Grid Layout Level 1 - CR */
let grid v => Property "grid" v;

let gridArea v => Property "gridArea" v;

let gridAutoColumns v => Property "gridAutoColumns" v;

let gridAutoFlow v => Property "gridAutoFlow" v;

let gridAutoRows v => Property "gridAutoRows" v;

let gridColumn v => Property "gridColumn" v;

let gridColumnEnd v => Property "gridColumnEnd" v;

let gridColumnGap v => Property "gridColumnGap" v;

let gridColumnStart v => Property "gridColumnStart" v;

let gridGap v => Property "gridGap" v;

let gridRow v => Property "gridRow" v;

let gridRowEnd v => Property "gridRowEnd" v;

let gridRowGap v => Property "gridRowGap" v;

let gridRowStart v => Property "gridRowStart" v;

let gridTemplate v => Property "gridTemplate" v;

let gridTempalteAreas v => Property "gridTempalteAreas" v;

let gridTemplateColumns v => Property "gridTemplateColumns" v;

let gridTemplateRows v => Property "gridTemplateRows" v;

/* Will Change Level 1 - CR */
let willChange v => Property "willChange" v;

/* Text Level 3 - LC */
let hangingPunctuation v => Property "hangingPunctuation" v;

let hyphens v => Property "hyphens" v;

/* letterSpacing - already defined by CSS2Properties */
let lineBreak v => Property "lineBreak" v;

let overflowWrap v => Property "overflowWrap" v;

let tabSize v => Property "tabSize" v;

/* textAlign - already defined by CSS2Properties */
let textAlignLast v => Property "textAlignLast" v;

let textJustify v => Property "textJustify" v;

let wordBreak v => Property "wordBreak" v;

let wordWrap v => Property "wordWrap" v;

/* Animations - WD */
let animation v => Property "animation" v;

let animationDelay v => Property "animationDelay" (string_of_float v ^ "s");

let animationDirection v =>
  Property
    "animationDirection"
    (
      switch v {
      | `normal => "normal"
      | `reverse => "reverse"
      | `alternate => "alternate"
      | `alternate_reverse => "alternate-reverse"
      }
    );

let animationDuration v => Property "animationDuration" (string_of_float v ^ "s");

let animationFillMode v =>
  Property
    "animationFillMode"
    (
      switch v {
      | `none => "none"
      | `forwards => "forwards"
      | `backwards => "backwards"
      | `both => "both"
      }
    );

let animationIterationCount v => Property "animationIterationCount" v;

let animationName v => Property "animationName" v;

let animationPlayState v => Property "animationPlayState" v;

let animationTimingFunction v => Property "animationTimingFunction" v;

/* Transitions - WD */
let transition v => Property "transition" v;

let transitionDelay v => Property "transitionDelay" v;

let transitionDuration v => Property "transitionDuration" v;

let transitionProperty v => Property "transitionProperty" v;

let transitionTimingFunction v => Property "transitionTimingFunction" v;

/* Transforms Level 1 - WD */
let backfaceVisibility v => Property "backfaceVisibility" v;

let perspective v => Property "perspective" v;

let perspectiveOrigin v => Property "perspectiveOrigin" v;

let transform v => Property "transform" v;

let transformOrigin v => Property "transformOrigin" v;

let transformStyle v => Property "transformStyle" v;

/* Box Alignment Level 3 - WD */
/* alignContent - already defined by Flexible Box Layout */
/* alignItems - already defined by Flexible Box Layout */
let justifyItems v => Property "justifyItems" v;

let justifySelf v => Property "justifySelf" v;

let placeContent v => Property "placeContent" v;

let placeItems v => Property "placeItems" v;

let placeSelf v => Property "placeSelf" v;

/* Basic User Interface Level 4 - FPWD */
let appearance v => Property "appearance" v;

let caret v => Property "caret" v;

let caretAnimation v => Property "caretAnimation" v;

let caretShape v => Property "caretShape" v;

let userSelect v => Property "userSelect" v;

/* Overflow Level 3 - WD */
let maxLines v => Property "maxLines" v;

/* Basix Box Model - WD */
let marqueeDirection v => Property "marqueeDirection" v;

let marqueeLoop v => Property "marqueeLoop" v;

let marqueeSpeed v => Property "marqueeSpeed" v;

let marqueeStyle v => Property "marqueeStyle" v;

let overflowStyle v => Property "overflowStyle" v;

let rotation v => Property "rotation" v;

let rotationPoint v => Property "rotationPoint" v;

/* svg */
let fill v => Property "fill" v;

let stroke v => Property "stroke" v;

let strokeWidth v => Property "strokeWidth" v;

let strokeMiterlimit v => Property "strokeMiterlimit" v;