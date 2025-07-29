#include <Geode/Geode.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include "Override.hpp"
using namespace geode::prelude;

class $modify(LevelInfoLayer) {
    void levelUpdateFinished(GJGameLevel* p0, UpdateResponse p1) {
        if (p0->m_accountID != GJAccountManager::get()->m_accountID) return LevelInfoLayer::levelUpdateFinished(p0, p1);
        SpoofLevel(p0, LevelInfoLayer::levelUpdateFinished(p0, p1), old);
		return;
    }
	bool init(GJGameLevel* p0, bool p1) {
        if (p0->m_accountID != GJAccountManager::get()->m_accountID) return LevelInfoLayer::init(p0, p1);
        SpoofLevelInit(p0, LevelInfoLayer::init(p0, p1), old,bool Output);
		return Output;
	}
};