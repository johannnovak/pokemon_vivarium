/* file : gameFrame.cpp  
*	This file implements the methods defined in the gameFrame.cpp file.
*	johann.novak25@gmail.com
*	16/03/14
*/

#include <gameFrame.hpp>

using namespace std;
using namespace sf;

/*	Constructors	*/

/*	Default constructor	*/
GameFrame::GameFrame()
{
	srand(time(NULL));
	vector<shared_ptr<FightManager>>::iterator it;
   _window.create(VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height),"Pokemon vivarium", Style::Titlebar | Style::Close | Style::Resize);
	_window.setFramerateLimit(60);
   _scene = shared_ptr<SceneManager>(new SceneManager());
/*	it = _scene->getFightManager().begin();
	while(it != _scene->getFightManager().end())
	{
		(*it)->setScene(_scene);
		++it;
	}*/
	_scene->getFightManager1()->setScene(_scene);
	_scene->getFightManager2()->setScene(_scene);
	_hasFocus = true;
	_sceneSpeed = 1;
	_scaleRatio = 1;
	_continuePop = true;
	_quit = 0;

	_bg.setSize(Vector2f(20,5));
	_bg.setOutlineColor(Color::White);
	_bg.setOutlineThickness(2);
	_bg.setFillColor(Color::Red);

	_fg.setFillColor(Color::Green);

	_font.loadFromFile("./gui/arial.ttf");
	_upRightText.setPosition(VideoMode::getDesktopMode().width-200, 30);
	_upRightText.setCharacterSize(15);
	_upRightText.setFont(_font);
	_upRightText.setString("0");
	_upRightText.setStyle(Text::Bold);
	_upRightText.setColor(Color::Black);

	_pokLvl.setCharacterSize(STATUS_LVL_CHAR_SIZE);
	_pokLvl.setFont(_font);
	_pokLvl.setStyle(Text::Bold);
	_pokLvl.setColor(Color::Black);
}

/*	Destructor	*/
GameFrame::~GameFrame()
{
   _scene.reset();
	delete[](_level);
	_pokemonSprites.clear();
}

/* Methods  */

