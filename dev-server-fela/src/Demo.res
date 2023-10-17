open Css

let fontItem = style(. [marginLeft(10->px), paddingRight(10->px), borderRight(1->px, solid, black)])

let spin = renderer =>
  renderKeyframes(.
    renderer,
    [(0, [transform(rotate(deg(0.)))]), (100, [transform(rotate(deg(360.)))])],
  )

let scaleAnimation = renderer =>
  renderKeyframes(.
    renderer,
    [(0, [transform(scale(0.3, 0.3))]), (100, [transform(scale(1.0, 1.0))])],
  )

let redBox = style(. [
  background(red),
  borderBottom(5->px, solid, black),
  width(50->px),
  height(50->px),
  margin(10->px),
])

let miniBox = style(. [border(2->px, solid, black), width(15->px), height(15->px), margin(1->px)])

let mergedStyles = merge(. [
  style(. [padding(0->px), fontSize(1->px)]),
  style(. [padding(20->px), fontSize(24->px), color(blue)]),
  style(. [media(. "(max-width: 768px)", [padding(10->px)])]),
  style(. [media(. "(max-width: 768px)", [fontSize(16->px), color(red)])]),
])

let differentHeightLengths = css =>
  [
    1.->cm,
    1.2->em,
    1.2->ex,
    10.->mm,
    50.->pct,
    14->pt,
    20->px,
    2.0->rem,
    1.->vh,
    1.0->vw,
    1.0->vmax,
    1.0->vmin,
    zero,
  ]->Belt.Array.map(x => {
    let className = css(. merge2(. redBox, style(. [height(x)])))
    <div className key=className />
  })

