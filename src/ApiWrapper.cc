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

Nan::Persistent<v8::Function> RootWrapper::constructor;

NAN_MODULE_INIT(RootWrapper::Init)
{
	v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
	tpl->SetClassName(Nan::New("Root").ToLocalChecked());
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	Nan::SetPrototypeMethod(tpl,"ApiVersion",ApiVersion);

	v8::Local<v8::ObjectTemplate> inst = tpl->InstanceTemplate();

	tpl->Set(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(),"test1"),Nan::New("huhu5").ToLocalChecked());
	tpl->Set(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(),"test2"),Nan::New("huhu6").ToLocalChecked());
	tpl->Set(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(),"test3"),Nan::New("huhu7").ToLocalChecked());

	Nan::SetNamedPropertyHandler(inst,
		RootWrapper::ApiVersionGetter);

	constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
	Nan::Set(target,Nan::New("Root").ToLocalChecked(),Nan::GetFunction(tpl).ToLocalChecked());
}

RootWrapper::RootWrapper()
{
}
RootWrapper::~RootWrapper()
{
}

NAN_METHOD(RootWrapper::New)
{
	if(info.IsConstructCall()) {
		double value = info[0]->IsUndefined() ? 0 : Nan::To<double>(info[0]).FromJust();
		RootWrapper *obj = new RootWrapper;
		obj->Wrap(info.This());
		info.GetReturnValue().Set(1);


	}
	else {
		const int argc = 1;
		v8::Local<v8::Value> argv[argc] ={info[0]};
		v8::Local<v8::Function> cons = Nan::New(constructor);
		info.GetReturnValue().Set(cons->NewInstance(argc,argv));
	}
}
NAN_METHOD(RootWrapper::ApiVersion)
{
	RootWrapper* obj = Nan::ObjectWrap::Unwrap<RootWrapper>(info.This());

	obj->version = "0.0.1";

	info.GetReturnValue().Set(Nan::New(obj->version.c_str()).ToLocalChecked());
}

NAN_PROPERTY_GETTER(RootWrapper::ApiVersionGetter)
{
	RootWrapper* obj = Nan::ObjectWrap::Unwrap<RootWrapper>(info.This());

	const char* prop = *v8::String::Utf8Value(property);

	if(strcmp(prop,"test1") == 0)
	{
		info.GetReturnValue().Set(Nan::New("it works xd").ToLocalChecked());
	}
	if(strcmp(prop,"test2") == 0)
	{
		info.GetReturnValue().Set(Nan::New("OMG!").ToLocalChecked());
	}
	if(strcmp(prop,"test3") == 0)
	{
		info.GetReturnValue().Set(Nan::New("PogChamp").ToLocalChecked());
	}
}