/* pokemon.cpp */

#include <pokemon.hpp>

using namespace std;
using namespace sf;

/* Constructors */

/*	Default constructor	*/
Pokemon::Pokemon(){}

/*	Copy constructor	*/
Pokemon::Pokemon(Pokemon const& pok)
{
   _number = pok._number;
   _name = pok._name;
   _lvl = pok._lvl;
   _xp = pok._xp;
   _xpLimit = pok._xpLimit;
   _xpCategory = pok._xpCategory;
   _type1 = pok._type1;
   _type2 = pok._type2;
   _evolution = pok._evolution;
   _attackList = pok._attackList;
   _menuAttacks = pok._menuAttacks;
   _state = pok._state;
	_direction = pok._direction;
   _base = pok._base;
   _evoObs = pok._evoObs;
   _xpObs = pok._xpObs;
	_clock = shared_ptr<Clock>(new Clock());
	_evolveTime = pok._evolveTime;

   _baseHP = pok._baseHP;
   _baseAttack = pok._baseAttack;
   _baseDefense = pok._baseDefense;
   _baseSpeed = pok._baseSpeed;
   _baseSpe_attack = pok._baseSpe_attack;
   _baseSpe_defense = pok._baseSpe_defense;
   _baseXP = pok._baseXP;

   _lvlHP = pok._lvlHP;
   _currentHP = pok._currentHP;
   _lvlAttack = pok._lvlAttack;
   _lvlDefense = pok._lvlDefense;
   _lvlSpeed = pok._lvlSpeed;
   _lvlSpe_attack = pok._lvlSpe_attack;
   _lvlSpe_defense = pok._lvlSpe_defense;

   _iv_hp = pok._iv_hp;
   _iv_attack = pok._iv_attack;
   _iv_defense = pok._iv_defense;
   _iv_speed = pok._iv_speed;
   _iv_special = pok._iv_special;

   _evs = pok._evs;
   _evsToGive = pok._evsToGive;

	left = pok.left;
	top = pok.top;

	_fighting = false;
	_toBeRemoved = false;
	_showStatus = false;
}

/*	Contrsutcor used to create a pokemon from characteristics	*/
Pokemon::Pokemon(string name, short number, short lvl, bool base, short evolutionLvl, string evolutionName, short evolutionNb, string xpCategory, short hp, short attack, short defense, short speed, short speattack, short spedefense, short baseXP)
{
   _number = shared_ptr<short>(new short(number));
   _name = name;
   _lvl = lvl;
   _xp = 0;
   _xpCategory = shared_ptr<string>(new string(xpCategory));
	_attackList = shared_ptr<multimap<short, shared_ptr<Attack>>>(new multimap<short, shared_ptr<Attack>>());
   _state = "normal";
   _direction = DIRECTION::RIGHT;
   _base = shared_ptr<bool>(new bool(base));
   _evolution = shared_ptr<tuple<short, short, string>>(new tuple<short, short, string>(make_tuple(evolutionLvl, evolutionNb, evolutionName)));

   _baseHP = shared_ptr<short>(new short(hp));
   _baseAttack = shared_ptr<short>(new short(attack));
   _baseDefense = shared_ptr<short>(new short(defense));
   _baseSpeed = shared_ptr<short>(new short(speed));
   _baseSpe_attack = shared_ptr<short>(new short(speattack));
   _baseSpe_defense = shared_ptr<short>(new short(spedefense));
   _baseXP = shared_ptr<short>(new short(baseXP));

   resetIVS();

   _evs["hp"] = 0;
   _evs["attack"] = 0;
   _evs["defense"] = 0;
   _evs["speed"] = 0;
   _evs["special attack"] = 0;
   _evs["special defense"] = 0;
   _totalEVS = 0;

   reCalculateCharacs();
   
	_evsToGive = shared_ptr<map<string, short>>(new map<string, short>());
	_fighting = false;
	_toBeRemoved = false;
	_showStatus = false;
}

