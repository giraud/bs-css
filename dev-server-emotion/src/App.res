open CssJs
global(. "html, body", [margin(#zero), padding(#zero), backgroundColor(lavender)])

switch ReactDOM.querySelector("#app") {
| Some(el) => ReactDOM.render(<Test />, el)
| None => ()
}
