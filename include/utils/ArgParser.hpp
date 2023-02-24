#pragma once

#include "pch.hpp"
#include "utils/ErrorOr.hpp"
#include "utils/Maybe.hpp"

namespace ion::utils
{

	class ArgParser
	{
	public:
		ArgParser(int argc, char** argv);

		[[nodiscard]] Path getExecutable() const;
		[[nodiscard]] Maybe<std::string> at(std::size_t index) const;
		[[nodiscard]] bool contains(std::string_view arg) const;
		[[nodiscard]] Maybe<std::string> getFlag(std::string_view arg) const;

	private:
		const std::size_t argc_;
		char* const* const argv_;
	};
}