@react.component
let make = () => {
  let {css, renderer, _} = CssReact.useFela()
  let cx = (baseStyle, rules) => css(. merge2(. baseStyle, style(. rules)))

  let spinAnimationName = spin(renderer)

  <div>
    <Section name="Angles">
      <div className={cx(redBox, [transform(rotate(deg(45.)))])} />
      <div className={cx(redBox, [transform(rotate(rad(3.1415)))])} />
      <div className={cx(redBox, [transform(rotate(grad(50.)))])} />
      <div className={cx(redBox, [transform(rotate(turn(1. /. 3.)))])} />
    </Section>
    <Section name="Colors">
      <div className={cx(redBox, [background(red)])} />
      <div className={cx(redBox, [background(rgb(255, 0, 0))])} />
      <div className={cx(redBox, [background(rgba(255, 0, 0, #num(0.5)))])} />
      <div className={cx(redBox, [background(hsl(deg(255.), 100.->pct, 50.->pct))])} />
      <div className={cx(redBox, [background(hsla(deg(255.), 100.->pct, 50.->pct, #num(0.5)))])} />
      <div className={cx(redBox, [background(hex("FF0000"))])} />
      <div className={cx(redBox, [background(transparent)])} />
      <div className={cx(redBox, [background(currentColor), color(blue)])} />
    </Section>
    <Section name="Named colors">
      {React.array(
        [
          ("aliceblue", aliceblue),
          ("antiquewhite", antiquewhite),
          ("aqua", aqua),
          ("aquamarine", aquamarine),
          ("azure", azure),
          ("beige", beige),
          ("aqua", bisque),
          ("black", black),
          ("blanchedalmond", blanchedalmond),
          ("blue", blue),
          ("blueviolet", blueviolet),
          ("brown", brown),
          ("burlywood", burlywood),
          ("cadetblue", cadetblue),
          ("chartreuse", chartreuse),
          ("chocolate", chocolate),
          ("coral", coral),
          ("cornflowerblue", cornflowerblue),
          ("cornsilk", cornsilk),
          ("crimson", crimson),
          ("cyan", cyan),
          ("darkblue", darkblue),
          ("darkcyan", darkcyan),
          ("darkgoldenrod", darkgoldenrod),
          ("cyan", darkgray),
          ("darkgreen", darkgreen),
          ("darkgrey", darkgrey),
          ("darkkhaki", darkkhaki),
          ("darkmagenta", darkmagenta),
          ("darkolivegreen", darkolivegreen),
          ("darkorange", darkorange),
          ("darkorchid", darkorchid),
          ("darkred", darkred),
          ("darksalmon", darksalmon),
          ("darkseagreen", darkseagreen),
          ("darkslateblue", darkslateblue),
          ("darkslategray", darkslategray),
          ("darkslategrey", darkslategrey),
          ("darkturquoise", darkturquoise),
          ("darkviolet", darkviolet),
          ("deeppink", deeppink),
          ("deepskyblue", deepskyblue),
          ("darkturquoise", dimgray),
          ("dimgrey", dimgrey),
          ("dodgerblue", dodgerblue),
          ("firebrick", firebrick),
          ("floralwhite", floralwhite),
          ("forestgreen", forestgreen),
          ("fuchsia", fuchsia),
          ("gainsboro", gainsboro),
          ("ghostwhite", ghostwhite),
          ("gold", gold),
          ("goldenrod", goldenrod),
          ("gray", gray),
          ("green", green),
          ("greenyellow", greenyellow),
          ("grey", grey),
          ("honeydew", honeydew),
          ("hotpink", hotpink),
          ("indianred", indianred),
          ("indigo", indigo),
          ("ivory", ivory),
          ("khaki", khaki),
          ("lavender", lavender),
          ("lavenderblush", lavenderblush),
          ("lawngreen", lawngreen),
          ("lemonchiffon", lemonchiffon),
          ("lightblue", lightblue),
          ("lightcoral", lightcoral),
          ("lightcyan", lightcyan),
          ("lightgoldenrodyellow", lightgoldenrodyellow),
          ("lightgray", lightgray),
          ("lightgreen", lightgreen),
          ("lightgrey", lightgrey),
          ("lightpink", lightpink),
          ("lightsalmon", lightsalmon),
          ("lightseagreen", lightseagreen),
          ("lightskyblue", lightskyblue),
          ("lightslategray", lightslategray),
          ("lightslategrey", lightslategrey),
          ("lightsteelblue", lightsteelblue),
          ("lightyellow", lightyellow),
          ("lime", lime),
          ("limegreen", limegreen),
          ("linen", linen),
          ("magenta", magenta),
          ("maroon", maroon),
          ("mediumaquamarine", mediumaquamarine),
          ("mediumblue", mediumblue),
          ("mediumorchid", mediumorchid),
          ("mediumpurple", mediumpurple),
          ("mediumseagreen", mediumseagreen),
          ("mediumslateblue", mediumslateblue),
          ("mediumspringgreen", mediumspringgreen),
          ("mediumturquoise", mediumturquoise),
          ("mediumvioletred", mediumvioletred),
          ("midnightblue", midnightblue),
          ("mintcream", mintcream),
          ("mistyrose", mistyrose),
          ("moccasin", moccasin),
          ("navajowhite", navajowhite),
          ("navy", navy),
          ("oldlace", oldlace),
          ("olive", olive),
          ("olivedrab", olivedrab),
          ("orange", orange),
          ("orangered", orangered),
          ("orchid", orchid),
          ("palegoldenrod", palegoldenrod),
          ("palegreen", palegreen),
          ("paleturquoise", paleturquoise),
          ("palevioletred", palevioletred),
          ("papayawhip", papayawhip),
          ("peachpuff", peachpuff),
          ("peru", peru),
          ("pink", pink),
          ("plum", plum),
          ("powderblue", powderblue),
          ("purple", purple),
          ("rebeccapurple", rebeccapurple),
          ("red", red),
          ("rosybrown", rosybrown),
          ("royalblue", royalblue),
          ("saddlebrown", saddlebrown),
          ("salmon", salmon),
          ("sandybrown", sandybrown),
          ("seagreen", seagreen),
          ("seashell", seashell),
          ("sienna", sienna),
          ("silver", silver),
          ("skyblue", skyblue),
          ("slateblue", slateblue),
          ("slategray", slategray),
          ("slategrey", slategrey),
          ("snow", snow),
          ("springgreen", springgreen),
          ("steelblue", steelblue),
          ("Css", Css.tan),
          ("teal", teal),
          ("thistle", thistle),
          ("tomato", tomato),
          ("transparent", transparent),
          ("turquoise", turquoise),
          ("violet", violet),
          ("wheat", wheat),
          ("white", white),
          ("whitesmoke", whitesmoke),
          ("yellow", yellow),
          ("yellowgreen", yellowgreen),
        ]->Belt.Array.map(((name, value)) =>
          <div key=name title=name className={cx(miniBox, [background(value)])} />
        ),
      )}
    </Section>
    <Section name="Gradients">
      <div
        className={cx(
          redBox,
          [background(linearGradient(deg(45.), [(zero, red), (100.->pct, blue)]))],
        )}
      />
      <div
        className={cx(
          redBox,
          [background(repeatingLinearGradient(deg(45.), [(zero, red), (10.->pct, blue)]))],
        )}
      />
      <div className={cx(redBox, [background(radialGradient([(zero, red), (100.->pct, blue)]))])} />
      <div
        className={cx(
          redBox,
          [background(repeatingRadialGradient([(zero, red), (10.->pct, blue)]))],
        )}
      />
    </Section>
    <Section name="Lengths">
      <div
        className={cx(
          redBox,
          [height(ch(1.2)), width(10->px), maxHeight(50.->pct), maxWidth(100.->pct)],
        )}
      />
      {differentHeightLengths(css)->React.array}
    </Section>
    <Section name="Calc">
      <div
        className={cx(
          redBox,
          [
            height({
              open Calc
              14->pt - 10->px
            }),
          ],
        )}
      />
      <div
        className={cx(
          redBox,
          [
            height({
              open Calc
              0.2->cm + 10.->mm
            }),
          ],
        )}
      />
    </Section>
    <Section name="Display">
      <div className={cx(redBox, [display(block)])} />
      <div className={cx(redBox, [display(inline)])} />
      <div className={cx(redBox, [display(inlineBlock)])} />
      <div className={cx(redBox, [display(none)])} />
      <div className={cx(redBox, [display(flexBox)])} />
    </Section>
    <Section name="Position">
      <div
        className={cx(
          redBox,
          [position(absolute), top(zero), left(zero), right(zero), bottom(zero)],
        )}
      />
      <div className={cx(redBox, [position(relative)])} />
      <div className={cx(redBox, [position(fixed), bottom(10->px), right(10->px)])} />
      <div className={cx(redBox, [position(static)])} />
      <div className={cx(redBox, [position(sticky)])} />
    </Section>
    <Section name="Padding & Margin">
      <div className={cx(redBox, [padding(10->px), margin(10->px)])} />
      <div
        className={cx(
          redBox,
          [
            paddingLeft(10->px),
            paddingRight(10->px),
            paddingTop(10->px),
            paddingBottom(10->px),
            marginLeft(10->px),
            marginRight(10->px),
            marginTop(10->px),
            marginBottom(10->px),
          ],
        )}
      />
      <div
        className={cx(redBox, [padding2(~v=10->px, ~h=20->px), margin2(~v=10->px, ~h=20->px)])}
      />
      <div
        className={cx(
          redBox,
          [
            padding3(~top=10->px, ~h=20->px, ~bottom=1->px),
            margin3(~top=10->px, ~h=20->px, ~bottom=2->px),
          ],
        )}
      />
      <div
        className={cx(
          redBox,
          [
            padding4(~top=10->px, ~bottom=1->px, ~left=5->px, ~right=15->px),
            margin4(~top=10->px, ~bottom=1->px, ~left=5->px, ~right=15->px),
          ],
        )}
      />
    </Section>
    <Section name="Grid">
      <div
        className={css(.
          style(. [
            width(100.->pct),
            height(500->px),
            display(grid),
            gridTemplateColumns([150->px, auto, 150->px]),
            gridTemplateRows([60->px, auto]),
          ]),
        )}>
        <div
          className={css(.
            style(. [
              gridColumnStart(1),
              gridColumnEnd(4),
              background(red),
              gridRowStart(1),
              gridRowEnd(1),
            ]),
          )}
        />
        <div className={css(. style(. [background(blue), gridColumn(1, 1), gridRow(2, 2)]))} />
        <div
          className={css(.
            style(. [
              background(green),
              gridColumn(2, 2),
              gridRow(2, 2),
              display(inlineGrid),
              gridTemplateColumns([50->px, auto]),
              gridTemplateRows([40->px, auto]),
            ]),
          )}>
          <div className={css(. style(. [background(yellow), gridRow(1, 1), gridColumn(2, 2)]))} />
          <div className={css(. style(. [background(green), gridRow(1, 2), gridColumn(1, 1)]))} />
          <div className={css(. style(. [background(purple), gridRow(2, 2), gridColumn(2, 2)]))} />
        </div>
        <div
          className={css(.
            style(. [
              gridColumnStart(3),
              gridColumnEnd(3),
              background(blue),
              gridRowStart(2),
              gridRowEnd(2),
            ]),
          )}
        />
      </div>
      <div className={css(. style(. [display(#grid), gridAutoFlow(#row)]))}>
        <div className={css(. style(. [background(purple)]))}>
          {"grid auto direction row 1"->React.string}
        </div>
        <div className={css(. style(. [background(green)]))}>
          {"grid auto direction row 2"->React.string}
        </div>
      </div>
      <div
        className={css(.
          style(. [display(#grid), gridTemplateColumns([100->px, #repeat(#num(2), 60->px)])]),
        )}>
        <div className={css(. style(. [background(purple)]))}>
          {"Grid track repeat"->React.string}
        </div>
        <div className={css(. style(. [background(green)]))}> {"two times"->React.string} </div>
        <div className={css(. style(. [background(red)]))}> {"three times"->React.string} </div>
      </div>
      <div className={css(. style(. [display(#grid), gridAutoColumns(100->px)]))}>
        <div className={css(. style(. [background(purple)]))}>
          {"Grid auto columns (100px)"->React.string}
        </div>
        <div className={css(. style(. [background(green)]))}> {"100px"->React.string} </div>
        <div className={css(. style(. [background(blue)]))}> {"100px"->React.string} </div>
      </div>
    </Section>
    <Section name="Flexbox">
      <div
        className={css(.
          style(. [
            flexDirection(column),
            flexGrow(1.),
            alignItems(stretch),
            selector(. "& > *", [marginBottom(10->px), width(100.->pct)]),
          ]),
        )}>
        <div
          className={css(.
            style(. [
              display(flexBox),
              flexDirection(row),
              background(gray),
              alignItems(flexStart),
              justifyContent(flexEnd),
            ]),
          )}>
          <div className={cx(redBox, [order(1), flexGrow(1.), flexShrink(1.), flexBasis(auto)])} />
          <div className={cx(redBox, [flex(none)])} />
          <div className={cx(redBox, [order(1), flex3(~grow=1.5, ~shrink=0.8, ~basis=100->px)])} />
          <div className={cx(redBox, [alignSelf(flexEnd)])} />
          <div className={css(. redBox)} />
        </div>
        <div
          className={css(.
            style(. [
              display(flexBox),
              flexDirection(column),
              background(gray),
              alignItems(baseline),
              justifyContent(flexStart),
            ]),
          )}>
          <div className={css(. redBox)} />
          <div className={css(. redBox)} />
          <div className={css(. redBox)} />
        </div>
        <div
          className={css(.
            style(. [
              display(flexBox),
              flexDirection(rowReverse),
              background(gray),
              alignItems(center),
              justifyContent(spaceBetween),
            ]),
          )}>
          <div className={css(. redBox)} />
          <div className={cx(redBox, [height(50->px), width(50->px)])} />
          <div className={css(. redBox)} />
        </div>
        <div
          className={css(.
            style(. [
              display(flexBox),
              flexDirection(columnReverse),
              background(gray),
              alignItems(flexEnd),
              justifyContent(flexEnd),
            ]),
          )}>
          <div className={css(. redBox)} />
          <div className={cx(redBox, [height(50->px), width(50->px)])} />
          <div className={css(. redBox)} />
        </div>
        <div
          className={css(.
            style(. [
              display(flexBox),
              flexDirection(row),
              background(gray),
              alignItems(stretch),
              justifyContent(spaceAround),
            ]),
          )}>
          <div className={css(. redBox)} />
          <div className={cx(redBox, [height(50->px), width(50->px)])} />
          <div className={css(. redBox)} />
        </div>
        <div
          className={css(.
            style(. [
              display(flexBox),
              flexDirection(row),
              background(gray),
              alignItems(stretch),
              justifyContent(spaceEvenly),
            ]),
          )}>
          <div className={css(. redBox)} />
          <div className={cx(redBox, [height(50->px), width(50->px)])} />
          <div className={css(. redBox)} />
        </div>
      </div>
    </Section>
    <Section name="Float">
      <div className={cx(redBox, [Css.float(#left), clear(#right)])} />
      <div className={cx(redBox, [Css.float(#right), clear(#left)])} />
      <div className={cx(redBox, [Css.float(none), clear(both)])} />
    </Section>
    <Section name="Overflow">
      <div className={cx(redBox, [overflow(hidden)])} />
      <div className={cx(redBox, [overflow(visible)])} />
      <div className={cx(redBox, [overflow(auto)])} />
      <div className={cx(redBox, [overflow(scroll)])} />
    </Section>
    <Section name="Border">
      <div className={cx(redBox, [border(5->px, solid, blue), borderRadius(1000->px)])} />
      <div
        className={cx(
          redBox,
          [
            border(5->px, solid, green),
            borderTopRightRadius(1000->px),
            borderTopLeftRadius(1000->px),
            borderBottomRightRadius(1000->px),
            borderBottomLeftRadius(1000->px),
          ],
        )}
      />
      <div
        className={cx(
          redBox,
          [
            borderTop(5->px, dashed, hex("FFF")),
            borderRight(5->px, dotted, rgb(0, 0, 0)),
            borderBottom(5->px, none, green),
            borderLeft(5->px, solid, blue),
          ],
        )}
      />
      <div className={cx(redBox, [borderWidth(5->px), borderStyle(solid), borderColor(blue)])} />
      <div
        className={cx(redBox, [borderTopWidth(5->px), borderTopStyle(solid), borderTopColor(blue)])}
      />
      <div
        className={cx(
          redBox,
          [borderBottomWidth(5->px), borderBottomStyle(solid), borderBottomColor(blue)],
        )}
      />
      <div
        className={cx(
          redBox,
          [borderLeftWidth(5->px), borderLeftStyle(solid), borderLeftColor(blue)],
        )}
      />
      <div
        className={cx(
          redBox,
          [borderRightWidth(5->px), borderRightStyle(solid), borderRightColor(blue)],
        )}
      />
    </Section>
    <Section name="Background">
      <div
        className={cx(
          redBox,
          [
            background(red),
            backgroundAttachment(scroll),
            backgroundClip(borderBox),
            backgroundOrigin(borderBox),
            backgroundPosition(#hv(50.->pct, 50.->pct)),
            backgroundRepeat(noRepeat),
            backgroundSize(size(100->px, 100->px)),
          ],
        )}
      />
      <div
        className={cx(
          redBox,
          [
            background(radialGradient([(zero, red), (10.->pct, blue)])),
            backgroundAttachment(fixed),
            backgroundClip(contentBox),
            backgroundOrigin(contentBox),
            backgroundRepeat(repeat),
            backgroundSize(auto),
          ],
        )}
      />
      <div
        className={cx(
          redBox,
          [
            background(url("./img-29.jpg")),
            backgroundAttachment(local),
            backgroundClip(paddingBox),
            backgroundOrigin(paddingBox),
            backgroundRepeat(repeatX),
            backgroundSize(cover),
          ],
        )}
      />
      <div
        className={cx(
          redBox,
          [
            backgroundColor(rgb(0, 0, 255)),
            backgroundImage(
              linearGradient(deg(45.), [(zero, green), (50.->pct, red), (100.->pct, yellow)]),
            ),
            backgroundRepeat(repeatY),
            backgroundSize(contain),
          ],
        )}
      />
    </Section>
    <Section name="Cursor">
      <div className={cx(redBox, [cursor(#auto)])}> {"auto"->React.string} </div>
      <div className={cx(redBox, [cursor(#default)])}> {"default"->React.string} </div>
      <div className={cx(redBox, [cursor(#none)])}> {"none"->React.string} </div>
      <div className={cx(redBox, [cursor(#contextMenu)])}> {"context menu"->React.string} </div>
      <div className={cx(redBox, [cursor(#help)])}> {"help"->React.string} </div>
      <div className={cx(redBox, [cursor(#pointer)])}> {"pointer"->React.string} </div>
      <div className={cx(redBox, [cursor(#progress)])}> {"progress"->React.string} </div>
      <div className={cx(redBox, [cursor(#wait)])}> {"wait"->React.string} </div>
      <div className={cx(redBox, [cursor(#cell)])}> {"cell"->React.string} </div>
      <div className={cx(redBox, [cursor(#crosshair)])}> {"crosshair"->React.string} </div>
      <div className={cx(redBox, [cursor(#text)])}> {"text"->React.string} </div>
      <div className={cx(redBox, [cursor(#verticalText)])}> {"vert text"->React.string} </div>
      <div className={cx(redBox, [cursor(#alias)])}> {"alias"->React.string} </div>
      <div className={cx(redBox, [cursor(#copy)])}> {"copy"->React.string} </div>
      <div className={cx(redBox, [cursor(#move)])}> {"move"->React.string} </div>
      <div className={cx(redBox, [cursor(#noDrop)])}> {"no drop"->React.string} </div>
      <div className={cx(redBox, [cursor(#notAllowed)])}> {"not allowed"->React.string} </div>
      <div className={cx(redBox, [cursor(#grab)])}> {"grab"->React.string} </div>
      <div className={cx(redBox, [cursor(#grabbing)])}> {"grabbing"->React.string} </div>
      <div className={cx(redBox, [cursor(#allScroll)])}> {"all scroll"->React.string} </div>
      <div className={cx(redBox, [cursor(#colResize)])}> {"col resize"->React.string} </div>
      <div className={cx(redBox, [cursor(#rowResize)])}> {"row resize"->React.string} </div>
      <div className={cx(redBox, [cursor(#nResize)])}> {"n resize"->React.string} </div>
      <div className={cx(redBox, [cursor(#eResize)])}> {"e resize"->React.string} </div>
      <div className={cx(redBox, [cursor(#sResize)])}> {"s resize"->React.string} </div>
      <div className={cx(redBox, [cursor(#wResize)])}> {"w resize"->React.string} </div>
      <div className={cx(redBox, [cursor(#neResize)])}> {"ne resize"->React.string} </div>
      <div className={cx(redBox, [cursor(#nwResize)])}> {"nw resize"->React.string} </div>
      <div className={cx(redBox, [cursor(#seResize)])}> {"se resize"->React.string} </div>
      <div className={cx(redBox, [cursor(#swResize)])}> {"sw resize"->React.string} </div>
      <div className={cx(redBox, [cursor(#ewResize)])}> {"ew resize"->React.string} </div>
      <div className={cx(redBox, [cursor(#nsResize)])}> {"ns resize"->React.string} </div>
      <div className={cx(redBox, [cursor(#neswResize)])}> {"nesw resize"->React.string} </div>
      <div className={cx(redBox, [cursor(#nwseResize)])}> {"nwse resize"->React.string} </div>
      <div className={cx(redBox, [cursor(#zoomIn)])}> {"zoom in"->React.string} </div>
      <div className={cx(redBox, [cursor(#zoomOut)])}> {"zoom out"->React.string} </div>
    </Section>
    <Section name="List">
      <ul>
        <li className={css(. style(. [listStyle(#disc, inside, none)]))} />
        <li className={css(. style(. [listStyleType(#circle)]))} />
        <li className={css(. style(. [listStyleType(#square)]))} />
        <li className={css(. style(. [listStyleType(#decimal)]))} />
        <li className={css(. style(. [listStyleType(#lowerAlpha)]))} />
        <li className={css(. style(. [listStyleType(#upperAlpha)]))} />
        <li className={css(. style(. [listStyleType(#lowerGreek)]))} />
        <li className={css(. style(. [listStyleType(#lowerLatin)]))} />
        <li className={css(. style(. [listStyleType(#upperLatin)]))} />
        <li className={css(. style(. [listStyleType(#lowerRoman)]))} />
        <li className={css(. style(. [listStyleType(#upperRoman)]))} />
        <li
          className={css(.
            style(. [
              listStyleType(#disc),
              listStylePosition(inside),
              listStyleImage(url("./facebook.png")),
            ]),
          )}
        />
      </ul>
    </Section>
    <Section name="Outline">
      <div className={cx(redBox, [outline(5->px, #double, green)])} />
      <div
        className={cx(
          redBox,
          [outlineStyle(solid), outlineWidth(5->px), outlineColor(green), outlineOffset(5->px)],
        )}
      />
      <div className={cx(redBox, [outline(5->px, #double, red)])} />
      <div className={cx(redBox, [outline(5->px, #ridge, red)])} />
    </Section>
    <Section name="Transform">
      <div className={cx(redBox, [opacity(0.5)])} />
      <div className={cx(redBox, [perspective(500->px), transform(rotate(deg(10.)))])} />
      <div
        className={cx(
          redBox,
          [transforms([translate(10->px, 10.->pct), skew(deg(10.), deg(10.))])],
        )}
      />
      <div
        className={cx(
          redBox,
          [
            transform(rotate(deg(19.))),
            transformOrigin(50.->pct, 50.->pct),
            transformStyle(#preserve3d),
            perspective(900->px),
            perspectiveOrigin(10.->pct, 10.->pct),
          ],
        )}
      />
      <div
        className={cx(
          redBox,
          [transform(translate(10->px, 10.->pct)), transformOrigin3d(10->px, 10->px, 10->px)],
        )}
      />
    </Section>
    <Section name="Transition">
      <div
        className={cx(
          redBox,
          [
            transition(
              ~duration=#ms(300.),
              ~delay=#ms(300.),
              ~timingFunction=easeInOut,
              "transform",
            ),
          ],
        )}
      />
      <div
        className={cx(
          redBox,
          [
            transitionProperty("height"),
            transitionDelay(#ms(300.)),
            transitionDuration(#ms(300.)),
            transitionTimingFunction(linear),
          ],
        )}
      />
    </Section>
    <Section name="Text">
      <p
        className={css(.
          style(. [
            color(black),
            fontFamilies([#custom("Helvetica"), #sansSerif]),
            fontSize(18->pt),
            fontVariant(#smallCaps),
            fontStyle(italic),
            fontWeight(#num(300)),
            letterSpacing(3->px),
            lineHeight(#abs(2.)),
            textAlign(#left),
            textDecoration(underline),
            textDecorationColor(pink),
            textDecorationStyle(wavy),
            textIndent(10->px),
            textOverflow(clip),
            textShadow(Shadow.text(~y=3->px, ~blur=2->px, black)),
            textTransform(capitalize),
            verticalAlign(sub),
            whiteSpace(normal),
            wordBreak(breakAll),
            wordSpacing(20->px),
            wordWrap(breakWord),
          ]),
        )}>
        {"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."->React.string}
      </p>
      <h2 className={css(. style(. [width(100.->pct)]))}> {"Named Font weights"->React.string} </h2>
      <span
        className={css(.
          style(. [fontWeight(thin), paddingRight(10->px), borderRight(1->px, solid, black)]),
        )}>
        {"thin"->React.string}
      </span>
      <span className={cx(fontItem, [fontWeight(#extraLight)])}>
        {"extra light"->React.string}
      </span>
      <span className={cx(fontItem, [fontWeight(#light)])}> {"light"->React.string} </span>
      <span className={cx(fontItem, [fontWeight(#normal)])}> {"normal"->React.string} </span>
      <span className={cx(fontItem, [fontWeight(#medium)])}> {"medium"->React.string} </span>
      <span className={cx(fontItem, [fontWeight(#semiBold)])}> {"semiBold"->React.string} </span>
      <span className={cx(fontItem, [fontWeight(#bold)])}> {"bold"->React.string} </span>
      <span className={cx(fontItem, [fontWeight(#extraBold)])}> {"extra bold"->React.string} </span>
      <span className={cx(fontItem, [fontWeight(#black)])}> {"black"->React.string} </span>
      <span className={cx(fontItem, [fontWeight(#lighter)])}> {"lighter"->React.string} </span>
      <span className={cx(fontItem, [fontWeight(#bolder)])}> {"bolder"->React.string} </span>
    </Section>
    <Section name="Animation">
      <div
        className={cx(
          redBox,
          [
            animation(
              ~duration=#ms(300.),
              ~delay=#ms(300.),
              ~direction=reverse,
              ~timingFunction=linear,
              ~fillMode=forwards,
              ~playState=running,
              ~iterationCount=infinite,
              spinAnimationName,
            ),
          ],
        )}
      />
      <div
        className={cx(
          redBox,
          [
            animations([
              Animation.shorthand(~duration=#ms(300.), ~iterationCount=infinite, spinAnimationName),
              Animation.shorthand(
                ~duration=#ms(300.),
                ~iterationCount=infinite,
                scaleAnimation(renderer),
              ),
            ]),
          ],
        )}
      />
      <div
        className={cx(
          redBox,
          [
            animationName(spinAnimationName),
            animationTimingFunction(easeIn),
            animationDuration(#ms(300.)),
            animationDelay(#ms(300.)),
            animationDirection(normal),
            animationFillMode(backwards),
            animationPlayState(paused),
            animationIterationCount(count(5)),
          ],
        )}
      />
    </Section>
    <Section name="Cascading">
      {"inherit"->React.string}
      <div
        className={css(.
          style(. [
            display(inherit_),
            position(inherit_),
            fontSize(inherit_),
            fontStyle(inherit_),
            lineHeight(inherit_),
          ]),
        )}
      />
      {"unset"->React.string}
      <div
        className={css(.
          style(. [
            display(unset),
            position(unset),
            fontSize(unset),
            fontStyle(unset),
            lineHeight(unset),
          ]),
        )}
      />
    </Section>
    <Section name="Columns">
      <p className={css(. style(. [columnCount(count(10))]))}>
        {"This is a bunch of text split into columns
             using the CSS `column-count` property. The text
             is equally distributed over the columns."->React.string}
      </p>
    </Section>
    <Section name="Resize">
      <textarea
        className={css(. style(. [resize(none)]))} value="Can't resize textarea" readOnly=true
      />
      <div className={css(. style(. [marginLeft(20->px), overflow(scroll), resize(horizontal)]))}>
        {"Resizable div (horizontal)"->React.string}
      </div>
      <div className={css(. style(. [marginLeft(20->px), overflow(scroll), resize(vertical)]))}>
        {"Resizable div (vertical)"->React.string}
      </div>
    </Section>
    <Section name="Content">
      <div
        className={css(.
          style(. [
            position(relative),
            after([
              contentRule(#none),
              position(absolute),
              top(zero),
              left(zero),
              width(100.->pct),
              height(100.->pct),
              border(1->px, solid, black),
            ]),
          ]),
        )}>
        {"none"->React.string}
      </div>
      <div
        className={css(.
          style(. [
            position(relative),
            after([
              contentRule(#normal),
              position(absolute),
              top(zero),
              left(zero),
              width(100.->pct),
              height(100.->pct),
              border(1->px, solid, black),
            ]),
          ]),
        )}>
        {"normal"->React.string}
      </div>
      <div className={css(. style(. [position(relative), marginLeft(20->px)]))}>
        <a
          href="https://github.com/SentiaAnalytics/bs-css"
          className={css(.
            style(. [
              before([
                contentRule(#text("external ")),
                backgroundColor(red),
                display(inlineBlock),
                flexBasis(content),
              ]),
            ]),
          )}>
          {"link"->React.string}
        </a>
      </div>
      <div
        className={css(.
          style(. [
            position(relative),
            marginLeft(20->px),
            after([
              contentRule(#text("")),
              position(absolute),
              top(zero),
              left(zero),
              width(100.->pct),
              height(100.->pct),
              border(1->px, solid, black),
            ]),
          ]),
        )}>
        {"empty content"->React.string}
      </div>
      <div
        className={css(.
          style(. [
            position(relative),
            marginLeft(20->px),
            paddingLeft(20->px),
            after([
              contentRule(#url("https://via.placeholder.com/18")),
              position(absolute),
              top(zero),
              left(zero),
              width(18->px),
              height(18->px),
              border(1->px, solid, black),
            ]),
          ]),
        )}>
        {"external "->React.string}
      </div>
      <div
        className={css(.
          style(. [
            marginLeft(20->px /* for test */),
            counterReset(Types.CounterReset.reset("foo", ~value=1)),
            before([contentRule(Types.Counter.counter("foo")), border(1->px, solid, black)]),
          ]),
        )}>
        {"counter"->React.string}
      </div>
      <div
        className={css(.
          style(. [counterReset(Types.CounterReset.reset("foo", ~value=1)), marginLeft(20->px)]),
        )}>
        <div
          className={css(.
            style(. [
              counterReset(Types.CounterReset.reset("foo", ~value=2)),
              before([
                contentRule(Types.Counters.counters("foo", ~separator="@", ~style=#upperRoman)),
                border(1->px, solid, black),
              ]),
            ]),
          )}>
          {"counters"->React.string}
        </div>
      </div>
      <div
        className={css(.
          style(. [
            marginLeft(20->px),
            before([contentRule(#attr("class")), border(1->px, solid, black)]),
          ]),
        )}>
        {"attr"->React.string}
      </div>
      <div
        className={css(.
          style(. [
            marginLeft(20->px),
            before([
              contentRule(linearGradient(deg(45.), [(zero, red), (100.->pct, blue)])),
              border(1->px, solid, black),
              display(inlineBlock),
              height(18->px),
              width(18->px),
            ]),
          ]),
        )}>
        {"linear gradient"->React.string}
      </div>
      <div
        className={css(.
          style(. [
            marginLeft(20->px),
            before([
              contentRules([#openQuote, #text("foo"), #closeQuote]),
              border(1->px, solid, black),
            ]),
          ]),
        )}>
        {"contents (quotes)"->React.string}
      </div>
    </Section>
    <Section name="InsertRule, the ultimate escape hatch">
      {"Render a green square --> "->React.string} <div className="raw-css" />
    </Section>
    <Section name="Merging style names">
      <button className={css(. mergedStyles)}> {"Merged"->React.string} </button>
    </Section>
    <Section name="Filter">
      <div className={cx(redBox, [filter([#blur(10->px)])])} />
      <div className={cx(redBox, [filter([#brightness(50.)])])} />
      <div className={cx(redBox, [filter([#contrast(50.)])])} />
      <div
        className={cx(redBox, [filter([#dropShadow(3->px, 3->px, 3->px, #rgb(200, 100, 100))])])}
      />
      <div className={cx(redBox, [filter([#grayscale(50.)])])} />
      <div className={cx(redBox, [filter([#hueRotate(#deg(180.))])])} />
      <div className={cx(redBox, [filter([#invert(50.)])])} />
      <div className={cx(redBox, [filter([#opacity(50.)])])} />
      <div className={cx(redBox, [filter([#saturate(50.)])])} />
      <div className={cx(redBox, [filter([#sepia(50.)])])} />
      <div
        className={cx(
          redBox,
          [
            filter([
              #sepia(50.),
              #saturate(50.),
              #dropShadow(3->px, 3->px, 3->px, #rgb(200, 100, 100)),
            ]),
          ],
        )}
      />
      <svg height="0" className={css(. style(. [display(#none)]))}>
        <filter id="f1"> <feGaussianBlur stdDeviation="3" /> </filter>
      </svg>
      <div className={cx(redBox, [filter([#url("#f1")])])} />
    </Section>
    <Section name="Direction">
      <Section name="ltr">
        <div className={css(. style(. [direction(#ltr), display(#flex)]))}>
          <div className={css(. redBox)}> {"1"->React.string} </div>
          <div className={css(. redBox)}> {"2"->React.string} </div>
          <div className={css(. redBox)}> {"3"->React.string} </div>
          <div className={css(. redBox)}> {"4"->React.string} </div>
        </div>
      </Section>
      <Section name="rtl">
        <div className={css(. style(. [direction(#rtl), display(#flex)]))}>
          <div className={css(. redBox)}> {"1"->React.string} </div>
          <div className={css(. redBox)}> {"2"->React.string} </div>
          <div className={css(. redBox)}> {"3"->React.string} </div>
          <div className={css(. redBox)}> {"4"->React.string} </div>
        </div>
      </Section>
      <Section name="Unset">
        <div className={css(. style(. [direction(#unset), display(#flex)]))}>
          <div className={css(. redBox)}> {"1"->React.string} </div>
          <div className={css(. redBox)}> {"2"->React.string} </div>
          <div className={css(. redBox)}> {"3"->React.string} </div>
          <div className={css(. redBox)}> {"4"->React.string} </div>
        </div>
      </Section>
    </Section>
    <Section name="object-fit">
      <img className={cx(redBox, [objectFit(#fill)])} src="./img-29.jpg" />
      <img className={cx(redBox, [objectFit(#contain)])} src="./img-29.jpg" />
      <img className={cx(redBox, [objectFit(#cover)])} src="./img-29.jpg" />
      <img className={cx(redBox, [objectFit(#none)])} src="./img-29.jpg" />
      <img className={cx(redBox, [objectFit(#scaleDown)])} src="./img-29.jpg" />
      <img className={cx(redBox, [objectFit(#inherit_)])} src="./img-29.jpg" />
      <img className={cx(redBox, [objectFit(#initial)])} src="./img-29.jpg" />
      <img className={cx(redBox, [objectFit(#unset)])} src="./img-29.jpg" />
    </Section>
  </div>
}
