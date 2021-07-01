switch ReactDOM.querySelector("#app") {
| None => ()
| Some(dom) => ReactDOM.render(<Test />, dom)
}
