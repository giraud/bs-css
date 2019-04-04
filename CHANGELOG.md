## 8.0.3 - 2019-03-20

- :rocket: [#118](https://github.com/SentiaAnalytics/bs-css/issues/118) - Minmax should allow fr
- :rocket: Add a toJson function to convert a list of rules to a json object

contributors: [@JakubMarkiewicz](https://github.com/JakubMarkiewicz) 

## 8.0.2 - 2019-02-25

- :rocket: [#119](https://github.com/SentiaAnalytics/bs-css/issues/119) - Missing resize attribute
- :rocket: [#117](https://github.com/SentiaAnalytics/bs-css/issues/117) - Add `spaceEvenly` for justifyContent and alignContent
- :rocket: [#113](https://github.com/SentiaAnalytics/bs-css/pull/113) - Minmax in grid implementation

contributors: [@JakubMarkiewicz](https://github.com/JakubMarkiewicz), [@lucasweng](https://github.com/lucasweng), [@wegry](https://github.com/wegry) 

## 8.0.1 - 2019-01-31

- :bug: [#108](https://github.com/SentiaAnalytics/bs-css/issues/108) - Wrong value for minWidth/maxWidth
- :rocket: [#111](https://github.com/SentiaAnalytics/bs-css/pull/111) - Fill all allowed display values

contributors: [@sean-clayton](https://github.com/sean-clayton), [@c19](https://github.com/c19)

## 8.0.0 - 2018-12-18

- :rocket: [#76](https://github.com/SentiaAnalytics/bs-css/issues/76) - Add support for commonly used name for font weight
- :bug: [#86](https://github.com/SentiaAnalytics/bs-css/issues/86) - Losing styles when merging nested selectors
- :bug: [#105](https://github.com/SentiaAnalytics/bs-css/issues/105) - flexGrow should accept a float instead of a int
- :house: [#95](https://github.com/SentiaAnalytics/bs-css/issues/95) - Remove unnecessary reverse of styles before passing to JS obj
- :house: [#91](https://github.com/SentiaAnalytics/bs-css/issues/91) - Swapped glamor runtime to emotion runtime

#### Breaking changes

This version of bs-css is using a new runtime library that replaces glamor.
 
This decision is driven by the following points:

- the author of glamor is no more maintaining its project, the last commit happened more than one year ago,
- emotion is the recommended alternative because it mostly matches glamor's API
- better grid support : glamor uses a lot of the old -ms-grid and -webkit-grid prefixes (with IE11 support)
- Merging styles with sub selectors work as expected and fix a bug bs-css had

Given that it is a major version, we also changed some functions in the API, especially regarding merging.

#### Migration

- `fontWeight` number must now use the `num` constructor: you must change `fontWeight(300)` to `fontWeight(num(300))`.
The benefit is that you can transform your absolute numbers to font names, see https://developer.mozilla.org/en-US/docs/Web/CSS/font-weight#Common_weight_name_mapping. 
- `merge` was really a `concat` function and could lead to problems as seen in #86. This is why it has been changed to use 
the internal library (emotion) and its signature is now : `list(string) => string`. If you want to keep the same functionality
than before, you can use `List.concat` instead or `@` operator.
- if you are mixin reason/js, you need to change your dependency and replace `glamor` with `emotion`
- `flexGrow` accepts a float instead of an int, add a `.` to your int value (for ex, convert `1` to `1.`)

#### Contributors

Big thanks to [@baldurh](https://github.com/baldurh) and [@wegry](https://github.com/wegry) for their work on emotion.
