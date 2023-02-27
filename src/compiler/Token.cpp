#include "compiler/Token.hpp"

namespace ion::compiler
{
	Token::Tokens Token::tokens = Token::Tokens();

	std::string Token::toString() const
	{
		return std::format("{: <{}}\t\t{: <{}}\t\t{: <{}}\t\t{: <{}}", line, 4, column, 4, Token::nameFromID(typeID), 34, text, 20);
	}
}