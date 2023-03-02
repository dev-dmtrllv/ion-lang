#pragma once

#include "compiler/ast/ScopeAST.hpp"

namespace ion::compiler::ast
{
	class ProjectAST: public ScopeAST
	{
	public:
		ProjectAST(): ScopeAST() {}
		virtual ~ProjectAST() {}
	};
}