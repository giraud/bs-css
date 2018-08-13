let text = ReasonReact.string;

let arialNarrow =
  Css.(
    fontFace(
      ~fontFamily="Arial FontFace Test",
      ~src=[localUrl("Arial Narrow")],
      ~fontStyle=normal,
      (),
    )
  );

let spin =
  Css.(
    keyframes([
      (0, [transform(rotate(deg(0)))]),
      (100, [transform(rotate(deg(360)))]),
    ])
  );

let scaleAnimation =
  Css.(
    keyframes([
      (0, [transform(scale(0.3, 0.3))]),
      (100, [transform(scale(1.0, 1.0))]),
    ])
  );

let box =
  Css.[
    background(red),
    borderBottom(px(5), solid, black),
    width(px(50)),
    height(px(50)),
    margin(px(10)),
  ];

let rowLayout = Css.[display(flexBox), flexDirection(row), flexWrap(wrap)];

let section =
  Css.[
    selector(
      "& > h1",
      [fontFamily(arialNarrow), fontSize(px(32)), fontWeight(300)],
    ),
    position(relative),
    background(hex("f5f5f5")),
    margin(px(20)),
    padding(px(20)),
    boxShadow(~y=px(1), ~blur=px(5), rgba(0, 0, 0, 0.3)),
    boxShadows([
      boxShadow(~y=px(1), ~blur=px(5), rgba(0, 0, 0, 0.3)),
      boxShadow(
        ~y=px(1),
        ~blur=px(10),
        ~inset=true,
        rgba(255, 255, 255, 0.5),
      ),
    ]),
  ];

module Section = {
  let component = ReasonReact.statelessComponent("Section");
  let make = (~name, children) => {
    ...component,
    render: _ =>
      <section className={Css.style(section)}>
        <h1> {text(name)} </h1>
        <div className={Css.style(rowLayout)}> ...children </div>
      </section>,
  };
};

