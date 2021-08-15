open Css
let renderer = createRenderer()

renderGlobal(. renderer, "html, body", [margin(#zero), padding(#zero), backgroundColor(lavender)])
renderRule(.
  renderer,
  ".raw-css { display:block; background-color: green; width: 50px; height: 50px; }",
)

switch ReactDOM.querySelector("#app") {
| None => ()
| Some(dom) =>
  ReactDOM.render(<CssReact.RendererProvider renderer> <Demo /> </CssReact.RendererProvider>, dom)
}
