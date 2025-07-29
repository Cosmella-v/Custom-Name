#include <Geode/Geode.hpp>
using namespace geode::prelude;

$execute {
	Mod *CurrentMod = Mod::get();
	if (CurrentMod->getSavedValue<bool>("username-migrated"))
		return;
	CurrentMod->setSavedValue<bool>("username-migrated", true);
	// check if there is a saved.json
	auto m_saveDirPath = dirs::getModsSaveDir() / "coopeeo.customname";
	if (!std::filesystem::exists(m_saveDirPath))
		return;
	auto settingPath = m_saveDirPath / "settings.json";
	if (std::filesystem::exists(settingPath)) {
		auto res15 = utils::file::readJson(settingPath);
		if (res15.isErr())
			return;
		auto json = std::move(res15).unwrap();
			if (json.get("thename")) {
				CurrentMod->setSettingValue<std::string>("username",json["thename"].asString().unwrapOr("You!"));
			}
	};
}