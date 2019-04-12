#include "PokemonEvolutions.h"

/************************************************************************
* Method PokemonEvolutions: Class PokemonEvolutions
*----------------------------------------------------------------------
* 	 This method creates the Pokemon Evolutions object
* 	 ==> returns nothing
*-----------------------------------------------------------------------
* PRE-CONDITIONS
* 	The following need to be passed in
*
* POST-CONDITIONS
* 	==> returns nothing
*************************************************************************/
PokemonEvolutions::PokemonEvolutions()
{
	pokedexCopy.clear();
}

/************************************************************************
* Method PokemonEvolutions: Class PokemonEvolutions
*----------------------------------------------------------------------
* 	 This method creates the Pokemon Evolutions object with values
* 	 ==> returns nothing
*-----------------------------------------------------------------------
* PRE-CONDITIONS
* 	The following need to be passed in
* 		pokedex       (vector<Pokemon>) - the pokedex
*   	currentPokemon(currentPokemon)  - the current Pokemon
*
* POST-CONDITIONS
* 	==> returns nothing
*************************************************************************/
PokemonEvolutions::PokemonEvolutions(const vector<Pokemon>& pokedex,
		 	 	 	 	 	 	 	 const Pokemon& currentPokemon)
{
	pokedexCopy = pokedex;

	mainPokemon = currentPokemon;

	firstEvo  	= pokedexCopy[mainPokemon.GetFirstEvoNum() - 1];

	//If the Pokemon has a second evolution, then store it
	if(mainPokemon.GetEvolutions() == 2)
		secondEvo 	= pokedexCopy[mainPokemon.GetSecondEvoNum() - 1];

	//If the Pokemon is not a special branch pokemon like Eevee which has
	//multiple final evolution forms, then store it
	if(mainPokemon.GetEvolutions() <= 2)
		finalEvo  	= pokedexCopy[mainPokemon.GetFinalEvoNum() - 1];

	//If the Pokemon only has one branch evo, then store it
	if(mainPokemon.GetBranchEvo() == true && mainPokemon.GetEvolutions() <= 2)
		branchEvo 	= pokedexCopy[mainPokemon.GetBranchEvoNum() - 1];
}

/************************************************************************
* Method ~PokemonEvolutions: Class PokemonEvolutions
*----------------------------------------------------------------------
* 	 This method deletes the Pokemon Evolutions object
* 	 ==> returns nothing
*-----------------------------------------------------------------------
* PRE-CONDITIONS
* 	The following need to be passed in
*
* POST-CONDITIONS
* 	==> returns nothing
*************************************************************************/
PokemonEvolutions::~PokemonEvolutions()
{
	pokedexCopy.clear();

	vector<Pokemon>().swap(pokedexCopy);
}

/************************************************************************
* Method SetInitialValues: Class PokemonEvolutions
*----------------------------------------------------------------------
* 	 This method sets the Pokemon Evolutions object with values
* 	 ==> returns nothing
*-----------------------------------------------------------------------
* PRE-CONDITIONS
* 	The following need to be passed in
* 		pokedex       (vector<Pokemon>) - the pokedex
*   	currentPokemon(currentPokemon)  - the current Pokemon
*
* POST-CONDITIONS
* 	==> returns nothing
*************************************************************************/
void PokemonEvolutions::SetInitialValues(const vector<Pokemon>& pokedex,
		 	 	 	 	 	 	 	 	 const Pokemon& currentPokemon)
{
	pokedexCopy = pokedex;

	mainPokemon = currentPokemon;

	firstEvo  	= pokedexCopy[mainPokemon.GetFirstEvoNum() - 1];

	//If the Pokemon has a second evolution, then store it
	if(mainPokemon.GetEvolutions() == 2)
		secondEvo 	= pokedexCopy[mainPokemon.GetSecondEvoNum() - 1];

	//If the Pokemon is not a special branch pokemon like Eevee which has
	//multiple final evolution forms, then store it
	if(mainPokemon.GetEvolutions() <= 2)
		finalEvo  	= pokedexCopy[mainPokemon.GetFinalEvoNum() - 1];

	//If the Pokemon only has one branch evo, then store it
	if(mainPokemon.GetBranchEvo() == true && mainPokemon.GetEvolutions() <= 2)
		branchEvo 	= pokedexCopy[mainPokemon.GetBranchEvoNum() - 1];
}

