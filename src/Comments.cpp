#include <Geode/Geode.hpp>
#include "../api/api.hpp"

using namespace geode::prelude;
// the comment cell was so fucking stupid i'd rather kill myself
#ifdef __viper_CustomName__ScuffedNetworkWatingForGettingData
#include <Geode/modify/GameLevelManager.hpp>
class $modify(GameLevelManager) {
	gd::string userNameForUserID(int UserID) {
		auto this_00 = m_userIDtoAccountIDDict->valueForKey(UserID);
		int CompAccountID = 0;
		if (this_00 != nullptr) {
			CompAccountID = this_00->intValue();
		} else {
			return GameLevelManager::userNameForUserID(UserID);
		}
		return Viper::CustomName::API::getNameFromAccountID(CompAccountID,GameLevelManager::userNameForUserID(UserID));
	};
};
#else
#include <hiimjasmine00.user_data_api/include/Events.hpp>
#define USER_DATA_API_EVENTS
#include <hiimjasmine00.user_data_api/include/UserDataAPI.hpp>
#include <Geode/modify/CommentCell.hpp>

class $modify(CommentCell) {
    void loadFromComment(GJComment* comment) {
        CommentCell::loadFromComment(comment);
		#define f if (auto text = typeinfo_cast<CCLabelBMFont*>(node)) { text->setString(str.c_str()); text->limitLabelWidth(15, 0.3, 0); \
				} else { \
				if (auto textmenu = typeinfo_cast<CCMenu*>(node); auto text = textmenu->getChildByType<CCLabelBMFont*>(0)) text->setString(str.c_str()); text->limitLabelWidth(360, 1, 0.1); \
				};
        user_data::handleCommentCell(this, [this](GJComment* comment) {
			if (auto str = Viper::CustomName::API::getNameFromAccountID(comment->m_accountID); !str.empty()) { 
				//log::info("data from text {}",static_cast<cocos2d::CCString *>(this->getUserObject("LabelWidthText"))->m_sString);
				if (auto node = this->getChildByIDRecursive("username-button")) {
					f
				} else if(auto node = this->getChildByIDRecursive("username-label")) {
					f
				}
			};
        });
    }
};
#endif