/*	Destructor	*/
Pokemon::~Pokemon()
{
   /* TODO TODO TODO TODO TODO TODO TODO */
	_number.reset();
   _xpLimit.reset();
	_xpCategory.reset();
   _type1.reset();
   _type2.reset();
	_evolution.reset();
   _base.reset();
	_evoObs.reset();
   _xpObs.reset();
   for(short i = 0; i < _menuAttacks.size(); ++i)
      _menuAttacks[i].reset();
   _menuAttacks.clear();
   multimap<short, shared_ptr<Attack>>::iterator it = _attackList->begin();
   while(it != _attackList->end())
   {
      it->second.reset();
      it++;
   }
   _attackList->clear();
	_attackList.reset();
   _evs.clear();
   _evsToGive->clear();
	_evsToGive.reset();
	_clock.reset();
	_evolveTime.reset();

	_baseHP.reset();
	_baseAttack.reset();
	_baseDefense.reset();
	_baseSpeed.reset();
	_baseSpe_attack.reset();
	_baseSpe_defense.reset();
	_baseXP.reset();
}

/* Getters and Setters */
short Pokemon::getLvl()
{
   return _lvl;
}
long Pokemon::getXP()
{
   return _xp;
}
shared_ptr<long> Pokemon::getXPLimit()
{
   return _xpLimit;
}
string Pokemon::getName()
{
   return _name;
}
short Pokemon::getNumber()
{
   return *_number;
}
tuple<short,short,std::string> Pokemon::getEvolution()
{
   return *_evolution;
}
bool Pokemon::isBase()
{
   return *_base;
}
bool Pokemon::showStatus()
{
	return _showStatus;
}
short Pokemon::getBaseHP()
{
   return *_baseHP;
}
short Pokemon::getBaseAttack()
{
   return *_baseAttack;
}
short Pokemon::getBaseDefense()
{
   return *_baseDefense;
}
short Pokemon::getBaseSpeAttack()
{
   return *_baseSpe_attack;
}
short Pokemon::getBaseSpeDefense()
{
   return *_baseSpe_defense;
}
short Pokemon::getBaseSpeed()
{
   return *_baseSpeed;
}
short Pokemon::getHP()
{
   return _lvlHP;
}
short Pokemon::getCurrentHP()
{
   return _currentHP;
}
short Pokemon::getAttack()
{
   return _lvlAttack;
}
short Pokemon::getDefense()
{
   return _lvlDefense;
}
short Pokemon::getSpeAttack()
{
   return _lvlSpe_attack;
}
short Pokemon::getSpeDefense()
{
   return _lvlSpe_defense;
}
short Pokemon::getSpeed()
{
   return _lvlSpeed;
}
shared_ptr<Type> Pokemon::getType1()
{
   return _type1;
}
shared_ptr<Type> Pokemon::getType2()
{
   return _type2;
}
string Pokemon::getState()
{
   return _state;
}
DIRECTION Pokemon::getDirection()
{
   return _direction;
}
vector<shared_ptr<Attack>> Pokemon::getMenuAttacks()
{
   return _menuAttacks;
}
multimap<short, shared_ptr<Attack>> Pokemon::getAttackList()
{
   return *_attackList;
}
shared_ptr<EvolutionObserver> Pokemon::getEvoObserver()
{
   return _evoObs;
}
shared_ptr<XPObserver> Pokemon::getXPObserver()
{
   return _xpObs;
}
string Pokemon::getXPCategory()
{
   return *_xpCategory;
}
map<string, short> Pokemon::getEVSToGive()
{
   return *_evsToGive;
}
pair<short,shared_ptr<Attack>> Pokemon::getNextAttack()
{
	/*	we check if the new attack is stronger than one of the attacks in the attack menu
	*	TODO
	*/
   multimap<short,shared_ptr<Attack>>::iterator it = _attackList->begin();
   short temp = 101;
   while(it != _attackList->end())
   {
      if(it->first > _lvl)
         if(temp > it->first)
            temp = it->first;
     it++;
   }
   pair<short, shared_ptr<Attack>> p = make_pair(temp, _attackList->find(temp)->second);
   return p;
}
float Pokemon::getX()
{
   return left;
}
float Pokemon::getY() 
{
   return top;
}
Clock Pokemon::getClock()
{
	return *_clock;
}
shared_ptr<Clock> Pokemon::getEvolveTime()
{
	return _evolveTime;
}
bool Pokemon::isFighting()
{
	return _fighting;
}
bool Pokemon::isFinalEvolution()
{
	return ((get<2>(*_evolution).compare("none") == 0)?true:false);
}
bool Pokemon::hasToBeRemoved()
{
	return _toBeRemoved;
}
void Pokemon::setName(std::string name)
{
   _name = name;
}
void Pokemon::setLvl(short lvl)
{
   _lvl = lvl;
   reCalculateCharacs();
}
void Pokemon::setXP(long xp)
{
   _xp = xp;
}
void Pokemon::setXPLimit(long xpLimit)
{
   *_xpLimit = xpLimit;
}
void Pokemon::setCurrentHP(short hp)
{
   _currentHP = hp;
}
void Pokemon::setAttack(short attack)
{
   _lvlAttack = attack;
}
void Pokemon::setDefense(short defense)
{
   _lvlDefense = defense;
}
void Pokemon::setSpeed(short speed)
{
   _lvlSpeed = speed;
}
void Pokemon::setSpeAttack(short speattack)
{
   _lvlSpe_attack = speattack;
}
void Pokemon::setSpeDefense(short spedefense)
{
   _lvlSpe_defense = spedefense;
}
void Pokemon::setType1(shared_ptr<Type> type1)
{
   _type1 = type1;
}
void Pokemon::setType2(shared_ptr<Type> type2)
{
   _type2 = type2;
}
void Pokemon::setDirection(DIRECTION dir)
{
	_direction = dir;
}
void Pokemon::setX(float x)
{
	left = x;
}
void Pokemon::setY(float y)
{
	top = y;
}
void Pokemon::setFighting(bool b)
{
	_fighting = b;
}
void Pokemon::setRemoved(bool b)
{
	_toBeRemoved = b;
}
void Pokemon::stopEvolveTime()
{
	_evolveTime.reset();
	_evolveTime = nullptr;
}
void Pokemon::setShowStatus(bool b)
{
	_showStatus = b;
}

