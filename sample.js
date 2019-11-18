const activeWindows = require('./build/Release/wm');

setInterval(() => {
    let result = activeWindows.getActiveWindow();

    if (result.error) {
        console.log(result);
    }
},1000);

module.exports = activeWindows;
