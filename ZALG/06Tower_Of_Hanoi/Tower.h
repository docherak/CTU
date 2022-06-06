#include <vector>

class Tower
{
public:
	int height;
	std::vector<int> discs;

	Tower();
	Tower(int discAmount);
	~Tower() = default;

	void nullify();
	void init();
	void print(int maxHeight);
};
