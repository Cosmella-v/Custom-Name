#include "../api/api.hpp"
#include <Geode/Geode.hpp>

using namespace geode::prelude;
// the comment cell was so fucking stupid i'd rather kill myself
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
		return Viper::CustomName::API::getNameFromAccountID(CompAccountID, GameLevelManager::userNameForUserID(UserID));
	};
};

#include <hiimjasmine00.user_data_api/include/Events.hpp>
#define USER_DATA_API_EVENTS
#include <Geode/modify/CommentCell.hpp>
#include <hiimjasmine00.user_data_api/include/UserDataAPI.hpp>

class $modify(CommentCell) {
	#define GertText(out) if (auto node = this->getChildByIDRecursive("username-button")) { \
			if(CCMenu* fish = typeinfo_cast<CCMenu*>(node)) { \
				out = fish->getChildByType<CCLabelBMFont*>(0); \
			} else { \
				out = typeinfo_cast<CCLabelBMFont*>(node); \
			} \
		} else { \
			out = typeinfo_cast<CCLabelBMFont*>(this->getChildByIDRecursive("username-label")); \
		}

	void updateNameLayout(GJComment *comment, const char* name, bool isSmallRow, float unk1) {
		CCLabelBMFont* NameLabel = nullptr;
		GertText(NameLabel)
		if (!NameLabel) return;

		float width, defaultScale;
		if (isSmallRow) {
			width = 150.0f;
			defaultScale = 0.5f;
		} else {
			defaultScale = 0.7f;
			width = comment->m_hasLevelID ? 100.0f : 150.0f;
		}
		NameLabel->setCString(name);

		NameLabel->limitLabelWidth(width, defaultScale, 0.0f);

		float widthPad = isSmallRow ? 8.0f : 12.0f;
		float heightPad = isSmallRow ? 11.5f : 19.5f;

		float xPos = ((unk1 + 10.0f) + (NameLabel->getContentSize().width)) + widthPad;

		float unk2 = 0.0f;
		if (auto m_pBadgeSprite = this->getChildByIDRecursive("mod-badge")) {
			float badgeScale = isSmallRow ? 0.55f : 0.75f;
			m_pBadgeSprite->setScale(badgeScale);
			m_pBadgeSprite->setPositionX(xPos);
			unk2 = isSmallRow ? 15.0f : 22.0f;
		}

		if (auto m_pPercentLabel = this->getChildByIDRecursive("percentage-label")) {
			float percentScale = isSmallRow ? 0.48f : 0.6f;
			m_pPercentLabel->setScale(percentScale);

			xPos = (((unk1 + 10.0f) + unk2) + (NameLabel->getContentSize().width)) + 4.0f; 
			m_pPercentLabel->setPositionX(xPos);
		}
	}


	void loadFromComment(GJComment *comment) {
		OnlineOnly_Call(CommentCell::loadFromComment(comment));
		CreateSharedandWeak(sharedptr, weakSelf)

		user_data::handleCommentCell(this, [this,weakSelf,sharedptr](GJComment *comment) {
			auto x = sharedptr;
			if (auto self = weakSelf.lock()) {
				if (auto str = Viper::CustomName::API::getNameFromAccountID(comment->m_accountID); !str.empty()) {
					float unk1 = 0.0f;
					if (self->getChildByIDRecursive("player-icon"))
					{
						unk1 = 26.0f;
					};

					this->updateNameLayout(comment, str.c_str(),this->m_height == 36.0, unk1);
				};
			}
		});
	};
};
