#include "Grid.hpp"

#include <iostream>
#include <algorithm>

//for testing only, push that later into Draw_Grid.hpp and make it look nice
void Grid::print()
{
	for (const auto &iy : mGrid) {
		for (const auto &ix : iy) {
			std::cout << ix << " ";
		}
		std::cout << "\n";
	}
}

////
//init functions
////

Grid::Grid(size_t width, size_t height)
	: mWidth(width), mHeight(height)
{
	for (size_t i = 0; i != mHeight; ++i) {
		mGrid.push_back(std::vector<int>(mWidth));
	}

	Reset();
}

void Grid::Reset()
{
	int cnt = 1;
	for (size_t iy = 0; iy != mWidth; ++iy) {
		for (size_t ix = 0; ix != mHeight; ++ix) {
			if (cnt < mWidth * mHeight) {
				mGrid[iy][ix] = cnt; //give it a number
			}
			else { //if its the last element
				mGrid[iy][ix] = 0; //give it value 0 (actually unneccessary...or however you write that word)
			}

			++cnt;
		}
	}
}

////
//boolean functions
////

bool Grid::Is_Solved()
{
	int cnt = 1;
	for (size_t iy = 0; iy != mWidth; ++iy) {
		for (size_t ix = 0; ix != mHeight; ++ix) {
			if (cnt < mWidth * mHeight) { //if it isnt the last element
				if (!mGrid[iy][ix]) //if other than last is empty
					return false; //false
				else if (mGrid[iy][ix] != cnt) //if not correct order
					return false; //false
			}
			else {
				if (mGrid[iy][ix]) //if last isnt empty
					return false; //false
			}

			++cnt;
		}
	}

	return true; //otherwise everything is fine :)
}

bool Grid::Has_Adjacent(pair_pos pos)
{
	if (pos.first < mHeight && pos.first >= 0 && pos.second < mWidth && pos.second >= 0) { //if position is acutally valid
		//below empty?
		if (pos.first + 1 < mHeight && !mGrid[pos.first + 1][pos.second])
			return false;
		//above empty?
		if (pos.first > 0 && !mGrid[pos.first - 1][pos.second])
			return false;
		//right empty?
		if (pos.second + 1 < mWidth && !mGrid[pos.first][pos.second + 1])
			return false;
		//left empty?
		if (pos.second > 0 && !mGrid[pos.first][pos.second - 1])
			return false;
	}

	else {
		std::cerr << "@Grid::Has_Adjacent: Y OR X NUMBER TOO BIG OR SMALL!\n";
		return false;
	}

	//every adjacent member has isnt empty? then everything is fine :)
	return true;
}

////
//getters
////

Grid::pair_pos Grid::Get_Pos(int number)
{
	if (number >= mWidth * mHeight || number < 0) { //if number is out of range
		std::cerr << "@Grid::Get_Pos: NUMBER NOT IN RANGE!\n";
		return pair_pos(mHeight + 1, mWidth + 1); //error
	}

	int y, x;

	for (auto iy = mGrid.begin(); iy != mGrid.end(); ++iy) { //only loop through Height
		auto ix = std::find_if(iy->begin(), iy->end(), [number](int i) { //find the Wdith really fancy per find_if algorithm (mhhh...so smoooooooth)
			return i == number; //if tile is not empty and the right number is found, return that
		});

		if (ix != iy->end()) { //if number was found
			y = iy - mGrid.begin(); //calculate Y as int
			x = ix - iy->begin(); //and X as int
			break;
		}
	}

	return pair_pos(y, x); //and return dat bitch
}

int Grid::Get_Number(Grid::pair_pos pos)
{
	if (pos.first >= mHeight || pos.first < 0 || pos.second >= mWidth || pos.second < 0) {
		return 0;
	}

	return mGrid[pos.first][pos.second];
}

////
//setters
////

void Grid::Swap_Adjacent(Grid::pair_pos p1, Grid::pair_pos p2)
{
	if (p1.first > mHeight || p1.second > mWidth || p2.first > mHeight || p2.second > mWidth) { //dont have to check if below Null, because its unsigned so it can only be invalid by being greater than mHeight or mWidth
		std::cerr << "@Grid::Swap: VALUE p1 OR p2 TOO BIG OR TOO SMALL!!";
		return;
	}

	std::swap(mGrid[p1.first][p1.second], mGrid[p2.first][p2.second]);
}

////
//others
////

void Grid::Draw_Grid()
{
	for (const auto &iy : mGrid) { 
		for (const auto &ix : iy) {
			if (!ix)
				std::cout << "  ";
			else if (ix < 10)
				std::cout << " " << ix;
			else
				std::cout << ix;

			std::cout << " ";
		}
		std::cout << std::endl;
	}
}
