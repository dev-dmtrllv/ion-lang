#pragma once

#include "pch.hpp"

namespace ion::utils
{
	class ArgParser
	{
	public:
		ArgParser(int argc, char** argv);

		[[nodiscard]] Path getExecutable() const;
		[[nodiscard]] std::optional<std::string> at(std::size_t index) const;
		[[nodiscard]] bool contains(std::string_view arg) const;
		[[nodiscard]] std::optional<std::string> getFlag(std::string_view arg) const;

	private:
		const std::size_t argc_;
		char* const* const argv_;
	};
}