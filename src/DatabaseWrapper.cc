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
#include "Root\Root.h"
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

const char* kArgUsername = "userName";
const char* kArgPass = "password";

DatabaseWrapper::DatabaseWrapper()
{


}

DatabaseWrapper::~DatabaseWrapper()
{

}

void DatabaseWrapper::Init(Nan::ADDON_REGISTER_FUNCTION_ARGS_TYPE target, ChiikaApi::Root* r)
{
	root_ = r;
	v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
	tpl->SetClassName(Nan::New("Database").ToLocalChecked());
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	v8::Local<v8::ObjectTemplate> inst = tpl->InstanceTemplate();

	Nan::SetPrototypeMethod(tpl, "SetUser", DatabaseWrapper::SetMalUser);

	tpl->Set(DEFINE_PROPERTY(kAnimeListProperty, Nan::New<Object>()));
	tpl->Set(DEFINE_PROPERTY(kPropertyUserInfo, Nan::New<Object>()));
	tpl->Set(DEFINE_PROPERTY(kPropertyMangaList, Nan::New<Object>()));

	Nan::SetNamedPropertyHandler(inst,
		DatabaseWrapper::DatabaseGetter);


	constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
	Nan::Set(target, Nan::New("Database").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());


}

NAN_METHOD(DatabaseWrapper::SetMalUser)
{
	DatabaseWrapper *obj = new DatabaseWrapper;
	obj->Wrap(info.This());
	v8::Local<v8::Array> args = info[0].As<v8::Array>();

	v8::Isolate* isolate = info.GetIsolate();

	std::string userName = "";
	std::string pass = "";

	V8Value vUsername = args->Get(v8::String::NewFromUtf8(isolate, kArgUsername));
	V8Value vPass	  = args->Get(v8::String::NewFromUtf8(isolate, kArgPass));

	userName = std::string(*v8::String::Utf8Value(vUsername));
	pass = std::string(*v8::String::Utf8Value(vPass));

	if (userName == "undefined" || pass == "undefined")
	{
		info.GetReturnValue().Set(Nan::New(false));
	}
	else
	{
		root_->GetUser().SetKeyValue("user_name", userName);
		root_->GetUser().SetKeyValue("Pass", pass);

		info.GetReturnValue().Set(Nan::New(true));
	}
	

	
}

NAN_METHOD(DatabaseWrapper::New)
{
	if (info.IsConstructCall())
	{
		v8::Isolate* isolate = info.GetIsolate();
		DatabaseWrapper *obj = new DatabaseWrapper;
		obj->Wrap(info.This());
	}
	else
	{
		const int argc = 1;
		v8::Local<v8::Value> argv[argc] = { info[0] };
		v8::Local<v8::Function> cons = Nan::New(constructor);
		info.GetReturnValue().Set(cons->NewInstance(argc, argv));
	}


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

}