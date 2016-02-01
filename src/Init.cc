#include <nan.h>
#include "ApiWrapper.h"

using v8::FunctionTemplate;
using v8::FunctionCallbackInfo;
using v8::Value;
ChiikaApi::Root* r = 0;
void DestroyChiika(const FunctionCallbackInfo<Value>& args)
{
	std::cout << "Destroying Native Addon" << std::endl;
	if(r)
	{
		delete r;
		r = NULL;
	}

}
NAN_MODULE_INIT(InitAll)
{
	r = new ChiikaApi::Root;


	RootWrapper::Init(target,r);

	NODE_SET_METHOD(target,"DestroyChiika",DestroyChiika);
}


NODE_MODULE(ChiikaNative,InitAll)
