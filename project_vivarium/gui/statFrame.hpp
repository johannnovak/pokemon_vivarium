/*	file : statFrame.hpp
*	This file is the header of the statFrame.cpp file.
*	This class is a window that is composed of a list of all the pokemons on the map, and severall informations.
*	johann.nova25@gmail.com
*	16/03/14
*/

#ifndef STATFRAME_HPP
#define STATFRAME_HPP

#include <vector>
#include <memory>
#include <string>

#include <SFML/Graphics.hpp>
#include <sceneManager.hpp>

#define BETWEEN_LINE_SPACE 20			/*	number of pixels between the top of the screen and the first pokemon	*/
#define BETWEEN_NAME_LVL_SPACE 200	/*	number of pixel between the level and the name	*/
#define BETWEEN_LVL_HP_SPACE 50		/*	number of pixel between the lvl and the hp	*/
#define HP_BAR_LENGTH 100				/*	length of the HP bar	*/
#define HP_BAR_WIDTH 12					/*	width of the hp var	*/
#define HEADER_DELIMITATION 0.27		/*	ratio of the window that seperates the iunformation and the list of pokemons	*/
#define LIST_MOVE 30			/*	the number of pixel the list will move	*/
#define AVG_POKEMON_NB 110	/*	average number of pokemon on the map	*/

class StatFrame
{
	private:
		/*	Attributes	*/
		sf::RenderWindow _window;			/*	window	*/
		sf::RenderTexture _targetHeader;		/*	header with the different informations	*/
		sf::Sprite _targetHeaderSprite;		/*	sprite of the texture /^	*/
		sf::RenderTexture _targetPokemonList;		/*	texture containing the list of all the pokemons	*/
		sf::Sprite _targetPokemonListSprite;		/*	sprite of the texture /^	*/

		bool _quit;		/*	tests if the windeow has to close or not	*/
		std::vector<sf::Text> _pokemonNames;		/*	vector of all the names of the pokemons on the screen	*/
		std::vector<sf::Text> _pokemonLvls;			/*	vector of all the levels of the pokemons on the screen	*/
		sf::Text _header1;		/*	text of the left in the header */
		sf::Text _header2;		/*	text of the right in the header	*/
		std::string _header1String;		/*	value of _header1	*/
		std::string _header2String;		/*	value of _header2	*/
		sf::Font _font;			/*	font */
		float _lastPokemonPosition;		/*	position of the last pokemon line drawn	*/

		sf::RectangleShape _bg;		/*	background of the hp bar	*/	
		sf::RectangleShape _fg;		/*	foreground of the hp bar	*/
		sf::CircleShape _best;		/*	highest level pokemon	*/
		sf::RectangleShape _bestSeeker;		/*	point indicating hte best pokemon	*/
		short _evolutionNb;		/*	number of evolution on the map	*/
		short _maxLvl;				/*	maximum level on the map	*/

	public:
		/*	Constructors and destructor	*/
		StatFrame();		/*	Default constructor	*/
		StatFrame(StatFrame const& sframe);		/*	Copy constructor	*/
		~StatFrame();		/*	Destructor	*/

		/*	Getters and Setters	*/
		short getMaxLvl();
		
		/*	Operators	*/
		StatFrame& operator=(StatFrame const& sframe);		/*	= operator	*/

		/* Methods	*/

		/*	update method	
		*	Updates the window with the new values of the sceneManager.
		*	parameters
		*		shared_ptr<SceneManager> scene : sceneManager that contains all the necessary informations.
		*	no return statement
		*/
		void update(std::shared_ptr<SceneManager> scene);

		/*	updateEvolution method
		*	Assigns the number in parameter to the _evolutionNumber in atribute.	
		*	parameters
		*		short number : number of evolution.
		*	no return statement
		*/
		void updateEvolutionNb(short nb);

		/*	updateMaxLevel method
		*	Assigns the number in parameter to the _maxLvl attribute.
		*	parameters
		*		short nb : max level on the map.
		*	no return statement
		*/
		void updateMaxLvl(short nb);

		/*	addPokemonList method	
		*	Adds a new pokemon to the list.
		*	parameters
		*		shared_ptr<Pokemon> pok : pokemon whose values need to be added to the list.
		*	no return statement
		*/
		void addPokemonList(std::shared_ptr<Pokemon> pok);

		/*	removePokemonList method
		*	Removes the pokemons in the list which has the attribute hasToBeRemoved to true.
		*	parameters
		*		shared_ptr<SceneManager> scene : sceneManager where we will be able to get the attributes of each pokemon.
		*	no return statement
		*/
		void removePokemonList(std::shared_ptr<SceneManager> scene);
};
#endif
