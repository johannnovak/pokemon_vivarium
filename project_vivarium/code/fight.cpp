/* file : fight.cpp   
*	This file implements the methods defined in the fight.cpp file.
*	johann.novak25@gmail.com
*	15/03/14
*/
#include <fight.hpp>

using namespace std;

/* Constructors   */
Fight::Fight(){}						/*	Default constructor	*/
Fight::Fight(Fight const& fight)	/*	Copy Constructor	*/
{
   _pok1 = fight._pok1;
   _pok2 = fight._pok2;
   _characs1 = fight._characs1;
   _characs2 = fight._characs2;
   _pokObs = fight._pokObs;
}

/* Constructor that is always used to instanciate the fight between two pokemons	*/
Fight::Fight(shared_ptr<Pokemon> pok1, shared_ptr<Pokemon> pok2)
{
   _pok1 = pok1;
   _characs1.push_back(pok1->getAttack());
   _characs1.push_back(pok1->getDefense());
   _characs1.push_back(pok1->getSpeed());
   _characs1.push_back(pok1->getSpeAttack());
   _characs1.push_back(pok1->getSpeDefense());
   
   _pok2 = pok2;
   _characs2.push_back(pok2->getAttack());
   _characs2.push_back(pok2->getDefense());
   _characs2.push_back(pok2->getSpeed());
   _characs2.push_back(pok2->getSpeAttack());
   _characs2.push_back(pok2->getSpeDefense());

	_hasBegun = false;
	_hasEnded = false;
}

/*	Destructor	*/
Fight::~Fight()
{
	_pokObs.reset();
	_pok1.reset();
   _characs1.clear();
	_pok2.reset();
   _characs2.clear();
}
/*	Getters and Setters	*/
bool Fight::hasEnded()
{
	return _hasEnded;
}
bool Fight::hasBegun()
{
	return _hasBegun;
}

/* Operators   */
/*	= operator	*/
Fight& Fight::operator=(Fight const& fight)
{
   _pok1 = fight._pok1;
	_characs1 = fight._characs1;
   _pok2 = fight._pok2;
	_characs2 = fight._characs2;
	_pokObs = fight._pokObs;

   return *this;
}

/*	startFight method
*	This method is used to assign true to hasBegun and print that a new fightt has begun.
*	no parameters
*	no return statement
*/
void Fight::startFight()

{
   cout << endl << "=============/!\\ NEW FIGHT /!\\ ============" << endl;
   cout << "Wild " << _pok1->getName()  << " lvl" << _pok1->getLvl() << " encounters a wild " << _pok2->getName() << " lvl" << _pok2->getLvl() << " !" << endl << endl;
	_hasBegun = true;
/*   cout << "Press ENTER to continue...";
   cin.ignore(numeric_limits<streamsize>::max(), '\n' );
   cout << string(50,'\n');*/
}

/*	startTurn method
*	This method consist in one turn in a pokemon battle : a pokemon attacks, the other pokemon attacks
*	no parameters
*	no return statement
*/
void Fight::startTurn()
{
   shared_ptr<Attack> a1(choiceOfAttack(*_pok1));
   shared_ptr<Attack> a2(choiceOfAttack(*_pok2));
	if(_pok1->getSpeed() < _pok2->getSpeed())
   {
   	_pok1.swap(_pok2);
      _characs1.swap(_characs2);
	}

   attack(_pok1,*a1, _pok2);
   if(_pok2->getCurrentHP() > 0)
      attack(_pok2,*a2, _pok1);

   cout << _pok1->getName() << " " << _pok1->getCurrentHP() << "/" << _pok1->getHP();
   cout << "\t" << _pok2->getName() << " " << _pok2->getCurrentHP() << "/" << _pok2->getHP() << endl;
   a1.reset();
   a2.reset();
	if(_pok1->getCurrentHP() == 0 || _pok2->getCurrentHP() == 0)
	{
		_hasEnded = true;
		if(_pok2->getCurrentHP() > 0)
		{
			_pok2.swap(_pok1);
			_characs2.swap(_characs1);
		}
	}
}

/*	choiceOfAttack method
*	IA for the  choice of the attack of the pokemon.
*	parameter
*		Pokemon pok : the pokemon that will perform an attack
*	return
*		a pointer on Attack, chosen by the IA
*/
shared_ptr<Attack> Fight::choiceOfAttack(Pokemon pok)
{
   vector<shared_ptr<Attack>> attacks(pok.getMenuAttacks());
   shared_ptr<Attack> a = attacks[0];
   if(pok.getCurrentHP() < 50)
   {
      for(short i = 0; i < attacks.size(); ++i)
         if(attacks[i])
            if(a->getPower() < attacks[i]->getPower())
               a = attacks[i];
      return a;
   }
   else
   {
      for(short i = 0; i < attacks.size(); ++i)
         if(attacks[i])
            if(a->getPower() < attacks[i]->getPower())
               a = attacks[i];
      return a;
   }
}

