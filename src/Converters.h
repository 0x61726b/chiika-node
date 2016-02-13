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
#include <nan.h>
#include "Root\Root.h"
//----------------------------------------------------------------------------
#ifndef __Converters_h__
#define __Converters_h__
//----------------------------------------------------------------------------
namespace Converters
{
	v8::Local<v8::Object> AnimeListToV8(ChiikaApi::Root* root);
	v8::Local<v8::Object> MangaListToV8(ChiikaApi::Root* root);
	v8::Local<v8::Object> UserInfoToV8(ChiikaApi::Root* root);
	v8::Local<v8::Object> SenpaiDataToV8(ChiikaApi::Root* root);
	v8::Local<v8::Object> AnimeToV8(ChiikaApi::Root* root,std::string animeId);
	std::string ObjectToString(v8::Local<v8::Value> value);
}


//----------------------------------------------------------------------------
#endif