/*	start meethod
*	Launches the gameFrame. Loads all texture, tilemap, etc ... Starts the thread of the window.
*	no parameters
*	return
*		a value telling if the window has exited normally.
*/
short GameFrame::start()
{
   short quit(0);
	bool end(false);
	short k(0);
	short evolutionNb(0);
	short tempLvl(0);
	short time;
   short direction;
	short spriteNb(0);
	string text;
	shared_ptr<Pokemon> ptemp;
   Texture t0, t1, t2, t3, t4, t5, t6, t7;
	vector<Texture> vect;

	/*	loading of textures for the evolution animation	*/
	_evolutionTexture1.loadFromFile("./images/sprites/misc/evolution1.png");
	_evolutionTexture2.loadFromFile("./images/sprites/misc/evolution2.png");
	_evolutionTexture3.loadFromFile("./images/sprites/misc/evolution3.png");
	_evolutionTexture4.loadFromFile("./images/sprites/misc/evolution4.png");
	_evolutionTexture5.loadFromFile("./images/sprites/misc/evolution5.png");
	_evolutionTexture6.loadFromFile("./images/sprites/misc/evolution6.png");
	_evolutionTexture7.loadFromFile("./images/sprites/misc/evolution7.png");
	_evolutionTexture8.loadFromFile("./images/sprites/misc/evolution8.png");
	_evolutionTexture9.loadFromFile("./images/sprites/misc/evolution9.png");
	_evolutionTexture10.loadFromFile("./images/sprites/misc/evolution10.png");
	
	/*	loading of the 8 sprites for each pokemons	*/
   for(auto pok: _scene->getFactory()->getPokemons())
   {
      t0.loadFromFile("./images/sprites/pokemons/"+to_string(pok->getNumber())+"/"+to_string(pok->getNumber())+"_ur.png");
      t1.loadFromFile("./images/sprites/pokemons/"+to_string(pok->getNumber())+"/"+to_string(pok->getNumber())+"_ul.png");
      t2.loadFromFile("./images/sprites/pokemons/"+to_string(pok->getNumber())+"/"+to_string(pok->getNumber())+"_dr.png");
      t3.loadFromFile("./images/sprites/pokemons/"+to_string(pok->getNumber())+"/"+to_string(pok->getNumber())+"_dl.png");
      t4.loadFromFile("./images/sprites/pokemons/"+to_string(pok->getNumber())+"/"+to_string(pok->getNumber())+"_lr.png");
      t5.loadFromFile("./images/sprites/pokemons/"+to_string(pok->getNumber())+"/"+to_string(pok->getNumber())+"_ll.png");
      t6.loadFromFile("./images/sprites/pokemons/"+to_string(pok->getNumber())+"/"+to_string(pok->getNumber())+"_rr.png");
      t7.loadFromFile("./images/sprites/pokemons/"+to_string(pok->getNumber())+"/"+to_string(pok->getNumber())+"_rl.png");
		vect.push_back(t0);
		vect.push_back(t1);
		vect.push_back(t2);
		vect.push_back(t3);
		vect.push_back(t4);
		vect.push_back(t5);
		vect.push_back(t6);
		vect.push_back(t7);
		_pokemonSprites[pok->getNumber()] = vect;
		vect.clear();
   }

	/*	parsing map.txt	*/
	parseMap();
	/*	creating overall window with the size from the text file	*/
	_target.create(TILE_SIZE*_tileWidthNb,TILE_SIZE*_tileHeightNb);
	/* set the mapeight and mapWidth in the factory for the random pop position of pokemons	*/
	_scene->getFactory()->setMapWidth(_target.getSize().x);
	_scene->getFactory()->setMapHeight(_target.getSize().y);
	/*	create the tile map	*/
   if(!_gameMap.load("./images/sprites/map/map.png", Vector2u(TILE_SIZE,TILE_SIZE),_level, _tileWidthNb, _tileHeightNb))
      return 1;
   while(!_quit)
   {
		evolutionNb = 0;

		timeForNewPokemon();
		_scene->checkCollisions();

      Event event;
      
		if(_hasFocus)
		{
			while(_window.pollEvent(event))
			{
				switch(event.type)
				{
					case Event::Closed:
						_quit = 1;
						break;
					case Event::LostFocus:
/*						_hasFocus = false;*/
						break;
					case Event::GainedFocus:
						_hasFocus = true;
						break;
					case Event::KeyPressed:
						switch(event.key.code)
						{
							case Keyboard::Escape:
								_quit = 1;
								break;
							case Keyboard::Return:
								_quit = 1;
								break;
							case Keyboard::Space:
								if(_continuePop)
									_continuePop = false;
								else
									_continuePop = true;
								break;
							case Keyboard::Add:
								++_sceneSpeed;
								break;
							case Keyboard::Subtract:
								--_sceneSpeed;
								break;
							case Keyboard::PageUp:
								++_scaleRatio;
								break;	
							case Keyboard::PageDown:
								if(_scaleRatio != 1)
								{
									--_scaleRatio;
									if(_targetSprite.getOrigin().x+(_window.getSize().x+SCREEN_MOVE)/_scaleRatio > _target.getSize().x)
										_targetSprite.setOrigin(_target.getSize().x-_window.getSize().x/_scaleRatio, _targetSprite.getOrigin().y);
									if(_targetSprite.getOrigin().y+(_window.getSize().y+SCREEN_MOVE)/_scaleRatio > _target.getSize().y)
										_targetSprite.setOrigin(_targetSprite.getOrigin().x,_target.getSize().y-(_window.getSize().y+SCREEN_MOVE)/_scaleRatio);
								}
								break;
						}
						break;
         	}
      	}
		}
		
		handleKeyInput();
		handleMouseInput();


      _window.clear(Color::Black);
		_target.clear(Color::Black);
		_target.draw(_gameMap);

		_statFrame.removePokemonList(_scene);
		_scene->removePokemons();
		_scene->evolvePokemons();
		_scene->addPokemons();

      if(!_scene->getPokemons()->empty())
      {
			vector<shared_ptr<Pokemon>>::iterator pokt = _scene->getPokemons()->begin();
			tempLvl = 0;
			evolutionNb = 0;
         while(pokt != _scene->getPokemons()->end())
         {
				Sprite s;
				(*pokt)->updatePosition(_sceneSpeed);

				direction = static_cast<underlying_type<DIRECTION>::type>((*pokt)->getDirection());
				if(_sceneSpeed != 0 && fmod((*pokt)->getClock().getElapsedTime().asSeconds(),1) < 0.5)
					spriteNb = 1;
				else
					spriteNb = 0;
				s.setPosition(Vector2f((*pokt)->getX(),(*pokt)->getY()));
				s.setTexture(_pokemonSprites[(*pokt)->getNumber()][2*direction+spriteNb]);
				_target.draw(s);
				
				if((*pokt)->isFighting() | (*pokt)->showStatus())
				{
					_bg.setPosition((*pokt)->getX(), (*pokt)->getY()-ABOVE_POKEMON);
					_fg.setPosition((*pokt)->getX(), (*pokt)->getY()-ABOVE_POKEMON);
					_fg.setSize(Vector2f((*pokt)->getCurrentHP()*20/(*pokt)->getHP(),5));
					_target.draw(_bg);
					_target.draw(_fg);
				}
				if((*pokt)->showStatus())
				{
					_pokLvl.setString("lvl "+to_string((*pokt)->getLvl()));
					_pokLvl.setPosition((*pokt)->getX()-2, (*pokt)->getY()-ABOVE_POKEMON-STATUS_LVL_CHAR_SIZE-2);
					_target.draw(_pokLvl);
				}
				if((*pokt)->getEvolveTime())
				{
					_evolutionSprite.setPosition(Vector2f((*pokt)->left+(*pokt)->width/2-_evolutionSprite.getLocalBounds().width/2,(*pokt)->top+(*pokt)->height/2-_evolutionSprite.getLocalBounds().height/2));
					time = (*pokt)->getEvolveTime()->getElapsedTime().asMilliseconds();
					time = (time-(time%100));
					switch(time)
					{
						case 100:
							_evolutionSprite.setTexture(_evolutionTexture1);
							break;
						case 200:
							_evolutionSprite.setTexture(_evolutionTexture2);
							break;
						case 300:
							_evolutionSprite.setTexture(_evolutionTexture3);
							break;
						case 400:
							_evolutionSprite.setTexture(_evolutionTexture4);
							break;
						case 500:
							_evolutionSprite.setTexture(_evolutionTexture5);
							break;
						case 600:
							_evolutionSprite.setTexture(_evolutionTexture6);
							break;
						case 700:
							_evolutionSprite.setTexture(_evolutionTexture7);
							break;
						case 800:
							_evolutionSprite.setTexture(_evolutionTexture8);
							break;
						case 900:
							_evolutionSprite.setTexture(_evolutionTexture9);
							break;
						case 1000:
							_evolutionSprite.setTexture(_evolutionTexture10);
							break;
					}
					_target.draw(_evolutionSprite);
					if((*pokt)->getEvolveTime()->getElapsedTime().asSeconds() > 1)
						(*pokt)->stopEvolveTime();
				}
				
				if(!(*pokt)->isBase())
					++evolutionNb;
				if(tempLvl < (*pokt)->getLvl())
					tempLvl = (*pokt)->getLvl();
				
				pokt++;
         }
      }
		_statFrame.updateMaxLvl(tempLvl);
		_statFrame.updateEvolutionNb(evolutionNb);
		text = "Pokemon count : "+to_string(_scene->getPokemons()->size())+"\nGame speed : "+((_sceneSpeed == 0)?"Paused":"x "+to_string(_sceneSpeed));
		_upRightText.setString(text);

		_target.display();
		_targetSprite.setTexture(_target.getTexture());
		_targetSprite.setScale(_scaleRatio, _scaleRatio);
		_window.draw(_targetSprite);
		_window.draw(_upRightText);
      _window.display();

		_statFrame.update(_scene);
   }
   return quit;
}

