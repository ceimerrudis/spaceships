#pragma once

namespace cat
{
	namespace Random
	{
		//both inclusive
		int RandomI(int min, int max);

		//both inclusive
		float RandomF(float min, float max);
		
		void SetRandomSeed(unsigned int seed);
	}
}
