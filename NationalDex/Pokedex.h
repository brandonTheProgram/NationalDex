#ifndef POKEDEX_H_
#define POKEDEX_H_

#include "Pokemon.h"           /** Pokemon                    **/
#include "PokemonEvolutions.h" /** PokemonEvolution           **/
#include "PokemonWeakness.h"   /** PokemonWeakness            **/
#include "Moveset.h"           /** Moveset                       **/
#include <vector>			   /** vector 					  **/
#include <iostream>			   /** cout & cin                 **/
#include <cstdlib>             /** srand & rand               **/
using std::vector;
using std::cout;
using std::cin;

//Namespace for the global constants in the class
/**************************************************************************
 * CONSTANTS
 * ------------------------------------------------------------------------
 * USED FOR ARRAY/VECTOR SIZE
 * ------------------------------------------------------------------------
 * AR_SIZE	: The size of the array/vector
 * ------------------------------------------------------------------------
 * USED FOR MAX REGION DEX SIZES
 * ------------------------------------------------------------------------
 * KANTO_DEX	: The size of the Kanto Pokedex
 * JOHTO_DEX	: The size of the Johto Pokedex
 * HOENN_DEX	: The size of the Hoenn Pokedex
 * SINNOH_DEX	: The size of the Sinnoh Pokedex
 * UNOVA_DEX	: The size of the Unova Pokedex
 * KALOS_DEX	: The size of the Kalos Pokedex
 * ALOLA_DEX	: The size of the Alola Pokedex
 * ------------------------------------------------------------------------
 * USED FOR COLUMN SIZE
 * ------------------------------------------------------------------------
 * INVALID_COL    : The size of the column for invalid input
 * ------------------------------------------------------------------------
 * USED FOR SPECIFIC VALUES
 * ------------------------------------------------------------------------
 * MENU    					: The menu that get's displayed
 * TYPE_EFFECTIVENESS_CHART : The chart of Pokemon types and their effectiveness
 * NATURES_CHART            : The chart of Pokemon Natures
 *************************************************************************/
namespace globalPDexConsts
{
	const int AR_SIZE          = 807;
	const int MAX_ATTKS        = 724;
	const int KANTO_DEX        = 151;
	const int JOHTO_DEX        = 251;
	const int HOENN_DEX        = 386;
	const int SINNOH_DEX       = 493;
	const int UNOVA_DEX        = 649;
	const int KALOS_DEX        = 721;
	const int ALOLA_DEX        = 807;
	const int INVALID_COL      = 30;

	const string MENU = "\nPokedex MENU:\n"
						"1 - Search for a Pokemon by name\n"
						"2 - Search for a Pokemon by pokedex number\n"
						"3 - Look at the Type Effectiveness Chart\n"
						"4 - Look at the Nature Chart for Effort Value\n"
						"5 - Surprise me with a Pokemon\n"
						"0 - EXIT\n"
						"Enter a command (0 to exit): ";

