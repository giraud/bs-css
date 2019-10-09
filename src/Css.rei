/* Css documentation is copy/pasted from mozilla mdn web docs */

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

/**
 The CSS align-content property sets the distribution of space between and around content items along a flexbox's
 cross-axis or a grid's block axis.
 */
let alignContent:
  [
    Types.AlignContent.t
    | Types.NormalAlignment.t
    | Types.BaselineAlignment.t
    | Types.DistributedAlignment.t
    | Types.Cascading.t
  ] =>
  rule;

/**
 The CSS align-items property sets the align-self value on all direct children as a group.
 In Flexbox, it controls the alignment of items on the Cross Axis.
 In Grid Layout, it controls the alignment of items on the Block Axis within their grid area.
 */
let alignItems:
  [
    Types.AlignItems.t
    | Types.PositionalAlignment.t
    | Types.BaselineAlignment.t
    | Types.Cascading.t
  ] =>
  rule;

/**
 The align-self CSS property overrides a grid or flex item's align-items value.
 In Grid, it aligns the item inside the grid area. In Flexbox, it aligns the item on the cross axis.
 */
let alignSelf:
  [
    Types.AlignSelf.t
    | Types.PositionalAlignment.t
    | Types.BaselineAlignment.t
    | Types.Cascading.t
  ] =>
  rule;

/**
 The animation-delay CSS property sets when an animation starts.
 The animation can start later, immediately from its beginning, or immediately and partway through the animation.
 */
let animationDelay: int => rule;

/**
 The animation-direction CSS property sets whether an animation should play forwards, backwards,
 or alternating back and forth.
 */
let animationDirection: Types.AnimationDirection.t => rule;

/**
 The animation-duration CSS property sets the length of time that an animation takes to complete one cycle.
 */
let animationDuration: int => rule;

/**
 The animation-fill-mode CSS property sets how a CSS animation applies styles to its target before and after
 its execution.
 */
let animationFillMode: Types.AnimationFillMode.t => rule;

/**
 The animation-iteration-count CSS property sets the number of times an animation cycle should be played
 before stopping.
 */
let animationIterationCount: Types.AnimationIterationCount.t => rule;

/**
 The animation-play-state CSS property sets whether an animation is running or paused.
 */
let animationPlayState: Types.AnimationPlayState.t => rule;

/**
 The animation-timing-function CSS property sets how an animation progresses through the duration of each cycle.
 */
let animationTimingFunction: Types.TimingFunction.t => rule;

/* Warning: experimental */
let backfaceVisibility:
  [ Types.BackfaceVisibility.t | Types.Cascading.t] => rule;

/**
 The background-attachment CSS property sets whether a background image's position is fixed within the viewport,
 or scrolls with its containing block.
 */
let backgroundAttachment:
  [ Types.BackgroundAttachment.t | Types.Cascading.t] => rule;

/**
 The background-color CSS property sets the background color of an element.
 */
let backgroundColor: Types.Color.t => rule;

/**
 The background-clip CSS property sets whether an element's background extends underneath its border box,
 padding box, or content box.
 */
let backgroundClip: [ Types.BackgroundClip.t | Types.Cascading.t] => rule;

/**
 The background-image CSS property sets one or more background images on an element.
 */
let backgroundImage:
  [ Types.BackgroundImage.t | Types.Url.t | Types.Gradient.t] => rule;

/**
 The background-origin CSS property sets the background's origin: from the border start,
 inside the border, or inside the padding.
 */
let backgroundOrigin: [ Types.BackgroundClip.t | Types.Cascading.t] => rule;

/**
 The background-position CSS property sets the initial position for each background image.
 The position is relative to the position layer set by background-origin.
 */
let backgroundPosition: ([ Types.Length.t], [ Types.Length.t]) => rule;

/**
 The background-repeat CSS property sets how background images are repeated.
 A background image can be repeated along the horizontal and vertical axes, or not repeated at all.
 */
