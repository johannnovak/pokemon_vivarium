/* file : sceneManager.cpp   
*	This file implements the methods in the sceneManager.hpp file.
*	johann.novak25@gmail.com
*	15/03/14
*/

#include <sceneManager.hpp>

using namespace std;
using namespace sf;

/* Constructors   */

/*	Default constructor	*/
SceneManager::SceneManager()
{
	_pokemons = shared_ptr<vector<shared_ptr<Pokemon>>>(new vector<shared_ptr<Pokemon>>());
/*	thread* t = new thread[NB_FIGHTMANAGER];
	for(short i = 0; i < NB_FIGHTMANAGER; ++i)
	{
		shared_ptr<FightManager> f = shared_ptr<FightManager>(new FightManager());
		_fightManagers.push_back(f);
		t[i](&FightManager::run, &_fightManagers[i]);
		t[i].detach();
		f.reset();
	}*/
	_fightManager1 = shared_ptr<FightManager>(new FightManager());
	thread t1(&FightManager::run, _fightManager1);
	t1.detach();
	_fightManager2 = shared_ptr<FightManager>(new FightManager());
	thread t2(&FightManager::run, _fightManager2);
	t2.detach();
	_factory = shared_ptr<Factory>(new Factory());
   _id = 0;
}

/*	Copy constructor	*/
SceneManager::SceneManager(SceneManager const& scene)
{
   _pokemons = scene._pokemons;
	_toEvolve = scene._toEvolve;
	_toAdd = scene._toAdd;
   _factory = scene._factory;
   _fightManager1 = scene._fightManager1;
   _fightManager2 = scene._fightManager2;
   _id = scene._id;
}

/*	Destructor	*/
SceneManager::~SceneManager()
{
   for(short i = 0; i < _pokemons->size(); ++i)
      (*_pokemons)[i].reset();
   _pokemons->clear();
	_pokemons.reset();
	vector<shared_ptr<Pokemon>>::iterator it = _toEvolve.begin();
	while(it != _toEvolve.end())
	{
		(*it).reset();
		it++;
	}
	_toEvolve.clear();

	vector<shared_ptr<Pokemon>>::iterator it1 = _toAdd.begin();
	while(it != _toAdd.end())
	{
		(*it).reset();
		it++;
	}
	_toAdd.clear();
	
/*	vector<shared_ptr<FightManager>>::iterator itfight = _fightManagers.begin();
	while(itfight != _fightManagers.end())
	{
		(*itfight).reset();
		++itfight;
	}
	_fightManagers.clear();*/
	_fightManager1.reset();
	_fightManager2.reset();
}

/* Getters and setters  */
shared_ptr<vector<shared_ptr<Pokemon>>> SceneManager::getPokemons()
{
   return _pokemons;
}
shared_ptr<Factory> SceneManager::getFactory()
{
   return _factory;
}
shared_ptr<FightManager> SceneManager::getFightManager1()
{
   return _fightManager1;
}
shared_ptr<FightManager> SceneManager::getFightManager2()
{
   return _fightManager2;
}
vector<shared_ptr<Pokemon>> SceneManager::getToAdd()
{
	return _toAdd;
}
/* Operators   */

/*	= operator	*/
SceneManager& SceneManager::operator=(SceneManager const& scene)
{
   _pokemons = scene._pokemons;
	_toAdd = scene._toAdd;
   _factory = scene._factory;
   _fightManager1 = scene._fightManager1;
   _fightManager2 = scene._fightManager2;
   _id = scene._id;

   return *this;
}

/*	<< operator	*/
ostream& operator<<(ostream& o, SceneManager scene)
{
   return o;
}

/* Methods   */

/*	addRandomPokemon method
*	Calls createRandomBasePokemon from factory, change the pokemon's name and add the different observers to the pokemon
*	no parameters	
*	no return statement
*/
void SceneManager::addRandomPokemon()
{
   shared_ptr<Pokemon> pok = _factory->createRandomBasePokemon();
 
   _toAdd.push_back(pok);
   pok->setName(pok->getName()+"|"+to_string(_id));
   ++_id;
   /* adding the observers */
   pok->addEvoObserver(_factory);
   pok->addXPObserver(_fightManager1);
}

