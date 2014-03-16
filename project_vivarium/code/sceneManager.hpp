/* file : sceneManager.hpp   
*	This file is the header of the sceneManager.cpp file.
*	This class handles all entities present on the screen. So it updates the positions, it creates a fight when collision, and remove pokemons when they are dead.
*	johann.novak25@gmail.com
*	15/03/14
*/

#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <vector>
#include <string.h>
#include <cstdlib>
#include <fstream>
#include <thread>

#include <pokemon.hpp>
#include <rapidxml.hpp>
#include <factory.hpp>
#include <fightManager.hpp>
#include <SFML/System.hpp>

#define NB_FIGHTMANAGER 2

class SceneManager: public PokemonObserver
{
   private:
		/*	Attributes	*/
      std::shared_ptr<std::vector<std::shared_ptr<Pokemon>>> _pokemons;		/*	vector of pokemon that are printted on the screen	*/
		std::vector<std::shared_ptr<Pokemon>> _toEvolve;		/*	pokemons that are requesting evolution	*/
		std::vector<std::shared_ptr<Pokemon>> _toAdd;		/*	pokemons that are to be added in the vector of printed pokemons	*/
/*      std::vector<std::shared_ptr<Type>> _types;			*/
      std::shared_ptr<Factory> _factory;					/*	factory used to request the creation of a pokemon	*/
      std::shared_ptr<FightManager> _fightManager1;	/*	fightManager that will handle the fights	*/
      std::shared_ptr<FightManager> _fightManager2;
      unsigned short _id;			/*	id that will be added of a newly created pokemon (to differentiates himself from the other pokemons)	*/
		std::mutex _mut;		/*	mutex to protect data from threads	*/
      
      /* Observer functions   */

		/*	removePokemon method			********	NOT USED ********
		*	remove a pokemon from the vector of pokemon to be printed.
		*	parameters	
		*		shared_ptr<Pokemon> pok : pokemon to be removed.
		*	no return statement
		*/
      void removePokemon(std::shared_ptr<Pokemon> pok);		

   public:
      /* Constructors   */
      SceneManager();						/*	Default constructor	*/
      SceneManager(SceneManager const& scene);		/*	Copy constructor	*/

      ~SceneManager();			/*	Destructor	*/

      /* Getters and setters  */
      std::shared_ptr<std::vector<std::shared_ptr<Pokemon>>> getPokemons();
      std::shared_ptr<Factory> getFactory();
      std::shared_ptr<FightManager> getFightManager1();
      std::shared_ptr<FightManager> getFightManager2();
		std::vector<std::shared_ptr<Pokemon>> getToAdd();

      /* Operators   */
      SceneManager& operator=(SceneManager const& scene);		/*	= operator	*/
      friend std::ostream& operator<<(std::ostream& o, SceneManager scene);		/*	<< operator	*/

      /* Methods   */

		/*	addRandomPokemon method
		*	Calls createRandomBasePokemon from factory, change the pokemon's name and add the different observers to the pokemon
		*	no parameters	
		*	no return statement
		*/
      void addRandomPokemon();

		/* addPokemons method
		*	Add the pokemons in the toAdd vector into the vector of printed pokemons.
		*	no parameters
		*	no return statement
		*/
		void addPokemons();

		/*	addPokemonToEvolve method
		*	Add a pokemon to the evolveList
		*	parameters
		*		shared_ptr<Pokemon> pok : pokemon that needs to be added to the evolution list.
		*	no return statement
		*/
		void addPokemonToEvolve(std::shared_ptr<Pokemon> pok);

		/*	printPokemons method	
		*	Print all pokemons of the _pokemons vector.
		*	no parameters
		*	no return statement
		*/
      void printPokemons();

		/*	listPokemons method
		*	List the names of the pokemons in _pokemons.
		*	no parameters
		*	no return statement
		*/
      void listPokemons();
		
		/*	removePokemons method
		*	Remove all the pokemons that has the value true for the attribute hasToBeRemoved.
		*	no parameters
		*	no return statement
		*/
		void removePokemons();

		/*	evolvePokemons method
		*	Request evolution for all the pokemons inside the toEvolve vector.
		*	no parameters
		*	no return statement
		*/
		void evolvePokemons();

		/*	checkCollisions method
		*	Check if the pokemons are in collision with each others.
		*	no parameters
		*	no return statement
		*/
		void checkCollisions();
};
#endif
