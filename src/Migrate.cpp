#include <Geode/Geode.hpp>
using namespace geode::prelude;

$execute {
	Mod *CurrentMod = Mod::get();
	if (CurrentMod->getSavedValue<bool>("username-migrated"))
		return;
	CurrentMod->setSavedValue<bool>("username-migrated", true);
	
	auto res15 = utils::file::readJson(dirs::getModsSaveDir() / "coopeeo.customname" / "settings.json");
	if (res15.isErr())
		return;
	auto json = std::move(res15).unwrap();
	if (json.get("thename")) {
		CurrentMod->setSettingValue<std::string>("username", json["thename"].asString().unwrapOr("You!"));
	}
}