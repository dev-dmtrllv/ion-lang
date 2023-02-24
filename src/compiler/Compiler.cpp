#include "compiler/Compiler.hpp"
#include "utils/ErrorOr.hpp"
#include "utils/print.hpp"
#include "utils/fs.hpp"
#include "utils/container.hpp"
#include "utils/Error.hpp"

namespace ion::compiler
{
	inline Path parseProjectPath(const utils::ArgParser& args)
	{
		const auto cwd = std::filesystem::current_path();
		const auto projectPath = Path(args.at(0).unwrapOr(cwd.string()));

		if(projectPath.is_relative())
			return cwd / projectPath;
		
		return projectPath;
	}

	void Compiler::run(const utils::ArgParser& args)
	{
		const auto projectPath = parseProjectPath(args);

		if(!std::filesystem::exists(projectPath))
			throw utils::Error(std::format("{} does not exists!", projectPath.string()));

		Compiler compiler(projectPath);
	}

	Compiler::Compiler(const Path& projectPath): 
		projectPath_(projectPath) 
	{
		utils::print(projectPath);
		// const auto files = ion::fs::getFiles(projectPath);
		// utils::container::forEach(files, [](const auto& path)
		// {
		// 	utils::print(path);
		// });
	}

	Compiler::~Compiler() { }
}