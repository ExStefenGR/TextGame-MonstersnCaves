#include <iostream>
#include <string>
#include <ctime>
#include "Minigame.h"


//Location relates to locator and is used for the navigation and as a secondary "boolean" statement that has more than one option, see further comments for info.
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
	THIEFFIGHT, 
	LAKEMONSTER, 
	VOLCANO,  
	CASTLE, 
	THIEFGUILD, 
	GAMEOVER
};


//Functions
void camp();		 //You can get the lighter for the torch for this, not very useful as you will need the sword later on and it is not obtainable later on
void castle();		 //Optional bossfight
void crossroads();	 //Where the player can navigate through different areas, unlocks or blocks different paths depending on situations
void fight();		 //All the fights and optional bossfights with trickier mechanics
void hideout();		 //Thief Hideout, re-used later on for the THIEFGUILD optional bossfight
void lake();		 //gameover
void monstercave(); //Last area where player has to fight 2 enemies at once.
void mountain();	//Area where you get the sword, pseudo-animation of flashing sword here.
void river();		//Area that the player encounters the thief
void ruins();		//Area that you use the Scroll item and go through the maze, Unlocks bossfights if they decide not to go in MONSTER CAVE yet.
void startpoint();	//Beginning of the adventure

void town();		//Town that you can interact with the old man AFTER defeating the thief, If you chose not to get the scroll on the first chance, there is an easter egg using the timer
					//also heals the player when they are doing the optional 

void volcano();		//Optional bossfight with a self-regenative magma creature using srand
void waterfall(); //Last are and credits

void gameover(); //Gameover screen which shows the player the final stats and the score

void SwitchState(); //One of the key elements of the game, it maps the whole of the game using the Enumarator Location and a switch with inline if statements. can be used as a debug tool too.

//timers
time_t init, final;//Used for one of the easter eggs with the Old man in Town.

double dif,w_dif;

//Wait function for the purpose of making the player read instead of skip important parts of the text game.
void wait(double w_seconds)
{
	clock_t w_start = clock();
	double w_secondsNeeded = w_seconds * CLOCKS_PER_SEC; // <--This lets the compiler know that we need to modify this to seconds

	while (clock() < w_start + w_secondsNeeded); // Does nothing until number is reached in seconds

	return;
	
}

//User's stats
struct Entity
{
	std::string Name;
	int DMG = 0;
	int HP = 0;
	int MaxHP = 0;
	int Score = 0;
	void increase(){ Score += 5; }
	void Set_Values(int x, int y){HP = x; DMG = y;}
	void SetName(std::string x){Name = x;}

	//Used to reset the Player's HP to the original value
	void ResetHP()
	{
		MaxHP = HP;
	} 
};

Entity MainChar; 
Entity Thief;
Entity SwampMonster;

Entity StrangeMonster1;
Entity StrangeMonster2;

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
		Sword = false;
		Lighter = false;
		Map = false;
		Scroll = false;

		count = 1;
		GearWeight = 1;
	}
};

Items Inventory;

//Situational variables
int locator, _decision; //For actual locations (Mountain/River...)

bool FirstMinigame, SecondMinigame; //Returns a true or false value depending on the minigame's outcome.
bool ThiefDefeated; //Thief defeated in Hideout
bool OldManDialogueDone; //Initial dialogue done
bool MapGiven; //Map Given From Old man
bool optionalFights;//Optional fights unlocked
bool monstercaveEntered; // if character has already gone to Monster Cave
bool Done{}; //This is so the Switch gets repeated until the Player uses the correct variable value

bool vdmdone, smdone, nkdone; //optional bossfights and checking if they are done, unlocks once monstercaveEntered is triggered as true and the player goes back before the final bossfight.

//Minigame 
Minigame Game;

//A quick tool to see statistics as well as inventory
void stats(Items* Inventory)
{
	std::cout << std::endl << "Your Health is at " << MainChar.HP << " HP" << std::endl
					       << "Your Damage is at " << MainChar.DMG << " Damage" << std::endl
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
	if (Inventory->count == 0)
	{
		std::cout << std::endl << "None" << std::endl;
	}
	std::cout << std::endl;
}

