#pragma once

namespace ion::utils::container
{
	template<template<typename...> class Container, typename... ContainerArgs, typename Callback>
	void forEach(const Container<ContainerArgs...>& collection, Callback callback)
	{
		for(const auto& item : collection)
			callback(item);
	}

	template<template<typename...> class Container, typename... ContainerArgs, typename Callback>
	Container<ContainerArgs...> map(const Container<ContainerArgs...>& collection, Callback callback)
	{
		Container<ContainerArgs...> newContainer();

		for(const auto& item : collection)
			newContainer.emplace_back(callback(item));
		
		return newContainer;
	}
}