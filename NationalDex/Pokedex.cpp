#include "Pokedex.h"

/************************************************************************
* Method Pokedex: Class Pokedex
*----------------------------------------------------------------------
* 	 This method creates the Pokedex object
* 	 ==> returns nothing
*-----------------------------------------------------------------------
* PRE-CONDITIONS
* 	The following need to be passed in
*
* POST-CONDITIONS
* 	==> returns nothing
*************************************************************************/
Pokedex::Pokedex()
{
	pokedex    .clear();
	attackDex  .clear();
	pokedexCopy.clear();
	pokedex    .reserve(globalPDexConsts::AR_SIZE);
	pokedexCopy.reserve(globalPDexConsts::AR_SIZE);
	attackDex  .reserve(globalPDexConsts::MAX_ATTKS);
}

/************************************************************************
* Method ~Pokedex: Class Pokedex
*----------------------------------------------------------------------
* 	 This method deletes the Pokedex object
* 	 ==> returns nothing
*-----------------------------------------------------------------------
* PRE-CONDITIONS
* 	The following need to be passed in
*
* POST-CONDITIONS
* 	==> returns nothing
*************************************************************************/
Pokedex::~Pokedex()
{
	pokedex.clear();
	attackDex.clear();
	pokedexCopy.clear();

	vector<Pkmn>().swap(pokedex);
	vector<Attack>().swap(attackDex);
	vector<Pokemon>().swap(pokedexCopy);
}

/************************************************************************
* Method CreateAttackList: Class Pokedex
*----------------------------------------------------------------------
* 	 This method creates the attackdex
* 	 ==> returns nothing
*-----------------------------------------------------------------------
* PRE-CONDITIONS
* 	The following need to be passed in
* 		INPUT_FILE (string) - the input file
*
* POST-CONDITIONS
* 	==> returns nothing
*************************************************************************/
void Pokedex::CreateAttackList(const string& INPUT_FILE)
{
	std::ifstream fin(INPUT_FILE.c_str()); //PROC - Open the input file

	int index;							   //PROC - the index in the array

	Attack *attack = new Attack;	       //PROC - create a new attack

	index = 0;

	while(!fin.eof() && (index < globalPDexConsts::MAX_ATTKS))
	{
		getline(fin, attack->name);
		getline(fin, attack->desc);
		getline(fin, attack->type);
		getline(fin, attack->category);
		fin >> attack->pwr;
		fin >> attack->acc;
		fin >> attack->pp;
		fin >> attack->effRate;
		fin >> attack->TM;
		fin >> attack->TMNum;

		attackDex.push_back(*attack);

		fin.ignore(1000, '\n');
		fin.ignore(1000, '\n');

		attack = new Attack;

		index++;
	}

	delete attack;
	attack = nullptr;

	fin.close();
}

/************************************************************************
* Method CreatePokedexCopy: Class Pokedex
*----------------------------------------------------------------------
* 	 This method creates a copy of the Pokedex with only a Pokemon and
* 	 	not attacks or weaknesses
* 	 ==> returns nothing
*-----------------------------------------------------------------------
* PRE-CONDITIONS
* 	The following need to be passed in
*
* POST-CONDITIONS
* 	==> returns nothing
*************************************************************************/
void Pokedex::CreatePokedexCopy()
{
	for(auto it: pokedex)
	{
		//PROCESSING - Add only the Pokemon to the list
		pokedexCopy.push_back(it.currentPkmn);
	}
}