let backgroundRepeat:
  [
    Types.BackgroundRepeat.t
    | `hv(Types.BackgroundRepeat.horizontal, Types.BackgroundRepeat.vertical)
    | Types.Cascading.t
  ] =>
  rule;

/**
 The border-bottom shorthand CSS property sets an element's bottom border.
 It sets the values of border-bottom-width, border-bottom-style and border-bottom-color.
 */
let borderBottom:
  (
    Types.Length.t,
    [ Types.BorderStyle.t | Types.Cascading.t],
    Types.Color.t
  ) =>
  rule;

/**
 The border-bottom-color CSS property sets the color of an element's bottom border.
 It can also be set with the shorthand CSS properties border-color or border-bottom.
 */
let borderBottomColor: Types.Color.t => rule;

/**
 The border-bottom-left-radius CSS property rounds the bottom-left corner of an element.
 */
let borderBottomLeftRadius: Types.Length.t => rule;

/**
 The border-bottom-right-radius CSS property rounds the bottom-right corner of an element.
 */
let borderBottomRightRadius: Types.Length.t => rule;

/**
 The border-bottom-style CSS property sets the line style of an element's bottom border.
 */
let borderBottomStyle: [ Types.BorderStyle.t | Types.Cascading.t] => rule;

/**
 The border-bottom-width CSS property sets the width of the bottom border of an element.
 */
let borderBottomWidth: Types.Length.t => rule;

/**
 The border-collapse CSS property sets whether cells inside a <table> have shared or separate borders.
 */
let borderCollapse: [ Types.BorderCollapse.t | Types.Cascading.t] => rule;

/**
 The border-color shorthand CSS property sets the color of an element's border.
 */
let borderColor: Types.Color.t => rule;

/**
 The border-left shorthand CSS property set an element's left border.
 */
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

/**
 The border-style shorthand CSS property sets the line style for all four sides of an element's border.
 */
let borderStyle: [ Types.BorderStyle.t | Types.Cascading.t] => rule;

let borderTopColor: Types.Color.t => rule;

let borderTopLeftRadius: Types.Length.t => rule;

let borderTopRightRadius: Types.Length.t => rule;

let borderTopStyle: [ Types.BorderStyle.t | Types.Cascading.t] => rule;

let borderTopWidth: Types.Length.t => rule;

let borderWidth: Types.Length.t => rule;

let bottom: [ Types.Length.t | Types.Cascading.t] => rule;

/**
 The box-sizing CSS property sets how the total width and height of an element is calculated.
 */
let boxSizing: [ Types.BoxSizing.t | Types.Cascading.t] => rule;

let boxShadow: [ Shadow.t(Shadow.box) | Types.Cascading.t] => rule;

let boxShadows: list([ Shadow.t(Shadow.box)]) => rule;

/**
 The clear CSS property sets whether an element must be moved below (cleared) floating elements that precede it.
 The clear property applies to floating and non-floating elements.
 */
let clear: [ Types.Clear.t | Types.Cascading.t] => rule;

/**
 The clip-path CSS property creates a clipping region that sets what part of an element should be shown.
 Parts that are inside the region are shown, while those outside are hidden.
 */
let clipPath:
  [ Types.ClipPath.t | Types.Url.t | Types.GeometyBox.t | Types.Cascading.t] =>
  rule;

let color: Types.Color.t => rule;

/**
 The column-count CSS property breaks an element's content into the specified number of columns.
 */
let columnCount: [ Types.ColumnCount.t | Types.Cascading.t] => rule;

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

/**
 The flex CSS property sets how a flex item will grow or shrink to fit the space available in its flex container.
 It is a shorthand for flex-grow, flex-shrink, and flex-basis.
 */
let flex: [ Types.Flex.t | `num(float)] => rule;

/**
 The flex-basis CSS property sets the initial main size of a flex item.
 It sets the size of the content box unless otherwise set with box-sizing.
 */
let flexBasis:
  [ Types.FlexBasis.t | Types.Percentage.t | Types.Length.t] => rule;

/**
 The flex-direction CSS property sets how flex items are placed in the flex container defining the main axis and the direction (normal or reversed).
 */
let flexDirection: [ Types.FlexDirection.t | Types.Cascading.t] => rule;

let flexGrow: float => rule;

let flexShrink: float => rule;

/**
 The flex-wrap CSS property sets whether flex items are forced onto one line or can wrap onto multiple lines.
 If wrapping is allowed, it sets the direction that lines are stacked.
 */
let flexWrap: [ Types.FlexWrap.t | Types.Cascading.t] => rule;

/**
 The float CSS property places an element on the left or right side of its container,
 allowing text and inline elements to wrap around it.
 The element is removed from the normal flow of the page, though still remaining a part of the flow
 (in contrast to absolute positioning).
 */
