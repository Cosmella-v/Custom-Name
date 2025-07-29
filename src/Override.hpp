#ifndef SpoofLevel
#define SpoofLevel(level,function,d) auto d = level->m_creatorName; \
		level->m_creatorName = Mod::get()->getSettingValue<std::string>("username"); \
        function; \
        level->m_creatorName = old;

#define SpoofLevelInit(level,function,d,Output) auto d = level->m_creatorName; \
		level->m_creatorName = Mod::get()->getSettingValue<std::string>("username"); \
        Output = function; \
        level->m_creatorName = old; 
#endif