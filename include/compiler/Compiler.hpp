#pragma once

#include "pch.hpp"
#include "utils/ArgParser.hpp"

namespace ion::compiler
{
	class Compiler
	{
	public:
		static void run(const utils::ArgParser& args);

	private:
		Compiler(const Path& projectPath_);
		Compiler(const Compiler&) = delete;
		Compiler(Compiler&&) = delete;
		~Compiler();

	private:
		const Path projectPath_;
	};
}