#pragma once

#include "pch.hpp"

namespace ion::fs
{
	[[nodiscard]] std::vector<Path> getFiles(const Path& path, bool recursive = true);
	[[nodiscard]] std::vector<Path> getEntries(const Path& path, bool recursive = true);
}