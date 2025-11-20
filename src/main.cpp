#include <Geode/Geode.hpp>
using namespace geode::prelude;
#include <Geode/modify/MenuLayer.hpp>

#include "../api/api.hpp"

#define HasupdateUserProfileButton

class $modify(MenuLayerProfileButton, MenuLayer) {
	void ModCompact() {
		geode::Loader *loader = geode::Loader::get();
		if (loader->getLoadedMod("ninxout.redash"))
			if (auto bottomMenu = this->getChildByIDRecursive("ninxout.redash/bottom-menu-bg")) {
				m_profileLabel->setScale(m_profileLabel->getScale() - 0.1f);
				m_profileLabel->setPositionX(bottomMenu->getPositionX());
				m_profileLabel->setPositionY(bottomMenu->getPositionY() - bottomMenu->getScaledContentHeight() / 2 - m_profileLabel->getScaledContentHeight() / 2 + 2.9f);
				if (m_profileLabel->getScaledContentWidth() > 54.f) {
					m_profileLabel->setScale(54.f / m_profileLabel->getContentWidth());
				}
			}
	}
	void UpdateUsername() {
		m_profileLabel->setString(Viper::CustomName::API::getLocalUsername().c_str());
		m_profileLabel->limitLabelWidth(70.0, 0.7, 0.0);
		// some mods modify the limitLabelWidth in init rather then updateUserProfileButton
		// so i run the normal code then i redo what they do to match, might bugfix a mod as well lol with username updates
		ModCompact();
	};
#ifdef HasupdateUserProfileButton
	void updateUserProfileButton() {
		MenuLayer::updateUserProfileButton();
		UpdateUsername();
	};
#else
	bool init() {
		if (!MenuLayer::init())
			return false;
		UpdateUsername();
		return true;
	}
#endif
};
// #define __limitLabelWidth_FINDER
#ifdef __limitLabelWidth_FINDER
#include <Geode/modify/CCLabelBMFont.hpp>
class $modify(CCLabelBMFont_SickandTwistedFinder, CCLabelBMFont) {
	void limitLabelWidth(float width, float defaultScale, float minScale) {
		log::debug("FROM {} :Width {}, defaultScale: {}, minScale: {}", this->getString(), width, defaultScale, minScale);
		// this->setUserObject("LabelWidthText",CCString::create(fmt::format("Width {}, defaultScale: {}, minScale: {}",width,defaultScale,minScale)));
		CCLabelBMFont::limitLabelWidth(width, defaultScale, minScale);
	};
};
#endif