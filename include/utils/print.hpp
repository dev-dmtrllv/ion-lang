#pragma once

#include "pch.hpp"

namespace ion::utils
{
	void print(const char* arg);
	void print(std::string_view arg);
	void print(const std::string& arg);
	void print(std::string&& arg);
	void print(const Path& arg);
	void print(bool arg);

	template<typename T>
	void print(const T& arg)
	{
		print(std::to_string(arg));
	}

	template<typename T>
	void print(T&& arg)
	{
		print(std::to_string(arg));
	}

	template<typename Arg, typename ...Args>
	void print(Arg&& arg, Args&&... args)
	{
		print(std::forward<Arg>(arg));
		print(std::forward<Args>(args)...);
	}

	template<typename ...Args>
	void print(Args&&... args)
	{
		print(std::forward<Args>(args)...);
	}
}
