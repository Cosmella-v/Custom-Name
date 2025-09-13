#include <Geode/Geode.hpp>
using namespace geode::prelude;
#include <Geode/modify/MenuLayer.hpp>

#include "../api/api.hpp"

#define HasupdateUserProfileButton

class $modify(MenuLayerProfileButton,MenuLayer) {
	void UpdateUsername() {
		m_profileLabel->setString(Viper::CustomName::API::getLocalUsername().c_str());
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
//#define __limitLabelWidth_FINDER
#ifdef __limitLabelWidth_FINDER
#include <Geode/modify/CCLabelBMFont.hpp>
class $modify(CCLabelBMFont_SickandTwistedFinder,CCLabelBMFont) {
	void limitLabelWidth(float width, float defaultScale, float minScale) {
		log::debug("FROM {} :Width {}, defaultScale: {}, minScale: {}",this->getString(),width,defaultScale,minScale);
		//this->setUserObject("LabelWidthText",CCString::create(fmt::format("Width {}, defaultScale: {}, minScale: {}",width,defaultScale,minScale)));
		CCLabelBMFont::limitLabelWidth(width,defaultScale,minScale);
	};
};
#endif