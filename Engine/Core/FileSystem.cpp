#include "FileSystem.h"
#include <filesystem>

namespace MarkOne {

	void MarkOne::setFilePath(const std::string& pathName)
	{
		std::filesystem::current_path(pathName);
	}

	std::string MarkOne::getFilePath()
	{
		return std::filesystem::current_path().string();
	}

}