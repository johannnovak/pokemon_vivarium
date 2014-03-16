/* file : tileMap.cpp 
*	This file impements the methods in the tileMap.hpp file.
*	This class corresponds to a a tileMap. I found this class at the following URL:
*					http://www.sfml-dev.org/tutorials/2.1/graphics-vertex-array-fr.php
*	johann.novak25@gmail.com
*	16/03/14
*/

#include <tileMap.hpp>

using namespace sf;
using namespace std;

bool TileMap::load(const string& tileset, Vector2u tileSize, const short* tiles, unsigned short width, unsigned short height)
{
   /* 74 w
         h
   */
   if(!_tileset.loadFromFile(tileset))
      return false;

   _vertices.setPrimitiveType(Quads);
   _vertices.resize(width * height * 4);

   for(short i = 0; i < width; ++i)
      for(short j = 0; j < height; ++j)
      {
         short tileNumber = tiles[i + j * width];

         short tx = tileNumber % (_tileset.getSize().x/tileSize.x);
         short ty = tileNumber / (_tileset.getSize().x/tileSize.x);

         Vertex* quad = &_vertices[(i + j * width) * 4];

         quad[0].position = Vector2f(i * tileSize.x, j*tileSize.y);
         quad[1].position = Vector2f((i+1) * tileSize.x, j*tileSize.y);
         quad[2].position = Vector2f((i+1) * tileSize.x, (j+1)*tileSize.y);
         quad[3].position = Vector2f(i * tileSize.x, (j+1)*tileSize.y);
         
         quad[0].texCoords = Vector2f(tx * tileSize.x, ty*tileSize.y);
         quad[1].texCoords = Vector2f((tx+1) * tileSize.x, ty*tileSize.y);
         quad[2].texCoords = Vector2f((tx+1) * tileSize.x, (ty+1)*tileSize.y);
         quad[3].texCoords = Vector2f(tx * tileSize.x, (ty+1)*tileSize.y);
      
      }
      return true;
}

void TileMap::draw(RenderTarget& target, RenderStates states) const
{
   states.texture = &_tileset;

   target.draw(_vertices, states);
}
