#pragma once

#include "pch.hpp"
#include "utils/ArgParser.hpp"
#include "compiler/File.hpp"
#include "compiler/ast/ProjectAST.hpp"

namespace ion::compiler
{
	class Compiler
	{
	public:
		Compiler(const Path& projectPath_);
		Compiler(const Compiler&) = delete;
		Compiler(Compiler&&) = delete;
		~Compiler();

	public:
		void configure(const utils::ArgParser& args);
		void run();

		ast::ProjectAST projectAST;
		
	private:
		bool isConfigured_;
		const Path projectPath_;
		std::vector<File> files_;
	};
}