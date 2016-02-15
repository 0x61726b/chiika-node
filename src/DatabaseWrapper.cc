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
//	Date: 20.1.2016
//	authors: arkenthera
//	Description:
//----------------------------------------------------------------------------
#include "DatabaseWrapper.h"
#include "Root/Root.h"
#include "Common.h"
#include "Converters.h"
//----------------------------------------------------------------------------

Nan::Persistent<v8::Function> DatabaseWrapper::constructor;
ChiikaApi::Root* DatabaseWrapper::root_;

using namespace v8;
using namespace ChiikaApi;

const char* kAnimeListProperty = "Animelist";
const char* kPropertyMangaList = "Mangalist";
const char* kPropertyUserInfo = "User";
const char* kPropertySenpaiData = "Senpai";

const char* kArgUsername = "userName";
const char* kArgPass = "password";

struct SystemEventCallbackParams
{
	Nan::Persistent<v8::Object,v8::CopyablePersistentTraits<v8::Object>> Caller;
	Nan::Persistent<v8::Function,v8::CopyablePersistentTraits<v8::Function>> Callback;
	ChiikaApi::SystemEvents Event;
};

DatabaseWrapper::DatabaseWrapper()
{
	loop = uv_default_loop();
	uv_async_init(loop,&async,&DatabaseWrapper::TaskOnMainThread);

}

DatabaseWrapper::~DatabaseWrapper()
{

}

void DatabaseWrapper::TaskOnMainThread(uv_async_t* req)
{
	SystemEventCallbackParams* params = reinterpret_cast<SystemEventCallbackParams*>(req->data);
	DatabaseWrapper *obj = new DatabaseWrapper;


	if(params)
	{
		obj->Wrap(Nan::New(params->Caller));
		Local<Function> local = Nan::New(params->Callback);

		if(params->Event == 0)
		{
			PersistentValue returnval;
			Local<Object> val = Nan::New<v8::Object>();
			Nan::Set(val,Nan::New("event_name").ToLocalChecked(),Nan::New("chiika_fs_ready").ToLocalChecked());

			returnval.Reset(val);

			Local<Value> ret[1] ={Nan::New(returnval)};


			local->Call(Null(Isolate::GetCurrent()),1,ret);
		}


	}
}

void DatabaseWrapper::Init(Nan::ADDON_REGISTER_FUNCTION_ARGS_TYPE target,ChiikaApi::Root* r)
{
	root_ = r;
	v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
	tpl->SetClassName(Nan::New("Database").ToLocalChecked());
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	v8::Local<v8::ObjectTemplate> inst = tpl->InstanceTemplate();

	Nan::SetPrototypeMethod(tpl,"SetUser",DatabaseWrapper::SetMalUser);

	tpl->Set(DEFINE_PROPERTY(kAnimeListProperty,Nan::New<Object>()));
	tpl->Set(DEFINE_PROPERTY(kPropertyUserInfo,Nan::New<Object>()));
	tpl->Set(DEFINE_PROPERTY(kPropertyMangaList,Nan::New<Object>()));
	tpl->Set(DEFINE_PROPERTY(kPropertySenpaiData,Nan::New<Object>()));

	Nan::SetNamedPropertyHandler(inst,
		DatabaseWrapper::DatabaseGetter);


	constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
	Nan::Set(target,Nan::New("Database").ToLocalChecked(),Nan::GetFunction(tpl).ToLocalChecked());


}

NAN_METHOD(DatabaseWrapper::SetMalUser)
{
	DatabaseWrapper *obj = new DatabaseWrapper;
	obj->Wrap(info.This());
	v8::Local<v8::Array> args = info[0].As<v8::Array>();

	v8::Isolate* isolate = info.GetIsolate();

	std::string userName = "";
	std::string pass = "";

	V8Value vUsername = args->Get(v8::String::NewFromUtf8(isolate,kArgUsername));
	V8Value vPass	  = args->Get(v8::String::NewFromUtf8(isolate,kArgPass));

	userName = std::string(*v8::String::Utf8Value(vUsername));
	pass = std::string(*v8::String::Utf8Value(vPass));

	if(userName == "undefined" || pass == "undefined")
	{
		info.GetReturnValue().Set(Nan::New(false));
	}
	else
	{
		root_->GetUser().SetKeyValue("user_name",userName);
		root_->GetUser().SetKeyValue("Pass",pass);

		info.GetReturnValue().Set(Nan::New(true));
	}



}

NAN_METHOD(DatabaseWrapper::New)
{
	if(info.IsConstructCall())
	{
		v8::Isolate* isolate = info.GetIsolate();
		DatabaseWrapper *obj = new DatabaseWrapper;
		obj->Wrap(info.This());



		PersistentFunction callback;
		callback.Reset((info[0].As<Function>()));

		PersistentObject caller;
		caller.Reset(info.This());

		obj->m_Caller = caller;
		obj->m_SystemEventCallback = callback;

		root_->RegisterSystemEventListener(obj);
		root_->InitDatabase();
	}
	else
	{
		const int argc = 1;
		v8::Local<v8::Value> argv[argc] ={info[0]};
		v8::Local<v8::Function> cons = Nan::New(constructor);
		info.GetReturnValue().Set(cons->NewInstance(argc,argv));
	}


}
void DatabaseWrapper::OnEvent(ChiikaApi::SystemEvents evt)
{
	SystemEventCallbackParams* callback = new SystemEventCallbackParams;
	callback->Callback = m_SystemEventCallback;
	callback->Caller = m_Caller;
	callback->Event = evt;
	async.data = reinterpret_cast<void*>(callback);

	uv_async_send(&async);
}
NAN_PROPERTY_GETTER(DatabaseWrapper::DatabaseGetter)
{
	DatabaseWrapper* obj = Nan::ObjectWrap::Unwrap<DatabaseWrapper>(info.This());

	std::string prop = Converters::ObjectToString(property);

	if (prop == kAnimeListProperty)
	{
		v8::Local<v8::Value> val = Converters::AnimeListToV8(obj->root_);
		info.GetReturnValue().Set(val);
	}

	if(prop == kPropertyUserInfo)
	{
		v8::Local<v8::Value> val = Converters::UserInfoToV8(obj->root_);
		info.GetReturnValue().Set(val);
	}
	if (prop == kPropertyMangaList)
	{
		v8::Local<v8::Value> val = Converters::MangaListToV8(obj->root_);
		info.GetReturnValue().Set(val);
	}

	if (prop == kPropertySenpaiData)
	{
		v8::Local<v8::Value> val = Converters::SenpaiDataToV8(obj->root_);
		info.GetReturnValue().Set(val);
	}

}