#include "Generator.hpp"
#include "GeneratorFrame.hpp"

#include <array>
#include <vector>
#include <random>


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
