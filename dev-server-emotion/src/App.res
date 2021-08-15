open CssJs

global(. "html, body", [margin(zero), padding(zero), backgroundColor(lavender)])

switch ReactDOM.querySelector("#app") {
| None => ()
| Some(dom) => ReactDOM.render(<Demo />, dom)
}
