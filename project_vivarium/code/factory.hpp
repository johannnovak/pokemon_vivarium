/* file : factory.hpp 
 *	This file is the header of the factory.cpp file.
 *	This class can create pokemons from the databank it owns on demand. It will first load the types, load the attacks, and finally load the pokemons.
 *	johann.novak25@gmail.com
 *	15/03/14
 */

#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <vector>
#include <fstream>
#include <string.h>
#include <memory>

#include <rapidxml.hpp>
#include <pokemon.hpp>
#include <evolutionObserver.hpp>

class Factory : public EvolutionObserver
{
   private:
		/*	Attributes	*/
      std::vector<std::shared_ptr<Pokemon>> _pokemons;			/* vector of all pokemons loaded	*/
		std::vector<std::shared_ptr<Pokemon>> _basePokemons;		/* vector of all base pokemons	(pokemons that start the evolution chain) */
      std::vector<std::shared_ptr<Type>> _types;					/* vector of all the types of pokemons loaded	*/
      std::map<std::string, std::shared_ptr<Attack>> _attacks;	/*	map of all the attacks loaded	*/
		short _mapWidth;			/*	width of the overall map	*/
		short _mapHeight;			/*	height of the overall map	*/

      /* Observer functions   */

		/* returnEvolution method
		* This method returns the evolution of the pokemon which possesses the number in parameter.
		*	parameters
		*		short evolutionNumber : number of the pokemon which asks to evolve.
		*	return
		*		a pointer on the evolution of the pokemon which asked the evolution.
		*/
      std::shared_ptr<Pokemon> returnEvolution(short evolutionNumber);		

   public:
      /* Constructors   */
      Factory();								/*	Default constructor	*/
      Factory(Factory const& fac);		/*	Copy constructor	*/

      ~Factory();	/*	Destructor	*/

      /* Getters and Setters  */
      std::vector<std::shared_ptr<Pokemon>> getPokemons();
		void setMapWidth(short width);
		void setMapHeight(short height);

      /* Operators   */
      Factory& operator=(Factory const& fac);	/*	= operator	*/

      /* Methods   */

		/* parseTypes method
		*	This method parse the different types a pokemon can have from the file /xml/types.xml using the rapid-xml parser.
		*	no parameters.
		*	no return statement.
		*/
      void parseTypes();

		/* parseAttacks method
		*	This method parse the different attacks a pokemon can have from the file /xml/attacks.xml using the rapid-xml parser.
		*	no parameters.
		*	no return statement.
		*/
      void parseAttacks();
      
		/* parsePokedex method
		*	This method parse the different attributes of each pokemon from the file /xml/pokedex.xml using the rapid-xml parser.
		*	no parameters.
		*	no return statement.
		*/
		void parsePokedex();
		
		/* TODO	*/
		/* parseObjects method
		*	This method parse the different objects of the pokemon world from the file /xml/objects.xml using the rapid-xml parser.
		*	no parameters.
		*	no return statement.
		*/
		void parseObjects();
      
		/* createRandomBasePokemon method
		*	This method create a new pokemon from the vector of base pokemon in attributes and returns a pointer pointing on it.
		*	no parameters.
		*	return
		*		a pointer of Pokemon pointing on the new pokemon created.
		*/
		std::shared_ptr<Pokemon> createRandomBasePokemon();

		/* createPokemon method
		*	This method create a new pokemon from the number in parameter, and returns a pointer pointing on it.
		* 	parameters
		*		short number : number of the pokemon to create from the vector containing all the pokemons.
		*	return
		*		a pointer of Pokemon pointing on the new pokemon created.
		*/
      std::shared_ptr<Pokemon> createPokemon(short number);

		/*	printPokemons method
		*	Print all pokemons contained in the pokemon vector
		*/
      void printPokemons();
};
#endif
