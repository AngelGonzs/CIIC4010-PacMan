#include <string>
class PowerUp{
	public:
		int powerAmount = 3;
		virtual void activate(string) = 0;
};
