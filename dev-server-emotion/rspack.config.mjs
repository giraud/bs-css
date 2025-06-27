import {dirname} from "node:path";
import {fileURLToPath} from "node:url";
import {defineConfig} from "@rspack/cli";
import {rspack} from "@rspack/core";
import {ReactRefreshRspackPlugin} from "@rspack/plugin-react-refresh";

const __dirname = dirname(fileURLToPath(import.meta.url));

export default defineConfig({
    context: __dirname,
    entry:   {
        main: "./lib/js/src/App.js"
    },
    resolve: {
        extensions: [".js"]
    },
    module:  {
        rules: [
            {
                test: /\.js$/,
                use:  [
                    {
                        loader:  "builtin:swc-loader",
                        options: {
                            jsc: {
                                parser:    {
                                    syntax: "typescript",
                                    tsx:    true
                                },
                                transform: {
                                    react: {
                                        runtime:     "automatic",
                                        development: true,
                                        refresh:     true
                                    }
                                }
                            },
                        }
                    }
                ]
            }
        ]
    },
    plugins: [
        new rspack.HtmlRspackPlugin({template: "../www/index.html"}), new ReactRefreshRspackPlugin()
    ]
});
