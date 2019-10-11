#include <napi.h>
#include "linux/windowlinux.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    return windowlinux::Init(env, exports);
}

NODE_API_MODULE(testaddon, InitAll)
