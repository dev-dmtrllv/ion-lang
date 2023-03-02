#pragma once

#include "pch.hpp"
#include "Maybe.hpp"

namespace ion::compiler
{
	class Token;

	struct TokenIterator
	{
	public:
		TokenIterator(const std::vector<Token>& t);
		TokenIterator(const TokenIterator&) = delete;
		TokenIterator(TokenIterator&&) = delete;
		~TokenIterator();

		Maybe<const Token&> next();
		Maybe<const Token&> at(std::size_t offset);
		Maybe<const Token&> current();
		Maybe<const Token&> offset(std::int64_t offset);
		bool is(const Token& token);

	private:
		const std::vector<Token>& vec_;
		std::size_t current_;
	};
}