/* Operators */

/*	= operator	*/
Pokemon& Pokemon::operator=(Pokemon const& pok)
{
   _number = pok._number;
   _name = pok._name;
   _lvl = pok._lvl;
	_xp = pok._xp;
	_xpLimit = pok._xpLimit;
   _xpCategory = pok._xpCategory;
   _type1 = pok._type1;
   _type2 = pok._type2;
	_evolution = pok._evolution;
   _attackList = pok._attackList;
   _menuAttacks = pok._menuAttacks;
   _state = pok._state;
	_direction = pok._direction;
	_base = pok._base;
   _evoObs = pok._evoObs;
   _xpObs = pok._xpObs;
	_clock = pok._clock;

   _baseHP = pok._baseHP;
   _baseAttack = pok._baseAttack;
   _baseDefense = pok._baseDefense;
   _baseSpeed = pok._baseSpeed;
   _baseSpe_attack = pok._baseSpe_attack;
   _baseSpe_defense = pok._baseSpe_defense;   
   _baseXP = pok._baseXP;
   
   _lvlHP = pok._lvlHP;
   _currentHP = pok._currentHP;
   _lvlAttack = pok._lvlAttack;
   _lvlDefense = pok._lvlDefense;
   _lvlSpeed = pok._lvlSpeed;
   _lvlSpe_attack = pok._lvlSpe_attack;
   _lvlSpe_defense = pok._lvlSpe_defense;

   _iv_hp = pok._iv_hp;
   _iv_attack = pok._iv_attack;
   _iv_defense = pok._iv_defense;
   _iv_speed = pok._iv_speed;
   _iv_special = pok._iv_special;
   
   _evs = pok._evs;
   _evsToGive = pok._evsToGive;

	_fighting = pok._fighting;
	top = pok.top;
	left = pok.left;

   return *this;
}

