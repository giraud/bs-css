# bs-css

Statically typed DSL for writing css in reason.

The bs-css library contains type css core definitions, it has different implementations:

- bs-css-emotion is a typed interface to [Emotion](https://github.com/emotion-js/emotion)
- bs-css-fela is a typed interface to [Fela](https://github.com/robinweser/fela) (react)
- bs-css-dom is a typed interface to `ReactDOMRe.Style.t` (reason-react)

If you know another implementation that can be added, send a link in an issue or create a PR.

## Installation

```sh
npm install --save bs-css-emotion
or
yarn add bs-css-emotion
```

In your `bsconfig.json`, include `"bs-css"` and `"bs-css-emotion"` in the `bs-dependencies`.

You can replace `bs-css-emotion` with `bs-css-dom` in the above instructions if you prefer
to use React styles, or `bs-css-fela` for a different runtime.

## Usage for bs-css-emotion

```rescript
module Theme = {
  let basePadding = CssJs.px(5)
  let textColor = CssJs.black
}

module Styles = {
  /*
  Open the Css module, so we can access the style properties below without prefixing them with Css.
  You can use either Css or CssJs: Css module is using lists, CssJs is using arrays.
  If you're targeting js and/or using Rescript, prefer CssJs
 */
  open CssJs

  let card = style(. [
    display(flexBox),
    flexDirection(column),
    alignItems(stretch),
    backgroundColor(white),
    boxShadow(Shadow.box(~y=px(3), ~blur=px(5), rgba(0, 0, 0, #num(0.3)))),
    // You can add non-standard and other unsafe style declarations using the `unsafe` function, with strings as the two arguments
    unsafe("-webkit-overflow-scrolling", "touch"),
    // You can place all your theme styles in Theme.re and access as normal module
    padding(Theme.basePadding),
  ])

  let title = style(. [
    fontSize(rem(1.5)),
    lineHeight(#abs(1.25)),
    color(Theme.textColor),
    marginBottom(Theme.basePadding),
  ])

  let actionButton = disabled =>
    style(. [
      background(disabled ? darkgray : white),
      color(black),
      border(px(1), solid, black),
      borderRadius(px(3)),
    ])
}

@react.component
let make = () =>
  <div className=Styles.card>
    <h1 className=Styles.title> {React.string("Hello")} </h1>
    <button className={Styles.actionButton(false)} />
  </div>
```

**Global css**

You can define global css rules with `global`

```rescript
open CssJs

global(. "body", [margin(px(0))])
global(. "h1, h2, h3", [color(rgb(33, 33, 33))])
```

**Keyframes**

Define animation keyframes;

```rescript
open CssJs

let bounce = keyframes(. [
  (0, [transform(scale(0.1, 0.1)), opacity(0.0)]),
  (60, [transform(scale(1.2, 1.2)), opacity(1.0)]),
  (100, [transform(scale(1.0, 1.0)), opacity(1.0)]),
])

let styles = style(. [
  animationName(bounce),
  animationDuration(2000),
  width(px(50)),
  height(px(50)),
  backgroundColor(rgb(255, 0, 0)),
])

// ...
<div className=styles> {React.string("bounce!")} </div>
```

### Merging styles

You should avoid trying to merge styles in the same list of rules or by concatinating lists. A list of rules is converted into a JS object before being passed to Emotion where every property becomes a key in the object. This means you lose any earlier rule if you have another rule with the same property later in the list. This is especially noticable [when writing sub-selectors and media queries](https://github.com/SentiaAnalytics/bs-css/issues/86)

Trying to merge styles by just using `List.concat` can result in unexpected results.

This example:

```rescript
let base = Css.[
  padding(px(0)),
  fontSize(px(1))
];
let overrides = Css.[
  padding(px(20)),
  fontSize(px(24)),
  color(blue)
];
let media1 = Css.[
  media("(max-width: 768px)", [
    padding(px(10))
  ])
];
let media2 = Css.[
  media("(max-width: 768px)", [
    fontSize(px(16)),
    color(red)
  ])
];
let mergedStyles = [base, overrides, media1, media2]->List.concat->Css.style;
```

generates the following:

```css
.css-1nuk4bg {
  padding: 20px;
  font-size: 24px;
  color: #0000ff;
}
@media (max-width: 768px) {
  .css-1nuk4bg {
    font-size: 16px;
    color: #ff0000;
  }
}
```

As you can see both properties from `base` are overwritten (as opposed to overridden in css) and the media query in `media1` is also lost because the media query from `media2` overwrites it.

#### The `merge` method

`merge` safely merges styles by name. Uses [Emotion’s `cx` method](https://emotion.sh/docs/cx).

```reason
open CssJs

let mergedStyles = merge(. [
  style(. [padding(px(0)), fontSize(px(1))]),
  style(. [padding(px(20)), fontSize(px(24)), color(blue)]),
  style(. [media("(max-width: 768px)", [padding(px(10))])]),
  style(. [media("(max-width: 768px)", [fontSize(px(16)), color(red)])]),
])
```

Generates the following:

```css
.css-q0lkhz {
  padding: 0px;
  font-size: 1px;
  padding: 20px;
  font-size: 24px;
  color: #0000ff;
}
@media (max-width: 768px) {
  .css-q0lkhz {
    padding: 10px;
  }
}
@media (max-width: 768px) {
  .css-q0lkhz {
    font-size: 16px;
    color: #ff0000;
  }
}
```

Nothing is lost and everything ends up in the final stylesheet where normal overrides apply.

## Usage for bs-css-fela

First you need to use a provider in your Jsx:

```rescript
let renderer = createRenderer()

switch ReactDOM.querySelector("#app") {
| None => ()
| Some(dom) =>
  ReactDOM.render(<CssReact.RendererProvider renderer> ... </CssReact.RendererProvider>, dom)
}
```

Then, you need to use the useFela hook in your Jsx:

```rescript
module Styles = {
  /*
   Open the Css module, so we can access the style properties below without prefixing them with Css.
   You can use either Css or CssJs: Css module is using lists, CssJs is using arrays.
   If you're targeting js and/or using Rescript, prefer CssJs
  */
  open Css

  let card = style(. [
    display(flexBox),
    flexDirection(column),
    alignItems(stretch),
    backgroundColor(white),
    boxShadow(Shadow.box(~y=px(3), ~blur=px(5), rgba(0, 0, 0, #num(0.3)))),
    // You can add non-standard and other unsafe style declarations using the `unsafe` function, with strings as the two arguments
    unsafe("-webkit-overflow-scrolling", "touch"),
    // You can place all your theme styles in Theme.re and access as normal Reason module
    padding(Theme.basePadding),
  ])

  let title = style(. [
    fontSize(rem(1.5)),
    lineHeight(#abs(1.25)),
    color(Theme.textColor),
    marginBottom(Theme.basePadding),
  ])

  let actionButton = disabled =>
    style(. [
      background(disabled ? darkgray : white),
      color(black),
      border(px(1), solid, black),
      borderRadius(px(3)),
    ])
}

@react.component
let make = () => {
  let {css, _} = CssReact.useFela()

  <div className={css(. Styles.card)}>
    <h1 className={css(. Styles.title)}> {React.string("Hello")} </h1>
    <button className={css(. Styles.actionButton(false))} />
  </div>
}
```

**Global css**

You can define global css rules with `global`

```rescript       
open Css
let renderer = createRenderer()

renderGlobal(. renderer, "body", [margin(px(0))])
renderGlobal(. renderer, "h1, h2, h3", [color(rgb(33, 33, 33))])
```

## Usage for bs-css-dom

Use style instead of classname, for example:

```rescript
module Styles = {
  // Open the Css module, so we can access the style properties below without prefixing them with Css
  open CssJs

  let card = style(. [
    display(flexBox),
    flexDirection(column),
    alignItems(stretch),
    backgroundColor(white),
    boxShadow(Shadow.box(~y=px(3), ~blur=px(5), rgba(0, 0, 0, #num(0.3)))),
    // You can add non-standard and other unsafe style declarations using the `unsafe` function, with strings as the two arguments
    unsafe("-webkit-overflow-scrolling", "touch"),
    // You can place all your theme styles in Theme.re and access as normal Reason module
    padding(Theme.basePadding),
  ])

  let title = style(. [fontSize(rem(1.5)), color(Theme.textColor), marginBottom(Theme.basePadding)])

  let actionButton = disabled =>
    style(. [
      background(disabled ? darkgray : white),
      color(black),
      border(px(1), solid, black),
      borderRadius(px(3)),
    ])
}

@react.component
let make = () =>
  <div style=Styles.card>
    <h1 style=Styles.title> {React.string("Hello")} </h1>
    <button style={Styles.actionButton(false)} />
  </div>
```

## Where is the documentation?

You can check out [Css_Js_Core.rei](bs-css/src/Css_Js_Core.rei) and [Css_Legacy_Core.rei](bs-css/src/Css_Legacy_Core.rei).

## Thanks

Thanks to [emotion](https://github.com/emotion-js/emotion) which is doing all the heavy lifting.

Thanks to [bs-glamor](https://github.com/poeschko/bs-glamor) which this repo was forked from.

Thanks to [elm-css](https://github.com/rtfeldman/elm-css) for dsl design inspiration.
