#pragma once

#include "pch.hpp"

namespace ion::utils
{
	struct Error: public std::exception
	{
		Error(const std::string& str): std::exception(str.data())
		{ }

		Error(const Path& path): std::exception(path.string().data())
		{ }

		template<typename T>
		Error(T other): std::exception(std::to_string(other).c_str())
		{ }
	};
}