/*	file : statFrame.cpp
*	This file implements the methods in the statFrame.cpp file.
*	johann.nova25@gmail.com
*	16/03/14
*/


#include <statFrame.hpp>

using namespace std;
using namespace sf;

/*	Constructors	*/

/*	Default Constructor	*/
StatFrame::StatFrame()
{
	_window.create(VideoMode(VideoMode::getDesktopMode().width/2,VideoMode::getDesktopMode().height/2), "Vivarium statistics", Style::Titlebar);
	_targetHeader.create(_window.getSize().x,_window.getSize().y*HEADER_DELIMITATION);
	_targetPokemonList.create(_window.getSize().x,LIST_MOVE*AVG_POKEMON_NB*2);
	_quit = false;

	_font.loadFromFile("./gui/arial.ttf");
	_evolutionNb = 0;
	_maxLvl = 0;
	
	_header1.setPosition(_window.getSize().x/30,10);
	_header1.setCharacterSize(15);
	_header1.setFont(_font);
	_header1.setStyle(Text::Bold);
	_header1.setColor(Color::Black);

	_header2.setPosition(_window.getSize().x*17/30, 10);
	_header2.setCharacterSize(15);
	_header2.setFont(_font);
	_header2.setStyle(Text::Bold);
	_header2.setColor(Color::Black);

	_targetPokemonListSprite.setPosition(0, _window.getSize().y*HEADER_DELIMITATION);

	_bg.setSize(Vector2f(HP_BAR_LENGTH,HP_BAR_WIDTH));
	_bg.setOutlineColor(Color::Black);
	_bg.setOutlineThickness(2);
	_bg.setFillColor(Color::Red);

	_fg.setFillColor(Color::Green);
	
	_best.setRadius(HP_BAR_WIDTH/2);
	_best.setFillColor(Color::Red);

	_bestSeeker.setSize(Vector2f(HP_BAR_WIDTH*3/4,4));
	_bestSeeker.setFillColor(Color::Red);
}

/*	Copy constructor	*/
StatFrame::StatFrame(StatFrame const& sframe){}

/*	Destructor	*/
StatFrame::~StatFrame()
{
}

/*	Getters and Setters	*/
short StatFrame::getMaxLvl()
{
	return _maxLvl;
}

/*	Operators	*/

/*	= operator	*/
StatFrame& StatFrame::operator=(StatFrame const& sframe)
{
	return *this;
}

/*	methods	*/

/*	update method	
*	Updates the window with the new values of the sceneManager.
*	parameters
*		shared_ptr<SceneManager> scene : sceneManager that contains all the necessary informations.
*	no return statement
*/
void StatFrame::update(shared_ptr<SceneManager> scene)
{
	/*	Clear view	*/
	_window.clear(Color::White);
	_targetHeader.clear(Color::White);
	_targetPokemonList.clear(Color::White);

	/*	Sets string's values	*/
	_header1String = "Number of Pokemon on the map : "+to_string(scene->getPokemons()->size())+
	"\nNumber of evolved Pokemon on the map : "+to_string(_evolutionNb)+
	"\n\n\t\t ***********************************************************************"+
	"\n\t\tName\t\t\t\t\t  Level\t\t\t HP";
	_header2String = "Maximum level on the map : "+to_string(_maxLvl)+
	"\nNumber of dead Pokemon : "+to_string(scene->getFightManager1()->getNbDeadPokemon()+scene->getFightManager2()->getNbDeadPokemon());
	_header1.setString(_header1String);
	_header2.setString(_header2String);

	if(Keyboard::isKeyPressed(Keyboard::Numpad8))
	{
		if(_targetPokemonListSprite.getOrigin().y > 0)
		{
			_targetPokemonListSprite.setOrigin(_targetPokemonListSprite.getOrigin().x,_targetPokemonListSprite.getOrigin().y-LIST_MOVE);
		}
	}
	else if(Keyboard::isKeyPressed(Keyboard::Numpad2))
	{
		if(_targetPokemonListSprite.getOrigin().y < _lastPokemonPosition);
		{
			_targetPokemonListSprite.setOrigin(_targetPokemonListSprite.getOrigin().x,_targetPokemonListSprite.getOrigin().y+LIST_MOVE);
		}
	}

	if(!_pokemonNames.empty())
	{
		for(short i(0); i < scene->getPokemons()->size(); ++i)
		{
			_pokemonLvls[i].setString(to_string(scene->getPokemons()->at(i)->getLvl()));
			if(_pokemonLvls[i].getString().toAnsiString().compare(to_string(_maxLvl)) == 0)
				_best.setPosition(_pokemonNames[i].getPosition().x-35, _pokemonNames[i].getPosition().y+3);
			if(_best.getPosition().y < _targetPokemonListSprite.getOrigin().y)
				_bestSeeker.setPosition(_best.getPosition().x,_targetPokemonListSprite.getOrigin().y+10);
			else if(_best.getPosition().y > _targetPokemonListSprite.getPosition().y+_targetPokemonListSprite.getOrigin().y)
				_bestSeeker.setPosition(_best.getPosition().x,_targetPokemonListSprite.getPosition().y+_window.getSize().y-_window.getSize().y);
			if(!scene->getPokemons()->at(i)->isBase())
			{
				_pokemonNames[i].setString(scene->getPokemons()->at(i)->getName());
				if(scene->getPokemons()->at(i)->isFinalEvolution())
					_pokemonNames[i].setColor(Color::Red);
				else
					_pokemonNames[i].setColor(Color::Blue);
			}
			_targetPokemonList.draw(_pokemonNames[i]);
			_targetPokemonList.draw(_pokemonLvls[i]);
			_bg.setPosition(_pokemonLvls[i].getPosition().x+BETWEEN_LVL_HP_SPACE, _pokemonLvls[i].getPosition().y);
			_fg.setPosition(_bg.getPosition());
			_fg.setSize(Vector2f(scene->getPokemons()->at(i)->getCurrentHP()*HP_BAR_LENGTH/scene->getPokemons()->at(i)->getHP(),HP_BAR_WIDTH));
			_targetPokemonList.draw(_bg);
			_targetPokemonList.draw(_fg);
		}
	}
	_targetPokemonList.draw(_best);
	_targetPokemonList.draw(_bestSeeker);
	_targetPokemonList.display();
	_targetHeader.draw(_header1);
	_targetHeader.draw(_header2);
	_targetHeader.display();

	_targetPokemonListSprite.setTexture(_targetPokemonList.getTexture());
	_window.draw(_targetPokemonListSprite);
	_targetHeaderSprite.setTexture(_targetHeader.getTexture());
	_window.draw(_targetHeaderSprite);
	_window.display();
}

