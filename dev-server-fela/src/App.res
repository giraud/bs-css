open Css;
let renderer = createRenderer();

renderGlobal(. renderer, "html, body", [margin(#zero), padding(#zero), backgroundColor(lavender)])
renderRule(. renderer, ".raw-css { display:block; background-color: green; width: 50px; height: 50px; }")

ReactDOMRe.renderToElementWithId(
    <CssReact.RendererProvider renderer>
        <Test/>
    </CssReact.RendererProvider>, "app");
