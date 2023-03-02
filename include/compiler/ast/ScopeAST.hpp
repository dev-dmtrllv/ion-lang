#pragma once

#include "pch.hpp"
#include "compiler/ast/AST.hpp"

namespace ion::compiler::ast
{
	class ScopeAST: public AST
	{
	public:
		ScopeAST(): AST() { }
		virtual ~ScopeAST() { }
	};
}