/* file : fight.hpp
*	This file is the header of the fight.cpp file.
*	This class defines the concept of a pokemon battle between 2 pokemons	
*	johann.novak25@gmail.com
*	15/03/14
*/

#ifndef FIGHT_HPP
#define FIGHT_HPP

#include <memory>
#include <mutex>
#include <chrono>
#include <thread>

#include <pokemon.hpp>
#include <pokemonObservable.hpp>

class Fight: public PokemonObservable
{
   public:
		/*	Attributes	*/
      std::shared_ptr<Pokemon> _pok1;		/*	pointer on the pokemon which has the highest speed	*/
      std::shared_ptr<Pokemon> _pok2;		/* pointer on the pokemon which has the lowest speed	*/
      std::vector<short> _characs1;			/*	characteristics of *pok1 when he entered battle	*/
      std::vector<short> _characs2;			/*	characteristics of *pok2 when he entered battle	*/
      std::shared_ptr<PokemonObserver> _pokObs;		/*	pokemon observer that will be useful when wanting to remove a pokemon from the sceneManager	*/
		bool _hasBegun;							/*	test if the fight has already begun	*/
		bool _hasEnded;							/*	test if the fight has ended	*/

   public:
      /* Constructors   */
      Fight();								/*	Default constructor	*/
      Fight(Fight const& fight);		/*	Copy constructor	*/
		Fight(std::shared_ptr<Pokemon> pok1, std::shared_ptr<Pokemon> pok2);		/* Constructor that is always used to instanciate the fight between two pokemons	*/

		/*	Destructor	*/
      ~Fight();

		/*	Getters and Setters	*/
		bool hasEnded();
		bool hasBegun();

      /* Operators   */
      Fight& operator=(Fight const& fight);	/*	= operator	*/

      /* Functions   */

		/*	startFight method
		*	This method is used to assign true to hasBegun and print that a new fightt has begun.
		*	no parameters
		*	no return statement
		*/
      void startFight();

		/*	startTurn method
		*	This method consist in one turn in a pokemon battle : a pokemon attacks, the other pokemon attacks
		*	no parameters
		*	no return statement
		*/
      void startTurn();

		/*	choiceOfAttack method
		*	IA for the  choice of the attack of the pokemon.
		*	parameter
		*		Pokemon pok : the pokemon that will perform an attack
		*	return
		*		a pointer on Attack, chosen by the IA
		*/
      std::shared_ptr<Attack> choiceOfAttack(Pokemon pok);

		/*	attack method
		*	Perform the attack attack to a pokemon *pok2 by a pokemon *pok1.
		*	parameters
		*		shared_ptr<Pokemon> pok1 : pointer on the pokemon that perform the attack.
		*		Attack attack : attack performed.
		*		shared_ptr<Pokemon> pok2 : pointer on the pokemon that undergoes the attack.
		*	no return statement
		*/
      void attack(std::shared_ptr<Pokemon> pok1, Attack attack, std::shared_ptr<Pokemon> pok2);

		/*	finishFight method
		*	Finishes fight, by printing the winner, tell the pokemon observer to remove the defeated pokemon, give xp to the winner and handle the evolution	
		*	no parameters	
		*	no return statement
		*/
      void finishFight();

		/* giveXP method
		*	Calculates and gives xp to the winner of the battle.
		*	parameters
		*		short lvl : level of the pokemon that won.
		*		string cat : the xp category of the pokemon that won.
		*	return
		*		the xp the pokemon got from winning the battle.
		*/
      long giveXP(short lvl, std::string cat);

		/*	calculateXP***	methods
		*	Give back the corresponding xp according to the level of the pokemon, each method correspon ds to a certain xp category.
		*	parameters
		*		short lvl : level of the pokemon that won.
		*	return
		*		the corresponding xp to the level and the category.
		*/
      long calculateXPFast(short lvl);
      long calculateXPMediumFast(short lvl);
      long calculateXPMediumSlow(short lvl);
      long calculateXPSlow(short lvl);
      
      /* observable functions */

		/*	addPokemonobserver method
		*	Add a pokemon observer to the list of pokemon observers, here it is a not a list but just an assignment.
		*	parameters
		*		shared_ptr<PokemonObserver> obs : pointer of PokemonObserver that is assigned to _pokObs.
		*	no return statement
		*/
      void addPokemonObserver(std::shared_ptr<PokemonObserver> obs);

		/*	removePokemonObserver method
		*	Assigns to null the pokemon observer passed in parameter.
		*	parameters
		*		shared_ptr<PokemonObserver> obs : pokemon observer to be removed.
		*	no return statement
		*/
      void removePokemonObserver(std::shared_ptr<PokemonObserver> obs);

		/*	addEvolveToSceneManager
		*	Adds in the sceneManager, in the list of pokemon that request evolution, a pokemon that is evolving.
		*	parameters
		*		shared_ptr<Pokemon> pok : pokemon that is going to evolve.
		*	no return statement
		*/
      void addEvolvePokemonToSceneManager(std::shared_ptr<Pokemon> pok);
};
#endif
