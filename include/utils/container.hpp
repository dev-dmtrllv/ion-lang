#pragma once

#include "pch.hpp"

namespace ion::utils::container::vector
{
	template<typename In, typename Callback>
	void forEach(const std::vector<In>& collection, Callback callback)
	{
		for(const auto& item : collection)
			callback(item);
	}

	template<typename In, typename Out>
	using MapCallback = Out(*)(const In&);
	
	template<typename In, typename Out, typename Data>
	using MapDataCallback = Out(*)(const In&, Data);

	template<typename In, typename Out>
	std::vector<Out> map(const std::vector<In>& collection, MapCallback<In, Out> callback)
	{
		std::vector<In> newContainer;

		for(const auto& item : collection)
			newContainer.emplace_back(callback(item));
		
		return newContainer;
	}

	template<typename In, typename Out, typename Data>
	std::vector<Out> map(const std::vector<In>& collection, MapDataCallback<In, Out, Data> callback, Data data)
	{
		std::vector<In> newContainer;

		for(const auto& item : collection)
			newContainer.emplace_back(callback(item, data));
		
		return newContainer;
	}
}