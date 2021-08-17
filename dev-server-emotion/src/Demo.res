open CssJs

insertRule(. ".raw-css { display:block; background-color: green; width: 50px; height: 50px; }")

module Section = Comp.Section
module RedBox = Comp.RedBox

let concat = Belt.Array.concat
let redBox = Comp.redBox
let addToRedBox = rules => redBox->concat(rules)

let fontItem = [marginLeft(10->px), paddingRight(10->px), borderRight(1->px, solid, black)]

let spin = keyframes(. [(0, [transform(rotate(deg(0.)))]), (100, [transform(rotate(deg(360.)))])])

let scaleAnimation = keyframes(. [
  (0, [transform(scale(0.3, 0.3))]),
  (100, [transform(scale(1.0, 1.0))]),
])

let miniBox = [border(2->px, solid, black), width(15->px), height(15->px), margin(1->px)]

let mergedStyles = merge(. [
  style(. [padding(0->px), fontSize(1->px)]),
  style(. [padding(20->px), fontSize(24->px), color(blue)]),
  style(. [media("(max-width: 768px)", [padding(10->px)])]),
  style(. [media("(max-width: 768px)", [fontSize(16->px), color(red)])]),
])

let differentHeightLengths =
  [
    cm(1.),
    em(1.2),
    ex(1.2),
    mm(10.),
    pct(50.),
    pt(14),
    20->px,
    rem(2.0),
    vh(1.),
    vw(1.0),
    vmax(1.0),
    vmin(1.0),
    zero,
  ]
  ->Belt.Array.map(x => {
    let className = style(. addToRedBox([height(x)]))
    <div className key=className />
  })
  ->React.array