/************************************************************************
* Method PrintEvoTree: Class PokemonEvolutions
*----------------------------------------------------------------------
* 	 This method prints the evolution tree
* 	 ==> returns nothing
*-----------------------------------------------------------------------
* PRE-CONDITIONS
* 	The following need to be passed in
* 		fout (ostream) - the output variable
*
* POST-CONDITIONS
* 	==> returns nothing
*************************************************************************/
void PokemonEvolutions::PrintEvoTree(std::ostream &fout) const
{
	fout << "\nEvolutionary Chain:\n\n";

	//PROCESSING - If the pokemon has a branch evolution tree, then display that
	if(mainPokemon.GetBranchEvo() == true)
	{
		PrintBranchEvos(fout);
	}
	else
	{
		//PROCESSING - If the pokemon has only one evolution, then display that
		if(mainPokemon.GetEvolutions() == 1)
		{
			PrintTwoEvos(fout);
		}
		//PROCESSING - If the pokemon has only two evolution, then display that
		else
		{
			PrintThreeEvos(fout);
		}
	}
}

/************************************************************************
* Method PrintTwoEvos: Class PokemonEvolutions
*----------------------------------------------------------------------
* 	 This prints a two evolution family tree
* 	 ==> returns nothing
*-----------------------------------------------------------------------
* PRE-CONDITIONS
* 	The following need to be passed in
* 		fout (ostream) - the output variable
*
* POST-CONDITIONS
* 	==> returns nothing
*************************************************************************/
void PokemonEvolutions::PrintTwoEvos(std::ostream &fout) const
{
	std::ostringstream evoTree; //PROC & OUT - The evolution tree

	//PROCESSING - If the pokemon is the first evolution
	evoTree << firstEvo.GetName() << " evolves by ";

	//PROCESSING - If the Pokemon evolves through special conditions
	if((firstEvo.GetEvoThroughLvl()  == true  &&
		firstEvo.GetEvoThroughCond() == true) ||
	   (firstEvo.GetEvoThroughLvl()  == false  &&
		firstEvo.GetEvoThroughCond() == true))
	{
		evoTree << firstEvo.GetFinalEvoCond();
	}
	else if(firstEvo.GetEvoThroughLvl()  == true  &&
			firstEvo.GetEvoThroughCond() == false)
	{
		evoTree << "leveling up to level " << firstEvo.GetEvoLvl();
	}
	else
	{
		evoTree << "\nERROR\n";
	}

	evoTree << " into " << finalEvo.GetName() << ".";

	//If the Pokemon has a branch evolution, then print their information
	if(mainPokemon.GetBranchEvo() == true)
	{
		evoTree << " A branch evolution is available by evolving "
			 << firstEvo.GetName() << " by ";

		//PROCESSING - If the Pokemon evolves through special conditions
		if((branchEvo.GetEvoThroughLvl() == true    &&
			branchEvo.GetEvoThroughCond() == true)   ||
		   (branchEvo.GetEvoThroughLvl()  == false   &&
		    branchEvo.GetEvoThroughCond() == true))
		{
			evoTree << branchEvo.GetFinalEvoCond();
		}
		else if(branchEvo.GetEvoThroughLvl()  == true &&
				branchEvo.GetEvoThroughCond() == false)
		{
			evoTree << "leveling up to level " << branchEvo.GetFinalEvoLvl();;
		}
		else
		{
			evoTree << "\nERROR\n";
		}

		evoTree << " into " << branchEvo.GetName() << ".";
	}

	//OUTPUT - Print the evolution tree in paragraph formation
	fout << globalPkmnConsts::WordWrap(evoTree.str(),
									   globalPkmEvoConsts::EVO_COL);
}

