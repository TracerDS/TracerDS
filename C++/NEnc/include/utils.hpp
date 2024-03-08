#pragma once

#include <cstdint>
#include <initializer_list>
#include <algorithm>

namespace NEnc::Utils {
	constexpr std::size_t strlen(const char* str) noexcept {
		auto length = 0;
		for (; str[length]; length++);
		return length;
	}
	constexpr int strcmp(const char* s1, const char* s2) noexcept {
		auto s1Len = strlen(s1);
		auto s2Len = strlen(s2);

		if (s1Len < s2Len) return -1;
		else if (s1Len > s2Len) return 1;

		for (auto i = 0; i < s1Len; i++) {
			if (s1[i] < s2[i]) return -1;
			else if (s1[i] > s2[i]) return 1;
		}
		return 0;
	}

	constexpr bool strcmp(const char* s1, std::initializer_list<const char*>&& s2) noexcept {
		auto s1Len = strlen(s1);
		auto status = false;
		for (auto elem : s2) {
			auto elemLen = strlen(elem);
			if (s1Len != elemLen) {
				status = true;
				continue;
			}
			for (auto i = 0; i < s1Len; i++) {
				if (s1[i] != elem[i]) {
					status = true;
					break;
				}
				status = false;
			}
			if (!status)
				break;
		}
		return status;
	}

	constexpr int strncmp(const char* str1, const char* str2, std::size_t len) noexcept {
		std::uint8_t u1, u2;
		while (len-- > 0) {
			u1 = (std::uint8_t) *str1++;
			u2 = (std::uint8_t) *str2++;
			if (u1 != u2)
				return u1 - u2;
			if (!u1)
				return 0;
		}
		return 0;
	}

	constexpr bool startsWith(const char* str, const char* with) noexcept {
		return strncmp(with, str, strlen(with)) == 0;
	}
	constexpr bool endsWith(const char* str, const char* with) noexcept {
		auto strLen = strlen(str);
		auto withLen = strlen(with);
		if (strLen < withLen) return false;
		return strncmp(str + strLen - withLen, with, withLen) == 0;
	}

	template <std::integral T>
	constexpr std::string to_string(T value) noexcept {
		std::string result;
		if (value == 0) {
			result += '0';
			return result;
		}
		bool inversed = false;
		if (value < 0) {
			inversed = true;
			value = -value;
		}
		while (value > 0) {
			result += '0' + (value % 10);
			value /= 10;
		}

		if (inversed)
			result += '-';

		std::reverse(result.begin(), result.end());
		return result;
	}

	constexpr std::string substr(
		const char* const str1,
		const std::size_t from,
		const std::size_t to = -1
	) noexcept {
		return std::string(str1).substr(from, to == -1 ? to : (to - from));
	}
	constexpr std::string substr(
		const std::string str1,
		const std::size_t from,
		const std::size_t to = -1
	) noexcept {
		return std::string(str1).substr(from, to == -1 ? to : (to - from));
	}
}