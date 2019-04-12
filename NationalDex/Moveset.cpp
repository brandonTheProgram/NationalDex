#include "Moveset.h"

/************************************************************************
* Method Moveset: Class Moveset
*----------------------------------------------------------------------
* 	 This method creates the Moveset object
* 	 ==> returns nothing
*-----------------------------------------------------------------------
* PRE-CONDITIONS
* 	The following need to be passed in
*
* POST-CONDITIONS
* 	==> returns nothing
*************************************************************************/
Moveset::Moveset()
{
	lvlMoveset.clear();
	TMMoveset.clear();
}

/************************************************************************
* Method Moveset: Class Moveset
*----------------------------------------------------------------------
* 	 This method creates the Moveset object with values
* 	 ==> returns nothing
*-----------------------------------------------------------------------
* PRE-CONDITIONS
* 	The following need to be passed in
*   	attackDex (vector<Attack>) - the attackdex
*   	moves     (vector<string>) - the moves the Pokemon learns
*   	lvls      (vector<int>)    - the levels when the Pokemon learns the move
* POST-CONDITIONS
* 	==> returns nothing
*************************************************************************/
Moveset::Moveset(const vector<Attack>& attackDex,
				 const vector<string>& moves,
				 const vector<int>   & lvls)
{
	int index;		//PROC - The index in the array
	int levelIndex;	//PROC - The index in the level array

	bool found;		//PROC - The condition if the move was found

	LvlAttack newAttack; //PROC - The attack with a level

	auto size = attackDex.size(); //PROC - The size of the attackdex

	found      = false;
	index      = 0;
	levelIndex = 0;

	//PROCESSING - for every move that the Pokemon has, find it in the
	//			   attackdex and store it as a TM move or a level move
	for(auto moveIt: moves)
	{
		while(!found && (index != signed(size)))
		{
			if(!(attackDex[index].name.compare(moveIt)))
			{
				//If the move found is a TM, store it
				if((attackDex[index].TM == 1) && (lvls[levelIndex] == 0))
					TMMoveset.push_back(attackDex[index]);
				//If the move is a level move, then store the level and attack
				else
				{
					newAttack.attack = attackDex[index];
					newAttack.lvl = lvls[levelIndex];
					lvlMoveset.push_back(newAttack);
					levelIndex++;
				}

				found = true;
			}
			else
				++index;
		}

		//If a move was not found in the list, output what attack could not be
		//found so that the user can fix it
		if(found == false || index == signed(size))
			std::cout << "ERROR! : " << moveIt << std::endl;

		index = 0;
		found = false;
	}
}

/************************************************************************
* Method ~Moveset: Class Moveset
*----------------------------------------------------------------------
* 	 This method deletes the Moveset object
* 	 ==> returns nothing
*-----------------------------------------------------------------------
* PRE-CONDITIONS
* 	The following need to be passed in
*
* POST-CONDITIONS
* 	==> returns nothing
*************************************************************************/
Moveset::~Moveset()
{
	lvlMoveset.clear();
	TMMoveset.clear();

	vector<LvlAttack>().swap(lvlMoveset);
	vector<Attack>().swap(TMMoveset);
}

/************************************************************************
* Method InitializeMoveSets: Class Moveset
*----------------------------------------------------------------------
* 	 This method initializes the Moveset object with values
* 	 ==> returns nothing
*-----------------------------------------------------------------------
* PRE-CONDITIONS
* 	The following need to be passed in
*   	attackDex (vector<Attack>) - the attackdex
*   	moves     (vector<string>) - the moves the Pokemon learns
*   	lvls      (vector<int>)    - the levels when the Pokemon learns the move
* POST-CONDITIONS
* 	==> returns nothing
*************************************************************************/
void Moveset::InitializeMoveSets(const vector<Attack>& attackDex,
								 const vector<string>& moves,
								 const vector<int>   & lvls)
{
	int index;		//PROC - The index in the array
	int levelIndex;	//PROC - The index in the level array

	bool found;		//PROC - The condition if the move was found

	LvlAttack newAttack; //PROC - The attack with a level

	auto size = attackDex.size(); //PROC - The size of the attackdex

	found      = false;
	index      = 0;
	levelIndex = 0;

	//PROCESSING - for every move that the Pokemon has, find it in the
	//			   attackdex and store it as a TM move or a level move
	for(auto moveIt: moves)
	{
		while(!found && (index != signed(size)))
		{
			if(!(attackDex[index].name.compare(moveIt)))
			{
				//If the move found is a TM, store it
				if((attackDex[index].TM == 1) && (lvls[levelIndex] == 0))
					TMMoveset.push_back(attackDex[index]);
				//If the move is a level move, then store the level and attack
				else
				{
					newAttack.attack = attackDex[index];
					newAttack.lvl = lvls[levelIndex];
					lvlMoveset.push_back(newAttack);
					levelIndex++;
				}

				found = true;
			}
			else
				++index;
		}

		//If a move was not found in the list, output what attack could not be
		//found so that the user can fix it
		if(found == false || index == signed(size))
			std::cout << "ERROR! : " << moveIt << std::endl;

		index = 0;
		found = false;
	}
}

