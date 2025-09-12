// this fucking ruins my life i might just keep it local, please don't define __viper_CustomName__ScuffedNetworkWatingForGettingData
#ifdef __viper_CustomName__ScuffedNetworkWatingForGettingData
#include "../api/api.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/CCHttpClient.hpp>
#include <Geode/modify/GameLevelManager.hpp>

using namespace geode::prelude;

std::unordered_map<std::string, std::string> parseQuery(const std::string &query) {
	std::unordered_map<std::string, std::string> params;
	std::stringstream ss(query);
	std::string pair;

	while (std::getline(ss, pair, '&')) {
		size_t eqPos = pair.find('=');
		if (eqPos != std::string::npos) {
			std::string key = pair.substr(0, eqPos);
			std::string value = pair.substr(eqPos + 1);
			params[key] = value;
		}
	}
	return params;
}
static CCArray *p_cArray_robfinished;
static CCArray *p_cArray_customnamefinished;
std::unordered_map<CCHttpRequest*, CCHttpResponse*> m_mapper;

$execute {
	auto x = CCArray::create();
	x->retain();
	p_cArray_robfinished = x;

	auto x2 = CCArray::create();
	x2->retain();
	p_cArray_customnamefinished = x2;
};

void parseAccount(CCHttpClient *param_1, CCHttpRequest *param_2, std::unordered_map<std::string, std::string> Redata) {
	param_2->retain();
	if (Redata.find("targetAccountID") != Redata.end()) {
		std::string target = Redata["targetAccountID"];
		web::WebRequest()
		    .get(fmt::format("https://playerdata.hiimjasmine00.com/v3/data?ids={}", target))
		    .listen([=](web::WebResponse *res) {
						if (res->ok()) {
							auto json = res->json().unwrapOrDefault();
							auto data = json.get(target);
							if (data.isOk(); auto vip = json[target].get("viper.custom-name")) {
								if (vip.isOk()) {
									auto GameLevelManger = Viper::CustomName::API::hiimjasmine00::user_data_api::GameLevelManger();
									auto formated = fmt::format("{}/cache/{}", Viper::CustomName::API::ID, target);
									if (auto obj =  static_cast<cocos2d::CCString *>(GameLevelManger->getUserObject(formated))) {
										obj->m_sString = json[target]["viper.custom-name"].dump();
									} else {
										GameLevelManger->setUserObject(
											formated,
											CCString::create(json[target]["viper.custom-name"].dump())
										);
									}
								};
							}
						}
			p_cArray_customnamefinished->addObject(param_2);
			if (p_cArray_robfinished->containsObject(param_2)) {
				Viper::CustomName::API::hiimjasmine00::user_data_api::GameLevelManger()->onProcessHttpRequestCompleted(param_1, m_mapper[param_2]);
			}; }, [](auto prog) {}, [=] { p_cArray_customnamefinished->addObject(param_2);
			if (p_cArray_robfinished->containsObject(param_2)) {
				Viper::CustomName::API::hiimjasmine00::user_data_api::GameLevelManger()->onProcessHttpRequestCompleted(param_1, m_mapper[param_2]);
			}; });
	} else {
		p_cArray_customnamefinished->addObject(param_2);
		if (p_cArray_robfinished->containsObject(param_2)) {
			Viper::CustomName::API::hiimjasmine00::user_data_api::GameLevelManger()->onProcessHttpRequestCompleted(param_1, m_mapper[param_2]);
		};
	};
};

class $modify(GameLevelManager) {
	void onProcessHttpRequestCompleted(CCHttpClient *param_1, CCHttpResponse *param_2) {
		auto r = param_2->getHttpRequest();
		if (!r)
			return GameLevelManager::onProcessHttpRequestCompleted(param_1, param_2);
		if (r->getType() != (int)GJHttpType::GetGJUserInfo) {
			return GameLevelManager::onProcessHttpRequestCompleted(param_1, param_2);
		} else {
			
			if (!p_cArray_robfinished->containsObject(r)) {
				param_2->retain();
				m_mapper[r] = param_2;
				r->retain();
				p_cArray_robfinished->addObject(r);
			}

			if (p_cArray_customnamefinished->containsObject(r)) {
				p_cArray_customnamefinished->removeObject(r);
				m_mapper[r] = nullptr;
				p_cArray_robfinished->removeObject(r);
				GameLevelManager::onProcessHttpRequestCompleted(param_1, param_2);
				param_2->release();
				return;
			};
		};
	};
};

class $modify(CCHttpClient) {
	void send(CCHttpRequest *req) {
		CCHttpClient::send(req);
		if (req->getType() == (int)GJHttpType::GetGJUserInfo) {
			parseAccount(this,req, parseQuery(req->getRequestData()));
		};
	};
};
#endif
// this network fix would be so scuffed