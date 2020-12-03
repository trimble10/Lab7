/*
Aiden Trimble
C++ Fall 2020
Due: December 2nd, 2020
To create the game battleship
*/


#include <iostream>
#include <time.h>
#include<fstream>

using namespace std;

//Enum that helps show which ship is being used
enum shiptype {destroyer, submarine, cruiser, battleship, carrier};

//Struct that contains the variables
struct shipstatus
{
	shiptype ship;
	int health;
	int direction;
	int length;
	int X;
	int Y;
};

/*Preconditions: The arrays pass through the function
Postconditions: The characters of the arrays are outputted */
void printboard(char array[][10]);
/*Preconditions: Previous functions need to work
Postconditions: Outputs the battle phase until a win or loss*/
void battle(shipstatus friendships[], shipstatus enemyship[], char array1[][10], char array2[][10], char array3[][10], char array4[][10], int& wins, int& loss);
void checkShip(shipstatus ship[], char array[][10], int X, int Y);
/*Preconditions: Needs functions before to be valid
Postconditions: Outputs the random ship location*/
void placeEship(shipstatus enemyship[], char array2[][10]);
/*Preconditions: Needs ship values and array goes through 
Postconditions: The ship is assigned the inputted x, y, and direction */
void placeFship(shipstatus friendship[], char array1[][10]);
/*Preconditions: Values from functions before need to be valid
Postconditions: Outputs the ship value */
void assignship(shipstatus ship[], char array[][10], int& crash, int i);
/*Preconditions: input would need to be invalid
Postconditions: Outputs an error message */
void error();