/*	close method
*	Closes the window.
*	no parameters
*	no return statement
*/
void GameFrame::close()
{
   _window.close();
}

/*	timeForNewPokemon method
*	Tests if it is time to make a pokemon pop on the map. Asks factory to create a new pokemon.
*	no parameters
*	no return statement
*/
void GameFrame::timeForNewPokemon()
{
	if(_continuePop && _sceneSpeed != 0)
	{
		if(_scene->getPokemons()->size() < AVG_POKEMON_NB && _clock.getElapsedTime().asMilliseconds() > 100)
		{
			short size;
			if(_scene->getPokemons()->empty())
				size = 1;
			else
				size = (short)AVG_POKEMON_NB/_scene->getPokemons()->size();
			_scene->addRandomPokemon();
			short nb = _scene->getToAdd().back()->getNumber();
			short direction = static_cast<underlying_type<DIRECTION>::type>(_scene->getToAdd().back()->getDirection());
			_scene->getToAdd().back()->width = _pokemonSprites[nb][2*direction+1].getSize().x;
			_scene->getToAdd().back()->height = _pokemonSprites[nb][2*direction+1].getSize().y;
			_statFrame.addPokemonList(_scene->getToAdd().back());
			_clock.restart();
		}
		else if(_clock.getElapsedTime().asMilliseconds() > 500)
		{
			short size;
			if(_scene->getPokemons()->empty())
				size = 1;
			else
				size = (short)AVG_POKEMON_NB/_scene->getPokemons()->size();
			_scene->addRandomPokemon();
			short nb = _scene->getToAdd().back()->getNumber();
			short direction = static_cast<underlying_type<DIRECTION>::type>(_scene->getToAdd().back()->getDirection());
			_scene->getToAdd().back()->width = _pokemonSprites[nb][2*direction+1].getSize().x;
			_scene->getToAdd().back()->height = _pokemonSprites[nb][2*direction+1].getSize().y;
			_statFrame.addPokemonList(_scene->getToAdd().back());
			_clock.restart();
		}
	}
}


