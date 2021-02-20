#pragma once

#include <map>
#include <vector>
#include <MC/Core/Chunk.hpp>

namespace MC
{
	class World
	{
	public:
		World();
		~World();

	private:
		std::map<int, MC::Chunk> m_chunks;
	};
}