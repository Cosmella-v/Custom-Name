#include "../api/api.hpp"
#include <Geode/modify/GJScoreCell.hpp>
#include <hiimjasmine00.user_data_api/include/Events.hpp>
#define USER_DATA_API_EVENTS
#include <Geode/Geode.hpp>
#include <hiimjasmine00.user_data_api/include/UserDataAPI.hpp>
using namespace geode::prelude;

class $modify(GJScoreCell) {
	void setName(const char *text) {
		if (CCNode *player_name = this->getChildByIDRecursive("player-name")) {
			if (CCLabelBMFont *Text = player_name->getChildByType<CCLabelBMFont *>(0)) {
				Text->setString(text);
				Text->limitLabelWidth(120, 0.8, 0);
			};
		};
	};
	void loadFromScore(GJUserScore *score) {
		OnlineOnly_Call(GJScoreCell::loadFromScore(score))

		if (auto str = Viper::CustomName::API::getNameFromAccountID(score->m_accountID); !str.empty()) {
			setName(str.c_str());
		};

		CreateSharedandWeak(item, weakSelf)
		    user_data::handleScoreCell(this, [this, weakSelf, item](GJUserScore *score) {
			    auto x = item;
			    if (auto self = weakSelf.lock()) {
				    if (auto str = Viper::CustomName::API::getNameFromAccountID(score); !str.empty()) {
					    this->setName(str.c_str());
				    };
			    }
		    });
	};
};