
#include <Geode/Geode.hpp>
using namespace geode::prelude;
#include <Geode/modify/ProfilePage.hpp>

#include "../api/api.hpp"
#define ID_DONTCALLME_MYDEADNAME_I_AM_NOT_MUHAMMAD_I_AM_COSMELLA Viper::CustomName::API::usernamebadge_ID

#include <hiimjasmine00.user_data_api/include/Events.hpp>
#define USER_DATA_API_EVENTS
#include <hiimjasmine00.user_data_api/include/UserDataAPI.hpp>

class $modify(CustomNameProfile, ProfilePage) {
	struct Fields {
		CCMenuItemSpriteExtra *m_deadName = nullptr; // DON'T CALL ME MY DEADNAME!!!!
	};
	void sleepwithOneEyeOpen(CCObject *xd) {
		geode::createQuickPopup(
		    m_score->m_userName.c_str(),
		    fmt::format("This account goes by <cr>{}</c>\n would you like to copy their username?", m_score->m_userName, Viper::CustomName::API::getNameFromAccountID(m_score->m_accountID)).c_str(),
		    "No", "Yes",
		    [this](auto, bool btn2) {
			    if (btn2) {
				    geode::utils::clipboard::write(m_score->m_userName);
			    };
		    });
	};
	void usernameStuff() {
		if (this->m_fields->m_deadName)
			return;

		CCSprite *spr = CCSprite::create("UsernameBadge.png"_spr);
		spr->setScale(0.075);
		CCMenuItemSpriteExtra *deadName = CCMenuItemSpriteExtra::create(
		    spr,
		    this,
		    menu_selector(CustomNameProfile::sleepwithOneEyeOpen));
		deadName->setID(ID_DONTCALLME_MYDEADNAME_I_AM_NOT_MUHAMMAD_I_AM_COSMELLA);
		deadName->setAnchorPoint({1, 0.5});
		this->m_fields->m_deadName = deadName;
		deadName->setVisible(false);
		m_buttonMenu->addChild(deadName);
	};
	void patchname(CCNode *item) {
		if (!m_usernameLabel)
			return;
		if (auto usernameMenu = m_mainLayer->getChildByID("username-menu")) {
			usernameMenu->updateLayout();
		}
		CCNode *Node = this->getChildByIDRecursive("mod-badge");
		if (!Node)
			Node = m_usernameLabel;

		if (item) {
			CCSize labelSize = Node->getContentSize();
			CCPoint worldPos = Node->convertToWorldSpace({0, labelSize.height - 5.0f});
			CCPoint buttonPos = m_buttonMenu->convertToNodeSpace(worldPos);
			item->setPosition(buttonPos);
		};
	}
	void loadPageFromUserInfo(GJUserScore *p0) {
		if (!m_usernameLabel)
			ProfilePage::loadPageFromUserInfo(p0);
		if (auto str = Viper::CustomName::API::getNameFromAccountID(p0->m_accountID); !str.empty()) {
			m_usernameLabel->setString(str.c_str());
			m_usernameLabel->limitLabelWidth(160, 0.8, 0);
		}
		if (Viper::CustomName::API::hiimjasmine00::user_data_api::isLoaded()) {
			usernameStuff();
#ifdef __viper_CustomName__ScuffedNetworkWatingForGettingData
			patchname(this->m_fields->m_deadName);
#endif
		}
		ProfilePage::loadPageFromUserInfo(p0);
#ifndef __viper_CustomName__ScuffedNetworkWatingForGettingData
		auto weakSelf = geode::WeakRef(this);
		user_data::handleProfilePage(this, [weakSelf](GJUserScore *score) {
			if (auto self = weakSelf.lock()) {
				if (self->m_usernameLabel) {
					if (auto str = Viper::CustomName::API::getNameFromAccountID(score->m_accountID); !str.empty()) {
						self->m_usernameLabel->setString(str.c_str());
						self->m_usernameLabel->limitLabelWidth(160, 0.8, 0);
						if (self->m_fields->m_deadName) self->m_fields->m_deadName->setVisible(true);
					};
					if (Viper::CustomName::API::hiimjasmine00::user_data_api::isLoaded()) {
						if (self->m_fields->m_deadName) self->patchname(self->m_fields->m_deadName);
					}
				};
			}
		});
#endif
	};
};
