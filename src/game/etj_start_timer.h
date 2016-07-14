#pragma once
#include "etj_map_entity.h"

namespace ETJump
{
	class StartTimer : public MapEntity
	{
	public:
		explicit StartTimer(gentity_t *entity);
		~StartTimer();

		void use(gentity_t* other, gentity_t* activator) override;
		void think(gentity_t* other, gentity_t* activator) override;
	};
}



