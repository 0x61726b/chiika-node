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
#include "Common\Required.h"
#include "Root\Root.h"
using namespace v8;
using namespace ChiikaApi;

namespace Converters
{
	v8::Local<v8::Object> AnimeListToV8(ChiikaApi::Root* root_)
	{
		Local<Object> val = Nan::New<v8::Object>();
		UserInfo& userInfo = root_->GetUser();
		UserAnimeList animeList = root_->GetUserAnimelist();
		AnimeList miscAnimeList = root_->GetAnimelist();

		KeyList animeKeyList;
		GetAnimeKeys(animeKeyList);

		KeyList userAnimeKeyList;
		GetUserAnimeEntryKeys(userAnimeKeyList);

		KeyList animeMiscKeys;
		GetAnimeMiscKeys(animeMiscKeys);

		KeyList charactersKeys ={kCharacterId,kCharacterName,kCharacter,kCharacterImage,kCharacterVa,kCharacterVaId};
		KeyList studioKeys ={kStudioId,kStudioName};
		KeyList genreKeys ={kGenre};

		UserAnimeList::iterator It = animeList.begin();
		AnimeList::iterator animelistIt = miscAnimeList.begin();
		Local<Array> animeArray = Nan::New<v8::Array>((int)animeList.size());
		int index = 0;
		for(It; It != animeList.end(); ++It)
		{
			Local<Object> singleAnimeObj = Nan::New<v8::Object>();
			Local<Object> animeObj = Nan::New<v8::Object>();

			Local<Object> animeMiscObj = Nan::New<v8::Object>();
			Local<Object> miscBaseObj = Nan::New<v8::Object>();

			UserAnimeEntry userAnime = It->second;

			AnimeList::iterator miscIt = miscAnimeList.find(userAnime.GetKeyValue(kSeriesAnimedbId));
			

			if(miscIt != miscAnimeList.end())
			{
				Anime anime = miscIt->second;
				FOR_(animeKeyList,j)
				{
					Nan::Set(animeObj,
						Nan::New(animeKeyList[j]).ToLocalChecked(),
						Nan::New(anime.GetKeyValue(animeKeyList[j])).ToLocalChecked());
				}


				FOR_(animeMiscKeys,k)
				{
					Nan::Set(miscBaseObj,
						Nan::New(animeMiscKeys[k]).ToLocalChecked(),
						Nan::New(anime.Misc.GetKeyValue(animeMiscKeys[k])).ToLocalChecked());
				}

				//Characters
				Local<Array> charArray = Nan::New<v8::Array>();
				std::vector<DictionaryBase> charList = anime.Misc.Characters;
				FOR_(charList,a)
				{
					Local<Object> singleCharacter = Nan::New<v8::Object>();
					FOR_(charactersKeys,k)
					{
						Nan::Set(singleCharacter,
							Nan::New(charactersKeys[k]).ToLocalChecked(),
							Nan::New(charList[a].GetKeyValue(charactersKeys[k])).ToLocalChecked());
					}
					Nan::Set(charArray,a,singleCharacter);
				}
				Nan::Set(miscBaseObj,Nan::New(kCharacters).ToLocalChecked(),charArray);
				//~
				//Genres
				Local<Array> genreArray = Nan::New<v8::Array>();
				std::vector<DictionaryBase> genreList = anime.Misc.Genres;
				FOR_(genreList,a)
				{
					Local<Object> singleGenre = Nan::New<v8::Object>();
					FOR_(genreKeys,k)
					{
						Nan::Set(singleGenre,
							Nan::New(genreKeys[k]).ToLocalChecked(),
							Nan::New(genreList[a].GetKeyValue(genreKeys[k])).ToLocalChecked());
					}
					Nan::Set(genreArray,a,singleGenre);
				}
				Nan::Set(miscBaseObj,Nan::New(kGenres).ToLocalChecked(),genreArray);
				//~
				//Studios
				Local<Array> studioArray = Nan::New<v8::Array>();
				std::vector<DictionaryBase> studioList = anime.Misc.Studios;
				FOR_(studioList,a)
				{
					Local<Object> singleStudio = Nan::New<v8::Object>();
					FOR_(studioKeys,k)
					{
						Nan::Set(singleStudio,
							Nan::New(studioKeys[k]).ToLocalChecked(),
							Nan::New(studioList[a].GetKeyValue(studioKeys[k])).ToLocalChecked());
					}
					Nan::Set(studioArray,a,singleStudio);
				}
				Nan::Set(miscBaseObj, Nan::New(kStudios).ToLocalChecked(), studioArray);
				//~

				Nan::Set(singleAnimeObj,Nan::New("Misc").ToLocalChecked(),miscBaseObj);
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
		}

		Nan::Set(val,Nan::New("UserInfo").ToLocalChecked(),UserInfoToV8(root_));
		Nan::Set(val,Nan::New("AnimeArray").ToLocalChecked(),animeArray);

		return val;
	}

	v8::Local<v8::Object> MangaListToV8(ChiikaApi::Root* root_)
	{
		Local<Object> val = Nan::New<v8::Object>();
		UserInfo& userInfo = root_->GetUser();
		UserMangaList animeList = root_->GetUserMangalist();

		std::vector<std::string> mangaKeyList
			={kSeriesMangadbId,kSeriesTitle,kSeriesSynonyms,kSeriesChapters,kSeriesVolumes,kSeriesType,kSeriesStatus,kSeriesStart,kSeriesEnd,kSeriesImage};

		std::vector<std::string> userMangaKeyList
			={kMyId,kMyReadChapters,kMyReadVolumes,kMyRewatchingEp,kMyScore,kMyRereading,kMyRereadingChap,kMyStatus,kMyStartDate,kMyFinishDate,kMyLastUpdated};

		UserMangaList::iterator It = animeList.begin();
		Local<Array> mangaArray = Nan::New<v8::Array>((int)animeList.size());
		int index = 0;
		for(It; It != animeList.end(); ++It)
		{
			Local<Object> singleAnimeObj = Nan::New<v8::Object>();
			Local<Object> animeObj = Nan::New<v8::Object>();
			UserMangaEntry userManga = It->second;

			Manga manga = userManga.Manga;

			FOR_(mangaKeyList,j)
			{
				Nan::Set(animeObj,
					Nan::New(mangaKeyList[j]).ToLocalChecked(),
					Nan::New(manga.GetKeyValue(mangaKeyList[j])).ToLocalChecked());
			}
			Nan::Set(singleAnimeObj,Nan::New("manga").ToLocalChecked(),animeObj);

			FOR_(userMangaKeyList,k)
			{
				Nan::Set(singleAnimeObj,
					Nan::New(userMangaKeyList[k]).ToLocalChecked(),
					Nan::New(userManga.GetKeyValue(userMangaKeyList[k])).ToLocalChecked());
			}
			Nan::Set(mangaArray,index,singleAnimeObj);
			index++;
		}

		Nan::Set(val,Nan::New("UserInfo").ToLocalChecked(),UserInfoToV8(root_));
		Nan::Set(val,Nan::New("MangaArray").ToLocalChecked(),mangaArray);

		return val;
	}

	v8::Local<v8::Object> AnimeToV8(ChiikaApi::Root* root_,std::string animeId)
	{
		Local<Object> val = Nan::New<v8::Object>();
		UserAnimeList animeList = root_->GetUserAnimelist();
		AnimeList miscAnimeList = root_->GetAnimelist();

		UserAnimeList::iterator It = animeList.find(animeId);

		KeyList animeKeyList;
		GetAnimeKeys(animeKeyList);

		KeyList userAnimeKeyList;
		GetUserAnimeEntryKeys(userAnimeKeyList);

		KeyList animeMiscKeys;
		GetAnimeMiscKeys(animeMiscKeys);

		KeyList charactersKeys ={kCharacterId,kCharacterName,kCharacter,kCharacterImage,kCharacterVa,kCharacterVaId};
		KeyList studioKeys ={kStudioId,kStudioName};
		KeyList genreKeys ={kGenre};

		if(It != animeList.end())
		{
			Local<Object> singleAnimeObj = Nan::New<v8::Object>();
			Local<Object> animeObj = Nan::New<v8::Object>();

			Local<Object> animeMiscObj = Nan::New<v8::Object>();
			Local<Object> miscBaseObj = Nan::New<v8::Object>();

			UserAnimeEntry userAnime = It->second;

			AnimeList::iterator miscIt = miscAnimeList.find(userAnime.GetKeyValue(kSeriesAnimedbId));
			

			if(miscIt != miscAnimeList.end())
			{
				Anime anime = miscIt->second;
				FOR_(animeKeyList,j)
				{
					Nan::Set(animeObj,
						Nan::New(animeKeyList[j]).ToLocalChecked(),
						Nan::New(anime.GetKeyValue(animeKeyList[j])).ToLocalChecked());
				}


				FOR_(animeMiscKeys,k)
				{
					Nan::Set(miscBaseObj,
						Nan::New(animeMiscKeys[k]).ToLocalChecked(),
						Nan::New(anime.Misc.GetKeyValue(animeMiscKeys[k])).ToLocalChecked());
				}

				//Characters
				Local<Array> charArray = Nan::New<v8::Array>();
				std::vector<DictionaryBase> charList = anime.Misc.Characters;
				FOR_(charList,a)
				{
					Local<Object> singleCharacter = Nan::New<v8::Object>();
					FOR_(charactersKeys,k)
					{
						Nan::Set(singleCharacter,
							Nan::New(charactersKeys[k]).ToLocalChecked(),
							Nan::New(charList[a].GetKeyValue(charactersKeys[k])).ToLocalChecked());
					}
					Nan::Set(charArray,a,singleCharacter);
				}
				Nan::Set(miscBaseObj,Nan::New(kCharacters).ToLocalChecked(),charArray);
				//~
				//Genres
				Local<Array> genreArray = Nan::New<v8::Array>();
				std::vector<DictionaryBase> genreList = anime.Misc.Genres;
				FOR_(genreList,a)
				{
					Local<Object> singleGenre = Nan::New<v8::Object>();
					FOR_(genreKeys,k)
					{
						Nan::Set(singleGenre,
							Nan::New(genreKeys[k]).ToLocalChecked(),
							Nan::New(genreList[a].GetKeyValue(genreKeys[k])).ToLocalChecked());
					}
					Nan::Set(genreArray,a,singleGenre);
				}
				Nan::Set(miscBaseObj,Nan::New(kGenres).ToLocalChecked(),genreArray);
				//~
				//Studios
				Local<Array> studioArray = Nan::New<v8::Array>();
				std::vector<DictionaryBase> studioList = anime.Misc.Studios;
				FOR_(studioList,a)
				{
					Local<Object> singleStudio = Nan::New<v8::Object>();
					FOR_(studioKeys,k)
					{
						Nan::Set(singleStudio,
							Nan::New(studioKeys[k]).ToLocalChecked(),
							Nan::New(studioList[a].GetKeyValue(studioKeys[k])).ToLocalChecked());
					}
					Nan::Set(studioArray,a,singleStudio);
				}
				Nan::Set(miscBaseObj, Nan::New(kStudios).ToLocalChecked(), studioArray);
				//~

				Nan::Set(singleAnimeObj,Nan::New("Misc").ToLocalChecked(),miscBaseObj);
				Nan::Set(singleAnimeObj,Nan::New("anime").ToLocalChecked(),animeObj);

				FOR_(userAnimeKeyList,k)
				{
					Nan::Set(singleAnimeObj,
						Nan::New(userAnimeKeyList[k]).ToLocalChecked(),
						Nan::New(userAnime.GetKeyValue(userAnimeKeyList[k])).ToLocalChecked());
				}
				val = singleAnimeObj;
			}
		}
		return val;
	}

	v8::Local<v8::Object> UserInfoToV8(ChiikaApi::Root* root_)
	{
		Local<Object> val = Nan::New<v8::Object>();
		UserInfo& userInfo = root_->GetUser();


		std::vector<std::string> userInfoKeys ={"user_id","user_name"};

		std::vector<std::string> mangaKeys ={kUserReading,kUserCompleted,kUserOnhold,kUserDropped,kUserPtr,kUserDaysSpentReading};

		std::vector<std::string> animeKeys ={kUserWatching,kUserCompleted,kUserOnhold,kUserDropped,kUserPtw,kUserDaysSpentWatching};



		Local<Object> userObj = Nan::New<v8::Object>();

		FOR_(userInfoKeys,i)
		{
			Nan::Set(userObj,Nan::New(userInfoKeys[i]).ToLocalChecked(),
				Nan::New(userInfo.GetKeyValue(userInfoKeys[i])).ToLocalChecked());
		}
		Nan::Set(val,Nan::New("UserInfo").ToLocalChecked(),userObj);

		Local<Object> animeInfo = Nan::New<v8::Object>();
		FOR_(animeKeys,i)
		{
			Nan::Set(animeInfo,Nan::New(animeKeys[i]).ToLocalChecked(),
				Nan::New(userInfo.Anime.GetKeyValue(animeKeys[i])).ToLocalChecked());
		}
		Nan::Set(val,Nan::New("AnimeInfo").ToLocalChecked(),animeInfo);

		Local<Object> mangaInfo = Nan::New<v8::Object>();
		FOR_(mangaKeys,i)
		{
			Nan::Set(mangaInfo,Nan::New(mangaKeys[i]).ToLocalChecked(),
				Nan::New(userInfo.Manga.GetKeyValue(mangaKeys[i])).ToLocalChecked());
		}
		Nan::Set(val,Nan::New("MangaInfo").ToLocalChecked(),mangaInfo);

		return val;
	}

	std::string ObjectToString(v8::Local<Value> value)
	{
		String::Utf8Value utf8_value(value);
		return std::string(*utf8_value);
	}

	v8::Local<v8::Object> SenpaiDataToV8(ChiikaApi::Root* root)
	{
		Local<Object> val = Nan::New<v8::Object>();

		std::vector<ChiikaApi::SenpaiItem> senpaiData = root->GetSenpaiData();
		Local<Array> moeArray = Nan::New<v8::Array>();

		FOR_(senpaiData,i)
		{
			Local<Object> moe = Nan::New<v8::Object>();
			

			
			Nan::Set(moe,Nan::New("Name").ToLocalChecked(),Nan::New(senpaiData[i].Name).ToLocalChecked());
			Nan::Set(moe,Nan::New("MalId").ToLocalChecked(),Nan::New(senpaiData[i].MalID));
			

			Local<Object> airdate = Nan::New<v8::Object>();

			Nan::Set(airdate,Nan::New("RdDate").ToLocalChecked(),Nan::New(senpaiData[i].Airdates.begin()->second.RdDate).ToLocalChecked());
			Nan::Set(airdate,Nan::New("RdTime").ToLocalChecked(),Nan::New(senpaiData[i].Airdates.begin()->second.RdTime).ToLocalChecked());
			Nan::Set(airdate,Nan::New("RdWeekday").ToLocalChecked(),Nan::New(senpaiData[i].Airdates.begin()->second.RdWeekday).ToLocalChecked());

			Nan::Set(moe,Nan::New("Airdate").ToLocalChecked(),airdate);
			Nan::Set(moeArray,i,moe);
		}

		return moeArray;
	}
}