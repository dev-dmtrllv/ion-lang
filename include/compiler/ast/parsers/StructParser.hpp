#pragma once

#include "compiler/ast/parsers/Parser.hpp"

namespace ion::compiler::ast
{
	void structParser(TokenIterator& iter, ast::AST& parent);
}