## [Unreleased]

- Add objectPosition by [@damianfral](https://github.com/damianfral) - [#177](https://github.com/SentiaAnalytics/bs-css/pull/177)
- Add support for fontDisplay in fontFace by [@bloodyowl](https://github.com/bloodyowl) - [#176](https://github.com/SentiaAnalytics/bs-css/pull/176)
- Fix typo string of `easeIn by [@zalcode](https://github.com/zalcode) - [#175](https://github.com/SentiaAnalytics/bs-css/pull/175)
- github repository moved to reasonml-labs organisation

### Breaking change

- FontFamily accepts cascading and predefined generic font names by [@erykpiast](https://github.com/erykpiast) - [#171](https://github.com/SentiaAnalytics/bs-css/pull/171)
 
  if you have code like this:
  ```fontFamily("Helvetica, sans-serif")```
  you need to convert it to:
  ```fontFamilies([`custom("Helvetica"), `sansSerif])```

### Changed

- Add upper bound to union types in Css.rei by [@tomiS](https://github.com/TomiS) - [#172](https://github.com/SentiaAnalytics/bs-css/issues/172)

## [11.0.0] - 2019-11-12

Major release because of the breaking change in background-position definition,
and some elements removed.

### Changed

- Extend rule to use gridLength type by [@lukiwolski](https://github.com/lukiwolski) - [#168](https://github.com/SentiaAnalytics/bs-css/pull/168)
- background-position definition by [@lucasweng](https://github.com/lucasweng) - [#167](https://github.com/SentiaAnalytics/bs-css/issues/167)
- Rename Css_Types to Css_AtomicTypes

### Removed

- noContent selector, duplicate of empty
- type aliases
 
## [10.0.1] - 2019-09-23

### Added

- textDecorationLine

### Changed

- Pseudo classes selectors have been updated and documented
- Update properties : backgroundAttachment, backgroundClip, backgroundOrigin, backgroundRepeat,
  textOverflow, textDecorationLine, textDecorationStyle, width, wordWrap

## [10.0.0] - 2019-09-04

Major release because of the breaking change in shadows definition.

### Breaking change

- Css.rule is now an abstract type [#153](https://github.com/SentiaAnalytics/bs-css/issues/153)
- Update shadow definition [#148](https://github.com/SentiaAnalytics/bs-css/issues/148)

boxShadow has been changed to be a rule to allow for `none`, `important` and all other rule related functions.

It means that the shadow properties must be updated to the following patterns:
```reason
// before:
boxShadow(~x=px(1), ~y=px(2));
boxShadows([boxShadow(yellow), boxShadow(red)]);
textShadow(~y=px(3), ~blur=px(2), black);
textShadows([textShadow(~y=px(3), ~blur=px(2), black), textShadow(~x=px(3), green)]);

// after:
boxShadow(Shadow.box(~x=px(1), ~y=px(2)));
boxShadows([Shadow.box(yellow), Shadow.box(red)]);
textShadow(Shadow.text(~y=px(3), ~blur=px(2), black));
textShadows([Shadow.text(~y=px(3), ~blur=px(2), black), Shadow.text(~x=px(3), green)]);
```

### Added

- Support for for `object-fit` property by [@kuy](https://github.com/kuy) - [#125](https://github.com/SentiaAnalytics/bs-css/pull/125)
- Add `fit-content` option for width property by [@mwarni](https://github.com/mwarni) - [#149](https://github.com/SentiaAnalytics/bs-css/pull/149)
- Add support for `grid-template-areas` and `grid-area` by [@drew887](https://github.com/drew887) - [#156](https://github.com/SentiaAnalytics/bs-css/issues/156)

### Fixed

- BoxShadow: none doesn't work - [#148](https://github.com/SentiaAnalytics/bs-css/issues/148)
- !important doesn't apply to boxShadow - [#147](https://github.com/SentiaAnalytics/bs-css/issues/147)

### Changed

- Move types to Css.Types, updated some css properties
- Use yarn instead of npm

## 9.0.1 - 2019-07-01

This is a major release: bs-css now depend on emotion 10.x instead of 9.x (see [#114](https://github.com/SentiaAnalytics/bs-css/pull/114)).

- :bug: [#139](https://github.com/SentiaAnalytics/bs-css/issues/139) - Units for hsl(a)
- :bug: [#138](https://github.com/SentiaAnalytics/bs-css/issues/138) - (top, bottom, left, right) properties should also belong to the 'cascading' type
- :bug: [#133](https://github.com/SentiaAnalytics/bs-css/issues/133) - Support pixel units for gradient color stops
- :rocket: [#131](https://github.com/SentiaAnalytics/bs-css/issues/131) - Support for "direction" property
- :bug: [#109](https://github.com/SentiaAnalytics/bs-css/issues/109) - flexShrink and flex should accept a float instead of a int

contributors: [@simonkberg](https://github.com/simonkberg), [@JakubMarkiewicz](https://github.com/JakubMarkiewicz), [@remitbri](https://github.com/remitbri), [@lucasweng](https://github.com/lucasweng) 

## 8.0.4 - 2019-04-04

- :rocket: [#125](https://github.com/SentiaAnalytics/bs-css/pull/125) - Add textShadows
- :house: webpack is replaced by parcel, zero config local server

contributors: [@Freddy03h](https://github.com/Freddy03h)

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

[Unreleased]: https://github.com/SentiaAnalytics/bs-css/compare/v11.0.0...HEAD
[11.0.0]: https://github.com/SentiaAnalytics/bs-css/compare/v10.0.1...v11.0.0
[10.0.1]: https://github.com/SentiaAnalytics/bs-css/compare/v10.0.0...v10.0.1
[10.0.0]: https://github.com/SentiaAnalytics/bs-css/compare/v9.0.1...v10.0.0
