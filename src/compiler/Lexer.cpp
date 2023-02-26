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
		// utils::println(path);
		// utils::println(Token::Keyword::ID);
		// utils::println(Token::Name::ID);
		// utils::println(Token::Unknown::ID);
		// utils::println(Token::Identifier::ID);

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
			utils::println(Token::nameFromID(T::ID));
			tokens.emplace_back(startTokenLine, startTokenColumn, type, text);
			startTokenLine = line;
			startTokenColumn = col;
		};

		while (!it.equal(end))
		{
			const char value = *it;
			const auto maybeIdent = Token::Identifier::fromValue({ value, false });
			Token::Identifier ident = Token::IDENT_NONE;
			if (maybeIdent.unwrap(ident)) // we need to split 
			{
				const std::size_t bs = buffer.size();

				if (bs == 1) // we have only one character in the buffer
				{
					const auto maybePreIdent = Token::Identifier::fromValue({ buffer.at(0), false });
					Token::Identifier preIdent = Token::IDENT_NONE;
					if (maybePreIdent.unwrap(preIdent)) // its not a char token
					{
						if (!preIdent.ignore())
						{
							push(preIdent, buffer);
						}
					}
					else // check if its a name
					{
						push(Token::Name::create(buffer), buffer);
					}
					buffer = "";
				}
				else if (bs >= 2)
				{
					const auto maybePreKeyword = Token::Keyword::fromValue(buffer.c_str());
					Token::Keyword preKeyword = Token::KEYWORD_NONE;
					if (maybePreKeyword.unwrap(preKeyword))
					{
						push(preKeyword, buffer);
					}
					else // check if its a name
					{
						push(Token::Name::create(buffer), buffer);
					}
					buffer = "";
				}

				if (!ident.ignore())
				{
					push(ident, { value });
				}
			}
			else
			{
				buffer += value;
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

			it++;
		}

		for (const auto& t : tokens)
			utils::println(t);
	}
}
