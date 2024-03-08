#include <main.hpp>

#include <fstream>
#include <random>
#include <concepts>
#include <cmath>
#include <sstream>
#include <filesystem>
#include <iostream>

namespace NEnc {
	namespace Core {
		namespace detail {
			inline std::random_device RandomNumberGenerator;
			inline std::mt19937 RandomEngine(RandomNumberGenerator());
		}

		template <std::integral T>
		T generateRandom(const T from, const T to) noexcept {
			return std::uniform_int_distribution<T>(from, to)(detail::RandomEngine);
		}

		template <std::floating_point T>
		T generateRandom(const T from, const T to) noexcept {
			return std::uniform_real_distribution<T>(from, to)(detail::RandomEngine);
		}

		template <std::integral T>
		std::string intToHex(T num) noexcept {
			std::stringstream stream;
			stream << std::hex << num;
			return stream.str();
		}
	}

	template <std::integral T>
	std::string generateKey(const T size) noexcept {
		std::string key;
		key.reserve(size * 2);
		for (auto i = 0; i < size; i++) {
			key += Core::intToHex(Core::generateRandom(0x00, 0xFF));
		}
		return key;
	}

	std::string GenerateEncryptKey(const std::uint64_t size) noexcept {
		return generateKey(size);
	}

	std::vector<std::uint8_t> ReadFile(const std::filesystem::path filename) noexcept {
		std::ifstream file(filename, std::ios::binary);
		if (!file) 
			return {};

		// Stop eating new lines in binary mode!!!
		file.unsetf(std::ios::skipws);

		file.seekg(0, std::ios::end);
		std::uint64_t fileSize = 0;
		fileSize = file.tellg();
		file.seekg(0, std::ios::beg);

		// reserve capacity
		std::vector<std::uint8_t> vec;
		vec.reserve(fileSize);

		// read the data:
		try {
			vec.insert(vec.begin(),
				std::istream_iterator<std::uint8_t>(file),
				std::istream_iterator<std::uint8_t>());
		} catch (...) {}

		return vec;
	}

	// ---------------------------------------- \\

	std::vector<std::uint8_t> EncryptData(
		const std::vector<std::uint8_t> data,
		const std::string_view key
	) noexcept {
		std::vector<std::uint8_t> encrypted;
		encrypted.reserve(data.size());

		for (auto i = 0; i < data.size(); i++) {
			encrypted.push_back(data[i] ^ key[i % key.size()]);
		}
		return encrypted;
	}
	
	std::vector<std::uint8_t> EncryptData(
		const std::string_view data,
		const std::string_view key
	) noexcept {
		return EncryptData(std::vector<uint8_t>(data.begin(), data.end()), key);
	}

	bool EncryptFile(
		const std::string filename,
		const std::string_view key
	) noexcept {
		std::error_code err;
		std::filesystem::path filenamePath(filename);
		std::filesystem::path encryptedFilePath = filenamePath.string() + ENC_EXTENSION;

		auto fileData = ReadFile(filenamePath);

		std::ofstream file(encryptedFilePath, std::ios::out | std::ios::binary);
		if (!file) return false;

		auto encryptedData = EncryptData(fileData, key);
		file.write(reinterpret_cast<const char*>(encryptedData.data()), fileData.size());
		file.close();

		std::filesystem::remove(filenamePath, err);

		return true;
	}

	bool DecryptFile(
		const std::string filename,
		const std::string_view key
	) noexcept {
		std::error_code err;
		std::filesystem::path filenamePath(filename);
		std::filesystem::path decryptedFilePath = filenamePath.stem().string();

		auto fileData = ReadFile(filenamePath);
		std::filesystem::remove(filenamePath, err);

		std::ofstream file(decryptedFilePath, std::ios::out | std::ios::binary);
		if (!file) return false;

		auto decryptedData = DecryptData(fileData, key);
		file.write(reinterpret_cast<const char*>(decryptedData.data()), fileData.size());
		file.close();

		return true;
	}


	std::vector<std::uint8_t> DecryptData(
		const std::vector<std::uint8_t> data,
		const std::string_view key
	) noexcept {
		return EncryptData(data, key);
	}

	std::vector<std::uint8_t> DecryptData(
		const std::string_view data,
		const std::string_view key
	) noexcept {
		return EncryptData(data, key);
	}
}