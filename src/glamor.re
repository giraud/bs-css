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



   let fontKerning v => Property "fontKerning" v;


   let fontVariantNumeric v => Property "fontVariantNumeric" v;
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


   let boxSizing v =>
     Property
       "boxSizing"
       (
         switch v {
         | `content_box => "content-box"
         | `border_box => "border-box"
         }
       );



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


   let wordBreak v => Property "wordBreak" v;

   let wordWrap v => Property "wordWrap" v;

   /* Animations - WD */






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

   /* Basix Box Model - WD */


   let rotation v => Property "rotation" v;

   let rotationPoint v => Property "rotationPoint" v;
   */