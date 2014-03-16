/* file : fightManager.cpp 
*	This file implements the methods defined in the fightManager.hpp file.
*	johann.nova25@gmail.com
*	15/03/14
*/
#include <fightManager.hpp>

using namespace std;
using namespace rapidxml;

/* constructors   */

/*	Default constructor	*/
FightManager::FightManager()
{
   parseXP();
	_nbDeadPokemon = 0;
	_nbFight = 0;
}

/*	Copy Constructor	*/
FightManager::FightManager(FightManager const& fight)
{
   _fights = fight._fights;
   _fast = fight._fast;
   _mediumFast = fight._mediumFast;
   _mediumSlow = fight._mediumSlow;
   _slow = fight._slow;
   _scene = fight._scene;
}

/*	Destructor	*/
FightManager::~FightManager()
{
   _fights.clear();
   map<short,shared_ptr<long>>::iterator it = _fast.begin();
   while(it != _fast.end())
   {
      it->second.reset();
      it++;
   }
   _fast.clear();
   it = _mediumFast.begin();
   while(it != _mediumFast.end())
   {
      it->second.reset();
      it++;
   }
   _mediumFast.clear();
   it = _mediumSlow.begin();
   while(it != _mediumSlow.end())
   {
      it->second.reset();
      it++;
   }
   _mediumSlow.clear();
   it = _slow.begin();
   while(it != _slow.end())
   {
      it->second.reset();
      it++;
   }
   _slow.clear();
	_scene.reset();
}

/* Getters and Setters  */
map<short, shared_ptr<long>> FightManager::getSlow()
{
   return _slow;
}
map<short, shared_ptr<long>> FightManager::getMediumSlow()
{
   return _mediumSlow;
}
map<short, shared_ptr<long>> FightManager::getFast()
{
   return _fast;
}
map<short, shared_ptr<long>> FightManager::getMediumFast()
{
   return _mediumFast;
}
shared_ptr<SceneManager> FightManager::getScene()
{
   return _scene;
}
list<shared_ptr<Fight>> FightManager::getFights()
{
	return _fights;
}
short FightManager::getNbDeadPokemon()
{
	return _nbDeadPokemon;
}

void FightManager::setScene(std::shared_ptr<SceneManager> scene)
{
   _scene = scene;
}
short FightManager::getNbFight()
{
	return _nbFight;
}
/* Operators   */
FightManager& FightManager::operator=(FightManager const& fight)		/*	= operator	*/
{
   _fights = fight._fights;
   _fast = fight._fast;
   _mediumFast = fight._mediumFast;
   _mediumSlow = fight._mediumSlow;
   _slow = fight._slow;
	_scene = fight._scene;

   return *this;
}

/* Methods   */
		
/*	parseXP method
*	Parse the xp tables (fast, medium fast, medium slow, slow) from the file /xml/xp.xml
*	no parameters
*	no return statement
*/
void FightManager::parseXP()
{
   short lvl;
   xml_document<> doc;
   ifstream file("./code/xml/xp.xml");
   if(file)
   {
      vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
      buffer.push_back('\0');
        
      doc.parse<0>(&buffer[0]);

		/*	For each line in the xp.xml file, we create 4 pointers of long corresponding to the xp categories, and we add them to the map as their line as key (it corresponds to the level)	*/
      xml_node<>* root_node = doc.first_node("xptable");
      for(xml_node<>* lvl_node = root_node->first_node("lvl"); lvl_node; lvl_node = lvl_node->next_sibling())
      {
         lvl = atoi(lvl_node->first_attribute("nb")->value());
         shared_ptr<long> ptr_fast = shared_ptr<long>(new long(atoi(lvl_node->first_attribute("fast")->value())));
         _fast[lvl] = ptr_fast;
         shared_ptr<long> ptr_mediumFast = shared_ptr<long>(new long(atoi(lvl_node->first_attribute("mediumfast")->value())));
         _mediumFast[lvl] = ptr_mediumFast;
         shared_ptr<long> ptr_mediumSlow = shared_ptr<long>(new long(atoi(lvl_node->first_attribute("mediumslow")->value())));
         _mediumSlow[lvl] = ptr_mediumSlow;
         shared_ptr<long> ptr_slow = shared_ptr<long>(new long(atoi(lvl_node->first_attribute("slow")->value())));
         _slow[lvl] = ptr_slow;
      }
   }
   else
      cout << "FILE attacks.xml NULL" << endl;
   file.close();
}

