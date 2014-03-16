/* file : evolutionObservable.hpp   
 * This file is an interface header file.
 *	This class observe the evolutionObserver class. It is inherited by the pokemon class and when it needs to evolve, it calls the requestEvolution method.
 *	johann.novak25@gmail.com
 *	16/03/14
*/

#ifndef EVOLUTIONOBSERVABLE_HPP
#define EVOLUTIONOBSERVABLE_HPP

#include <evolutionObserver.hpp>

class EvolutionObservable
{
      public:
         /* Constructors   */
         virtual ~EvolutionObservable(){}		/*	Virtual destructor empty	*/
 
         /* Methods  */
         virtual void addEvoObserver(std::shared_ptr<EvolutionObserver> obs) = 0;
         virtual void removeEvoObserver(std::shared_ptr<EvolutionObserver> obs) = 0;
         virtual void requestEvolution(std::shared_ptr<EvolutionObserver> obs) = 0;
};
#endif
