#include <iostream>
#include <string>
#include <ctime>


//enum for places that will replace numbers
enum Location
{
	START_POINT,
	MOUNTAIN,
	CROSSROADS,
	RIVER,
	HIDEOUT,
	RUINS,
	TOWN,
	CAMP,
	LAKE,
	MONSTER_CAVE,
	WATERFALL,
	FIGHT1,
	FIGHT2,
	LAKEMONSTER, //You can go back to lake AFTER RUINS (Just more strength)
	VOLCANO,  //Optional Boss BroadSword (more damage)
	CASTLE, //Optional Boss Magic spell Fire (new spell that casts 10 + the DMG stat)
	THIEFGUILD, //Optional Boss (More damage but many enemies, player will have to wait for his/her turn)
	GAMEOVER
};


//You can refer other classes here
void crossroads();
void startpoint();
void mountain();
void camp();
void lake(); //gameover
void river(); //Thief encounter
void ruins();
void town();
void monstercave();
void hideout();
void waterfall();
void fight(); //All the fights and secret bossfights
void gameover();

void SwitchState();

//timer
time_t init, final; //Used for one of the easter eggs with the Old man in Town
double dif;
//User's stats
struct Entity
{
	std::string Name;
	int DMG = 0;
	int HP = 0;
	int Score = 0;
	void increase(){ Score += 5; }
	void Set_Values(int x, int y){HP = x; DMG = y;}
	void SetName(std::string x){Name = x;}
};

Entity MainCharacter;
Entity Thief;
Entity SwampMonster;

//Character Items
struct Items
{
	bool Sword = false;
	bool Lighter = false;
	bool Map = false;
	bool Scroll = false;
	bool Torch = false;
	int count = 0;
	int GearWeight = 1;
	void increase() { count++;}
	void decrease() { count--;}
	void reset()
	{
		
		bool Sword = false;
		bool Lighter = false;
		bool Map = false;
		bool Scroll = false;
		bool Torch = false;
		int count = 1;
		int GearWeight = 1;
	}
};

Items Inventory;

//Situational variables
int locator; //For actual locations (Mountain/River...)
int _direction; //For directions within locations (NPC/People)
int _decision;
bool trigger1;
bool trigger2;
bool trigger3;
bool optionalFights;//Used for various situations
bool Done{}; //This is so the Switch gets repeated until the Player uses the correct variable value

void stats(Items* Inventory)
{
	std::cout << std::endl << "Your Health is at " << MainCharacter.HP << " HP" << std::endl
					       << "Your Damage is at " << MainCharacter.DMG << " Damage" << std::endl
						   << "Your gear weighs " << Inventory->GearWeight << " Kilograms and" << std::endl
						   << "You have " << Inventory->count << " Items in your possession" <<std::endl
						   << "Items you have acquired so far" << std::endl;

	if (Inventory->Torch == true)
	{

		std::cout << std::endl << "Torch" << std::endl;

	}
	if (Inventory->Sword == true)
	{

		std::cout << std::endl <<"Sword"<< std::endl;

	}
	if (Inventory->Map == true)
	{
		std::cout << std::endl << "Map" << std::endl;
	}
	if (Inventory->Lighter == true)
	{
		std::cout << std::endl << "Lighter" << std::endl;
	}
	if (Inventory->Scroll == true)
	{
		std::cout << std::endl << "Scroll" << std::endl;
	}
	if (Inventory->count < 1)
	{
		std::cout << std::endl << "None" << std::endl;
	}
	std::cout << std::endl;
}

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
			else if (locator == CROSSROADS && trigger1 == false)
			{
				river();
			}
			else if (locator == CROSSROADS && trigger1 == true)
			{
				std::cout << std::endl << "It appears that there is no reason to go to the river again" << std::endl;
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
			else if (locator == CROSSROADS && Inventory.Map == true && trigger1 == true)
			{
				ruins();
			}
			else if (locator == CROSSROADS && Inventory.Map == false)
			{
				std::cout << std::endl << "There is nothing there?" << std::endl;
			}
			else if (locator == RUINS)
			{
				crossroads();
			}
			break;
		case 3:
			if (locator == START_POINT)
			{
				lake();
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
				std::cout << std::endl << "nonono" << std::endl;
			}
		case 4:
			if (locator == CROSSROADS && trigger1 == true)
			{
				hideout();
			}
			else if (locator == CROSSROADS && trigger1 == false)
			{
				std::cout << std::endl << "You see a building but you will have to go through the river first.." << std::endl;
				system("pause");
				system("cls");
				crossroads();
			}
			break;
		case 5:
			stats(&Inventory);
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
	//Resetting variables in case player wants to play again after game-over
	Inventory.reset();

	Inventory.Torch = true;
	Inventory.increase();

	MainCharacter.DMG = 1;
	MainCharacter.HP = 10;
	MainCharacter.Score = 0;

	system("cls");

	std::cout << "Greetings young wanderer.." << std::endl << "What is your name?" << std::endl;
	std::cin >> MainCharacter.Name;
	std::cout << "Shall we begin with your adventure.. " << MainCharacter.Name << " ?" << std::endl;
	system("pause");
	system("cls");
	std::cin.clear();
	std::cout << "Good luck and bear in mind your adventure has many co-existing and alternate realities.. " << MainCharacter.Name << std::endl;
	system("pause");
	system("cls");
	startpoint();
}

