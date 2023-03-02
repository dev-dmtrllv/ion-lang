#pragma once

#include "pch.hpp"

namespace ion::compiler
{
	class Token;

	class SyntaxError : public std::runtime_error
	{
	public:
		SyntaxError(const char* msg, Token& token): std::runtime_error(msg),
			token_(token)
		{}

		const Token& token() const { return token_; }

	private:
		Token& token_;
	};
}