/*	<< operator	*/
ostream& operator<<(ostream& o, Pokemon pok)
{
   bool boo = false;
   o << "***********************************" << endl;
   o << "           " << pok.getName()  << endl;
   o << "***********************************" << endl; 
   o << "N° " << pok.getNumber();
   o << "\t| Lvl " << pok.getLvl();
   o << "\t| " << pok.getCurrentHP() << "/" << pok.getHP() << " HP" << endl;
   o << "Type " << pok.getType1()->getName();
   if(pok.getType2()->getName() != pok.getType1()->getName())
      o << "/" << pok.getType2()->getName();
   o << endl << "-----------------------------------"<< endl;
   o << "Attack " << pok.getAttack();
   o << "\t| Defense " << pok.getDefense() << endl;
   o << "Spe Attack " << pok.getSpeAttack();
   o << "\t| Spe Defense " << pok.getSpeDefense() << endl;
   o << "Speed " << pok.getSpeed() << endl;
   o << "-----------------------------------"<< endl;
   o << "         ATTACKS" << endl;
   if(pok.getMenuAttacks().size() > 0)
      o << pok.getMenuAttacks()[0]->getName();
   else
      o << "-------";
   o << "\t\t\t";
   if(pok.getMenuAttacks().size() > 1)
      o << pok.getMenuAttacks()[1]->getName();
   else
      o << "-------";
   o << endl;
   if(pok.getMenuAttacks().size() > 2)
      o << pok.getMenuAttacks()[2]->getName();
   else
      o << "-------";
   o << "\t\t\t";
   if(pok.getMenuAttacks().size() > 3)
      o << pok.getMenuAttacks()[3]->getName();
   else
      o << "-------";
   /* TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO */
   o << endl << "Next attack to learn : ";

   auto p = pok.getNextAttack();
   o << p.second->getName() << " at lvl " << p.first;
   o << endl  << "-----------------------------------"<< endl;
   o << "XP : " << pok.getXP() << "/" << *pok.getXPLimit() << endl;
   o << "Next evolution : " << get<2>(pok.getEvolution()) << " at lvl " << get<0>(pok.getEvolution());
   o << endl;
   o << "===================================" << endl;
   return o;
}

/* Methods   */


/* winEVS mehod
*	When a fight is done, the winner gain the certain amount of evs the defeated pokemons has to give.
*	parameters
*		map<string, short> evToGive : map of evs the defeated pokemon has to give (in string, the category; in short, the amount).
*	no return statement
*/
void Pokemon::winEVS(map<string, short> evToGive)
{
	/*	If the pokemons has not yet 512 evs and if it has not yet 255 evs in the specific ev, then it add the defeated pokemon's ev to give.
	*/
   map<string, short>::iterator it = evToGive.begin();
	if(_totalEVS < 512)
	{
		while(it != evToGive.end())
		{
			if(_evs[it->first] < 255)
			{
				_evs[it->first] += it->second;
				_totalEVS += it->second;
			}
			it++;
		}
   }
}

/* addEVSToGive method
*	Adds an EV to give when defeated in the _evsToGive map.
*	parameters
*		string cat : name of the category.
*		short nb : amount of ev that will be given.
*	no return statement
*
*/
void Pokemon::addEVSToGive(string cat, short nb)
{
   (*_evsToGive)[cat] = nb;
}

/*	resetIVS method
*	Resets the IVs of the pokemon so that it is a unique pokemon
*	no parameters
*	no return statement
*/
void Pokemon::resetIVS()
{
   _iv_hp = 0;
   _iv_attack = rand()%16;
   _iv_defense = rand()%16;
   _iv_speed = rand()%16;
   _iv_special = rand()%16;
   if(_iv_attack%2 == 1)
      _iv_hp += 8;
   if(_iv_defense%2 == 1)
      _iv_hp += 4;
   if(_iv_speed%2 == 1)
      _iv_hp += 2;
   if(_iv_special%2 == 1)
      _iv_hp += 1;
}

/*	addAttack method
*	Adds an attack to the atttackList of the pokemon.
*	parameters
*		short lvl : level to reach to learn the attack.
*		shared_ptr<Attack> attack : pointer on the Attack the pokemon will be able to learn.
*	no return statement
*/
void Pokemon::addAttack(short lvl, shared_ptr<Attack> attack)
{
   _attackList->insert(pair<short, shared_ptr<Attack>>(lvl, attack));
   if(lvl == 1 && _menuAttacks.size() < 4)
      _menuAttacks.push_back(attack);
}

