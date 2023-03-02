#include "compiler/Lexer.hpp"
#include "print.hpp"

namespace ion::compiler
{
	Lexer::Lexer(const Path& path): path(path) { }

	Lexer::~Lexer() { }

	bool Lexer::checkIdentifier(const char value, std::vector<Token>& tokens)
	{
		const auto maybeIdent = Token::Identifier::fromValue({ value, false });
		Token::Identifier ident = Token::tokens.IDENT_NONE;
		const bool ok = maybeIdent.unwrap(ident);

		const auto name = std::string({ value });

		if (ok)
		{
			if (!ident.ignore())
				tokens.emplace_back(line_, col_, ident, name);
		}
		else
		{
			tokens.emplace_back(line_, col_, Token::Name::create(name), name);
		}

		if (value == '\n')
		{
			col_ = 1;
			line_++;
		}
		else if (value == '\t')
		{
			col_ += 4;
		}
		else
		{
			col_++;
		}

		return ok;
	};

	bool Lexer::checkBuffer(std::string& buffer, std::vector<Token>& tokens)
	{
		const auto maybeKeyword = Token::Keyword::fromValue(buffer);
		Token::Keyword keyword = Token::tokens.KEYWORD_NONE;
		const bool ok = maybeKeyword.unwrap(keyword);

		if (ok)
		{
			tokens.emplace_back(line_, col_, keyword, buffer);
		}
		else
		{
			tokens.emplace_back(line_, col_, Token::Name::create(buffer), buffer);
		}

		col_ += buffer.size();
		buffer = "";
		return true;
	};

	void Lexer::parse([[maybe_unused]] std::vector<Token>& tokens)
	{
		std::ifstream file(path);
		std::istreambuf_iterator<char> it(file);
		std::istreambuf_iterator<char> end;

		std::string buffer;

		reset();

		while (!it.equal(end))
		{
			const char value = *it;
			const auto maybeIdent = Token::Identifier::fromValue({ value, false });
			Token::Identifier ident = Token::tokens.IDENT_NONE;
			if (maybeIdent.unwrap(ident)) // we need to split 
			{
				const std::size_t bs = buffer.size();
				if (bs == 1)
				{
					checkIdentifier(buffer.at(0), tokens);
					buffer = "";
				}
				else if (bs > 1)
				{
					checkBuffer(buffer, tokens);
				}

				checkIdentifier(value, tokens);
			}
			else
			{
				buffer += value;
			}

			it++;
		}
	}
}
