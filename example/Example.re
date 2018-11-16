Css.(global("html, body", [margin(zero), padding(zero)]));

module Page = {
  let component = ReasonReact.statelessComponent("Page");
  let make = _ => {...component, render: _ => <div> Test.tests </div>};
};

ReactDOMRe.renderToElementWithId(<Page />, "app");
