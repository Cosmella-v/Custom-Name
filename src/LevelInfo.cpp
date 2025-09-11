#include <Geode/Geode.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
using namespace geode::prelude;
#include "../api/api.hpp"
class $modify(LevelInfoLayer) {
    void levelUpdateFinished(GJGameLevel* p0, UpdateResponse p1) {
        auto oldn = p0->m_creatorName;
        p0->m_creatorName =  Viper::CustomName::API::getNameFromAccountID(p0->m_accountID, oldn);
        LevelInfoLayer::levelUpdateFinished(p0, p1); 
        p0->m_creatorName = oldn;
		return;
    }
	bool init(GJGameLevel* p0, bool p1) {
        auto oldn = p0->m_creatorName;
        p0->m_creatorName =  Viper::CustomName::API::getNameFromAccountID(p0->m_accountID, oldn);
        bool Output = LevelInfoLayer::init(p0, p1); 
        p0->m_creatorName = oldn;
		return Output;
	}
};