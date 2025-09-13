#include <Geode/modify/GJScoreCell.hpp>
#include "../api/api.hpp"
#include <hiimjasmine00.user_data_api/include/Events.hpp>
#define USER_DATA_API_EVENTS
#include <hiimjasmine00.user_data_api/include/UserDataAPI.hpp>
#include <Geode/Geode.hpp>
using namespace geode::prelude;

class $modify(GJScoreCell) {
    void setName(const char* text) {
        if (CCNode* player_name = this->getChildByIDRecursive("player-name") ) {
            if (CCLabelBMFont* Text = player_name->getChildByType<CCLabelBMFont*>(0)) {
                Text->setString(text);
                Text->limitLabelWidth(120,0.8,0);
            };
        };
    };
    void loadFromScore(GJUserScore* score) {
        GJScoreCell::loadFromScore(score);

        if (auto str = Viper::CustomName::API::getNameFromAccountID(score->m_accountID); !str.empty()) {
            setName(str.c_str());
        };

        if (Viper::CustomName::API::hiimjasmine00::user_data_api::isLoaded()) {
            std::shared_ptr<GJScoreCell> item(
                this,
                [](GJScoreCell *p) { 
                    });
            std::weak_ptr<GJScoreCell> weakSelf = item;

            user_data::handleScoreCell(this, [this,weakSelf](GJUserScore* score) {
                if (auto self = weakSelf.lock()) {
                    if (auto str = Viper::CustomName::API::getNameFromAccountID(score->m_accountID); !str.empty()) {
                        this->setName(str.c_str());
                    };
                }
            });
        }
    };
    
};