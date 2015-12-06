#ifndef GUARD_GRID_HPP
#define GUARD_GRID_HPP

#include <vector>
#include <utility>

class Grid
{
private:
	typedef std::pair<size_t, size_t> pair_pos;

public:
	void print();

	//init functions
	Grid(size_t width, size_t height);
	
	void Reset();
	
	//boolean functions
	bool Is_Solved();
	bool Has_Adjacent(pair_pos pos);
	inline bool Has_Adjacent(int y, int x) { return Has_Adjacent(pair_pos(y, x)); }
	
	//getters
	pair_pos Get_Pos(int number);
	inline pair_pos Get_Pos_Empty() { return Get_Pos(0); }
	int Get_Number(pair_pos pos);
	inline std::vector<std::vector<int>> Get_Raw_Grid() { return mGrid; }
	inline int Get_Size() { return mWidth * mHeight; }

	//setters
	void Swap_Adjacent(pair_pos p1, pair_pos p2);

	//others
	void Draw_Grid();
private:
	const size_t mHeight;
	const size_t mWidth;

	std::vector<std::vector<int>> mGrid; //vector of vector of pairs of ints and bools for the 
};

#endif //GUARD_GRID_HPP
