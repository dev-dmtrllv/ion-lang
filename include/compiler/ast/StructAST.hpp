#pragma once

#include "compiler/ast/ScopeAST.hpp"

namespace ion::compiler::ast
{
	class StructAST: public ScopeAST
	{
	public:
		StructAST(Maybe<AST&> parent, std::string_view name): ScopeAST(parent),
			name(name) {}
		virtual ~StructAST() {}
	
	private:
		std::string name;
	};
}