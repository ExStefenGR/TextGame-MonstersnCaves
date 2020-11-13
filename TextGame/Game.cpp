#include <iostream>
#include <string>


//enum for places that will replace numbers
enum Location
{
	START_POINT,
	MOUNTAIN,
	CROSSROADS,
	RIVER2,
	HIDEOUT,
	RUINS,
	TOWN,
	CAMP,
	RIVER1,
	MONSTER_CAVE,
	WATERFALL,
	FIGHT1,
	FIGHT2,
	GAMEOVER
};


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
void hideout();
void waterfall();
void fight();
void gameover();

void SwitchState();

//User's stats
struct Player
{
	std::string _Name;
	int DMG = 0;
	int HP = 0;
	int Score = 0;
};

Player MainCharacter;
Player Thief;

//Character Items
struct Items
{
	bool Sword = {};
	bool Lighter = {};
	bool Map = {};
	bool Scroll = {};
	bool Torch = true;
	int GearWeight = 1;
};

Items Inventory;

//Situational variables
int locator; //For actual locations (Mountain/River...)
int _direction; //For directions within locations (NPC/People)
int _decision;
bool trigger; //Used for various situations
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
			if (locator == START_POINT)
			{
				mountain();
			}
			else if (locator == CROSSROADS)
			{
				river2();
			}
		
			//River2 is a combat fight

			else if (locator == HIDEOUT)
			{
				crossroads();
			}
			else if (locator == RUINS)
			{
				std::cout << std::endl << "Not quite right, try again" << std::endl;
				SwitchState();
			}
			else if (locator == TOWN)
			{
				crossroads();
			}
			break;
		case 2:
			if (locator == START_POINT)
			{
				camp();
			}
			else if (locator == CROSSROADS)
			{
				ruins();
			}
			else if (locator == RUINS)
			{
				crossroads();
			}
			break;
		case 3:
			if (locator == START_POINT)
			{
				river1();
			}
			else if (locator == MOUNTAIN)
			{
				std::cout << std::endl << "There is only One direction here traveller... Try again?" << std::endl;
				SwitchState();
			}
			else if (locator == CROSSROADS)
			{
				town();
			}
			else if (locator == HIDEOUT)
			{
				std::cout << std::endl << "There is only One direction here traveller... Try again?" << std::endl;
				SwitchState();
			}
			else if (locator == RUINS)
			{
				std::cout << std::endl << "There is only two directions here traveller... Try again?" << std::endl;
				SwitchState();
			}
		case 4:
			if (locator == CROSSROADS && trigger == true)
			{
				hideout();
			}
			else if (locator == CROSSROADS && trigger == false)
			{
				std::cout << std::endl << "You see a building but you will have to go through the river first.." << std::endl;
				system("pause");
				system("cls");
				crossroads();
			}
			break;

		default:
			std::cout << std::endl << "Please enter a valid number" << std::endl;
			Done = false;
			break;
		}
	}
}



//start
int main()
{
	MainCharacter.DMG = 1;
	MainCharacter.HP = 10;
	MainCharacter.Score = 0;
	system("cls");

	std::cout << "Greetings young wanderer.." << std::endl << "What is your name?" << std::endl;
	std::cin >> MainCharacter._Name;
	std::cout << "Shall we begin with your adventure.. " << MainCharacter._Name << " ?" << std::endl;
	system("pause");
	system("cls");
	std::cin.clear();
	std::cout << "Good luck and bear in mind your adventure has many co-existing and alternate realities.. " << MainCharacter._Name << std::endl;
	system("pause");
	system("cls");
	startpoint();
}

//self explanatory
void gameover()
{
	system("cls");
	std::cin.clear();
	Done = {};

	std::cout << std::endl << "        Game over        " << std::endl << std::endl << std::endl;
	system("pause");

	std::cout << std::endl << "You did well, " << MainCharacter._Name << "." << std::endl

		<< "Final stats" << std::endl
		<< "Highest Damage dealt " << MainCharacter.DMG << std::endl
		<< "Progression score " << MainCharacter.Score << std::endl << std::endl
		<< "Play again?" << std::endl
		<< "1. Play Again" << std::endl
		<< "2. Exit" << std::endl;

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

			main();
			Done = true;
			break;
		case 2:

			system("exit");
			
			Done = true;
			break;
		default:
			std::cout << std::endl << "Please decide..." << std::endl;
		}
	}
}

//START_POINT
void startpoint()
{
	locator = START_POINT;

	std::cout << "You awake and find yourself in a large field with a few pathroads.." << std::endl
		<< "What you have on you is just a torch but nothing to light it up yet.." << std::endl
		<< "Gear weighs " << Inventory.GearWeight << " Kilograms" << std::endl
		<< "Where would you like to go?" << std::endl
		<< "1. Towards mountain" << std::endl
		<< "2. Towards camp" << std::endl
		<< "3. Towards river" << std::endl << std::endl;
	SwitchState();
}