	const string TYPE_EFFECTIVENESS_CHART =
	"\n| CHART    | NORMAL |FIGHTING| FLYING | POISON | GROUND |  ROCK  |  BUG "
	"  | GHOST  | STEEL  |  FIRE  | WATER  | GRASS | ELETRIC | PSYCHIC |  ICE  "
	"| DRAGON |  DARK  | FAIRY |\n"
	"|-------------------------------------------------------------------------"
	"--------------------------------------------------------------------------"
	"------------------------|\n"
    "| NORMAL   |   1x   |   1x   |   1x   |   1x   |   1x   |  0.5x  |   1x   "
    "|   0x   |  0.5x  |   1x   |   1x   |   1x  |   1x    |   1x    |   1x  | "
    "  1x   |   1x   |   1x  |\n"
	"|-------------------------------------------------------------------------"
	"--------------------------------------------------------------------------"
	"------------------------|\n"
    "| FIGHTING |   2x   |   1x   |  0.5x  |  0.5x  |   1x   |   2x   |  0.5x  "
    "|   0x   |   2x   |   1x   |   1x   |   1x  |   1x    |  0.5x   |   2x  | "
    "  1x   |   2x   |  0.5x |\n"
	"|-------------------------------------------------------------------------"
	"--------------------------------------------------------------------------"
	"------------------------|\n"
    "| FLYING   |   1x   |   2x   |   1x   |   1x   |   1x   |  0.5x  |   2x   "
    "|   1x   |  0.5x  |   1x   |   1x   |   2x  |  0.5x   |   1x    |   1x  | "
    "  1x   |   1x   |   1x  |\n"
	"|-------------------------------------------------------------------------"
	"--------------------------------------------------------------------------"
	"------------------------|\n"
    "| POISON   |   1x   |   1x   |   1x   |  0.5x  |  0.5x  |  0.5x  |   1x   "
    "|  0.5x  |   0x   |   1x   |   1x   |   2x  |   1x    |   1x    |   1x  | "
    "  1x   |   1x   |   2x  |\n"
	"|-------------------------------------------------------------------------"
	"--------------------------------------------------------------------------"
	"------------------------|\n"
    "| GROUND   |   1x   |   1x   |   0x   |   2x   |   1x   |   2x   |  0.5x  "
    "|   1x   |   2x   |   2x   |   1x   |  0.5x |   2x    |   1x    |   1x  | "
    "  1x   |   1x   |   1x  |\n"
	"|-------------------------------------------------------------------------"
	"--------------------------------------------------------------------------"
	"------------------------|\n"
    "| ROCK     |   1x   |  0.5x  |   2x   |   1x   |  0.5x  |   1x   |   2x   "
    "|   1x   |  0.5x  |   2x   |   1x   |   1x  |   1x    |   1x    |   2x  | "
    "  1x   |   1x   |   1x  |\n"
	"|-------------------------------------------------------------------------"
	"--------------------------------------------------------------------------"
	"------------------------|\n"
    "| BUG      |   1x   |  0.5x  |  0.5x  |  0.5x  |   1x   |   1x   |   1x   "
    "|  0.5x  |  0.5x  |  0.5x  |   1x   |   2x  |   1x    |   2x    |   1x  | "
    "  1x   |   2x   |  0.5x |\n"
	"|-------------------------------------------------------------------------"
	"--------------------------------------------------------------------------"
	"------------------------|\n"
    "| GHOST    |   0x   |   1x   |   1x   |   1x   |   1x   |   1x   |   1x   "
    "|   2x   |   1x   |   1x   |   1x   |   1x  |   1x    |   2x    |   1x  | "
    "  1x   |  0.5x  |   1x  |\n"
	"|-------------------------------------------------------------------------"
	"--------------------------------------------------------------------------"
	"------------------------|\n"
    "| STEEL    |   1x   |   1x   |   1x   |   1x   |   1x   |   2x   |   1x   "
    "|   1x   |  0.5x  |  0.5x  |  0.5x  |   1x  |  0.5x   |   1x    |   2x  | "
    "  1x   |   1x   |   2x  |\n"
	"|-------------------------------------------------------------------------"
	"--------------------------------------------------------------------------"
	"------------------------|\n"
    "| FIRE     |   1x   |   1x   |   1x   |   1x   |   1x   |  0.5x  |   2x   "
    "|   1x   |   2x   |  0.5x  |  0.5x  |   2x  |   1x    |   1x    |   2x  | "
    " 0.5x  |   1x   |   1x  |\n"
	"|-------------------------------------------------------------------------"
	"--------------------------------------------------------------------------"
	"------------------------|\n"
    "| WATER    |   1x   |   1x   |   1x   |   1x   |   2x   |   2x   |   1x   "
    "|   1x   |   1x   |   2x   |  0.5x  |  0.5x |   1x    |   1x    |   1x  | "
    " 0.5x  |   1x   |   1x  |\n"
	"|-------------------------------------------------------------------------"
	"--------------------------------------------------------------------------"
	"------------------------|\n"
    "| GRASS    |   1x   |   1x   |  0.5x  |  0.5x  |   2x   |   2x   |  0.5x  "
    "|   1x   |  0.5x  |  0.5x  |   2x   |  0.5x |   1x    |   1x    |   1x  | "
    " 0.5x  |   1x   |   1x  |\n"
	"|-------------------------------------------------------------------------"
	"--------------------------------------------------------------------------"
	"------------------------|\n"
    "| ELETRIC  |   1x   |   1x   |   2x   |   1x   |   0x   |   1x   |   1x   "
    "|   1x   |   1x   |   1x   |   2x   |  0.5x |  0.5x   |   1x    |   1x  | "
    " 0.5x  |   1x   |   1x  |\n"
	"|-------------------------------------------------------------------------"
	"--------------------------------------------------------------------------"
	"------------------------|\n"
    "| PSYCHIC  |   1x   |   2x   |   1x   |   2x   |   1x   |   1x   |   1x   "
    "|   1x   |  0.5x  |   1x   |   1x   |   1x  |   1x    |  0.5x   |   1x  | "
    "  1x   |   0x   |   1x  |\n"
	"|-------------------------------------------------------------------------"
	"--------------------------------------------------------------------------"
	"------------------------|\n"
    "| ICE      |   1x   |   1x   |   2x   |   1x   |   2x   |   1x   |   1x   "
    "|   1x   |  0.5x  |  0.5x  |  0.5x  |   2x  |   1x    |   1x    |  0.5x | "
    "  2x   |   1x   |   1x  |\n"
	"|-------------------------------------------------------------------------"
	"--------------------------------------------------------------------------"
	"------------------------|\n"
    "| DRAGON   |   1x   |   1x   |   1x   |   1x   |   1x   |   1x   |   1x   "
    "|   1x   |  0.5x  |   1x   |   1x   |   1x  |   1x    |   1x    |   1x  | "
    "  2x   |   1x   |   0x  |\n"
	"|-------------------------------------------------------------------------"
	"--------------------------------------------------------------------------"
	"------------------------|\n"
    "| DARK     |   1x   |  0.5x  |   1x   |   1x   |   1x   |   1x   |   1x   "
    "|   2x   |   1x   |   1x   |   1x   |   1x  |   1x    |   2x    |   1x  | "
    "  1x   |  0.5x  |  0.5x |\n"
	"|-------------------------------------------------------------------------"
	"--------------------------------------------------------------------------"
	"------------------------|\n"
    "| FAIRY    |   1x   |   2x   |   1x   |  0.5x  |   1x   |   1x   |   1x   "
    "|   1x   |  0.5x  |  0.5x  |   1x   |   1x  |   1x    |   1x    |   1x  | "
    "  2x   |   2x   |   1x  |\n"
	"|-------------------------------------------------------------------------"
	"--------------------------------------------------------------------------"
	"------------------------|\n";

