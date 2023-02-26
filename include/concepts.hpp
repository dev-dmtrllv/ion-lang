#pragma once

#include "pch.hpp"

namespace ion::utils::concepts
{
	template<typename T>
	concept ToStringable = requires(T toStringable)
	{
		{ toStringable.toString() } -> std::same_as<std::string>;
	};
}