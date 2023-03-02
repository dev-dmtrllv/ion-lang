#pragma once

namespace ion::compiler
{
	struct TokenIterator;

	namespace ast
	{
		class AST;
		
		using Parser = void(*)(TokenIterator&, ast::AST&);

		void defaultParser(TokenIterator&, ast::AST&);
	}
}