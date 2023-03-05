#include "pch.hpp"

#include "utils/ArgParser.hpp"
#include "print.hpp"
#include "Error.hpp"
#include "Maybe.hpp"
#include "compiler/SyntaxError.hpp"

#include "compiler/Compiler.hpp"

#include <algorithm>
#include <string>

Path getProjectPath(const ion::utils::ArgParser& args)
{
	const auto cwd = std::filesystem::current_path();
	const auto projectPath = Path(args.at(0).value_or(cwd.string()));

	if (projectPath.is_relative())
		return cwd / projectPath;

	return projectPath;
}

namespace Tokens
{
	struct Type
	{
		const std::string name;
		const std::string value;

		static inline std::string tolower(std::string s)
		{
			std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return static_cast<unsigned char>(std::tolower(c)); });
			return s;
		}

		Type(std::string_view name): Type(name, name)
		{ }

		Type(std::string_view name, const char value):
			name(name),
			value({ value })
		{ }

		Type(std::string_view name, std::string_view val):
			name(name),
			value(tolower(std::string(val)))
		{ }

		bool operator==(const Type& other) const noexcept
		{
			if (name.compare(other.name) != 0)
				return false;

			if (value.compare(other.value) != 0)
				return false;

			return true;
		}

		bool operator==(std::string_view val) const noexcept
		{
			return value.compare(val) != 0;
		}

		bool operator==(const char val) const noexcept
		{
			return value.at(0) == val;
		}

		bool isKeyword() const noexcept { return value.length() > 1; }
	};

	const Type END = Type("\0");
	const Type EXPORT = Type("export");
	const Type IMPORT = Type("import");
	const Type RETURN = Type("return");
	const Type LET = Type("let");
	const Type PUB = Type("pub");
	const Type FN = Type("fn");
	const Type STRUCT = Type("struct");
	const Type TRAIT = Type("trait");
	const Type TYPE = Type("type");
	const Type USING = Type("using");
	const Type INTERFACE = Type("interface");
	const Type IF = Type("if");
	const Type ELSEIF = Type("else if");
	const Type ELSE = Type("else");
	const Type FOR = Type("for");
	const Type WHILE = Type("while");
	const Type MATCH = Type("match");
	const Type CONST = Type("const");
	const Type MUT = Type("mut");
	const Type THIS = Type("this");
	const Type AS = Type("as");

	const Type NEW_LINE = Type("NEW_LINE", '\n');
	const Type CARIAGE_RETURN = Type("CARIAGE_RETURN", '\r');
	const Type TAB = Type("TAB", '\t');
	const Type SPACE = Type("SPACE", ' ');

	const Type END_STMT = Type("END_STMT", ';');
	const Type SCOPE_START = Type("SCOPE_START", '{');
	const Type SCOPE_END = Type("SCOPE_END", '}');
	const Type BRACKET_START = Type("BRACKET_START", '(');
	const Type BRACKET_END = Type("BRACKET_END", ')');
	const Type GENERIC_START = Type("GENERIC_START", '<');
	const Type GENERIC_END = Type("GENERIC_END", '>');
	const Type SQ_BRACKET_START = Type("SQ_BRACKET_START", '[');
	const Type SQ_BRACKET_END = Type("SQ_BRACKET_END", ']');
	const Type SEP = Type("SEP", ',');
	const Type ADD = Type("ADD", '+');
	const Type SUBTRACT = Type("SUBTRACT", '-');
	const Type DIVIDE = Type("DIVIDE", '/');
	const Type MULTPLY = Type("MULTPLY", '*');
	const Type ATTRIBUTE = Type("ATTRIBUTE", '#');
	const Type COLON = Type("COLON", ':');
	const Type DOT = Type("DOT", '.');
	const Type REF = Type("REF", '&');
	const Type TILDE = Type("TILDE", '~');
	const Type PIPE = Type("PIPE", '|');
	const Type NOT = Type("NOT", '!');

	const Type UNKNOWN = Type("UNKNOWN", '\0');
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
	using namespace ion;

	assert(Tokens::ADD == Tokens::ADD);

	// const utils::ArgParser args(argc, argv);

	// try
	// {
	// 	const auto projectPath = getProjectPath(args);

	// 	if (!std::filesystem::exists(projectPath))
	// 		throw utils::Error(std::format("{} does not exists!", projectPath.string()));

	// 	compiler::Compiler compiler(projectPath);
	// 	compiler.configure(args);
	// 	compiler.run();
	// }
	// catch (const utils::Error& err)
	// {
	// 	utils::println(err.what());
	// }
	// catch (const compiler::SyntaxError& err)
	// {
	// 	utils::println(err.what(), "but found", err.token());
	// }

	return 0;
}