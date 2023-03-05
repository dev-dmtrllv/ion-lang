#include "compiler/ast/parsers/FunctionParser.hpp"
#include "compiler/ast/parsers/Parser.hpp"
#include "compiler/ast/FunctionAST.hpp"
#include "compiler/Token.hpp"
#include "compiler/SyntaxError.hpp"
#include "print.hpp"

namespace ion::compiler::ast
{
	void functionParser(TokenIterator& iter, [[maybe_unused]] ast::AST& parent)
	{
		iter.skipIf("fn");

		// const bool isPublic = iter.find<std::string>(-2, "pub");
		// const bool isExport = iter.find<std::string>(-3, "export");
		
		Token token;
		if (!iter.next().unwrap(token))
			throw SyntaxError("Unexpected end of file", token);

		if (!token.is<Token::Name>())
			throw SyntaxError("Excpected a name", token);

		const std::string name = token.type.type<Token::Name>().value;

		utils::println("fn ", name);
	}
}