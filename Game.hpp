#ifndef GUARD_GAME_HPP
#define GUARD_GAME_HPP

#include "Grid.hpp"

class Game
{
public:
	//init functions
	Game();

	void Shuffle_Grid(int steps = 15);
	void Run();

	//IO
	int Read_Input();
	void Print_Grid();

	//main loop
	void Main_Loop();
	bool Change_Number(int number);

private:
	Grid mGrid;
};

#endif //GUARD_GAME_HPP
