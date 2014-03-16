/* pokemonObserver.hpp  */

#ifndef POKEMONOBSERVER_HPP
#define POKEMONOBSERVER_HPP

#include <pokemon.hpp>

class Pokemon;
class PokemonObserver
{
   public:
      /* Contructors */
      virtual ~PokemonObserver(){}

      /* Methods  */
      virtual void addPokemonToEvolve(std::shared_ptr<Pokemon> pok) = 0;
};
#endif
