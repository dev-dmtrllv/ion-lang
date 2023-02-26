#pragma once

#include "pch.hpp"
#include "compiler/Token.hpp"

namespace ion::compiler
{
	class Lexer
	{
	public:
		Lexer();
		Lexer(const Lexer&) = delete;
		Lexer(Lexer&&) = delete;
		~Lexer();

		void getTokenStream(const Path& path, std::vector<Token>& tokens);
	};
}