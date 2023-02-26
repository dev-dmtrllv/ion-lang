#include "compiler/Lexer.hpp"
#include "print.hpp"

namespace ion::compiler
{
	Lexer::Lexer()
	{

	}

	Lexer::~Lexer()
	{

	}

	void Lexer::getTokenStream([[maybe_unused]] const Path& path, [[maybe_unused]] std::vector<Token>& tokens)
	{
		utils::println(path);

		std::ifstream file(path);
		std::istreambuf_iterator<char> it(file);
		std::istreambuf_iterator<char> end;

		std::size_t startTokenLine = 1;
		std::size_t startTokenColumn = 1;

		std::size_t line = 1;
		std::size_t col = 1;

		std::string buffer;

		const auto push = [&]<typename T>(const T type, const std::string & text)
		{
			tokens.emplace_back(startTokenLine, startTokenColumn, type, text);
		};

		const auto checkAndPushChar = [ & ](const char value) -> bool
		{
			const auto maybeIdent = Token::Identifier::fromValue({ value, false });
			Token::Identifier ident = Token::IDENT_NONE;
			const bool ok = maybeIdent.unwrap(ident);

			const auto name = std::string({ value });

			if (ok)
			{
				if (!ident.ignore())
					tokens.emplace_back(col, line, ident, name);
			}
			else
			{
				tokens.emplace_back(col, line, Token::Name::create(name), name);
			}

			if (value == '\n')
			{
				col = 1;
				line++;
			}
			else if (value == '\t')
			{
				col += 4;
			}
			else
			{
				col++;
			}

			return ok;
		};

		const auto checkAndPushString = [ & ](std::string& buffer) -> bool
		{
			const auto maybeKeyword = Token::Keyword::fromValue(buffer);
			Token::Keyword keyword = Token::KEYWORD_NONE;
			const bool ok = maybeKeyword.unwrap(keyword);

			if (ok)
			{
				tokens.emplace_back(col, line, keyword, buffer);
			}
			else
			{
				tokens.emplace_back(col, line, Token::Name::create(buffer), buffer);
			}

			col += buffer.size();
			buffer = "";
			return true;
		};

		while (!it.equal(end))
		{
			const char value = *it;
			const auto maybeIdent = Token::Identifier::fromValue({ value, false });
			Token::Identifier ident = Token::IDENT_NONE;
			if (maybeIdent.unwrap(ident)) // we need to split 
			{
				const std::size_t bs = buffer.size();
				if (bs == 1)
				{
					checkAndPushChar(buffer.at(0));
					buffer = "";
				}
				else if (bs > 1)
				{
					checkAndPushString(buffer);
				}

				checkAndPushChar(value);
			}
			else
			{
				buffer += value;
			}

			it++;
		}

		for (const auto& t : tokens)
			utils::println(t);


		utils::println("");
	}
}
