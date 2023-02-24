#include "pch.hpp"
#include "utils/ArgParser.hpp"
#include "utils/print.hpp"
#include "compiler/Compiler.hpp"

int main(int argc, char** argv)
{
	using namespace ion;

	const utils::ArgParser	args(argc, argv);
	try
	{
		compiler::Compiler::run(args);
	}
	catch(const utils::Error& err)
	{
		utils::print(err.what());
	}
}