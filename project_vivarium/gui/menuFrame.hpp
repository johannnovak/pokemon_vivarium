/* file ; menuFrame.hpp 
*	This file is the header of the menuFrame.cpp file.
*	This class is the home screen of the pokemon vivarium.
*	johann.novak25@gmail.com
*	16/03/14
*/

#ifndef MENUFRAME_HPP
#define MENUFRAME_HPP

#include <iostream>

#include <gameFrame.hpp>

class MenuFrame
{
   private:
		/*	Attributes	*/
      sf::RenderWindow _window;		/*	window of the menuFrame	*/
      sf::Texture _bgTexture;			/*	background texture 	*/
      sf::Sprite _bgSprite;			/*	sprite of the background texture	*/

      sf::Texture _playOTexture;		/*	texture of the play button if the mouse isn't on it	*/
      sf::Texture _playITexture;			/*	texture of the play button if the mouse is on it	*/
      sf::Sprite _playSprite;			/*	sprite of the play button texture	*/

      sf::Vector2i _mousePos;		/*	position of the mouse	*/

      /* Methods  */

		/*	isOnPlayButton method
		*	Tests if the misue is on the play button.
		*	no parameters
		*	return
		*		true if it is on	/	false if not.
		*/
      bool isOnPlayButton();
   public:
      /* Constructors   */	
      MenuFrame();			/*	Default constructor	*/
      MenuFrame(MenuFrame const& frame);		/*	Copy constructor	*/
      ~MenuFrame();		/*	Destructor	*/

      /* Operators   */
      MenuFrame& operator=(MenuFrame const& frame);		/*	=	operator	*/

      /* Methods  */
		
		/*	start method
		*	Starts the window.
		*	no parameters
		*	no return statement
		*/
      short start();

		/*	isOpen method
		*	Tests if the window is open or not.
		*	no parameters
		*	return
		*		true if it the window is open	/	false if not.
		*/
      bool isOpen();

		/*	close method
		*	Closes the window.
		*	no parameters
		*	no return statement
		*/
      void close();
};
#endif
