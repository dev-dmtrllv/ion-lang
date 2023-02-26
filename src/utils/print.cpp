#include "print.hpp"

namespace ion::utils
{
	std::array<const char*, 2> boolStrings = { "true", "false" };

	void print(const char* arg)
	{
		std::printf("%s ", arg);
	}

	void print(std::string_view arg)
	{
		std::printf("%s ", arg.data());
	}

	void print(const std::string& arg)
	{
		std::printf("%s ", arg.c_str());
	}

	void print(std::string&& arg)
	{
		std::printf("%s ", arg.c_str());
	}

	void print(const Path& arg)
	{
		print(std::move(arg.string()));
	}

	void print(bool arg)
	{
		std::printf("%s ", boolStrings[arg]);
	}

	void println(const char* arg)
	{
		std::printf("%s\n", arg);
	}

	void println(std::string_view arg)
	{
		std::printf("%s\n", arg.data());
	}

	void println(const std::string& arg)
	{
		std::printf("%s\n", arg.c_str());
	}

	void println(std::string&& arg)
	{
		std::printf("%s\n", arg.c_str());
	}

	void println(const Path& arg)
	{
		println(arg.string());
	}

	void println(bool arg)
	{
		std::printf("%s\n", boolStrings[arg]);
	}
}