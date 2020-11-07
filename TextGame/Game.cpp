#include <iostream>
#include <string>

//You can refer other classes here
void crossroads();
void startpoint();
void mountain();
void camp();
void river1(); //gameover
void river2(); //fight
void ruins();
void town();
void monstercave();
void waterfall();
void gameover();

void SwitchState();

//User's stats
std::string _Name;
int _Damage = 1;
int _HP = 10;

//score Variable
int _Score;

//Character Items
bool _Sword = {};
bool _Lighter = {};
bool _Map = {};
bool _Scroll = {};

bool _Torch = true;

//Character Stats
int GearWeight = 1;

//Situational variables
int _locator; //For actual locations (Mountain/River...)
int _direction; //For directions within locations (NPC/People)
int _decision;
bool Done{}; //This is so the Switch gets repeated until the Player uses the correct variable value


void SwitchState()
{
	while (!Done)
	{
		if (!(std::cin >> _decision))
		{
			std::cin.clear();
			while (std::cin.get() != '\n');
			std::cout << "Invalid Input!" << std::endl << std::endl;
			continue;
		}

		switch (_decision)
		{
		case 1:
			if (_locator == 0)
			{
				mountain();
			}
			else if (_locator == 1)
			{
				crossroads();
			}
			else if (_locator == 2)
			{
				river2();
			}
			else if (_locator == 3)
			{
				crossroads();
			}
			else if (_locator == 4)//River2 is fight so if the player wins they go to Hideout
			{
				crossroads();
			}
			else if (_locator == 6)
			{
				crossroads();
			}
		case 2:
			if (_locator == 0)
			{
				camp();
			}
			else if (_locator == 2)
			{
				ruins();
			}
			else if (_locator == 5)//????Why??
			{
				crossroads();
			}

		default:
			std::cout << std::endl << "Please enter a valid number" << std::endl;
			break;
		}
	}
}

//self-explanatory
void gameover()
{

}

//start
int main()
{


	std::cout << "Greetings young wanderer.." << std::endl << "What is your name?" << std::endl;
	std::cin >> _Name;
	std::cout << "Shall we begin with your adventure.. " << _Name << " ?" << std::endl;
	system("pause");
	system("clear");
	std::cin.clear();
	std::cout << "Good luck and bear in mind your adventure has many co-existing and alternate realities.. " << _Name << std::endl;
	system("pause");
	system("clear");
	startpoint();
}

//0
void startpoint()
{
	_locator = 0;

	std::cout << "You awake and find yourself in a large field with a few pathroads.." << std::endl
		<< "What you have on you is just a torch but nothing to light it up yet.." << std::endl
		<< "Gear weighs " << GearWeight << " Kilograms" << std::endl
		<< "Where would you like to go?" << std::endl
		<< "1. Towards mountain" << std::endl
		<< "2. Towards camp" << std::endl
		<< "3. Towards river" << std::endl << std::endl;
	SwitchState();
}

//1
void mountain()
{
	system("clear");
	_locator = 1;

	std::cout << "You have finally arrived on the side of the mountain" << std::endl
		<< "You notice a unique object stuck in the rocks that is out of the ordinary" << std::endl
		<< "Pick up?" << std::endl
		<< "1. Yes" << std::endl
		<< "2. No" << std::endl << std::endl;

	std::cin.clear();

	while (!Done)
	{
		if (!(std::cin >> _decision))
		{
			std::cin.clear();
			while (std::cin.get() != '\n');
			std::cout << "Invalid Input!" << std::endl << std::endl;
			continue;
		}

		switch (_decision)
		{
		case 1:
			system("clear");
			std::cout << std::endl << "o==={==>====>==>" << std::endl
				<< "You have found a sword!" << std::endl;

			_Sword = true;
			system("pause");
			Done = true;

			break;
		case 2:
			system("clear");
			std::cout << std::endl << "You have left the object untouched" << std::endl;
			
			system("pause");
			Done = true;
			break;
		default:
			std::cout << std::endl << "Please decide with" << std::endl
				<< "1. Yes" << std::endl
				<< "2. No" << std::endl;

			Done = false;
			break;
		}
	}
		_decision = {}; //Reset the variables since I don't need them
		Done = {};

	system("clear");
	if (_Sword == true)
	{
		_Damage += 5;
		std::cout << std::endl << "Your damage has increased to " << _Damage << std::endl;
		system("pause");
	}
	std::cout << std::endl << "You have heard an echo in the distance.." << std::endl
			  << "You follow the road the echo came from regardless of the consequences" << std::endl;
	system("pause");
	system("clear");
	std::cin.clear();
	crossroads();
}

//7
void camp()
{
	_locator = 7;
	std::cout << std::endl << "camp" << std::endl;
	SwitchState();
}

//8
void river1()
{
	_locator = 8;
	std::cout << std::endl << "river" << std::endl;
	SwitchState();
}

//2
void crossroads()
{
	_locator = 2;
	std::cout << std::endl << "Crossroads" << std::endl;
	SwitchState();
}

//3
void river2()
{
	_locator = 3;
	std::cout << std::endl << "River2" << std::endl;
	SwitchState();
}

//4
void hideout()
{
	_locator = 4;
	std::cout << std::endl << "Mountain" << std::endl;
	SwitchState();
}

//5
void ruins()
{
	_locator = 5;
	std::cout << std::endl << "Ruins" << std::endl;
	SwitchState();
}

//6
void town()
{
	_locator = 6;
	std::cout << std::endl << "town" << std::endl;
	SwitchState();
}

//9
void monstercave()
{
	_locator = 9;
	std::cout << std::endl << "Monster Cave" << std::endl;
	SwitchState();
}

//10
void waterfall()
{
	_locator = 10;
	std::cout << std::endl << "Waterfall" << std::endl;
	SwitchState();
}