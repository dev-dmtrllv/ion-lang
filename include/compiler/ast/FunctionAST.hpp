#pragma once

#include "compiler/ast/ScopeAST.hpp"

namespace ion::compiler::ast
{
	class FunctionAST: public ScopeAST
	{
	public:
		FunctionAST(Maybe<AST&> parent): ScopeAST(parent) {}
		virtual ~FunctionAST() {}
	};
}