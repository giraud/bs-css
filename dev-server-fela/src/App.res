open Css
let renderer = createRenderer()

renderGlobal(. renderer, "html, body", [margin(#zero), padding(#zero), backgroundColor(lavender)])
renderRule(.
  renderer,
  ".raw-css { display:block; background-color: green; width: 50px; height: 50px; }",
)

switch ReactDOM.querySelector("#app") {
| Some(el) =>
  ReactDOM.render(<CssReact.RendererProvider renderer> <Test /> </CssReact.RendererProvider>, el)
| None => ()
}