/*	updateEvolution method
*	Assigns the number in parameter to the _evolutionNumber in atribute.	
*	parameters
*		short number : number of evolution.
*	no return statement
*/
void StatFrame::updateEvolutionNb(short nb)
{
	_evolutionNb = nb;
}

/*	updateMaxLevel method
*	Assigns the number in parameter to the _maxLvl attribute.
*	parameters
*		short nb : max level on the map.
*	no return statement
*/
void StatFrame::updateMaxLvl(short nb)
{
	_maxLvl = nb;
}

/*	addPokemonList method	
*	Adds a new pokemon to the list.
*	parameters
*		shared_ptr<Pokemon> pok : pokemon whose values need to be added to the list.
*	no return statement
*/
void StatFrame::addPokemonList(shared_ptr<Pokemon> pok)
{
	Text tempName;
	Text tempLvl;

	/*	setting the name of the new pokemon	*/
	if(_pokemonNames.empty())
		tempName.setPosition(50, 10);
	else
		tempName.setPosition(_pokemonNames.back().getPosition().x, _pokemonNames.back().getPosition().y+BETWEEN_LINE_SPACE);
	tempName.setCharacterSize(15);
	tempName.setFont(_font);
	tempName.setStyle(Text::Bold);
	tempName.setColor(Color::Black);
	tempName.setString(pok->getName());

	_pokemonNames.push_back(tempName);

	/*	setting the lvl of the new pokemon	*/
	if(_pokemonLvls.empty())
		tempLvl.setPosition(20+BETWEEN_NAME_LVL_SPACE, 10);
	else
		tempLvl.setPosition(_pokemonLvls.back().getPosition().x, _pokemonLvls.back().getPosition().y+BETWEEN_LINE_SPACE);
	tempLvl.setCharacterSize(15);
	tempLvl.setFont(_font);
	tempLvl.setStyle(Text::Bold);
	tempLvl.setColor(Color::Black);
	tempLvl.setString(to_string(pok->getLvl()));

	_pokemonLvls.push_back(tempLvl);
	_lastPokemonPosition = _pokemonNames.back().getPosition().y;
}

/*	removePokemonList method
*	Removes the pokemons in the list which has the attribute hasToBeRemoved to true.
*	parameters
*		shared_ptr<SceneManager> scene : sceneManager where we will be able to get the attributes of each pokemon.
*	no return statement
*/
void StatFrame::removePokemonList(shared_ptr<SceneManager> scene)
{
	short j(0);
	for(short i = 0; i < scene->getPokemons()->size(); ++i)
	{
		if(scene->getPokemons()->at(i)->hasToBeRemoved())
		{
			_pokemonNames.erase(_pokemonNames.begin()+i+j);
			_pokemonLvls.erase(_pokemonLvls.begin()+i+j);
			++j;
			for(short k = i; k < _pokemonNames.size(); ++k)
				_pokemonNames[k].setPosition(_pokemonNames[k].getPosition().x, _pokemonNames[k].getPosition().y-BETWEEN_LINE_SPACE);
			for(short k = i; k < _pokemonLvls.size(); ++k)
				_pokemonLvls[k].setPosition(_pokemonLvls[k].getPosition().x, _pokemonLvls[k].getPosition().y-BETWEEN_LINE_SPACE);
		}
	}
	_lastPokemonPosition = _pokemonNames.back().getPosition().y;
}
