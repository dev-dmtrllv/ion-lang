#include "utils/ArgParser.hpp"

namespace ion::utils
{
	ArgParser::ArgParser(int argc, char** argv):
		argc_(static_cast<std::size_t>(argc)),
		argv_(argv)
	{ }

	[[nodiscard]] Path ArgParser::getExecutable() const
	{
		return argv_[0];
	}

	[[nodiscard]] Maybe<std::string> ArgParser::at(std::size_t index) const
	{
		index++;
		if(index < argc_)
			return argv_[index];
		return {};
	}

	[[nodiscard]] bool ArgParser::contains(std::string_view arg) const
	{
		for (int i = 0; i != argc_; i++)
			if (arg.compare(argv_[i]) == 0)
				return true;
		return false;
	}

	[[nodiscard]] Maybe<std::string> ArgParser::getFlag(std::string_view arg) const
	{
		for (int i = 0; i != argc_; i++)
			if (arg.compare(argv_[i]) == 0)
				return argv_[i];
		return {};
	}
}