//GameOver sequence
void gameover()
{
	system("cls");
	std::cin.clear();
	Done = {};

	std::cout << std::endl << "        Game over        " << std::endl << std::endl << std::endl;
	system("pause");

	std::cout << std::endl << "You did well, " << MainCharacter.Name << "." << std::endl

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
		<< "Where would you like to go?" << std::endl << std::endl
		<< "1. Towards mountain" << std::endl
		<< "2. Towards camp" << std::endl
		<< "3. Towards Lake" << std::endl
		<< "5. Check your stats"<< std::endl << std::endl;
	SwitchState();
}

//MOUNTAIN
void mountain()
{
	system("cls");
	locator = MOUNTAIN;

	std::cout << "You have finally arrived on the side of the mountain" << std::endl
		<< "You notice a unique object stuck in the rocks that is out of the ordinary" << std::endl
		<< "Pick up?" << std::endl <<std::endl
		<< "1. Yes" << std::endl
		<< "2. No" << std::endl << std::endl
		<< "5. Check your stats" << std::endl << std::endl;;

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

			for (size_t i = 0; i < 3; i++)
			{


				system("color 09");
				std::cout << std::endl << "o==={==>====>==>" << std::endl
					<< "You have found a sword!" << std::endl;
				system("color 07");

				system("cls");
			}
			
			system("color 07");

			std::cout << std::endl << "o==={==>====>==>" << std::endl
				<< "You have found a sword!" << std::endl;
			system("color 07");

			Inventory.Sword = true;
			Inventory.increase();
			system("pause");
			Done = true;

			break;
		case 2:
			system("cls");
			std::cout << std::endl << "You have left the object untouched" << std::endl;
			
			system("pause");
			Done = true;
			break;
		case 5:
			stats(&Inventory);
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
		Inventory.GearWeight += 5;
		std::cout << std::endl << "Your damage has increased to " << MainCharacter.DMG << std::endl
			<< "Gear weight increased! +" << Inventory.GearWeight << std::endl;
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
	std::cout << std::endl << "You find yourself near an uninhibited camp.." << std::endl
		<< "You find the lighter that is required to light up the torch, do you pick it up?" << std::endl
		<< "1. Yes" << std::endl << "2. No"<<std::endl;
	while (!Done)
	{
		if (!(std::cin >> _decision))
		{
			std::cin.clear();
			while (std::cin.get() != '\n');
			std::cout << "Invalid Input!" << std::endl << std::endl;
			continue;
		}

		if (_decision == 1)
		{
			Inventory.increase();
			Inventory.Lighter = true;
			std::cout << std::endl << "You add the lighter to your inventory and go back, Something's changed..." << std::endl;
			Done = true;
		}
		else
		{
			std::cout << std::endl << "You have heard an echo in the distance.." << std::endl
				<< "You follow the road the echo came from regardless of the consequences.." << std::endl;
			Done = true;
		}
	}
	Done = {};
	system("pause");
	system("cls");
	crossroads();
}

//LAKE
void lake()
{
	locator = LAKE;

	std::cout <<std::endl<< "You arrive at a lake..." << std::endl;

	system("pause");
	system("cls");

	std::cout << std::endl << "The center of the lake has a big chest, try to go towards it?" << std::endl
		<<"1. Yes"<<std::endl << "2. No" << std::endl <<std::endl;
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
			{
			std::cout << std::endl << "You have been trapped in a quicksand!" << std::endl;
			system("pause");
			gameover();
			}
		break;
			case 2:
			{
			locator = LAKEMONSTER;
			fight();
			}
		break;
			default:
			{
			std::cout << std::endl << "Try again..";
			}
		}
	}
}

