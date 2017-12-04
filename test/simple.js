var screenshot = require('../index')

console.log('--- testing capture')
var result = screenshot.capture(function(err, result){
  console.log('result:', result)
  console.log('--- capture has been run')  
})
