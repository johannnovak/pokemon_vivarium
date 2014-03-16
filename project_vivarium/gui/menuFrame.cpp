/* file ; menuFrame.cpp 
*	This file impelements the methods in the menuFrame.hpp file.
*	johann.novak25@gmail.com
*	16/03/14
*/

#include <menuFrame.hpp>

using namespace std;
using namespace sf;

/* Constructors   */

/*	Default constructor	*/
MenuFrame::MenuFrame()
{
   _window.create(VideoMode(1000,600),"Pokemon vivarium", Style::Titlebar | Style::Close);
   _window.setPosition(Vector2i(VideoMode::getDesktopMode().width/5,VideoMode::getDesktopMode().height/7));
   _window.setVerticalSyncEnabled(true);

   _bgTexture.loadFromFile("./images/images/bgmenu.png");
   _bgSprite.setTexture(_bgTexture);

   _playOTexture.loadFromFile("./images/images/playO.png");
   _playITexture.loadFromFile("./images/images/playI.png");
   _playSprite.setTexture(_playOTexture);
   _playSprite.setPosition(Vector2f(_window.getSize().x/2, _window.getSize().y*7/10));
   _playSprite.move(Vector2f((-1)*_playSprite.getLocalBounds().width/2,(-1)*_playSprite.getLocalBounds().height/2));
}

/*	Destructor	*/
MenuFrame::~MenuFrame()
{

}

/* Operators   */

/* Methods  */

/*	start method
*	Starts the window.
*	no parameters
*	no return statement
*/
short MenuFrame::start()
{
   short choice = 0;
   while(!choice)
   {
      Event event;
      while(_window.pollEvent(event))
      {
         switch(event.type)
         {
            case Event::Closed:
               _window.close();
               choice = 1;
               break;
            case Event::MouseButtonPressed:
               switch(event.mouseButton.button)
               {
                  case Mouse::Left:
                     if(isOnPlayButton())
                        choice = 2;
                     break;
                  default:
                     break;
               }
               break;
            case Event::KeyPressed:
               switch(event.key.code)
               {
                  case Keyboard::Return:
                     choice=2;
                     break;
               }
               break;
            default:
               break;
         }
      }
      _mousePos = Mouse::getPosition(_window);
      if(isOnPlayButton())
         _playSprite.setTexture(_playITexture);
      else
         _playSprite.setTexture(_playOTexture);
      _window.clear(Color::Black);
      _window.draw(_bgSprite);
      _window.draw(_playSprite);
      _window.display();
   }
   return choice;
}
bool MenuFrame::isOnPlayButton()
{
   return _playSprite.getGlobalBounds().contains(_mousePos.x,_mousePos.y);
}

/*	isOpen method
*	Tests if the window is open or not.
*	no parameters
*	return
*		true if it the window is open	/	false if not.
*/
bool MenuFrame::isOpen()
{
   return _window.isOpen();
}

/*	close method
*	Closes the window.
*	no parameters
*	no return statement
*/
void MenuFrame::close()
{
   _window.close();
}
