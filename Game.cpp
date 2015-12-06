#include "Game.hpp"

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

////
//init functions
////

Game::Game()
	: mGrid(4, 4)
{ 

}

void Game::Run()
{
	Shuffle_Grid(3);
	Main_Loop();
}


//I couuuuuld implemet an interface, so that you can choose your difficulty
//like doing it per number or saying easy is 20 steps, medium is 50 steps, hard is 200 steps and impossible is 1*10^6 steps
//I couuuuuld also implement a better system for using it, but I already know how to do those things and it would only consume time, soooo
//fuck off! This game works, and I like that, so the logical thing to do is leave it as it is and never touch it again.... :)
void Game::Shuffle_Grid(int steps)
{
	std::vector<std::pair<size_t, size_t>> dirs;
	auto calc_rand = [](int num1, int num2) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(num1, num2);

		return int(dist(gen));
	};
	std::pair<size_t, size_t> pos_emp;
	
	for (int i = 0; i != steps; ++i) {
		//calculate possible steps
		pos_emp = mGrid.Get_Pos_Empty();
		int cnt = 1;
		//push all possible points inot dirs
		dirs.push_back(std::make_pair(pos_emp.first + 1, pos_emp.second));
		dirs.push_back(std::make_pair(pos_emp.first - 1, pos_emp.second));
		dirs.push_back(std::make_pair(pos_emp.first, pos_emp.second + 1));
		dirs.push_back(std::make_pair(pos_emp.first, pos_emp.second - 1));

		dirs.erase(std::remove_if(dirs.begin(), dirs.end(), [&](std::pair<size_t, size_t> i) { 
			return !mGrid.Get_Number(i);
		}), dirs.end());

		//decide which he should go
		mGrid.Swap_Adjacent(dirs[calc_rand(0, dirs.size() - 1)], pos_emp);

		dirs.clear();
	}
}

////
//IO
////

int Game::Read_Input()
{
	int input = -1;

	while (true) {
		std::cout << "Input number you want to change: \n";
		try {
			std::cin >> input;
			if (!std::cin)
				throw "Input isnt a number you dumbfuck!";
		}
		catch (std::exception &e) {
			std::cerr << "Exceptions thrown during input: " << e.what() << std::endl;
		}

		if (input > 0 && input < mGrid.Get_Size())
			return input;
		else if (input < 1)
			std::cerr << "Input too small, try again!\n";
		else
			std::cerr << "Input too big, try again!\n";

		std::cout << std::endl;
	}
}

void Game::Print_Grid()
{
	std::cout << std::endl;
	mGrid.Draw_Grid();
	std::cout << std::endl;
}

void Game::Main_Loop()
{
	int change_number = 0;

	while (!mGrid.Is_Solved()) {

		system("cls");

		Print_Grid();
		do {
			change_number = Read_Input();
		} while (!Change_Number(change_number));
	}

	system("cls");

	mGrid.Draw_Grid();

	std::cout << "\n\n\nCongratulations, you won!!\n\n";
}

bool Game::Change_Number(int number)
{
	std::pair<size_t, size_t> pos_num, pos_emp;

	pos_num = mGrid.Get_Pos(number);
	if (mGrid.Has_Adjacent(pos_num)) {
		std::cerr << "Entered Number doesn't have any empty adjacent fields! Please Enter again!\n";
		return false;
	}

	pos_emp = mGrid.Get_Pos_Empty();

	mGrid.Swap_Adjacent(pos_num, pos_emp);

	return true;
}
