#include <Geode/Geode.hpp>
#include <Geode/modify/LevelCell.hpp>
#include "Override.hpp"
using namespace geode::prelude;

class $modify(LevelCell) {
    bool init() {
        if (m_level) {
            if (m_level->m_accountID != GJAccountManager::get()->m_accountID) return LevelCell::init();
            SpoofLevelInit(m_level, LevelCell::init(), old,bool Output);
            return Output;
        }
        return LevelCell::init();
    }
    void loadFromLevel(GJGameLevel* p0) {
        if (p0->m_accountID != GJAccountManager::get()->m_accountID) return LevelCell::loadFromLevel(p0);
        SpoofLevel(p0, LevelCell::loadFromLevel(p0), old);
    }
};