/* addPokemons method
*	Add the pokemons in the toAdd vector into the vector of printed pokemons.
*	no parameters
*	no return statement
*/
void SceneManager::addPokemons()
{
	vector<shared_ptr<Pokemon>>::iterator it = _toAdd.begin();
	while(!_toAdd.empty())
	{
		_pokemons->push_back(*it);
		it->reset();
		_toAdd.erase(it);
	}
}

/*	addPokemonToEvolve method
*	Add a pokemon to the evolveList
*	parameters
*		shared_ptr<Pokemon> pok : pokemon that needs to be added to the evolution list.
*	no return statement
*/
void SceneManager::addPokemonToEvolve(shared_ptr<Pokemon> pok)
{
	_toEvolve.push_back(pok);
}

/*	printPokemons method	
*	Print all pokemons of the _pokemons vector.
*	no parameters
*	no return statement
*/
void SceneManager::printPokemons()
{
   for(short i = 0; i < _pokemons->size(); ++i)
      cout << *(*_pokemons)[i] << endl;
}

/*	listPokemons method
*	List the names of the pokemons in _pokemons.
*	no parameters
*	no return statement
*/
void SceneManager::listPokemons()
{
   cout << "List of Pokemons :" << endl;
   for(short i = 0; i < _pokemons->size(); ++i)
      cout << (*_pokemons)[i]->getName() << endl;
   cout << endl;
}

/*	removePokemons method
*	Remove all the pokemons that has the value true for the attribute hasToBeRemoved.
*	no parameters
*	no return statement
*/
void SceneManager::removePokemons()
{
	vector<shared_ptr<Pokemon>>::iterator it = _pokemons->begin();
	while(it != _pokemons->end())
	{
		if((*it)->hasToBeRemoved())
			_pokemons->erase(it);
		else
			it++;
	}
}

/*	evolvePokemons method
*	Request evolution for all the pokemons inside the toEvolve vector.
*	no parameters
*	no return statement
*/
void SceneManager::evolvePokemons()
{
	vector<shared_ptr<Pokemon>>::iterator it = _toEvolve.begin();
	while(_toEvolve.size() != 0)
	{
		(*it)->evolve();
		_toEvolve.erase(it);
	}
}

/*	checkCollisions method
*	Check if the pokemons are in collision with each others.
*	no parameters
*	no return statement
*/
void SceneManager::checkCollisions()
{
	vector<shared_ptr<FightManager>>::iterator it;
	vector<shared_ptr<FightManager>>::iterator tempIt;
	set<shared_ptr<Pokemon>> s;

	for(auto pok1 : *_pokemons)
	{
		s.insert(pok1);
		for(auto pok2 : *_pokemons)
		{
			if(s.count(pok2) == 0)
			{
				if(pok1->intersects(*pok2))
				{
					if(!pok2->isFighting())
					{
						/*it = _fightManagers.begin();
						tempIt = _fightManagers.begin();
						while(it != _fightManagers.end())
						{
							if((*it)->getNbFight() > (*tempIt)->getNbFight())
								tempIt = it;
							++it;
						}
						(*tempIt)->addFight(pok1, pok2);
						*/
						if(_fightManager1->getNbFight() > _fightManager2->getNbFight())
							_fightManager2->addFight(pok1, pok2);
						else
							_fightManager1->addFight(pok1, pok2);
					}
					else if(!pok1->isFighting() && pok2->isFighting())
						pok1->switchDirection();
				}
			}
		}
	}
	s.clear();
}
/* Observer functions   */

/*	removePokemon method			********	NOT USED ********
*	remove a pokemon from the vector of pokemon to be printed.
*	parameters	
*		shared_ptr<Pokemon> pok : pokemon to be removed.
*	no return statement
*/
void SceneManager::removePokemon(std::shared_ptr<Pokemon> pok)
{
   short i = 0;
   bool b = false;
	vector<shared_ptr<Pokemon>>::iterator it = _pokemons->begin();
   while(it != _pokemons->end() && !b)
   {
      if((*it)->getName().compare(pok->getName()) == 0)
         b = true;
      else
         it++;
   }
   _pokemons->erase(it);
}
