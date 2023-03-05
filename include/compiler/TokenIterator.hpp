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

		template<typename V>
		bool find(std::int64_t offset, const V& value)
		{
			assert(offset != 0);

			std::size_t i = current_;
			const std::size_t target = i + offset;
			
			Token token;

			if (offset < 0)
			{
				while (i >= 0)
				{
					if (!at(i--).unwrap(token))
						return false;

					if (token.match(value))	
						return true;
				
					if (i == 0 || i == target)
						return false;
				}
			}
			else if (offset > 0)
			{
				while (i <= target)
				{
					if (!at(i++).unwrap(token))
						return false;
					
					if (token.match(value))
						return true;
					
					if (i == target)
						return false;
				}
			}
			return false;
		}

		template<typename V>
		bool find(std::int64_t offset, const V& value, Token& found)
		{
			assert(offset != 0);

			std::size_t i = current_;
			const std::size_t target = i + offset;
			
			Token token;

			if (offset < 0)
			{
				while (i >= 0)
				{
					if (!at(i--).unwrap(token))
						return false;
					if (token.match(value))
					{
						found = token;
						return true;
					}
					if (i == 0 || i == target)
						return false;
				}
			}
			else if (offset > target)
			{
				while (i <= target)
				{
					if (!at(i++).unwrap(token))
						return false;
					if (token.match(value))
					{
						found = token;
						return true;
					}
					if (i == target)
						return false;
				}
			}
			return false;
		}

		void skipIf(std::string_view value);

	private:
		const std::vector<Token>& vec_;
		std::size_t current_;
	};
}