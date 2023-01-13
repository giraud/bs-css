open CssJs

module Section = {
  module Styles = {
    let arialNarrow = fontFace(
      ~fontFamily="Arial FontFace Test",
      ~src=[localUrl("Arial Narrow")],
      ~fontStyle=normal,
      ~fontWeight=#num(500),
      (),
    )

    let section = style(. [
      selector(. "& > h1", [fontFamily(#custom(arialNarrow)), marginTop(zero)]),
      position(relative),
      background(hex("f5f5f5")),
      margin(20->px),
      padding(10->px),
      boxShadow(Shadow.box(~y=1->px, ~blur=5->px, rgba(0, 0, 0, #num(0.3)))),
      boxShadows([
        Shadow.box(~y=1->px, ~blur=5->px, rgba(0, 0, 0, #num(0.3))),
        Shadow.box(~y=1->px, ~blur=10->px, ~inset=true, rgba(255, 255, 255, #num(0.5))),
      ]),
    ])

    let rowLayout = style(. [display(flexBox), flexDirection(row), flexWrap(wrap)])
  }

  @react.component
  let make = (~name, ~children) =>
    <section className=Styles.section>
      <h1> {name->React.string} </h1> <div className=Styles.rowLayout> children </div>
    </section>
}

let redBox = [
  background(red),
  borderBottom(5->px, solid, black),
  width(50->px),
  height(50->px),
  margin(10->px),
]

module RedBox = {
  @react.component
  let make = (~rules=?, ~children=?) =>
    <div
      className={style(.
        rules->Belt.Option.mapWithDefaultU(redBox, (. r) => redBox->Belt.Array.concat(r)),
      )}>
      {switch children {
      | None => React.null
      | Some(c) => c
      }}
    </div>
}