/************************************************************************
* Method LoadRegion: Class Pokedex
*----------------------------------------------------------------------
* 	 This method loads in one region at a time and initializes the Pokedex
* 	 ==> returns nothing
*-----------------------------------------------------------------------
* PRE-CONDITIONS
* 	The following need to be passed in
* 		INPUT_FILE  (string) - The name of the input file
* 		REGION_MAX  (int)    - The max number of Pokemon available in the region
* 		ATTACK_FILE (string) - The name of the attack file for the region
*
* POST-CONDITIONS
* 	==> returns nothing
*************************************************************************/
void Pokedex::LoadRegion(const string& INPUT_FILE, const int& REGION_MAX,
						 const string& ATTACK_FILE)
{
	static int pokdexIndex = 0;                   //PROC - the position in
											      //	   in vector

	std::ifstream fin(INPUT_FILE.c_str());        //IN   - the input file
											      //       variable

	std::ifstream attackFin(ATTACK_FILE.c_str()); //IN   - the attack
												  //       file variable

	vector<string> attackNames;					  //PROC - the names of the
												  //       attacks
	vector<int> attackLvls;						  //PROC - the levels of the
												  //       attacks

	Pkmn *newPokemon = new Pkmn;				  //PROC - Create a new Pokemon

	//While not at the end of the file and the index doesn't exceed the max
	//number of Pokemon available in the region
	while(!fin.eof() && pokdexIndex < REGION_MAX)
	{
		//INPUT - Store the information of the Pokemon
		fin >> newPokemon->currentPkmn;

		//PROCESSING - Initialize the Enums using the types
		newPokemon->pkmnWeakness.InitializePriTypeEnum
									(newPokemon->currentPkmn.GetPriType());

		newPokemon->pkmnWeakness.InitializeSecTypeEnum
									(newPokemon->currentPkmn.GetSecType());

		//PROCESSING - Calculate the damage that the Pokemon would take
		newPokemon->pkmnWeakness.CalcDamageTaken();

		//PROCESSING - Load in the Pokemon's moves
		LoadPokemonMoves(attackFin, attackNames, attackLvls);

		//PROCESSING - Initialize the Pokemon's moves
		newPokemon->pkmnMoves.InitializeMoveSets
								(attackDex, attackNames, attackLvls);

		//PROCESSING - Store the Pokemon in the vector
		pokedex.push_back(*newPokemon);

		//PROCESSING - Clear the arrays for reuse and deallocate memory
		attackNames.clear();
		attackLvls.clear();

		vector<string>().swap(attackNames);
		vector<int>().swap(attackLvls);

		newPokemon = new Pkmn;

		pokdexIndex++;
	}

	delete newPokemon;

	//Close the input files
	fin.close();
	attackFin.close();
}

/************************************************************************
* Method LoadPokemonMoves: Class Pokedex
*----------------------------------------------------------------------
* 	 This method loads the Pokemon's moves
* 	 ==> returns attackNames and attackLvls
*-----------------------------------------------------------------------
* PRE-CONDITIONS
* 	The following need to be passed in
* 		fin         (ifstream)       - the input file variable
*   	attackNames (vector<string>) - the list of attack names
*   	attackLvls  (vector<int>)    - the list of attack levels
*
* POST-CONDITIONS
* 	==> returns attackNames and attackLvls
*************************************************************************/
void Pokedex::LoadPokemonMoves(std::ifstream& fin, vector<string>& attackNames,
							   vector<int>& attackLvls)
{
	string pokemonName;	//PROC - The name of the Pokemon
	string attackName;  //PROC - The name of the attack

	int moveListSize;   //PROC - The amount of moves the Pokemon knows
	int    attackLvl;	//PROC - The level of the attack

	getline(fin, pokemonName);

	fin >> moveListSize;

	attackNames.reserve(moveListSize);
	attackLvls.reserve(moveListSize);

	for(int index = 0; index < moveListSize; index++)
	{
		fin >> attackLvl;
		fin.ignore(1000, ' ');
		getline(fin, attackName);

		attackNames.push_back(attackName);
		attackLvls.push_back(attackLvl);
	}

	fin.ignore(1000, '\n');
}

/************************************************************************
* Method SearchByName: Class Pokedex
*----------------------------------------------------------------------
* 	 This method gets and checks the name of the Pokemon that the user will
* 	 	search for. If found, then print the information, else output an error
* 	 	message
* 	 ==> returns nothing
*-----------------------------------------------------------------------
* PRE-CONDITIONS
* 	The following need to be passed in
* 		fout (ostream) - the output variable
*
* POST-CONDITIONS
* 	==> returns nothing
*************************************************************************/
void Pokedex::SearchByName(std::ostream &fout)
{
	string pokemonName; //IN - the name of the Pokemon

	//INPUT - Get the name of the Pokemon
	cout << "\nWhat is the name of the Pokemon? ";

	getline(cin, pokemonName);

	//PROCESSING - Capitalize the first letter of the Pokemon's name
	pokemonName[0] = toupper(pokemonName[0]);

	//PROCESSING - Search for the Pokemon
	currentPokemon = FindPokemon(pokemonName);

	//If it is not found, output a message saying it wasn't found
	if(currentPokemon.currentPkmn.GetPokedexNumber() == 0)
	{
		cout << "\nThe Pokemon was not found. Check your spelling.\n";
	}
	else
	{
		//If the Pokemon has evolutions, then initialize them
		if(currentPokemon.currentPkmn.GetEvolutions() != 0)
		{
			currentPokemon.pkmnEvos.SetInitialValues(pokedexCopy,
												    currentPokemon.currentPkmn);
		}

		cout << endl;

		cout << currentPokemon.currentPkmn.GetName()
			 << " was found. Check the output "
			 << "file for the Pokemon\'s information\n";

		//OUTPUT - Print the pokemon's information
		PrintPokemon(fout);
	}
}

