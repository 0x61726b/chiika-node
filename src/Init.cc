#include <nan.h>
#include "ApiWrapper.h"

using v8::FunctionTemplate;

NAN_MODULE_INIT(InitAll)
{
	ChiikaApi::Root* r = new ChiikaApi::Root;
	

	RootWrapper::Init(target,r);
}

NODE_MODULE(ChiikaNative,InitAll)
