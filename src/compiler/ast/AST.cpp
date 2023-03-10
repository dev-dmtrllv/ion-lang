#include "compiler/ast/AST.hpp"

namespace ion::compiler::ast
{
	void AST::parse(TokenIterator& iterator, AST& parseParent)
	{
		Token token;
		if (!iterator.current().unwrap(token))
			return;
		do
		{
			const auto parser = token.type.parser();
			if (parser != nullptr)
				parser(iterator, parseParent);
		} while (iterator.next().unwrap(token));
	}

	AST::AST(Maybe<AST&> parent):
		parent(parent),
		children()
	{ }

	AST::~AST()
	{
		for (const auto& child : children)
			delete child;
	}
}