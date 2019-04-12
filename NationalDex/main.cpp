#include "Pokedex.h"			  /** Pokedex **/
#include <time.h>                 /** time    **/
using namespace globalPDexConsts; /** Menu    **/

/******************************************************************************
 * NATIONALDEX
 *-----------------------------------------------------------------------------
 * This program will allow the user to input as a choice from the menu how they
 *    wish the Pokedex to perform to help the user. It will display the
 *    information in an output file after the user choose to search by name,
 *    pokedex number, surprise them with a random Pokemon, or displaying the
 *    type effectivness chart. The program will end once the user chooses to
 *    exit the program. This program is meant to mimic the functions of the
 *    Pokedex as seen in anime and in the games.
 *-----------------------------------------------------------------------------
 * INPUT
 * 		The following information will be input for this program:
 * 	  		menuChoice         	: The choice of action for the Pokedex
 * 	  		pokemonName         : The name of the Pokemon chosen
 * 	  		pokedexNum          : The index in the Pokedex chosen
 * OUTPUT
 * 	  	The following information will be output for this program:
			oFile    : The output file variable
			pokemonAr: The pokemon array
 ***********************************************************************/
int main()
{
	/**************************************************************************
	 * CONSTANTS
	 * ------------------------------------------------------------------------
	 * USED FOR I/O FILES
	 * ------------------------------------------------------------------------
	 * KANTO_INPUT_FILE   : the name of the input file for the Kanto region
	 * KANTO_ATTACK_FILE  : the name of the input file for the Kanto attacks
	 * JOHTO_INPUT_FILE   : the name of the input file for the Johto region
	 * JOHTO_ATTACK_FILE  : the name of the input file for the Johto attacks
	 * HOENN_INPUT_FILE   : the name of the input file for the Hoenn region
	 * HOENN_ATTACK_FILE  : the name of the input file for the Hoenn attacks
	 * SINNOH_INPUT_FILE  : the name of the input file for the Sinnoh region
	 * SINNOH_ATTACK_FILE : the name of the input file for the Sinnoh attacks
	 * UNOVA_INPUT_FILE	  : the name of the input file for the Unova region
	 * UNOVA_ATTACK_FILE  : the name of the input file for the Unova attacks
	 * KALOS_INPUT_FILE   : the name of the input file for the Kalos region
	 * KALOS_ATTACK_FILE  : the name of the input file for the Kalos attacks
	 * ALOLA_INPUT_FILE   : the name of the input file for the Alola region
	 * ALOLA_ATTACK_FILE  : the name of the input file for the Alola attacks
	 * OUTPUT_FILE        : the name of the output file
	 * ATTACKDEX_FILE     : the name of the input file for the Pokemon Attacks
	 *************************************************************************/
	const string KANTO_INPUT_FILE  = "Kanto.txt";
	const string KANTO_ATTACK_FILE = "KantoAttacks.txt";
	const string JOHTO_INPUT_FILE  = "Johto.txt";
	const string JOHTO_ATTACK_FILE = "JohtoAttacks.txt";
	const string HOENN_INPUT_FILE  = "Hoenn.txt";
	const string HOENN_ATTACK_FILE = "HoennAttacks.txt";
	const string SINNOH_INPUT_FILE = "Sinnoh.txt";
	const string SINNOH_ATTACK_FILE = "SinnohAttacks.txt";
	const string UNOVA_INPUT_FILE  = "Unova.txt";
	const string UNOVA_ATTACK_FILE = "UnovaAttacks.txt";
	const string KALOS_INPUT_FILE  = "Kalos.txt";
	const string KALOS_ATTACK_FILE = "KalosAttacks.txt";
	const string ALOLA_INPUT_FILE  = "Alola.txt";
	const string ALOLA_ATTACK_FILE = "AlolaAttacks.txt";
	const string OUTPUT_FILE       = "OFile.txt";
	const string ATTACKDEX_FILE    = "AttackDex.txt";

	Pokedex pokedex;				  //IN & PROC & OUT - The Pokedex

	Menu menuChoice;				  //IN & PROC       - The choice from
									  //                  the menu

	srand(time(NULL));				  //PROC 			- The random seed
									  //                  generator

	std::ofstream fout;				  //OUT             - The output file
								      //                  variable

	//PROCESSING - Create the AttackDex
	pokedex.CreateAttackList(ATTACKDEX_FILE);

	//INPUT - Read in the data from the  Kanto file
	pokedex.LoadRegion(KANTO_INPUT_FILE, KANTO_DEX, KANTO_ATTACK_FILE);

	//INPUT - Read in the data from the  Johto file
	pokedex.LoadRegion(JOHTO_INPUT_FILE, JOHTO_DEX, JOHTO_ATTACK_FILE);

	//INPUT - Read in the data from the  Hoenn file
	pokedex.LoadRegion(HOENN_INPUT_FILE, HOENN_DEX, HOENN_ATTACK_FILE);

	//INPUT - Read in the data from the  Sinnoh file
	pokedex.LoadRegion(SINNOH_INPUT_FILE, SINNOH_DEX, SINNOH_ATTACK_FILE);

	//INPUT - Read in the data from the  Unova file
	pokedex.LoadRegion(UNOVA_INPUT_FILE, UNOVA_DEX, UNOVA_ATTACK_FILE);

	//INPUT - Read in the data from the  Kalos file
	pokedex.LoadRegion(KALOS_INPUT_FILE, KALOS_DEX, KALOS_ATTACK_FILE);

	//INPUT - Read in the data from the  Alola file
	pokedex.LoadRegion(ALOLA_INPUT_FILE, ALOLA_DEX, ALOLA_ATTACK_FILE);

	//PROCESSING - Create a copy of the Pokedex with only Pokemon
	pokedex.CreatePokedexCopy();

	//OUTPUT - Open the output file as a c-string
	fout.open(OUTPUT_FILE.c_str());

	cout << "\nWelcome to the Pokemon Encyclopedia or Pokedex for short. "
			"\nMy name is Dexter, how may I help you on your "
			"journey to become a Pokemon Master? \n";

	/**************************************************************************
	 * INPUT - gets the choice from the menu as input and checks to make sure
	 *         that it is valid.
	 *************************************************************************/
	menuChoice = pokedex.GetAndCheckMenu();

	/**************************************************************************
	 * PROCESSING - This is the primary loop for the program.
	 *              It will continue to ask the user what would like to do with
	 *              the Pokedex until they choose to exit.
	 *************************************************************************/
	while(menuChoice != EXIT)
	{
		switch(menuChoice)
		{
		case SEARCH_NAME:				pokedex.SearchByName(fout);
										break;

		case SEARCH_NUM:				pokedex.SearchByNum(fout);
										break;

		case TYPE_EFFECTIVNESS_CHART:	cout << "\nCheck the output file for "
											 << "the wekaness chart\n";

										pokedex.PrintTypeChart(fout);
										break;

		case NATURE_CHART:				cout << "\nCheck the output file for "
				 	 	 	 	 	 	 	 << "the nature chart\n";

										pokedex.PrintNatureChart(fout);
										break;

		case SURPRISE:					pokedex.RandomPokemon(fout);
										break;

		default:						cout << "\nERROR\n";
		}

		//INPUT - Get the menu choice from the user again
		menuChoice = pokedex.GetAndCheckMenu();
	}

	//Close the output file
	fout.close();

	return 0;
}
