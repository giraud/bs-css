## [Unreleased]

- BREAKING CHANGE - use an array for areas type
- BREAKING CHANGE - rename Geomety to Geometry (missing r)


- Make height and width respect all the interface by [@davesnx](https://github.com/davesnx) - [#262](https://github.com/reasonml-labs/bs-css/pull/262)
- Add missing values by [@davesnx](https://github.com/davesnx) - [#257](https://github.com/reasonml-labs/bs-css/pull/257)
- Update README example to use CssJs and Rescript syntax by [hugihlynsson](https://github.com/hugihlynsson)

## [15.3.1] - 2022-10-30

- Convert bs-css files to Rescript - [#260](https://github.com/giraud/bs-css/issues/260)

bs-css-dom@3.3.1, bs-css-emotion@4.3.1, bs-css-fela@2.3.1

## [15.3.0] - 2022-05-18

- Add `touchAction` by [@RuslanGrigoryev](https://github.com/RuslanGrigoryev) - [#256](https://github.com/reasonml-labs/bs-css/pull/256)

bs-css-dom@3.3.0, bs-css-emotion@4.3.0, bs-css-fela@2.3.0

## [15.2.0] - 2022-03-14

- Update `width` property with `maxContent` and `minContent` by [@RuslanGrigoryev](https://github.com/RuslanGrigoryev) - [#254](https://github.com/reasonml-labs/bs-css/pull/254)
- Add `isolation` property by [@lucasweng](https://github.com/lucasweng) - [#253](https://github.com/reasonml-labs/bs-css/pull/253)
- Removed dependency to bs-jest

bs-css-dom@3.2.0, bs-css-emotion@4.2.0, bs-css-fela@2.2.0

## [15.1.1] - 2022-03-02

- Add conic-gradient by [@happylinks](https://github.com/happylinks) - [#252](https://github.com/reasonml-labs/bs-css/pull/252)

bs-css-dom@3.1.1, bs-css-emotion@4.1.1, bs-css-fela@2.1.1

## [15.1.0] - 2022-01-20

- Add new types (overscrollBehavior, overflowAnchor, maskPosition, maskImage) on behalf of [Ahrefs](https://ahrefs.com/) - [#251](https://github.com/reasonml-labs/bs-css/pull/251)

bs-css-dom@3.1.0, bs-css-emotion@4.1.0, bs-css-fela@2.1.0

## [15.0.2] - 2021-12-06

- Add scrollBehavior, columnWidth and caretColor by [@Amirmoh10](https://github.com/Amirmoh10) - [#249](https://github.com/reasonml-labs/bs-css/pull/249)
- Add gap (shortcut to gridGap), and gap2

bs-css-dom@3.0.2, bs-css-emotion@4.0.2, bs-css-fela@2.0.2

## [15.0.1] - 2021-08-26

- BREAKING CHANGE - use rescript and @rescript/react
- BREAKING CHANGE - for better consistency in CssJs, use array instead of list in gradient definition
- BREAKING CHANGE - for better consistency in CssJs, uncurry selector and media functions - [#244](https://github.com/giraud/bs-css/issues/244) 

- Fix global injection in legacy mode - [#238](https://github.com/giraud/bs-css/issues/238) 
- Add borderRadius4 by [@davesnx](https://github.com/davesnx) - [#247](https://github.com/reasonml-labs/bs-css/pull/247)
- Add `start in TextAlign by [@davesnx](https://github.com/davesnx) - [#246](https://github.com/reasonml-labs/bs-css/pull/246)

bs-css-dom@3.0.1, bs-css-emotion@4.0.1, bs-css-fela@2.0.1

## [14.0.2] - 2021-05-03

- Add rowGap by [@jeong-sik](https://github.com/jeong-sik) - [#240](https://github.com/reasonml-labs/bs-css/pull/240)  
   
bs-css-dom@2.5.2, bs-css-fela@1.0.2            

### bs-css-emotion@3.0.0

- BREAKING CHANGE bs-css-emotion: update to emotion v11
  by [@TomiS](https://github.com/TomiS) - [#229](https://github.com/reasonml-labs/bs-css/pull/229)
  
## [14.0.1] - 2021-03-30

- Fix test helper dependency - [#237](https://github.com/giraud/bs-css/issues/237) 

bs-css-dom@2.5.1, bs-css-emotion@2.5.1, bs-css-fela@1.0.1            

## [14.0.0] - 2021-03-29

- BREAKING CHANGE bs-css: updated the Css_Core API to accept renderer. it should have no impact on existing implementations.
- Added bs-css-fela with a dependency to the [fela](https://github.com/robinweser/fela) library

bs-css-dom@2.5.0, bs-css-emotion@2.5.0, bs-css-fela@1.0.0
            
## [13.4.1] - 2021-03-19

- Move react dependency out of bs-css-emotion
- Use peer dependencies in bs-css-dom
- Fix broken link to rei (doc) by [@abenoit](https://github.com/abenoit) - [#234](https://github.com/reasonml-labs/bs-css/pull/234)  
- Add support for focus-visible pseudo-class by [@TomiS](https://github.com/TomiS) - [#233](https://github.com/reasonml-labs/bs-css/pull/233)

bs-css-dom@2.4.1, bs-css-emotion@2.4.1

## [13.4.0] - 2021-02-20

- Fix `strokeDasharray` property by [@lucasweng](https://github.com/lucasweng) - [#232](https://github.com/reasonml-labs/bs-css/pull/232)
- Fix `backdropFilter` property by [@lucasweng](https://github.com/lucasweng) - [#231](https://github.com/reasonml-labs/bs-css/pull/231)
- Fix color - [#230](https://github.com/giraud/bs-css/issues/230)

bs-css-dom@2.4.0, bs-css-emotion@2.4.0

## [13.3.0] - 2021-01-26

- Add `stroke-dasharray` for SVG by [@pzshine](https://github.com/pzshine)

bs-css-dom@2.3.0, bs-css-emotion@2.3.0

## [13.2.0] - 2020-11-20

- Add `justify-items` by [@rusty-key](https://github.com/rusty-key) - [#219](https://github.com/reasonml-labs/bs-css/pull/219)
- Support `auto` keyword for positional rules by [@rusty-key](https://github.com/rusty-key) - [#215](https://github.com/reasonml-labs/bs-css/pull/215)
- Support `transform: none` by [@rusty-key](https://github.com/rusty-key) - [#216](https://github.com/reasonml-labs/bs-css/pull/216)
- Allow var where color can be applied by [@rusty-key](https://github.com/rusty-key) - [#214](https://github.com/reasonml-labs/bs-css/pull/214)
- Support `auto` in `trackLength` by [@rusty-key](https://github.com/rusty-key) - [#213](https://github.com/reasonml-labs/bs-css/pull/213)

bs-css-dom@2.2.0, bs-css-emotion@2.2.0

## [13.1.0] - 2020-10-09

### Added

- New CssJs module that uses arrays instead of list for styles, more friendly to js and Rescript.
This is not a breaking change, to use that new code you need to import `CssJs` instead of `Css`. 

## [13.0.0] - 2020-08-26

### Added

- Add column-gap by [@lucasweng](https://github.com/lucasweng) - [#203](https://github.com/giraud/bs-css/issues/203)
- Introduce var (usage only) - [#152](https://github.com/giraud/bs-css/issues/152)

### Breaking change

- Update rgba/hsl/hsla signatures - [#194](https://github.com/giraud/bs-css/issues/194)
- Update SVG fill property - [#193](https://github.com/giraud/bs-css/issues/193)
- Delete the empty rule, it was just a shortcut to `[]` and was conflicting with the `empty` selector 

bs-css-dom@2.0.0, bs-css-emotion@2.0.0

## [12.2.0] - 2020-04-14

- Add missing "stretch" property for alignSelf by [@bloodyowl](https://github.com/bloodyowl) - [#192](https://github.com/giraud/bs-css/pull/192)
- Udpate incorrect link in README by [@mfakhrusy](https://github.com/mfakhrusy) - [#191](https://github.com/giraud/bs-css/pull/191)

bs-css-dom@1.2.0, bs-css-emotion@1.2.0

## [12.1.0] - 2020-03-20

- Add `backdropFilter` by [@Arnarkari93](https://github.com/Arnarkari93) - [#186](https://github.com/giraud/bs-css/pull/186)
- Add aliases to `GridTemplateAreas` and `GridArea` - [#185](https://github.com/giraud/bs-css/issues/185)

## [12.0.1] - 2020-03-04

This release introduce 2 new packages: `bs-css-emotion` and `bs-css-dom`.
You need to replace `bs-css` with `bs-css-emotion` (or `bs-css-dom`) in your `package.json`, and you need to add either `bs-css-emotion` or `bs-css-dom` in your `bsconfig.json`.

- Add cursor aliases - [#179](https://github.com/giraud/bs-css/issues/179)
- Add objectPosition by [@damianfral](https://github.com/damianfral) - [#177](https://github.com/giraud/bs-css/pull/177)
- Add support for fontDisplay in fontFace by [@bloodyowl](https://github.com/bloodyowl) - [#176](https://github.com/giraud/bs-css/pull/176)
- Fix typo string of `easeIn by [@zalcode](https://github.com/zalcode) - [#175](https://github.com/giraud/bs-css/pull/175)
- github repository moved to reasonml-labs organisation

### Breaking change

- Redesign content rule to support all possible values by  [@erykpiast](https://github.com/erykpiast) - [#180](https://github.com/giraud/bs-css/pull/180)
- FontFamily accepts cascading and predefined generic font names by [@erykpiast](https://github.com/erykpiast) - [#171](https://github.com/giraud/bs-css/pull/171)
 
  if you have code like this:
  ```fontFamily("Helvetica, sans-serif")```
  you need to convert it to:
  ```fontFamilies([`custom("Helvetica"), `sansSerif])```

### Changed

- Add upper bound to union types in Css.rei by [@tomiS](https://github.com/TomiS) - [#172](https://github.com/giraud/bs-css/issues/172)

## [11.0.0] - 2019-11-12

Major release because of the breaking change in background-position definition,
and some elements removed.

### Changed

- Extend rule to use gridLength type by [@lukiwolski](https://github.com/lukiwolski) - [#168](https://github.com/giraud/bs-css/pull/168)
- background-position definition by [@lucasweng](https://github.com/lucasweng) - [#167](https://github.com/giraud/bs-css/issues/167)
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

- Css.rule is now an abstract type [#153](https://github.com/giraud/bs-css/issues/153)
- Update shadow definition [#148](https://github.com/giraud/bs-css/issues/148)

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

- Support for for `object-fit` property by [@kuy](https://github.com/kuy) - [#125](https://github.com/giraud/bs-css/pull/125)
- Add `fit-content` option for width property by [@mwarni](https://github.com/mwarni) - [#149](https://github.com/giraud/bs-css/pull/149)
- Add support for `grid-template-areas` and `grid-area` by [@drew887](https://github.com/drew887) - [#156](https://github.com/giraud/bs-css/issues/156)

### Fixed

- BoxShadow: none doesn't work - [#148](https://github.com/giraud/bs-css/issues/148)
- !important doesn't apply to boxShadow - [#147](https://github.com/giraud/bs-css/issues/147)

### Changed

- Move types to Css.Types, updated some css properties
- Use yarn instead of npm

## 9.0.1 - 2019-07-01

This is a major release: bs-css now depend on emotion 10.x instead of 9.x (see [#114](https://github.com/giraud/bs-css/pull/114)).

- :bug: [#139](https://github.com/giraud/bs-css/issues/139) - Units for hsl(a)
- :bug: [#138](https://github.com/giraud/bs-css/issues/138) - (top, bottom, left, right) properties should also belong to the 'cascading' type
- :bug: [#133](https://github.com/giraud/bs-css/issues/133) - Support pixel units for gradient color stops
- :rocket: [#131](https://github.com/giraud/bs-css/issues/131) - Support for "direction" property
- :bug: [#109](https://github.com/giraud/bs-css/issues/109) - flexShrink and flex should accept a float instead of a int

contributors: [@simonkberg](https://github.com/simonkberg), [@JakubMarkiewicz](https://github.com/JakubMarkiewicz), [@remitbri](https://github.com/remitbri), [@lucasweng](https://github.com/lucasweng) 

## 8.0.4 - 2019-04-04

- :rocket: [#125](https://github.com/giraud/bs-css/pull/125) - Add textShadows
- :house: webpack is replaced by parcel, zero config local server

contributors: [@Freddy03h](https://github.com/Freddy03h)

## 8.0.3 - 2019-03-20

- :rocket: [#118](https://github.com/giraud/bs-css/issues/118) - Minmax should allow fr
- :rocket: Add a toJson function to convert a list of rules to a json object

contributors: [@JakubMarkiewicz](https://github.com/JakubMarkiewicz) 

## 8.0.2 - 2019-02-25

- :rocket: [#119](https://github.com/giraud/bs-css/issues/119) - Missing resize attribute
- :rocket: [#117](https://github.com/giraud/bs-css/issues/117) - Add `spaceEvenly` for justifyContent and alignContent
- :rocket: [#113](https://github.com/giraud/bs-css/pull/113) - Minmax in grid implementation

contributors: [@JakubMarkiewicz](https://github.com/JakubMarkiewicz), [@lucasweng](https://github.com/lucasweng), [@wegry](https://github.com/wegry) 

## 8.0.1 - 2019-01-31

- :bug: [#108](https://github.com/giraud/bs-css/issues/108) - Wrong value for minWidth/maxWidth
- :rocket: [#111](https://github.com/giraud/bs-css/pull/111) - Fill all allowed display values

contributors: [@sean-clayton](https://github.com/sean-clayton), [@c19](https://github.com/c19)

## 8.0.0 - 2018-12-18

- :rocket: [#76](https://github.com/giraud/bs-css/issues/76) - Add support for commonly used name for font weight
- :bug: [#86](https://github.com/giraud/bs-css/issues/86) - Losing styles when merging nested selectors
- :bug: [#105](https://github.com/giraud/bs-css/issues/105) - flexGrow should accept a float instead of a int
- :house: [#95](https://github.com/giraud/bs-css/issues/95) - Remove unnecessary reverse of styles before passing to JS obj
- :house: [#91](https://github.com/giraud/bs-css/issues/91) - Swapped glamor runtime to emotion runtime

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

[Unreleased]: https://github.com/giraud/bs-css/compare/15.3.1...HEAD
[15.3.1]: https://github.com/giraud/bs-css/compare/15.3.0...15.3.1
[15.3.0]: https://github.com/giraud/bs-css/compare/15.2.0...15.3.0
[15.2.0]: https://github.com/giraud/bs-css/compare/15.1.1...15.2.0
[15.1.1]: https://github.com/giraud/bs-css/compare/15.1.0...15.1.1
[15.1.0]: https://github.com/giraud/bs-css/compare/15.0.2...15.1.0
[15.0.2]: https://github.com/giraud/bs-css/compare/15.0.1...15.0.2
[15.0.1]: https://github.com/giraud/bs-css/compare/14.0.2...15.0.1
[14.0.2]: https://github.com/giraud/bs-css/compare/14.0.1...14.0.2
[14.0.1]: https://github.com/giraud/bs-css/compare/14.0.0...14.0.1
[14.0.0]: https://github.com/giraud/bs-css/compare/13.4.1...14.0.0
[13.4.1]: https://github.com/giraud/bs-css/compare/13.4.0...13.4.1
[13.4.0]: https://github.com/giraud/bs-css/compare/13.3.0...13.4.0
[13.3.0]: https://github.com/giraud/bs-css/compare/13.2.0...13.3.0
[13.2.0]: https://github.com/giraud/bs-css/compare/13.1.0...13.2.0
[13.1.0]: https://github.com/giraud/bs-css/compare/13.0.0...13.1.0
[13.0.0]: https://github.com/giraud/bs-css/compare/v12.1.0...13.0.0
[12.2.0]: https://github.com/giraud/bs-css/compare/v12.1.0...v12.2.0
[12.1.0]: https://github.com/giraud/bs-css/compare/v12.0.1...v12.1.0
[12.0.1]: https://github.com/giraud/bs-css/compare/v11.0.0...v12.0.1
[11.0.0]: https://github.com/giraud/bs-css/compare/v10.0.1...v11.0.0
[10.0.1]: https://github.com/giraud/bs-css/compare/v10.0.0...v10.0.1
[10.0.0]: https://github.com/giraud/bs-css/compare/v9.0.1...v10.0.0
