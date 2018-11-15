# bs-css

statically typed DSL for writing css in reason.

Bs-css is a statically typed interface to [Emotion](https://github.com/emotion-js/emotion)

## Installation

```sh
npm install --save bs-css
```

In your `bsconfig.json`, include `"bs-css"` in the `bs-dependencies`.

## Usage

```reason
module Styles = {
  /*Open the Css module, so we can access the style properties below without prefixing them with Css.*/
  open Css;

  let card = style([
    display(flexBox),
    flexDirection(column),
    alignItems(stretch),
    backgroundColor(white),
    boxShadow(~y=px(3), ~blur=px(5), rgba(0, 0, 0, 0.3)),
    /* You can place all your theme styles in Theme.re and access as normal Reason module */
    padding(Theme.basePadding)
  ]);

  let title = style([
    fontSize(rem(1.5)),
    color(Theme.textColor),
    marginBottom(Theme.basePadding)
  ]);
  let actionButton = disabled =>
    style([
      background(disabled ? darkgray : white),
      color(black),
      border(px(1), solid, black),
      borderRadius(px(3)),
    ])
};

<div className=Styles.card>
  <h1 className=Styles.title> (ReasonReact.stringToElement("Hello")) </h1>
  <button className=Styles.actionButton(false)>
</div>
```

**Global css**

 You can define global css rules with `global`

 ```reason
 Css.(
   global("body", [margin(px(0))])
 );

 Css.(
   global("h1, h2, h3", [color(rgb(33, 33, 33))])
 );
 ```

**Keyframes**

define animation keyframes;

```reason
let bounce = Css.keyframes([
  (0, [ transform( scale(0.1, 0.1) ),  opacity(0.0) ]),
  (60, [ transform( scale(1.2, 1.2) ),  opacity(1.0) ]),
  (100, [ transform( scale(1.0,1.0) ), opacity(1.0) ])
]);

let styles = style([
  animationName(bounce),
  animationDuration(2000),
  width(px(50)),
  height(px(50)),
  backgroundColor(rgb(255, 0, 0))
]);

// ...
<div className=styles>
  (ReasonReact.stringToElement("bounce!"))
</div>
```


## Development

```sh
npm run start
```

## Where is the documentation?
Its on its way!
until then you can check out [css.rei](./src/Css.rei).

## Thanks
Thanks to [emotion](https://github.com/emotion-js/emotion) which is doing all the heavy lifting.
Thanks to [bs-glamor](https://github.com/poeschko/bs-glamor) which this repo was forked from.
Thanks to [elm-css](https://github.com/rtfeldman/elm-css) for dsl design inspiration.
