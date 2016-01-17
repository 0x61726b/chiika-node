//----------------------------------------------------------------------------
//Chiika-Node
//Copyright (C) 2016 arkenthera
//This program is free software; you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation; either version 2 of the License, or
//(at your option) any later version.
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along
//with this program; if not, write to the Free Software Foundation, Inc.,
//51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.*/
//
//	Date: 17.1.2016
//	authors: arkenthera
//	Description:
//----------------------------------------------------------------------------
#include "ApiWrapper.h"
#include "Root\Root.h"
#include "Logging\LogManager.h"

#include "Request\AccountVerify.h"

Nan::Persistent<v8::Function> RootWrapper::constructor;
ChiikaApi::Root* RootWrapper::root_;


const char kArgsAppMode[] = "appMode";
const char kArgsDebugMode[] = "debugMode";
const char kArgsUserName[] = "userName";
const char kArgsPass[] = "pass";
const char kArgsModulePath[] = "modulePath";

using v8::Function;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Null;
using v8::Object;
using v8::String;
using v8::Value;


void RootWrapper::Init(Nan::ADDON_REGISTER_FUNCTION_ARGS_TYPE target,ChiikaApi::Root* r)
{
	root_ = r;
	v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
	tpl->SetClassName(Nan::New("Root").ToLocalChecked());
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	v8::Local<v8::ObjectTemplate> inst = tpl->InstanceTemplate();

	Nan::SetPrototypeMethod(tpl,"verifyUser",RootWrapper::VerifyUser);

	tpl->Set(DEFINE_PROPERTY(kArgsAppMode,Nan::New(false));
	tpl->Set(DEFINE_PROPERTY(kArgsDebugMode,Nan::New(false));

	tpl->Set(DEFINE_PROPERTY(kArgsUserName,Nan::New("Not_Defined").ToLocalChecked());
	tpl->Set(DEFINE_PROPERTY(kArgsPass,Nan::New("Not_Defined").ToLocalChecked());
	tpl->Set(DEFINE_PROPERTY(kArgsModulePath,Nan::New("Not_Defined").ToLocalChecked());

	Nan::SetNamedPropertyHandler(inst,
		RootWrapper::RootGetter);

	constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
	Nan::Set(target,Nan::New("Root").ToLocalChecked(),Nan::GetFunction(tpl).ToLocalChecked());


}

RootWrapper::RootWrapper()
{

}
RootWrapper::~RootWrapper()
{
}

void RootWrapper::OnSuccess(ChiikaApi::RequestInterface* )
{
	root_->m_pLogManager->LogMessage("Success");
}
void RootWrapper::OnError(ChiikaApi::RequestInterface*)
{
	root_->m_pLogManager->LogMessage("Error");
}
NAN_METHOD(RootWrapper::VerifyUser)
{
	RootWrapper *obj = new RootWrapper;
	obj->Wrap(info.This());

	v8::Isolate* isolate = info.GetIsolate();
	Local<Function> callback = Local<Function>::Cast(info[0]);

	ChiikaApi::UserInfo ui;
	ui.UserName = "arkenthera";
	ui.Pass = "123";

	ChiikaApi::AccountVerifyRequest request;
	request.Initialize();
	request.SetOptions();
	request.SetUserInfo(ui);
	request.AddListener(obj);
	request.Initiate();


	//Return
	Local<v8::Array> returnArray = v8::Array::New(isolate,3);

	returnArray->Set(0,String::NewFromUtf8(isolate,"Test1"));
	returnArray->Set(1,String::NewFromUtf8(isolate,"Test2"));
	returnArray->Set(2,String::NewFromUtf8(isolate,"Test3"));

	const unsigned argc = 1;
	Local<Value> argv[argc] ={returnArray};

	callback->Call(Null(isolate),argc,argv);

}

NAN_METHOD(RootWrapper::New)
{
	if(info.IsConstructCall())
	{
		v8::Isolate* isolate = v8::Isolate::GetCurrent();
		RootWrapper *obj = new RootWrapper;
		obj->Wrap(info.This());


		bool isAppMode = false;
		bool isDebugMode = false;
		std::string userName = "";
		std::string pass = "";
		std::string modulePath = "";
		v8::Local<v8::Array> args = info[0].As<v8::Array>();

		V8Value vAppMode = args->Get(v8::String::NewFromUtf8(isolate,kArgsAppMode));
		V8Value vDebugMode = args->Get(v8::String::NewFromUtf8(isolate,kArgsDebugMode));
		V8Value vUserName = args->Get(v8::String::NewFromUtf8(isolate,kArgsUserName));
		V8Value vPass = args->Get(v8::String::NewFromUtf8(isolate,kArgsPass));
		V8Value vModulePath = args->Get(v8::String::NewFromUtf8(isolate,kArgsModulePath));

		isAppMode = vAppMode->BooleanValue();
		isDebugMode = vDebugMode->BooleanValue();
		userName = std::string(*v8::String::Utf8Value(vUserName));
		pass = std::string(*v8::String::Utf8Value(vPass));
		modulePath = std::string(*v8::String::Utf8Value(vModulePath));

		RootOptions opts;
		opts.appMode = isAppMode;
		opts.debugMode = isDebugMode;
		opts.userName = userName;
		opts.passWord = pass;
		opts.modulePath = modulePath;


		root_->Initialize(opts);
		

		info.GetReturnValue().Set(info.This());


	}
	else {
		const int argc = 1;
		v8::Local<v8::Value> argv[argc] ={info[0]};
		v8::Local<v8::Function> cons = Nan::New(constructor);
		info.GetReturnValue().Set(cons->NewInstance(argc,argv));
	}
}

NAN_PROPERTY_GETTER(RootWrapper::RootGetter)
{
	RootWrapper* obj = Nan::ObjectWrap::Unwrap<RootWrapper>(info.This());

	const char* prop = *v8::String::Utf8Value(property);

	if(strcmp(prop,kArgsAppMode) == 0)
	{
		bool appMode = obj->root_->GetRootOptions().appMode;
		info.GetReturnValue().Set(Nan::New(appMode));
	}
	if(strcmp(prop,kArgsDebugMode) == 0)
	{
		bool debugMode = obj->root_->GetRootOptions().debugMode;
		info.GetReturnValue().Set(Nan::New(debugMode));
	}
	if(strcmp(prop,kArgsUserName) == 0)
	{
		info.GetReturnValue().Set(Nan::New("nope").ToLocalChecked());
	}
	if(strcmp(prop,kArgsPass) == 0)
	{
		info.GetReturnValue().Set(Nan::New("nope").ToLocalChecked());
	}
	if(strcmp(prop,kArgsModulePath) == 0)
	{
		std::string module = obj->root_->GetRootOptions().modulePath;
		info.GetReturnValue().Set(Nan::New(module.c_str()).ToLocalChecked());
	}
}