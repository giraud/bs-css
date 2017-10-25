/* /*
      ==============
      CSS properties
      ==============
    */

   let clear v => Property "clear" v;

   let clip v => Property "clip" v;


   let content v => Property "content" v;


   let cursor v => Property "cursor" v;

   let direction v => Property "direction" v;


   let filter v => Property "filter" v;




   let listStyle v => Property "listStyle" v;

   let listStyleImage v => Property "listStyleImage" v;

   let listStylePosition v => Property "listStylePosition" v;

   let listStyleType v => Property "listStyleType" v;



   let outline v => Property "outline" v;

   let outlineColor v => Property "outlineColor" v;

   let outlineStyle v => Property "outlineStyle" v;

   let outlineWidth v => Property "outlineWidth" v;

   type overflow =
     | Auto
     | Visible
     | Hidden
     | Scroll;

   let overflowToString v =>
     switch v {
     | Auto => "auto"
     | Visible => "visible"
     | Hidden => "hidden"
     | Scroll => "scroll"
     };

   let overflow v => Property "overflow" (overflowToString v);

   let overflowY v => Property "overflowY" (overflowToString v);

   let overflowX v => Property "overflowX" (overflowToString v);





   let size v => Property "size" v;



   let verticalAlign v => Property "verticalAlign" v;

   let visibility v => Property "visibility" v;

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



   let wordSpacing v => Property "wordSpacing" v;

   let zIndex v => Property "zIndex" (string_of_int v);

   let opacity v => Property "opacity" (from_float v);

   let backgroundOrigin v => Property "backgroundOrigin" v;

   let backgroundSize v => Property "backgroundSize" v;

   let backgroundClip v => Property "backgroundClip" v;


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
   let placeContent v => Property "placeContent" v;

   /* Basic User Interface Level 4 - FPWD */
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

   let strokeMiterlimit v => Property "strokeMiterlimit" v; */