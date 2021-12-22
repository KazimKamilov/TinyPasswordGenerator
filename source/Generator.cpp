#include "Generator.hpp"
#include "GeneratorFrame.hpp"

#include <array>
#include <vector>
#include <random>


static constexpr std::array<char, 62u> CHARACTERS
{
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
	0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A,
	0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A
};

inline std::vector<char> make_array(const std::vector<std::pair<char, char>>& character_range_pairs, const std::vector<char>& other_characters = {})
{
	std::vector<char> result;

	for (const auto& pair : character_range_pairs)
	{
		if (pair.second <= pair.first)
			continue;

		const uint32_t count = (pair.second - pair.first) + 1u;

		for (uint32_t i = static_cast<uint32_t>(pair.first); i < (static_cast<uint32_t>(pair.second) + 1u); ++i)
			result.push_back(static_cast<char>(i));
	}

	if (!other_characters.empty())
	{
		for(const auto& character : other_characters)
			result.push_back(character);
	}

	std::shuffle(result.begin(), result.end(), std::default_random_engine {});

	return result;
}

Generator::Generator(GeneratorFrame* frame) noexcept :
	_frame(frame)
{
}

std::string Generator::make()
{
	const auto RandomChar = [](const std::vector<char>& characters) -> const char
	{
		std::random_device device;
		std::default_random_engine generator(device());
		std::uniform_int_distribution<uint16_t> random(0u, static_cast<uint16_t>(characters.size() - 1u));

		return characters[random(generator)];
	};

	const auto RandomSymbol = [this]() -> const char
	{
		const auto symbols = _frame->getSpecialSymbols();

		if (symbols.empty())
			return '*';

		std::random_device device;
		std::default_random_engine generator(device());
		std::uniform_int_distribution<uint16_t> random(0u, static_cast<uint16_t>(symbols.size() - 1u));

		const auto index = random(generator);
		const auto character = symbols[index];
		return character;
	};

	const auto RandomAny = [&]() -> const char
	{
		const auto symbols = _frame->getSpecialSymbols();

		const auto& symbols_array = make_array({{'0', '9'}, {'A', 'Z'}, {'a', 'z'}}, {symbols.cbegin(), symbols.cend()});

		std::random_device device;
		std::default_random_engine generator(device());
		std::uniform_int_distribution<uint16_t> random(0u, static_cast<uint16_t>(symbols_array.size() - 1u));

		const auto index = random(generator);
		const auto character = symbols_array[index];
		return character;
	};

	// XD
	std::string password(static_cast<size_t>(_frame->getPasswordLength()), '*');

	const auto mode = _frame->getGeneratorMode();

	switch (mode)
	{
		case GeneratorMode::NUMBERS:
		{
			for (auto& character : password)
				character = RandomChar(make_array({{'0', '9'}}));
		}
		break;

		case GeneratorMode::LOWCASE_LETTERS:
		{
			for (auto& character : password)
				character = RandomChar(make_array({{'a', 'z'}}));
		}
		break;

		case GeneratorMode::UPPERCASE_LETTERS:
		{
			for (auto& character : password)
				character = RandomChar(make_array({{'A', 'Z'}}));
		}
		break;

		case GeneratorMode::SPECIAL_SYMBOLS:
		{
			for (auto& character : password)
				character = RandomSymbol();
		}
		break;

		case GeneratorMode::JUST_LETTERS:
		{
			for (auto& character : password)
				character = RandomChar(make_array({{'A', 'Z'}, {'a', 'z'}}));
		}
		break;

		case GeneratorMode::LOWCASE_LETTERS_AND_NUMBERS:
		{
			for (auto& character : password)
				character = RandomChar(make_array({{'0', '9'}, {'a', 'z'}}));
		}
		break;

		case GeneratorMode::UPPERCASE_LETTERS_AND_NUMBERS:
		{
			for (auto& character : password)
				character = RandomChar(make_array({{'0', '9'}, { 'A', 'Z' }}));
		}
		break;

		case GeneratorMode::LETTERS_AND_NUMBERS:
		{
			for (auto& character : password)
				character = RandomChar(make_array({{'0', '9'}, {'A', 'Z'}, {'a', 'z'}}));
		}
		break;

		case GeneratorMode::ALL:
		{
			for (auto& character : password)
				character = RandomAny();
		}
		break;

		default:
		break;
	}

	return password;
}