/*	addNullAttackToMenu method
*	Adds a null attack to the attacks the pokemon will be able to use in battles.
*	no parameters
*	no return statement
*/
void Pokemon::addNullAttackToMenu()
{
   _menuAttacks.push_back(nullptr);
}

/* printAttackList method
*	Prints the attack list of the pokemon.
*	no parameters
*	no return statement
*/
void Pokemon::printAttackList()
{
   map<short, shared_ptr<Attack>>::iterator it = _attackList->begin();
   cout << _name << endl;
   while(it != _attackList->end())
   {
      cout << "lvl " << it->first << "\t" << it->second->getName() << endl;
      ++it;
   }
}

/*	resistanceTo method
*	Checks if the type of the pokemon is resistant to the Type *type and returns the ratio.
*	parameters
*		shared_ptr<Type> type : type belonging to opponent.
*	return
*		ratio of the resistance/effectiveness of the type againt *type as a short
*/
short Pokemon::resistanceTo(shared_ptr<Type> type)
{
   /* TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO */
	/*	We check in each set of resistance if the opponent's type exists. If so :
	*	-> if it is in resistantTo => ratio / 2
	*	-> if it is in weakTo => ratio * 2
	*	-> if it is in immuneTo => ratio * 0
	*/
   short ratio = 1;
   set<string>::iterator it;
   if(!_type1->getWeak().empty())
   {
      it = _type1->getWeak().begin();
      while(it != _type1->getWeak().end())
      {
         if(type->getName() == *it)
            ratio *= 2;
         it++;
      }
   }
  
   if(!_type1->getResistant().empty())
   {
      it = _type1->getResistant().begin();
      while(it != _type1->getResistant().end())
      {
         if(type->getName() == *it)
            ratio *= 0.5;
         it++;
      }
   }
  
   if(!_type1->getImmune().empty())
   {
      it = _type1->getImmune().begin();
      while(it != _type1->getImmune().end())
      {
         if(type->getName() == *it)
            ratio *= 0;
            it++;
      }
   }
   
   if(_type1 != _type2)
   {
      if(!_type2->getWeak().empty())
      {
         it = _type2->getWeak().begin();
         while(it != _type2->getWeak().end())
         {
            if(type->getName() == *it)
               ratio *= 2;
            it++;
         }
      }
      
      if(!_type2->getResistant().empty())
      {
         it = _type2->getResistant().begin();
         while(it != _type2->getResistant().end())
         {
            if(type->getName() == *it)
               ratio *= 0.5;
            it++;
         }
      }
      if(!_type2->getImmune().empty())
      {
         it = _type2->getImmune().begin();
         while(it != _type2->getImmune().end())
         {
            if(type->getName() == *it)
               ratio *= 0;
            it++;
         }
      }
   }
   
   return ratio;
}

/*	rerCalculateCharacs  method
*	When leveled up, the pokemon needs to re calculate its level characterisitcs from its new level
*	no parameters
*	no return statement
*/
void Pokemon::reCalculateCharacs()
{
   _lvlHP = calculateLvlHP();
   _currentHP = _lvlHP;
   _lvlAttack = calculateLvlAttack();
   _lvlDefense = calculateLvlDefense();
   _lvlSpeed = calculateLvlSpeed();
   _lvlSpe_attack = calculateLvlSpeAttack();
   _lvlSpe_defense = calculateLvlSpeDefense();
}

