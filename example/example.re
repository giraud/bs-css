module Page = {
  let styles =
    Css.(
      {
        "page":
          style([
            position(Absolute),
            width(vw(100.)),
            height(vh(100.)),
            backgroundColor(rgba(0, 0, 0, 0.4)),
            backgroundImage("./img-29.jpg"),
            backgroundAttachment(Scroll),
            backgroundPosition(Left),
            border(vh(5.), Solid, black),
            transforms([rotate(deg(20.0)), scale(0.4, 0.4)]),
            boxShadow(shadow(~y=3, ~blur=15, rgba(0, 0, 0, 0.5)))
          ])
      }
    );
  let component = ReasonReact.statelessComponent("Page");
  let make = (_) => {
    ...component,
    render: (_) => <div> <div className=styles##page /> <Gradient /> </div>
  };
};

ReactDOMRe.renderToElementWithId(<Page />, "app");
