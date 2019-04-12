#include "Pokemon.h"

/************************************************************************
* Method Pokemon: Class Pokemon
*----------------------------------------------------------------------
* 	 This method creates the Pokemon object
* 	 ==> returns nothing
*-----------------------------------------------------------------------
* PRE-CONDITIONS
* 	The following need to be passed in
*
* POST-CONDITIONS
* 	==> returns nothing
*************************************************************************/
Pokemon::Pokemon()
{
	basic.pokedexNumber 				    = 0;
	basic.name								.clear();
	basic.species							.clear();
	basic.priType							.clear();
	basic.secType							.clear();
	basic.description						.clear();
	basic.abilites 							= 0;
	basic.ability							.clear();
	basic.abilityDesc						.clear();
	basic.altAbility						.clear();
	basic.altAbilityDesc					.clear();
	basic.hiddenAbility						.clear();
	basic.hiddenAbilityDesc					.clear();
	evol.evolutions 						= 0;
	evol.secondEvo							= false;
	evol.finalEvo							= false;
	evol.branchEvo							= false;
	evol.evoThroughLvl 						= false;
	evol.evoThroughCond 					= false;
	evol.evoLvl 							= 0;
	evol.finalEvoLvl 						= 0;
	evol.firstEvoNum 						= 0;
	evol.secondEvoNum 						= 0;
	evol.finalEvoNum 						= 0;
	evol.branchEvoNum 						= 0;
	evol.secondEvoCond						.clear();
	evol.finalEvoCond						.clear();
}

/************************************************************************
* Method ~Pokemon: Class Pokemon
*----------------------------------------------------------------------
* 	 This method deletes the Pokemon object
* 	 ==> returns nothing
*-----------------------------------------------------------------------
* PRE-CONDITIONS
* 	The following need to be passed in
*
* POST-CONDITIONS
* 	==> returns nothing
*************************************************************************/
Pokemon::~Pokemon()
{

}

/************************************************************************
* Method PrintAbility: Class Pokemon
*----------------------------------------------------------------------
* 	 This method prints the abilities of the Pokemon
* 	 ==> returns nothing
*-----------------------------------------------------------------------
* PRE-CONDITIONS
* 	The following need to be passed in
* 		fout (ostream) - the output variable
*
* POST-CONDITIONS
* 	==> returns nothing
*************************************************************************/
void Pokemon::PrintAbility(std::ostream &fout) const
{
	using namespace globalPkmnConsts;

	//PROCESSING - Based on how many abilities the pokemon has, print their info
	switch(basic.abilites)
	{
	case 1: fout << "Ability: " << basic.ability << endl << endl;

			fout << basic.ability << ": "
				 << WordWrap(basic.abilityDesc, ABILITY_COL) << endl;
			break;

	case 2: fout << "Abilities: " << basic.ability << " - "
				 << basic.hiddenAbility << " (Hidden Ability)" << endl << endl;

			fout << basic.ability << ": "
				 << WordWrap(basic.abilityDesc, ABILITY_COL);

			fout << "\n\nHidden Ability\n\n";

			fout << basic.hiddenAbility << ": "
				 << WordWrap(basic.hiddenAbilityDesc, ABILITY_COL) << endl;
			break;

	case 3:	fout << "Abilities: "       << basic.ability << " - "
				 << basic.altAbility    << " - "         << basic.hiddenAbility
				 << " (Hidden Ability)" << endl          << endl;

			fout << basic.ability << ": " << WordWrap(basic.abilityDesc,
													  ABILITY_COL)
				 << endl << endl;

			fout << basic.altAbility << ": " << WordWrap(basic.altAbilityDesc,
														 ABILITY_COL);

			fout << "\n\nHidden Ability\n\n";

			fout << basic.hiddenAbility                            << ": "
				 << WordWrap(basic.hiddenAbilityDesc, ABILITY_COL) << endl;
	}
}

//Overloading the extraction operator to get input from the file
std::ifstream& operator >>(std::ifstream& isObject, Pokemon& cObject)
{
	isObject >> cObject.basic.pokedexNumber;

	isObject.ignore(10000, '\n');

	getline(isObject, cObject.basic.name);

	getline(isObject, cObject.basic.species);

	getline(isObject, cObject.basic.priType);

	getline(isObject, cObject.basic.secType);

	getline(isObject, cObject.basic.description);

	getline(isObject, cObject.basic.ability);

	getline(isObject, cObject.basic.abilityDesc);

	getline(isObject, cObject.basic.hiddenAbility);

	getline(isObject, cObject.basic.hiddenAbilityDesc);

	isObject >> cObject.basic.abilites;

	isObject.ignore(1000, '\n');

	getline(isObject, cObject.basic.altAbility);

	getline(isObject, cObject.basic.altAbilityDesc);

	isObject >> cObject.evol.evolutions;

	isObject >> cObject.evol.secondEvo;

	isObject >> cObject.evol.evoThroughLvl;

	isObject >> cObject.evol.evoThroughCond;

	isObject >> cObject.evol.evoLvl;

	isObject >> cObject.evol.firstEvoNum;

	isObject.ignore(1000, '\n');

	getline(isObject, cObject.evol.secondEvoCond);

	isObject >> cObject.evol.secondEvoNum;

	isObject >> cObject.evol.finalEvo;

	isObject >> cObject.evol.finalEvoLvl;

	isObject.ignore(1000, '\n');

	getline(isObject, cObject.evol.finalEvoCond);

	isObject >> cObject.evol.finalEvoNum;

	isObject >> cObject.evol.branchEvo;

	isObject >> cObject.evol.branchEvoNum;

	isObject.ignore(1000, '\n');

	return isObject;
}

//Overloading the insertion operator to output the Pokemon's information
std::ostream& operator <<(std::ostream& osObject, const Pokemon& cObject)
{
	osObject << "*************************************"
			 << "**************************\n";

	osObject << cObject.basic.name << " #" << std::setw(3)
		     << cObject.basic.pokedexNumber;

	osObject << endl << endl;

	osObject << "Species: " << cObject.basic.species << "\nType(s): ";

	//OUTPUT - If the pokemon has two different types, display both of them
	if(cObject.basic.priType.compare(cObject.basic.secType))
	{
		osObject << cObject.basic.priType << " and "
			     << cObject.basic.secType << endl << endl;
	}
	else
	{
		osObject << cObject.basic.priType << endl << endl;
	}

	//OUTPUT - Print the pokemon's description in neat paragraph formation
	osObject << globalPkmnConsts::WordWrap(cObject.basic.description,
			                       globalPkmnConsts::DESC_COL)
			 << endl << endl;

	osObject << "**********************************"
			    "*****************************\n";

	//OUTPUT - Display the Pokemon's abilities
	cObject.PrintAbility(osObject);

	osObject << "********************************************"
			    "*******************\n";

	return osObject;
}
