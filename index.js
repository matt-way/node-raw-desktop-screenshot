var screenshot = require('./build/Release/desktop-screenshot.node')

exports.capture = function(cb) {
  screenshot.capture(function(err, res){
    // replace buffer with clamped array view
    res.image = new Uint8ClampedArray(res.image)
    return cb(null, res)
  })
}