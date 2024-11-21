#include "CharacterTypes.hpp"

constexpr std::array<uint8_t, 256> CharacterTypes::createCharacterTable()
{
	std::array<uint8_t, 256> table = {};

	for (int i = 0; i < 256; i++)
	{
		unsigned char c = static_cast<unsigned char>(i);
		uint8_t& flags = table[i];
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		{
			flags |= TOKEN;
			flags |= URI;
			flags |= HEADER;
			flags |= VALUE;
			if ((c <= 'F') || (c >= 'a' && c <= 'f'))
				flags |= HEX;
		} else if ((c >= '0' && c <= '9'))
		{
			flags |= TOKEN;
			flags |= URI;
			flags |= HEADER;
			flags |= VALUE;
			flags |= DIGIT;
			flags |= HEX;
		} else if (c == '!' || c == '#' || c == '$' || c == '%' || c == '&' ||
                c == '\'' || c == '*' || c == '+' || c == '-' || c == '.' ||
                c == '^' || c == '_' || c == '`' || c == '|' || c == '~')
		{
			flags |= TOKEN;
			flags |= URI;
			flags |= HEADER;
			flags |= VALUE;
		} else if (c == ':' || c == '/' || c == '?' || c == '#' ||
                c == '[' || c == ']' || c == '@' ||
                c == '(' || c == ')' || c == ',' || c == ';' ||
                c == '=')
		{
            flags |= CharacterTypes::URI;
            flags |= CharacterTypes::VALUE;
            flags |= CharacterTypes::SEPARATOR;
        } else if (c == ' ' || c == '\t')
        {
            flags |= CharacterTypes::VALUE;
            flags |= CharacterTypes::SEPARATOR;
        } else if (c >= 33 && c <= 126)
        {
            flags |= CharacterTypes::VALUE;
        } else if (c >= 0x80) {
            flags |= CharacterTypes::VALUE;
        }
	}
	return table;
}