/************************************************************************
* Method PrintThreeEvos: Class PokemonEvolutions
*----------------------------------------------------------------------
* 	 This prints a three evolution family tree
* 	 ==> returns nothing
*-----------------------------------------------------------------------
* PRE-CONDITIONS
* 	The following need to be passed in
* 		fout (ostream) - the output variable
*
* POST-CONDITIONS
* 	==> returns nothing
*************************************************************************/
void PokemonEvolutions::PrintThreeEvos(std::ostream& fout) const
{
	std::ostringstream evoTree; //PROC & OUT - The evolution tree

	evoTree << firstEvo.GetName() << " evolves by ";

	//If the first evolution evolves through leveling and condition
	//or just condition
	if((firstEvo.GetEvoThroughLvl()  == true  &&
		firstEvo.GetEvoThroughCond() == true) ||
	   (firstEvo.GetEvoThroughLvl()  == false  &&
		firstEvo.GetEvoThroughCond() == true))
	{
		evoTree << firstEvo.GetSecondEvoCond();
	}
	//If the first evolution evolves through leveling and not condition
	else if(firstEvo.GetEvoThroughLvl()  == true &&
			firstEvo.GetEvoThroughCond() == false)
	{
		evoTree << "leveling up to level " << firstEvo.GetEvoLvl();
	}
	else
	{
		evoTree << "\nERROR\n";
	}

	evoTree << " into " << secondEvo.GetName() << "\nthen by ";

	//If the second evolution evolves through leveling and condition
	//or just condition
	if((secondEvo.GetEvoThroughLvl()  == true  &&
		secondEvo.GetEvoThroughCond() == true) ||
	   (secondEvo.GetEvoThroughLvl()  == false  &&
		secondEvo.GetEvoThroughCond() == true))
	{
		evoTree << secondEvo.GetFinalEvoCond();
	}
	//If the second evolution evolves through leveling and not condition
	else if(secondEvo.GetEvoThroughLvl()  == true &&
			secondEvo.GetEvoThroughCond() == false)
	{
		evoTree << "leveling up to level " << secondEvo.GetEvoLvl();
	}
	else
	{
		evoTree << "\nERROR\n";
	}

	evoTree << " into " << finalEvo.GetName() << ".";

	//If the Pokemon has a branch evolution, then print their information
	if(mainPokemon.GetBranchEvo() == true)
	{
		evoTree << " A branch evolution is available by evolving "
			 << secondEvo.GetName() << " by ";

		if((branchEvo.GetEvoThroughLvl() == true    &&
			branchEvo.GetEvoThroughCond() == true)   ||
		   (branchEvo.GetEvoThroughLvl()  == false   &&
		    branchEvo.GetEvoThroughCond() == true))
		{
			evoTree << branchEvo.GetFinalEvoCond();
		}
		else if(branchEvo.GetEvoThroughLvl()  == true &&
				branchEvo.GetEvoThroughCond() == false)
		{
			evoTree << "leveling up to level "
				 << branchEvo.GetFinalEvoLvl();;
		}
		else
		{
			evoTree << "\nERROR\n";
		}

		evoTree << " into " << branchEvo.GetName() << ".";
	}

	//OUTPUT - Print the evolution tree in paragraph formation
	fout << globalPkmnConsts::WordWrap(evoTree.str(),
									   globalPkmEvoConsts::EVO_COL);
}

