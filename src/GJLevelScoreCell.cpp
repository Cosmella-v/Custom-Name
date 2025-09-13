#include <Geode/modify/GJLevelScoreCell.hpp>
#include "../api/api.hpp"
#include <hiimjasmine00.user_data_api/include/Events.hpp>
#define USER_DATA_API_EVENTS
#include <hiimjasmine00.user_data_api/include/UserDataAPI.hpp>
#include <Geode/Geode.hpp>
using namespace geode::prelude;

class $modify(GJLevelScoreCell) {
    void setName(const char* text) {
        if (CCNode* player_name = this->getChildByIDRecursive("player-name") ) {
            if (CCLabelBMFont* Text = player_name->getChildByType<CCLabelBMFont*>(0)) {
                Text->setString(text);
                Text->limitLabelWidth(120,0.8,0);
            };
        } else {
            // i'm gonna assume node ids doesn't have the ids yet
            // im also too lazy to write control c and control v on a node and fix stuff
            if(CCMenu* fish = m_mainLayer->getChildByType<CCMenu*>(0)) {
                if(CCMenuItemSpriteExtra* fish2 = fish->getChildByType<CCMenuItemSpriteExtra*>(0)) {
                     if (CCLabelBMFont* Text = fish2->getChildByType<CCLabelBMFont*>(0)) {
                        Text->setString(text);
                        Text->limitLabelWidth(130,0.8,0);
                    };
                };
            };
        };
    };
    void loadFromScore(GJUserScore* score) {
        GJLevelScoreCell::loadFromScore(score);

        if (auto str = Viper::CustomName::API::getNameFromAccountID(score->m_accountID); !str.empty()) {
            setName(str.c_str());
        };

        if (Viper::CustomName::API::hiimjasmine00::user_data_api::isLoaded()) {
            std::shared_ptr<GJLevelScoreCell> item(
                this,
                [](GJLevelScoreCell *p) { 
                    });
            std::weak_ptr<GJLevelScoreCell> weakSelf = item;

            user_data::handleLevelScoreCell(this, [this,weakSelf](GJUserScore* score) {
                if (auto self = weakSelf.lock()) {
                    if (auto str = Viper::CustomName::API::getNameFromAccountID(score); !str.empty()) {
                        this->setName(str.c_str());
                    };
                }
            });
        }
    };
    
};