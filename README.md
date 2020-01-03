# Active Window

Node C++ N-API module to get information on the currently selected window and the user idle time on Linux, MacOS and Windows.

> Currently only supports Windows and Linux / Xorg. 

Work in progress. Not on every platform all information are supported.

### Building / Installation

```bash
npm install
```

### Usage

```javascript
const activeWindows = require('active-windows');

console.log(activeWindows.getActiveWindow());
```

See `sample.js` for more information.

### Return-Value

```javascript
{
  // Operating system (linux | windows | macos)
  os: 'linux',
  // Process name (chromium.exe on windows)
  windowClass: 'chromium',
  // Blog | bytee.net
  windowName: 'Blog | bytee.net - Chromium',
  // Desktop on which the window is displayed (Linux only)
  windowDesktop: '2',
  // Window Type (Linux only)
  windowType: '340',
  // Process ID of the window
  windowPid: '34218',
  // Idle Time in seconds
  idleTime: '42',
}
```
