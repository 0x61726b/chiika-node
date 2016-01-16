#include <nan.h>
#include "Root/Root.h"

using v8::FunctionTemplate;

// NativeExtension.cc represents the top level of the module.
// C++ constructs that are exposed to javascript are exported here

NAN_MODULE_INIT(InitAll) {
  ChiikaApi::Root r;
	r.Initialize("D:/Arken/C++/ElectronProjects/chiika-node");
}

NODE_MODULE(ChiikaNative, InitAll)
