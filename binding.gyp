{
  "targets": [
    {
      "target_name": "wm",
      "sources": [ "cppsrc/main.cpp", "cppsrc/linux/windowlinux.cpp" ],
      "cflags": ["-fno-exceptions", "-std=c++11", "-lX11"],
      "cflags_cc": ["-fno-exceptions -lX11"],
      "libraries": [
        "/usr/lib64/libX11.so",
        "/usr/lib64/libxcb.so",
      ],
      'include_dirs': [
           "<!@(node -p \"require('node-addon-api').include\")"
       ],
      'dependencies': [
         "<!(node -p \"require('node-addon-api').gyp\")"
       ],
       'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    },
  ]
}
