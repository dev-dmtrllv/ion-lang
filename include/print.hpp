#pragma once

#include "pch.hpp"
#include "concepts.hpp"

namespace ion::utils
{
	void print(const char* arg);
	void print(std::string_view arg);
	void print(const std::string& arg);
	void print(std::string&& arg);
	void print(const Path& arg);
	void print(bool arg);
	
	template<concepts::ToStringable T>
	void print(const T& arg)
	{
		print(std::move(arg.toString()));
	}
	
	template<concepts::ToStringable T>
	void print(T&& arg)
	{
		print(arg.toString());
	}

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



	void println(const char* arg);
	void println(std::string_view arg);
	void println(const std::string& arg);
	void println(std::string&& arg);
	void println(const Path& arg);
	void println(bool arg);

	template<concepts::ToStringable T>
	void println(const T& arg)
	{
		println(arg.toString());
	}
	
	template<concepts::ToStringable T>
	void println(T&& arg)
	{
		println(arg.toString());
	}


	template<typename T>
	void println(const T& arg)
	{
		println(std::to_string(arg));
	}

	template<typename T>
	void println(T&& arg)
	{
		println(std::to_string(arg));
	}

	template<typename Arg, typename ...Args>
	void println(Arg&& arg, Args&&... args)
	{
		print(std::forward<Arg>(arg));
		println(std::forward<Args>(args)...);
	}

	template<typename ...Args>
	void println(Args&&... args)
	{
		println(std::forward<Args>(args)...);
	}
}
