#pragma once

#include "pch.hpp"
#include "compiler/Token.hpp"

namespace ion::compiler
{
	class Lexer
	{
	public:
		Lexer(const Path& path);
		Lexer(const Lexer&) = delete;
		Lexer(Lexer&&) = delete;
		~Lexer();

		void parse(std::vector<Token>& tokens);

		const Path& path;

	private:
		inline void reset() 
		{
			line_ = 1;
			col_ = 1;
		}

		bool checkIdentifier(const char value, std::vector<Token>& tokens);
		bool checkBuffer(std::string& buffer, std::vector<Token>& tokens);
		
		std::size_t line_ = 1;
		std::size_t col_ = 1;
	};
}