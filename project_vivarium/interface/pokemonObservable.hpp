/* pokemonObservable.hpp   */

#ifndef POKEMONOBSERVABLE_HPP
#define POKEMONOBSERVABLE_HPP

#include <pokemonObserver.hpp>

class PokemonObservable
{
   public:
      /* Constructors   */
      virtual ~PokemonObservable(){}

      /* Methods  */
      virtual void addPokemonObserver(std::shared_ptr<PokemonObserver> obs) = 0;
      virtual void removePokemonObserver(std::shared_ptr<PokemonObserver> obs) = 0;
      virtual void addEvolvePokemonToSceneManager(std::shared_ptr<Pokemon> pok) = 0;
};
#endif