let float: [ Types.Float.t | Types.Cascading.t] => rule;

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

/**
 The grid-area CSS property is a shorthand property for grid-row-start, grid-column-start, grid-row-end and
 grid-column-end, specifying a grid item’s size and location within the grid by contributing a line, a span,
 or nothing (automatic) to its grid placement, thereby specifying the edges of its grid area.
 */
let gridArea: [ Types.GridArea.t | Types.Cascading.t] => rule;
let gridArea2: (Types.GridArea.t, Types.GridArea.t) => rule;
let gridArea3: (Types.GridArea.t, Types.GridArea.t, Types.GridArea.t) => rule;
let gridArea4:
  (Types.GridArea.t, Types.GridArea.t, Types.GridArea.t, Types.GridArea.t) =>
  rule;

/**
 The grid-auto-flow CSS property controls how the auto-placement algorithm works,
 specifying exactly how auto-placed items get flowed into the grid.
 */
let gridAutoFlow: [ Types.GridAutoFlow.t | Types.Cascading.t] => rule;

/**
 The grid-column CSS property is a shorthand property for grid-column-start and grid-column-end
 specifying a grid item's size and location within the grid column by contributing a line, a span,
 or nothing (automatic) to its grid placement, thereby specifying the inline-start and
 inline-end edge of its grid area.
 */
let gridColumn: (int, int) => rule;

/**
 The grid-column-end CSS property specifies a grid item’s end position within the grid column by contributing a line,
 a span, or nothing (automatic) to its grid placement, thereby specifying the block-end edge of its grid area.
 */
let gridColumnEnd: int => rule;

/**
 The column-gap CSS property sets the size of the gap (gutter) between an element's columns.
 */
let gridColumnGap:
  [
    Types.GridColumnGap.t
    | Types.Percentage.t
    | Types.Length.t
    | Types.Cascading.t
  ] =>
  rule;

/**
 The grid-column-start CSS property specifies a grid item’s start position within the grid column
 by contributing a line, a span, or nothing (automatic) to its grid placement.
 This start position defines the block-start edge of the grid area.
 */
let gridColumnStart: int => rule;

/**
 The gap CSS property sets the gaps (gutters) between rows and columns. It is a shorthand for row-gap and column-gap.
 */
let gridGap:
  [ Types.Percentage.t | Types.Length.t | Types.Cascading.t] => rule;

/**
 The grid-row CSS property is a shorthand property for grid-row-start and grid-row-end specifying a grid item’s size
 and location within the grid row by contributing a line, a span, or nothing (automatic) to its grid placement,
 thereby specifying the inline-start and inline-end edge of its grid area.
 */
let gridRow: (int, int) => rule;

/**
 The grid-row-end CSS property specifies a grid item’s end position within the grid row by contributing a line, a span,
 or nothing (automatic) to its grid placement, thereby specifying the inline-end edge of its grid area.
 */
let gridRowEnd: int => rule;

/**
 The row-gap CSS property sets the size of the gap (gutter) between an element's grid rows.
 */
let gridRowGap:
  [ Types.Percentage.t | Types.Length.t | Types.Cascading.t] => rule;

/**
 The grid-row-start CSS property specifies a grid item’s start position within the grid row by contributing a line,
 a span, or nothing (automatic) to its grid placement, thereby specifying the inline-start edge of its grid area.
 */
let gridRowStart: int => rule;

/**
 The grid-template-areas CSS property specifies named grid areas.
 */
let gridTemplateAreas:
  [ Types.GridTemplateAreas.t | Types.Cascading.t] => rule;

/**
 The height CSS property specifies the height of an element.
 By default, the property defines the height of the content area.
 If box-sizing is set to border-box, however, it instead determines the height of the border area.
 */
let height:
  [
    Types.Height.t
    | Types.Percentage.t
    | Types.Length.t
    | Types.Cascading.t
  ] =>
  rule;

/**
 The CSS justify-content property defines how the browser distributes space between and around content items
 along the main-axis of a flex container, and the inline axis of a grid container.
 */
let justifyContent:
  [
    Types.PositionalAlignment.t
    | Types.NormalAlignment.t
    | Types.DistributedAlignment.t
    | Types.Cascading.t
  ] =>
  rule;