int main()
{
	//Welcome message
	cout << "Welcome To BattleShip! Good Luck!" << endl;
	//Initial values to track wins and losses
	int wins = 0;
	int loss = 0;
	bool playagain = true;
	//Helps the RNG
	srand(unsigned int(time(NULL)));

	//Main loop
	do
	{
		//Gets info for the ships
		shipstatus enemyship[5];
		shipstatus friendship[5];
		//Loop for the ships
		for (int i = 0; i < 5; i++)
		{
			enemyship[i].direction = 0;
			friendship[i].direction = 0;
			enemyship[i].Y = 0;
			friendship[i].Y = 0;
			enemyship[i].X = 0;
			friendship[i].X = 0;
			//Gives the info for each ship
			switch(i)
			{
			case 0:
				enemyship[i].ship = destroyer;
				friendship[i].ship = destroyer;
				enemyship[i].health = 2;
				friendship[i].health = 2;
				enemyship[i].length = 2;
				friendship[i].length = 2;
				break;
			case 1:
				enemyship[i].ship = submarine;
				friendship[i].ship = submarine;
				enemyship[i].health = 3;
				friendship[i].health = 3;
				enemyship[i].length = 3;
				friendship[i].length = 3;
				break;
			case 2:
				enemyship[i].ship = cruiser;
				friendship[i].ship = cruiser;
				enemyship[i].health = 3;
				friendship[i].health = 3;
				enemyship[i].length = 3;
				friendship[i].length = 3;
				break;
			case 3:
				enemyship[i].ship = battleship;
				friendship[i].ship = battleship;
				enemyship[i].health = 4;
				friendship[i].health = 4;
				enemyship[i].length = 4;
				friendship[i].length = 4;
				break;
			case 4:
				enemyship[i].ship = carrier;
				friendship[i].ship = carrier;
				enemyship[i].health = 5;
				friendship[i].health = 5;
				enemyship[i].length = 5;
				friendship[i].length = 5;
				break;


			}
		}
		//Defines the arrays
		char array1[10][10];
		char array2[10][10];
		char array3[10][10];
		char array4[10][10];
		//Sets the boards to water
		for (int row = 0; row < 10; row++)
		{
			for (int column = 0; column < 10; column++)
			{
				array1[row][column] = '~';
				array2[row][column] = '~';
				array3[row][column] = '~';
				array4[row][column] = '~';
			}
		}
	//Displays the board
	printboard(array1);
	//Function that places the friendly ships
	placeFship(friendship, array1);
	//Function that places the enemy ships
	placeEship(enemyship, array2);
	//Function that allows player to play
	battle(friendship, enemyship, array1, array2, array3, array4, wins, loss);

	//Askes if the player wants to play again
	int again;
	cout << "    Do You Want To Play Again?\nInput 1 For Yes or 2 For No: ";
	cin >> again;
	error();
	if (again == 2)
		{
			playagain = false;
		}
	} while (playagain);
	//Outputs the number of wins and losses
	cout << "\nWins: " << wins << "\nLosses: " << loss;

	return 0;
}
//Function that outputs the board
void printboard(char array[][10])
{
	cout << "   1 2 3 4 5 6 7 8 9 10\n";
	int Y = 1;
	//Loop that goes through the rows
	for (int row = 0; row < 10; row++)
	{
		if (Y == 10)
		{
			cout << Y << " ";
		}
		else
		{
			cout << Y << "  ";
		}
		Y++;
		//loop that goes through the columns
		for (int column = 0; column < 10; column++)
		{
			cout << array[row][column] << " ";
		}
		cout << "\n";
	}
	
}
//Function that runs a loop for the player to play the game
void battle(shipstatus friendships[], shipstatus enemyship[], char array1[][10], char array2[][10], char array3[][10], char array4[][10], int& wins, int& loss)
{
	//Keeps track of the points
	bool gamewin = true;
	int points = 0;
	int Epoints = 0;
	bool redo = true;

	cout << "Prepare for Battle" << endl;
	//Loop for the player to guess
	while (gamewin)
	{
		int Yinput;
		int Xinput;
		//A visual for the player to shoot
		printboard(array3);
		//Input phase where on the X they want to shoot
		cout << "Shoot Your Shot Captain! Input Your X Coordinate: ";
		cin >> Xinput;
		Xinput--;
		error();
		//Input phase where on the Y they want to shoot
		cout << "Now Input Your Y Coordinate: ";
		cin >> Yinput;
		Yinput--;
		error();
		//Makes sure the inputs are valid
		if (Xinput < 0 || Xinput > 9)
		{
			cout << "\nYour X Input is Out of Bounds.\n";
			continue;
		}
		if (Yinput < 0 || Yinput > 9)
		{
			cout << "\nYour Y Input is Out of Bounds.\n";
			continue;
		}
		//Outputs if the ship was hit or not
		switch (array2[Yinput][Xinput])
		{

		case '~':
			array2[Yinput][Xinput] = 'M';
			array3[Yinput][Xinput] = 'M';
			cout << "Miss!" << endl;
			break;
		case '#':
			points++;
			array2[Yinput][Xinput] = 'H';
			array3[Yinput][Xinput] = 'H';
			checkShip(enemyship, array2, Xinput, Yinput);
			cout << "Hit!" << endl;
			break;
		default: 
			cout << "Guess Somewhere Else.";
				continue;
			break;
		}
		//Outputs the guess shot
		printboard(array3);
		//Outputs if they destroyed a hip
		for (int i = 0; i < 5; i++)
		{
			if (enemyship[i].health == 0)
			{
				cout << "\nThat Shot Was Lethal, It's Gone\n";
				enemyship[i].health++;
			}
		}

		if (gamewin == false)
		{
			break;
		}

		while (redo)
		{	
			int GuessY = rand() % 10;
			int GuessX = rand() % 10;
			cout << "\nThe enemy fires at: " << GuessX << ", " << GuessY;
			//Sees if they hit missed
			switch (array1[GuessY][GuessX])
			{
			case '~': array1[GuessY][GuessX] = 'M';
				array4[GuessY][GuessX] = 'M';
				cout << "\nYou Were Not Hit\n";
				redo = false;
				break;
			case '#': Epoints++; array1[GuessY][GuessX] = 'H';
				array4[GuessY][GuessX] = 'H';
				checkShip(friendships, array1, GuessX, GuessY);
				cout << "\nYou Were Hit.\n";
				redo = false;
				break;
			default:
				break;
			}
		}
		//Outputs the computers guess
		printboard(array4);
		printboard(array1);
		//Sees if the player won
		if (points == 17)
		{
			cout << "\nYou Win!\n";
			gamewin = false;
			wins++;
		}
		//Sees if the player lost
		if (Epoints == 17)
		{
			cout << "\nYou Lost!\n";
			gamewin = false;
			loss++;
		}
	}
}
//Function that places friendly ships
void placeFship(shipstatus friendship[], char array1[][10])
{
	for (int i = 0; i < 5; i++)
	{
		//Loop that allows player to input where and what direction they want the ship
		switch (i)
		{
		case 0: cout << "\n\tNow place the Destroyer ship, it's length is 2 spaces: \n";
			cout << "\n\tInput where on the X-axis you want it (Between one and ten): ";
				cin >> friendship[i].X;
				error();
				--friendship[i].X;
			cout << "\n\tInput where on the Y-axis you want it (Between one and ten): ";
				cin >> friendship[i].Y;
				error();
				--friendship[i].Y;
			cout << "\n\tInput 1 for vertical or 2 for horizontal: ";
				cin >> friendship[i].direction;
				error();
			break;
		case 1: cout << "\n\tNow place the Submarine, it's length is 3 spaces: \n";
			cout << "\n\tInput where on the X-axis you want it (Between one and ten): ";
				cin >> friendship[i].X;
				error();
				--friendship[i].X;
			cout << "\n\tInput where on the Y-axis you want it (Between one and ten): ";
				cin >> friendship[i].Y;
				error();
				--friendship[i].Y;
			cout << "\n\tInput 1 for vertical or 2 for horizontal: ";
				cin >> friendship[i].direction;
				error();
			break;
		case 2: cout << "\n\tNow place the Cruiser, it's length is 3 spaces: \n";
			cout << "\n\tInput where on the X-axis you want it (Between one and ten): ";
				cin >> friendship[i].X;
				error();
				--friendship[i].X;
			cout << "\n\tInput where on the Y-axis you want it (Between one and ten): ";
				cin >> friendship[i].Y;
				error();
				--friendship[i].Y;
			cout << "\n\tInput 1 for vertical or 2 for horizontal: ";
				cin >> friendship[i].direction;
				error();
			break;
		case 3: cout << "\n\tNow place the Battleship, it's length is 4 spaces: \n";
			cout << "\n\tInput where on the X-axis you want it (Between one and ten): ";
				cin >> friendship[i].X;
				error();
				--friendship[i].X;
			cout << "\n\tInput where on the Y-axis you want it (Between one and ten): ";
				cin >> friendship[i].Y;
				error();
				--friendship[i].Y;
			cout << "\n\tInput 1 for vertical or 2 for horizontal: ";
				cin >> friendship[i].direction;
				error();
			break;
		case 4: cout << "\n\tNow place the Carrier, it's length is 5 spaces: \n";
			cout << "\n\tInput where on the X-axis you want it (Between one and ten): ";
				cin >> friendship[i].X;
				error();
				--friendship[i].X;
			cout << "\n\tInput where on the Y-axis you want it (Between one and ten): ";
				cin >> friendship[i].Y;
				error();
				--friendship[i].Y;
			cout << "\n\tInput 1 for vertical or 2 for horizontal: ";
				cin >> friendship[i].direction;
				error();
			break;
		}
		//Makes sure the Y input is in bounds
		if (friendship[i].Y < 0 || friendship[i].Y > 9)
		{
			cout << "\n The Y coordinate input didn't work, try again \n";
			--i;
			continue;
		}
		//Makes sure the X input is in bounds
		if (friendship[i].X < 0 || friendship[i].X > 9)
		{
			cout << "\n The X coordinate input didn't work, try again \n";
			--i;
			continue;
		}
		
		int crash = 0;
		assignship(friendship, array1, crash, i);
		//Outputs a message if the ships over lap
		if (crash > 0)
		{
			cout << "\nThere was a problem with the ships\n";
			i--;
			continue;
		}
		//The ship is outputted to the board
		printboard(array1);
	}
}
//Function that randomly places the enemy ships
void placeEship(shipstatus enemyship[], char array2[][10])
{
	for (int i = 0; i < 5; i++)
	{
		//Generates the random numbers
		int randomX = rand() % 10;
		int randomY = rand() % 10;
		int randomDirection = rand() % 2 + 1;
		//chooses a random X, Y, and direction
		switch (i)
		{
		case 0: enemyship[i].X = randomX;
			enemyship[i].Y = randomY;
			enemyship[i].direction = randomDirection;
			break;
		case 1: enemyship[i].X = randomX;
			enemyship[i].Y = randomY;
			enemyship[i].direction = randomDirection;
			break;
		case 2: enemyship[i].X = randomX;
			enemyship[i].Y = randomY;
			enemyship[i].direction = randomDirection;
			break;
		case 3: enemyship[i].X = randomX;
			enemyship[i].Y = randomY;
			enemyship[i].direction = randomDirection;
			break;
		case 4:; enemyship[i].X = randomX;
			enemyship[i].Y = randomY;
			enemyship[i].direction = randomDirection;
			break;
		}
		int crash = 0;
		assignship(enemyship, array2, crash, i);
		//Checks to see if there was an over lap
		if (crash > 0)
		{
			i--;
			continue;
		}
	}
}
//Function that tells the placement of the ship
void assignship(shipstatus ship[], char array[][10], int& crash, int i)
{
	int bounds = (10 - ship[i].length);
	//Tells if the ship is being placed vertically or horizontally
	switch (ship[i].direction)
	{
	case 1: if (ship[i].Y <= bounds)
	{
		for (int n = 1; n <= ship[i].length; n++)
		{
			if (array[ship[i].Y][ship[i].X] == '#')
			{
				crash++;
			}
			ship[i].Y++;
		}
		for (int n = 1; n <= ship[i].length; n++)
		{
			array[ship[i].Y][ship[i].X] = '#';
			ship[i].Y++;
		}
		for (int n = 1; n <= ship[i].length; n++)
		{
			ship[i].Y--;
		}
		//Ends if over lap
		if (crash > 0)
		{
			break;
		}

		--ship[i].Y;
	}
	//Places it other way
	else
	{
		for (int n = 1; n <= ship[i].length; n++)
		{
			if (array[ship[i].Y][ship[i].X] == '#')
			{
				crash++;
			}
			ship[i].Y--;
		}
		//Ends if over lap
		if (crash > 0)
		{
			break;
		}

		for (int n = 1; n <= ship[i].length; n++)
		{
			ship[i].Y++;
		}

		for (int n = 1; n <= ship[i].length; n++)
		{
			array[ship[i].Y][ship[i].X] = '#';
			ship[i].Y--;
		}
		++ship[i].Y;
	}
	break;
	//Ship moves down
	case 2: if (ship[i].X <= bounds)
	{
		{//Sees if the ships over lap
			for (int n = 1; n <= ship[i].length; n++)
			{
				if (array[ship[i].Y][ship[i].X] == '#')
				{
					crash++;
				}
				ship[i].X++;
			}
			//Ends if over lap
			if (crash > 0)
			{
				break;
			}
			for (int n = 1; n <= ship[i].length; n++)
			{
				ship[i].X--;
			}
			//Sets value to each ship
			for (int n = 1; n <= ship[i].length; n++)
			{
				array[ship[i].Y][ship[i].X] = '#';
				ship[i].X++;
			}
			--ship[i].X;
		}
	}//ship moves up
		else
			{//checks for over lap
			for (int n = 1; n <= ship[i].length; n++)
				{
				if (array[ship[i].Y][ship[i].X] == '#')
				{
					crash++;
				}

				ship[i].X--;
			}
			//ends if over lap
			if (crash > 0)
			{
				break;
			}
			for (int n = 1; n <= ship[i].length; n++)
			{
				ship[i].X++;
			}
			for (int n = 1; n <= ship[i].length; n++)
			{
				array[ship[i].Y][ship[i].X] = '#';
				ship[i].X--;
			}
			++ship[i].X;	
		 
		}
	break;
	}
}

