# bs-glamor – [BuckleScript](https://github.com/bucklescript/bucklescript) bindings for [glamor](https://github.com/threepointone/glamor)

The API is still **experimental**. Only the `css` function from glamor is exposed (with its result slightly incorrectly typed as a `string`); no other functions such as `renderStatic` are supported yet.

## Installation

```sh
npm install --save bs-glamor
```

In your `bsconfig.json`, include `"bs-glamor"` in the `bs-dependencies`.

## Usage

The following examples (in [Reason](http://reasonml.github.io) syntax) assume that `Glamor` is included in the namespace:

```reason
open Glamor;
```

* Simple styling:

    ```reason
    css [
        color "red",
        border "1px solid black"
    ]
    ```

* Styling with selectors (`@media`, `:hover`, `&`, etc.):

    ```reason
    css [
        color "red",
        Selector "@media (min-width: 300px)" [
            color "green"
        ]
    ]
    ```

* Selectors can be nested:

    ```reason
    css [
        color "red",
        Selector "@media (min-width: 300px)" [
            color "green",
            Selector "& .foo" [
                color "blue"
            ]
        ]
    ]
    ```

You can isolate inclusion of the `Glamor` namespace in the following way:

```reason
Glamor.(css [color "red"])
```

The result of the `css` function can be assigned to a class name, e.g. in JSX:

```reason
<div className=(css [color "red"]) />
```
### Merging css rules

You can merge css rules using `merge`


```
let text_primary = css [ color "indigo" ];
let small = css [fontSize "10px"];


<p  className=(merge [text_primary, small])> ...
```

glamor will make sure that rules are merged in the correct order, managing nesting and precedence for you.


### Global css
 You can defined global css rules with `global`

 ```
 Glamor.(global "body" [margin "0px"]);

 Glamor.(global "h1, h2, h3" [color "palegoldenrod"]);

 ```

## Keyframes

define animation keyframes;

```
let bounce = Glamor.keyframes [
  ("0%": [transform "scale(0.1)",  opacity "0"]),
  ("60%": [transform "scale(1.2)",  opacity "1"]),
  ("100%": [transform "scale(1)"])
];
let styles = css [
    animationName bounce,
    animationDuration "2s",
    width "50px",
    height "50px",
    backgroundColor "red"
];

// ...
<div className=styles>
  bounce!
</div>
```

## Example

See [reason-react-tictactoe](https://github.com/poeschko/reason-react-tictactoe) for a live example.

## Development

```sh
npm run start
```

### Tests

There are some simplistic tests using [bs-jest](https://github.com/BuckleTypes/bs-jest).

```sh
npm run test
```

## Thanks

Thanks to [reason-react-example](https://github.com/chenglou/reason-react-example), [reason-react](https://github.com/reasonml/reason-react), and [bs-jest](https://github.com/BuckleTypes/bs-jest) for inspiration how to create a Reason library, and of course, thanks to [glamor](https://github.com/threepointone/glamor).