/**
 The CSS justify-self property sets the way a box is justified inside its alignment container along the appropriate axis.
 */
let justifySelf:
  [
    Types.JustifySelf.t
    | Types.PositionalAlignment.t
    | Types.BaselineAlignment.t
    | Types.Cascading.t
  ] =>
  rule;

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

/**
 The list-style CSS property is a shorthand to set list style properties list-style-type,
 list-style-image, and list-style-position.
 */
let listStyle:
  (
    Types.ListStyleType.t,
    Types.ListStylePosition.t,
    [ Types.ListStyleImage.t | Types.Url.t]
  ) =>
  rule;

/**
 The list-style-image CSS property sets an image to be used as the list item marker.
 It is often more convenient to use the shorthand list-style.
 */
let listStyleImage:
  [ Types.ListStyleImage.t | Types.Url.t | Types.Cascading.t] => rule;

/**
 The list-style-type CSS property sets the marker (such as a disc, character, or custom counter style) of a list item element.
 */
let listStyleType: [ Types.ListStyleType.t | Types.Cascading.t] => rule;

/**
 The list-style-position CSS property sets the position of the ::marker relative to a list item.
 */
let listStylePosition:
  [ Types.ListStylePosition.t | Types.Cascading.t] => rule;

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

/**
 The max-height CSS property sets the maximum height of an element.
 It prevents the used value of the height property from becoming larger than the value specified for max-height.
 */
let maxHeight:
  [
    Types.MaxHeight.t
    | Types.Percentage.t
    | Types.Length.t
    | Types.Cascading.t
  ] =>
  rule;

/**
 The max-width CSS property sets the maximum width of an element.
 It prevents the used value of the width property from becoming larger than the value specified by max-width.
 */
let maxWidth:
  [
    Types.MaxWidth.t
    | Types.Percentage.t
    | Types.Length.t
    | Types.Cascading.t
  ] =>
  rule;

/**
 The min-height CSS property sets the minimum height of an element.
 It prevents the used value of the height property from becoming smaller than the value specified for min-height.
 */
let minHeight:
  [
    Types.Height.t
    | Types.Percentage.t
    | Types.Length.t
    | Types.Cascading.t
  ] =>
  rule;

/**
 The min-width CSS property sets the minimum width of an element.
 It prevents the used value of the width property from becoming smaller than the value specified for min-width.
 */
let minWidth:
  [ Types.Width.t | Types.Percentage.t | Types.Length.t | Types.Cascading.t] =>
  rule;

/**
 The object-fit CSS property sets how the content of a replaced element,
 such as an <img> or <video>, should be resized to fit its container.
 */
let objectFit: [ Types.ObjectFit.t | Types.Cascading.t] => rule;

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

/**
 The overflow-wrap CSS property applies to inline elements, setting whether the browser
 should insert line breaks within an otherwise unbreakable string to prevent text
 from overflowing its line box.
 */
let overflowWrap: [ Types.OverflowWrap.t | Types.Cascading.t] => rule;

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

/**
 The perspective CSS property determines the distance between the z=0 plane and the user in order
 to give a 3D-positioned element some perspective.
 Each 3D element with z>0 becomes larger; each 3D-element with z<0 becomes smaller.
 The strength of the effect is determined by the value of this property.
 */
let perspective:
  [ Types.Perspective.t | Types.Length.t | Types.Cascading.t] => rule;

/**
 The perspective-origin CSS property determines the position at which the viewer is looking.
 It is used as the vanishing point by the perspective property.
 */
let perspectiveOrigin:
  (
    [ Types.Perspective.t | Types.Length.t],
    [ Types.Perspective.t | Types.Length.t]
  ) =>
  rule;

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

/**
 The table-layout CSS property sets the algorithm used to lay out <table> cells, rows, and columns.
 */
let tableLayout: [ Types.TableLayout.t | Types.Cascading.t] => rule;

/**
 The text-align CSS property sets the horizontal alignment of a block element or table-cell box.
 This means it works like vertical-align but in the horizontal direction.
 */
let textAlign: [ Types.TextAlign.t | Types.Cascading.t] => rule;

/**
 The text-decoration-color CSS property sets the color of decorations added to text by text-decoration-line.
 */
let textDecorationColor: [ Types.Color.t | Types.Cascading.t] => rule;

