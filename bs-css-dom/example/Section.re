module Styles = {
  open Css;

  let arialNarrow =
    fontFace(
      ~fontFamily="Arial FontFace Test",
      ~src=[localUrl("Arial Narrow")],
      ~fontStyle=normal,
      ~fontWeight=`num(500),
      (),
    );

  let section =
    style([
      selector(
        "& > h1",
        [
          fontFamily(`custom(arialNarrow)),
          fontSize(px(32)),
          fontWeight(`num(300)),
          marginTop(zero),
        ],
      ),
      position(relative),
      background(hex("f5f5f5")),
      margin(px(20)),
      padding(px(10)),
      boxShadow(Shadow.box(~y=px(1), ~blur=px(5), rgba(0, 0, 0, 0.3))),
      boxShadows([
        Shadow.box(~y=px(1), ~blur=px(5), rgba(0, 0, 0, 0.3)),
        Shadow.box(
          ~y=px(1),
          ~blur=px(10),
          ~inset=true,
          rgba(255, 255, 255, 0.5),
        ),
      ]),
    ]);

  let rowLayout =
    style([display(flexBox), flexDirection(row), flexWrap(wrap)]);
};

[@react.component]
let make = (~name, ~children) =>
  <section style=Styles.section>
    <h1> name->ReasonReact.string </h1>
    <div style=Styles.rowLayout> children </div>
  </section>;