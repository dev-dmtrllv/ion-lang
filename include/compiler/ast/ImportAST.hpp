#pragma once

#include "compiler/ast/AST.hpp"

namespace ion::compiler::ast
{
	class ImportAST: public AST
	{
	public:
		struct Import
		{
			std::string symbol;
			std::string alias;

			Import(std::string_view name):
				symbol(name),
				alias(name)
			{ }

			Import(std::string_view name, std::string_view alias):
				symbol(name),
				alias(alias)
			{ }
		};

		ImportAST(Maybe<AST&> parent, Path&& path, std::vector<Import>&& imports): AST(parent),
			path(path),
			imports(imports)
		{ }

		virtual ~ImportAST() { }

		virtual std::string toString() const override
		{
			std::string str = std::format("import {}\r\n", path.string());
			for (const auto& import : imports)
			{
				if (import.alias.compare(import.symbol) == 0)
					str += std::format("\t- {}\r\n", import.alias);
				else
					str += std::format("\t- {} as {}\r\n", import.symbol, import.alias);
			}
			return str;
		}

		Path path;
		std::vector<Import> imports;
	};
}