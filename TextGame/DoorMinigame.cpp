#include "DoorMinigame.h"


bool DoorMinigame::execute(bool &FirstMinigame)
{
	m_lives = 3;
	srand((int)time(0));

	m_randomresult = rand() % 3 + 1; //Random number result

	std::cout << std::endl << "   Three paths, choose wisely which you can follow...         ";
	system("sleep 2");
	std::cout << std::endl << "   three chances to get this right..        ";
	system("sleep 2");
	std::cout << std::endl << "1. Left path" <<std::endl<<"2. Middle path" << std::endl << "3. Right path" << std::endl << std::endl;
	system("sleep 2");
	while (!m_Done)
	{
		if (!(std::cin >> m_decision))
		{
			std::cin.clear();
			while (std::cin.get() != '\n');
			std::cout << "Invalid Input!" << std::endl << std::endl;

		}

		if (m_randomresult == m_decision && m_lives != 0)
		{
			system("cls");
			std::cout << std::endl << "This is correct..Move on, Champion..";
			system("sleep 5");
			return true;

			m_Done = true;
		}
		else if (m_lives == 0)
		{
			system("cls");
			std::cout << std::endl << "Okay, lets try this again....";
			return false;
			m_Done = true;
		}
		else if (m_randomresult != m_decision)
		{
			system("cls");
			std::cout << std::endl << "Incorrect..." << std::endl;
			m_lives--;
		}
	}

	std::cout << std::endl << "reached a place I shouldn't? thats ok.";
	
	return true;
}