//The below function can also be used as a debug tool to explore different rooms.
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
			else if (locator == CROSSROADS && monstercaveEntered == true)
			{
				locator = MONSTER_CAVE;
				fight();
			}
			else if (locator == CROSSROADS && ThiefDefeated == false)
			{
				river();
			}
			else if (locator == CROSSROADS && ThiefDefeated == true)
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
				monstercave();
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
			else if (locator == CROSSROADS && Inventory.Map == true && ThiefDefeated == true)
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
			if (locator == CROSSROADS && ThiefDefeated == true)
			{
				hideout();
			}
			else if (locator == CROSSROADS && ThiefDefeated == false)
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
		case 6:
			if (locator == CROSSROADS && monstercaveEntered == true)
			{
				locator = LAKEMONSTER;
				fight();
			}
			break;
		case 7:
			if (locator == CROSSROADS && monstercaveEntered == true)
			{
				locator = VOLCANO;
				volcano();
				
			}
		case 8:
			if (locator == CROSSROADS && monstercaveEntered == true)
			{
				locator = CASTLE;
				castle();
			}
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

	MainChar.Set_Values(10, 1);
	MainChar.MaxHP = 10;
	MainChar.Score = 0;

	system("cls");

	std::cout << "Greetings young wanderer.." << std::endl << "What is your name?" << std::endl;
	std::cin >> MainChar.Name;
	std::cout << "Shall we begin with your adventure.. " << MainChar.Name << " ?" << std::endl;
	system("pause");
	system("cls");
	std::cin.clear();
	std::cout << "Good luck and bear in mind your adventure has many co-existing and alternate realities.. " << MainChar.Name << std::endl;
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

	std::cout << std::endl << "You did well, " << MainChar.Name << "." << std::endl

		<< "Final stats" << std::endl
		<< "Highest Damage dealt " << MainChar.DMG << std::endl
		<< "Progression score " << MainChar.Score << std::endl << std::endl
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
	Inventory.reset();
	 ThiefDefeated = false; 
	 OldManDialogueDone = false;
	 MapGiven = false; 
	 optionalFights = false; //Resetting in case of gameover


	MainChar.Set_Values(10, 1);
	MainChar.MaxHP = 10;

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
		<< "Pick up?" << std::endl << std::endl
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
		MainChar.DMG += 5;
		Inventory.GearWeight += 5;
		std::cout << std::endl << "Your damage has increased to " << MainChar.DMG << std::endl
			<< "Gear weight increased! +" << Inventory.GearWeight << std::endl;
		system("pause");
	}

	std::cout << std::endl << "You have heard an echo in the distance.." << std::endl
		<< "You follow the road the echo came from regardless of the consequences" << std::endl;

	system("pause");
	system("cls");
	std::cin.clear();

	Game.MiniGame1(FirstMinigame); //MiniGame Session
	if (FirstMinigame == false)
	{
		startpoint(); //Failed the minigame
	}

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

	if (ThiefDefeated == false)
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
	else if (Inventory.Scroll == false && monstercaveEntered == true)
	{
		std::cout << std::endl << "You have arrived in a field that has a cross-like shape, where do you wish to go?" << std::endl
			<< std::endl << "1. Monster Cave"
			<< std::endl << "3. Towards Town"
			<< std::endl << "4. Towards Hideout" << std::endl
			<<std::endl << "6. Towards Lake (Lake Monster Bossfight)"
						<< "7. Towards Volcano (Optional BossFight)"
					    << "8. Towards Castle (Optional BossFight)"
			<< std::endl << "5. Check stats" << std::endl << std::endl;
	}
	else if (ThiefDefeated == true)
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
	locator = THIEFFIGHT; //Tells the fight(); function to initiate thief bossfight if true in 

	//dialogue
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
	
	std::cout << "The scroll has vanished and a door catacomb has revealed the MONSTER CAVE" << std::endl << std::endl;

	stats(&Inventory);

	system("pause");
	system("cls");

	system("color 0C");

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
	if (ThiefDefeated == false)
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
				std::cout << "You only have one option " << MainChar.Name;
				Done = false;
				break;
			}
		}
	}
	else if (monstercaveEntered == true)
	{
		system("cls");
		std::cout << std::endl << "Old Man: Back to me I see? Let me heal you..." << std::endl << std::endl;
		wait(3);
		std::cout << std::endl << "The old man casts a healing spell, your wounds have been healed!" << std::endl << std::endl
			<<"HP was at " << MainChar.HP << " and you have been healed back at " << MainChar.MaxHP << " !" <<std::endl;
		MainChar.ResetHP();


	}
	else if (MapGiven == true)
	{
		system("cls");

		std::cout << std::endl << "Old Man: Be careful out there.. " << MainChar.Name << std::endl << std::endl;

		system("pause");

		crossroads();

	}
	else if (ThiefDefeated == true && Inventory.Scroll == true)
	{
		std::cout << std::endl << "You approach the Old man in the empty town to seek answers for the mysterious scroll you have found" << std::endl << std::endl;

		system("pause");
		system("cls");

		std::cout << std::endl << "Old Man: Oh hi there.. " << MainChar.Name << ", what brings you here today?" << std::endl
			<< "Old Man: Oh...You found one of the relics I see, You can use it to open the gate in the RUINS..." << std::endl
			<< "Old Man: I will also guide you with this here MAP...But be careful..There are strange things happening inside the cave..." << std::endl 
			<< "Old Man: Also, Let me grant you some magical strength..." << std::endl << std::endl;
		system("pause");
		system("cls");

		Inventory.Map = true;
		Inventory.increase();
		MapGiven = true;

		MainChar.Score++;
		MainChar.HP += 10;
		MainChar.DMG += 5;

	}
	else if (ThiefDefeated == true && OldManDialogueDone == true)
	{
		std::cout << std::endl << "Old Man: Be useful please and find us the SCROLL we've been looking for.. " << std::endl;
		system("pause");
		system("cls");

		std::cout << std::endl << "You heard the Old man and went back to cross-roads to look for what he is searching for..." << std::endl;

		crossroads();
	}
	else if (ThiefDefeated == true)
	{
		time(&init); //Using time as years easter egg
		std::cout << "!!" << std::endl;
		wait(3);
		system("cls");
		std::cout << std::endl << "You see an old man waving in the distance, looking at you with a frowny look.." << std::endl << std::endl
			<< "Old man: Well well if it isn't " << MainChar.Name << "... Where have you been?!" << std::endl;
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
				
				OldManDialogueDone = true; //To make sure this dialogue is not repeated if the player revisits
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

				OldManDialogueDone = true; //To make sure this dialogue is not repeated if the player revisits
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

				OldManDialogueDone = true; //To make sure this dialogue is not repeated if the player revisits
				crossroads();
			
			}
			break;
			default:
				std::cout << std::endl << "Old Man: I cannot understand the gibberish young one.. (Invalid input)" << std::endl << std::endl;
				break;
			}
		}

		OldManDialogueDone = true;
	}
	crossroads();
}

