/* file : attack.cpp   
 * This file implements the several constructors and methods written in the attack.hpp file.
 i	johann.novak25@gmail.com
 * 15/03/14
 */

#include <attack.hpp>

using namespace std;

/* Constructors   */
/*	Default Constructor	*/
Attack::Attack(){}

/*	Copy Constructor	*/
Attack::Attack(Attack const& attack):_name(attack._name),_category(attack._category), _power(attack._power),_accuracy(attack._accuracy),_type(attack._type),_pp(attack._pp){}

/*	Constructor used to create the attack with specific parameters
 *	parameters
 *		string name : name of the attack
 *		string category	: string associated with the category of the pokemon attack
 *		short power : power of the attack
 *		accuracy : accuracy of the attack
 *		shared_ptr<Type> type : type of the attack
 *		short pp : points of power of the attack
 */
Attack::Attack(string name, string category, short power, short accuracy, shared_ptr<Type> type, short pp):_name(name),_category(category),_power(power),_accuracy(accuracy),_type(type),_pp(pp){}

/*	Destructor	*/
Attack::~Attack()
{
   _type.reset();
}

/* Getters and Setters  */
string Attack::getName()
{
   return _name;
}
string Attack::getCategory()
{
   return _category;
}
short Attack::getPower()
{
   return _power;
}
short Attack::getAccuracy()
{
   return _accuracy;
}
shared_ptr<Type> Attack::getType()
{
   return _type;
}
/* Operators   */
/*	= operator	*/
Attack& Attack::operator=(Attack const& attack)
{
   _name = attack._name;
   _category = attack._category;
   _power = attack._power;
   _accuracy = attack._accuracy;
   _type = attack._type;
   _pp = attack._pp;

   return *this;
}

/*	<< operator	*/
ostream& operator<<(ostream& o, Attack a)
{  
   o << "Name : " << a.getName() << endl;
   return o;
}
