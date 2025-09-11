#include <Geode/Geode.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include "../api/api.hpp"
using namespace geode::prelude;

class $modify(GJGarageLayer) {
	bool init() {
	    if(!GJGarageLayer::init())
            return false;
        
        m_usernameInput->setString(Viper::CustomName::API::getLocalUsername().c_str());
		return true;
	}
};