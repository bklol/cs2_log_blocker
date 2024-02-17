#include "cs2_log_block.h"

#include "utils/addresses.h"
#include "tier0/memdbgon.h"
#include "utils/cdetour.h"

cs2_log_block g_cs2_log_block;
CUtlVector<CDetourBase*> g_vecDetours;

#define DECLARE_SERVER_DETOUR(name) DECLARE_DETOUR(name, BaseDetour::Detour_##name, &modules::tier0);
#define DECLARE_SERVER_EXTERN_DETOUR(name) extern CDetour<decltype(BaseDetour::Detour_##name)> name;

namespace BaseDetour
{
	bool FASTCALL Detour_iLoggingSystem_IsChannelEnabled(int channelID, int severity);
}

DECLARE_SERVER_EXTERN_DETOUR(iLoggingSystem_IsChannelEnabled);
DECLARE_SERVER_DETOUR(iLoggingSystem_IsChannelEnabled);

PLUGIN_EXPOSE(cs2_log_block, g_cs2_log_block);

bool cs2_log_block::Load(PluginId id, ISmmAPI *ismm, char *error, size_t maxlen, bool late)
{
	PLUGIN_SAVEVARS();
	modules::tier0 = new CModule(ROOTBIN, "tier0");
	INIT_DETOUR(iLoggingSystem_IsChannelEnabled);
	return true;
}

bool FASTCALL BaseDetour::Detour_iLoggingSystem_IsChannelEnabled(int channelID, int severity)
{
#ifdef _WIN32
	if((channelID == 41 || channelID == 39) && severity == 2)
#else
	if((channelID == 33 || channelID == 13) && severity == 2)
#endif
		return true;
	return false;
}

bool cs2_log_block::Unload(char *error, size_t maxlen)
{	
	return true;
}

void cs2_log_block::AllPluginsLoaded()
{
}

bool cs2_log_block::Pause(char *error, size_t maxlen)
{
	return true;
}

bool cs2_log_block::Unpause(char *error, size_t maxlen)
{
	return true;
}

const char *cs2_log_block::GetLicense()
{
	return "";
}

const char *cs2_log_block::GetVersion()
{
	return "1.0.0";
}

const char *cs2_log_block::GetDate()
{
	return __DATE__;
}

const char *cs2_log_block::GetLogTag()
{
	return "cs2_log_block";
}

const char *cs2_log_block::GetAuthor()
{
	return "bklol";
}

const char *cs2_log_block::GetDescription()
{
	return "cs2_log_block";
}

const char *cs2_log_block::GetName()
{
	return "cs2_log_block";
}

const char *cs2_log_block::GetURL()
{
	return "";
}
