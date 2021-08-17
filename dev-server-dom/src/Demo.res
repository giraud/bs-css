open CssJs
module Section = Comp.Section
module RedBox = Comp.RedBox

let concat = Belt.Array.concat
let addToRedBox = rules => Comp.redBox->Belt.Array.concat(rules)

let fontItem = [marginLeft(10->px), paddingRight(10->px), borderRight(1->px, solid, black)]

let miniBox = [border(2->px, solid, black), width(15->px), height(15->px), margin(1->px)]

let mergedStyles = merge(. [
  style(. [padding(0->px), fontSize(1->px)]),
  style(. [padding(20->px), fontSize(24->px), color(blue)]),
  style(. [media("(maxWidth: 768px)", [padding(10->px)])]),
  style(. [media("(maxWidth: 768px)", [fontSize(16->px), color(red)])]),
])

let differentHeightLengths =
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
  ]
  ->Belt.Array.map(x => {
    let className = style(. addToRedBox([height(x)]))
    <div style=className key="x" />
  })
  ->React.array

@react.component
let make = () =>
  <div style={style(. [background(hex("f5f5f5"))])}>
    <Section name="angles">
      <RedBox rules=[transform(rotate(45.->deg))] />
      <RedBox rules=[transform(rotate(3.1415->rad))] />
      <RedBox rules=[transform(rotate(50.->grad))] />
      <RedBox rules=[transform(rotate(turn(1. /. 3.)))] />
    </Section>
    <Section name="colors">
      <RedBox rules=[background(red)] />
      <RedBox rules=[background(rgb(255, 0, 0))] />
      <RedBox rules=[background(rgba(255, 0, 0, #num(0.5)))] />
      <RedBox rules=[background(hsl(255.->deg, 100.->pct, 50.->pct))] />
      <RedBox rules=[background(hsla(255.->deg, 100.->pct, 50.->pct, #num(0.5)))] />
      <RedBox rules=[background(hex("FF0000"))] />
      <RedBox rules=[background(transparent)] />
      <RedBox rules=[background(currentColor), color(blue)] />
    </Section>
    <Section name="Named colors">
      {React.array(
        [
          aliceblue,
          antiquewhite,
          aqua,
          aquamarine,
          azure,
          beige,
          bisque,
          black,
          blanchedalmond,
          blue,
          blueviolet,
          brown,
          burlywood,
          cadetblue,
          chartreuse,
          chocolate,
          coral,
          cornflowerblue,
          cornsilk,
          crimson,
          cyan,
          darkblue,
          darkcyan,
          darkgoldenrod,
          darkgray,
          darkgreen,
          darkgrey,
          darkkhaki,
          darkmagenta,
          darkolivegreen,
          darkorange,
          darkorchid,
          darkred,
          darksalmon,
          darkseagreen,
          darkslateblue,
          darkslategray,
          darkslategrey,
          darkturquoise,
          darkviolet,
          deeppink,
          deepskyblue,
          dimgray,
          dimgrey,
          dodgerblue,
          firebrick,
          floralwhite,
          forestgreen,
          fuchsia,
          gainsboro,
          ghostwhite,
          gold,
          goldenrod,
          gray,
          green,
          greenyellow,
          grey,
          honeydew,
          hotpink,
          indianred,
          indigo,
          ivory,
          khaki,
          lavender,
          lavenderblush,
          lawngreen,
          lemonchiffon,
          lightblue,
          lightcoral,
          lightcyan,
          lightgoldenrodyellow,
          lightgray,
          lightgreen,
          lightgrey,
          lightpink,
          lightsalmon,
          lightseagreen,
          lightskyblue,
          lightslategray,
          lightslategrey,
          lightsteelblue,
          lightyellow,
          lime,
          limegreen,
          linen,
          magenta,
          maroon,
          mediumaquamarine,
          mediumblue,
          mediumorchid,
          mediumpurple,
          mediumseagreen,
          mediumslateblue,
          mediumspringgreen,
          mediumturquoise,
          mediumvioletred,
          midnightblue,
          mintcream,
          mistyrose,
          moccasin,
          navajowhite,
          navy,
          oldlace,
          olive,
          olivedrab,
          orange,
          orangered,
          orchid,
          palegoldenrod,
          palegreen,
          paleturquoise,
          palevioletred,
          papayawhip,
          peachpuff,
          peru,
          pink,
          plum,
          powderblue,
          purple,
          rebeccapurple,
          red,
          rosybrown,
          royalblue,
          saddlebrown,
          salmon,
          sandybrown,
          seagreen,
          seashell,
          sienna,
          silver,
          skyblue,
          slateblue,
          slategray,
          slategrey,
          snow,
          springgreen,
          steelblue,
          tan,
          teal,
          thistle,
          tomato,
          transparent,
          turquoise,
          violet,
          wheat,
          white,
          whitesmoke,
          yellow,
          yellowgreen,
        ]->Belt.Array.map(c =>
          <div style={style(. [background(c)]->Belt.Array.concat(miniBox))} />
        ),
      )}
    </Section>
    <Section name="gradients">
      <RedBox rules=[background(linearGradient(45.->deg, [(zero, red), (100.->pct, blue)]))] />
      <RedBox
        rules=[background(repeatingLinearGradient(45.->deg, [(zero, red), (10.->pct, blue)]))]
      />
      <RedBox rules=[background(radialGradient([(zero, red), (100.->pct, blue)]))] />
      <RedBox rules=[background(repeatingRadialGradient([(zero, red), (10.->pct, blue)]))] />
    </Section>
    <Section name="lengths">
      <RedBox rules=[height(ch(1.2)), width(10->px), maxHeight(50.->pct), maxWidth(100.->pct)] />
      differentHeightLengths
    </Section>
    <Section name="calc">
      <RedBox
        rules=[
          height({
            open Calc
            14->pt - 10->px
          }),
        ]
      />
      <RedBox
        rules=[
          height({
            open Calc
            0.2->cm + 10.->mm
          }),
        ]
      />
    </Section>
    <Section name="display">
      <RedBox rules=[display(block)] />
      <RedBox rules=[display(inline)] />
      <RedBox rules=[display(inlineBlock)] />
      <RedBox rules=[display(none)] />
      <RedBox rules=[display(flexBox)] />
    </Section>
    <Section name="position">
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
    <Section name="grid">
      <div
        style={style(. [
          width(100.->pct),
          height(500->px),
          display(grid),
          gridTemplateColumns([150->px, auto, 150->px]),
          gridTemplateRows([60->px, auto]),
        ])}>
        <div
          style={style(. [
            gridColumnStart(1),
            gridColumnEnd(4),
            background(red),
            gridRowStart(1),
            gridRowEnd(1),
          ])}
        />
        <div style={style(. [background(blue), gridColumn(1, 1), gridRow(2, 2)])} />
        <div
          style={style(. [
            background(green),
            gridColumn(2, 2),
            gridRow(2, 2),
            display(inlineGrid),
            gridTemplateColumns([50->px, auto]),
            gridTemplateRows([40->px, auto]),
          ])}>
          <div style={style(. [background(yellow), gridRow(1, 1), gridColumn(2, 2)])} />
          <div style={style(. [background(green), gridRow(1, 2), gridColumn(1, 1)])} />
          <div style={style(. [background(purple), gridRow(2, 2), gridColumn(2, 2)])} />
        </div>
        <div
          style={style(. [
            gridColumnStart(3),
            gridColumnEnd(3),
            background(blue),
            gridRowStart(2),
            gridRowEnd(2),
          ])}
        />
      </div>
      <div style={style(. [display(#grid), gridAutoFlow(#row)])}>
        <div style={style(. [background(purple)])}>
          {"grid auto direction row 1"->React.string}
        </div>
        <div style={style(. [background(green)])}>
          {"grid auto direction row 2"->React.string}
        </div>
      </div>
      <div
        style={style(. [display(#grid), gridTemplateColumns([100->px, #repeat(#num(2), 60->px)])])}>
        <div style={style(. [background(purple)])}> {"Grid track repeat"->React.string} </div>
        <div style={style(. [background(green)])}> {"two times"->React.string} </div>
        <div style={style(. [background(red)])}> {"three times"->React.string} </div>
      </div>
      <div style={style(. [display(#grid), gridAutoColumns(100->px)])}>
        <div style={style(. [background(purple)])}>
          {"Grid auto columns (100px)"->React.string}
        </div>
        <div style={style(. [background(green)])}> {"100px"->React.string} </div>
        <div style={style(. [background(blue)])}> {"100px"->React.string} </div>
      </div>
    </Section>
    <Section name="flexbox">
      <div
        style={style(. [
          flexDirection(column),
          flexGrow(1.),
          alignItems(stretch),
          selector("& > *", [marginBottom(10->px), width(100.->pct)]),
        ])}>
        <div
          style={style(. [
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
          style={style(. [
            display(flexBox),
            flexDirection(column),
            background(gray),
            alignItems(baseline),
            justifyContent(flexStart),
          ])}>
          <RedBox /> <RedBox /> <RedBox />
        </div>
        <div
          style={style(. [
            display(flexBox),
            flexDirection(rowReverse),
            background(gray),
            alignItems(center),
            justifyContent(spaceBetween),
          ])}>
          <RedBox /> <RedBox rules=[height(50->px), width(50->px)] /> <RedBox />
        </div>
        <div
          style={style(. [
            display(flexBox),
            flexDirection(columnReverse),
            background(gray),
            alignItems(flexEnd),
            justifyContent(flexEnd),
          ])}>
          <RedBox /> <RedBox rules=[height(50->px), width(50->px)] /> <RedBox />
        </div>
        <div
          style={style(. [
            display(flexBox),
            flexDirection(row),
            background(gray),
            alignItems(stretch),
            justifyContent(spaceAround),
          ])}>
          <RedBox /> <RedBox rules=[height(50->px), width(50->px)] /> <RedBox />
        </div>
        <div
          style={style(. [
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
    <Section name="float">
      <RedBox rules=[float(#left), clear(#right)] />
      <RedBox rules=[float(#right), clear(#left)] />
      <RedBox rules=[float(none), clear(both)] />
    </Section>
    <Section name="overflow">
      <RedBox rules=[overflow(hidden)] />
      <RedBox rules=[overflow(visible)] />
      <RedBox rules=[overflow(auto)] />
      <RedBox rules=[overflow(scroll)] />
    </Section>
    <Section name="border">
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
    <Section name="background">
      <RedBox
        rules=[
          background(red),
          backgroundAttachment(scroll),
          backgroundClip(borderBox),
          backgroundOrigin(borderBox),
          backgroundPosition(#hv(50.->pct, 50.->pct)),
          backgroundRepeat(noRepeat),
          backgroundSize(size(100->px, 100->px)),
        ]
      />
      <RedBox
        rules=[
          background(radialGradient([(zero, red), (10.->pct, blue)])),
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
            linearGradient(45.->deg, [(zero, green), (50.->pct, red), (100.->pct, yellow)]),
          ),
          backgroundRepeat(repeatY),
          backgroundSize(contain),
        ]
      />
    </Section>
    <Section name="cursor">
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
    <Section name="list">
      <ul>
        <li style={style(. [listStyle(#disc, inside, none)])} />
        <li style={style(. [listStyleType(#circle)])} />
        <li style={style(. [listStyleType(#square)])} />
        <li style={style(. [listStyleType(#decimal)])} />
        <li style={style(. [listStyleType(#lowerAlpha)])} />
        <li style={style(. [listStyleType(#upperAlpha)])} />
        <li style={style(. [listStyleType(#lowerGreek)])} />
        <li style={style(. [listStyleType(#lowerLatin)])} />
        <li style={style(. [listStyleType(#upperLatin)])} />
        <li style={style(. [listStyleType(#lowerRoman)])} />
        <li style={style(. [listStyleType(#upperRoman)])} />
        <li
          style={style(. [
            listStyleType(#disc),
            listStylePosition(inside),
            listStyleImage(url("./facebook.png")),
          ])}
        />
      </ul>
    </Section>
    <Section name="outline">
      <RedBox rules=[outline(5->px, #double, green)] />
      <RedBox
        rules=[outlineStyle(solid), outlineWidth(5->px), outlineColor(green), outlineOffset(5->px)]
      />
      <RedBox rules=[outline(5->px, #double, red)] />
      <RedBox rules=[outline(5->px, #ridge, red)] />
    </Section>
    <Section name="transform">
      <RedBox rules=[opacity(0.5)] />
      <RedBox rules=[perspective(500->px), transform(rotate(10.->deg))] />
      <RedBox rules=[transforms([translate(10->px, 10.->pct), skew(10.->deg, 10.->deg)])] />
      <RedBox
        rules=[
          transform(rotate(19.->deg)),
          transformOrigin(50.->pct, 50.->pct),
          transformStyle(#preserve3d),
          perspective(900->px),
          perspectiveOrigin(10.->pct, 10.->pct),
        ]
      />
      <RedBox
        rules=[transform(translate(10->px, 10.->pct)), transformOrigin3d(10->px, 10->px, 10->px)]
      />
    </Section>
    <Section name="transition">
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
    <Section name="text">
      <p
        style={style(. [
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
        ])}>
        {"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."->React.string}
      </p>
      <h2 style={style(. [width(100.->pct)])}> {"Named Font weights"->React.string} </h2>
      <span
        style={style(. [fontWeight(thin), paddingRight(10->px), borderRight(1->px, solid, black)])}>
        {"thin"->React.string}
      </span>
      <span style={style(. [fontWeight(extraLight)]->concat(fontItem))}>
        {"extra light"->React.string}
      </span>
      <span style={style(. [fontWeight(light)]->concat(fontItem))}> {"light"->React.string} </span>
      <span style={style(. [fontWeight(normal)]->concat(fontItem))}>
        {"normal"->React.string}
      </span>
      <span style={style(. [fontWeight(medium)]->concat(fontItem))}>
        {"medium"->React.string}
      </span>
      <span style={style(. [fontWeight(semiBold)]->concat(fontItem))}>
        {"semiBold"->React.string}
      </span>
      <span style={style(. [fontWeight(bold)]->concat(fontItem))}> {"bold"->React.string} </span>
      <span style={style(. [fontWeight(extraBold)]->concat(fontItem))}>
        {"extra bold"->React.string}
      </span>
      <span style={style(. [fontWeight(#black)]->concat(fontItem))}> {"black"->React.string} </span>
      <span style={style(. [fontWeight(lighter)]->concat(fontItem))}>
        {"lighter"->React.string}
      </span>
      <span style={style(. [fontWeight(bolder)]->concat(fontItem))}>
        {"bolder"->React.string}
      </span>
    </Section>
    <Section name="cascading">
      {"inherit"->React.string}
      <div
        style={style(. [
          display(inherit_),
          position(inherit_),
          fontSize(inherit_),
          fontStyle(inherit_),
          lineHeight(inherit_),
        ])}
      />
      {"unset"->React.string}
      <div
        style={style(. [
          display(unset),
          position(unset),
          fontSize(unset),
          fontStyle(unset),
          lineHeight(unset),
        ])}
      />
    </Section>
    <Section name="columns">
      <p style={style(. [columnCount(count(10))])}>
        {"This is a bunch of text split into columns
             using the CSS `column-count` property. The text
             is equally distributed over the columns."->React.string}
      </p>
    </Section>
    <Section name="resize">
      <textarea style={style(. [resize(none)])}> {"Can't resize textarea"->React.string} </textarea>
      <div style={style(. [marginLeft(20->px), overflow(scroll), resize(horizontal)])}>
        {"Resizable div (horizontal)"->React.string}
      </div>
      <div style={style(. [marginLeft(20->px), overflow(scroll), resize(vertical)])}>
        {"Resizable div (vertical)"->React.string}
      </div>
    </Section>
    <Section name="content">
      <div
        style={style(. [
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
        ])}>
        {"none"->React.string}
      </div>
      <div
        style={style(. [
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
        ])}>
        {"normal"->React.string}
      </div>
      <div style={style(. [position(relative), marginLeft(20->px)])}>
        <a
          href="https://github.com/SentiaAnalytics/bs-css"
          style={style(. [
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
        style={style(. [
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
        ])}>
        {"empty content"->React.string}
      </div>
      <div
        style={style(. [
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
        style={style(. [
          marginLeft(20->px),
          counterReset(Types.CounterReset.reset /* for test */("foo", ~value=1)),
          before([contentRule(Types.Counter.counter("foo")), border(1->px, solid, black)]),
        ])}>
        {"counter"->React.string}
      </div>
      <div
        style={style(. [
          counterReset(Types.CounterReset.reset("foo", ~value=1)),
          marginLeft(20->px),
        ])}>
        <div
          style={style(. [
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
        style={style(. [
          marginLeft(20->px),
          before([contentRule(#attr("class")), border(1->px, solid, black)]),
        ])}>
        {"attr"->React.string}
      </div>
      <div
        style={style(. [
          marginLeft(20->px),
          before([
            contentRule(linearGradient(45.->deg, [(zero, red), (100.->pct, blue)])),
            border(1->px, solid, black),
            display(inlineBlock),
            height(18->px),
            width(18->px),
          ]),
        ])}>
        {"linear gradient"->React.string}
      </div>
      <div
        style={style(. [
          marginLeft(20->px),
          before([
            contentRules([#openQuote, #text("foo"), #closeQuote]),
            border(1->px, solid, black),
          ]),
        ])}>
        {"contents (quotes)"->React.string}
      </div>
    </Section>
    <Section name="insertRule, the ultimate escape hatch"> <div className="raw-css" /> </Section>
    <Section name="merging style names">
      <button style=mergedStyles> {"Merged"->React.string} </button>
    </Section>
    <Section name="filter">
      <RedBox rules=[filter([#blur(10->px)])] />
      <RedBox rules=[filter([#brightness(50.)])] />
      <RedBox rules=[filter([#contrast(50.)])] />
      <RedBox rules=[filter([#dropShadow(3->px, 3->px, 3->px, #rgb(200, 100, 100))])] />
      <RedBox rules=[filter([#grayscale(50.)])] />
      <RedBox rules=[filter([#hueRotate(180.->deg)])] />
      <RedBox rules=[filter([#invert(50.)])] />
      <RedBox rules=[filter([#opacity(50.)])] />
      <RedBox rules=[filter([#saturate(50.)])] />
      <RedBox rules=[filter([#sepia(50.)])] />
      <RedBox
        rules=[
          filter([
            #sepia(50.),
            #saturate(50.),
            #dropShadow(3->px, 3->px, 3->px, #rgb(200, 100, 100)),
          ]),
        ]
      />
      <svg height="0" style={style(. [display(none)])}>
        <filter id="f1"> <feGaussianBlur stdDeviation="3" /> </filter>
      </svg>
      <RedBox rules=[filter([#url("#f1")])] />
    </Section>
    <Section name="direction">
      <Section name="ltr">
        <div style={style(. [direction(#ltr), display(#flex)])}>
          <RedBox> {"1"->React.string} </RedBox>
          <RedBox> {"2"->React.string} </RedBox>
          <RedBox> {"3"->React.string} </RedBox>
          <RedBox> {"4"->React.string} </RedBox>
        </div>
      </Section>
      <Section name="rtl">
        <div style={style(. [direction(#rtl), display(#flex)])}>
          <RedBox> {"1"->React.string} </RedBox>
          <RedBox> {"2"->React.string} </RedBox>
          <RedBox> {"3"->React.string} </RedBox>
          <RedBox> {"4"->React.string} </RedBox>
        </div>
      </Section>
      <Section name="unset">
        <div style={style(. [direction(#unset), display(#flex)])}>
          <RedBox> {"1"->React.string} </RedBox>
          <RedBox> {"2"->React.string} </RedBox>
          <RedBox> {"3"->React.string} </RedBox>
          <RedBox> {"4"->React.string} </RedBox>
        </div>
      </Section>
    </Section>
    <Section name="object-fit">
      <img style={style(. addToRedBox([objectFit(#fill)]))} src="./img-29.jpg" />
      <img style={style(. addToRedBox([objectFit(#contain)]))} src="./img-29.jpg" />
      <img style={style(. addToRedBox([objectFit(#cover)]))} src="./img-29.jpg" />
      <img style={style(. addToRedBox([objectFit(#none)]))} src="./img-29.jpg" />
      <img style={style(. addToRedBox([objectFit(#scaleDown)]))} src="./img-29.jpg" />
      <img style={style(. addToRedBox([objectFit(#inherit_)]))} src="./img-29.jpg" />
      <img style={style(. addToRedBox([objectFit(#initial)]))} src="./img-29.jpg" />
      <img style={style(. addToRedBox([objectFit(#unset)]))} src="./img-29.jpg" />
    </Section>
  </div>
