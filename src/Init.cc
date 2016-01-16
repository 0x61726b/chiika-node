#include <nan.h>
#include "Root/Root.h"
#include "ApiWrapper.h"

using v8::FunctionTemplate;

// NativeExtension.cc represents the top level of the module.
// C++ constructs that are exposed to javascript are exported here

NAN_MODULE_INIT(InitAll) {
  ChiikaApi::Root r;
	r.Initialize("D:/Arken/C++/ElectronProjects/chiika-node");

	RootWrapper::Init(target);
}

NODE_MODULE(ChiikaNative, InitAll)
