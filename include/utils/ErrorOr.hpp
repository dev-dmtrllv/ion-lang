#pragma once

#include "utils/Error.hpp"

namespace ion::utils
{
	struct Error;

	template<typename T>
	class ErrorOr
	{
	private:
		enum class State
		{
			Data,
			Error,
			Moved
		};

	// 	[[noreturn]] static void defaultUnwrapCallack(const Error& error)
	// 	{
	// 		throw std::move(error);
	// 	}

	public:
		ErrorOr(const T& data):
			data_(data),
			state_(State::Data)
		{ }
		// ErrorOr(T&& data):
		// 	data_(data),
		// 	state_(State::Data)
		// { }

		// ErrorOr(const Error& error):
		// 	error_(error),
		// 	state_(State::Error)
		// { }
		// ErrorOr(Error&& error):
		// 	error_(error),
		// 	state_(State::Error)
		// { }

		// ErrorOr(const ErrorOr&) = delete;
		// ErrorOr(ErrorOr&&) = delete;

		// ~ErrorOr()
		// {
		// 	if (state_ == State::Data)
		// 		data_.~T();
		// }

		// template<typename Callback>
		// [[nodiscard]] T&& unwrap(Callback errorCallback = defaultUnwrapCallack) const
		// {
		// 	if (isMoved())
		// 	{
		// 		throw std::runtime_error("Data has been moved!");
		// 	}
		// 	else if (hasError())
		// 	{
		// 		errorCallback(error_);
		// 	}
		// 	else
		// 	{
		// 		state_ = State::Moved;
		// 		return std::move(data_);
		// 	}
		// }

		// [[nodiscard]] inline bool hasError() const noexcept { return state_ == State::Error; }
		// [[nodiscard]] inline bool isMoved() const noexcept { return state_ == State::Moved; }

		// [[nodiscard]] const Error& error() const noexcept
		// {
		// 	assert(state_ == State::Error);
		// 	return std::move(data_);
		// }

		// [[nodiscard]] inline const T& error() const noexcept
		// {
		// 	assert(state_ == State::Data);
		// 	return data_;
		// }

	private:
		union
		{
			const T data_;
			const Error error_;
		};

		State state_;
	};
}