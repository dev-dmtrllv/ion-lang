#include "utils/fs.hpp"

namespace ion::fs
{
	namespace
	{
		inline void getEntriesRecursive(std::string_view path, std::vector<Path>& paths)
		{
			for (const auto& entry : std::filesystem::directory_iterator(path))
			{
				paths.emplace_back(entry.path());
				if (entry.is_directory())
					getEntriesRecursive(entry.path().string(), paths);
			}
		}

		inline void getFilesRecursive(std::string_view path, std::vector<Path>& paths)
		{
			for (const auto& entry : std::filesystem::directory_iterator(path))
			{
				if (entry.is_directory())
					getFilesRecursive(entry.path().string(), paths);
				else
					paths.emplace_back(entry.path());
			}
		}

		inline void getEntries(std::string_view path, std::vector<Path>& paths)
		{
			for (const auto& entry : std::filesystem::directory_iterator(path))
				paths.emplace_back(entry.path());
		}

		inline void getFiles(std::string_view path, std::vector<Path>& paths)
		{
			for (const auto& entry : std::filesystem::directory_iterator(path))
				if (!entry.is_directory())
					paths.emplace_back(entry.path());
		}

		using FSGetter = void(*)(std::string_view, std::vector<Path>&);

		static std::array<FSGetter, 2> fileGetters = {
			getFiles,
			getFilesRecursive
		};

		static std::array<FSGetter, 2> entryGetters = {
			getEntries,
			getEntriesRecursive,
		};
	}

	[[nodiscard]] std::vector<Path> getFiles(const Path& path, bool recursive)
	{
		std::vector<Path> paths;
		fileGetters[recursive](path.string(), paths);
		return paths;
	}

	[[nodiscard]] std::vector<Path> getEntries(const Path& path, bool recursive)
	{
		std::vector<Path> paths;
		entryGetters[recursive](path.string(), paths);
		return paths;
	}
}