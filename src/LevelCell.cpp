#include <Geode/Geode.hpp>
#include <Geode/modify/LevelCell.hpp>
#include <Geode/modify/LevelListCell.hpp>
using namespace geode::prelude;

#define USER_DATA_API_DEPS
#include "../api/api.hpp"


class $modify(LevelListCell) {
	void loadFromList(GJLevelList* p0) {
		LevelListCell::loadFromList(p0);

		Viper::CustomName::API::hiimjasmine00::user_data_api::WaitForDataApi(p0->m_accountID, this, [this](matjson::Value data) {
            if (this) {
                
				if (auto node = this->getChildByIDRecursive("creator-name")) {
                    if (auto name = node->getChildByType<CCLabelBMFont*>(0)) {
                        if (auto h = data.get("name"); h.isOk()) {
                            name->setString(data["name"].asString().unwrapOr(name->getString()).c_str());
                            if (this->m_height > 50) {
                                name->limitLabelWidth(140,0.7,0);
                            } else {
                                name->limitLabelWidth(80,0.45,0);
                            }
                        };
                    }
                };
			}
		});
	};
};

class $modify(LevelCell) {
	void loadCustomLevelCell() {
		LevelCell::loadCustomLevelCell();

         if (!Viper::CustomName::API::hiimjasmine00::user_data_api::isLoaded()) {
            if (auto str = Viper::CustomName::API::getNameFromAccountID(m_level->m_accountID); !str.empty()) {    

				if (auto node = this->getChildByIDRecursive("creator-name")) {
                    if (auto name = node->getChildByType<CCLabelBMFont*>(0)) {
                        name->setString(str.c_str());
                        if (this->m_height > 50) {
                                name->limitLabelWidth(140,0.7,0);
                            } else {
                                name->limitLabelWidth(80,0.45,0);
                            }
                    }
                }
            }
            return;
        }
        std::shared_ptr<LevelCell> shared_ptr(
			this,
			[](LevelCell* p){}
		);
		std::weak_ptr<LevelCell> weakSelf = shared_ptr;
		Viper::CustomName::API::hiimjasmine00::user_data_api::WaitForDataApi(m_level->m_accountID, this, [this,weakSelf](matjson::Value data) {
            if (auto self = weakSelf.lock()) {
				if (auto node = self->getChildByIDRecursive("creator-name")) {
                    if (auto name = node->getChildByType<CCLabelBMFont*>(0)) {
                        if (auto h = data.get("name"); h.isOk()) {
                            name->setString(data["name"].asString().unwrapOr(name->getString()).c_str());
                            if (this->m_height > 50) {
                                name->limitLabelWidth(140,0.7,0);
                            } else {
                                name->limitLabelWidth(80,0.45,0);
                            }
                        };
                    }
                };
			}
		});
	};
};