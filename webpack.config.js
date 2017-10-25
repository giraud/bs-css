var webpack = require('webpack');
var path = require('path')

module.exports = {
  context: __dirname,
  entry: [
    './lib/js/example/example.js'
  ],
  output: {
    path: path.join(__dirname, 'example'),
    publicPath: '/',
    filename: 'bundle.js'
  }
};