/************************************************************************
* Method PrintBranchEvos: Class PokemonEvolutions
*----------------------------------------------------------------------
* 	 This prints a branch evolution family tree
* 	 ==> returns nothing
*-----------------------------------------------------------------------
* PRE-CONDITIONS
* 	The following need to be passed in
* 		fout (ostream) - the output variable
*
* POST-CONDITIONS
* 	==> returns nothing
*************************************************************************/
void PokemonEvolutions::PrintBranchEvos(std::ostream& fout) const
{
	unsigned int index;				//PROC - The index in the array

	bool specialBranchs;	        //PROC - The condition if the Pokemon is
									//       a special branch with more
									//       evolutions than normal(>2)

	//PROCESSING - Initialize the values
	index = 0;
	specialBranchs = false;

	//PROCESSING - Store the value of the size of the vector
	auto vsize = globalPkmEvoConsts::SPECIAL_BRANCHE_EVOS.size();

	//PROCESSING - Loop through to find if the specificed pokemon has a unique
	//			   branch evolutions
	while(index < vsize && !specialBranchs)
	{
		//If the Pokemon is a special branch evolution, then print their
		//specific information
		if(mainPokemon.GetPokedexNumber() ==
				globalPkmEvoConsts::SPECIAL_BRANCHE_EVOS[index])
		{
			PrintSpecialEvosBranch(fout);
			specialBranchs = true;
		}
		index++;
	}

	//PROCESSING - If the pokemon is not a special branch evo, then print the
	//			   evo branch for that pokemon
	if(specialBranchs == false)
	{
		//PROCESSING - Pokemon with only 2 normal evolutions and 1 branch evo
		if(mainPokemon.GetEvolutions() == 1)
		{
			PrintTwoEvos(fout);
		}
		//PROCESSING - Pokemon with only 3 normal evolutions and 1 branch evo
		else
		{
			PrintThreeEvos(fout);
		}
	}
}