//MONSTER_CAVE
void monstercave()
{
	system("cls");
	locator = MONSTER_CAVE;
	Game.MiniGame2(SecondMinigame);
	if (SecondMinigame == false)
	{
		ruins();
	}

	Inventory.Scroll = false;
	Inventory.decrease();
	monstercaveEntered = true;

	std::cout << std::endl << "You encounter a strange monster!" << std::endl;
	fight();
}

//WATERFALL
void waterfall()
{
	system("color 08");
	system("cls");
	locator = WATERFALL;
	std::cout << std::endl << "Inside the Monster cave you find a waterfall" << std::endl;
	wait(2);
	std::cout << std::endl << "You hear the echo from the Mountain suddendly surrounding you" << std::endl;
	wait(2);
	std::cout << std::endl << "You approach the waterfall closer and closer by the second but every second turns to a minute.." << std::endl;
	wait(2);
	std::cout << std::endl << "Every minute to an hour....."<< std::endl;
	wait(3);
	std::cout << std::endl << "!!!" << std::endl;
	wait(1);
	system("cls");

	std::cout << std::endl << "???: Wake up " << MainChar.Name << ", we have arrived.." << std::endl << std::endl;
	wait(3);
	system("cls");
	std::cout << std::endl << "You have awoken at the back of a horse carriage in the woods" << std::endl;
	wait(3);
	std::cout << std::endl << "The place seems like the gates of the Town you visited a while ago..But something is different.." << std::endl;
	wait(3);
	system("cls");
	std::cout << std::endl << "Old Man: So " << MainChar.Name << ", How was the Mountain..?" << std::endl;
	wait(3);
	std::cout << std::endl << "Old Man: You seem really out of speech so I take it as really breath-taking." << std::endl;
	wait(3);
	system("cls");
	std::cout << "Old Man: Let's get to Jason's inn, I doubt the sun comes out soon, better avoid another Monster invasion" << std::endl;
	system("pause");
	
	system("cls");
	wait(3);
	system("color 03");

	std::cout << "             [         Developed by Stefanos Triantafyllidis          ]                   " << std::endl<<std::endl<<std::endl;
	wait(5);
	stats(&Inventory);

	std::cout << std::endl << std::endl << "Final score: " << MainChar.Score << std::endl;
	system("pause");
	system("exit");
}

