# bs-glamor – [BuckleScript](https://github.com/bloomberg/bucklescript) bindings for [glamor](https://github.com/threepointone/glamor)

**Highly experimental!**

## Installation

```sh
npm install --save bs-glamor
```

In your `bsconfig.js`, include `"bs-glamor"` in the `bs-dependencies`.

## Usage

The following examples (in [Reason](https://facebook.github.io/reason) syntax) assume that `Glamor` is included in the namespace:

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
