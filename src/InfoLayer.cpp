#include <Geode/Geode.hpp>
#include <Geode/modify/InfoLayer.hpp>
#include "../api/api.hpp"
using namespace geode::prelude;

class $modify(InfoLayer) {

    bool init(GJGameLevel* p0, GJUserScore* p1, GJLevelList* p2) {
        std::string UsernameGJLEVEL = "";
        std::string UsernameGJScore = "";
        if (p0) {
            UsernameGJLEVEL = p0->m_creatorName ;
            p0->m_creatorName = Viper::CustomName::API::getNameFromAccountID(p0->m_accountID,UsernameGJLEVEL);
        }
       // if (p1) {
        //    UsernameGJScore = p1->m_userName;
       //     p1->m_userName = Viper::CustomName::API::getNameFromAccountID(p0->m_accountID,UsernameGJScore);
       // }
        bool out = InfoLayer::init(p0, p1, p2);
        if (!UsernameGJLEVEL.empty())  p0->m_creatorName = UsernameGJLEVEL;
        if (!UsernameGJScore.empty())  p1->m_userName = UsernameGJScore;
        return out;
	}
};