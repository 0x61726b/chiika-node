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
#ifndef __RequestWrapper_h__
#define __RequestWrapper_h__
//----------------------------------------------------------------------------
#include <nan.h>
#include "Root/Root.h"
#include "Request/RequestInterface.h"
#include "Common.h"
//----------------------------------------------------------------------------
class RequestWrapper : public Nan::ObjectWrap, public ChiikaApi::RequestListener
{
public:
	static void Init(Nan::ADDON_REGISTER_FUNCTION_ARGS_TYPE target, ChiikaApi::Root* r);

	explicit RequestWrapper();
	~RequestWrapper();

	static NAN_METHOD(New);

	//ChiikaApi Request binds
	static NAN_METHOD(VerifyUser);
	static NAN_METHOD(GetMyAnimelist);
	static NAN_METHOD(GetMyMangalist);
	static NAN_METHOD(AnimeScrape);
	static NAN_METHOD(RefreshAnimeDetails);
	static NAN_METHOD(GetAnimeDetails);
	static NAN_METHOD(UpdateAnime);

	static NAN_METHOD(TestoDicto);
	static Nan::Persistent<v8::Function> constructor;

	static ChiikaApi::Root* root_;
	void OnSuccess(ChiikaApi::RequestInterface*);
	void OnError(ChiikaApi::RequestInterface*);

	PersistentValue ParseRequest(const std::string& r, ChiikaApi::RequestInterface*);

	//http://i3.kym-cdn.com/photos/images/newsfeed/000/632/366/97a.jpg
	typedef std::map<std::string,
		std::pair<Nan::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object> >,
		Nan::Persistent<v8::Function, v8::CopyablePersistentTraits<v8::Function> > > > CallbackMap;


	CallbackMap m_CallbackMap;



	static void TaskOnMainThread(uv_async_t* req);

	uv_async_t async;
	uv_loop_t *loop;
};
//----------------------------------------------------------------------------
#endif
