/* file : type.cpp 
*	This file implements the methods in the the type.hpp file.
*	johann.novak25@gmail.com
*	15/03/14
*/

#include <type.hpp>

using namespace std;

/* Constructors   */

/*	Default constructor	*/
Type::Type(){}

/*	Copy constructor	*/
Type::Type(Type const& type):_stringType(type._stringType),_enumType(type._enumType),_resistantTo(type._resistantTo),_weakTo(type._weakTo),_immuneTo(type._immuneTo),_efficientOn(type._efficientOn),_notEfficientOn(type._notEfficientOn),_inefficientOn(type._inefficientOn){}

/*	Constructor that is used to create a type and its enum	*/
Type::Type(string type):_stringType(type)
{
   if(type == "GRASS")
      _enumType = enumType::GRASS;
  else if(type == "FIRE")
     _enumType = enumType::FIRE;
  else if(type == "WATER")
     _enumType = enumType::WATER;
  else if(type == "ELECTRIC")
     _enumType = enumType::ELECTRIC;
  else if(type == "POISON")
     _enumType = enumType::POISON;
  else if(type == "ROCK")
     _enumType = enumType::ROCK;
  else if(type == "GROUND")
     _enumType = enumType::GROUND;
  else if(type == "NORMAL")
     _enumType = enumType::NORMAL;
  else if(type == "GHOST")
     _enumType = enumType::GHOST;
  else if(type == "FIGHTING")
     _enumType = enumType::FIGHTING;
  else if(type == "FLYING")
     _enumType = enumType::FLYING;
  else if(type == "PSYCHIC")
     _enumType = enumType::PSYCHIC;
  else if(type == "ICE")
     _enumType = enumType::ICE;
  else if(type == "BUG")
     _enumType = enumType::BUG;
  else if(type == "DARK")
     _enumType = enumType::DARK;
  else if(type == "DRAGON")
     _enumType = enumType::DRAGON;
}

/*	Destructor	*/
Type::~Type()
{
   _weakTo.clear();
   _immuneTo.clear();
   _resistantTo.clear();
   _efficientOn.clear();
   _notEfficientOn.clear();
   _inefficientOn.clear();
}

/* Getters and Setters  */
string Type::getName()
{
   return _stringType;
}
enumType Type::getEnum()
{
   return _enumType;
}
set<string> Type::getWeak()
{
   return _weakTo;
}
set<string> Type::getResistant()
{
   return _resistantTo;
}
set<string> Type::getImmune()
{
   return _immuneTo;
}
set<string> Type::getEfficient()
{
   return _efficientOn;
}
set<string> Type::getNotEfficient()
{
   return _notEfficientOn;
}
set<string> Type::getInefficient()
{
   return _inefficientOn;
}
/* Operators   */

/*	= operator */
Type& Type::operator=(Type const& type)
{
   _stringType = type._stringType;
   _enumType = type._enumType;
   _weakTo = type._weakTo;
   _resistantTo = type._resistantTo;
   _immuneTo = type._immuneTo;
   _efficientOn = type._efficientOn;
   _notEfficientOn = type._notEfficientOn;
   _inefficientOn = type._inefficientOn;

   return (*this);
}

/*	<< operator	*/
ostream& operator<<(ostream& o, Type type)
{
   o << "Type " << type.getName() << " " << type.getEnum() << endl;
   o << "-------------------------------" << endl;
   o << "weak to ";
   if(!type.getWeak().empty())
      for(set<string>::iterator it=type.getWeak().begin(); it!=type.getWeak().end(); ++it)
         o << (*it) << "/";
   o << endl;

   return o;
}

/*	add*** methods
*	Add a Type to the **** set.
*	parameters
*		string type : string name of the Type.
*	no return statement
*/
void Type::addWeak(string type)
{
   _weakTo.insert(type);
}
void Type::addResistant(string type)
{
   _resistantTo.insert(type);
}
void Type::addImmune(string type)
{
   _immuneTo.insert(type);
}
void Type::addEfficient(string type)
{
   _efficientOn.insert(type);
}
void Type::addNotEfficient(string type)
{
   _notEfficientOn.insert(type);
}
void Type::addInefficient(string type)
{
   _inefficientOn.insert(type);
}