@react.component
let make = () =>
  <div>
    <Section name="Angles">
      <RedBox rules=[transform(rotate(deg(45.)))] />
      <RedBox rules=[transform(rotate(rad(3.1415)))] />
      <RedBox rules=[transform(rotate(grad(50.)))] />
      <RedBox rules=[transform(rotate(turn(1. /. 3.)))] />
    </Section>
    <Section name="Colors">
      <RedBox rules=[background(red)] />
      <RedBox rules=[background(rgb(255, 0, 0))] />
      <RedBox rules=[background(rgba(255, 0, 0, #num(0.5)))] />
      <RedBox rules=[background(hsl(deg(255.), pct(100.), pct(50.)))] />
      <RedBox rules=[background(hsla(deg(255.), pct(100.), pct(50.), #num(0.5)))] />
      <RedBox rules=[background(hex("FF0000"))] />
      <RedBox rules=[background(transparent)] />
      <RedBox rules=[background(currentColor), color(blue)] />
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
          ("bisque", bisque),
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
          ("darkgray", darkgray),
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
          ("dimgray", dimgray),
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
          <div key=name title=name className={style(. [background(value)]->concat(miniBox))} />
        ),
      )}
    </Section>
    <Section name="Gradients">
      <RedBox rules=[background(linearGradient(deg(45.), [(zero, red), (pct(100.), blue)]))] />
      <RedBox
        rules=[background(repeatingLinearGradient(deg(45.), [(zero, red), (pct(10.), blue)]))]
      />
      <RedBox rules=[background(radialGradient([(zero, red), (pct(100.), blue)]))] />
      <RedBox rules=[background(repeatingRadialGradient([(zero, red), (pct(10.), blue)]))] />
    </Section>
    <Section name="Lengths">
      <RedBox rules=[height(ch(1.2)), width(10->px), maxHeight(pct(50.)), maxWidth(pct(100.))] />
      differentHeightLengths
    </Section>
    <Section name="Calc">
      <RedBox
        rules=[
          height({
            open Calc
            pt(14) - px(10)
          }),
        ]
      />
      <RedBox
        rules=[
          height({
            open Calc
            cm(0.2) + mm(10.)
          }),
        ]
      />
    </Section>
    <Section name="Display">
      <RedBox rules=[display(block)] />
      <RedBox rules=[display(inline)] />
      <RedBox rules=[display(inlineBlock)] />
      <RedBox rules=[display(none)] />
      <RedBox rules=[display(flexBox)] />
    </Section>
    <Section name="Position">
      <RedBox rules=[position(absolute), top(zero), left(zero), right(zero), bottom(zero)] />
      <RedBox rules=[position(relative)] />
      <RedBox rules=[position(fixed), bottom(10->px), right(10->px)] />
      <RedBox rules=[position(static)] />
      <RedBox rules=[position(sticky)] />
    </Section>
    <Section name="Padding & Margin">
      <RedBox rules=[padding(10->px), margin(10->px)] />
      <RedBox
        rules=[
          paddingLeft(10->px),
          paddingRight(10->px),
          paddingTop(10->px),
          paddingBottom(10->px),
          marginLeft(10->px),
          marginRight(10->px),
          marginTop(10->px),
          marginBottom(10->px),
        ]
      />
      <RedBox rules=[padding2(~v=10->px, ~h=20->px), margin2(~v=10->px, ~h=20->px)] />
      <RedBox
        rules=[
          padding3(~top=10->px, ~h=20->px, ~bottom=1->px),
          margin3(~top=10->px, ~h=20->px, ~bottom=2->px),
        ]
      />
      <RedBox
        rules=[
          padding4(~top=10->px, ~bottom=1->px, ~left=5->px, ~right=15->px),
          margin4(~top=10->px, ~bottom=1->px, ~left=5->px, ~right=15->px),
        ]
      />
    </Section>
    <Section name="Grid">
      <div
        className={style(. [
          width(pct(100.)),
          height(500->px),
          display(grid),
          gridTemplateColumns([150->px, auto, 150->px]),
          gridTemplateRows([60->px, auto]),
        ])}>
        <div
          className={style(. [
            gridColumnStart(1),
            gridColumnEnd(4),
            background(red),
            gridRowStart(1),
            gridRowEnd(1),
          ])}
        />
        <div className={style(. [background(blue), gridColumn(1, 1), gridRow(2, 2)])} />
        <div
          className={style(. [
            background(green),
            gridColumn(2, 2),
            gridRow(2, 2),
            display(inlineGrid),
            gridTemplateColumns([50->px, auto]),
            gridTemplateRows([40->px, auto]),
          ])}>
          <div className={style(. [background(yellow), gridRow(1, 1), gridColumn(2, 2)])} />
          <div className={style(. [background(green), gridRow(1, 2), gridColumn(1, 1)])} />
          <div className={style(. [background(purple), gridRow(2, 2), gridColumn(2, 2)])} />
        </div>
        <div
          className={style(. [
            gridColumnStart(3),
            gridColumnEnd(3),
            background(blue),
            gridRowStart(2),
            gridRowEnd(2),
          ])}
        />
      </div>
      <div className={style(. [display(#grid), gridAutoFlow(#row)])}>
        <div className={style(. [background(purple)])}>
          {"grid auto direction row 1"->React.string}
        </div>
        <div className={style(. [background(green)])}>
          {"grid auto direction row 2"->React.string}
        </div>
      </div>
      <div
        className={style(. [
          display(#grid),
          gridTemplateColumns([100->px, #repeat(#num(2), 60->px)]),
        ])}>
        <div className={style(. [background(purple)])}> {"Grid track repeat"->React.string} </div>
        <div className={style(. [background(green)])}> {"two times"->React.string} </div>
        <div className={style(. [background(red)])}> {"three times"->React.string} </div>
      </div>
      <div className={style(. [display(#grid), gridAutoColumns(100->px)])}>
        <div className={style(. [background(purple)])}>
          {"Grid auto columns (100px)"->React.string}
        </div>
        <div className={style(. [background(green)])}> {"100px"->React.string} </div>
        <div className={style(. [background(blue)])}> {"100px"->React.string} </div>
      </div>
    </Section>
    <Section name="Flexbox">
      <div
        className={style(. [
          flexDirection(column),
          flexGrow(1.),
          alignItems(stretch),
          selector("& > *", [marginBottom(10->px), width(pct(100.))]),
        ])}>
        <div
          className={style(. [
            display(flexBox),
            flexDirection(row),
            background(gray),
            alignItems(flexStart),
            justifyContent(flexEnd),
          ])}>
          <RedBox rules=[order(1), flexGrow(1.), flexShrink(1.), flexBasis(auto)] />
          <RedBox rules=[flex(none)] />
          <RedBox rules=[order(1), flex3(~grow=1.5, ~shrink=0.8, ~basis=100->px)] />
          <RedBox rules=[alignSelf(flexEnd)] />
          <RedBox />
        </div>
        <div
          className={style(. [
            display(flexBox),
            flexDirection(column),
            background(gray),
            alignItems(baseline),
            justifyContent(flexStart),
          ])}>
          <RedBox /> <RedBox /> <RedBox />
        </div>
        <div
          className={style(. [
            display(flexBox),
            flexDirection(rowReverse),
            background(gray),
            alignItems(center),
            justifyContent(spaceBetween),
          ])}>
          <RedBox /> <RedBox rules=[height(50->px), width(50->px)] /> <RedBox />
        </div>
        <div
          className={style(. [
            display(flexBox),
            flexDirection(columnReverse),
            background(gray),
            alignItems(flexEnd),
            justifyContent(flexEnd),
          ])}>
          <RedBox /> <RedBox rules=[height(50->px), width(50->px)] /> <RedBox />
        </div>
        <div
          className={style(. [
            display(flexBox),
            flexDirection(row),
            background(gray),
            alignItems(stretch),
            justifyContent(spaceAround),
          ])}>
          <RedBox /> <RedBox rules=[height(50->px), width(50->px)] /> <RedBox />
        </div>
        <div
          className={style(. [
            display(flexBox),
            flexDirection(row),
            background(gray),
            alignItems(stretch),
            justifyContent(spaceEvenly),
          ])}>
          <RedBox /> <RedBox rules=[height(50->px), width(50->px)] /> <RedBox />
        </div>
      </div>
    </Section>
    <Section name="Float">
      <RedBox rules=[CssJs.float(#left), clear(#right)] />
      <RedBox rules=[CssJs.float(#right), clear(#left)] />
      <RedBox rules=[CssJs.float(none), clear(both)] />
    </Section>
    <Section name="Overflow">
      <RedBox rules=[overflow(hidden)] />
      <RedBox rules=[overflow(visible)] />
      <RedBox rules=[overflow(auto)] />
      <RedBox rules=[overflow(scroll)] />
    </Section>
    <Section name="Border">
      <RedBox rules=[border(5->px, solid, blue), borderRadius(1000->px)] />
      <RedBox
        rules=[
          border(5->px, solid, green),
          borderTopRightRadius(1000->px),
          borderTopLeftRadius(1000->px),
          borderBottomRightRadius(1000->px),
          borderBottomLeftRadius(1000->px),
        ]
      />
      <RedBox
        rules=[
          borderTop(5->px, dashed, hex("FFF")),
          borderRight(5->px, dotted, rgb(0, 0, 0)),
          borderBottom(5->px, none, green),
          borderLeft(5->px, solid, blue),
        ]
      />
      <RedBox rules=[borderWidth(5->px), borderStyle(solid), borderColor(blue)] />
      <RedBox rules=[borderTopWidth(5->px), borderTopStyle(solid), borderTopColor(blue)] />
      <RedBox rules=[borderBottomWidth(5->px), borderBottomStyle(solid), borderBottomColor(blue)] />
      <RedBox rules=[borderLeftWidth(5->px), borderLeftStyle(solid), borderLeftColor(blue)] />
      <RedBox rules=[borderRightWidth(5->px), borderRightStyle(solid), borderRightColor(blue)] />
    </Section>
    <Section name="Background">
      <RedBox
        rules=[
          background(red),
          backgroundAttachment(scroll),
          backgroundClip(borderBox),
          backgroundOrigin(borderBox),
          backgroundPosition(#hv(pct(50.), pct(50.))),
          backgroundRepeat(noRepeat),
          backgroundSize(size(100->px, 100->px)),
        ]
      />
      <RedBox
        rules=[
          background(radialGradient([(zero, red), (pct(10.), blue)])),
          backgroundAttachment(fixed),
          backgroundClip(contentBox),
          backgroundOrigin(contentBox),
          backgroundRepeat(repeat),
          backgroundSize(auto),
        ]
      />
      <RedBox
        rules=[
          background(url("./img-29.jpg")),
          backgroundAttachment(local),
          backgroundClip(paddingBox),
          backgroundOrigin(paddingBox),
          backgroundRepeat(repeatX),
          backgroundSize(cover),
        ]
      />
      <RedBox
        rules=[
          backgroundColor(rgb(0, 0, 255)),
          backgroundImage(
            linearGradient(deg(45.), [(zero, green), (pct(50.), red), (pct(100.), yellow)]),
          ),
          backgroundRepeat(repeatY),
          backgroundSize(contain),
        ]
      />
    </Section>
    <Section name="Cursor">
      <RedBox rules=[cursor(#auto)]> {"auto"->React.string} </RedBox>
      <RedBox rules=[cursor(#default)]> {"default"->React.string} </RedBox>
      <RedBox rules=[cursor(#none)]> {"none"->React.string} </RedBox>
      <RedBox rules=[cursor(#contextMenu)]> {"context menu"->React.string} </RedBox>
      <RedBox rules=[cursor(#help)]> {"help"->React.string} </RedBox>
      <RedBox rules=[cursor(#pointer)]> {"pointer"->React.string} </RedBox>
      <RedBox rules=[cursor(#progress)]> {"progress"->React.string} </RedBox>
      <RedBox rules=[cursor(#wait)]> {"wait"->React.string} </RedBox>
      <RedBox rules=[cursor(#cell)]> {"cell"->React.string} </RedBox>
      <RedBox rules=[cursor(#crosshair)]> {"crosshair"->React.string} </RedBox>
      <RedBox rules=[cursor(#text)]> {"text"->React.string} </RedBox>
      <RedBox rules=[cursor(#verticalText)]> {"vert text"->React.string} </RedBox>
      <RedBox rules=[cursor(#alias)]> {"alias"->React.string} </RedBox>
      <RedBox rules=[cursor(#copy)]> {"copy"->React.string} </RedBox>
      <RedBox rules=[cursor(#move)]> {"move"->React.string} </RedBox>
      <RedBox rules=[cursor(#noDrop)]> {"no drop"->React.string} </RedBox>
      <RedBox rules=[cursor(#notAllowed)]> {"not allowed"->React.string} </RedBox>
      <RedBox rules=[cursor(#grab)]> {"grab"->React.string} </RedBox>
      <RedBox rules=[cursor(#grabbing)]> {"grabbing"->React.string} </RedBox>
      <RedBox rules=[cursor(#allScroll)]> {"all scroll"->React.string} </RedBox>
      <RedBox rules=[cursor(#colResize)]> {"col resize"->React.string} </RedBox>
      <RedBox rules=[cursor(#rowResize)]> {"row resize"->React.string} </RedBox>
      <RedBox rules=[cursor(#nResize)]> {"n resize"->React.string} </RedBox>
      <RedBox rules=[cursor(#eResize)]> {"e resize"->React.string} </RedBox>
      <RedBox rules=[cursor(#sResize)]> {"s resize"->React.string} </RedBox>
      <RedBox rules=[cursor(#wResize)]> {"w resize"->React.string} </RedBox>
      <RedBox rules=[cursor(#neResize)]> {"ne resize"->React.string} </RedBox>
      <RedBox rules=[cursor(#nwResize)]> {"nw resize"->React.string} </RedBox>
      <RedBox rules=[cursor(#seResize)]> {"se resize"->React.string} </RedBox>
      <RedBox rules=[cursor(#swResize)]> {"sw resize"->React.string} </RedBox>
      <RedBox rules=[cursor(#ewResize)]> {"ew resize"->React.string} </RedBox>
      <RedBox rules=[cursor(#nsResize)]> {"ns resize"->React.string} </RedBox>
      <RedBox rules=[cursor(#neswResize)]> {"nesw resize"->React.string} </RedBox>
      <RedBox rules=[cursor(#nwseResize)]> {"nwse resize"->React.string} </RedBox>
      <RedBox rules=[cursor(#zoomIn)]> {"zoom in"->React.string} </RedBox>
      <RedBox rules=[cursor(#zoomOut)]> {"zoom out"->React.string} </RedBox>
    </Section>
    <Section name="List">
      <ul>
        <li className={style(. [listStyle(#disc, inside, none)])} />
        <li className={style(. [listStyleType(#circle)])} />
        <li className={style(. [listStyleType(#square)])} />
        <li className={style(. [listStyleType(#decimal)])} />
        <li className={style(. [listStyleType(#lowerAlpha)])} />
        <li className={style(. [listStyleType(#upperAlpha)])} />
        <li className={style(. [listStyleType(#lowerGreek)])} />
        <li className={style(. [listStyleType(#lowerLatin)])} />
        <li className={style(. [listStyleType(#upperLatin)])} />
        <li className={style(. [listStyleType(#lowerRoman)])} />
        <li className={style(. [listStyleType(#upperRoman)])} />
        <li
          className={style(. [
            listStyleType(#disc),
            listStylePosition(inside),
            listStyleImage(url("./facebook.png")),
          ])}
        />
      </ul>
    </Section>
    <Section name="Outline">
      <RedBox rules=[outline(5->px, #double, green)] />
      <RedBox
        rules=[outlineStyle(solid), outlineWidth(5->px), outlineColor(green), outlineOffset(5->px)]
      />
      <RedBox rules=[outline(5->px, #double, red)] />
      <RedBox rules=[outline(5->px, #ridge, red)] />
    </Section>
    <Section name="Transform">
      <RedBox rules=[opacity(0.5)] />
      <RedBox rules=[perspective(500->px), transform(rotate(deg(10.)))] />
      <RedBox rules=[transforms([translate(10->px, pct(10.)), skew(deg(10.), deg(10.))])] />
      <RedBox
        rules=[
          transform(rotate(deg(19.))),
          transformOrigin(pct(50.), pct(50.)),
          transformStyle(#preserve3d),
          perspective(900->px),
          perspectiveOrigin(pct(10.), pct(10.)),
        ]
      />
      <RedBox
        rules=[transform(translate(10->px, pct(10.))), transformOrigin3d(10->px, 10->px, 10->px)]
      />
    </Section>
    <Section name="Transition">
      <RedBox
        rules=[transition(~duration=300, ~delay=300, ~timingFunction=easeInOut, "transform")]
      />
      <RedBox
        rules=[
          transitionProperty("height"),
          transitionDelay(300),
          transitionDuration(300),
          transitionTimingFunction(linear),
        ]
      />
    </Section>
    <Section name="Text">
      <p
        className={style(. [
          color(black),
          fontFamilies([#custom("Helvetica"), #sansSerif]),
          fontSize(pt(18)),
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
        ])}>
        {"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."->React.string}
      </p>
      <h2 className={style(. [width(pct(100.))])}> {"Named Font weights"->React.string} </h2>
      <span
        className={style(. [
          fontWeight(thin),
          paddingRight(10->px),
          borderRight(1->px, solid, black),
        ])}>
        {"thin"->React.string}
      </span>
      <span className={style(. [fontWeight(extraLight)]->concat(fontItem))}>
        {"extra light"->React.string}
      </span>
      <span className={style(. [fontWeight(light)]->concat(fontItem))}>
        {"light"->React.string}
      </span>
      <span className={style(. [fontWeight(normal)]->concat(fontItem))}>
        {"normal"->React.string}
      </span>
      <span className={style(. [fontWeight(medium)]->concat(fontItem))}>
        {"medium"->React.string}
      </span>
      <span className={style(. [fontWeight(semiBold)]->concat(fontItem))}>
        {"semiBold"->React.string}
      </span>
      <span className={style(. [fontWeight(bold)]->concat(fontItem))}>
        {"bold"->React.string}
      </span>
      <span className={style(. [fontWeight(extraBold)]->concat(fontItem))}>
        {"extra bold"->React.string}
      </span>
      <span className={style(. [fontWeight(#black)]->concat(fontItem))}>
        {"black"->React.string}
      </span>
      <span className={style(. [fontWeight(lighter)]->concat(fontItem))}>
        {"lighter"->React.string}
      </span>
      <span className={style(. [fontWeight(bolder)]->concat(fontItem))}>
        {"bolder"->React.string}
      </span>
    </Section>
    <Section name="Animation">
      <RedBox
        rules=[
          animation(
            ~duration=300,
            ~delay=300,
            ~direction=reverse,
            ~timingFunction=linear,
            ~fillMode=forwards,
            ~playState=running,
            ~iterationCount=infinite,
            spin,
          ),
        ]
      />
      <RedBox
        rules=[
          animations([
            Animation.shorthand(~duration=300, ~iterationCount=infinite, spin),
            Animation.shorthand(~duration=300, ~iterationCount=infinite, scaleAnimation),
          ]),
        ]
      />
      <RedBox
        rules=[
          animationName(spin),
          animationTimingFunction(easeIn),
          animationDuration(300),
          animationDelay(300),
          animationDirection(normal),
          animationFillMode(backwards),
          animationPlayState(paused),
          animationIterationCount(count(5)),
        ]
      />
    </Section>
    <Section name="Cascading">
      {"inherit"->React.string}
      <div
        className={style(. [
          display(inherit_),
          position(inherit_),
          fontSize(inherit_),
          fontStyle(inherit_),
          lineHeight(inherit_),
        ])}
      />
      {"unset"->React.string}
      <div
        className={style(. [
          display(unset),
          position(unset),
          fontSize(unset),
          fontStyle(unset),
          lineHeight(unset),
        ])}
      />
    </Section>
    <Section name="Columns">
      <p className={style(. [columnCount(count(10))])}>
        {"This is a bunch of text split into columns
             using the CSS `column-count` property. The text
             is equally distributed over the columns."->React.string}
      </p>
    </Section>
    <Section name="Resize">
      <textarea className={style(. [resize(none)])} value="Can't resize textarea" readOnly=true />
      <div className={style(. [marginLeft(20->px), overflow(scroll), resize(horizontal)])}>
        {"Resizable div (horizontal)"->React.string}
      </div>
      <div className={style(. [marginLeft(20->px), overflow(scroll), resize(vertical)])}>
        {"Resizable div (vertical)"->React.string}
      </div>
    </Section>
    <Section name="Content">
      <div
        className={style(. [
          position(relative),
          after([
            contentRule(#none),
            position(absolute),
            top(zero),
            left(zero),
            width(pct(100.)),
            height(pct(100.)),
            border(1->px, solid, black),
          ]),
        ])}>
        {"none"->React.string}
      </div>
      <div
        className={style(. [
          position(relative),
          after([
            contentRule(#normal),
            position(absolute),
            top(zero),
            left(zero),
            width(pct(100.)),
            height(pct(100.)),
            border(1->px, solid, black),
          ]),
        ])}>
        {"normal"->React.string}
      </div>
      <div className={style(. [position(relative), marginLeft(20->px)])}>
        <a
          href="https://github.com/SentiaAnalytics/bs-css"
          className={style(. [
            before([
              contentRule(#text("external ")),
              backgroundColor(red),
              display(inlineBlock),
              flexBasis(content),
            ]),
          ])}>
          {"link"->React.string}
        </a>
      </div>
      <div
        className={style(. [
          position(relative),
          marginLeft(20->px),
          after([
            contentRule(#text("")),
            position(absolute),
            top(zero),
            left(zero),
            width(pct(100.)),
            height(pct(100.)),
            border(1->px, solid, black),
          ]),
        ])}>
        {"empty content"->React.string}
      </div>
      <div
        className={style(. [
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
        ])}>
        {"url"->React.string}
      </div>
      <div
        className={style(. [
          marginLeft(20->px),
          counterReset(Types.CounterReset.reset("foo", ~value=1)),
          before([
            contentRule(Types.Counter.counter("foo")),
            border(px /* for test */(1), solid, black),
          ]),
        ])}>
        {"counter"->React.string}
      </div>
      <div
        className={style(. [
          counterReset(Types.CounterReset.reset("foo", ~value=1)),
          marginLeft(20->px),
        ])}>
        <div
          className={style(. [
            counterReset(Types.CounterReset.reset("foo", ~value=2)),
            before([
              contentRule(Types.Counters.counters("foo", ~separator="@", ~style=#upperRoman)),
              border(1->px, solid, black),
            ]),
          ])}>
          {"counters"->React.string}
        </div>
      </div>
      <div
        className={style(. [
          marginLeft(20->px),
          before([contentRule(#attr("class")), border(1->px, solid, black)]),
        ])}>
        {"attr"->React.string}
      </div>
      <div
        className={style(. [
          marginLeft(20->px),
          before([
            contentRule(Types.Gradient.linearGradient(deg(45.), [(zero, red), (pct(100.), blue)])),
            border(1->px, solid, black),
            display(inlineBlock),
            height(18->px),
            width(18->px),
          ]),
        ])}>
        {"linear gradient"->React.string}
      </div>
      <div
        className={style(. [
          marginLeft(20->px),
          before([
            contentRules([#openQuote, #text("foo"), #closeQuote]),
            border(px(1), solid, black),
          ]),
        ])}>
        {"contents (quotes)"->React.string}
      </div>
    </Section>
    <Section name="InsertRule, the ultimate escape hatch"> <div className="raw-css" /> </Section>
    <Section name="Merging style names">
      <button className=mergedStyles> {"Merged"->React.string} </button>
    </Section>
    <Section name="Filter">
      <RedBox rules=[filter([#blur(10->px)])] />
      <RedBox rules=[filter([#brightness(50.)])] />
      <RedBox rules=[filter([#contrast(50.)])] />
      <RedBox rules=[filter([#dropShadow(3->px, 3->px, 3->px, #rgb(200, 100, 100))])] />
      <RedBox rules=[filter([#grayscale(50.)])] />
      <RedBox rules=[filter([#hueRotate(#deg(180.))])] />
      <RedBox rules=[filter([#invert(50.)])] />
      <RedBox rules=[filter([#opacity(50.)])] />
      <RedBox rules=[filter([#saturate(50.)])] />
      <RedBox rules=[filter([#sepia(50.)])] />
      <RedBox
        rules=[
          filter([
            #sepia(50.),
            #saturate(50.),
            #dropShadow(3->px, 3->px, 3->px, rgb(200, 100, 100)),
          ]),
        ]
      />
      <svg height="0" className={style(. [display(none)])}>
        <filter id="f1"> <feGaussianBlur stdDeviation="3" /> </filter>
      </svg>
      <RedBox rules=[filter([url("#f1")])] />
    </Section>
    <Section name="Direction">
      <Section name="ltr">
        <div className={style(. [direction(#ltr), display(#flex)])}>
          <RedBox> {"1"->React.string} </RedBox>
          <RedBox> {"2"->React.string} </RedBox>
          <RedBox> {"3"->React.string} </RedBox>
          <RedBox> {"4"->React.string} </RedBox>
        </div>
      </Section>
      <Section name="rtl">
        <div className={style(. [direction(#rtl), display(#flex)])}>
          <RedBox> {"1"->React.string} </RedBox>
          <RedBox> {"2"->React.string} </RedBox>
          <RedBox> {"3"->React.string} </RedBox>
          <RedBox> {"4"->React.string} </RedBox>
        </div>
      </Section>
      <Section name="Unset">
        <div className={style(. [direction(#unset), display(#flex)])}>
          <RedBox> {"1"->React.string} </RedBox>
          <RedBox> {"2"->React.string} </RedBox>
          <RedBox> {"3"->React.string} </RedBox>
          <RedBox> {"4"->React.string} </RedBox>
        </div>
      </Section>
    </Section>
    <Section name="object-fit">
      <img className={style(. addToRedBox([objectFit(#fill)]))} src="./img-29.jpg" />
      <img className={style(. addToRedBox([objectFit(#contain)]))} src="./img-29.jpg" />
      <img className={style(. addToRedBox([objectFit(#cover)]))} src="./img-29.jpg" />
      <img className={style(. addToRedBox([objectFit(#none)]))} src="./img-29.jpg" />
      <img className={style(. addToRedBox([objectFit(#scaleDown)]))} src="./img-29.jpg" />
      <img className={style(. addToRedBox([objectFit(#inherit_)]))} src="./img-29.jpg" />
      <img className={style(. addToRedBox([objectFit(#initial)]))} src="./img-29.jpg" />
      <img className={style(. addToRedBox([objectFit(#unset)]))} src="./img-29.jpg" />
    </Section>
  </div>
