switch ReactDOM.querySelector("#app") {
| Some(el) => ReactDOM.render(<Test />, el)
| None => ()
}
