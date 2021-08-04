#pragma once
#include <string>

namespace MarkOne {
	class Resource {

	public:
		virtual bool Load(const std::string& filename, void* data = nullptr) = 0;
	};

}