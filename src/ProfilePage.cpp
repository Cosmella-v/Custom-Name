
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
		bool nodeidsFix = false;
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
		if (!this) return;
		if (this->m_fields->m_deadName)
			return;
		if (!m_usernameLabel)
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
		m_buttonMenu->addChild(deadName);

		// m_usernameLabel->addChild(deadName);
	};
	void patchname() {
		if (m_fields->nodeidsFix) {
			if (auto usernameMenu = m_mainLayer->getChildByID("username-menu")) {
				usernameMenu->updateLayout();
			}
			CCNode *Node = this->getChildByIDRecursive("mod-badge");
			if (!Node)
				Node = m_usernameLabel;
			if (this->m_fields->m_deadName) {
				CCSize labelSize = Node->getContentSize();
				CCPoint worldPos = Node->convertToWorldSpace({0, labelSize.height - 5.0f});
				CCPoint buttonPos = m_buttonMenu->convertToNodeSpace(worldPos);
				this->m_fields->m_deadName->setPosition(buttonPos);
			};
		} else {
			if (this->m_fields->m_deadName) {
				CCSize labelSize = m_usernameLabel->getContentSize();
				CCPoint worldPos = m_usernameLabel->convertToWorldSpace({0, labelSize.height - 5.0f});
				CCPoint buttonPos = m_buttonMenu->convertToNodeSpace(worldPos);
				this->m_fields->m_deadName->setPosition(buttonPos);
			};
		}
	}
	void loadPageFromUserInfo(GJUserScore *p0) {
		if (!m_usernameLabel)
			ProfilePage::loadPageFromUserInfo(p0);
		if (auto str = Viper::CustomName::API::getNameFromAccountID(p0->m_accountID); !str.empty()) {
			m_usernameLabel->setString(str.c_str());
			m_usernameLabel->limitLabelWidth(160, 0.8, 0);
			usernameStuff();
		}
		ProfilePage::loadPageFromUserInfo(p0);
		#ifndef __viper_CustomName__ScuffedNetworkWatingForGettingData
			user_data::handleProfilePage(this, [this](GJUserScore *score) {
				if (this && m_usernameLabel && this->m_fields.self()) {
					if (auto str = Viper::CustomName::API::getNameFromAccountID(score->m_accountID); !str.empty()) {
						m_usernameLabel->setString(str.c_str());
						m_usernameLabel->limitLabelWidth(160, 0.8, 0);
						usernameStuff();
					};
					patchname();
				};
			});
		#else
			patchname();
		#endif
	};
};
