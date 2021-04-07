#pragma once
#include <string>
#include <vector>
class PowerUp{
	public:
		int powerAmount = 3;
		virtual void activate() = 0;
};
