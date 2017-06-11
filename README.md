# glamor-reason

[glamor](https://github.com/threepointone/glamor) bindings for [Reason](https://facebook.github.io/reason/). **Highly experimental**.

## Installation

    npm install glamor-reason

## Usage

The following examples assume that `GlamorRe` is included in the namespace:

    open GlamorRe;    

* Simple styling:

        css [
            color "red",
            border "1px solid black"
        ]

* Styling with selectors (`@media`, `:hover`, `&`, etc.):

        css [
            color "red",
            Selector "@media (min-width: 300px)" [
                color "green"
            ]
        ]

* Selectors can be nested:

        css [
            color "red",
            Selector "@media (min-width: 300px)" [
                color "green",
                Selector "& .foo" [
                    color "blue"
                ]
            ]
        ]

You can isolate inclusion of the `GlamorRe` namespace in the following way:

    GlamorRe.(css [color "red"])
    
The result of the `css` function can be assigned to a class name, e.g. in JSX:

    <div className=(css [color "red"]) />
    
## Development

    npm run start    
    
### Tests

There are some simplistic tests using [bs-jest](https://github.com/BuckleTypes/bs-jest).

    npm run test
