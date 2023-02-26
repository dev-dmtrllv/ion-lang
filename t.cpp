#include "compiler/Token.hpp"

#define COMPARATOR(__NAME__, ...) static bool __NAME__##Matcher(const std::string& token) { \
	static std::vector<std::string> comparators { __VA_ARGS__ }; \
	for(const auto& str : comparators) \
		if(str.compare(token) == 0) \
			return true; \
	return false; \
}; \

#define CHAR_COMPARATOR(__NAME__, ...) static bool __NAME__##Matcher(const std::string& token) { \
	static std::vector<std::string> comparators { __VA_ARGS__ }; \
	for(const auto& str : comparators) \
		if(str.compare(token) == 0 || token.at(token.size() - 1) == str.at(0)) \
			return true; \
	return false; \
}; \

namespace ion::compiler
{
	std::string_view Token::typeToString(Type type)
	{
		switch (type)
		{
			case Type::EXPORT: return "EXPORT";
			case Type::IMPORT: return "IMPORT";
			case Type::RETURN: return "RETURN";
			case Type::VARIABLE: return "VARIABLE";
			case Type::NAME: return "NAME";
			case Type::END_STMT: return "END_STMT";
			case Type::SCOPE_START: return "SCOPE_START";
			case Type::SCOPE_END: return "SCOPE_END";
			case Type::BRACKET_START: return "BRACKET_START";
			case Type::BRACKET_END: return "BRACKET_END";
			case Type::GENERIC_START: return "GENERIC_START";
			case Type::GENERIC_END: return "GENERIC_END";
			case Type::SQ_BRACKET_START: return "SQ_BRACKET_START";
			case Type::SQ_BRACKET_END: return "SQ_BRACKET_END";
			case Type::SEP: return "SEP";
			case Type::OPERATOR: return "OPERATOR";
			case Type::ACCESSOR: return "ACCESSOR";
			case Type::ATTRIBUTE: return "ATTRIBUTE";
			case Type::CONDITIONAL: return "CONDITIONAL";
			case Type::LOOP: return "LOOP";
			case Type::COLON: return "COLON";
			case Type::DOT: return "DOT";
			case Type::FUNCTION: return "FUNCTION";
			case Type::STRUCT: return "STRUCT";
			case Type::TRAIT: return "TRAIT";
			case Type::TYPE: return "TYPE";
			case Type::USING: return "USING";
			case Type::INTERFACE: return "INTERFACE";
			case Type::UNKNOWN:
			default:
				return "UNKNOWN";
		}
	}

	COMPARATOR(export, "export");
	COMPARATOR(import, "import");
	COMPARATOR(ret, "return");
	COMPARATOR(var, "let", "const");
	CHAR_COMPARATOR(endStatement, ";");
	CHAR_COMPARATOR(scopeStart, "{");
	CHAR_COMPARATOR(scopeEnd, "}");
	CHAR_COMPARATOR(bracketStart, "(");
	CHAR_COMPARATOR(bracketEnd, ")");
	CHAR_COMPARATOR(genericStart, "<");
	CHAR_COMPARATOR(genericEnd, ">");
	CHAR_COMPARATOR(squareBracketStart, "[");
	CHAR_COMPARATOR(squareBracketEnd, "]");
	CHAR_COMPARATOR(seperator, ",");
	CHAR_COMPARATOR(operator, "/", "+", "-", "*");
	COMPARATOR(accessor, "pub", "const");
	CHAR_COMPARATOR(attribute, "#");
	COMPARATOR(conditional, "if", "else if", "else");
	COMPARATOR(loop, "for", "while");
	CHAR_COMPARATOR(colon, ":");
	CHAR_COMPARATOR(dot, ".");
	COMPARATOR(function, "fn");
	COMPARATOR(strct, "struct");
	COMPARATOR(trait, "trait");
	COMPARATOR(type, "type");
	COMPARATOR(using, "using");
	COMPARATOR(interface, "interface");

