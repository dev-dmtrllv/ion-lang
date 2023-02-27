#include "compiler/Compiler.hpp"
#include "compiler/Lexer.hpp"

#include "print.hpp"
#include "utils/container.hpp"
#include "utils/fs.hpp"
#include "Error.hpp"

namespace ion::compiler
{
	Compiler::Compiler(const Path& projectPath):
		isConfigured_(false),
		projectPath_(projectPath),
		files_()
	{
		const auto paths = ion::fs::getFiles(projectPath);
		files_.reserve(paths.size());
		utils::container::vector::forEach(paths, [ & ](const auto& path) { files_.emplace_back(path); });
	}

	Compiler::~Compiler() { }

	void Compiler::configure([[maybe_unused]] const utils::ArgParser& args)
	{
		isConfigured_ = true;
	}

	void Compiler::run()
	{
		if (!isConfigured_)
			throw utils::Error("Compiler is not configured!");


		for (auto& file : files_)
		{
			Lexer lexer(file.path);
			lexer.parse(file.tokens);

			utils::println("line:\t\tcol:\t\ttype:\t\t\t\t\t\t\ttext:");

			for (const auto& t : file.tokens)
				utils::println(t);

			utils::println("");
		}

		for (auto& file : files_)
			file.buildSymbolTable();
	}
}