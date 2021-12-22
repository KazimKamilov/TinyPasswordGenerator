#ifndef _TINY_PASSWORD_GENERATOR_HPP_
#define _TINY_PASSWORD_GENERATOR_HPP_

#include <string>

class GeneratorFrame;

class Generator final
{
public:
	Generator(GeneratorFrame* frame) noexcept;
	~Generator() = default;

	std::string make();

private:
	GeneratorFrame* _frame = nullptr;

};

#endif