/************************************************************************
* Method SearchByName: Class Pokedex
*----------------------------------------------------------------------
* 	 This method gets and checks the number of the Pokemon that the user will
* 	 	search for. It then print the information
* 	 ==> returns nothing
*-----------------------------------------------------------------------
* PRE-CONDITIONS
* 	The following need to be passed in
* 		fout (ostream) - the output variable
*
* POST-CONDITIONS
* 	==> returns nothing
*************************************************************************/
void Pokedex::SearchByNum(std::ostream &fout)
{
	int pokedexNumber;   //IN          - the number of the pokemon that
					     //              corresponds with the Pokedex

	bool   invalid;      //PROC       - the condition for invalid inputs
	bool   fail;         //PROC       - the condition for failed inputs

	string intString;    //PROC & OUT - the int converted to a string
	string errorMessage; //OUT        - the message when an error is encountered

	do
	{
		//INPUT - Get the number of the Pokemon
		cout << "\nWhat is the number of the pokemon that you are "
			 <<	"looking for? ";

		cin  >> pokedexNumber;

		invalid = (pokedexNumber < 1 ||
				   pokedexNumber > globalPDexConsts::AR_SIZE);

		fail    = (cin.fail());

		if(invalid || fail)
		{
			//If input fail, then specify that a number should be entered
			if(fail)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "\n**** Please input a NUMBER between 1 and "
					 << globalPDexConsts::AR_SIZE << " ****\n\n";
			}
			//Output an error message
			else
			{
				intString = std::to_string(pokedexNumber);
				errorMessage = ("The number " + intString
											  + " is an invalid entry");
				cout << std::left << endl;
				cout << "**** " << std::setw(globalPDexConsts::INVALID_COL)
					 << (errorMessage)
					 << " ****";
				cout << "\n**** " << "Please input a number between 1 and "
					 << globalPDexConsts::AR_SIZE << " ****\n\n";
				cout << std::right;
			}
		}

	}while(invalid || fail);

	//PROCESSING - Store the Pokemon that was searched for
	currentPokemon = pokedex[pokedexNumber - 1];

	//If the Pokemon has evolutions, then initialize them
	if(currentPokemon.currentPkmn.GetEvolutions() != 0)
	{
		currentPokemon.pkmnEvos.SetInitialValues(pokedexCopy,
											    currentPokemon.currentPkmn);
	}

	cout << endl;

	cout << "Check the output file for " << currentPokemon.currentPkmn.GetName()
		 << "\'s information\n";

	//OUTPUT - Print the pokemon's information
	PrintPokemon(fout);

	cin.ignore(1000, '\n');
}

/************************************************************************
* Method RandomPokemon: Class Pokedex
*----------------------------------------------------------------------
* 	 This method find a random Pokemon from the list, then prints
* 	 	the information
* 	 ==> returns nothing
*-----------------------------------------------------------------------
* PRE-CONDITIONS
* 	The following need to be passed in
* 		fout (ostream) - the output variable
*
* POST-CONDITIONS
* 	==> returns nothing
*************************************************************************/
void Pokedex::RandomPokemon(std::ostream& fout)
{
	int index;	//PROC - The index in the vector

	//PROCESSING - Store a randon index between 0 and the max size
	index = (rand() % globalPDexConsts::AR_SIZE);

	//PROCESSING - Store the current Pokemon
	currentPokemon = pokedex[index];

	cout << endl;

	cout << "Check the output file for " << currentPokemon.currentPkmn.GetName()
		 << "\'s information\n";

	//If the Pokemon has evolutions, then initialize them
	if(currentPokemon.currentPkmn.GetEvolutions() != 0)
	{
		currentPokemon.pkmnEvos.SetInitialValues(pokedexCopy,
											    currentPokemon.currentPkmn);
	}

	//OUTPUT - Print the pokemon's information
	PrintPokemon(fout);
}

