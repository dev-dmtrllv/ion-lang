#pragma once

#include "pch.hpp"
#include "compiler/Token.hpp"

namespace ion::compiler
{
	class File
	{
	public:
		File(const Path& path);

		void buildSymbolTable();

		Path path;
		std::vector<Token> tokens;
	};
}