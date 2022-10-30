type asyncDone<'a> = 'a => unit
type expectation<'a>

@val
external describe: (string, @uncurry (unit => unit)) => unit = "describe"
@val
external test: (string, @uncurry (unit => unit)) => unit = "test"
@val
external testAsync: (string, @uncurry (asyncDone<'a> => unit)) => unit = "it"

@val external expect: 'a => expectation<'a> = "expect"
@send external toEqual: (expectation<'a>, 'a) => unit = "toEqual"
@send external toBe: (expectation<'a>, 'a) => unit = "toBe"
