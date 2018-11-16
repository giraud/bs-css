# bs-css

statically typed DSL for writing css in reason.

:boom: NEXT VERSION WILL BE A MAJOR VERSION (8.0) AND WILL SWAP GLAMOR TO EMOTION, but it's not yet released :boom:

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

## Merging styles

You should avoid trying to merge styles in the same list of rules or by concatinating lists. A list of rules is converted into a JS object before being passed to Emotion where every property becomes a key in the object. This means you lose any earlier rule if you have another rule with the same property later in the list. This is especially noticable [when writing sub-selectors and media queries](https://github.com/SentiaAnalytics/bs-css/issues/86)

`bs-css` offers two options for merging styles:

1. `mergeStyles` merges styles by name. Uses [Emotion’s `cx` method](https://emotion.sh/docs/cx).
   Rules will overrride earlier rules in the list.

```reason
let mergedStyles =
  Css.(
    mergeStyles([
      style([padding(px(0))]),
      style([fontSize(px(1))]),
      style([padding(px(20)), fontSize(px(24)), color(blue)]),
      style([media("(max-width: 768px)", [padding(px(10))])]),
      style([
        media("(max-width: 768px)", [fontSize(px(16)), color(red)]),
      ]),
    ])
  );
```

2. `styleList` takes a list of rule lists (`list(list(rule))`) and passes an array of JS objects to [Emotion’s primary `css` method](https://emotion.sh/docs/object-styles#arrays)
   effectively combining the rules. Rules will overrride earlier rules in the list.

```reason
let combinedStyles =
  Css.(
    styleList([
      [padding(px(0)), fontSize(px(1))],
      [padding(px(20)), fontSize(px(24)), color(blue)],
      [media("(max-width: 768px)", [padding(px(10))])],
      [media("(max-width: 768px)", [fontSize(px(16)), color(red)])],
    ])
  );
```

Both these methods should produce the same results.

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