//MOUNTAIN
void mountain()
{
	system("cls");
	locator = MOUNTAIN;

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
			system("cls");
			std::cout << std::endl << "o==={==>====>==>" << std::endl
				<< "You have found a sword!" << std::endl;

			Inventory.Sword = true;
			system("pause");
			Done = true;

			break;
		case 2:
			system("cls");
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

	system("cls");
	if (Inventory.Sword == true)
	{
		MainCharacter.DMG += 5;
		std::cout << std::endl << "Your damage has increased to " << MainCharacter.DMG << std::endl;
		system("pause");
	}

	std::cout << std::endl << "You have heard an echo in the distance.." << std::endl
			  << "You follow the road the echo came from regardless of the consequences" << std::endl;

	system("pause");
	system("cls");
	std::cin.clear();
	crossroads();
}

//CAMP
void camp()
{
	locator = CAMP;
	std::cout << std::endl << "camp" << std::endl;
	SwitchState();
}

//RIVER1
void river1()
{
	locator = RIVER1;
	std::cout << std::endl << "river" << std::endl;
	SwitchState();
}

//CROSSROADS
void crossroads()
{
	locator = CROSSROADS;
	std::cout << std::endl << "You have arrived in a field that has a cross-like shape, where do you wish to go?" << std::endl;

	SwitchState();
}

//RIVER2
void river2()
{
	locator = FIGHT1;
	std::cout << std::endl << "River2" << std::endl;
	fight();
}

//HIDEOUT
void hideout()
{
	locator = HIDEOUT;
	std::cout << std::endl << "Mountain" << std::endl;
	SwitchState();
}

//RUINS
void ruins()
{
	locator = RUINS;
	std::cout << std::endl << "Ruins" << std::endl;
	SwitchState();
}

//TOWN
void town()
{
	locator = TOWN;
	std::cout << std::endl << "town" << std::endl;
	SwitchState();
}

//MONSTER_CAVE
void monstercave()
{
	locator = MONSTER_CAVE;
	std::cout << std::endl << "Monster Cave" << std::endl;
	SwitchState();
}

//WATERFALL
void waterfall()
{
	locator = WATERFALL;
	std::cout << std::endl << "Waterfall" << std::endl;
	SwitchState();
}

void fight()
{
	//Thief in River 2
	Thief.DMG = 3;
	Thief.HP = 15;

	system("cls");
	if (locator == FIGHT1)
	{
		
		while (Thief.HP > 0 && MainCharacter.HP > 0) //Winning condition, losing condition within loop
		{
			system("cls");


			std::cout << std::endl << "You're being ambushed by a thief!" << std::endl << std::endl
				<< "The thief has " << Thief.HP << " HP" << std::endl << std::endl
				<< "You have " << MainCharacter.HP << " HP"<< std::endl << std::endl
				<< "What do you do?" << std::endl
				<< "1. Attack" << std::endl
				<< "2. Use Item" << std::endl;
			if (!(std::cin >> _decision))
			{
				std::cin.clear();
				while (std::cin.get() != '\n');
				std::cout << "Invalid Input!" << std::endl << std::endl;
				continue;
			}
			if (_decision == 1)
			{
				Thief.HP -= MainCharacter.DMG;
				std::cout << std::endl << "You attack the thief with " << MainCharacter.DMG << " Damage!" << std::endl;

			}
			else if (_decision == 2)
			{
				system("cls");
				std::cout << std::endl << "Which item do you wish to use?" << std::endl
						  << "1. Torch" << std::endl
						  << "2. Go back" << std::endl;

				if (!(std::cin >> _decision))
				{
					std::cin.clear();
					while (std::cin.get() != '\n');
					std::cout << "Invalid Input!" << std::endl << std::endl;
					continue;
				}

				Done = {};

				switch (_decision)
				{
				case 1:
				{
					if (Inventory.Lighter == true)
					{
						Thief.HP -= 10;
						std::cout << std::endl << "You have used the lighter to light up the torch and use it against the thief!" << std::endl;
						system("pause");
					}
					else if (Inventory.Lighter == false)
					{
						std::cout << std::endl << ("You do not have a lighter!") << std::endl;
						system("pause");
					}
				}
				break;

				case 2:
				{
					continue;
				}
				default:
					break;
				}
			}
			MainCharacter.HP -= Thief.DMG;

			std::cout << "Thief attacks with " << Thief.DMG << std::endl;
			system("pause");
		}
	}
	if (MainCharacter.HP < 0)
	{
		gameover();
	}
	//Rewards
	MainCharacter.Score += 5;
	MainCharacter.DMG += 2;
	MainCharacter.HP = 10;
	MainCharacter.HP += 8;
	std::cout << "You have defeated the thief!" << std::endl << std::endl
		<< "You gained experience from this fight, You can deal " << MainCharacter.DMG << " Damage now!" << std::endl;
	system("pause");
	gameover();//Game over for now

	if (locator == FIGHT2)
	{

	}
}