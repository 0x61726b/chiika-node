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


		std::vector<const char*> userKeyList =
		{
			kUserId,kUserName,kUserWatching,kUserCompleted,kUserOnhold,kUserDropped,kUserPtw,kUserDaysSpentWatching,
			kUserReading,kUserPtr,kUserDaysSpentReading
		};

		std::vector<const char*> animeKeyList =
		{
			kSeriesAnimedbId,kSeriesTitle,kSeriesSynonyms,kSeriesEpisodes,kSeriesType,kSeriesStatus,
			kSeriesStart,kSeriesEnd,kSeriesImage
		};

		std::vector<const char*> userAnimeKeyList =
		{
			kMyId,kMyWatchedEpisodes,kMyStartDate,kMyFinishDate,kMyScore,kMyStatus,
			kMyRewatching,kMyRewatchingEp,kMyLastUpdated
		};
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
		Local<Object> userObj = Nan::New<v8::Object>();
		FOR_(userKeyList,i)
		{
			Nan::Set(userObj,Nan::New(userKeyList[i]).ToLocalChecked(),
				Nan::New(userInfo.GetKeyValue(userKeyList[i])).ToLocalChecked());
		}
		Nan::Set(val,Nan::New("UserInfo").ToLocalChecked(),userObj);
		Nan::Set(val,Nan::New("AnimeArray").ToLocalChecked(),animeArray);

		return val;
	}

	v8::Local<v8::Object> UserInfoToV8(ChiikaApi::Root* root_)
	{
		Local<Object> val = Nan::New<v8::Object>();
		UserInfo userInfo = root_->GetUser();
		


		std::vector<const char*> userKeyList =
		{
			kUserId,kUserName,kUserWatching,kUserCompleted,kUserOnhold,kUserDropped,kUserPtw,kUserDaysSpentWatching,
			kUserReading,kUserPtr,kUserDaysSpentReading
		};
		Local<Object> userObj = Nan::New<v8::Object>();

		FOR_(userKeyList,i)
		{
			Nan::Set(userObj,Nan::New(userKeyList[i]).ToLocalChecked(),
				Nan::New(userInfo.GetKeyValue(userKeyList[i])).ToLocalChecked());
		}
		Nan::Set(val,Nan::New("UserInfo").ToLocalChecked(),userObj);

		return val;
	}
}