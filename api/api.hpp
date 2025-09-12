// I KNOW this isn't needed however just in case someone wants to use the apis i will be using
// there are no hooks just pure api infact you can just use the header
#pragma once
#include <Geode/loader/Event.hpp>
namespace Viper::CustomName::API {
const std::string ID = "viper.custom-name";
const std::string usernamebadge_ID = "viper.custom-name/deadName";

namespace hiimjasmine00::user_data_api {
	/* MIT License

	Copyright (c) 2025 hiimjasmine00

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
	*/
	const std::string ID = "hiimjasmine00.user_data_api";
	inline bool isLoaded() {
		return (geode::Loader::get()->getLoadedMod(hiimjasmine00::user_data_api::ID) != nullptr);
	};
	inline GameLevelManager *GameLevelManger() {
		static GameLevelManager *gmanger = GameLevelManager::get();
		return gmanger;
	};
	
	// wait for mod
	template <typename F>
	static void waitforMod(F &&callback) {
		if (geode::Loader::get()->getLoadedMod(hiimjasmine00::user_data_api::ID) != nullptr) {
			callback();
		} else {
			auto mod = geode::Loader::get()->getInstalledMod(hiimjasmine00::user_data_api::ID);
			if (!mod)
				return;

			new geode::EventListener(
				[callback = std::forward<F>(callback)](geode::ModStateEvent *) {
					callback();
				},
				geode::ModStateFilter(mod, geode::ModEventType::Loaded));
		}
	};
	#ifndef __viper_CustomName__ScuffedNetworkWatingForGettingData
	/// Retrieves user data from the given node for the specified ID and converts it to the specified type. (Defaults to matjson::Value)
	/// @param node The node to retrieve data from
	/// @param id The ID to retrieve data for (Defaults to your mod ID)
	/// @returns A Result containing the user data as the specified type, or an error if the data could not be retrieved or converted.

	// (Viper addition) added it to default to the GameLevelManager
	// todo add it to call if not cached
	template <class T = matjson::Value>
	inline geode::Result<T> get(cocos2d::CCNode *node, int accountID=0, std::string_view id = Viper::CustomName::API::ID) {
		if (!node) {
			return geode::Err("Node is null");
		}
		if (auto obj = static_cast<cocos2d::CCString *>(node->getUserObject(fmt::format("{}/{}", ID, id)))) {
			return matjson::parseAs<T>(obj->m_sString);
		} else {
			return geode::Err("User object not found");
		}
	};
	#else
	inline geode::Result<matjson::Value> data(int accountid) {
		if (auto obj = static_cast<cocos2d::CCString *>(GameLevelManger()->getUserObject(fmt::format("{}/cache/{}", Viper::CustomName::API::ID, accountid)))) {
			return matjson::parseAs<matjson::Value>(obj->m_sString);
		}
		return geode::Err("User object not found");
	};
	#endif
}; // namespace hiimjasmine00::user_data_api

static inline geode::Mod* self() {
	static geode::Mod *self = geode::Loader::get()->getLoadedMod(ID);
	return self;
};

inline bool enabledLocally() {
	return self()->getSettingValue<bool>("mod-toggled");
};

inline std::string getLocalUsername() {
	if (self() && enabledLocally()) {
			return self()->getSettingValue<std::string>("username");
		} else {
			return GJAccountManager::get()->m_username;
		};
};

inline std::string getNameFromAccountID(int accountID, std::string defaultstr = "") {
	if (/*accountID == GJAccountManager::get()->m_accountID*/false==true) {
		if (self() && enabledLocally()) {
			return self()->getSettingValue<std::string>("username");
		} else {
			return defaultstr;
		}
	} else {

		if (!hiimjasmine00::user_data_api::isLoaded())
			return defaultstr;
		#ifndef DEBUG__Scuffed__NetworkFix
			matjson::Value data = hiimjasmine00::user_data_api::get(hiimjasmine00::user_data_api::GameLevelManger()->userInfoForAccountID(accountID),accountID,Viper::CustomName::API::ID).unwrapOrDefault();
		#elif
			matjson::Value data = hiimjasmine00::user_data_api::data(accountID).unwrapOrDefault();
		#endif
		if (auto h = data.get("name"); h.isOk()) {
			return data["name"].asString().unwrapOr(defaultstr);
		};
		return defaultstr;
	};
};

// check for the mod
template <typename F>
static void waitforMod(F &&callback) {
	if (geode::Loader::get()->getLoadedMod(ID) != nullptr) {
		callback();
	} else {
		auto mod = geode::Loader::get()->getInstalledMod(ID);
		if (!mod)
			return;

		new geode::EventListener(
		    [callback = std::forward<F>(callback)](geode::ModStateEvent *) {
			    callback();
		    },
		    geode::ModStateFilter(mod, geode::ModEventType::Loaded));
	}
};

} // namespace Viper::CustomName::API