#pragma once
#include "platform.h"
#include "stdint.h"
#include "utils/module.h"
#include "utlstring.h"


struct Signature {
	const char *data = nullptr;
	size_t length = 0;

	template<size_t N>
	Signature(const char(&str)[N]) {
		data = str;
		length = N - 1;
	}
};
#define DECLARE_SIG(name, sig) inline const Signature name = Signature(sig);

namespace modules
{
	inline CModule *tier0;
	void Initialize();
}

namespace sigs
{
#ifdef _WIN32
	DECLARE_SIG(iLoggingSystem_IsChannelEnabled, "\x4C\x8D\x05\x2A\x2A\x2A\x2A\x83\xFA\x05");
#else
	DECLARE_SIG(iLoggingSystem_IsChannelEnabled, "\x31\xD2\x83\xFE\x05");
#endif
}