/*	attack method
*	Perform the attack attack to a pokemon *pok2 by a pokemon *pok1.
*	parameters
*		shared_ptr<Pokemon> pok1 : pointer on the pokemon that perform the attack.
*		Attack attack : attack performed.
*		shared_ptr<Pokemon> pok2 : pointer on the pokemon that undergoes the attack.
*	no return statement
*/
void Fight::attack(shared_ptr<Pokemon> pok1, Attack attack, shared_ptr<Pokemon> pok2)
{
   cout << pok1->getName() << " attacks " << pok2->getName() << " with " << attack.getName() << endl;
   short TYPEBONUS = 1;
   if(attack.getType() == pok1->getType1() || attack.getType() == pok1->getType2())
      TYPEBONUS = 1.5;
   short EFFICIENCY = pok2->resistanceTo(attack.getType());
   short damage = (((((2*(pok1->getLvl()/5)+2))*(pok1->getAttack())*attack.getPower()/(pok2->getDefense()))/50)+2)*TYPEBONUS*EFFICIENCY*((rand()%16)+85)/100;
   pok2->setCurrentHP(pok2->getCurrentHP()- damage);
   if(pok2->getCurrentHP() < 0)
      pok2->setCurrentHP(0);
   cout << pok2->getName() << " lost " << damage << " HP" << endl;
   if(EFFICIENCY == 0.25)
      cout << "It is really not effective ..." << endl;
   else if(EFFICIENCY == 0.5)
         cout << "It is not effective ..." << endl;
   else if(EFFICIENCY == 2)
         cout << "It is effective !" << endl;
   else if(EFFICIENCY == 4)
         cout << "It is really effective !" << endl;
	this_thread::sleep_for(chrono::milliseconds(50));
}

/*	finishFight method
*	Finishes fight, by printing the winner, tell the pokemon observer to remove the defeated pokemon, give xp to the winner and handle the evolution	
*	no parameters	
*	no return statement
*/
void Fight::finishFight()
{
   long xp;
   /* end of fight   */
   cout << "------------------------------" << endl;
   cout << "\tThe fight is over " << endl;
   cout << "> The winner is ";

   cout << _pok1->getName() << " !" << endl;
   xp = giveXP(_pok1->getLvl(), _pok1->getXPCategory());
   cout << ">> " << _pok1->getName() << " receives " << xp << " XP !" << endl;
   _pok1->setAttack(_characs1[0]);
   _pok1->setDefense(_characs1[1]);
   _pok1->setSpeed(_characs1[2]);
   _pok1->setSpeAttack(_characs1[3]);
   _pok1->setSpeDefense(_characs1[4]);
   if(_pok1->getLvl() != 100)
   {
      _pok1->setXP(_pok1->getXP()+xp);
      _pok1->winEVS(_pok2->getEVSToGive());
      if(_pok1->getXP() >= *_pok1->getXPLimit())
      {
			_pok1->lvlUP();
			if(_pok1->getLvl() == get<0>(_pok1->getEvolution()))
				addEvolvePokemonToSceneManager(_pok1);
		}
   }
	_pok1->setFighting(false);
	_pok2->setRemoved(true);
}

/* giveXP method
*	Calculates and gives xp to the winner of the battle.
*	parameters
*		short lvl : level of the pokemon that won.
*		string cat : the xp category of the pokemon that won.
*	return
*		the xp the pokemon got from winning the battle.
*/

long Fight::giveXP(short lvl, string cat)
{
   long xp;
   if(cat.compare("fast") == 0)
      xp = calculateXPFast(lvl);
   else if(cat.compare("medium fast") == 0)
      xp = calculateXPMediumFast(lvl);
   else if(cat.compare("medium slow") == 0)
      xp = calculateXPMediumSlow(lvl);
   else if(cat.compare("slow") == 0)
      xp = calculateXPSlow(lvl);
   
   xp = (1 * 1 * xp * 1 * _pok2->getLvl())/(7 * 1);

   return xp;
}

/*	calculateXP***	methods
*	Give back the corresponding xp according to the level of the pokemon, each method correspon ds to a certain xp category.
*	parameters
*		short lvl : level of the pokemon that won.
*	return
*		the corresponding xp to the level and the category.
*/
long Fight::calculateXPFast(short lvl)
{
   return (4*lvl*lvl*lvl/5);
}
long Fight::calculateXPMediumFast(short lvl)
{
   return (lvl*lvl*lvl);
}
long Fight::calculateXPMediumSlow(short lvl)
{
   if(lvl == 1)
      return 4;
   return ((6*lvl*lvl*lvl/5)-(15*lvl*lvl)+(100*lvl)-140);
}
long Fight::calculateXPSlow(short lvl)
{
   return (5*lvl*lvl*lvl/4);
}

/* Observable functions */

/*	addPokemonobserver method
*	Add a pokemon observer to the list of pokemon observers, here it is a not a list but just an assignment.
*	parameters
*		shared_ptr<PokemonObserver> obs : pointer of PokemonObserver that is assigned to _pokObs.
*	no return statement
*/
void Fight::addPokemonObserver(std::shared_ptr<PokemonObserver> obs)
{
   _pokObs = obs; 
}

/*	removePokemonObserver method
*	Assigns to null the pokemon observer passed in parameter.
*	parameters
*		shared_ptr<PokemonObserver> obs : pokemon observer to be removed.
*	no return statement
*/
void Fight::removePokemonObserver(std::shared_ptr<PokemonObserver> obs)
{
   _pokObs.reset();
}

/*	addEvolveToSceneManager
*	Adds in the sceneManager, in the list of pokemon that request evolution, a pokemon that is evolving.
*	parameters
*		shared_ptr<Pokemon> pok : pokemon that is going to evolve.
*	no return statement
*/
void Fight::addEvolvePokemonToSceneManager(shared_ptr<Pokemon> pok)
{
   _pokObs->addPokemonToEvolve(pok);
}

/*
bool FightManager::runAway(Pokemon pok1, Pokemon pok2)
{
   short temp;
   temp = rand()%100;
   if(*pok1.getSpeed() > *pok2.getSpeed())
   {
      if(temp > 97)
         return false;
      else
         return true;
   }
   else
   {
      if(temp > 20)
         return false;
      else
         return true;
   }
}*/


