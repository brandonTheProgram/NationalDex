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
 * 	  		MenuChoice         	: The choice of action for the Pokedex
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
	 * KANTO_INPUT_FILE  : the name of the input file for the Kanto region
	 * JOHTO_INPUT_FILE  : the name of the input file for the Johto region
	 * HOENN_INPUT_FILE  : the name of the input file for the Hoenn region
	 * SINNOH_INPUT_FILE : the name of the input file for the Sinnoh region
	 * UNOVA_INPUT_FILE	 : the name of the input file for the Unova region
	 * KALOS_INPUT_FILE  : the name of the input file for the Kalos region
	 * ALOLA_INPUT_FILE  : the name of the input file for the Alola region
	 * OUTPUT_FILE       : the name of the output file
	 *************************************************************************/
	const string KANTO_INPUT_FILE  = "Kanto.txt";
	const string JOHTO_INPUT_FILE  = "Johto.txt";
	const string HOENN_INPUT_FILE  = "Hoenn.txt";
	const string SINNOH_INPUT_FILE = "Sinnoh.txt";
	const string UNOVA_INPUT_FILE  = "Unova.txt";
	const string KALOS_INPUT_FILE  = "Kalos.txt";
	const string ALOLA_INPUT_FILE  = "Alola.txt";
	const string OUTPUT_FILE       = "OFile.txt";

	Pokedex pokedex;				  //IN & PROC & OUT - The Pokedex

	Menu menuChoice;				  //IN & PROC       - The choice from
									  //                  the menu

	srand(time(NULL));				  //PROC 			- The random seed
									  //                  generator

	std::ofstream fout;				  //OUT             - The output file
								      //                  variable

	//INPUT - Read in the data from the  Kanto file
	pokedex.LoadRegion(KANTO_INPUT_FILE, 151);

	//INPUT - Read in the data from the  Johto file
	pokedex.LoadRegion(JOHTO_INPUT_FILE, 251);

	//INPUT - Read in the data from the  Hoenn file
	pokedex.LoadRegion(HOENN_INPUT_FILE, 386);

	//INPUT - Read in the data from the  Sinnoh file
	pokedex.LoadRegion(SINNOH_INPUT_FILE, 493);

	//INPUT - Read in the data from the  Unova file
	pokedex.LoadRegion(UNOVA_INPUT_FILE, 649);

	//INPUT - Read in the data from the  Kalos file
	pokedex.LoadRegion(KALOS_INPUT_FILE, 721);

	//INPUT - Read in the data from the  Kalos file
	pokedex.LoadRegion(ALOLA_INPUT_FILE, 807);

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
