#pragma once

#include "pch.hpp"
#include "compiler/ast/AST.hpp"

namespace ion::compiler::ast
{
	class ScopeAST: public AST
	{
	public:
		ScopeAST(Maybe<AST&> parent): AST(parent) { }

		virtual ~ScopeAST() { }
	};
}