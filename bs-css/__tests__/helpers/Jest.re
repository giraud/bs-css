type asyncDone('a) = 'a => unit;
type expectation('a);

[@bs.val]
external describe: (string, [@bs.uncurry] (unit => unit)) => unit = "describe";
[@bs.val]
external test: (string, [@bs.uncurry] (unit => unit)) => unit = "test";
[@bs.val]
external testAsync: (string, [@bs.uncurry] (asyncDone('a) => unit)) => unit =
  "it";

[@bs.val] external expect: 'a => expectation('a) = "expect";
[@bs.send] external toEqual: (expectation('a), 'a) => unit = "toEqual";
[@bs.send] external toBe: (expectation('a), 'a) => unit = "toBe";
