open Css;

let fontItem =
  style(. [|
    marginLeft(px(10)),
    paddingRight(px(10)),
    borderRight(px(1), solid, black),
  |]);

let spin = renderer =>
  renderKeyframes(.
    renderer,
    [|
      (0, [|transform(rotate(deg(0.)))|]),
      (100, [|transform(rotate(deg(360.)))|]),
    |],
  );

let scaleAnimation = renderer =>
  renderKeyframes(.
    renderer,
    [|
      (0, [|transform(scale(0.3, 0.3))|]),
      (100, [|transform(scale(1.0, 1.0))|]),
    |],
  );

let redBox =
  style(. [|
    background(red),
    borderBottom(px(5), solid, black),
    width(px(50)),
    height(px(50)),
    margin(px(10)),
  |]);

let miniBox =
  style(. [|
    border(px(2), solid, black),
    width(px(15)),
    height(px(15)),
    margin(px(1)),
  |]);

// https://github.com/SentiaAnalytics/bs-css/issues/86
let mergedStyles =
  merge(. [|
    style(. [|padding(px(0)), fontSize(px(1))|]),
    style(. [|padding(px(20)), fontSize(px(24)), color(blue)|]),
    style(. [|media("(max-width: 768px)", [|padding(px(10))|])|]),
    style(. [|
      media("(max-width: 768px)", [|fontSize(px(16)), color(red)|]),
    |]),
  |]);

let differentHeightLengths = css =>
  [|
    cm(1.),
    em(1.2),
    ex(1.2),
    mm(10.),
    pct(50.),
    pt(14),
    px(20),
    rem(2.0),
    vh(1.),
    vw(1.0),
    vmax(1.0),
    vmin(1.0),
    zero,
  |]
  ->Belt.Array.map(x => {
      let className = css(. merge2(. redBox, style(. [|height(x)|])));
      <div className key=className />;
    });

