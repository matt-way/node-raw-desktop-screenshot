# node-raw-desktop-screenshot
Node/Electron addon for doing native screen capturing

Every screen capture library out there has strange APIs, or issues that make them unusable in some cases. For example the chromium `getUserMedia` has hard coded enforcement of the mouse cursor. Other desktop screenshot modules simply write an image file locally using third party tools. This library is intended to be a native node module for capturing simple full desktop screenshots cross platform, and return the actual pixel data to work with.

Currently only osx, and extremely basic.