/*	addFight method
*	Add a fight to the vector of fights occuring.
*	parameters
*		shared_ptr<Pokemon> pok1 : pointer of Pokemon pointing on one of the two pokemon that will participate in the battle
*		shared_ptr<Pokemon> pok2 : pointer of Pokemon pointing on one of the two pokemon that will participate in the battle
*	no return statement
*/
void FightManager::addFight(shared_ptr<Pokemon> pok1, shared_ptr<Pokemon> pok2)
{
	if(pok1 && pok2)
	{
		/*	If the pokemons exist :
		*	->	we set their fighting state to true,
		*	-> we create a new Fight between those two
		*	-> we assign the sceneManager to the fight's attribute
		*	->	we add the fight to the FightManager
		*	-> increment the number of fights that is occuring
		*/
		pok1->setFighting(true);
		pok2->setFighting(true);
  	 	shared_ptr<Fight> fight(shared_ptr<Fight>(new Fight(pok1,pok2)));
  		fight->addPokemonObserver(_scene);
		_fights.push_back(fight);
		++_nbFight;
	}
}

/*	printXPTable method
*	Prints the xp table of all the categories
*/
void FightManager::printXPTable()
{
   cout << "Table of XP : " << endl;
   cout << "Lvl\tfast\tmediumFast\tmediumSlow\tslow" << endl;
   map<short,shared_ptr<long>>::iterator it1 = _fast.begin();
   map<short,shared_ptr<long>>::iterator it2 = _mediumFast.begin();
   map<short,shared_ptr<long>>::iterator it3 = _mediumSlow.begin();
   map<short,shared_ptr<long>>::iterator it4 = _slow.begin();
   while(it1 != _fast.end())
   {
      cout << it1->first << "->" << (it1->first+1) << "\t";
      cout << *it1->second;
      cout << "\t" ;
      cout << *it2->second;
      cout << "\t\t";
      cout << *it3->second;
      cout << "\t\t";
      cout << *it4->second;
      cout << endl;
      it1++;
      it2++;
      it3++;
      it4++;
   }
}

/* Observer methods  */

/*	getNextXPLimit method
*	Returns the amount of xp required to lvl up according to the level and the category
*	parameters.
*		short lvl : level of the pokemon making the request.
*		string cat : category of the pokemon making the request.
*	return 
*		the amount of xp needed to lvl up as a long.
*/
shared_ptr<long> FightManager::getNextXPLimit(short lvl, string cat)
{
   if(cat.compare("fast") == 0)
      return _fast[lvl];
   else if(cat.compare("medium fast") == 0)
      return _mediumFast[lvl];
   else if(cat.compare("medium slow") == 0)
      return _mediumSlow[lvl];
   else if(cat.compare("slow") == 0)
      return _slow[lvl];
}

/*	run method
*	Start the thread that will start to :
*		-> begin fights 
*		-> start turns of fights not over  
*		->	remove fights that are over
*	no parameters
*	no return statement
*/
void FightManager::run()
{
	list<shared_ptr<Fight>>::iterator it;
	bool stop = false;
	while(!stop)
	{
		if(!_fights.empty())
		{
			it = _fights.begin();
			while(it != _fights.end())
			{
				if(!(*it)->hasBegun() && !(*it)->hasEnded())
					(*it)->startFight();
				if((*it)->hasBegun() && !(*it)->hasEnded())
					(*it)->startTurn();
				if((*it)->hasEnded())
				{
					++_nbDeadPokemon;
					(*it)->finishFight();
					(*it).reset();
					it = _fights.erase(it);
					--_nbFight;
				}
				else
					++it;
			}
		}
	}
}
