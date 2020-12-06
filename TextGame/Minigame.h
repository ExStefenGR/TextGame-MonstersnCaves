#pragma once
#include <iostream>
#include <ctime>

class Minigame
{

public:
	bool MiniGame1(bool& FirstMinigame);
	bool MiniGame2(bool& SecondMinigame);

	
	time_t m_start, m_finish;
	int m_choice, m_randomdoor, m_decision, m_randomresult, m_lives;
	double m_dif;
	bool m_Done;


private:

};