//CROSSROADS
void crossroads()
{
	system("cls");
	system("color 07");
	locator = CROSSROADS;

	if (trigger1 == false)
	{
		std::cout << std::endl << "You have arrived in a field that has a cross-like shape, where do you wish to go?" << std::endl
			<< std::endl << "1. Towards River"
			<< std::endl << "3. Towards Town"
			<< std::endl << "5. Check stats" << std::endl << std::endl;
	}
	else if (Inventory.Scroll == true && Inventory.Map == true)
	{
		std::cout << std::endl << "You have arrived in a field that has a cross-like shape, where do you wish to go?" << std::endl
			<< std::endl << "2. Towards Ruins"
			<< std::endl << "3. Towards Town"
			<< std::endl << "4. Towards Hideout"
			<< std::endl << "5. Check stats" << std::endl << std::endl;
	}
	else if (trigger1 == true)
	{
		std::cout << std::endl << "You have arrived in a field that has a cross-like shape, where do you wish to go?" << std::endl
			<< std::endl << "3. Towards Town"
			<< std::endl << "4. Towards Hideout"
			<< std::endl << "5. Check stats" << std::endl << std::endl;
	}


	SwitchState();
}

//RIVER
void river()
{
	locator = FIGHT1;
	std::cout << std::endl << "You approach the bank of a river, There seems to be a cave on the other side covered by logs and leaves.. " << std::endl;
	system("pause");
	system("cls");
	std::cout << std::endl << "???: Well Well... Look what luck brought us.." << std::endl
		      <<"???: Lets see how much Gold you got on you, shall we..?" << std::endl;
	system("pause");
	system("clear");
	fight();
}

//HIDEOUT
void hideout()
{
	locator = HIDEOUT;
	system("cls");
	Done = false;
	if (Inventory.Scroll == false)
	{
		std::cout << std::endl << "You're inside the thief's hideout, the area is really dusty" << std::endl
			<< std::endl << "Search up the area?" << std::endl << "1. Yes" << std::endl << "2. No" << std::endl << std::endl;
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
			{
				system("cls");
				Inventory.Scroll = true;
				Inventory.increase();
				system("color 05");
				std::cout << std::endl <<
						 " ,-----------." << std::endl <<
					    " (_/           )" << std::endl <<
						 "|_           |" << std::endl <<
						 " |    ***    |" <<std::endl <<
						 " |  ***  *   |" <<std::endl << 
					     " |_    **   _|_" <<std::endl <<
					    " _ |            |" <<std::endl <<
					  " (_ / _____(*)___ /" <<std::endl <<
					"You have found a scroll with mysterious writings!" << std::endl; //easter egg, the hash stars are the main areas and the monster cave is the last mission
				
				system("pause");
				system("color 07");
				system("cls");

				crossroads();

			}
			break;

			case 2:
			{
				std::cout << std::endl << "You have left the place without touching anything, who knows what could have been there.." << std::endl;
				system("pause");
				std::cout << std::endl << "Heading back to cross roads.." << std::endl;

				system("pause");
				system("cls");
				crossroads();
			}
			break;

			default:
				std::cout << std::endl << "Please decide, (1 = Yes, 2 = No)" << std::endl << std::endl;
				Done = false;
				break;
			}

		}
	}

	else if (Inventory.Scroll == true)
	{
		std::cout << std::endl << "You're inside the thief's hideout, looks like there is nothing here, head back?" << std::endl
			<< std::endl << "0. Go back to crossroads" << std::endl << std::endl;

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
			case 0:

				crossroads();

			default:
				std::cout << std::endl << "Not a valid move" << std::endl;
				break;
			}

		}

	
	}
}

//RUINS
void ruins()
{
	locator = RUINS;

	std::cout << std::endl << "You arrive at an ancient place filled with relics.." << std::endl;
	
	system("pause");
	system("cls");
	
	std::cout << std::endl << "The Scroll from your inventory is radiating with a purple glow!" << std::endl;
	
	system("pause");
	system("cls");
	
	Inventory.Scroll = false;
	Inventory.decrease();
	std::cout << "The scroll has vanished and a door catacomb has revealed the MONSTER CAVE" << std::endl << std::endl;

	stats(&Inventory);

	system("pause");
	system("cls");

	system("color 04");

	std::cout << std::endl << "An ominous aura fills the place, Whenever you are ready.." << std::endl << std::endl
		<< "1. Continue inside the MONSTER CAVE" << std::endl
		<< "2. Go back and prepare" << std::endl << std::endl;

	optionalFights = true; //Player can train in other areas because the next section of the code might use srand for damage

	SwitchState();
}