/************************************************************************
* Method PrintBranchEvos: Class PokemonEvolutions
*----------------------------------------------------------------------
* 	 This prints the special branch evolution family tree
* 	 ==> returns nothing
*-----------------------------------------------------------------------
* PRE-CONDITIONS
* 	The following need to be passed in
* 		fout (ostream) - the output variable
*
* POST-CONDITIONS
* 	==> returns nothing
*************************************************************************/
void PokemonEvolutions::PrintSpecialEvosBranch(std::ostream& fout) const
{
	using namespace globalPkmEvoConsts; //The vectors of the special
									    //Pokemon pokedex numbers

	int wurmpleEvoIndex;	//PROC - The index in the Wurmple Vector
	int tyroEvoIndex;		//PROC - The index in the Tyrogue Vector
	int eeveeEvoIndex;		//PROC - The index in the Eevee Vector

	bool continueChecking;	//PROC - The condition to keep checking
	bool wurmpleFamily;		//PROC - The index in the Eevee Vector
	bool tyrogueFamily;		//PROC - The index in the Eevee Vector
	bool eeveeFamily;		//PROC - The index in the Eevee Vector
	bool firstRun;			//PROC - The index in the Eevee Vector

	//PROCESSING - Initialize the values
	continueChecking = true;
	wurmpleFamily    = false;
	tyrogueFamily    = false;
	eeveeFamily      = false;
	firstRun         = true;

	//PROCESSING - Check if the pokemon is part of the Wurmple family
	for(auto wurmpleIt: WURPLE_EVOLUTIONS)
	{
		if(continueChecking == true)
		{
			if(mainPokemon.GetPokedexNumber() == (int(wurmpleIt)))
			{
				wurmpleFamily    = true;
				continueChecking = false;
			}
		}
	}

	if(continueChecking == true)
	{
		//PROCESSING - Check if the pokemon is part of the Tyrogue family
		for(auto tyrogueIt: TYROGUE_EVOLUTIONS)
		{
			if(continueChecking == true)
			{
				if(mainPokemon.GetPokedexNumber() == (int(tyrogueIt)))
				{
					tyrogueFamily    = true;
					continueChecking = false;
				}
			}
		}
	}

	if(continueChecking == true)
	{
		//PROCESSING - Check if the pokemon is part of the Eevee family
		for(auto eeveeIt: EEVEELUTIONS)
		{
			if(continueChecking == true)
			{
				if(mainPokemon.GetPokedexNumber() == (int(eeveeIt)))
				{
					eeveeFamily      = true;
					continueChecking = false;
				}
			}
		}
	}

	//OUTPUT - Print the information in the Wurmple family
	if(wurmpleFamily == true)
	{
		//Check the wurmple evolutions
		for(auto it: WURPLE_EVOLUTIONS)
		{
			if(firstRun == true && (mainPokemon.GetPokedexNumber() !=
			   WURPLE_EVOLUTIONS[0]))
			{
				fout << "Wurmple - first evolution\n\n";
				firstRun = false;
			}

			wurmpleEvoIndex = (int(it) - 1);

			if(pokedexCopy[wurmpleEvoIndex].GetSecondEvo() == true)
			{
				fout << pokedexCopy[wurmpleEvoIndex].GetName() << " by "
					 << pokedexCopy[wurmpleEvoIndex].GetSecondEvoCond()
					 << " then leveling up to "
					 << pokedexCopy[wurmpleEvoIndex].GetEvoLvl() << " into "
					 << pokedexCopy[wurmpleEvoIndex + 1].GetName() << ".\n\n";
			}
		}
	}
	//OUTPUT - Print the information in the Tyrogue family
	else if(tyrogueFamily == true)
	{
		for(auto it: TYROGUE_EVOLUTIONS)
		{
			//If the pokemon is not the first evolution in the family
			if(firstRun == true && (mainPokemon.GetPokedexNumber() !=
			   TYROGUE_EVOLUTIONS[0]))
			{
				fout << "Tyrogue - first evolution\n\n";
				firstRun = false;
			}

			tyroEvoIndex = (int(it) - 1);

			//If the Pokemon is not Tyrogue, then output how to obtain it
			if(tyroEvoIndex != (TYROGUE_EVOLUTIONS[0] - 1))
			{
				fout << pokedexCopy[tyroEvoIndex].GetName() << " obtained by ";

				if((pokedexCopy[tyroEvoIndex].GetEvoThroughCond() == true  &&
					pokedexCopy[tyroEvoIndex].GetEvoThroughLvl()  == true) ||
				   (pokedexCopy[tyroEvoIndex].GetEvoThroughCond() == true  &&
				    pokedexCopy[tyroEvoIndex].GetEvoThroughLvl()  == false))
				{
					fout << pokedexCopy[tyroEvoIndex].GetFinalEvoCond()
						 << ".\n\n";
				}
				else if(pokedexCopy[tyroEvoIndex].GetEvoThroughCond() == false
						&&
						pokedexCopy[tyroEvoIndex].GetEvoThroughLvl()  == true)
				{
					fout << " leveling up to "
						 << pokedexCopy[tyroEvoIndex].GetEvoLvl() << ".\n\n";
				}
			}
		}
	}
	//OUTPUT - Print the information in the Eevee family
	else if(eeveeFamily == true)
	{
		for(auto it: EEVEELUTIONS)
		{
			//If the pokemon is not the first evolution in the family
			if(firstRun == true && (mainPokemon.GetPokedexNumber() !=
			   EEVEELUTIONS[0]))
			{
				fout << "Eevee - first evolution\n\n";
				firstRun = false;
			}

			eeveeEvoIndex = (int(it) - 1);

			//If the Pokemon is not Eevee, then output how to obtain it
			if(eeveeEvoIndex != (EEVEELUTIONS[0] - 1))
			{
				fout << pokedexCopy[eeveeEvoIndex].GetName() << " obtained by ";

				if((pokedexCopy[eeveeEvoIndex].GetEvoThroughCond() == true  &&
					pokedexCopy[eeveeEvoIndex].GetEvoThroughLvl()  == true) ||
				   (pokedexCopy[eeveeEvoIndex].GetEvoThroughCond() == true  &&
				    pokedexCopy[eeveeEvoIndex].GetEvoThroughLvl()  == false))
				{
					fout << pokedexCopy[eeveeEvoIndex].GetFinalEvoCond()
						 << ".\n\n";
				}
				else if(pokedexCopy[eeveeEvoIndex].GetEvoThroughCond() == false
						&&
						pokedexCopy[eeveeEvoIndex].GetEvoThroughLvl()  == true)
				{
					fout << " leveling up to "
						 << pokedexCopy[eeveeEvoIndex].GetEvoLvl() << ".\n\n";
				}
			}
		}
	}
}
