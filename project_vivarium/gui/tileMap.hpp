/* file : tileMap.hpp 
*	This file is the header of the tileMap.cpp file.
*	This class corresponds to a a tileMap. I found this class at the following URL:
*					http://www.sfml-dev.org/tutorials/2.1/graphics-vertex-array-fr.php
*	johann.novak25@gmail.com
*	16/03/14
*/

#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include<SFML/Graphics.hpp>

class TileMap : public sf::Drawable
{
   private:
      sf::VertexArray _vertices;
      sf::Texture _tileset;

      virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
   public:
      bool load(const std::string& tileset, sf::Vector2u tileSize, const short* tiles, unsigned short width, unsigned short height);
};
#endif
