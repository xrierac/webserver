#pragma once
#include <array>
#include <cstdint>

class CharacterTypes {
	private:
		static constexpr uint8_t TOKEN = 1 << 0;
		static constexpr uint8_t URI = 1 << 1;
		static constexpr uint8_t HEADER = 1 << 2;
		static constexpr uint8_t VALUE = 1 << 3;
		static constexpr uint8_t HEX = 1 << 4;
		static constexpr uint8_t DIGIT = 1 << 5;
		static constexpr uint8_t SEPARATOR = 1 << 6;
		static constexpr std::array<uint8_t, 256> createCharacterTable();
};