[@react.component]
let make = () => {
  let {css, renderer, _} = CssReact.useFela();
  let cx = (baseStyle, rules) =>
    css(. merge2(. baseStyle, style(. rules)));

  let spinAnimationName = spin(renderer);

  <div>
    <Section name="Angles">
      <div className={cx(redBox, [|transform(rotate(deg(45.)))|])} />
      <div className={cx(redBox, [|transform(rotate(rad(3.1415)))|])} />
      <div className={cx(redBox, [|transform(rotate(grad(50.)))|])} />
      <div
        className={cx(redBox, [|transform(rotate(turn(1. /. 3.)))|])}
      />
    </Section>
    <Section name="Colors">
      <div className={cx(redBox, [|background(red)|])} />
      <div className={cx(redBox, [|background(rgb(255, 0, 0))|])} />
      <div
        className={cx(redBox, [|background(rgba(255, 0, 0, `num(0.5)))|])}
      />
      <div
        className={cx(
          redBox,
          [|background(hsl(deg(255.), pct(100.), pct(50.)))|],
        )}
      />
      <div
        className={cx(
          redBox,
          [|
            background(hsla(deg(255.), pct(100.), pct(50.), `num(0.5))),
          |],
        )}
      />
      <div className={cx(redBox, [|background(hex("FF0000"))|])} />
      <div className={cx(redBox, [|background(transparent)|])} />
      <div
        className={cx(redBox, [|background(currentColor), color(blue)|])}
      />
    </Section>
    <Section name="Named colors">
      {React.array(
         [|
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
         |]
         ->Belt.Array.map(((name, value)) =>
             <div
               key=name
               title=name
               className={cx(miniBox, [|background(value)|])}
             />
           ),
       )}
    </Section>
    <Section name="Gradients">
      <div
        className={cx(
          redBox,
          [|
            background(
              linearGradient(deg(45.), [(zero, red), (pct(100.), blue)]),
            ),
          |],
        )}
      />
      <div
        className={cx(
          redBox,
          [|
            background(
              repeatingLinearGradient(
                deg(45.),
                [(zero, red), (pct(10.), blue)],
              ),
            ),
          |],
        )}
      />
      <div
        className={cx(
          redBox,
          [|
            background(radialGradient([(zero, red), (pct(100.), blue)])),
          |],
        )}
      />
      <div
        className={cx(
          redBox,
          [|
            background(
              repeatingRadialGradient([(zero, red), (pct(10.), blue)]),
            ),
          |],
        )}
      />
    </Section>
    <Section name="Lengths">
      <div
        className={cx(
          redBox,
          [|
            height(ch(1.2)),
            width(px(10)),
            maxHeight(pct(50.)),
            maxWidth(pct(100.)),
          |],
        )}
      />
      {differentHeightLengths(css)->React.array}
    </Section>
    <Section name="Calc">
      <div className={cx(redBox, [|height(Calc.(pt(14) - px(10)))|])} />
      <div className={cx(redBox, [|height(Calc.(cm(0.2) + mm(10.)))|])} />
    </Section>
    <Section name="Display">
      <div className={cx(redBox, [|display(block)|])} />
      <div className={cx(redBox, [|display(inline)|])} />
      <div className={cx(redBox, [|display(inlineBlock)|])} />
      <div className={cx(redBox, [|display(none)|])} />
      <div className={cx(redBox, [|display(flexBox)|])} />
    </Section>
    <Section name="Position">
      <div
        className={cx(
          redBox,
          [|
            position(absolute),
            top(zero),
            left(zero),
            right(zero),
            bottom(zero),
          |],
        )}
      />
      <div className={cx(redBox, [|position(relative)|])} />
      <div
        className={cx(
          redBox,
          [|position(fixed), bottom(px(10)), right(px(10))|],
        )}
      />
      <div className={cx(redBox, [|position(static)|])} />
      <div className={cx(redBox, [|position(sticky)|])} />
    </Section>
    <Section name="Padding & Margin">
      <div className={cx(redBox, [|padding(px(10)), margin(px(10))|])} />
      <div
        className={cx(
          redBox,
          [|
            paddingLeft(px(10)),
            paddingRight(px(10)),
            paddingTop(px(10)),
            paddingBottom(px(10)),
            marginLeft(px(10)),
            marginRight(px(10)),
            marginTop(px(10)),
            marginBottom(px(10)),
          |],
        )}
      />
      <div
        className={cx(
          redBox,
          [|
            padding2(~v=px(10), ~h=px(20)),
            margin2(~v=px(10), ~h=px(20)),
          |],
        )}
      />
      <div
        className={cx(
          redBox,
          [|
            padding3(~top=px(10), ~h=px(20), ~bottom=px(1)),
            margin3(~top=px(10), ~h=px(20), ~bottom=px(2)),
          |],
        )}
      />
      <div
        className={cx(
          redBox,
          [|
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
          |],
        )}
      />
    </Section>
    <Section name="Grid">
      <div
        className={
          css(.
            style(. [|
              width(pct(100.)),
              height(px(500)),
              display(grid),
              gridTemplateColumns([|px(150), auto, px(150)|]),
              gridTemplateRows([|px(60), auto|]),
            |]),
          )
        }>
        <div
          className={
            css(.
              style(. [|
                gridColumnStart(1),
                gridColumnEnd(4),
                background(red),
                gridRowStart(1),
                gridRowEnd(1),
              |]),
            )
          }
        />
        <div
          className={
            css(.
              style(. [|
                background(blue),
                gridColumn(1, 1),
                gridRow(2, 2),
              |]),
            )
          }
        />
        <div
          className={
            css(.
              style(. [|
                background(green),
                gridColumn(2, 2),
                gridRow(2, 2),
                display(inlineGrid),
                gridTemplateColumns([|px(50), auto|]),
                gridTemplateRows([|px(40), auto|]),
              |]),
            )
          }>
          <div
            className={
              css(.
                style(. [|
                  background(yellow),
                  gridRow(1, 1),
                  gridColumn(2, 2),
                |]),
              )
            }
          />
          <div
            className={
              css(.
                style(. [|
                  background(green),
                  gridRow(1, 2),
                  gridColumn(1, 1),
                |]),
              )
            }
          />
          <div
            className={
              css(.
                style(. [|
                  background(purple),
                  gridRow(2, 2),
                  gridColumn(2, 2),
                |]),
              )
            }
          />
        </div>
        <div
          className={
            css(.
              style(. [|
                gridColumnStart(3),
                gridColumnEnd(3),
                background(blue),
                gridRowStart(2),
                gridRowEnd(2),
              |]),
            )
          }
        />
      </div>
      <div
        className={css(. style(. [|display(`grid), gridAutoFlow(`row)|]))}>
        <div className={css(. style(. [|background(purple)|]))}>
          "grid auto direction row 1"->React.string
        </div>
        <div className={css(. style(. [|background(green)|]))}>
          "grid auto direction row 2"->React.string
        </div>
      </div>
      <div
        className={
          css(.
            style(. [|
              display(`grid),
              gridTemplateColumns([|100->px, `repeat((`num(2), 60->px))|]),
            |]),
          )
        }>
        <div className={css(. style(. [|background(purple)|]))}>
          "Grid track repeat"->React.string
        </div>
        <div className={css(. style(. [|background(green)|]))}>
          "two times"->React.string
        </div>
        <div className={css(. style(. [|background(red)|]))}>
          "three times"->React.string
        </div>
      </div>
      <div
        className={
          css(. style(. [|display(`grid), gridAutoColumns(100->px)|]))
        }>
        <div className={css(. style(. [|background(purple)|]))}>
          "Grid auto columns (100px)"->React.string
        </div>
        <div className={css(. style(. [|background(green)|]))}>
          "100px"->React.string
        </div>
        <div className={css(. style(. [|background(blue)|]))}>
          "100px"->React.string
        </div>
      </div>
    </Section>
    <Section name="Flexbox">
      <div
        className={
          css(.
            style(. [|
              flexDirection(column),
              flexGrow(1.),
              alignItems(stretch),
              selector(
                "& > *",
                [|marginBottom(px(10)), width(pct(100.))|],
              ),
            |]),
          )
        }>
        <div
          className={
            css(.
              style(. [|
                display(flexBox),
                flexDirection(row),
                background(gray),
                alignItems(flexStart),
                justifyContent(flexEnd),
              |]),
            )
          }>
          <div
            className={cx(
              redBox,
              [|order(1), flexGrow(1.), flexShrink(1.), flexBasis(auto)|],
            )}
          />
          <div className={cx(redBox, [|flex(none)|])} />
          <div
            className={cx(
              redBox,
              [|order(1), flex3(~grow=1.5, ~shrink=0.8, ~basis=100->px)|],
            )}
          />
          <div className={cx(redBox, [|alignSelf(flexEnd)|])} />
          <div className={css(. redBox)} />
        </div>
        <div
          className={
            css(.
              style(. [|
                display(flexBox),
                flexDirection(column),
                background(gray),
                alignItems(baseline),
                justifyContent(flexStart),
              |]),
            )
          }>
          <div className={css(. redBox)} />
          <div className={css(. redBox)} />
          <div className={css(. redBox)} />
        </div>
        <div
          className={
            css(.
              style(. [|
                display(flexBox),
                flexDirection(rowReverse),
                background(gray),
                alignItems(center),
                justifyContent(spaceBetween),
              |]),
            )
          }>
          <div className={css(. redBox)} />
          <div
            className={cx(redBox, [|height(px(50)), width(px(50))|])}
          />
          <div className={css(. redBox)} />
        </div>
        <div
          className={
            css(.
              style(. [|
                display(flexBox),
                flexDirection(columnReverse),
                background(gray),
                alignItems(flexEnd),
                justifyContent(flexEnd),
              |]),
            )
          }>
          <div className={css(. redBox)} />
          <div
            className={cx(redBox, [|height(px(50)), width(px(50))|])}
          />
          <div className={css(. redBox)} />
        </div>
        <div
          className={
            css(.
              style(. [|
                display(flexBox),
                flexDirection(row),
                background(gray),
                alignItems(stretch),
                justifyContent(spaceAround),
              |]),
            )
          }>
          <div className={css(. redBox)} />
          <div
            className={cx(redBox, [|height(px(50)), width(px(50))|])}
          />
          <div className={css(. redBox)} />
        </div>
        <div
          className={
            css(.
              style(. [|
                display(flexBox),
                flexDirection(row),
                background(gray),
                alignItems(stretch),
                justifyContent(spaceEvenly),
              |]),
            )
          }>
          <div className={css(. redBox)} />
          <div
            className={cx(redBox, [|height(px(50)), width(px(50))|])}
          />
          <div className={css(. redBox)} />
        </div>
      </div>
    </Section>
    <Section name="Float">
      <div className={cx(redBox, [|Css.float(`left), clear(`right)|])} />
      <div className={cx(redBox, [|Css.float(`right), clear(`left)|])} />
      <div className={cx(redBox, [|Css.float(none), clear(both)|])} />
    </Section>
    <Section name="Overflow">
      <div className={cx(redBox, [|overflow(hidden)|])} />
      <div className={cx(redBox, [|overflow(visible)|])} />
      <div className={cx(redBox, [|overflow(auto)|])} />
      <div className={cx(redBox, [|overflow(scroll)|])} />
    </Section>
    <Section name="Border">
      <div
        className={cx(
          redBox,
          [|border(px(5), solid, blue), borderRadius(px(1000))|],
        )}
      />
      <div
        className={cx(
          redBox,
          [|
            border(px(5), solid, green),
            borderTopRightRadius(px(1000)),
            borderTopLeftRadius(px(1000)),
            borderBottomRightRadius(px(1000)),
            borderBottomLeftRadius(px(1000)),
          |],
        )}
      />
      <div
        className={cx(
          redBox,
          [|
            borderTop(px(5), dashed, hex("FFF")),
            borderRight(px(5), dotted, rgb(0, 0, 0)),
            borderBottom(px(5), none, green),
            borderLeft(px(5), solid, blue),
          |],
        )}
      />
      <div
        className={cx(
          redBox,
          [|borderWidth(px(5)), borderStyle(solid), borderColor(blue)|],
        )}
      />
      <div
        className={cx(
          redBox,
          [|
            borderTopWidth(px(5)),
            borderTopStyle(solid),
            borderTopColor(blue),
          |],
        )}
      />
      <div
        className={cx(
          redBox,
          [|
            borderBottomWidth(px(5)),
            borderBottomStyle(solid),
            borderBottomColor(blue),
          |],
        )}
      />
      <div
        className={cx(
          redBox,
          [|
            borderLeftWidth(px(5)),
            borderLeftStyle(solid),
            borderLeftColor(blue),
          |],
        )}
      />
      <div
        className={cx(
          redBox,
          [|
            borderRightWidth(px(5)),
            borderRightStyle(solid),
            borderRightColor(blue),
          |],
        )}
      />
    </Section>
    <Section name="Background">
      <div
        className={cx(
          redBox,
          [|
            background(red),
            backgroundAttachment(scroll),
            backgroundClip(borderBox),
            backgroundOrigin(borderBox),
            backgroundPosition(`hv((pct(50.), pct(50.)))),
            backgroundRepeat(noRepeat),
            backgroundSize(size(px(100), px(100))),
          |],
        )}
      />
      <div
        className={cx(
          redBox,
          [|
            background(radialGradient([(zero, red), (pct(10.), blue)])),
            backgroundAttachment(fixed),
            backgroundClip(contentBox),
            backgroundOrigin(contentBox),
            backgroundRepeat(repeat),
            backgroundSize(auto),
          |],
        )}
      />
      <div
        className={cx(
          redBox,
          [|
            background(url("./img-29.jpg")),
            backgroundAttachment(local),
            backgroundClip(paddingBox),
            backgroundOrigin(paddingBox),
            backgroundRepeat(repeatX),
            backgroundSize(cover),
          |],
        )}
      />
      <div
        className={cx(
          redBox,
          [|
            backgroundColor(rgb(0, 0, 255)),
            backgroundImage(
              linearGradient(
                deg(45.),
                [(zero, green), (pct(50.), red), (pct(100.), yellow)],
              ),
            ),
            backgroundRepeat(repeatY),
            backgroundSize(contain),
          |],
        )}
      />
    </Section>
    <Section name="Cursor">
      <div className={cx(redBox, [|cursor(`auto)|])}>
        "auto"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`default)|])}>
        "default"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`none)|])}>
        "none"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`contextMenu)|])}>
        "context menu"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`help)|])}>
        "help"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`pointer)|])}>
        "pointer"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`progress)|])}>
        "progress"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`wait)|])}>
        "wait"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`cell)|])}>
        "cell"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`crosshair)|])}>
        "crosshair"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`text)|])}>
        "text"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`verticalText)|])}>
        "vert text"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`alias)|])}>
        "alias"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`copy)|])}>
        "copy"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`move)|])}>
        "move"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`noDrop)|])}>
        "no drop"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`notAllowed)|])}>
        "not allowed"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`grab)|])}>
        "grab"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`grabbing)|])}>
        "grabbing"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`allScroll)|])}>
        "all scroll"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`colResize)|])}>
        "col resize"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`rowResize)|])}>
        "row resize"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`nResize)|])}>
        "n resize"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`eResize)|])}>
        "e resize"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`sResize)|])}>
        "s resize"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`wResize)|])}>
        "w resize"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`neResize)|])}>
        "ne resize"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`nwResize)|])}>
        "nw resize"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`seResize)|])}>
        "se resize"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`swResize)|])}>
        "sw resize"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`ewResize)|])}>
        "ew resize"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`nsResize)|])}>
        "ns resize"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`neswResize)|])}>
        "nesw resize"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`nwseResize)|])}>
        "nwse resize"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`zoomIn)|])}>
        "zoom in"->React.string
      </div>
      <div className={cx(redBox, [|cursor(`zoomOut)|])}>
        "zoom out"->React.string
      </div>
    </Section>
    <Section name="List">
      <ul>
        <li
          className={css(. style(. [|listStyle(`disc, inside, none)|]))}
        />
        <li className={css(. style(. [|listStyleType(`circle)|]))} />
        <li className={css(. style(. [|listStyleType(`square)|]))} />
        <li className={css(. style(. [|listStyleType(`decimal)|]))} />
        <li className={css(. style(. [|listStyleType(`lowerAlpha)|]))} />
        <li className={css(. style(. [|listStyleType(`upperAlpha)|]))} />
        <li className={css(. style(. [|listStyleType(`lowerGreek)|]))} />
        <li className={css(. style(. [|listStyleType(`lowerLatin)|]))} />
        <li className={css(. style(. [|listStyleType(`upperLatin)|]))} />
        <li className={css(. style(. [|listStyleType(`lowerRoman)|]))} />
        <li className={css(. style(. [|listStyleType(`upperRoman)|]))} />
        <li
          className={
            css(.
              style(. [|
                listStyleType(`disc),
                listStylePosition(inside),
                listStyleImage(url("./facebook.png")),
              |]),
            )
          }
        />
      </ul>
    </Section>
    <Section name="Outline">
      <div className={cx(redBox, [|outline(px(5), `double, green)|])} />
      <div
        className={cx(
          redBox,
          [|
            outlineStyle(solid),
            outlineWidth(px(5)),
            outlineColor(green),
            outlineOffset(px(5)),
          |],
        )}
      />
      <div className={cx(redBox, [|outline(px(5), `double, red)|])} />
      <div className={cx(redBox, [|outline(px(5), `ridge, red)|])} />
    </Section>
    <Section name="Transform">
      <div className={cx(redBox, [|opacity(0.5)|])} />
      <div
        className={cx(
          redBox,
          [|perspective(px(500)), transform(rotate(deg(10.)))|],
        )}
      />
      <div
        className={cx(
          redBox,
          [|
            transforms([|
              translate(px(10), pct(10.)),
              skew(deg(10.), deg(10.)),
            |]),
          |],
        )}
      />
      <div
        className={cx(
          redBox,
          [|
            transform(rotate(deg(19.))),
            transformOrigin(pct(50.), pct(50.)),
            transformStyle(`preserve3d),
            perspective(px(900)),
            perspectiveOrigin(pct(10.), pct(10.)),
          |],
        )}
      />
      <div
        className={cx(
          redBox,
          [|
            transform(translate(px(10), pct(10.))),
            transformOrigin3d(px(10), px(10), px(10)),
          |],
        )}
      />
    </Section>
    <Section name="Transition">
      <div
        className={cx(
          redBox,
          [|
            transition(
              ~duration=300,
              ~delay=300,
              ~timingFunction=easeInOut,
              "transform",
            ),
          |],
        )}
      />
      <div
        className={cx(
          redBox,
          [|
            transitionProperty("height"),
            transitionDelay(300),
            transitionDuration(300),
            transitionTimingFunction(linear),
          |],
        )}
      />
    </Section>
    <Section name="Text">
      <p
        className={
          css(.
            style(. [|
              color(black),
              fontFamilies([|`custom("Helvetica"), `sansSerif|]),
              fontSize(pt(18)),
              fontVariant(`smallCaps),
              fontStyle(italic),
              fontWeight(`num(300)),
              letterSpacing(px(3)),
              lineHeight(`abs(2.)),
              textAlign(`left),
              textDecoration(underline),
              textDecorationColor(pink),
              textDecorationStyle(wavy),
              textIndent(px(10)),
              textOverflow(clip),
              textShadow(Shadow.text(~y=px(3), ~blur=px(2), black)),
              textTransform(capitalize),
              verticalAlign(sub),
              whiteSpace(normal),
              wordBreak(breakAll),
              wordSpacing(px(20)),
              wordWrap(breakWord),
            |]),
          )
        }>
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."
        ->React.string
      </p>
      <h2 className={css(. style(. [|width(pct(100.))|]))}>
        "Named Font weights"->React.string
      </h2>
      <span
        className={
          css(.
            style(. [|
              fontWeight(thin),
              paddingRight(px(10)),
              borderRight(px(1), solid, black),
            |]),
          )
        }>
        "thin"->React.string
      </span>
      <span className={cx(fontItem, [|fontWeight(`extraLight)|])}>
        "extra light"->React.string
      </span>
      <span className={cx(fontItem, [|fontWeight(`light)|])}>
        "light"->React.string
      </span>
      <span className={cx(fontItem, [|fontWeight(`normal)|])}>
        "normal"->React.string
      </span>
      <span className={cx(fontItem, [|fontWeight(`medium)|])}>
        "medium"->React.string
      </span>
      <span className={cx(fontItem, [|fontWeight(`semiBold)|])}>
        "semiBold"->React.string
      </span>
      <span className={cx(fontItem, [|fontWeight(`bold)|])}>
        "bold"->React.string
      </span>
      <span className={cx(fontItem, [|fontWeight(`extraBold)|])}>
        "extra bold"->React.string
      </span>
      <span className={cx(fontItem, [|fontWeight(`black)|])}>
        "black"->React.string
      </span>
      <span className={cx(fontItem, [|fontWeight(`lighter)|])}>
        "lighter"->React.string
      </span>
      <span className={cx(fontItem, [|fontWeight(`bolder)|])}>
        "bolder"->React.string
      </span>
    </Section>
    <Section name="Animation">
      <div
        className={cx(
          redBox,
          [|
            animation(
              ~duration=300,
              ~delay=300,
              ~direction=reverse,
              ~timingFunction=linear,
              ~fillMode=forwards,
              ~playState=running,
              ~iterationCount=infinite,
              spinAnimationName,
            ),
          |],
        )}
      />
      <div
        className={cx(
          redBox,
          [|
            animations([|
              Animation.shorthand(
                ~duration=300,
                ~iterationCount=infinite,
                spinAnimationName,
              ),
              Animation.shorthand(
                ~duration=300,
                ~iterationCount=infinite,
                scaleAnimation(renderer),
              ),
            |]),
          |],
        )}
      />
      <div
        className={cx(
          redBox,
          [|
            animationName(spinAnimationName),
            animationTimingFunction(easeIn),
            animationDuration(300),
            animationDelay(300),
            animationDirection(normal),
            animationFillMode(backwards),
            animationPlayState(paused),
            animationIterationCount(count(5)),
          |],
        )}
      />
    </Section>
    <Section name="Cascading">
      "inherit"->React.string
      <div
        className={
          css(.
            style(. [|
              display(inherit_),
              position(inherit_),
              fontSize(inherit_),
              fontStyle(inherit_),
              lineHeight(inherit_),
            |]),
          )
        }
      />
      "unset"->React.string
      <div
        className={
          css(.
            style(. [|
              display(unset),
              position(unset),
              fontSize(unset),
              fontStyle(unset),
              lineHeight(unset),
            |]),
          )
        }
      />
    </Section>
    <Section name="Columns">
      <p className={css(. style(. [|columnCount(count(10))|]))}>
        "This is a bunch of text split into columns
             using the CSS `column-count` property. The text
             is equally distributed over the columns."
        ->React.string
      </p>
    </Section>
    <Section name="Resize">
      <textarea
        className={css(. style(. [|resize(none)|]))}
        value="Can't resize textarea"
        readOnly=true
      />
      <div
        className={
          css(.
            style(. [|
              marginLeft(px(20)),
              overflow(scroll),
              resize(horizontal),
            |]),
          )
        }>
        "Resizable div (horizontal)"->React.string
      </div>
      <div
        className={
          css(.
            style(. [|
              marginLeft(px(20)),
              overflow(scroll),
              resize(vertical),
            |]),
          )
        }>
        "Resizable div (vertical)"->React.string
      </div>
    </Section>
    <Section name="Content">
      <div
        className={
          css(.
            style(. [|
              position(relative),
              after([|
                contentRule(`none),
                position(absolute),
                top(zero),
                left(zero),
                width(pct(100.)),
                height(pct(100.)),
                border(px(1), solid, black),
              |]),
            |]),
          )
        }>
        "none"->React.string
      </div>
      <div
        className={
          css(.
            style(. [|
              position(relative),
              after([|
                contentRule(`normal),
                position(absolute),
                top(zero),
                left(zero),
                width(pct(100.)),
                height(pct(100.)),
                border(px(1), solid, black),
              |]),
            |]),
          )
        }>
        "normal"->React.string
      </div>
      <div
        className={
          css(. style(. [|position(relative), marginLeft(px(20))|]))
        }>
        <a
          href="https://github.com/SentiaAnalytics/bs-css"
          className={
            css(.
              style(. [|
                before([|
                  contentRule(`text("external ")),
                  backgroundColor(red),
                  display(inlineBlock),
                  flexBasis(content /*for test*/),
                |]),
              |]),
            )
          }>
          "link"->React.string
        </a>
      </div>
      <div
        className={
          css(.
            style(. [|
              position(relative),
              marginLeft(px(20)),
              after([|
                contentRule(`text("")),
                position(absolute),
                top(zero),
                left(zero),
                width(pct(100.)),
                height(pct(100.)),
                border(px(1), solid, black),
              |]),
            |]),
          )
        }>
        "empty content"->React.string
      </div>
      <div
        className={
          css(.
            style(. [|
              position(relative),
              marginLeft(px(20)),
              paddingLeft(px(20)),
              after([|
                contentRule(`url("https://via.placeholder.com/18")),
                position(absolute),
                top(zero),
                left(zero),
                width(px(18)),
                height(px(18)),
                border(px(1), solid, black),
              |]),
            |]),
          )
        }>
        "url"->React.string
      </div>
      <div
        className={
          css(.
            style(. [|
              marginLeft(px(20)),
              counterReset(Types.CounterReset.reset("foo", ~value=1)),
              before([|
                contentRule(Types.Counter.counter("foo")),
                border(px(1), solid, black),
              |]),
            |]),
          )
        }>
        "counter"->React.string
      </div>
      <div
        className={
          css(.
            style(. [|
              counterReset(Types.CounterReset.reset("foo", ~value=1)),
              marginLeft(px(20)),
            |]),
          )
        }>
        <div
          className={
            css(.
              style(. [|
                counterReset(Types.CounterReset.reset("foo", ~value=2)),
                before([|
                  contentRule(
                    Types.Counters.counters(
                      "foo",
                      ~separator="@",
                      ~style=`upperRoman,
                    ),
                  ),
                  border(px(1), solid, black),
                |]),
              |]),
            )
          }>
          "counters"->React.string
        </div>
      </div>
      <div
        className={
          css(.
            style(. [|
              marginLeft(px(20)),
              before([|
                contentRule(`attr("class")),
                border(px(1), solid, black),
              |]),
            |]),
          )
        }>
        "attr"->React.string
      </div>
      <div
        className={
          css(.
            style(. [|
              marginLeft(px(20)),
              before([|
                contentRule(
                  Types.Gradient.linearGradient(
                    deg(45.),
                    [(zero, red), (pct(100.), blue)],
                  ),
                ),
                border(px(1), solid, black),
                display(`inlineBlock),
                height(px(18)),
                width(px(18)),
              |]),
            |]),
          )
        }>
        "linear gradient"->React.string
      </div>
      <div
        className={
          css(.
            style(. [|
              marginLeft(px(20)),
              before([|
                contentRules([|`openQuote, `text("foo"), `closeQuote|]),
                border(px(1), solid, black),
              |]),
            |]),
          )
        }>
        "contents (quotes)"->React.string
      </div>
    </Section>
    <Section name="InsertRule, the ultimate escape hatch">
      "Render a green square --> "->React.string
      <div className="raw-css" />
    </Section>
    <Section name="Merging style names">
      <button className={css(. mergedStyles)}>
        "Merged"->React.string
      </button>
    </Section>
    <Section name="Filter">
      <div className={cx(redBox, [|filter([|`blur(`px(10))|])|])} />
      <div className={cx(redBox, [|filter([|`brightness(50.)|])|])} />
      <div className={cx(redBox, [|filter([|`contrast(50.)|])|])} />
      <div
        className={cx(
          redBox,
          [|
            filter([|
              `dropShadow((
                `px(3),
                `px(3),
                `px(3),
                `rgb((200, 100, 100)),
              )),
            |]),
          |],
        )}
      />
      <div className={cx(redBox, [|filter([|`grayscale(50.)|])|])} />
      <div
        className={cx(redBox, [|filter([|`hueRotate(`deg(180.))|])|])}
      />
      <div className={cx(redBox, [|filter([|`invert(50.)|])|])} />
      <div className={cx(redBox, [|filter([|`opacity(50.)|])|])} />
      <div className={cx(redBox, [|filter([|`saturate(50.)|])|])} />
      <div className={cx(redBox, [|filter([|`sepia(50.)|])|])} />
      <div
        className={cx(
          redBox,
          [|
            filter([|
              `sepia(50.),
              `saturate(50.),
              `dropShadow((
                `px(3),
                `px(3),
                `px(3),
                `rgb((200, 100, 100)),
              )),
            |]),
          |],
        )}
      />
      <svg height="0" className={css(. style(. [|display(`none)|]))}>
        <filter id="f1"> <feGaussianBlur stdDeviation="3" /> </filter>
      </svg>
      <div className={cx(redBox, [|filter([|`url("#f1")|])|])} />
    </Section>
    <Section name="Direction">
      <Section name="ltr">
        <div
          className={css(. style(. [|direction(`ltr), display(`flex)|]))}>
          <div className={css(. redBox)}> "1"->React.string </div>
          <div className={css(. redBox)}> "2"->React.string </div>
          <div className={css(. redBox)}> "3"->React.string </div>
          <div className={css(. redBox)}> "4"->React.string </div>
        </div>
      </Section>
      <Section name="rtl">
        <div
          className={css(. style(. [|direction(`rtl), display(`flex)|]))}>
          <div className={css(. redBox)}> "1"->React.string </div>
          <div className={css(. redBox)}> "2"->React.string </div>
          <div className={css(. redBox)}> "3"->React.string </div>
          <div className={css(. redBox)}> "4"->React.string </div>
        </div>
      </Section>
      <Section name="Unset">
        <div
          className={css(. style(. [|direction(`unset), display(`flex)|]))}>
          <div className={css(. redBox)}> "1"->React.string </div>
          <div className={css(. redBox)}> "2"->React.string </div>
          <div className={css(. redBox)}> "3"->React.string </div>
          <div className={css(. redBox)}> "4"->React.string </div>
        </div>
      </Section>
    </Section>
    <Section name="object-fit">
      <img
        className={cx(redBox, [|objectFit(`fill)|])}
        src="./img-29.jpg"
      />
      <img
        className={cx(redBox, [|objectFit(`contain)|])}
        src="./img-29.jpg"
      />
      <img
        className={cx(redBox, [|objectFit(`cover)|])}
        src="./img-29.jpg"
      />
      <img
        className={cx(redBox, [|objectFit(`none)|])}
        src="./img-29.jpg"
      />
      <img
        className={cx(redBox, [|objectFit(`scaleDown)|])}
        src="./img-29.jpg"
      />
      <img
        className={cx(redBox, [|objectFit(`inherit_)|])}
        src="./img-29.jpg"
      />
      <img
        className={cx(redBox, [|objectFit(`initial)|])}
        src="./img-29.jpg"
      />
      <img
        className={cx(redBox, [|objectFit(`unset)|])}
        src="./img-29.jpg"
      />
    </Section>
  </div>;
};
