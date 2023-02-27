#include "compiler/Token.hpp"

namespace ion::compiler
{
	Token::Tokens Token::tokens = Token::Tokens();

	std::string Token::toString() const
	{
		return std::format("{}\t\t{}\t\ttypeID: {}\t\t{}\t\t{}", line, column, Token::nameFromID(typeID), name(), text);
	}
}