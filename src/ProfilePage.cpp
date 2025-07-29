
#include <Geode/Geode.hpp>
using namespace geode::prelude;
#include <Geode/modify/ProfilePage.hpp>

class $modify(ProfilePage) {
      bool init(int accountID, bool ownProfile) {
        if (!ProfilePage::init(accountID, ownProfile)) return false;
        if (accountID == GJAccountManager::get()->m_accountID) m_usernameLabel->setString(Mod::get()->getSettingValue<std::string>("username").c_str());
        return true;
      }
	void loadPageFromUserInfo(GJUserScore* p0) {
    if (p0->m_accountID == GJAccountManager::get()->m_accountID) p0->m_userName = Mod::get()->getSettingValue<std::string>("username");
		ProfilePage::loadPageFromUserInfo(p0);
	};
    void getUserInfoFinished(GJUserScore* p0) {
    if (p0->m_accountID == GJAccountManager::get()->m_accountID) p0->m_userName = Mod::get()->getSettingValue<std::string>("username");
		ProfilePage::getUserInfoFinished(p0);
    }
    void userInfoChanged(GJUserScore* p0) {
    if (p0->m_accountID == GJAccountManager::get()->m_accountID) p0->m_userName = Mod::get()->getSettingValue<std::string>("username");
		ProfilePage::userInfoChanged(p0);
    }
};
