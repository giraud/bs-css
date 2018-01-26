Css.(global("html, body", [
  margin(zero),
  padding(zero)
]));
let text = ReasonReact.stringToElement;
let fadeIn = Css.(keyframes([
  (0, [opacity(0.)]),
  (100, [opacity(1.)]),
]));

let spin = Css.(keyframes([
  (0, [ transform(rotate(deg(0))) ]),
  (100, [ transform(rotate(deg(360))) ]),
]));



module Page = {
  let styles = Css.({
    "page": [
      boxSizing(borderBox),
      width(vw(100.)),
      height(vh(100.))
    ]
  });
  let component = ReasonReact.statelessComponent("Page");
  let make = (_) => {
    ...component,
    render: (_) => {
      <div> 
        <div className=(Css.style(styles##page))> 
       Test.tests
        </div>
      </div>
    }
  };
};
ReactDOMRe.renderToElementWithId(<Page />, "app");