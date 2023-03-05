#pragma once

#include "compiler/ast/parsers/Parser.hpp"

namespace ion::compiler::ast
{
	void scopeParser(TokenIterator& iter, ast::AST& parent);
}