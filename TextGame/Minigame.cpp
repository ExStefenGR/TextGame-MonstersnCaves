#include "Minigame.h"


bool Minigame::MiniGame1(bool& FirstMinigame)
{
	m_lives = 3;
	srand((int)time(0));

	m_randomresult = rand() % 3 + 1; //Random number result

	std::cout << std::endl << "   Three paths, choose wisely which you can follow...         ";
	system("pause");
	std::cout << std::endl << "   three chances to get this right..        ";
	system("pause");
	std::cout << std::endl << "1. Left path" <<std::endl<<"2. Middle path" << std::endl << "3. Right path" << std::endl << std::endl;

	m_Done = false;
	while (!m_Done)
	{
		std::cin.clear();
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
			system("pause");
			FirstMinigame = true;

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

	/* Used below expression in case the class didn't work as intended
	std::cout << std::endl << "reached a place I shouldn't? thats ok.";
	*/
	
	return true;
}
bool Minigame::MiniGame2(bool& SecondMinigame)
{
	m_lives = 3;

	srand((int)time(0));

	m_randomresult = rand() % 5 + 1; //Random number result

	std::cout << std::endl << "   Five paths, choose wisely which you can follow...         ";
	system("pause");
	std::cout << std::endl << "   three chances to get this right..        ";
	system("pause");
	std::cout << std::endl << "   Also, You have 5 seconds to get this right..Or You'll get trapped...        ";
	system("pause");
	std::cout << std::endl << "1. Left Path" << std::endl << "2. Middle Path" << std::endl << "3. Right Path" << std::endl <<"4. Up Path" <<std::endl<< "5. Down Path" << std::endl << std::endl;
	time(&m_start);

	m_Done = false;
	while (!m_Done)
	{
		std::cin.clear();
		if (!(std::cin >> m_decision))
		{
			std::cin.clear();
			while (std::cin.get() != '\n');
			std::cout << "Invalid Input!" << std::endl << std::endl;

		}
		time(&m_finish);
		m_dif = difftime(m_finish, m_start);

		if (m_randomresult == m_decision && m_lives != 0)
		{
			system("cls");
			std::cout << std::endl << "This is correct..Move on, Champion..";
			system("pause");
			SecondMinigame = true;
			m_Done = true;
		}
		else if (m_lives == 0 || m_dif >= 5)
		{
			
			system("cls");
			std::cout << std::endl << "The paths leading to the Monster Cave have closed around you and now you can only exit and try again!";
			SecondMinigame = false;
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

	std::cout << std::endl << "The paths leading to the Monster Cave have closed around you and now you can only exit and try again!";

	/* Used below expression in case the class didn't work as intended
	std::cout << std::endl << "reached a place I shouldn't? thats ok.";
	*/
	return true;
}
