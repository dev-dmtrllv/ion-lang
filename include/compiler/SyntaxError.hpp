#pragma once

#include "pch.hpp"
#include "compiler/Token.hpp"

namespace ion::compiler
{
	class SyntaxError : public std::runtime_error
	{
	public:
		SyntaxError(const char* msg, const Token& token);

		const Token& token() const;

	private:
		Token token_;
	};
}