/************************************************************************
* Method PrintTM: Class Moveset
*----------------------------------------------------------------------
* 	 This method prints the Pokemon's TM moveset
* 	 ==> returns nothing
*-----------------------------------------------------------------------
* PRE-CONDITIONS
* 	The following need to be passed in
*   	out (ostream) - the output variable
* POST-CONDITIONS
* 	==> returns nothing
*************************************************************************/
void Moveset::PrintTM(std::ostream& out) const
{
	using namespace movesetGlobalConsts; //Using the column constants
	using std::setw; 					 //Used for output column sizes

	string tm;	//PROC - the number of the TM

	//If the Pokemon knows TM moves, then output them
	if(!TMMoveset.empty())
	{
		out << "TM Attacks\n";

		out << std::left;

		out << setw(LVL_COL)    << "TM #"        << " "
			<< setw(NAME_COL)   << "Attack Name"  << " "
			<< setw(TYPE_COL)   << "Type"		  << " "
			<< setw(CAT_COL)    << "Cat."		  << " "
			<< setw(ATK_COL)    << "Att."		  << " "
			<< setw(ACC_COL)    << "Acc."		  << " "
			<< setw(PP_COL)     << "PP"			  << " "
			<< setw(EFFECT_COL) << "Effect %";

		out << std::endl << std::setfill('-')
		    << setw(LINE_COL) << "-" << std::endl;

		out << std::setfill(' ');

		for(auto it: TMMoveset)
		{
			//Punctuate the TM number
			if(it.TMNum < 10)
				tm = ("TM0" + std::to_string(it.TMNum));
			else
				tm = ("TM" + std::to_string(it.TMNum));

			out << setw(LVL_COL)    <<  tm			<< " "
			    << setw(NAME_COL)   << it.name		<< " "
				<< setw(TYPE_COL)   << it.type		<< " "
				<< setw(CAT_COL)    << it.category	<< " "
				<< setw(ATK_COL)    << it.pwr		<< " "
				<< setw(ACC_COL)    << it.acc		<< " "
				<< setw(PP_COL)     << it.pp		<< " "
				<< setw(EFFECT_COL) << it.effRate	<< " " << std::endl;

			out << setw(DES_COL) << " " << it.desc
				<< std::endl << std::endl;
		}

		out << std::endl;
	}
}

/************************************************************************
* Method PrintLvl: Class Moveset
*----------------------------------------------------------------------
* 	 This method prints the Pokemon's lvl moveset
* 	 ==> returns nothing
*-----------------------------------------------------------------------
* PRE-CONDITIONS
* 	The following need to be passed in
*   	out (ostream) - the output variable
* POST-CONDITIONS
* 	==> returns nothing
*************************************************************************/
void Moveset::PrintLvl(std::ostream& out) const
{
	using namespace movesetGlobalConsts; //Using the column constants
	using std::setw; 					 //Used for output column sizes

	//If the Pokemon knows moves by leveling up, then output them
	if(!lvlMoveset.empty())
	{
		out << std::endl << std::endl << GENERATION << " Level Up\n\n";

		out << std::left;

		out << setw(LVL_COL)    << "Level"        << " "
			<< setw(NAME_COL)   << "Attack Name"  << " "
			<< setw(TYPE_COL)   << "Type"		  << " "
			<< setw(CAT_COL)    << "Cat."		  << " "
			<< setw(ATK_COL)    << "Att."		  << " "
			<< setw(ACC_COL)    << "Acc."		  << " "
			<< setw(PP_COL)     << "PP"			  << " "
			<< setw(EFFECT_COL) << "Effect %";

		out << std::endl << std::setfill('-')
		    << setw(LINE_COL) << "-" << std::endl;

		out << std::setfill(' ');

		for(auto it: lvlMoveset)
		{

			out << setw(LVL_COL)    << it.lvl             << " "
				<< setw(NAME_COL)   << it.attack.name	  << " "
				<< setw(TYPE_COL)   << it.attack.type	  << " "
				<< setw(CAT_COL)    << it.attack.category << " "
				<< setw(ATK_COL)    << it.attack.pwr	  << " "
				<< setw(ACC_COL)    << it.attack.acc	  << " "
				<< setw(PP_COL)     << it.attack.pp		  << " "
				<< setw(EFFECT_COL) << it.attack.effRate  << std::endl;

			out << setw(DES_COL) << " " << it.attack.desc
				<< std::endl << std::endl;
		}

		out << std::endl;
	}
}
