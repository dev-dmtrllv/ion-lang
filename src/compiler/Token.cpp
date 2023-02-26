#include "compiler/Token.hpp"

namespace ion::compiler
{
	Token::Keyword Token::KEYWORD_NONE = Keyword::create("\0");
	Token::Keyword Token::EXPORT = Keyword::create("export");
	Token::Keyword Token::IMPORT = Keyword::create("import");
	Token::Keyword Token::RETURN = Keyword::create("return");
	Token::Keyword Token::LET = Keyword::create("let");
	Token::Keyword Token::PUB = Keyword::create("pub");
	Token::Keyword Token::FN = Keyword::create("fn");
	Token::Keyword Token::STRUCT = Keyword::create("struct");
	Token::Keyword Token::TRAIT = Keyword::create("trait");
	Token::Keyword Token::TYPE = Keyword::create("type");
	Token::Keyword Token::USING = Keyword::create("using");
	Token::Keyword Token::INTERFACE = Keyword::create("interface");
	Token::Keyword Token::IF = Keyword::create("if");
	Token::Keyword Token::ELSEIF = Keyword::create("else if");
	Token::Keyword Token::ELSE = Keyword::create("else");
	Token::Keyword Token::FOR = Keyword::create("for");
	Token::Keyword Token::WHILE = Keyword::create("while");
	Token::Keyword Token::MATCH = Keyword::create("match");
	Token::Keyword Token::CONST = Keyword::create("const");
	Token::Keyword Token::MUT = Keyword::create("mut");
	Token::Keyword Token::THIS = Keyword::create("this");

	Token::Identifier Token::IDENT_NONE = Identifier::create('\0', true);
	Token::Identifier Token::NEW_LINE = Identifier::create('\n', true);
	Token::Identifier Token::CARIAGE_RETURN = Identifier::create('\r', true);
	Token::Identifier Token::TAB = Identifier::create('\t', true);
	Token::Identifier Token::SPACE = Identifier::create(' ', true);

	Token::Identifier Token::END_STMT = Identifier::create(';');
	Token::Identifier Token::SCOPE_START = Identifier::create('{');
	Token::Identifier Token::SCOPE_END = Identifier::create('}');
	Token::Identifier Token::BRACKET_START = Identifier::create('(');
	Token::Identifier Token::BRACKET_END = Identifier::create(')');
	Token::Identifier Token::GENERIC_START = Identifier::create('<');
	Token::Identifier Token::GENERIC_END = Identifier::create('>');
	Token::Identifier Token::SQ_BRACKET_START = Identifier::create('[');
	Token::Identifier Token::SQ_BRACKET_END = Identifier::create(']');
	Token::Identifier Token::SEP = Identifier::create(',');
	Token::Identifier Token::ADD = Identifier::create('+');
	Token::Identifier Token::SUBTRACT = Identifier::create('-');
	Token::Identifier Token::DIVIDE = Identifier::create('/');
	Token::Identifier Token::MULTPLY = Identifier::create('*');
	Token::Identifier Token::ATTRIBUTE = Identifier::create('#');
	Token::Identifier Token::COLON = Identifier::create(':');
	Token::Identifier Token::DOT = Identifier::create('.');
	Token::Identifier Token::REF = Identifier::create('&');
	Token::Identifier Token::TILDE = Identifier::create('~');
	Token::Identifier Token::PIPE = Identifier::create('|');
	Token::Identifier Token::NOT = Identifier::create('!');

	std::string Token::toString() const
	{
		return std::format("{}\t\t{}\t\ttypeID: {}\t\t{}", line, column, Token::nameFromID(typeID), text);
	}
}