/**
 The text-decoration-line CSS property sets the kind of decoration
 that is used on text in an element, such as an underline or overline.
 */
let textDecorationLine:
  [ Types.TextDecorationLine.t | Types.Cascading.t] => rule;

/**
 The text-decoration-style CSS property sets the style of the lines specified by text-decoration-line.
 The style applies to all lines that are set with text-decoration-line.
 */
let textDecorationStyle:
  [ Types.TextDecorationStyle.t | Types.Cascading.t] => rule;

/**
 The text-indent CSS property sets the length of empty space (indentation)
 that is put before lines of text in a block.
 */
let textIndent:
  [ Types.Percentage.t | Types.Length.t | Types.Cascading.t] => rule;

/**
 The text-overflow CSS property sets how hidden overflow content is signaled to users.
 It can be clipped, display an ellipsis ('…'), or display a custom string.
 */
let textOverflow: [ Types.TextOverflow.t | Types.Cascading.t] => rule;

/**
 The text-shadow CSS property adds shadows to text.
 It accepts a comma-separated list of shadows to be applied to the text and any of its decorations.
 Each shadow is described by some combination of X and Y offsets from the element, blur radius, and color.
 */
let textShadow: [ Shadow.t(Shadow.text) | Types.Cascading.t] => rule;
let textShadows: list([ Shadow.t(Shadow.text)]) => rule;

/**
 The text-transform CSS property specifies how to capitalize an element's text.
 It can be used to make text appear in all-uppercase or all-lowercase, or with each word capitalized.
 */
let textTransform: [ Types.TextTransform.t | Types.Cascading.t] => rule;

let top: [ Types.Length.t | Types.Cascading.t] => rule;

let transform: Types.Transform.t => rule;

let transforms: list(Types.Transform.t) => rule;

/**
 The transform-origin CSS property sets the origin for an element's transformations.
 */
let transformOrigin: (Types.Length.t, Types.Length.t) => rule;
let transformOrigin3d:
  (Types.Length.t, Types.Length.t, Types.Length.t) => rule;

let transitionDelay: int => rule;

let transitionDuration: int => rule;

let transitionProperty: string => rule;

let transformStyle: [ Types.TransformStyle.t | Types.Cascading.t] => rule;

let transitionTimingFunction: Types.TimingFunction.t => rule;

/**
 The user-select CSS property controls whether the user can select text.
 This doesn't have any effect on content loaded as chrome, except in textboxes.
 */
let userSelect: [ Types.UserSelect.t | Types.Cascading.t] => rule;

/**
 The vertical-align CSS property sets vertical alignment of an inline or table-cell box.
 */
let verticalAlign:
  [ Types.VerticalAlign.t | Types.Length.t | Types.Cascading.t] => rule;

/**
 The visibility CSS property shows or hides an element without changing the layout of a document.
 The property can also hide rows or columns in a <table>.
 */
let visibility: [ Types.Visibility.t | Types.Cascading.t] => rule;

/**
 The width CSS property sets an element's width.
 By default, it sets the width of the content area, but if box-sizing is set to border-box,
 it sets the width of the border area.
 */
let width:
  [ Types.Width.t | Types.Percentage.t | Types.Length.t | Types.Cascading.t] =>
  rule;

/**
 The white-space CSS property sets how white space inside an element is handled.
 */
let whiteSpace: [ Types.WhiteSpace.t | Types.Cascading.t] => rule;

/**
 The word-break CSS property sets whether line breaks appear wherever the text would otherwise overflow its content box.
 */
let wordBreak: [ Types.WordBreak.t | Types.Cascading.t] => rule;

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
 see overflowWrap
 */
let wordWrap: [ Types.OverflowWrap.t | Types.Cascading.t] => rule;

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

/** type selector */

/*
 Pseudo-classes selectors

 A CSS pseudo-class is a keyword added to a selector that specifies a special state of the selected element(s).
 */

/**
 The :active CSS pseudo-class represents an element (such as a button) that is being activated by the user.
 When using a mouse, "activation" typically starts when the user presses down the primary mouse button.
 */
let active: list(rule) => rule;

/**
 The :checked CSS pseudo-class selector represents any radio (<input type="radio">), checkbox (<input type="checkbox">),
 or option (<option> in a <select>) element that is checked or toggled to an on state.
 */
let checked: list(rule) => rule;

