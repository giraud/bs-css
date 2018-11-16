## 8.0.0 - 2018-11-??

- :rocket: [#76](https://github.com/SentiaAnalytics/bs-css/issues/76) - Add support for commonly used name for font weight
- :bug: [#86](https://github.com/SentiaAnalytics/bs-css/issues/86) - Losing styles when merging nested selectors
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

- fontWeight number must now use the `num constructor: from  ```fontWeight(300)``` to ```fontWeight(num(300))```
- todo merge ...
