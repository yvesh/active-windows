# Active Window

Work in progress, not ready for production.

> Currently only supports Linux / Xorg. 

Node C++ N-API module to get information on the currently selected window on Linux, MacOS and Windows.

### Building

```bash
npm install
```

### Usage

```javascript
const activeWindows = require('active-windows');

console.log(activeWindows.getActiveWindowLinux());
```
