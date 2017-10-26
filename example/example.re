module Page = {
  let styles =
    Css.(
      {
        "page":
          style [
            width 600.0 px,
            height 600.0 px,
            backgroundColor (rgba 0 0 0 0.4),
            backgroundImage "./img-29.jpg",
            backgroundAttachment Scroll,
            backgroundPosition Left,
            border 10.0 px Solid black,
            transforms [rotate 20.0 deg, scale 0.4 0.4],
            boxShadow 0. px 3. px 5. px 0. px (rgba 0 0 0 0.3)
          ]
      }
    );
  let component = ReasonReact.statelessComponent "Page";
  let make _ => {...component, render: fun _ => <div className=styles##page />};
};

ReactDOMRe.renderToElementWithId <Page /> "app";