/**
 The :default CSS pseudo-class selects form elements that are the default in a group of related elements.
 */
let default: list(rule) => rule;

/**
 The :defined CSS pseudo-class represents any element that has been defined.
 This includes any standard element built in to the browser, and custom elements that have been successfully defined
 (i.e. with the CustomElementRegistry.define() method).
 */
let defined: list(rule) => rule;

/**
 The :disabled CSS pseudo-class represents any disabled element.
 An element is disabled if it can't be activated (selected, clicked on, typed into, etc.) or accept focus.
 The element also has an enabled state, in which it can be activated or accept focus.
 */
let disabled: list(rule) => rule;

/**
 The :empty CSS pseudo-class represents any element that has no children.
 Children can be either element nodes or text (including whitespace).
 Comments, processing instructions, and CSS content do not affect whether an element is considered empty.
 */
let empty: list(rule) => rule;

/**
 The :enabled CSS pseudo-class represents any enabled element.
 An element is enabled if it can be activated (selected, clicked on, typed into, etc.) or accept focus.
 The element also has a disabled state, in which it can't be activated or accept focus.
 */
let enabled: list(rule) => rule;

/**
 The :first CSS pseudo-class, used with the  @page at-rule, represents the first page of a printed document.
 */
let first: list(rule) => rule;

/**
 The :first-child CSS pseudo-class represents the first element among a group of sibling elements.
 */
let firstChild: list(rule) => rule;

/**
 The :first-of-type CSS pseudo-class represents the first element of its type among a group of sibling elements.
 */
let firstOfType: list(rule) => rule;

/**
 The :focus CSS pseudo-class represents an element (such as a form input) that has received focus.
 It is generally triggered when the user clicks or taps on an element or selects it with the keyboard's "tab" key.
 */
let focus: list(rule) => rule;

/**
 The :focus-within CSS pseudo-class represents an element that has received focus or contains an element
 that has received focus. In other words, it represents an element that is itself matched by the :focus pseudo-class or has a descendant that is matched by :focus.
  (This includes descendants in shadow trees.)
 */
let focusWithin: list(rule) => rule;

/**
 The :host CSS pseudo-class selects the shadow host of the shadow DOM containing the CSS it is used inside
 — in other words, this allows you to select a custom element from inside its shadow DOM.
 */
let host: (~selector: string=?, list(rule)) => rule;

/**
 The :hover CSS pseudo-class matches when the user interacts with an element with a pointing device,
 but does not necessarily activate it.
 It is generally triggered when the user hovers over an element with the cursor (mouse pointer).
 */
let hover: list(rule) => rule;

/**
 The :indeterminate CSS pseudo-class represents any form element whose state is indeterminate.
 */
let indeterminate: list(rule) => rule;

/**
 The :in-range CSS pseudo-class represents an <input> element whose current value is
 within the range limits specified by the min and max attributes.
 */
let inRange: list(rule) => rule;

/**
 The :invalid CSS pseudo-class represents any <input> or other <form> element whose contents fail to validate.
 */
let invalid: list(rule) => rule;

/**
 The :lang() CSS pseudo-class matches elements based on the language they are determined to be in.
 */
let lang: (string, list(rule)) => rule;

/**
 The :last-child CSS pseudo-class represents the last element among a group of sibling elements.
 */
let lastChild: list(rule) => rule;

/**
 The :last-of-type CSS pseudo-class represents the last element of its type among a group of sibling elements.
 */
let lastOfType: list(rule) => rule;

//let left: list(rule) => rule;

/**
 The :link CSS pseudo-class represents an element that has not yet been visited.
 It matches every unvisited <a>, <area>, or <link> element that has an href attribute.
 */
let link: list(rule) => rule;

/**
 The :not() CSS pseudo-class represents elements that do not match a list of selectors.
 Since it prevents specific items from being selected, it is known as the negation pseudo-class.
 */
let not_: (string, list(rule)) => rule;

module Nth: {
  type t = [ | `odd | `even | `n(int) | `add(int, int)];
  let toString: t => string;
};

/**
 The :nth-child() CSS pseudo-class matches elements based on their position in a group of siblings.
 */
let nthChild: (Nth.t, list(rule)) => rule;

/**
 The :nth-last-child() CSS pseudo-class matches elements based on their position among a group of siblings,
 counting from the end.
 */
let nthLastChild: (Nth.t, list(rule)) => rule;

