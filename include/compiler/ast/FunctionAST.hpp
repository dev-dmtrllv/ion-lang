#pragma once

#include "compiler/ast/ScopeAST.hpp"

namespace ion::compiler::ast
{
	class FunctionAST: public ScopeAST
	{
	public:
		FunctionAST(): ScopeAST() {}
		virtual ~FunctionAST() {}
	};
}