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
#ifndef __ApiWrapper_h__
#define __ApiWrapper_h__
//----------------------------------------------------------------------------
#include <nan.h>
#include "Root\Root.h"
#include "Request\RequestInterface.h"
//----------------------------------------------------------------------------

#define V8Value v8::Local<v8::Value>
#define DEFINE_PROPERTY(name,value) v8::String::NewFromUtf8(v8::Isolate::GetCurrent(),name),value)

class RootWrapper : public Nan::ObjectWrap,public ChiikaApi::RequestListener
{
public:
	static void Init(Nan::ADDON_REGISTER_FUNCTION_ARGS_TYPE target,ChiikaApi::Root* r);

public:
	explicit RootWrapper();
	~RootWrapper();

	static NAN_METHOD(ApiVersion);
	static NAN_METHOD(New);
	static NAN_METHOD(VerifyUser);
	static Nan::Persistent<v8::Function> constructor;

	static NAN_PROPERTY_GETTER(RootGetter);
	void OnSuccess(ChiikaApi::RequestInterface*);
	void OnError(ChiikaApi::RequestInterface*);

	//RequestInterface


	std::string version;
	static ChiikaApi::Root* root_;

	
	typedef std::map<std::string, std::pair<v8::Handle<v8::Function>, v8::Isolate*> > CallbackMap;
	CallbackMap m_CallbackMap;
};


#endif