# bs-css

statically typed DSL for writing css in reason.


Bs-css is a statically typed interface to [Glamor] (https://github.com/threepointone/glamor)


## Installation

```sh
npm install --save bs-css
```

In your `bsconfig.json`, include `"bs-css"` in the `bs-dependencies`.

## Usage


**Merging css rules**

You can merge css rules using `merge`


```
let text_primary = style [ color white ];
let small = style [fontSize (px 10)];


<p  className=(merge [text_primary, small])> ...
```

bs-css will make sure that rules are merged in the correct order, managing nesting and precedence for you.


**Global css**

 You can defined global css rules with `global`

 ```
 Css.(global "body" [margin (px 0)]);

 Css.(global "h1, h2, h3" [color (rgb 33 33 33)]);

 ```

**Keyframes**

define animation keyframes;

```
let bounce = Css.keyframes [
  ("0%": [transform (scale 0.1 0.1),  opacity 0.0]),
  ("60%": [transform (scale 1.2 1.2),  opacity 1.0]),
  ("100%": [transform (scale 1.0 1.0), opacity 1.0])
];

let styles = css [
    animationName bounce,
    animationDuration 2000,
    width (px 50),
    height (px 50),
    backgroundColor (rgb 255 0 0)
];

// ...
<div className=styles>
  bounce!
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
Thanks to [glamor](https://github.com/threepointone/glamor) which is doing all the heavi lifting.
Thanks to [bs-glamor](https://github.com/poeschko/bs-glamor) which this repo was forked from.
Thanks to [elm-css](https://github.com/rtfeldman/elm-css) for dsl design inspiration.
