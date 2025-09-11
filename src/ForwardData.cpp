#include <Geode/Geode.hpp>
#include "../api/api.hpp"

#include <hiimjasmine00.user_data_api/include/Events.hpp>
#define USER_DATA_API_EVENTS
#include <hiimjasmine00.user_data_api/include/UserDataAPI.hpp>

using namespace geode::prelude;

auto saved = matjson::makeObject({});
void SendData() {
	if (Viper::CustomName::API::hiimjasmine00::user_data_api::isLoaded()) {
		user_data::upload(saved);
	};
};

void initSettingsHooks() {
	if (Viper::CustomName::API::enabledLocally()) {
		saved["name"] = Viper::CustomName::API::self()->getSettingValue<std::string>("username");
	};
	listenForSettingChanges("username", [](std::string nom) {
		if (Viper::CustomName::API::enabledLocally()) {
			saved["name"] = nom;
			SendData();
		};
	});
	listenForSettingChanges("mod-toggled", [](bool enabled){
		if (enabled) {
			saved["name"] = Viper::CustomName::API::self()->getSettingValue<std::string>("username");
		} else {
			saved = matjson::makeObject({});
		}
		SendData();
	});
	Viper::CustomName::API::hiimjasmine00::user_data_api::waitforMod([=]{
		SendData();
	});
};

void PortName() {
	if (Viper::CustomName::API::self()->getSavedValue<bool>("username-migrated"))
		return;
	Viper::CustomName::API::self()->setSavedValue<bool>("username-migrated", true);
	
	auto res15 = utils::file::readJson(dirs::getModsSaveDir() / "coopeeo.customname" / "settings.json");
	if (res15.isErr())
		return;
	auto json = std::move(res15).unwrap();
	if (json.get("thename")) {
		Viper::CustomName::API::self()->setSettingValue<std::string>("username", json["thename"].asString().unwrapOr("You!"));
	}
}
$execute {
	PortName();
	initSettingsHooks();
}
