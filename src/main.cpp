#include <Geode/Geode.hpp>
using namespace geode::prelude;
#include <Geode/modify/MenuLayer.hpp>

#define HasupdateUserProfileButton

class $modify(MenuLayerProfileButton,MenuLayer) {
	void UpdateUsername() {
		m_profileLabel->setString(Mod::get()->getSettingValue<std::string>("username").c_str());
		m_profileLabel->limitLabelWidth(70.0,0.7,0.0);
	};
	#ifdef HasupdateUserProfileButton
		void updateUserProfileButton() {
			MenuLayer::updateUserProfileButton();
			UpdateUsername();
		};
	#else
		bool init() {
			if (!MenuLayer::init()) return false;
			UpdateUsername();
			return true;
		}
	#endif
};
