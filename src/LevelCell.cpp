#include <Geode/Geode.hpp>
#include <Geode/modify/LevelCell.hpp>
using namespace geode::prelude;
#include "../api/api.hpp"

class $modify(LevelCell) {
    void loadFromLevel(GJGameLevel* p0) {
        auto oldn = p0->m_creatorName;
        p0->m_creatorName =  Viper::CustomName::API::getNameFromAccountID(p0->m_accountID, oldn);
        LevelCell::loadFromLevel(p0); 
        p0->m_creatorName = oldn;
    }
};