//VOLCANO (Optional bossfight with random heal regen twist)
void volcano()
{
	locator = VOLCANO;
	system("cls");
	system("color 8C");

	//dialogue
	std::cout << std::endl << "You have revisited the mountain, Now with your newfound magical powers from the Old Man in Town you can climb your way to the top.." << std::endl;
	wait(5);
	system("cls");
	std::cout << std::endl << "!!!" << std::endl;
	wait(1);
	system("cls");
	fight();
}

//CASTLE (Optional bossfight with random heal regen twist and random critical chance)
void castle()
{

	locator = CASTLE;
	system("cls");
	system("color 06"); //Using this colour throughout the fight to indicate that is different from the others

	//dialogue
	std::cout << std::endl << "You begin to get through the Town, You notice a huge castle entrance opposite the plaza..." << std::endl;
	wait(5);
	system("cls");
	std::cout << std::endl << "???: I CHALLENGE THEE TO A FIGHT" << std::endl;
	wait(5);
	std::cout << std::endl << "!!!" << std::endl;
	wait(1);
	system("cls");


	fight();
}

void fight()
{
	std::cin.clear();
	system("cls");
	if (locator == MONSTER_CAVE)
	{
		StrangeMonster1.Set_Values(35, 3);
		StrangeMonster1.SetName("Void Walker");
		StrangeMonster2.Set_Values(20, 2);
		StrangeMonster2.SetName("Piranha Plant");
		int _counter = 0;
		while (_counter < 2 && MainChar.HP > 0) //Counter used to determine if BOTH enemies are defeated
		{

			std::cin.clear();
			system("cls");
			system("color 0C");

			std::cout << std::endl << "You are being attacked by " << StrangeMonster1.Name << " and " << StrangeMonster2.Name << std::endl << std::endl
				<< StrangeMonster1.Name << " has" << StrangeMonster1.HP << "  HP" << std::endl
				<< StrangeMonster2.Name << " has" << StrangeMonster2.HP << "  HP" << std::endl << std::endl
				<< "You have " << MainChar.HP << " HP" << std::endl
				<< "What do you do?" << std::endl << std::endl
				<< "1. Attack" << std::endl
				<< "2. Try to Talk to them?" << std::endl
				<< "4. RUN" << std::endl
				<< "5. Check stats" << std::endl << std::endl;

			// Player Choice

			std::cin.clear();
			if (!(std::cin >> _decision))
			{
				std::cin.clear();
				while (std::cin.get() != '\n');
				std::cout << "Invalid Input!" << std::endl << std::endl;
				continue;
			}
			if (_decision == 1)
			{
				std::cin.clear();
				system("cls");
				std::cout << "Choose an enemy to attack!" << std::endl << std::endl;

				if (StrangeMonster1.HP <= 0)
				{
					std::cout << "2. " << StrangeMonster2.Name << " " << StrangeMonster2.HP << " HP" << std::endl << std::endl;
				}
				else if (StrangeMonster2.HP <= 0)
				{
					std::cout << "1. " << StrangeMonster1.Name << " " << StrangeMonster1.HP << " HP" << std::endl << std::endl;
				}
				else if (StrangeMonster1.HP > 0 && StrangeMonster2.HP > 0)
				{
					std::cout << "1. " << StrangeMonster1.Name << " " << StrangeMonster1.HP << " HP" << std::endl
						<< "2. " << StrangeMonster2.Name << " " << StrangeMonster2.HP << " HP" << std::endl << std::endl;
				}

				if (!(std::cin >> _decision))
				{
					std::cin.clear();
					while (std::cin.get() != '\n');
					std::cout << "Invalid Input!" << std::endl << std::endl;
					continue;
				}

				//If Target 1 is Alive
				if (_decision == 1 && StrangeMonster1.HP > 0)
				{
					StrangeMonster1.HP -= MainChar.DMG;
					std::cout << std::endl << "You dealt " << MainChar.DMG << " Damage to " << StrangeMonster1.Name << "!" << std::endl << std::endl;
					system("pause");

				}
				//If Target 1 is Down
				else if (_decision == 1 && StrangeMonster1.HP <= 0)
				{
					std::cout << std::endl << "The Target has already been defeated, choose your turns wisely!" << std::endl;
					system("pause");
				}
				//If Target 2 is Alive
				if (_decision == 2 && StrangeMonster2.HP > 0)
				{
					StrangeMonster2.HP -= MainChar.DMG;
					std::cout << std::endl << "You dealt " << MainChar.DMG << " Damage to " << StrangeMonster2.Name << "!" << std::endl << std::endl;
					system("pause");

				}
				//If Target 2 is Down
				else if (_decision == 2 && StrangeMonster2.HP <= 0)
				{
					std::cout << std::endl << "The Target has already been defeated, choose your turns wisely!" << std::endl;
				}


			}
			else if (_decision == 2)
			{
				std::cout << std::endl << "You begin a very pleasant and high class conversation with the monsters, ";
				wait(2);
				std::cout << std::endl << "They don't seem to care that much ";
				wait(2);
			}
			else if (_decision == 4)
			{
				std::cout << "You run out of Monster Cave!" << std::endl;

				crossroads();
			}

			else if (_decision == 5)
			{
				stats(&Inventory);
			}

			if (StrangeMonster1.HP <= 0 && StrangeMonster2.HP <= 0)
			{
				_counter = 2;
			}

			//Damage Step
			if (StrangeMonster1.HP <= 0)
			{

				MainChar.HP -= StrangeMonster2.DMG;
				std::cout << std::endl << StrangeMonster2.Name << " Has attacked you for " << StrangeMonster2.DMG << " Damage" << std::endl << std::endl;
			}
			if (StrangeMonster2.HP <= 0)
			{
				MainChar.HP -= StrangeMonster1.DMG;
				std::cout << std::endl << StrangeMonster1.Name << " Has attacked you for " << StrangeMonster1.DMG << " Damage" << std::endl << std::endl;

			}
			else if (StrangeMonster1.HP > 0 && StrangeMonster2.HP > 0)
			{
				MainChar.HP -= StrangeMonster1.DMG;
				MainChar.HP -= StrangeMonster2.DMG;

				std::cout << std::endl << StrangeMonster1.Name << " Has attacked you for " << StrangeMonster1.DMG << " Damage" << std::endl << std::endl;
				std::cout << std::endl << StrangeMonster2.Name << " Has attacked you for " << StrangeMonster2.DMG << " Damage" << std::endl << std::endl;
			}
			system("pause");


		}
		if (MainChar.HP <= 0)
		{
			gameover();
		}

		std::cout << std::endl << "You have defeated " << StrangeMonster1.Name << " and " << StrangeMonster2.Name << std::endl << std::endl;
		MainChar.Score += 10;

		system("pause");

		waterfall();
	}
	if (locator == LAKEMONSTER)
	{
		system("color 0B");
		SwampMonster.Set_Values(100, 2);
		SwampMonster.SetName("Swamp Monster");

		while (SwampMonster.HP > 0 && MainChar.HP > 0)
		{
			system("cls");


			std::cout << std::endl << "You are being ambushed by a " << SwampMonster.Name << "!" << std::endl << std::endl
				<< "The " << SwampMonster.Name << " has " << SwampMonster.HP << " HP" << std::endl << std::endl
				<< "You have " << MainChar.HP << " HP" << std::endl << std::endl
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
				SwampMonster.HP -= MainChar.DMG;
				std::cout << std::endl << "You attack the " << SwampMonster.Name << " with " << MainChar.DMG << " Damage!" << std::endl;

			}

			MainChar.HP -= SwampMonster.DMG;

			std::cout << SwampMonster.Name << " attacks with " << SwampMonster.DMG << std::endl;
			wait(2);

		}
		if (MainChar.HP <= 0) //Gameover if Character is dead
		{
			gameover();
		}

		MainChar.Score += 10;
		smdone = true;

		std::cout << std::endl << "The monster begins to disappear in the mists as it falls in the lake" << std::endl;
		wait(3);
		std::cout << std::endl << "You gain experience from this fight" << std::endl << std::endl;
		MainChar.MaxHP += 10;
		MainChar.DMG += 5;
		std::cout << std::endl << "Damage increased to " << MainChar.DMG << "!" << std::endl;
		std::cout << std::endl << "HP increased to " << MainChar.HP << "!" << std::endl << std::endl;
		system("pause");
		MainChar.ResetHP();

	}
	if (locator == THIEFFIGHT)
	{
		//Thief in River
		Thief.Set_Values(10, 3);
		Thief.SetName("Thief");

		while (Thief.HP > 0 && MainChar.HP > 0) //Winning condition
		{
			system("cls");


			std::cout << std::endl << "You're being ambushed by a " << Thief.Name << "!" << std::endl << std::endl
				<< "The thief has " << Thief.HP << " HP" << std::endl << std::endl
				<< "You have " << MainChar.HP << " HP" << std::endl << std::endl
				<< "What do you do?" << std::endl
				<< "1. Attack" << std::endl
				<< "2. Use Item" << std::endl
				<< "5. Check stats (Will skip your turn)" << std::endl << std::endl;
			if (!(std::cin >> _decision))
			{
				std::cin.clear();
				while (std::cin.get() != '\n');
				std::cout << "Invalid Input!" << std::endl << std::endl;
				continue;
			}
			if (_decision == 1)
			{
				Thief.HP -= MainChar.DMG;
				std::cout << std::endl << "You attack the " << Thief.Name << " with " << MainChar.DMG << " Damage!" << std::endl;

			}
			else if (_decision == 2)
			{
				system("cls");
				std::cout << std::endl << "Which item do you wish to use?" << std::endl
					<< "1. Torch" << std::endl
					<< "2. Cancel (Skips your turn)" << std::endl << std::endl;

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
			else if (_decision == 5)
			{
				stats(&Inventory);
			}
			MainChar.HP -= Thief.DMG;

			std::cout << "Thief attacks with " << Thief.DMG << std::endl;
			system("pause");
		}
		if (MainChar.HP <= 0)
		{
			gameover();
		}
		MainChar.Score += 5;
		MainChar.DMG += 2;
		MainChar.HP = 10;
		MainChar.HP += 8;
		MainChar.Score++;
		std::cout << "You have defeated the thief!" << std::endl << std::endl
			<< "You gained experience from this fight!" << std::endl
			<< "You can deal " << MainChar.DMG << " Damage now!" << std::endl
			<< "HP increased to " << MainChar.HP << std::endl << std::endl;
		system("pause");
		ThiefDefeated = true;
		hideout();
	}
	if (locator == VOLCANO)
	{
		int _heal;
		Entity VDM;
		VDM.SetName("Volcanic Demolisher");
		VDM.Set_Values(50, 10);
		VDM.MaxHP = 50;

		std::cout << std::endl << "You exncounter a collosal monster the size of the crater at the center of the volcano!" << std::endl;
		wait(3);
		std::cout << std::endl << "The giant demon grabs his axe and is ready to fight you.." << std::endl;
		system("pause");

		while (MainChar.HP >= 0 && VDM.HP >= 0)
		{
			system("cls");


			std::cout << std::endl << "You are fighting against " << VDM.Name << "!" << std::endl << std::endl
				<< "The " << VDM.Name << " has " << VDM.HP << " HP" << std::endl << std::endl
				<< "You have " << MainChar.HP << " HP" << std::endl << std::endl
				<< "What do you do?" << std::endl
				<< "1. Attack" << std::endl
				<< "2. Rest" << std::endl << std::endl;

			//Player choices and actions
			if (!(std::cin >> _decision))
			{
				std::cin.clear();
				while (std::cin.get() != '\n');
				std::cout << "Invalid Input!" << std::endl << std::endl;
				continue;
			}
			if (_decision == 1)
			{
				std::cout << std::endl << "You deal " << MainChar.DMG << " Damage to " << VDM.Name << std::endl;
				VDM.HP -= MainChar.HP;
				wait(3);
			}
			if (_decision == 2)
			{
				//Random Healing factor
				srand((int)time(0));
				_heal = rand() % 10 + 1;
				std::cout << std::endl << "You attempt to catch your breath for a moment and restore " << _heal << " HP";
				wait(3);
			}

			//This Optional bossfight regens HP randomly
			if (VDM.HP < VDM.MaxHP)
			{
				srand((int)time(0));
				_heal = rand() % 20 + 1;
				if (_heal < 5)
				{
					std::cout << std::endl << VDM.Name << " Has merged with the volcanic magma and restored " << _heal << " HP" << std::endl;
					_heal += VDM.HP;

				}
			}

			std::cout << std::endl << "The " << VDM.Name << " has striked with " << VDM.DMG << " Damage!" << std::endl;
			system("pause");

		}

		if (MainChar.HP <= 0)
		{
			gameover();
		}

		vdmdone = true;

		std::cout << std::endl << "The Demon gets melted into the volcano" << std::endl;
		wait(3);
		std::cout << std::endl << "You gain experience from this fight" << std::endl << std::endl;
		MainChar.MaxHP += 10;
		MainChar.DMG += 5;
		MainChar.ResetHP();


	}
	if (locator == CASTLE)
	{ //Crit chance and heal factor



	}
}