/**
 The :nth-last-of-type() CSS pseudo-class matches elements of a given type,
 based on their position among a group of siblings, counting from the end.
 */
let nthLastOfType: (Nth.t, list(rule)) => rule;

/**
 The :nth-of-type() CSS pseudo-class matches elements of a given type,
 based on their position among a group of siblings.
 */
let nthOfType: (Nth.t, list(rule)) => rule;

/**
 The :only-child CSS pseudo-class represents an element without any siblings.
 This is the same as :first-child:last-child or :nth-child(1):nth-last-child(1),
 but with a lower specificity.
 */
let onlyChild: list(rule) => rule;

/**
 The :only-of-type CSS pseudo-class represents an element that has no siblings of the same type.
 */
let onlyOfType: list(rule) => rule;

/**
 The :optional CSS pseudo-class represents any <input>, <select>,
 or <textarea> element that does not have the required attribute set on it.
 */
let optional: list(rule) => rule;

/**
 The :out-of-range CSS pseudo-class represents an <input> element whose current value
 is outside the range limits specified by the min and max attributes.
 */
let outOfRange: list(rule) => rule;

/**
 The :read-only CSS pseudo-class represents an element (such as input or textarea)
 that is not editable by the user.
 */
let readOnly: list(rule) => rule;

/**
 The :read-write CSS pseudo-class represents an element (such as input or textarea)
 that is editable by the user.
 */
let readWrite: list(rule) => rule;

/**
 The :required CSS pseudo-class represents any <input>, <select>, or <textarea> element
 that has the required attribute set on it.
 */
let required: list(rule) => rule;

//let right: list(rule) => rule;

/**
 The :root CSS pseudo-class matches the root element of a tree representing the document.
 In HTML, :root represents the <html> element and is identical to the selector html,
 except that its specificity is higher.
 */
let root: list(rule) => rule;

/**
 The :scope CSS pseudo-class represents elements that are a reference point for selectors to match against.
 */
let scope: list(rule) => rule;

/**
 The :target CSS pseudo-class represents a unique element (the target element) with an id matching
 the URL's fragment.
 */
let target: list(rule) => rule;

/**
 The :valid CSS pseudo-class represents any <input> or other <form> element whose contents validate successfully.
 This allows to easily make valid fields adopt an appearance that helps the user confirm that their data is formatted properly.
 */
let valid: list(rule) => rule;

/**
 The :visited CSS pseudo-class represents links that the user has already visited.
 For privacy reasons, the styles that can be modified using this selector are very limited.
 */
let visited: list(rule) => rule;

/* ***** */

let after: list(rule) => rule;
let before: list(rule) => rule;
let children: list(rule) => rule;
let directSibling: list(rule) => rule;
let noContent: list(rule) => rule;
let anyLink: list(rule) => rule;
let siblings: list(rule) => rule;
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
type gradient = Types.Gradient.t;
type animationName;

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

let none: [> | `none];
let local: [> | `local];

let paddingBox: [> | `paddingBox];
let borderBox: [> | `borderBox];
let contentBox: [> | `contentBox];

let noRepeat: [> | `noRepeat];
let space: [> | `space];
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

let solid: [> | `solid];
let dotted: [> | `dotted];
let dashed: [> | `dashed];

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

let round: [> | `round];
let miter: [> | `miter];
let bevel: [> | `bevel];
let butt: [> | `butt];
let square: [> | `square];
let thin: [> | `thin];
let extraLight: [> | `extraLight];
let light: [> | `light];
let medium: [> | `medium];
let semiBold: [> | `semiBold];
let bold: [> | `bold];
let extraBold: [> | `extraBold];
let lighter: [> | `lighter];
let bolder: [> | `bolder];
let fr: float => [> | `fr(float)];
let vw: float => [> | `vw(float)];

let localUrl: string => [> | `localUrl(string)];
let url: string => [> | `url(string)];

let linear: [> Types.TimingFunction.t];
let ease: [> Types.TimingFunction.t];
let easeIn: [> Types.TimingFunction.t];
let easeOut: [> Types.TimingFunction.t];
let easeInOut: [> Types.TimingFunction.t];
let stepStart: [> Types.TimingFunction.t];
let stepEnd: [> Types.TimingFunction.t];
let steps: (int, [ | `start | `end_]) => [> Types.TimingFunction.t];
let cubicBezier: (float, float, float, float) => [> Types.TimingFunction.t];