/*	calculate**** methods
*	Calculates the new _lvl*** atribute in function of the level of the pokemon
*	no parameters
*	return
*		the new calculated characteristic as a short
*/
short Pokemon::calculateLvlHP()
{
   return ((((_iv_hp+(*_baseHP)+(sqrt(_evs["hp"])/8)+50)*_lvl)/50)+10);
}
short Pokemon::calculateLvlAttack()
{
   return ((((_iv_attack+(*_baseAttack)+(sqrt(_evs["attack"])/8))*_lvl)/50)+5);
}
short Pokemon::calculateLvlDefense()
{
   return ((((_iv_defense+(*_baseDefense)+(sqrt(_evs["defense"])/8))*_lvl)/50)+5);
}
short Pokemon::calculateLvlSpeed()
{
   return ((((_iv_speed+(*_baseSpeed)+(sqrt(_evs["speed"])/8))*_lvl)/50)+5);
}
short Pokemon::calculateLvlSpeAttack()
{
   return ((((_iv_special+(*_baseSpe_attack)+(sqrt(_evs["special attack"])/8))*_lvl)/50)+5);
}
short Pokemon::calculateLvlSpeDefense()
{
   return ((((_iv_special+(*_baseSpe_defense)+(sqrt(_evs["special attack"])/8))*_lvl)/50)+5);
}

/*	lvlUp method
*	The xp limit has already been looked for. It only increments the level, and reajust the xp that was over the former xpLimit.
*	no parameters
*	no return statement
*/
void Pokemon::lvlUP()
{
   short overXP = _xp - *_xpLimit;
   ++_lvl;
   cout << ">>> " << _name << " gains a level ! It is now lvl " << _lvl << " \\o/ !" << endl;
   _xp = overXP;
}

/* checkNewAttack method
*	It looks inside the attackList to check if at its new level, an attack can be learned.IA to learn the attack or not.
*	no parameters
*	no return statement
*/
void Pokemon::checkNewAttacks()
{
   if(_attackList->count(_lvl) > 0)
   {
      short pos;
      if(_menuAttacks.size() < 4)
      {
         pos = _menuAttacks.size();
         _menuAttacks.push_back(_attackList->find(_lvl)->second);
      }
      else
      {
         for(short j = 0; j < _menuAttacks.size()-1; ++j)
            if(_menuAttacks[j]->getPower() < _menuAttacks[j+1]->getPower())
               pos = j;
         _menuAttacks[pos] = _attackList->find(_lvl)->second;
      }
         cout << "> " << _name << " learned the attack " << _menuAttacks[pos]->getName() << endl;
   }
}

/*	evolve method
*	Evolves the pokemon. So it request the evolution, request the new xp limit, recalculate the characs, check for new attacks and start the clock for the animation
*	no parameters
*	no return statement
*/
void Pokemon::evolve()
{
   requestEvolution(_evoObs);
   needXPLimit(_xpObs);
   reCalculateCharacs();
   checkNewAttacks();
	_evolveTime = shared_ptr<Clock>(new Clock());
}

/*	updatePosition method
*	Updates the position of the pokemon in function of the speed of the scene.
*	parameters
*		short sceneSpeed : speed of the scene
*	no return statement
*/
void Pokemon::updatePosition(short sceneSpeed)
{
	if(!_fighting && sceneSpeed != 0)
	{
		short temp;
		switch(_direction)
		{
			case DIRECTION::UP:
/*				if((temp = top-1 * log10(_lvlSpeed) * sceneSpeed) > 0)
					top = temp;
				else
					switchDirection();
	
	*/
				top = top-1*log10(_lvlSpeed) * sceneSpeed;
				break;
			case DIRECTION::DOWN:
/*				if((temp =  top+1 * log10(_lvlSpeed) * sceneSpeed)< sf::VideoMode::getDesktopMode().height)
					top = temp;
				else
					switchDirection();
*/
				top = top+1*log10(_lvlSpeed) * sceneSpeed;

				break;
			case DIRECTION::LEFT:
/*				if((temp = left-1 * log10(_lvlSpeed) * sceneSpeed) > 0)
					left = temp;
				else
					switchDirection();
*/
				left = left-1*log10(_lvlSpeed) * sceneSpeed;

				break;
			case DIRECTION::RIGHT:
/*				if((temp = left+1 * log10(_lvlSpeed) * sceneSpeed) < sf::VideoMode::getDesktopMode().width)
					left = temp;
				else
					switchDirection();
*/
	
				left = left+1*log10(_lvlSpeed) * sceneSpeed;
				break;
		}
		if(_clock->getElapsedTime().asSeconds() > (2+rand()%2))
			switchDirection();
	}
}

