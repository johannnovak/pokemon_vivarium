/* file : attack.hpp   
 * This file is the header of the attack.cpp file.
 * This class defines the concept of an attack that a pokemon can do when he battles.
 *	johann.novak25@gmail.com
 * 15/03/14
 */

#ifndef ATTACK_HPP
#define ATTACK_HPP

#include <memory> 
#include <iostream>

#include <type.hpp>

class Attack
{
   private :
		/*	Attributes	*/
		
      std::string _name;				/*	name of the attack	*/
      std::string _category;			/*	string associated with the type of the attack	*/
      short _power;						/*	power of the attack	*/
      short _accuracy;					/*	accuracy of the attack	*/
      short _pp;							/*	pp of the attack	*/
      std::shared_ptr<Type> _type;	/*	type of the attack	*/
   public :
      /* Constructors   */
      Attack();							/*	Default constructor	*/
      Attack(Attack const& attack);	/*	Copy constructor	*/
      /*	Constructor used to create the attack with specific parameters
 *	parameters
 *		string name : name of the attack
 *		string category	: string associated with the category of the pokemon attack
 *		short power : power of the attack
 *		accuracy : accuracy of the attack
 *		shared_ptr<Type> type : type of the attack
 *		short pp : points of power of the attack
 */
		Attack(std::string name,std::string category, short power, short accuracy, std::shared_ptr<Type> type, short pp);		

      ~Attack();		/* Destructor	*/

      /* Getters and Setters  */
      std::string getName();
      std::string getCategory();
      short getPower();
      short getAccuracy();
      short getPP();
      std::shared_ptr<Type> getType();
   
      /* Operators   */
      Attack& operator=(Attack const& attack);	/*	= operator	*/
      friend std::ostream& operator<<(std::ostream& o, Attack a);	/*	<< operator	*/
};
#endif