let marginBox: [> Types.GeometyBox.t];
//let borderBox: [> Types.GeometyBox.t];
//let paddingBox: [> Types.GeometyBox.t];
//let contentBox: [> Types.GeometyBox.t];
let fillBox: [> Types.GeometyBox.t];
let strokeBox: [> Types.GeometyBox.t];
let viewBox: [> Types.GeometyBox.t];

let translate: (Types.Length.t, Types.Length.t) => [> Types.Transform.t];
let translate3d:
  (Types.Length.t, Types.Length.t, Types.Length.t) => [> Types.Transform.t];
let translateX: Types.Length.t => [> Types.Transform.t];
let translateY: Types.Length.t => [> Types.Transform.t];
let translateZ: Types.Length.t => [> Types.Transform.t];
let scale: (float, float) => [> Types.Transform.t];
let scale3d: (float, float, float) => [> Types.Transform.t];
let scaleX: float => [> Types.Transform.t];
let scaleY: float => [> Types.Transform.t];
let scaleZ: float => [> Types.Transform.t];
let rotate: Types.Angle.t => [> Types.Transform.t];
let rotate3d: (float, float, float, Types.Angle.t) => [> Types.Transform.t];
let rotateX: Types.Angle.t => [> Types.Transform.t];
let rotateY: Types.Angle.t => [> Types.Transform.t];
let rotateZ: Types.Angle.t => [> Types.Transform.t];
let skew: (Types.Angle.t, Types.Angle.t) => [> Types.Transform.t];
let skewX: Types.Angle.t => [> Types.Transform.t];
let skewY: Types.Angle.t => [> Types.Transform.t];

let linearGradient:
  (Types.Angle.t, list((Types.Length.t, Types.Color.t))) =>
  [> Types.Gradient.t];
let repeatingLinearGradient:
  (Types.Angle.t, list((Types.Length.t, Types.Color.t))) =>
  [> Types.Gradient.t];
let radialGradient:
  list((Types.Length.t, Types.Color.t)) => [> Types.Gradient.t];
let repeatingRadialGradient:
  list((Types.Length.t, Types.Color.t)) => [> Types.Gradient.t];

/********************************************************
 ********************************************************
 ********************************************************/

let flex3:
  (
    ~grow: float,
    ~shrink: float,
    ~basis: [ Types.Length.t | Types.FlexBasis.t]
  ) =>
  rule;
let gridAutoColumns: [ Types.Length.t | `auto] => rule;
let gridAutoRows: [ Types.Length.t | `auto] => rule;

let border:
  (
    Types.Length.t,
    [ Types.BorderStyle.t | Types.Cascading.t],
    Types.Color.t
  ) =>
  rule;
let borderTop:
  (
    Types.Length.t,
    [ Types.BorderStyle.t | Types.Cascading.t],
    Types.Color.t
  ) =>
  rule;
let backgroundSize:
  [ | `size(Types.Length.t, Types.Length.t) | `auto | `cover | `contain] =>
  rule;

let textDecoration:
  [ | `none | `underline | `overline | `lineThrough | Types.Cascading.t] =>
  rule;

let background: [ Types.Color.t | Types.Url.t | gradient | `none] => rule;
let backgrounds:
  list([ Types.Color.t | Types.Url.t | gradient | `none]) => rule;

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

let gridTemplateColumns: list([ gridLength | `auto]) => rule;
let gridTemplateRows: list([ gridLength | `auto]) => rule;

module Calc: {
  let (-): (Types.Length.t, Types.Length.t) => [> Types.Length.t];
  let (+): (Types.Length.t, Types.Length.t) => [> Types.Length.t];
};

let size:
  (Types.Length.t, Types.Length.t) =>
  [> | `size(Types.Length.t, Types.Length.t)];

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
  | Types.Url.t
  | `none
  | Types.Cascading.t
];

let filter: list(filter) => rule;

let fontFace:
  (
    ~fontFamily: string,
    ~src: list([< | `localUrl(string) | Types.Url.t]),
    ~fontStyle: fontStyle=?,
    ~fontWeight: [ fontWeight | Types.Cascading.t]=?,
    unit
  ) =>
  string;

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

/* *
 SVG
 *** */

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
