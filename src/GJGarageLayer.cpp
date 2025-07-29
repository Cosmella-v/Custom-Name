#include <Geode/Geode.hpp>
#include <Geode/modify/GJGarageLayer.hpp>

using namespace geode::prelude;

class $modify(GJGarageLayer) {
	bool init() {
	    if(!GJGarageLayer::init())
            return false;
        
        m_usernameInput->setString(Mod::get()->getSettingValue<std::string>("username").c_str());
		return true;
	}
};