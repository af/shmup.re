const path = require('path')
const {BundleAnalyzerPlugin} = require('webpack-bundle-analyzer')
const {ANALYZE_BUNDLE} = process.env


module.exports = {
  entry: {
    main: './lib/es6/src/main.js',
  },
  output: {
    path: path.join(__dirname, 'dist'),
    filename: '[name].js',
  },

  // Note: rollup makes this less informative; remove the rollup loader below to get useful results:
  plugins: ANALYZE_BUNDLE ? [new BundleAnalyzerPlugin()] : [],

  module: {
    rules: [
      {
        test: /main.js$/,
        use: [{ loader: 'webpack-rollup-loader', options: {}, }]
      }
    ]
  }
}
