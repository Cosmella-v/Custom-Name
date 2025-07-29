#include <Geode/Geode.hpp>
#include <Geode/modify/GameLevelManager.hpp>

using namespace geode::prelude;
// the comment cell was so fucking stupid i'd rather do this, this is to fix comments lol
class $modify(GameLevelManager) {
	gd::string userNameForUserID(int UserID) {
		auto this_00 = m_userIDtoAccountIDDict->valueForKey(UserID);
		int CompAccountID = 0;
		if (this_00 != nullptr) {
			CompAccountID = this_00->intValue();
		} else {
			return GameLevelManager::userNameForUserID(UserID);
		}

		 //log::debug(" {} VS {} ",  GJAccountManager::get()->m_accountID,CompAccountID);
		 if ( GJAccountManager::get()->m_accountID == CompAccountID) return Mod::get()->getSettingValue<std::string>("username");
		 return GameLevelManager::userNameForUserID(UserID);
	};
};