/* createMap mathod
*	Creates a random map. TODO
*	no parameters
*	no return statement
*/
void GameFrame::createMap()
{

}

/*	parseMap method
*	Parses the map from the /map/map1.txt
*	no parameters
*	no return statement
*/
void GameFrame::parseMap()
{
	ifstream file("./map/map1.txt");
	if(!file)
	{
		cerr << "Parse file doesn't exist !" << endl;
		_quit = 1;
	}
	else
	{
		short i(0);
		vector<short> vec;
		string line;
		string word;
		
		while(getline(file,line))
		{
			if(i == 0)
			{
				istringstream iss(line);
				iss>> _tileWidthNb;
				iss >> _tileHeightNb;

			cout << _tileWidthNb << "/" << _tileHeightNb << endl;
			++i;
			}
			else if(i == 1)
			{
				istringstream iss(line);
				while(iss >> word)
					vec.push_back(atoi(word.c_str()));
				_level = new short[vec.size()];
				copy(vec.begin(), vec.end(), _level);
			}
		}
		vec.clear();
		file.close();
	}
}

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
void GameFrame::handleKeyInput()
{
	/*	movement of the camera using the arrows */
	if(_hasFocus)
	{
		if(Keyboard::isKeyPressed(Keyboard::Up))
		{
			if(_targetSprite.getOrigin().y-SCREEN_MOVE > 0)
			{
				_targetSprite.setOrigin(_targetSprite.getOrigin().x,_targetSprite.getOrigin().y-SCREEN_MOVE);
			}
			else
			{
				_targetSprite.setOrigin(_targetSprite.getOrigin().x,0);
			}
		}
		if(Keyboard::isKeyPressed(Keyboard::Down))
		{
			if(_targetSprite.getOrigin().y+(_window.getSize().y+SCREEN_MOVE)/_scaleRatio < _target.getSize().y-SCREEN_MOVE/_scaleRatio)
			{
				_targetSprite.setOrigin(_targetSprite.getOrigin().x,_targetSprite.getOrigin().y+SCREEN_MOVE);
			}
			else
			{
				_targetSprite.setOrigin(_targetSprite.getOrigin().x,_target.getSize().y-(_window.getSize().y+SCREEN_MOVE)/_scaleRatio);
			}
		}
		if(Keyboard::isKeyPressed(Keyboard::Left))
		{
			if(_targetSprite.getOrigin().x-SCREEN_MOVE > 0)
			{
				_targetSprite.setOrigin(_targetSprite.getOrigin().x-SCREEN_MOVE,_targetSprite.getOrigin().y);
			}
			else
			{
				_targetSprite.setOrigin(0,_targetSprite.getOrigin().y);
			}
		}
		if(Keyboard::isKeyPressed(Keyboard::Right))
		{
			if(_targetSprite.getOrigin().x+(_window.getSize().x+SCREEN_MOVE)/_scaleRatio < _target.getSize().x)
			{
				_targetSprite.setOrigin(_targetSprite.getOrigin().x+SCREEN_MOVE,_targetSprite.getOrigin().y);
			}
			else
			{
				_targetSprite.setOrigin(_target.getSize().x-_window.getSize().x/_scaleRatio, _targetSprite.getOrigin().y);
			}
		}
	}
}

/*	handleMouseInput method
*	Handles mouse input. If left click on a pokemon, show status turned to true.
*	no parameters
*	no return statement
*/
void GameFrame::handleMouseInput()
{
	/*	 conditions for the mouse	*/
/*	if(event.type == Event::MouseButtonPressed)
	{
		if(event.mouseButton.button == Mouse::Left)
		{
			k = 0;
			end = false;
			_hasFocus = true;

			while(k < _scene->getPokemons()->size() && !end)
			{
				ptemp = _scene->getPokemons()->at(k);
				if(ptemp->contains(Mouse::getPosition().x/_scaleRatio, Mouse::getPosition().y/_scaleRatio))
				{
					if(ptemp->showStatus())
						ptemp->setShowStatus(false);
					else
						ptemp->setShowStatus(true);
					end = true;
					ptemp.reset();
				}
				else
				{
					++k;
					ptemp.reset();
				}
			}
		}
	}*/
}
