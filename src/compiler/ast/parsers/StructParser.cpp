#include "compiler/ast/parsers/StructParser.hpp"

#include "compiler/ast/parsers/Parser.hpp"
#include "compiler/ast/StructAST.hpp"
#include "compiler/Token.hpp"
#include "compiler/SyntaxError.hpp"
#include "print.hpp"

namespace ion::compiler::ast
{
	void structParser(TokenIterator& iter, [[maybe_unused]] ast::AST& parent)
	{
		iter.skipIf("struct");

		const bool isExport = iter.find<std::string>(-3, "export");

		Token token;

		if (!iter.next().unwrap(token))
			throw SyntaxError("Unexpected end of file", token);

		if (!token.is<Token::Name>())
			throw SyntaxError("Excpected a name", token);

		const std::string name = token.type.type<Token::Name>().value;

		parent.addChild<StructAST>(parent, name);

		utils::println(std::format("{}struct {}", isExport ? "export " : "", name));
	}
}