#pragma once

#include "compiler/ast/parsers/Parser.hpp"
#include "compiler/ast/ImportAST.hpp"
#include "compiler/Token.hpp"
#include "compiler/SyntaxError.hpp"
#include "print.hpp"

namespace ion::compiler::ast
{
	Path getImportPath(TokenIterator& iter)
	{
		Token token;

		bool expectSeperator = false; // check if we expected a DOT (.)

		Path importPath = "";

		while (iter.next().unwrap(token))
		{
			if (expectSeperator)
			{
				if (!token.is<Token::Identifier>())
					throw SyntaxError("Expected a seperator", token);

				if (token.type == Token::tokens.DOT)
				{
					expectSeperator = !expectSeperator;
					continue;
				}
				else if (token.type == Token::tokens.SCOPE_START)
					return importPath;
				else
					throw SyntaxError("Expected a '.' or '{'", token);
			}
			else
			{
				if (!token.is<Token::Name>())
					throw SyntaxError("Expected a name", token);

				importPath /= token.type.type<Token::Name>().value;
			}
			expectSeperator = !expectSeperator;
		}

		throw SyntaxError("Unxpected end of statement", token);
	}

	std::vector<ImportAST::Import> getImports(TokenIterator& iter)
	{
		Token token;

		std::vector<ImportAST::Import> imports;

		bool expectSeperator = false; // check if we expected a DOT (.)

		std::string name;
		std::string alias;

		while (iter.next().unwrap(token))
		{
			const bool gotAlias = alias.length() > 0;
			if (gotAlias)
			{
				const auto a = token.is<Token::Identifier>();
				const auto b = token.type != Token::tokens.SEP && token.type != Token::tokens.SCOPE_END;
				if (!a || b)
					throw SyntaxError("Expected a ',' or '}'", token);
			}

			if (expectSeperator)
			{
				if (token.is<Token::Keyword>())
				{
					if (token.type != Token::tokens.AS)
						throw SyntaxError("Expected 'as'", token);
				}
				else if (token.is<Token::Identifier>())
				{
					if (token.type != Token::tokens.SEP && token.type != Token::tokens.SCOPE_END)
						throw SyntaxError("Expected a ',' or '}'", token);

					if (alias.length() == 0)
						imports.emplace_back(name);
					else
						imports.emplace_back(name, alias);
					name = "";
					alias = "";

					if (token.type == Token::tokens.SCOPE_END)
						return imports;
				}
			}
			else
			{
				if (!token.is<Token::Name>())
					throw SyntaxError("Expected a name", token);

				if (name.length() == 0)
					name = token.type.type<Token::Name>().value;
				else
					alias = token.type.type<Token::Name>().value;
			}
			expectSeperator = !expectSeperator;
		}

		throw SyntaxError("Unxpected end of statement", token);

		return imports;
	}

	void importParser(TokenIterator& iter, [[maybe_unused]] AST& parent)
	{
		Path importPath = getImportPath(iter);
		std::vector<ImportAST::Import> imports = getImports(iter);

		Token token;

		if(!iter.next().unwrap(token))
			throw SyntaxError("Unxpected end of statement", token);

		if(!token.is<Token::Identifier>() || token.type != Token::tokens.END_STMT)
			throw SyntaxError("Expected a ';'", token);

		parent.addChild<ImportAST>(parent, std::move(importPath), std::move(imports));
	}
}