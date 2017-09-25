var screenshot = require('./build/Release/desktop-screenshot.node')

exports.capture = function() {
  var res = screenshot.capture()
  // replace buffer with clamped array view
  res.image = new Uint8ClampedArray(res.image)
  return res
}