const activeWindows = require('./build/Release/wm');

console.log(activeWindows.getActiveWindow());

module.exports = activeWindows;
