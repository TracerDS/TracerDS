#include <main.hpp>
#include <iostream>
#include <filesystem>

void printUsage() noexcept;
void printVersion() noexcept;

int main(int argc, const char* argv[]) {
	std::cout <<
		"//----------------------------------\\\\" "\n"
		"|| NEnc - Copyright 2024 (c) Tracer ||" "\n"
		"\\\\----------------------------------//" "\n"
		<< std::endl;

	std::vector<const char*> files;
	std::string key;

	enum class Mode{
		NONE,
		ENCRYPT,
		DECRYPT,
	} mode = Mode::NONE;

	for (auto i = 1; i < argc; i++) {
		if (!NEnc::Utils::startsWith(argv[i], "-")) {
			files.push_back(argv[i]);
			continue;
		}
		if (!NEnc::Utils::strcmp(argv[i], { "-h", "--help" })) {
			printUsage();
			return 0;
		}
		if (!NEnc::Utils::strcmp(argv[i], { "-v", "--version" })) {
			printVersion();
			return 0;
		}
		if (!NEnc::Utils::strcmp(argv[i], { "-e", "--encrypt" })) {
			mode = Mode::ENCRYPT;
			continue;
		}
		if (!NEnc::Utils::strcmp(argv[i], { "-d", "--decrypt" })) {
			mode = Mode::DECRYPT;
			continue;
		}
		if (!NEnc::Utils::strcmp(argv[i], "-k")) {
			if (i == argc - 1) {
				std::cerr << "No key provided!" << std::endl;
				return 1;
			}
			key = argv[++i];
			continue;
		}
		if (NEnc::Utils::startsWith(argv[i], "--key=")) {
			key = NEnc::Utils::substr(argv[i], 6);
			if (key.empty()) {
				std::cerr << "No key provided!" << std::endl;
				return 1;
			}
			continue;
		}
		if (!NEnc::Utils::strcmp(argv[i], "-gk")) {
			if (i == argc - 1) {
				std::cerr << "No key size provided!" << std::endl;
				return 1;
			}
			try {
				key = NEnc::GenerateEncryptKey(std::stoull(argv[++i]));
			} catch (...) {
				std::cerr << "That's not a valid key size! "
					"Value must be a number" << std::endl;
				return 1;
			}
			continue;
		}
		if (!NEnc::Utils::strcmp(argv[i], "--generate-key=")) {
			auto keySize = NEnc::Utils::substr(argv[i], 15);
			if (keySize.empty()) {
				std::cerr << "No key size provided!" << std::endl;
				return 1;
			}
			try {
				key = NEnc::GenerateEncryptKey(std::stoull(keySize));
			} catch (...) {
				std::cerr << "That's not a valid key size! "
					"Value must be a number" << std::endl;
				return 1;
			}
			continue;
		}
	}

	if (key.empty()) key = NEnc::GenerateEncryptKey(64);

	if (mode == Mode::NONE) {
		printUsage();
		return 0;
	}


	std::cout << R"ASCII(
  _   _  _         _      _    ______                                   _               
 | \ | |(_)       | |    | |  |  ____|                                 | |              
 |  \| | _   __ _ | |__  | |_ | |__    _ __    ___  _ __  _   _  _ __  | |_  ___   _ __ 
 | . ` || | / _` || '_ \ | __||  __|  | '_ \  / __|| '__|| | | || '_ \ | __|/ _ \ | '__|
 | |\  || || (_| || | | || |_ | |____ | | | || (__ | |   | |_| || |_) || |_| (_) || |   
 |_| \_||_| \__, ||_| |_| \__||______||_| |_| \___||_|    \__, || .__/  \__|\___/ |_|   
             __/ |                                         __/ || |                     
            |___/                                         |___/ |_|                                     
		)ASCII" << std::endl;
	std::cout << "Your encryption key: \n"
		<< key <<
		"\nStore it somewhere or you WILL lose your data.\n"
	<< std::endl;

	switch (mode) {
		case Mode::ENCRYPT:
			for (const auto& file : files) {
				if (!std::filesystem::exists(file)) {
					std::cerr << "File \"" << file << "\" doesn't exist!" << std::endl;
					continue;
				}
				if (!NEnc::EncryptFile(file, key)) {
					std::cerr << "Cannot encrypt file \"" << file << "\"" << std::endl;
					continue;
				}
				std::cout << "Encrypted \"" << file << "\"" << std::endl;
			}
			break;
		case Mode::DECRYPT:
			for (const auto& file : files) {
				if (!std::filesystem::exists(file)) {
					std::cerr << "File \"" << file << "\" doesn't exist!" << std::endl;
					continue;
				}
				if (!NEnc::Utils::endsWith(file, ENC_EXTENSION)) {
					std::cerr << "File \"" << file << "\" is not encrypted!" << std::endl;
					continue;
				}
				if (!NEnc::DecryptFile(file, key)) {
					std::cerr << "Cannot decrypt file \"" << file << "\"" << std::endl;
					continue;
				}
				std::cout << "Decrypted \"" << file << "\"" << std::endl;
			}
			break;
	}
}

void printUsage() noexcept {
	std::cout <<
		"  -h, --help                 " "Help manual" "\n"
		"  -v, --version              " "Show version number" "\n"
		"  -e, --encrypt              " "Encrypt a file" "\n"
		"  -d, --decrypt              " "Decrypt a file" "\n"
		"  -k, --key=<key>            " "Encryption key. Random if not provided" "\n"
		"  -gk, --generate-key=<size> " "Generate encryption key with specified size" "\n"
	<< std::endl;
}

void printVersion() noexcept {
	std::cout << "NEnc v" << NEnc::VERSION_STRING << std::endl;
}