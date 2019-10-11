const activeWindows = require('./build/Release/wm');

console.log(activeWindows);
console.log(activeWindows.getActiveWindowLinux());

module.exports = activeWindows;
