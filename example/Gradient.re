module Box = {
  let baseStyle =
    Css.(
      style([
        width(vw(10.)),
        height(vh(10.)),
        margin(vh(1.)),
        backgroundColor(hex("f5f5f5"))
      ])
    );
  let component = ReasonReact.statelessComponent("Box");
  let make = (~style, _children) => {
    ...component,
    render: _self => <div className=(Css.merge([baseStyle, style])) />
  };
};

let component = ReasonReact.statelessComponent("Gradient");

let make = _children => {
  ...component,
  render: _self =>
    <div>
      <Box
        style=Css.(
                style([
                  backgroundGradient(
                    linearGradient(
                      ToTopLeft,
                      [(hex("123"), pct(0.)), (hex("FED"), pct(100.))]
                    )
                  )
                ])
              )
      />
      <Box
        style=Css.(
                style([
                  backgroundGradient(
                    repeatingLinearGradient(
                      ToRight,
                      [(hex("123"), px(10)), (hex("FED"), px(15))]
                    )
                  )
                ])
              )
      />
      <Box
        style=Css.(
                style([
                  backgroundGradient(
                    repeatingRadialGradient(
                      Circle,
                      Bottom,
                      FromRight(pct(10.)),
                      FarthestCorner,
                      [(hex("123"), px(10)), (hex("FED"), px(15))]
                    )
                  )
                ])
              )
      />
    </div>
};