//TOWN
void town()
{
	system("cls");
	locator = TOWN;
	if (trigger1 == false)
	{
		system("cls");
		std::cout << std::endl << "You enter an area that seems like a village." << std::endl
			<< "most of the shops are closed and it almost feels like no one's here.." << std::endl;
		system("pause");
		system("cls");
		std::cout << std::endl << "Go back to the cross-field?" << std::endl << "1. Yes" <<std::endl << std::endl;
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
			  {
				crossroads();
				Done = true;
				break;
			  }
			default:
				std::cout << "You only have one option " << MainCharacter.Name;
				Done = false;
				break;
			}
		}
	}
	else if (trigger3 == true)
	{
		system("cls");

		std::cout << std::endl << "Old Man: Be careful out there.. " << MainCharacter.Name << std::endl << std::endl;

		system("pause");

		crossroads();

	}
	else if (trigger1 == true && Inventory.Scroll == true)
	{
		std::cout << std::endl << "You approach the Old man in the empty town to seek answers for the mysterious scroll you have found" << std::endl << std::endl;

		system("pause");
		system("cls");

		std::cout << std::endl << "Old Man: Oh hi there.. " << MainCharacter.Name << ", what brings you here today?" << std::endl
			<< "Old Man: Oh...You found one of the relics I see, You can use it to open the gate in the RUINS..." << std::endl
			<< "Old Man: I will also guide you with this here map...But be careful..There are strange things happening inside the cave..." << std::endl << std::endl;
		system("pause");
		system("cls");

		Inventory.Map = true;
		Inventory.increase();
		trigger3 = true;

	}
	else if (trigger1 == true && trigger2 == true)
	{
		std::cout << std::endl << "Old Man: Be useful please and find us the SCROLL we've been looking for.. " << std::endl;
		system("pause");
		system("cls");

		std::cout << std::endl << "You heard the Old man and went back to cross-roads to look for what he is searching for..." << std::endl;

		crossroads();
	}
	else if (trigger1 == true)
	{
		time(&init); //Using time as years easter egg
		std::cout << "!!" << std::endl;
		system("pause");
		system("cls");
		std::cout << std::endl << "You see an old man waving in the distance, looking at you with a frowny look.." << std::endl << std::endl
			<< "Old man: Well well if it isn't " << MainCharacter.Name << "... Where have you been?!" << std::endl;
		system("pause");
		system("cls");
		std::cout << "Old Man: Do you have any idea how many years you've been in the forests?" << std::endl;
		system("pause");
		std::cout << "The old man expects to hear an answer... " << std::endl << std::endl
			<< "1. No" << std::endl
			<< "2. Of course I do!" << std::endl
			<< "3. What is this place and how do you know me?!" << std::endl;
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
			{
				time(&final);
				dif = difftime(final, init);
				std::cout << std::endl << "Old Man: " << dif << " Years!!!!" << std::endl
				<< std::endl << "Old Man: Now go be useful please and find us the SCROLL we've been looking for.. " << std::endl;
				system("pause");
				system("cls");
				
				std::cout << std::endl << "You heard the Old man and went back to cross-roads to look for what he is searching for..." << std::endl;
				
				trigger2 = true; //To make sure this dialogue is not repeated if the player revisits
				crossroads();
				
				
			}
			break;

			case 2:
			{
				time(&final);
				dif = difftime(final, init);
				std::cout << std::endl << "Old Man: Yes..You mean to tell me that I will totally believe" <<
					std::endl << "that you were counting every second within the past " << dif << " years" << std::endl
					<< std::endl << "Old Man: Now go be useful please and find us the SCROLL we've been looking for.. " << std::endl;
				system("pause");
				system("cls");

				std::cout << std::endl << "You heard the Old man and went back to cross-roads to look for what he is searching for..." << std::endl;

				trigger2 = true; //To make sure this dialogue is not repeated if the player revisits
				crossroads();;
			
			
			}
			break;

			case 3:
			{
				time(&final);
				dif = difftime(final, init);
				std::cout << std::endl << "Old Man: Of course you have forgotten me, although " << dif << " years is nothing compared to how long this town has been suffering.." << std::endl
					<< std::endl << "Old Man: Now go be useful please and find us the SCROLL we've been looking for.. " << std::endl;
				system("pause");
				system("cls");

				std::cout << std::endl << "You heard the Old man and went back to cross-roads to look for what he is searching for..." << std::endl;

				trigger2 = true; //To make sure this dialogue is not repeated if the player revisits
				crossroads();
			
			}
			break;
			default:
				std::cout << std::endl << "Old Man: I cannot understand the gibberish young one.. (Invalid input)" << std::endl << std::endl;
				break;
			}
		}

		trigger2 = true;
	}
	crossroads();
}

