
#include <Geode/Geode.hpp>
using namespace geode::prelude;
#include <Geode/modify/SecretLayer2.hpp>
#include <iostream>
#include "../api/api.hpp"
#include <string>

class $modify(SecretLayer2) {
    static void onModify(auto& self) {
        if (!self.setHookPriority("SecretLayer2::updateMessageLabel", Priority::First)) {
            log::warn("Failed to set SecretLayer2::updateMessageLabel hook priority, mod may break with other ones");
        }
    }
	std::string replaceUsername(std::string text, const std::string &pattern, const std::string &replace) {
		size_t pos = 0;

		while ((pos = text.find(pattern, pos)) != std::string::npos) {
			size_t endPos = pos + pattern.size();
			std::string suffix;

			if (endPos + 2 <= text.size() && text.substr(endPos, 3) == "'s ") {
				suffix = "'s ";
				endPos += 3;
			} else if (endPos + 1 <= text.size() && text.substr(endPos, 2) == "' ") {
				suffix = "' ";
				endPos += 2;
			} else if (endPos < text.size() && (text[endPos] == ' ' || text[endPos] == ',' ) ) {
				suffix = " ";
				endPos += 1;
			} else {
				pos += pattern.size();
				continue;
			}
			text.replace(pos, endPos - pos, replace + suffix);
			pos += replace.size() + suffix.size();
		}

		return text;
	}
	void updateMessageLabel(gd::string p0) {
		if (auto val = Viper::CustomName::API::getLocalUsername(); val != GJAccountManager::get()->m_username) p0 = replaceUsername(p0,GJAccountManager::get()->m_username,val);
        SecretLayer2::updateMessageLabel(p0);
	}
};