void checkShip(shipstatus ship[], char array[][10], int X, int Y)
{

	for (int i = 0; i < 5; i++)
	{

		int bound = (10 - ship[i].length);

		switch (ship[i].direction)
		{

		case 1:

			if (ship[i].Y > bound)
			{

				for (int n = 1; n <= ship[i].length; n++)
				{

					if (ship[i].X == X && ship[i].Y == Y)
					{
						ship[i].health--;
					}
					ship[i].Y--;
				}

				for (int n = 1; n <= ship[i].length; n++)
				{
					ship[i].Y++;
				}
			}

			else
			{
				for (int n = 1; n <= ship[i].length; n++)
				{
					if (ship[i].X == X && ship[i].Y == Y)
					{
						ship[i].health--;
					}
					ship[i].Y++;
				}

				for (int n = 1; n <= ship[i].length; n++)
				{
					ship[i].Y--;
				}
			}
		case 2:

			if (ship[i].X > bound)
			{
				for (int n = 1; n <= ship[i].length; n++)
				{
					if (ship[i].X == X && ship[i].Y == Y)
					{
						ship[i].health--;
					}
					ship[i].X--;
				}

				for (int n = 1; n <= ship[i].length; n++)
				{
					ship[i].X++;
				}
			}
			else
			{
				for (int n = 1; n <= ship[i].length; n++)
				{
					if (ship[i].X == X && ship[i].Y == Y)
					{
						ship[i].health--;
					}
					ship[i].X++;
				}

				for (int n = 1; n <= ship[i].length; n++)
				{
					ship[i].X--;
				}
			}

			break;
		}
	}

}
//function that outputs Error message if input is not valid
void error()
{
	if (!cin)
	{
		cout << "Error!";
	}
}

