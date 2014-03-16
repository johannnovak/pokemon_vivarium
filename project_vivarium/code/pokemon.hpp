/* file : pokemon.hpp 
 *	This file is the header file of the pokemon.cpp file.
 *	This cless defines what a pokemon is. It will inherit the class Rect<float> to be able to check the collisions easily.
 *	johann.novak25@gmail.com
 *	16/03/14
*/

#ifndef POKEMON_HPP
#define POKEMON_HPP

#include <limits>
#include <iostream>
#include <cstdlib>
#include <string>
#include <memory>
#include <time.h>
#include <string.h>
#include <math.h>
#include <map>
#include <tuple>
#include <vector>

#include <type.hpp>
#include <attack.hpp>
#include <evolutionObservable.hpp>
#include <xpObservable.hpp>
#include <SFML/Graphics.hpp>

/*	enumeration used to tell the direction of a pokemon	*/
enum class DIRECTION
{
   UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3
};

class Pokemon : public EvolutionObservable, public XPObservable, public sf::Rect<float>
{
   protected :
      /* Attributes  */
      std::shared_ptr<short> _number;		/*	number of the pokemon	*/
      std::string _name;						/*	name of the pokemon	*/
      short _lvl;									/*	level of the pokemon	*/
      long _xp;									/*	current xp of the pokemon	*/
      std::shared_ptr<long> _xpLimit;		/*	amount of xp the pokemon has to gain to level up	*/
      std::shared_ptr<std::string> _xpCategory;	/*	the xp category the pokemon belongs to	*/
      std::shared_ptr<Type> _type1;			/*	The first Type of the pokemon	*/
      std::shared_ptr<Type> _type2;			/*	The second Type of the pokemon	*/

		/*	Triplet of value defining an evolution : 
		*	-> short ! level of the evolution
		*	-> number of the evolution
		*	-> name of the evolution
		*/
      std::shared_ptr<std::tuple<short,short,std::string>> _evolution;

		/*	map of values concerning the attack list:
		*	-> key = short : level to reach to learn the attack.
		*	->	value = shared_ptr<Attack> : pointer on the attack to learn.
		*/
      std::shared_ptr<std::multimap<short, std::shared_ptr<Attack>>> _attackList;
      std::vector<std::shared_ptr<Attack>> _menuAttacks;	/*	vector of 4 pointer on Attack (null value can be inside) corresponding to the 4 attacks a pokemon can have to battle	*/
      std::string _state;		/*	state of the pokemon (poisonned, ...)	*/
      DIRECTION _direction;	/*	direction of the pokemon	*/
      std::shared_ptr<bool> _base;		/*	if the pokemon is a base pokemon */
      std::shared_ptr<EvolutionObserver> _evoObs;	/* pointer on the evolutionObserver : the factory	*/
      std::shared_ptr<XPObserver> _xpObs;		/*	pointer on the xp observer : the fightManager	*/
		std::shared_ptr<sf::Clock> _clock;		/*	a clock useful for the animation	*/
		std::shared_ptr<sf::Clock> _evolveTime;	/*	a clock useful fot the animation of the evolution	*/

         /* characs  */
      std::shared_ptr<short> _baseHP;     /*	base hp of a pokemon	*/
      std::shared_ptr<short> _baseAttack;	/*	base attack of a pokemon	*/
      std::shared_ptr<short> _baseDefense;   /*	base defense of a pokemon	*/
      std::shared_ptr<short> _baseSpeed;   /*	base speed of a pokemon	*/
      std::shared_ptr<short> _baseSpe_attack;   /*	base special attack of a pokemon	*/
      std::shared_ptr<short> _baseSpe_defense;   /*	base special defense of a pokemon	*/
      std::shared_ptr<short> _baseXP;   /*	base xp of a pokemon	*/
       
      short _lvlHP;				/*	total hp of the pokemon at its level	*/
      short _currentHP;			/*	current hp of the pokemon	*/
      short _lvlAttack;			/*	current attack of the pokemon at its level	*/	
      short _lvlDefense;			/*	current defense of the pokemon at its level	*/		
      short _lvlSpeed;		/*	current speed of the pokemon at its level	*/	
      short _lvlSpe_attack;		/*	current special attack of the pokemon at its level	*/	
      short _lvlSpe_defense;		/*	current special defense of the pokemon at its level	*/	

