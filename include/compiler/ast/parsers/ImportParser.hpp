#pragma once

#include "compiler/ast/parsers/Parser.hpp"


namespace ion::compiler::ast
{
	void importParser(TokenIterator& iter, ast::AST& parent);
}