//MONSTER_CAVE
void monstercave()
{
	system("cls");
	locator = MONSTER_CAVE;
	std::cout << std::endl << "Monster Cave" << std::endl;
	SwitchState();
}

//WATERFALL
void waterfall()
{
	system("cls");
	locator = WATERFALL;
	std::cout << std::endl << "Waterfall" << std::endl;
	SwitchState();
}

void fight()
{
	system("cls");
	if (locator == LAKEMONSTER)
	{
		SwampMonster.Set_Values(100, 2);
		SwampMonster.SetName("SwampMonster");

		while (SwampMonster.HP > 0 && MainCharacter.HP > 0) //Winning condition, losing condition within loop
		{
			system("cls");


			std::cout << std::endl << "You're being ambushed by a " << SwampMonster.Name << "!" << std::endl << std::endl
				<< "The "<< SwampMonster.Name << " has " << SwampMonster.HP << " HP" << std::endl << std::endl
				<< "You have " << MainCharacter.HP << " HP" << std::endl << std::endl
				<< "What do you do?" << std::endl
				<< "1. Attack" << std::endl << std::endl;
			if (!(std::cin >> _decision))
			{
				std::cin.clear();
				while (std::cin.get() != '\n');
				std::cout << "Invalid Input!" << std::endl << std::endl;
				continue;
			}
			if (_decision == 1)
			{
				SwampMonster.HP -= MainCharacter.DMG;
				std::cout << std::endl << "You attack the " << SwampMonster.Name << " with " << MainCharacter.DMG << " Damage!" << std::endl;

			}

			MainCharacter.HP -= SwampMonster.DMG;

			std::cout << SwampMonster.Name <<  " attacks with " << SwampMonster.DMG << std::endl;
			system("pause");
			
		}
		if (MainCharacter.HP <= 0)
		{
			gameover();
		}
	}
	
	if (locator == FIGHT1)
		{
			//Thief in River
			Thief.Set_Values(10, 3);
			Thief.SetName("Thief");

			while (Thief.HP > 0 && MainCharacter.HP > 0) //Winning condition
			{
				system("cls");


				std::cout << std::endl << "You're being ambushed by a " << Thief.Name << "!" << std::endl << std::endl
					<< "The thief has " << Thief.HP << " HP" << std::endl << std::endl
					<< "You have " << MainCharacter.HP << " HP" << std::endl << std::endl
					<< "What do you do?" << std::endl
					<< "1. Attack" << std::endl
					<< "2. Use Item" << std::endl << std::endl;
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
					std::cout << std::endl << "You attack the "<< Thief.Name << " with " << MainCharacter.DMG << " Damage!" << std::endl;

				}
				else if (_decision == 2)
				{
					system("cls");
					std::cout << std::endl << "Which item do you wish to use?" << std::endl
						<< "1. Torch" << std::endl
						<< "2. Cancel (Skips your turn)" << std::endl <<std::endl;

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

							std::cout << std::endl << "You have used the lighter to light up the torch and throw it against the thief!" << std::endl << std::endl
									  << "Thief: What have you done!? Are you MAD?!?";
							system("pause");
							Inventory.Lighter = false;
							Inventory.decrease();
							Inventory.Torch = false;
							Inventory.decrease();
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
			if (MainCharacter.HP <= 0)
			{
				gameover();
			}
			MainCharacter.Score += 5;
			MainCharacter.DMG += 2;
			MainCharacter.HP = 10;
			MainCharacter.HP += 8;
			MainCharacter.Score ++;
			std::cout << "You have defeated the thief!" << std::endl << std::endl
				<< "You gained experience from this fight!"<<std::endl 
				<< "You can deal " << MainCharacter.DMG << " Damage now!" << std::endl
				<< "HP increased to " << MainCharacter.HP << std::endl << std::endl;
			system("pause");
			trigger1 = true;
			hideout();
		}

}