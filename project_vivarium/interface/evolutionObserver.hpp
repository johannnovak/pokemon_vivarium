/* file : evolutionObserver.hpp   
 * This file is an interface header file.
 *	This interface is inherited by the Factory class. It is useful when a pokemon needs to evolve.
 *	johann.novak25@gmail.com
 *	16/03/14
*/

#ifndef EVOLUTIONOBSERVER_HPP
#define EVOLUTIONOBSERVER_HPP

#include <pokemon.hpp>

class Pokemon;
class EvolutionObserver
{
   public:
      /* Constructors   */
      virtual ~EvolutionObserver(){}

      /* Methods  */
      virtual std::shared_ptr<Pokemon> returnEvolution(short evolutionNumber)= 0;
};
#endif