/*	switchDirection method
*	Switches the direction of the pokemon.
*	no parameters
*	no return statement
*/
void Pokemon::switchDirection()
{
	short temp;
	bool b(false);
	
	_currentHP += 5;
	if(_currentHP > _lvlHP)
		_currentHP = _lvlHP;

	do
	{
		temp = rand()%4;
		switch(temp)
		{
			case 0:
				if((int)_direction != temp)
				{
					b = true;
					setDirection(DIRECTION::UP);
				}
				break;
			case 1:
				if((int)_direction != temp)
				{
					b = true;
					_direction = DIRECTION::DOWN;
				}
				break;
			case 2:
				if((int)_direction != temp)
				{
					b = true;
					_direction = DIRECTION::LEFT;
				}
				break;
			case 3:
				if((int)_direction != temp)
				{
					b = true;
					_direction = DIRECTION::RIGHT;
				}
				break;
		}
	}while(!b);
	_clock->restart();
}

/* Observable functions */

/*	addEvoObserver method
*	Assign obs to _evoObs attribute.
*	parameters
*		shared_ptr<EvolutionObserver> obs : observer that will be attribute.
*	no return statement
*/
void Pokemon::addEvoObserver(shared_ptr<EvolutionObserver> obs)
{
   _evoObs = obs;
}
	
/* removeEvoObserver method
*	Resets the pointer of the attribute evoObs.
*	parameters
*		shared_ptr<EvolutionObserver> obs : observer that will be reset.
*	no return statement
*/
void Pokemon::removeEvoObserver(shared_ptr<EvolutionObserver> obs)
{
   _evoObs.reset();
}

/* requestEvolution method
*	Asks the evolution observer to return its next evolution. Performs all necessary arrangements to shift the different attributes from the evolution to the existant pokemon.
*	parameters
*		shared_ptr<EvolutionObserver> obs : observer asked to return the evolution.
*	no return statement
*/
void Pokemon::requestEvolution(shared_ptr<EvolutionObserver> obs)
{
   /* TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO */
   shared_ptr<Pokemon> pok = obs->returnEvolution(get<1>(*_evolution));
   string s;
   char* cstr = new char[_name.length()+1];
   strcpy(cstr, _name.c_str());
   strtok(cstr,"|");
   s = strtok(NULL,"|");
   delete cstr;

   _number = pok->_number;
   cout << "Amazing ! " << _name << " evolves in ";
   _name = pok->_name+"|"+s;
   cout << _name << endl;
   _xpCategory = pok->_xpCategory;
   _type1 = pok->_type1;
   _type2 = pok->_type2;
   _evolution = pok->_evolution;
   _attackList = pok->_attackList;
   _base = pok->_base;

   _baseHP = pok->_baseHP;
   _baseAttack = pok->_baseAttack;
   _baseDefense = pok->_baseDefense;
   _baseSpeed = pok->_baseSpeed;
   _baseSpe_attack = pok->_baseSpe_attack;
   _baseSpe_defense = pok->_baseSpe_defense;
   _baseXP = pok->_baseXP;

   _evsToGive = pok->_evsToGive;

   pok.reset();
}

/*	addXPObserver methpd
*	Assign obs to the xpObserver attribute.
*	parameters
*		shared_ptr<XPObserver> obs : observer that will be assigned to xpObs.
*	no return statement
*/
void Pokemon::addXPObserver(shared_ptr<XPObserver> obs)
{
   _xpObs = obs;
   needXPLimit(_xpObs);
}

/*	removeXPObserver method
*	Reset the observer.
*	parameters
*		shared_ptr<XPObserver> obs : observer that will be reset.
*	no return statement
*/
void Pokemon::removeXPObserver(shared_ptr<XPObserver> obs)
{
   _xpObs.reset();
}

/*	needXPLimit method
*	Request then next xp limit to the observer
*	parameters
*		shared_ptr<XPObserver> obs : observer asked to return the next xp limit.
*	no return statement
*/
void Pokemon::needXPLimit(shared_ptr<XPObserver> obs)
{
   _xpLimit = obs->getNextXPLimit(_lvl, *_xpCategory);
}
