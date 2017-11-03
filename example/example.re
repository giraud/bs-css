module Page = {
  let styles =
    Css.(
      {
        "page":
          style([
            width(px(600)),
            height(px(600)),
            backgroundColor(rgba(0, 0, 0, 0.4)),
            backgroundImage("./img-29.jpg"),
            backgroundAttachment(Scroll),
            backgroundPosition(Left),
            border(px(60), Solid, black),
            transforms([rotate(deg(20.0)), scale(0.4, 0.4)]),
            boxShadow(shadow(~y=3, ~blur=15, rgba(0, 0, 0, 0.5)))
          ])
      }
    );
  let component = ReasonReact.statelessComponent("Page");
  let make = (_) => {...component, render: (_) => <div className=styles##page />};
};

ReactDOMRe.renderToElementWithId(<Page />, "app");
