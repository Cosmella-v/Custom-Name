#include <Geode/Geode.hpp>
#include <Geode/modify/LevelCell.hpp>
#include <Geode/modify/LevelListCell.hpp>
using namespace geode::prelude;

#define USER_DATA_API_DEPS
#include "../api/api.hpp"

class $modify(LevelListCell) {
	void loadFromList(GJLevelList *p0) {
		OnlineOnly_Call(LevelListCell::loadFromList(p0));
		CreateSharedandWeak(shared_ptr, weakSelf)

		    Viper::CustomName::API::hiimjasmine00::user_data_api::WaitForDataApi(p0->m_accountID, this, [this, weakSelf, shared_ptr](matjson::Value data) {
			    auto x = shared_ptr;
			    if (auto self = weakSelf.lock()) {

				    if (auto node = self->getChildByIDRecursive("creator-name")) {
					    if (auto name = node->getChildByType<CCLabelBMFont *>(0)) {
						    if (auto h = data.get("name"); h.isOk()) {
							    name->setString(
							        (std::string("by ") +
							        data["name"].asString().unwrapOr(name->getString())).c_str());
							    if (self->m_height > 50) {
								    name->limitLabelWidth(140, 0.7, 0);
							    } else {
								    name->limitLabelWidth(80, 0.45, 0);
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
		OnlineOnly_Call(LevelCell::loadCustomLevelCell());
		CreateSharedandWeak(sharedptr, weakSelf)
		    Viper::CustomName::API::hiimjasmine00::user_data_api::WaitForDataApi(m_level->m_accountID, this, [this, weakSelf, sharedptr](matjson::Value data) {
			    auto x = sharedptr;
			    if (auto self = weakSelf.lock()) {
				    if (auto node = self->getChildByIDRecursive("creator-name")) {
					    if (auto name = node->getChildByType<CCLabelBMFont *>(0)) {
						    if (auto h = data.get("name"); h.isOk()) {
							    name->setString(
							        (std::string("by ") +
							        data["name"].asString().unwrapOr(name->getString())).c_str());
							    if (this->m_height > 50) {
								    name->limitLabelWidth(140, 0.7, 0);
							    } else {
								    name->limitLabelWidth(80, 0.45, 0);
							    }
						    };
					    };
				    };
			    }
		    });
	};
};