let tests =
  <div className=Css.(style([background(hex("f5f5f5"))]))>
    <Section name="angles">
      <div className=Css.(style([transform(rotate(deg(45))), ...box])) />
      <div
        className=Css.(style([transform(rotate(rad(3.1415))), ...box]))
      />
      <div className=Css.(style([transform(rotate(grad(50.))), ...box])) />
      <div
        className=Css.(style([transform(rotate(turn(1. /. 3.))), ...box]))
      />
    </Section>
    <Section name="colors">
      <div className=Css.(style([background(red), ...box])) />
      <div className=Css.(style([background(rgb(255, 0, 0)), ...box])) />
      <div
        className=Css.(style([background(rgba(255, 0, 0, 0.5)), ...box]))
      />
      <div className=Css.(style([background(hsl(255, 100, 50)), ...box])) />
      <div
        className=Css.(style([background(hsla(255, 100, 50, 0.5)), ...box]))
      />
      <div className=Css.(style([background(hex("FF0000")), ...box])) />
      <div className=Css.(style([background(transparent), ...box])) />
      <div
        className=Css.(
          style([background(currentColor), color(blue), ...box])
        )
      />
    </Section>
    <Section name="gradients">
      <div
        className=Css.(
          style([
            background(linearGradient(deg(45), [(0, red), (100, blue)])),
            ...box,
          ])
        )
      />
      <div
        className=Css.(
          style([
            background(
              repeatingLinearGradient(deg(45), [(0, red), (10, blue)]),
            ),
            ...box,
          ])
        )
      />
      <div
        className=Css.(
          style([
            background(radialGradient([(0, red), (100, blue)])),
            ...box,
          ])
        )
      />
      <div
        className=Css.(
          style([
            background(repeatingRadialGradient([(0, red), (10, blue)])),
            ...box,
          ])
        )
      />
    </Section>
    <Section name="lengths">
      <div
        className=Css.(
          style([
            height(ch(1.2)),
            width(px(10)),
            maxHeight(pct(50.)),
            maxWidth(pct(100.)),
            ...box,
          ])
        )
      />
      <div className=Css.(style([height(cm(1.)), ...box])) />
      <div className=Css.(style([height(em(1.2)), ...box])) />
      <div className=Css.(style([height(ex(1.2)), ...box])) />
      <div className=Css.(style([height(mm(10.)), ...box])) />
      <div className=Css.(style([height(pct(50.)), ...box])) />
      <div className=Css.(style([height(pt(14)), ...box])) />
      <div className=Css.(style([height(px(20)), ...box])) />
      <div className=Css.(style([height(rem(2.0)), ...box])) />
      <div className=Css.(style([height(vh(1.)), ...box])) />
      <div className=Css.(style([height(vw(1.0)), ...box])) />
      <div className=Css.(style([height(vmax(1.0)), ...box])) />
      <div className=Css.(style([height(vmin(1.0)), ...box])) />
      <div className=Css.(style([height(zero), ...box])) />
    </Section>
    <Section name="calc">
      <div
        className=Css.(style([height(Calc.(pt(14) - px(10))), ...box]))
      />
      <div
        className=Css.(style([height(Calc.(cm(0.2) + mm(10.))), ...box]))
      />
    </Section>
    <Section name="display">
      <div className=Css.(style([display(block), ...box])) />
      <div className=Css.(style([display(inline), ...box])) />
      <div className=Css.(style([display(inlineBlock), ...box])) />
      <div className=Css.(style([display(none), ...box])) />
      <div className=Css.(style([display(flexBox), ...box])) />
    </Section>
    <Section name="position">
      <div
        className=Css.(
          style([
            position(absolute),
            top(zero),
            left(zero),
            right(zero),
            bottom(zero),
            ...box,
          ])
        )
      />
      <div className=Css.(style([position(relative), ...box])) />
      <div
        className=Css.(
          style([position(fixed), bottom(px(10)), right(px(10)), ...box])
        )
      />
      <div className=Css.(style([position(static), ...box])) />
      <div className=Css.(style([position(sticky), ...box])) />
    </Section>
    <Section name="Padding & Margin">
      <div
        className=Css.(style([padding(px(10)), margin(px(10)), ...box]))
      />
      <div
        className=Css.(
          style([
            paddingLeft(px(10)),
            paddingRight(px(10)),
            paddingTop(px(10)),
            paddingBottom(px(10)),
            marginLeft(px(10)),
            marginRight(px(10)),
            marginTop(px(10)),
            marginBottom(px(10)),
            ...box,
          ])
        )
      />
      <div
        className=Css.(
          style([
            padding2(~v=px(10), ~h=px(20)),
            margin2(~v=px(10), ~h=px(20)),
            ...box,
          ])
        )
      />
      <div
        className=Css.(
          style([
            padding3(~top=px(10), ~h=px(20), ~bottom=px(1)),
            margin3(~top=px(10), ~h=px(20), ~bottom=px(2)),
            ...box,
          ])
        )
      />
      <div
        className=Css.(
          style([
            padding4(
              ~top=px(10),
              ~bottom=px(1),
              ~left=px(5),
              ~right=px(15),
            ),
            margin4(
              ~top=px(10),
              ~bottom=px(1),
              ~left=px(5),
              ~right=px(15),
            ),
            ...box,
          ])
        )
      />
    </Section>
    <Section name="grid">
      <div
        className=Css.(
          style([
            width(pct(100.)),
            height(px(500)),
            display(grid),
            gridTemplateColumns([px(150), auto, px(150)]),
            gridTemplateRows([px(60), auto]),
          ])
        )>
        <div
          className=Css.(
            style([
              gridColumnStart(1),
              gridColumnEnd(4),
              background(red),
              gridRowStart(1),
              gridRowEnd(1),
            ])
          )
        />
        <div
          className=Css.(
            style([background(blue), gridColumn(1, 1), gridRow(2, 2)])
          )
        />
        <div
          className=Css.(
            style([
              background(green),
              gridColumn(2, 2),
              gridRow(2, 2),
              display(inlineGrid),
              gridTemplateColumns([px(50), auto]),
              gridTemplateRows([px(40), auto]),
            ])
          )>
          <div
            className=Css.(
              style([background(yellow), gridRow(1, 1), gridColumn(2, 2)])
            )
          />
          <div
            className=Css.(
              style([background(green), gridRow(1, 2), gridColumn(1, 1)])
            )
          />
          <div
            className=Css.(
              style([background(purple), gridRow(2, 2), gridColumn(2, 2)])
            )
          />
        </div>
        <div
          className=Css.(
            style([
              gridColumnStart(3),
              gridColumnEnd(3),
              background(blue),
              gridRowStart(2),
              gridRowEnd(2),
            ])
          )
        />
      </div>
    </Section>
    <Section name="flexbox">
      <div
        className=Css.(
          style([
            flexDirection(column),
            flexGrow(1),
            alignItems(stretch),
            selector("& > *", [marginBottom(px(10)), width(pct(100.))]),
          ])
        )>
        <div
          className=Css.(
            style([
              display(flexBox),
              flexDirection(row),
              background(gray),
              alignItems(flexStart),
              justifyContent(flexEnd),
            ])
          )>
          <div
            className=Css.(
              style([
                order(1),
                flexGrow(1),
                flexShrink(1),
                flexBasis(auto),
                ...box,
              ])
            )
          />
          <div className=Css.(style([alignSelf(flexEnd), ...box])) />
          <div className={Css.style(box)} />
        </div>
        <div
          className=Css.(
            style([
              display(flexBox),
              flexDirection(column),
              background(gray),
              alignItems(baseline),
              justifyContent(flexStart),
            ])
          )>
          <div className={Css.style(box)} />
          <div className={Css.style(box)} />
          <div className={Css.style(box)} />
        </div>
        <div
          className=Css.(
            style([
              display(flexBox),
              flexDirection(rowReverse),
              background(gray),
              alignItems(center),
              justifyContent(spaceBetween),
            ])
          )>
          <div className={Css.style(box)} />
          <div
            className=Css.(style([height(px(50)), width(px(50)), ...box]))
          />
          <div className={Css.style(box)} />
        </div>
        <div
          className=Css.(
            style([
              display(flexBox),
              flexDirection(columnReverse),
              background(gray),
              alignItems(flexEnd),
              justifyContent(flexEnd),
            ])
          )>
          <div className={Css.style(box)} />
          <div
            className=Css.(style([height(px(50)), width(px(50)), ...box]))
          />
          <div className={Css.style(box)} />
        </div>
        <div
          className=Css.(
            style([
              display(flexBox),
              flexDirection(row),
              background(gray),
              alignItems(stretch),
              justifyContent(spaceAround),
            ])
          )>
          <div className={Css.style(box)} />
          <div
            className=Css.(style([height(px(50)), width(px(50)), ...box]))
          />
          <div className={Css.style(box)} />
        </div>
      </div>
    </Section>
    <Section name="float">
      <div className=Css.(style([float(`left), clear(`right), ...box])) />
      <div className=Css.(style([float(`right), clear(`left), ...box])) />
      <div className=Css.(style([float(none), clear(both), ...box])) />
    </Section>
    <Section name="overflow">
      <div className=Css.(style([overflow(hidden), ...box])) />
      <div className=Css.(style([overflow(visible), ...box])) />
      <div className=Css.(style([overflow(auto), ...box])) />
      <div className=Css.(style([overflow(scroll), ...box])) />
    </Section>
    <Section name="border">
      <div
        className=Css.(
          style([
            border(px(5), solid, blue),
            borderRadius(px(1000)),
            ...box,
          ])
        )
      />
      <div
        className=Css.(
          style([
            border(px(5), solid, green),
            borderTopRightRadius(px(1000)),
            borderTopLeftRadius(px(1000)),
            borderBottomRightRadius(px(1000)),
            borderBottomLeftRadius(px(1000)),
            ...box,
          ])
        )
      />
      <div
        className=Css.(
          style([
            borderTop(px(5), dashed, hex("FFF")),
            borderRight(px(5), dotted, rgb(0, 0, 0)),
            borderBottom(px(5), none, green),
            borderLeft(px(5), solid, blue),
            ...box,
          ])
        )
      />
      <div
        className=Css.(
          style([
            borderWidth(px(5)),
            borderStyle(solid),
            borderColor(blue),
            ...box,
          ])
        )
      />
      <div
        className=Css.(
          style([
            borderTopWidth(px(5)),
            borderTopStyle(solid),
            borderTopColor(blue),
            ...box,
          ])
        )
      />
      <div
        className=Css.(
          style([
            borderBottomWidth(px(5)),
            borderBottomStyle(solid),
            borderBottomColor(blue),
            ...box,
          ])
        )
      />
      <div
        className=Css.(
          style([
            borderLeftWidth(px(5)),
            borderLeftStyle(solid),
            borderLeftColor(blue),
            ...box,
          ])
        )
      />
      <div
        className=Css.(
          style([
            borderRightWidth(px(5)),
            borderRightStyle(solid),
            borderRightColor(blue),
            ...box,
          ])
        )
      />
    </Section>
    <Section name="background">
      <div
        className=Css.(
          style([
            background(red),
            backgroundAttachment(scroll),
            backgroundClip(borderBox),
            backgroundOrigin(borderBox),
            backgroundPosition(pct(50.), pct(50.)),
            backgroundRepeat(noRepeat),
            backgroundSize(size(px(100), px(100))),
            ...box,
          ])
        )
      />
      <div
        className=Css.(
          style([
            background(radialGradient([(0, red), (10, blue)])),
            backgroundAttachment(fixed),
            backgroundClip(contentBox),
            backgroundOrigin(contentBox),
            backgroundRepeat(repeat),
            backgroundSize(auto),
            ...box,
          ])
        )
      />
      <div
        className=Css.(
          style([
            background(url("./img-29.jpg")),
            backgroundAttachment(local),
            backgroundClip(paddingBox),
            backgroundOrigin(paddingBox),
            backgroundRepeat(repeatX),
            backgroundSize(cover),
            ...box,
          ])
        )
      />
      <div
        className=Css.(
          style([
            backgroundColor(rgb(0, 0, 255)),
            backgroundImage(
              linearGradient(
                deg(45),
                [(0, green), (50, red), (100, yellow)],
              ),
            ),
            backgroundRepeat(repeatY),
            backgroundSize(contain),
            ...box,
          ])
        )
      />
    </Section>
    <Section name="cursor">
      <div className=Css.(style([cursor(`pointer), ...box])) />
      <div className=Css.(style([cursor(`alias), ...box])) />
      <div className=Css.(style([cursor(`allScroll), ...box])) />
      <div className=Css.(style([cursor(`auto), ...box])) />
      <div className=Css.(style([cursor(`cell), ...box])) />
      <div className=Css.(style([cursor(`contextMenu), ...box])) />
      <div className=Css.(style([cursor(`default), ...box])) />
      <div className=Css.(style([cursor(`none), ...box])) />
      <div className=Css.(style([cursor(`crosshair), ...box])) />
      <div className=Css.(style([cursor(`copy), ...box])) />
      <div className=Css.(style([cursor(`grab), ...box])) />
      <div className=Css.(style([cursor(`grabbing), ...box])) />
      <div className=Css.(style([cursor(`help), ...box])) />
      <div className=Css.(style([cursor(`move), ...box])) />
      <div className=Css.(style([cursor(`notAllowed), ...box])) />
      <div className=Css.(style([cursor(`progress), ...box])) />
      <div className=Css.(style([cursor(`text), ...box])) />
      <div className=Css.(style([cursor(`wait), ...box])) />
      <div className=Css.(style([cursor(`zoomIn), ...box])) />
      <div className=Css.(style([cursor(`zoomOut), ...box])) />
    </Section>
    <Section name="list">
      <ul>
        <li className=Css.(style([listStyle(`disc, inside, none)])) />
        <li className=Css.(style([listStyleType(`circle)])) />
        <li className=Css.(style([listStyleType(`square)])) />
        <li className=Css.(style([listStyleType(`decimal)])) />
        <li className=Css.(style([listStyleType(`lowerAlpha)])) />
        <li className=Css.(style([listStyleType(`upperAlpha)])) />
        <li className=Css.(style([listStyleType(`lowerGreek)])) />
        <li className=Css.(style([listStyleType(`lowerLatin)])) />
        <li className=Css.(style([listStyleType(`upperLatin)])) />
        <li className=Css.(style([listStyleType(`lowerRoman)])) />
        <li className=Css.(style([listStyleType(`upperRoman)])) />
        <li
          className=Css.(
            style([
              listStyleType(`disc),
              listStylePosition(inside),
              listStyleImage(url("./facebook.png")),
            ])
          )
        />
      </ul>
    </Section>
    <Section name="outline">
      <div
        className=Css.(style([outline(px(5), `double, green), ...box]))
      />
      <div
        className=Css.(
          style([
            outlineStyle(solid),
            outlineWidth(px(5)),
            outlineColor(green),
            outlineOffset(px(5)),
            ...box,
          ])
        )
      />
      <div className=Css.(style([outline(px(5), `double, red), ...box])) />
      <div className=Css.(style([outline(px(5), `ridge, red), ...box])) />
    </Section>
    <Section name="transform">
      <div className=Css.(style([opacity(0.5), ...box])) />
      <div
        className=Css.(
          style([
            perspective(px(500)),
            transform(rotate(deg(10))),
            ...box,
          ])
        )
      />
      <div
        className=Css.(
          style([
            transforms([
              translate(px(10), pct(10.)),
              skew(deg(10), deg(10)),
            ]),
            ...box,
          ])
        )
      />
      <div
        className=Css.(
          style([
            transform(rotate(deg(19))),
            transformOrigin(pct(50.), pct(50.)),
            transformStyle(`preserve3d),
            perspective(px(900)),
            perspectiveOrigin(pct(10.), pct(10.)),
            ...box,
          ])
        )
      />
      <div
        className=Css.(
          style([
            transform(translate(px(10), pct(10.))),
            transformOrigin3d(px(10), px(10), px(10)),
            ...box,
          ])
        )
      />
    </Section>
    <Section name="transition">
      <div
        className=Css.(
          style([
            transition(
              ~duration=300,
              ~delay=300,
              ~timingFunction=easeInOut,
              "transform",
            ),
            ...box,
          ])
        )
      />
      <div
        className=Css.(
          style([
            transitionProperty("height"),
            transitionDelay(300),
            transitionDuration(300),
            transitionTimingFunction(linear),
            ...box,
          ])
        )
      />
    </Section>
    <Section name="text">
      <p
        className=Css.(
          style([
            color(black),
            fontFamily("Helvetica, sans-serif"),
            fontSize(pt(18)),
            fontVariant(`smallCaps),
            fontStyle(italic),
            fontWeight(300),
            letterSpacing(px(3)),
            lineHeight(`abs(2.)),
            textAlign(`left),
            textDecoration(underline),
            textDecorationColor(pink),
            textDecorationStyle(wavy),
            textIndent(px(10)),
            textOverflow(clip),
            textShadow(~y=px(3), ~blur=px(2), black),
            textTransform(capitalize),
            verticalAlign(sub),
            whiteSpace(normal),
            wordBreak(breakAll),
            wordSpacing(px(20)),
            wordWrap(breakWord),
          ])
        )>
        {
          text(
            "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.",
          )
        }
      </p>
    </Section>
    <Section name="animation">
      <div
        className=Css.(
          style([
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
            ...box,
          ])
        )
      />
      <div
        className=Css.(
          style([
            animations([
              animation(~duration=300, ~iterationCount=infinite, spin),
              animation(
                ~duration=300,
                ~iterationCount=infinite,
                scaleAnimation,
              ),
            ]),
            ...box,
          ])
        )
      />
      <div
        className=Css.(
          style([
            animationName(spin),
            animationTimingFunction(easeIn),
            animationDuration(300),
            animationDelay(300),
            animationDirection(normal),
            animationFillMode(backwards),
            animationPlayState(paused),
            animationIterationCount(count(5)),
            ...box,
          ])
        )
      />
    </Section>
  </div>;
