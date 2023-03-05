#pragma once

#include "compiler/ast/parsers/Parser.hpp"

namespace ion::compiler::ast
{
	void functionParser(TokenIterator& iter, ast::AST& parent);
}