#include <Geode/Geode.hpp>
#include <Geode/modify/InfoLayer.hpp>
#include "Override.hpp"
using namespace geode::prelude;

class $modify(InfoLayer) {

    bool init(GJGameLevel* p0, GJUserScore* p1, GJLevelList* p2) {
        std::string UsernameGJLEVEL = "";
        std::string UsernameGJScore = "";
        int accountID = GJAccountManager::get()->m_accountID;
        if (p0) {
            if (p0->m_accountID == accountID) {
                UsernameGJLEVEL = p0->m_creatorName ;
                p0->m_creatorName = Mod::get()->getSettingValue<std::string>("username");
            }
        }
        if (p1) {
            if (p1->m_accountID == accountID) { 
                UsernameGJScore = p1->m_userName ;
                p1->m_userName = Mod::get()->getSettingValue<std::string>("username");
            }
        }
        bool out = InfoLayer::init(p0, p1, p2);
        if (!UsernameGJLEVEL.empty())  p0->m_creatorName = UsernameGJLEVEL;
        if (!UsernameGJScore.empty())  p1->m_userName = UsernameGJScore;
        return out;
	}
};