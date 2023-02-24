#pragma once

namespace ion::utils
{
	template<typename T>
	class Maybe
	{
	public:
		Maybe():
			value_(),
			hasValue_(false)
		{ }

		Maybe(const T& value):
			value_({ value }),
			hasValue_(true)
		{ }

		Maybe(T&& value):
			value_({ value }),
			hasValue_(true)
		{ }

		template<typename... Args>
		Maybe(Args&& ...args) :
			value_{ T(std::forward<Args>(args)...) },
			hasValue_(true)
		{ }

		~Maybe()
		{
			if (hasValue_)
				value_[0].~T();
		}

		[[nodiscard]] T unwrap()
		{
			if (!hasValue_)
				throw std::runtime_error("Maybe is empty!");

			return value_[0];
		}

		[[nodiscard]] T unwrapOr(T&& otherValue)
		{
			if (!hasValue_)
				return otherValue;

			return value_[0];
		}

		inline T operator->() { return unwrap(); }

	private:
		T value_[1];
		bool hasValue_;
	};
}