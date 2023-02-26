#include "pch.hpp"

#include "utils/ArgParser.hpp"
#include "print.hpp"
#include "Error.hpp"
#include "Maybe.hpp"

#include "compiler/Compiler.hpp"

Path getProjectPath(const ion::utils::ArgParser& args)
{
	const auto cwd = std::filesystem::current_path();
	const auto projectPath = Path(args.at(0).value_or(cwd.string()));

	if (projectPath.is_relative())
		return cwd / projectPath;

	return projectPath;
}

int main(int argc, char** argv)
{
	using namespace ion;

	const utils::ArgParser args(argc, argv);

	try
	{
		const auto projectPath = getProjectPath(args);

		if (!std::filesystem::exists(projectPath))
			throw utils::Error(std::format("{} does not exists!", projectPath.string()));

		compiler::Compiler compiler(projectPath);
		compiler.configure(args);
		compiler.run();
	}
	catch (const utils::Error& err)
	{
		utils::println(err.what());
	}
}