	const string NATURES_CHART =
"| CHART    | -Attack |-Defense| -Sp.Atk | -Sp.Def | -Speed |\n"
"|----------------------------------------------------------|\n"
"| +Attack  |  Hardy  | Lonely | Adamant | Naughty | Brave  |\n"
"|----------------------------------------------------------|\n"
"| +Defense |  Bold   | Docile | Impish  | Lax     | Relaxed|\n"
"|----------------------------------------------------------|\n"
"| +Sp.Atk  |  Modest | Mild   | Bashful | Rash    | Quiet  |\n"
"|----------------------------------------------------------|\n"
"| +Sp.Def  |  Calm   | Gentle | Careful | Quirky  | Sassy  |\n"
"|----------------------------------------------------------|\n"
"| +Speed   |  Timid  | Hasty  | Jolly   | Naive   | Serious|\n"
"|----------------------------------------------------------|\n";

	//The menu for the user
	enum Menu
	{
		EXIT,
		SEARCH_NAME,
		SEARCH_NUM,
		TYPE_EFFECTIVNESS_CHART,
		NATURE_CHART,
		SURPRISE,
		END
	};
}

//A Pokemon object with it's information
struct Pkmn
{
	Pokemon           currentPkmn;
	PokemonEvolutions pkmnEvos;
	Moveset           pkmnMoves;
	PokemonWeakness   pkmnWeakness;
};

/************************************************************************
* Pokedex Class
* 	This class represents a Pokedex object. It manages 4 attributes:
* 		pokedex, attackDex, pokedexCopy, and currentPokemon
*************************************************************************/
class Pokedex //Base class
{
	public:
		/******************************
		 **      OVERLOADERS         **
		 ******************************/
		//Overloading the array operator
		Pkmn& operator[] (int index){return pokedex[index];}

		/******************************
		 ** CONSTRUCTOR & DESTRUCTOR **
		 ******************************/

		/****************************************************************
		 * Pokedex ();
		 *   Constructor; this method initializes the Pokdex object
		 *   Parameters: none
		 *   Return: none
		 ***************************************************************/
		Pokedex(); //Default Constructor

		/****************************************************************
		 * ~Pokedex ();
		 *   Deconstructor; does not perform any specific function
		 *   Parameters: none
		 *   Return: none
		 ***************************************************************/
		~Pokedex(); //Deconstructor

		/******************
		 **** MUTATORS ****
		 ******************/

		/****************************************************************
		 * 	void CreateAttackList(const string& INPUT_FILE);
		 *
		 *   Mutator; this method creates the attackdex for the program
		 *   Parameters: INPUT_FILE (string) - the name of the input file
		 *   Return: none
		 ***************************************************************/
		void CreateAttackList(const string& INPUT_FILE);

		/****************************************************************
		 * 	void CreatePokedexCopy();
		 *
		 *   Mutator; this method creates a copy of the Pokedex with only a
		 *   		  Pokemon and not attacks or weaknesses
		 *   Parameters:
		 *   Return: none
		 ***************************************************************/
		void CreatePokedexCopy();

