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
#include "Converters.h"
#include "Root\Root.h"
using namespace v8;
using namespace ChiikaApi;

namespace Converters
{
	v8::Local<v8::Object> AnimeListToV8(ChiikaApi::Root* root_)
	{
		Local<Object> val = Nan::New<v8::Object>();
		UserInfo userInfo = root_->GetUser();
		UserAnimeList animeList = root_->GetUserAnimelist();

		KeyList animeKeyList;
		GetAnimeKeys(animeKeyList);
		
		KeyList userAnimeKeyList;
		GetUserAnimeEntryKeys(userAnimeKeyList);

		UserAnimeList::iterator It = animeList.begin();
		Local<Array> animeArray = Nan::New<v8::Array>((int)animeList.size());
		int index = 0;
		for(It; It != animeList.end(); ++It)
		{
			Local<Object> singleAnimeObj = Nan::New<v8::Object>();
			Local<Object> animeObj = Nan::New<v8::Object>();
			UserAnimeEntry userAnime = It->second;

			Anime anime = userAnime.Anime;

			FOR_(animeKeyList,j)
			{
				Nan::Set(animeObj,
					Nan::New(animeKeyList[j]).ToLocalChecked(),
					Nan::New(anime.GetKeyValue(animeKeyList[j])).ToLocalChecked());
			}
			Nan::Set(singleAnimeObj,Nan::New("anime").ToLocalChecked(),animeObj);

			FOR_(userAnimeKeyList,k)
			{
				Nan::Set(singleAnimeObj,
					Nan::New(userAnimeKeyList[k]).ToLocalChecked(),
					Nan::New(userAnime.GetKeyValue(userAnimeKeyList[k])).ToLocalChecked());
			}
			Nan::Set(animeArray,index,singleAnimeObj);
			index++;
		}

		Nan::Set(val, Nan::New("UserInfo").ToLocalChecked(), UserInfoToV8(root_));
		Nan::Set(val,Nan::New("AnimeArray").ToLocalChecked(),animeArray);

		return val;
	}

	v8::Local<v8::Object> MangaListToV8(ChiikaApi::Root* root_)
	{
		Local<Object> val = Nan::New<v8::Object>();
		UserInfo userInfo = root_->GetUser();
		UserMangaList animeList = root_->GetUserMangalist();

		KeyList mangaKeyList;
		GetMangaKeys(mangaKeyList);

		KeyList userMangaKeyList;
		GetUserMangaEntryKeys(userMangaKeyList);

		UserMangaList::iterator It = animeList.begin();
		Local<Array> mangaArray = Nan::New<v8::Array>((int)animeList.size());
		int index = 0;
		for (It; It != animeList.end(); ++It)
		{
			Local<Object> singleAnimeObj = Nan::New<v8::Object>();
			Local<Object> animeObj = Nan::New<v8::Object>();
			UserMangaEntry userManga = It->second;

			Manga manga = userManga.Manga;

			FOR_(mangaKeyList, j)
			{
				Nan::Set(animeObj,
					Nan::New(mangaKeyList[j]).ToLocalChecked(),
					Nan::New(manga.GetKeyValue(mangaKeyList[j])).ToLocalChecked());
			}
			Nan::Set(singleAnimeObj, Nan::New("manga").ToLocalChecked(), animeObj);

			FOR_(userMangaKeyList, k)
			{
				Nan::Set(singleAnimeObj,
					Nan::New(userMangaKeyList[k]).ToLocalChecked(),
					Nan::New(userManga.GetKeyValue(userMangaKeyList[k])).ToLocalChecked());
			}
			Nan::Set(mangaArray, index, singleAnimeObj);
			index++;
		}

		Nan::Set(val, Nan::New("UserInfo").ToLocalChecked(), UserInfoToV8(root_));
		Nan::Set(val, Nan::New("MangaArray").ToLocalChecked(), mangaArray);

		return val;
	}

	v8::Local<v8::Object> UserInfoToV8(ChiikaApi::Root* root_)
	{
		Local<Object> val = Nan::New<v8::Object>();
		UserInfo userInfo = root_->GetUser();
		

		KeyList userInfoKeys;
		GetUserInfoKeys(userInfoKeys);

		userInfoKeys.erase(std::find(userInfoKeys.begin(), userInfoKeys.end(), kPass));

		KeyList mangaKeys;
		GetUserInfoMangaKeys(mangaKeys);

		KeyList animeKeys;
		GetUserInfoAnimeKeys(animeKeys);


		Local<Object> userObj = Nan::New<v8::Object>();

		FOR_(userInfoKeys, i)
		{
			Nan::Set(userObj, Nan::New(userInfoKeys[i]).ToLocalChecked(),
				Nan::New(userInfo.GetKeyValue(userInfoKeys[i])).ToLocalChecked());
		}
		Nan::Set(val, Nan::New("UserInfo").ToLocalChecked(), userObj);

		Local<Object> animeInfo = Nan::New<v8::Object>();
		FOR_(animeKeys, i)
		{
			Nan::Set(animeInfo, Nan::New(animeKeys[i]).ToLocalChecked(),
				Nan::New(userInfo.Anime.GetKeyValue(animeKeys[i])).ToLocalChecked());
		}
		Nan::Set(val, Nan::New("AnimeInfo").ToLocalChecked(), animeInfo);

		Local<Object> mangaInfo = Nan::New<v8::Object>();
		FOR_(mangaKeys, i)
		{
			Nan::Set(mangaInfo, Nan::New(mangaKeys[i]).ToLocalChecked(),
				Nan::New(userInfo.Manga.GetKeyValue(mangaKeys[i])).ToLocalChecked());
		}
		Nan::Set(val, Nan::New("MangaInfo").ToLocalChecked(), mangaInfo);

		return val;
	}
	std::string ObjectToString(v8::Local<Value> value)
	{
		String::Utf8Value utf8_value(value);
		return std::string(*utf8_value);
	}
}