/************************************************************************
* Method GetAndCheckMenu: Class Pokedex
*----------------------------------------------------------------------
* 	 This method gets and checks an option from the menu
* 	 ==> returns menu choice
*-----------------------------------------------------------------------
* PRE-CONDITIONS
* 	The following need to be passed in
*
* POST-CONDITIONS
* 	==> returns menuChoice
*************************************************************************/
globalPDexConsts::Menu Pokedex::GetAndCheckMenu() const
{
	using globalPDexConsts::Menu; //PROC       - the menu enums

	Menu menuChoice;  			  //PROC       - the choice from menu converted
								  //             to an enum

	int  choiceFromMenu; 		  //IN         - the choice from the menu;

	bool   invalid;      		  //PROC       - the condition for invalid input
	bool   fail;         		  //PROC       - the condition for failed input

	string menuString;   		  //PROC & OUT - the menu choice converted to
								  //             a string
	string errorMessage; 		  //OUT        - the message when an error is
								  //             encountered

	do
	{
		cout << globalPDexConsts::MENU;

		cin  >> choiceFromMenu;

		//PROCESSING - Convert the menu choic into an enumerated type
		menuChoice = Menu(choiceFromMenu);

		invalid = (menuChoice != Menu::EXIT                    &&
				   menuChoice != Menu::SEARCH_NAME 			   &&
				   menuChoice != Menu::SEARCH_NUM  			   &&
				   menuChoice != Menu::TYPE_EFFECTIVNESS_CHART &&
				   menuChoice != Menu::NATURE_CHART 		   &&
				   menuChoice != Menu::SURPRISE);

		fail    = (cin.fail());

		if(invalid || fail)
		{
			//If input fail, then specify that a number should be entered
			if(fail)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "\n**** Please input a NUMBER between "
					 << Menu::EXIT
					 << " and " << (Menu::END - 1) << " ****\n";
			}
			//Output an error message
			else
			{
				menuString = std::to_string(menuChoice);
				errorMessage = ("The number " + menuString
											  + " is an invalid entry");
				cout << std::left << endl;
				cout << "**** " << std::setw(globalPDexConsts::INVALID_COL)
					 << (errorMessage)
					 << " ****";
				cout << "\n**** " << "Please input a number between "
					 << Menu::EXIT  <<  " and " << (Menu::END - 1)
					 << " ****\n\n";
				cout << std::right;
			}
		}

	}while(invalid || fail);

	cin.ignore(1000, '\n');

	return menuChoice;
}

/************************************************************************
* Method GetAndCheckMenu: Class Pokedex
*----------------------------------------------------------------------
* 	 This method searches the Pokedex for the Pokemon matching the name that the
*    	user inputted. If the Pokemon is found, then it will be returned, but if
*    	it is not found, then an empty Pokemon object will be returned
* 	 ==> found/not found Pokemon
*-----------------------------------------------------------------------
* PRE-CONDITIONS
* 	The following need to be passed in
* 		NAME (string) - The name of the Pokemon that is being searched for
*
* POST-CONDITIONS
* 	==> found/not found Pokemon
*************************************************************************/
Pkmn Pokedex::FindPokemon(const string &NAME) const
{
	Pkmn searchPokemon;     //PROC -  The Pokemon that will be returned found
							//		  or not found

	int index;		        //PROC - the index in the array

	bool found;		        //PROC - the condition if the pokemon was found

	//PROCESSING - Initialize the values
	index = 0;
	found = false;

   while(!found && index < globalPDexConsts::AR_SIZE)
   {
	   //If the name matches the one being searched for, then end the loop
		if (!NAME.compare(pokedex[index].currentPkmn.GetName()))
		{
			found = true;
			searchPokemon = pokedex[index];
		}
		else
		{
			index++;
		}
	}

   return searchPokemon;
}

/************************************************************************
* Method PrintPokemon: Class Pokedex
*----------------------------------------------------------------------
* 	 This method will output all of a Pokemon's information, including the
*    	evolution tree if available
* 	 ==> returns nothing
*-----------------------------------------------------------------------
* PRE-CONDITIONS
* 	The following need to be passed in
* 		fout (ostream) - the output variable
*
* POST-CONDITIONS
* 	==> returns nothing
*************************************************************************/
void Pokedex::PrintPokemon(std::ostream& fout) const
{
	//OUTPUT - Display the basic Pokemon's information
	fout << currentPokemon.currentPkmn;

	//OUTPUT - Display the Pokemon's damage
	fout << currentPokemon.pkmnWeakness;

	//PROCESSING - If the Pokemon has evolutions, then output the evolution tree
	if(currentPokemon.currentPkmn.GetEvolutions() != 0)
		currentPokemon.pkmnEvos.PrintEvoTree(fout);

	//OUTPUT - Display the Pokemon's lvl moveset
	currentPokemon.pkmnMoves.PrintLvl(fout);

	//OUTPUT - Display the Pokemon's TM moveset
	currentPokemon.pkmnMoves.PrintTM(fout);

	fout << "*******************************************"
			"********************\n\n";
}
