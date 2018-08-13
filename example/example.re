module Styles = {
  open Css;
  let fadeIn =
    Css.(keyframes([(0, [opacity(0.)]), (100, [opacity(1.)])]));
  let spin =
    Css.(
      keyframes([
        (0, [transform(rotate(deg(0)))]),
        (100, [transform(rotate(deg(360)))]),
      ])
    );
  global("html, body", [margin(zero), marginLeft(px(5)), padding(zero)]);
  let page =
    style([
      boxSizing(borderBox),
      background(linearGradient(deg(45), [(0, red), (100, blue)])),
      width(vw(100.)),
      height(vh(100.)),
    ]);
};

let text = ReasonReact.string;

module Page = {
  let component = ReasonReact.statelessComponent("Page");
  let make = _ => {
    ...component,
    render: _ => <div> <div className=Styles.page> Test.tests </div> </div>,
  };
};

ReactDOMRe.renderToElementWithId(<Page />, "app");