	static bool nameMatcher(const std::string& str)
	{
		const std::size_t l = str.size();

		char c = str.at(0);

		bool isLowerAlpha = c >= 'a' || c <= 'z';
		bool isUpperAlpha = c >= 'A' || c <= 'Z';
		bool isUnderscore = c == '_';
		bool isNumeric = false;
		if (!isLowerAlpha && !isUpperAlpha && !isUnderscore)
			return false;

		for (std::size_t i = 1; i < l; i++)
		{
			c = str.at(i);
			isLowerAlpha = c >= 'a' || c <= 'z';
			isUpperAlpha = c >= 'A' || c <= 'Z';
			isNumeric = c >= '0' || c <= '9';
			isUnderscore = c == '_';
			if (!isLowerAlpha && !isUpperAlpha && !isNumeric && !isUnderscore)
				return false;
		}

		return true;
	}

	static bool unknownMatcher([[maybe_unused]] const std::string& str)
	{
		return true;
	}

	std::array<std::vector<Token::Matcher>, Token::typeSize> Token::getTypeMatchers()
	{
		static std::array<std::vector<Token::Matcher>, Token::typeSize> matchers = {};

		const auto set = [&]<typename ...Args>(const Type type, Matcher matcher)
		{
			matchers.at(typeToIndex(type)).emplace_back(matcher);
		};

		set(Type::EXPORT, exportMatcher);
		set(Type::IMPORT, importMatcher);
		set(Type::RETURN, retMatcher);
		set(Type::VARIABLE, varMatcher);
		set(Type::NAME, nameMatcher);
		set(Type::END_STMT, endStatementMatcher);
		set(Type::SCOPE_START, scopeStartMatcher);
		set(Type::SCOPE_END, scopeEndMatcher);
		set(Type::BRACKET_START, bracketStartMatcher);
		set(Type::BRACKET_END, bracketEndMatcher);
		set(Type::GENERIC_START, genericStartMatcher);
		set(Type::GENERIC_END, genericEndMatcher);
		set(Type::SQ_BRACKET_START, squareBracketStartMatcher);
		set(Type::SQ_BRACKET_END, squareBracketEndMatcher);
		set(Type::SEP, seperatorMatcher);
		set(Type::OPERATOR, operatorMatcher);
		set(Type::ACCESSOR, accessorMatcher);
		set(Type::ATTRIBUTE, attributeMatcher);
		set(Type::CONDITIONAL, conditionalMatcher);
		set(Type::LOOP, loopMatcher);
		set(Type::COLON, colonMatcher);
		set(Type::DOT, dotMatcher);
		set(Type::FUNCTION, functionMatcher);
		set(Type::STRUCT, strctMatcher);
		set(Type::TRAIT, traitMatcher);
		set(Type::TYPE, typeMatcher);
		set(Type::USING, usingMatcher);
		set(Type::INTERFACE, interfaceMatcher);
		set(Type::UNKNOWN, unknownMatcher);

		return matchers;
	}

	Token::Type Token::typeFromString([[maybe_unused]] const std::string& token)
	{
		static std::array<std::vector<Token::Matcher>, Token::typeSize> typeMatchers = getTypeMatchers();
		const std::size_t l = typeMatchers.size();
		for (std::size_t i = 0; i < l; i++)
		{
			const auto& matchers = typeMatchers.at(i);
			for (const auto& matcher : matchers)
				if (matcher(token))
					return static_cast<Token::Type>(i);
		}

		return Token::Type::UNKNOWN;
	}

	Token::Token(std::size_t line, std::size_t column, Type type, std::string text):
		line(line),
		column(column),
		type(type),
		text(text)
	{ }

	std::string Token::toString() const
	{
		return std::format("{:>{}}:{:>{}} {:>{}} {:>{}}", line, 8, column, 8, text, 32, Token::typeToString(type), 16);
	}
}