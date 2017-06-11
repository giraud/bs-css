/*
 A ReasonML bridge to glamor for CSS-in-JS/Reason.

 Usage:

 * Simple styling:

    <div className=(Glamor.css [color "red", border "1px solid black"])> </div>

 * Styling with selectors (@media, :hover, &, etc.):

    <div className=(Glamor.css [color "red", Selector "@media (min-width: 300px)" [color "green"]])> </div>

 * Selectors can be nested:

    <div className=(Glamor.css [color "red", Selector "@media (min-width: 300px)" [color "green", Selector "& .foo" [color "blue"]]])> </div>

 */
type styleObj;

external makeCSS : styleObj => string = "css" [@@bs.module "glamor"];

let addObjToStyles: styleObj => string => styleObj => styleObj = [%bs.raw
  {|
        function (obj, key, value) {
            var newObj = {};
            newObj[key] = value;
            return Object.assign({}, obj, newObj);
        }
    |}
];

let addStringToStyles: styleObj => string => string => styleObj = [%bs.raw
  {|
        function (obj, key, value) {
            var newObj = {};
            newObj[key] = value;
            return Object.assign({}, obj, newObj);
        }
    |}
];

let createEmptyObj: unit => styleObj = [%bs.raw
  {|
            function () {
                return {};
            }
    |}
];

let emptyObj = createEmptyObj ();

let rec addDeclaration obj (decl: CSS.declaration) =>
  switch decl {
  | Nothing => obj
  | Property name value => addStringToStyles obj name value
  | Selector sel decls => addObjToStyles obj sel (declarationsToObj decls)
  }
and declarationsToObj decls => List.fold_left addDeclaration emptyObj decls;

let css decls => makeCSS (declarationsToObj decls);
