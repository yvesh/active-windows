/**
 * Executes getActiveWindow every second and prints it the console
 * 
 * Run with `node sample.js`
 */
const activeWindows = require('./index');

const interval = setInterval(() => {
  let result = activeWindows.getActiveWindow();

  console.log(result);

  // Error returned from cpp is added to the object
  if (result.error) {
      console.log('error', result);
      clearInterval(interval);
  }
}, 1000);
