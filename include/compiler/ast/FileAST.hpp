#pragma once

#include "compiler/ast/ScopeAST.hpp"

namespace ion::compiler::ast
{
	class FileAST: public ScopeAST
	{
	public:
		FileAST(): ScopeAST() {}
		virtual ~FileAST() {}

		virtual std::string toString() const override
		{
			std::string str;
			for(const auto child : children)
				str += child->toString();
			return str;
		}
	};
}