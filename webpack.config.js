const path = require('path')
const {BundleAnalyzerPlugin} = require('webpack-bundle-analyzer')
const {ANALYZE_BUNDLE} = process.env

module.exports = {
  entry: {
    main: './lib/js/src/main.js',
  },
  output: {
    path: path.join(__dirname, 'lib/bundle'),
    filename: '[name].js',
  },
  plugins: ANALYZE_BUNDLE ? [new BundleAnalyzerPlugin()] : []
}
