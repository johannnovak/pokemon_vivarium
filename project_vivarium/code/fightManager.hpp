/* file : fightManager.hpp 
*	This file contains the header of the fightManager.cpp file.
*	This class manages fights, it starts them, it performs turn, and end them. All of these actions are runned inside a thread.
*	johann.nova25@gmail.com
*	15/03/14
*/

#ifndef FIGHTMANAGER_HPP
#define FIGHTMANAGER_HPP

#include <fstream>
#include <thread>
#include <mutex>
#include <list>

#include <fight.hpp>
#include <pokemon.hpp>
#include <xpObserver.hpp>
#include <rapidxml.hpp>

class SceneManager;
class FightManager: public XPObserver
{
   private:
		/*	Attributes	*/
		std::list<std::shared_ptr<Fight>> _fights;		/*	vector of pointer on the different fights occuring */
		short _nbFight;			/*	number of fight on the moment	(size of the vector /^)	*/
      std::map<short,std::shared_ptr<long>> _fast;		/*	map that wil contain all the xp according to the levels 1 to 100 and the fast xp category	*/
      std::map<short,std::shared_ptr<long>> _mediumFast;		/*	map that wil contain all the xp according to the levels 1 to 100 and the medium fast xp category	*/
      std::map<short,std::shared_ptr<long>> _mediumSlow;		/*	map that wil contain all the xp according to the levels 1 to 100 and the medium slow xp category	*/
      std::map<short,std::shared_ptr<long>> _slow;		/*	map that wil contain all the xp according to the levels 1 to 100 and the slow xp category	*/
      std::shared_ptr<SceneManager> _scene;				/*	pointer on the sceneManager	*/
		short _nbDeadPokemon;			/*	number of dead pokemon from the beginning	*/

      /* Observer methods  */
		/*	getNextXPLimit method
		*	Returns the amount of xp required to lvl up according to the level and the category
		*	parameters.
		*		short lvl : level of the pokemon making the request.
		*		string cat : category of the pokemon making the request.
		*	return 
		*		the amount of xp needed to lvl up as a long.
		*/
      std::shared_ptr<long> getNextXPLimit(short lvl, std::string cat);
   public:
      /* Constructors */
      FightManager();									/*	default constructor	*/
      FightManager(FightManager const& fight);	/*	Copy constructor	*/
      FightManager(SceneManager scene);			/*	Constructor that define the sceneManager	*/

      ~FightManager();	/*	Destructor	*/

      /* Getters and Setters  */
      std::map<short, std::shared_ptr<long>> getSlow();
      std::map<short, std::shared_ptr<long>> getMediumSlow();
      std::map<short, std::shared_ptr<long>> getFast();
      std::map<short, std::shared_ptr<long>> getMediumFast();
      std::shared_ptr<SceneManager> getScene();
		std::list<std::shared_ptr<Fight>> getFights();
		short getNbDeadPokemon();
		short getNbFight();

      void setScene(std::shared_ptr<SceneManager> scene);

      /* Operators   */
      FightManager& operator=(FightManager const& fight);	/*	= operator	*/

      /* Methods   */
		
		/*	parseXP method
		*	Parse the xp tables (fast, medium fast, medium slow, slow) from the file /xml/xp.xml
		*	no parameters
		*	no return statement
		*/
      void parseXP();

		/*	addFight method
		*	Add a fight to the vector of fights occuring.
		*	parameters
		*		shared_ptr<Pokemon> pok1 : pointer of Pokemon pointing on one of the two pokemon that will participate in the battle
		*		shared_ptr<Pokemon> pok2 : pointer of Pokemon pointing on one of the two pokemon that will participate in the battle
		*	no return statement
		*/
      void addFight(std::shared_ptr<Pokemon> pok1, std::shared_ptr<Pokemon> pok2);

		/*	printXPTable method
		*	Prints the xp table of all the categories
		*/
      void printXPTable();

		/*	run method
		*	Start the thread that will start to :
		*		-> begin fights 
		*		-> start turns of fights not over  
		*		->	remove fights that are over
		*	no parameters
		*	no return statement
		*/
		void run();
};
#include <sceneManager.hpp>
#endif