      short _iv_hp;			/*	hp iv of the pokemon	*/
      short _iv_attack;		/*	attakc iv of the pokemon	*/	
      short _iv_defense;	/*	defense iv of the pokemon	*/
      short _iv_speed;		/*	speed iv of the pokemon	*/
      short _iv_special;	/*	special iv of the pokemon	*/

      std::map<std::string, long> _evs;	/*	map of evs the pokemon has gained : the key is the string of the name of the ev, and the value is the value from 0 to 255	*/
      std::shared_ptr<std::map<std::string, short>> _evsToGive;	/*	evs to give to a pokemon when it is defeated	*/
		short _totalEVS; 		/*	total evs gained from the beginning	*/
		
		bool _fighting;			/*	is the pokemon is fighting	*/
		bool _toBeRemoved;		/*	if the pokemon has to be removed of the map	*/
		bool _showStatus;		/*	if the status of the pokemon has to be shown	*/

   public:
      /* Constructors */
      Pokemon();			/*	Default constructor	*/
      Pokemon(Pokemon const& pok);		/*	Copy constructor	*/
		/*	Constructor used to create a pokemon with its different characteristics	*/
      Pokemon(std::string name, short number, short lvl, bool base, short evolutionLvl, std::string evolutionName, short evolutionNb,std::string xpCategory, short hp, short attack, short defense, short speed, short speattack, short spedefense, short baseXP);

      virtual ~Pokemon();	/*	Destructor	*/

      /*Getters and Setters */
      short getLvl();
      long getXP();
      std::shared_ptr<long> getXPLimit();
      std::string getName();
      short getNumber();
      std::tuple<short,short,std::string> getEvolution();
      std::shared_ptr<Type> getType1();
      std::shared_ptr<Type> getType2();
      std::string getState();
      std::string getXPCategory();
      std::vector<std::shared_ptr<Attack>> getMenuAttacks();
      std::multimap<short, std::shared_ptr<Attack>> getAttackList();
      std::shared_ptr<EvolutionObserver> getEvoObserver();
      std::shared_ptr<XPObserver> getXPObserver();
      bool isBase();
		bool showStatus();

      short getBaseHP();
      short getBaseAttack();
      short getBaseDefense();
      short getBaseSpeed();
      short getBaseSpeAttack();
      short getBaseSpeDefense();
      short getHP();
      short getCurrentHP();
      short getAttack();
      short getDefense();
      short getSpeed();
      short getSpeAttack();
      short getSpeDefense();
      std::map<std::string, short> getEVSToGive();
      std::pair<short, std::shared_ptr<Attack>> getNextAttack();
      float getX();
      float getY();
      DIRECTION getDirection();
		sf::Clock getClock();
		std::shared_ptr<sf::Clock> getEvolveTime();
		bool isFighting();
		bool isFinalEvolution();
		bool hasToBeRemoved();

      void setName(std::string name);
      void setLvl(short lvl);
      void setXP(long xp);
      void setXPLimit(long xpLimit);
      void setCurrentHP(short hp);
      void setAttack(short attack);
      void setDefense(short defense);
      void setSpeed(short speed);
      void setSpeAttack(short speattack);
      void setSpeDefense(short spedefense);
      void setType1(std::shared_ptr<Type> type);
      void setType2(std::shared_ptr<Type> type);
		void setDirection(DIRECTION dir);
		void setX(float x);
		void setY(float y);
		void setFighting(bool b);
		void setRemoved(bool b);
		void stopEvolveTime();
		void setShowStatus(bool b);

      /*Operators */
      Pokemon& operator=(Pokemon const& pok);	/*	= operator	*/
      friend std::ostream& operator<<(std::ostream& o, Pokemon pok);	/*	<< operator	*/

      /* Methods   */

		/* winEVS mehod
		*	When a fight is done, the winner gain the certain amount of evs the defeated pokemons has to give.
		*	parameters
		*		map<string, short> evToGive : map of evs the defeated pokemon has to give (in string, the category; in short, the amount).
		*	no return statement
		*/
      void winEVS(std::map<std::string, short> evToGive);

		/* addEVSToGive method
		*	Adds an EV to give when defeated in the _evsToGive map.
		*	parameters
		*		string cat : name of the category.
		*		short nb : amount of ev that will be given.
		*	no return statement
		*
		*/
      void addEVSToGive(std::string cat, short nb);

		/*	resetIVS method
		*	Resets the IVs of the pokemon so that it is a unique pokemon
		*	no parameters
		*	no return statement
		*/
      void resetIVS();

