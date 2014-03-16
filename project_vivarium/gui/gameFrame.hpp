/* file : gameFrame.hpp  
*	This file is the header of the gameFrame.cpp file.
*	This class contains the window where will be printed the tilemap, the pokemons and various informations.
*	johann.novak25@gmail.com
*	16/03/14
*/

#ifndef GAMEFRAME_HPP
#define GAMEFRAME_HPP

#include <mutex>
#include <sstream>
#include <fstream>

#include <tileMap.hpp>
#include <statFrame.hpp>

#define TILE_SIZE 16			/*	defines the size of the tiles	*/
#define SCREEN_MOVE 50		/*	defines the number of pixel we move when we move the camera	*/
#define ABOVE_POKEMON 10	/*	define the number of pixel the satus will be shown above the pokemon's sprite	*/
#define STATUS_LVL_CHAR_SIZE 10  	/*	defines the size of the font of the status above the pokemon	*/

class GameFrame
{
   private:
      sf::RenderWindow _window;	/*	GameWindow	*/
		StatFrame _statFrame;		/*	cindow containing the statistics of every pokemons	*/
		sf::RenderTexture _target;	/*	spritebatch that is drawn every updates	*/
		sf::Sprite _targetSprite;	/*	sprite of the spriteBatch	*/
		short* _level;					/*	array of short defining the tilemap (each number is associated to a tile)	*/
		short _tileWidthNb;			/*	number of tiles in width	*/
		short _tileHeightNb;			/*	number of tiles in height	*/
      TileMap _gameMap;				/*	tilemap of the window	*/
      sf::Vector2i _mousePos;		/*	position of the mouse	*/
		bool _hasFocus;				/*	if the window has focus or not	*/	
      std::shared_ptr<SceneManager> _scene;		/*	pointer on the sceneManager	*/
      sf::Clock _clock;				/*	clock needed for the update	*/
		short _quit;					/*	tells if the the window needs to close	*/
		short _sceneSpeed;			/*	speed of the scene	*/
		float _scaleRatio;			/*	ratio of the scale	*/
		bool _continuePop;			/*	if pokemons continue to pop or not	*/
   	std::map<short, std::vector<sf::Texture>> _pokemonSprites;		/*	map contianing the sprites of all pokemons	*/
		sf::RectangleShape _bg;		/*	rectangle corresponding to the total life of the pokemon	*/
		sf::RectangleShape _fg;		/*	rectangle corresponding to the current life of the pokemon 	*/

		sf::Font _font;				/*	font used for texts	*/
		sf::Text _upRightText;		/*	text that will be drawn on the top right corner	*/
		sf::Text _pokLvl;				/*	text drawn when a pokemon's show status is set to true	*/

		sf::Texture _evolutionTexture1;		/*	texture of the evolution animation	*/
		sf::Texture _evolutionTexture2;		/*	texture of the evolution animation	*/
		sf::Texture _evolutionTexture3;		/*	texture of the evolution animation	*/
		sf::Texture _evolutionTexture4;		/*	texture of the evolution animation	*/
		sf::Texture _evolutionTexture5;		/*	texture of the evolution animation	*/
		sf::Texture _evolutionTexture6;		/*	texture of the evolution animation	*/
		sf::Texture _evolutionTexture7;		/*	texture of the evolution animation	*/
		sf::Texture _evolutionTexture8;		/*	texture of the evolution animation	*/
		sf::Texture _evolutionTexture9;		/*	texture of the evolution animation	*/
		sf::Texture _evolutionTexture10;		/*	texture of the evolution animation	*/
		sf::Sprite _evolutionSprite;			/*	sprite of the evolution animation	*/

   public:
      /* Constructors   */
      GameFrame();		/*	Default constructor	*/
      GameFrame(GameFrame const& frame),		/*	Copy constructor	*/
      ~GameFrame();		/*	Destructor	*/
	
		/*	Getters and Setters	*/
   	std::map<short, std::vector<sf::Texture>> getPokemonSprites();

      /* Methods  */

		/*	start meethod
		*	Launches the gameFrame. Loads all texture, tilemap, etc ... Starts the thread of the window.
		*	no parameters
		*	return
		*		a value telling if the window has exited normally.
		*/
      short start();

		/*	close method
		*	Closes the window.
		*	no parameters
		*	no return statement
		*/
      void close();

		/*	timeForNewPokemon method
		*	Tests if it is time to make a pokemon pop on the map. Asks factory to create a new pokemon.
		*	no parameters
		*	no return statement
		*/
		void timeForNewPokemon();

		/* createMap mathod
		*	Creates a random map. TODO
		*	no parameters
		*	no return statement
		*/
      void createMap();

		/*	parseMap method
		*	Parses the map from the /map/map1.txt
		*	no parameters
		*	no return statement
		*/
		void parseMap();	

		/*	handleKeyInput method
		*	Handles key input :
		*	->	Arrows to move the camera.
		*	->	SPACE to change the value of the pop of the pokemons.
		*	->	PAGEUP/PAGEDOWN to change the ratio of the scale.
		*	->	+/- on the numeric pad to increase or decrease the speed of the scene.
		*	->	ENTER to quit
		*	no parameters
		*	no return statement
		*/
		void GameFrame::handleKeyInput();

		/*	handleMouseInput method
		*	Handles mouse input. If left click on a pokemon, show status turned to true.
		*	no parameters
		*	no return statement
		*/
		void handleMouseInput();


};
#endif
