#pragma once

#include <vector>
#include <string>

namespace NEnc {
	std::string GenerateEncryptKey(const std::uint64_t size) noexcept;

	std::vector<std::uint8_t> EncryptData(
		const std::vector<std::uint8_t> data,
		const std::string_view key
	) noexcept;

	std::vector<std::uint8_t> EncryptData(
		const std::string_view data,
		const std::string_view key
	) noexcept;

	bool EncryptFile(
		const std::string filename,
		const std::string_view key
	) noexcept;

	bool DecryptFile(
		const std::string filename,
		const std::string_view key
	) noexcept;

	std::vector<std::uint8_t> DecryptData(
		const std::vector<std::uint8_t> data,
		const std::string_view key
	) noexcept;

	std::vector<std::uint8_t> DecryptData(
		const std::string_view data,
		const std::string_view key
	) noexcept;
}