#pragma once

#include <lib.hpp>
#include <utils.hpp>
#define ENC_EXTENSION ".nenc"

namespace NEnc {
	constexpr auto VERSION_MAJOR = 1;
	constexpr auto VERSION_MINOR = 0;
	constexpr auto VERSION_FULL = VERSION_MAJOR + VERSION_MINOR / 100.0;
	inline const auto VERSION_STRING = Utils::to_string(VERSION_MAJOR)
		+ "." + Utils::to_string(VERSION_MINOR);
}