#pragma once
#include <iostream>
#include <ctime>

class Minigame
{

public:
	bool MiniGame1(bool& FirstMinigame);
	bool MiniGame2(bool& SecondMinigame);
	
	void wait(double seconds)
	{
		clock_t startClock = clock();
		double secondsAhead = seconds * CLOCKS_PER_SEC;
		// do nothing until the elapsed time has passed.
		while (clock() < startClock + secondsAhead);
		return;

	} //Used for the minigames, the equivelant of the same function in game.cpp
	
	time_t m_start, m_finish;
	int m_choice, m_randomdoor, m_decision, m_randomresult, m_lives;
	double m_dif;
	bool m_Done;


private:

};