		/*	addAttack method
		*	Adds an attack to the atttackList of the pokemon.
		*	parameters
		*		short lvl : level to reach to learn the attack.
		*		shared_ptr<Attack> attack : pointer on the Attack the pokemon will be able to learn.
		*	no return statement
		*/
      void addAttack(short lvl, std::shared_ptr<Attack> attack);

		/*	addNullAttackToMenu method
		*	Adds a null attack to the attacks the pokemon will be able to use in battles.
		*	no parameters
		*	no return statement
		*/
      void addNullAttackToMenu();

		/* printAttackList method
		*	Prints the attack list of the pokemon.
		*	no parameters
		*	no return statement
		*/
      void printAttackList();

		/*	resistanceTo method
		*	Checks if the type of the pokemon is resistant to the Type *type and returns the ratio.
		*	parameters
		*		shared_ptr<Type> type : type belonging to opponent.
		*	return
		*		ratio of the resistance/effectiveness of the type againt *type as a short
		*/
      short resistanceTo(std::shared_ptr<Type> type);

		/*	rerCalculateCharacs  method
		*	When leveled up, the pokemon needs to re calculate its level characterisitcs from its new level
		*	no parameters
		*	no return statement
		*/
      void reCalculateCharacs();

		/*	calculate**** methods
		*	Calculates the new _lvl*** atribute in function of the level of the pokemon
		*	no parameters
		*	return
		*		the new calculated characteristic as a short
		*/
      short calculateLvlHP();
      short calculateLvlAttack();
      short calculateLvlDefense();
      short calculateLvlSpeed();
      short calculateLvlSpeAttack();
      short calculateLvlSpeDefense();

		/*	lvlUp method
		*	The xp limit has already been looked for. It only increments the level, and reajust the xp that was over the former xpLimit.
		*	no parameters
		*	no return statement
		*/
      void lvlUP();

		/* checkNewAttack method
		*	It looks inside the attackList to check if at its new level, an attack can be learned.IA to learn the attack or not.
		*	no parameters
		*	no return statement
		*/
      void checkNewAttacks();

		/*	evolve method
		*	Evolves the pokemon. So it request the evolution, request the new xp limit, recalculate the characs, check for new attacks and start the clock for the animation
		*	no parameters
		*	no return statement
		*/
      void evolve();

		/*	position updating	*/

		/*	updatePosition method
		*	Updates the position of the pokemon in function of the speed of the scene.
		*	parameters
		*		short sceneSpeed : speed of the scene
		*	no return statement
		*/
		void updatePosition(short SceneSpeed);

		/*	switchDirection method
		*	Switches the direction of the pokemon.
		*	no parameters
		*	no return statement
		*/
		void switchDirection();
      
      /* observable functions */

		/*	addEvoObserver method
		*	Assign obs to _evoObs attribute.
		*	parameters
		*		shared_ptr<EvolutionObserver> obs : observer that will be attribute.
		*	no return statement
		*/
      void addEvoObserver(std::shared_ptr<EvolutionObserver> obs);

		/* removeEvoObserver method
		*	Resets the pointer of the attribute evoObs.
		*	parameters
		*		shared_ptr<EvolutionObserver> obs : observer that will be reset.
		*	no return statement
		*/
      void removeEvoObserver(std::shared_ptr<EvolutionObserver> obs);

		/* requestEvolution method
		*	Asks the evolution observer to return its next evolution. Performs all necessary arrangements to shift the different attributes from the evolution to the existant pokemon.
		*	parameters
		*		shared_ptr<EvolutionObserver> obs : observer asked to return the evolution.
		*	no return statement
		*/
      void requestEvolution(std::shared_ptr<EvolutionObserver> obs);

		/*	addXPObserver methpd
		*	Assign obs to the xpObserver attribute.
		*	parameters
		*		shared_ptr<XPObserver> obs : observer that will be assigned to xpObs.
		*	no return statement
		*/
      void addXPObserver(std::shared_ptr<XPObserver> obs);

		/*	removeXPObserver method
		*	Reset the observer.
		*	parameters
		*		shared_ptr<XPObserver> obs : observer that will be reset.
		*	no return statement
		*/
      void removeXPObserver(std::shared_ptr<XPObserver> obs);

		/*	needXPLimit method
		*	Request then next xp limit to the observer
		*	parameters
		*		shared_ptr<XPObserver> obs : observer asked to return the next xp limit.
		*	no return statement
		*/
      void needXPLimit(std::shared_ptr<XPObserver> obs);
};

#endif
