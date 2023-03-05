#include "compiler/SyntaxError.hpp"
#include "compiler/Token.hpp"

namespace ion::compiler
{
	SyntaxError::SyntaxError(const char* msg, const Token& token): std::runtime_error(msg),
		token_(token)
	{ }

	const Token& SyntaxError::token() const { return token_; }

}