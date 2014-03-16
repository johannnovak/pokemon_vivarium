/* file : type.hpp 
*	This file is the header of the type.cpp file.
*	This class defines the conept of Type in the pokemon game.
*	johann.novak25@gmail.com
*	15/03/14
*/

#ifndef TYPE_HPP
#define TYPE_HPP

#include <set>
#include <string>
#include <iostream>

/*	enum containing all the types of Pokemon	*/
enum enumType
{
   GRASS,
   FIRE,
   WATER,
   ELECTRIC,
   POISON,
   ROCK,
   GROUND,
   NORMAL,
   GHOST,
   FIGHTING,
   FLYING,
   PSYCHIC,
   ICE,
   BUG,
   DARK,
   DRAGON
};

class Type 
{
   private:
		/*	Attributes	*/
      std::string _stringType;		/*	name of the type in string	*/
      enumType _enumType;				/*	name of the type in enum	*/
      std::set<std::string> _weakTo;			/*	set of string defining the weaknesses of the type	*/
      std::set<std::string> _resistantTo;		/*	set of string definign the types to which it is resistant	*/
      std::set<std::string> _immuneTo;			/*	set of string defining the type it is immune to	*/
      std::set<std::string> _efficientOn;		/*	set of string defining the types against whoch it is efficient	*/
      std::set<std::string> _notEfficientOn;		/*	set of string defining the types against whoch it is not efficient	*/
      std::set<std::string> _inefficientOn;	/*	set of string defining the types against whoch it is inefficient	*/

   public:
      /* Constructors   */
      Type();							/*	Default Constructor	*/
      Type(Type const& type);		/*	Copy Constructor	*/
      Type(std::string type);		/*Constructor that defines its name with a string	*/

      ~Type();				/*	Destructor	*/

     /* Getters and Setters  */
      std::string getName();
      enumType getEnum();
      std::set<std::string> getWeak();
      std::set<std::string> getResistant();
      std::set<std::string> getImmune();
      std::set<std::string> getEfficient();
      std::set<std::string> getNotEfficient();
      std::set<std::string> getInefficient();
      /* Operator */
      Type& operator=(Type const& type);		/*	= operator	*/
      friend std::ostream& operator<<(std::ostream& o, Type type);		/*	<< operator	*/

      /* Methods   */

		/*	add*** methods
		*	Add a Type to the **** set.
		*	parameters
		*		string type : string name of the Type.
		*	no return statement
		*/
      void addWeak(std::string type);		
      void addResistant(std::string type);
      void addImmune(std::string type);
      void addEfficient(std::string type);
      void addNotEfficient(std::string type);
      void addInefficient(std::string type);	
};
#endif