		/****************************************************************
		 * 	void LoadRegion(const string& INPUT_FILE, const int& REGION_MAX,
		 * 					const string& ATTACK_FILE);
		 *
		 *   Mutator; this method initializes the pokedex by loading in a region
		 *   Parameters: INPUT_FILE (string) - the name of the input file
		 *   			 REGION_MAX (int)    - the regional max in the pokedex
		 *   			 ATTACK_FILE(string) - the attacks for that region
		 *   Return: none
		 ***************************************************************/
		void LoadRegion(const string& INPUT_FILE, const int& REGION_MAX,
						const string& ATTACK_FILE);

		/****************************************************************
		 * 	void LoadPokemonMoves(std::ifstream & fin,
		 * 						  vector<string>& attackNames,
		 *		   	   	   	      vector<int>   & attackLvls);
		 *
		 *   Mutator; this method loads the moves of a pokemon from the
		 *   		  input file
		 *   Parameters: fin         (ifstream)       - the input file variable
		 *   			 attackNames (vector<string>) - the list of attack names
		 *   			 attackLvls  (vector<int>)    - the list of attack
		 *   			 								levels
		 *   Return: attackNames and attackLvls
		 ***************************************************************/
		void LoadPokemonMoves(std::ifstream& fin, vector<string>& attackNames,
				   	   	   	  vector<int>& attackLvls);

		/****************************************************************
		 * 	void SearchByName(std::ostream &fout);
		 *
		 *   Mutator; this method find the Pokemon by name that the user will
		 *   		  input
		 *   Parameters: fout (ostream) - the output variable
		 *   Return: none
		 ***************************************************************/
		void SearchByName(std::ostream &fout);

		/****************************************************************
		 * 	void SearchByNum(std::ostream &fout);
		 *
		 *   Mutator; this method find the Pokemon by pokedex number that the
		 *   		  user will input
		 *   Parameters: fout (ostream) - the output variable
		 *   Return: none
		 ***************************************************************/
		void SearchByNum(std::ostream &fout);

		/****************************************************************
		 * 	void RandomPokemon(std::ostream &fout);
		 *
		 *   Mutator; this method find a random Pokemon from the list
		 *   Parameters: fout (ostream) - the output variable
		 *   Return: none
		 ***************************************************************/
		void RandomPokemon(std::ostream &fout);

		/*******************
		 **** ACCESSORS ****
		 *******************/

		/****************************************************************
		 * 	globalPDexConsts::Menu GetAndCheckMenu() const;
		 *
		 *   Accessor; this method gets and checks an option from the menu
		 *   Parameters: none
		 *   Return: valid menu choice
		 ***************************************************************/
		globalPDexConsts::Menu GetAndCheckMenu() const;

		/****************************************************************
		 * 	Pokemon FindPokemon(const string &NAME) const;
		 *
		 *   Accessor; this method searches the Pokedex for the Pokemon matching
		 *   the name that the user inputted. If the Pokemon is found, then it
		 *   will be returned, but if it is not found, then an empty Pokemon
		 *   object will be returned
		 *   Parameters: none
		 *   Return: found/not found Pokemon
		 ***************************************************************/
		Pkmn FindPokemon(const string &NAME) const;

		/****************************************************************
		 * 	void PrintPokemon(std::ostream &fout) const;
		 *
		 *   Accessor; this method will output all of a Pokemon's information,
		 *   including the evolution tree if available
		 *   Parameters: fout (ostream) - the output variable
		 *   Return: none
		 ***************************************************************/
		void PrintPokemon(std::ostream &fout) const;

		/****************************************************************
		 * 	void PrintTypeChart(std::ostream &fout) const;
		 *
		 *   Accessor; this method will output the Type Effectivness Chart
		 *   Parameters: fout (ostream) - the output variable
		 *   Return: none
		 ***************************************************************/
		void PrintTypeChart(std::ostream &fout) const
		{
			fout << globalPDexConsts::TYPE_EFFECTIVENESS_CHART << endl;
		}

		/****************************************************************
		 * 	void PrintNatureChart(std::ostream &fout) const;
		 *
		 *   Accessor; this method will output the Pokemon Nature Chart
		 *   Parameters: fout (ostream) - the output variable
		 *   Return: none
		 ***************************************************************/
		void PrintNatureChart(std::ostream &fout) const
		{
			fout << globalPDexConsts::NATURES_CHART << endl;
		}

	private:
		vector<Pkmn>      pokedex;			//The Pokedex
		vector<Attack>    attackDex;		//The AttackDex
		vector<Pokemon>   pokedexCopy;		//The Copy of the Pokedex
		Pkmn              currentPokemon;	//The current Pokemon
};

#endif /* POKEDEX_H_ */
