#include "compiler/TokenIterator.hpp"
#include "compiler/Token.hpp"

namespace ion::compiler
{
	TokenIterator::TokenIterator(const std::vector<Token>& t): vec_(t), current_(0) { }
	TokenIterator::~TokenIterator() { }

	Maybe<const Token&> TokenIterator::next()
	{
		return at(current_++);
	}

	Maybe<const Token&> TokenIterator::at(std::size_t offset)
	{
		if (offset >= vec_.size())
			return {};
		return vec_.at(offset);
	}

	Maybe<const Token&> TokenIterator::current()
	{
		return at(current_);
	}

	Maybe<const Token&> TokenIterator::offset(std::int64_t offset)
	{
		return at(offset + current_);
	}

	bool TokenIterator::is(const Token& token)
	{
		Token cur;
		if (!current().unwrap(cur))
			return false;
		return cur == token;
	}
}