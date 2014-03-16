/* main.cpp */

#include <menuFrame.hpp>

#include <sceneManager.hpp>

using namespace std;
using namespace sf;

/*
int main(int argc, char** argv)
{
	RenderWindow win(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Pokemon Vivarium", sf::Style::Titlebar | sf::Style::Close);

	RectangleShape bg;
	bg.setSize(Vector2f(300,100));
	bg.setPosition(500, 500);
	bg.setOutlineColor(Color::White);
	bg.setOutlineThickness(5);
	bg.setFillColor(Color::Red);
	
	RectangleShape fg;
	fg.setSize(Vector2f(150,100));
	fg.setPosition(500, 500);
	fg.setFillColor(Color::Green);
	
	while(win.isOpen())
	{
		Event e;
		while(win.pollEvent(e))
		{
			switch(e.type)
			{
				case Event::Closed:
					win.close();
					break;
				default:
					break;
			}
		}
		win.clear(Color::Black);
		win.draw(bg);
		win.draw(fg);
		win.display();
	}

	return 0;
}
*/

int main(int argc, char** argv)
{
   short choice;
   MenuFrame menuFrame;
	/*	creates the menuFrame	*/
   choice = menuFrame.start();
   menuFrame.close();
   if(choice == 2)
   {
		/*	If the menuFrame is closed and the play button pressed, it launches the gameFrame	*/
      GameFrame gameFrame;
      gameFrame.start();
      gameFrame.close();
   }
	return 0;
}

/*
int main(int argc, char** argv)
{
	shared_ptr<SceneManager> scene = shared_ptr<SceneManager>(new SceneManager());
   scene->getFightManager()->setScene(scene);

   short nb=10;
   for(short i = 0; i < nb; ++i)
   	scene->addRandomPokemon();
    short nb2;
    short nb3;
    short size;
	 */
	 /*
    do
    {
    	nb2=rand()%(scene->getPokemons().size());
 	   do
      {
         nb3=rand()%(scene->getPokemons().size());
      }while(nb3 == nb2);
      scene->intersectWith(scene->getPokemons()[nb2],scene->getPokemons()[nb3]);
   }while(scene->getPokemons().size() > 1);*/
/*	cout << scene->getFightManager()->getFights().size() << endl;
	scene->getFightManager()->addFight((*scene->getPokemons())[0], (*scene->getPokemons())[1]);
	cout << scene->getFightManager()->getFights().size() << endl;
	cout << scene->getFightManager()->getFights().size() << endl;
	cout << scene->getFightManager()->getFights().size() << endl;
	cout << scene->getFightManager()->getFights().size() << endl;
	cout << scene->getFightManager()->getFights().size() << endl;
	cout << scene->getFightManager()->getFights().size() << endl;
	cout << scene->getFightManager()->getFights().size() << endl;
	cout << scene->getFightManager()->getFights().size() << endl;
	cout << scene->getFightManager()->getFights().size() << endl;
	cout << scene->getFightManager()->getFights().size() << endl;
	cout << scene->getFightManager()->getFights().size() << endl;
	cout << scene->getFightManager()->getFights().size() << endl;
	cout << scene->getFightManager()->getFights().size() << endl;
	cout << scene->getFightManager()->getFights().size() << endl;
	cout << scene->getFightManager()->getFights().size() << endl;
	cout << scene->getFightManager()->getFights().size() << endl;
	cout << scene->getFightManager()->getFights().size() << endl;
	cout << scene->getFightManager()->getFights().size() << endl;
	cout << scene->getFightManager()->getFights().size() << endl;
	cout << scene->getFightManager()->getFights().size() << endl;
	cout << scene->getFightManager()->getFights().size() << endl;
	cout << scene->getFightManager()->getFights().size() << endl;
	cout << scene->getFightManager()->getFights().size() << endl;
	cout << scene->getFightManager()->getFights().size() << endl;
	cout << scene->getFightManager()->getFights().size() << endl;
	cout << scene->getFightManager()->getFights().size() << endl;
	cout << scene->getFightManager()->getFights().size() << endl;
	cout << scene->getFightManager()->getFights().size() << endl;
	cout << scene->getFightManager()->getFights().size() << endl;
   scene.reset();

   return 0;
}
*/
