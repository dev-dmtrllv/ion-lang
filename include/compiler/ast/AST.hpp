#pragma once

#include "compiler/Token.hpp"
#include "compiler/TokenIterator.hpp"

namespace ion::compiler::ast
{
	class AST
	{
	public:
		static void parse(TokenIterator& iterator, AST& parseParent);

		AST(Maybe<AST&> parent = {});
		AST(const AST&) = delete;
		AST(AST&&) = delete;

		virtual ~AST();

		template<typename T, typename ...Args>
		inline T& addChild(Args&& ...args)
		{
			T* child = new T(std::forward<Args>(args)...);
			children.push_back(child);
			return *child;
		}

		virtual std::string toString() const { return "AST\r\n"; };

		Maybe<AST&> parent;
		std::vector<AST*> children;
	};
}