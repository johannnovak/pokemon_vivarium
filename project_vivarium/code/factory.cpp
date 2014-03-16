/* file : factory.cpp 
 *	This file implements the methods created in the factory.hpp file.
 *	johann.novak25@gmail.com
 *	15/03/14
 */

#include <factory.hpp>

using namespace std;
using namespace rapidxml;

/*	Default constructor	*/
Factory::Factory()
{
	/*	parse all the data necessary to the class	*/
   parseTypes();
   parseAttacks();
   parsePokedex();
}

/*	Copy contructor	*/
Factory::Factory(Factory const& fac)
{
   _pokemons = fac._pokemons;
   _types = fac._types;
   _attacks = fac._attacks;
}

/*	Destructor	*/
Factory::~Factory()
{
   _pokemons.clear();
   for(short i =0; i < _types.size(); ++i)
      _types[i].reset();
   _types.clear();
   map<string, shared_ptr<Attack>>::iterator it = _attacks.begin();
   while(it != _attacks.end())
   {
      it->second.reset();
      it++;
   }
   _attacks.clear();
}

/* Getters and Setters  */
vector<shared_ptr<Pokemon>> Factory::getPokemons()
{
   return _pokemons;
}
void Factory::setMapWidth(short width)
{
	_mapWidth = width;
}
void Factory::setMapHeight(short height)
{
	_mapHeight = height;
}
/* Operators   */

/*	= operator	*/
Factory& Factory::operator=(Factory const& fac)
{
   _pokemons = fac._pokemons;
   _types = fac._types;
   _attacks = fac._attacks;

   return *this;
}
/* Methods   */

/* createRandomBasePokemon method
*	This method create a new pokemon from the vector of base pokemon in attributes and returns a pointer pointing on it.
*	no parameters.
*	return
*		a pointer of Pokemon pointing on the new pokemon created.
*/
shared_ptr<Pokemon> Factory::createRandomBasePokemon()
{
	/*	We create a new pointer on Pokemon and we create the value of the pointer from the vector of base pokemon thanks to a random value	*/
	shared_ptr<Pokemon> creation = NULL;
	creation = shared_ptr<Pokemon>(new Pokemon(*_basePokemons[rand()%(_basePokemons.size())]));

	/*	We reset the IVs of the pokemon to differ him from other pokemon of the same species, we set its level from 1 to 5, set its position on the overall map	*/
	creation->resetIVS();
	creation->setLvl(rand()%5+1);	
	creation->setX(rand()%(_mapWidth*8/10)+_mapWidth/10);
	creation->setY(rand()%(_mapHeight*8/10)+_mapHeight/10);
	cout << "New " << creation->getName() << " created" << endl;
   
	return creation;
}

/* createPokemon method
*	This method create a new pokemon from the number in parameter, and returns a pointer pointing on it.
* 	parameters
*		short number : number of the pokemon to create from the vector containing all the pokemons.
*	return
*		a pointer of Pokemon pointing on the new pokemon created.
*/
shared_ptr<Pokemon> Factory::createPokemon(short number)
{
	/*	We create a new pointer on Pokemon and we create the value of the pointer from the vector of base pokemon thanks to the parameter	*/
   shared_ptr<Pokemon> creation = NULL;
   if(number >= 0 && number < _pokemons.size())
   {
      creation = shared_ptr<Pokemon>(new Pokemon(*_pokemons[number]));
	
		/*	We reset the IVs of the pokemon to differ him from other pokemon of the same species, we set its level from 1 to 5, set its position on the overall map	*/
      creation->resetIVS();
      creation->setLvl(rand()%5+1);
		creation->setX(rand()%(_mapWidth*8/10)+_mapWidth/10);
		creation->setY(rand()%(_mapHeight*8/10)+_mapHeight/10);
      cout << "New " << creation->getName() << " created" << endl;
   }
   else
      cout << "Wrong number for Pokemon Factory" << endl;
   return creation;
}

/* parseTypes method
*	This method parse the different types a pokemon can have from the file /xml/types.xml using the rapid-xml parser.
*	no parameters.
*	no return statement.
*/
void Factory::parseTypes()
{
	/*	We create a xml document, a ifstream from a file, and we test the file if it exists	*/
   xml_document<> doc;
   ifstream file("./code/xml/types.xml");
   if(file)
   {
      vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
      buffer.push_back('\0');
        
      doc.parse<0>(&buffer[0]);
      /* To set the current tag : <types> */
      xml_node<> *root_node = doc.first_node("pokemonTypes");
      
      /* for each type inside the xml, we create a new pointer on Type and we will add its values little by little	*/
      for(xml_node<>* types_node = root_node->first_node("type"); types_node ; types_node = types_node->next_sibling())
      {
         shared_ptr<Type> typeTemp = shared_ptr<Type>(new Type(types_node->first_attribute("name")->value()));

         /* Set the current tag to <weakTo>  */
         xml_node<>* weak_node = types_node->first_node("weakTo");   
         /* for each types inside <weakTo>  */
         for(xml_node<>* type_node = weak_node->first_node("type"); type_node; type_node = type_node->next_sibling())
         {
            typeTemp->addWeak(type_node->first_attribute("name")->value());
         }
         /* Set the current tag to <resistantTo>  */
         xml_node<>* resistant_node = types_node->first_node("resistantTo");
         /* for each types inside <resistantTo>  */
         for(xml_node<>* type_node = resistant_node->first_node("type"); type_node ; type_node = type_node->next_sibling())
         {
            typeTemp->addResistant(type_node->first_attribute("name")->value());
         }
         /* Set the current tag to <immuneTo>  */
         xml_node<>* immune_node = types_node->first_node("immuneTo");
         /* for each types inside <immuneTo>  */
         for(xml_node<>* type_node = immune_node->first_node("type"); type_node ; type_node = type_node->next_sibling())
         {
            typeTemp->addImmune(type_node->first_attribute("name")->value());
         }
         /* Set the current tag to <efficientOn>  */
         xml_node<>* efficient_node = types_node->first_node("efficientOn");
         /* for each types inside <efficientOn>  */
         for(xml_node<>* type_node = efficient_node->first_node("type"); type_node ; type_node = type_node->next_sibling())
         {
            typeTemp->addEfficient(type_node->first_attribute("name")->value());
         }
         /* Set the current tag to <notEfficientOn>  */
         xml_node<>* nefficient_node = types_node->first_node("notEfficientOn");
         /* for each types inside <notEfficientOn>  */
         for(xml_node<>* type_node = nefficient_node->first_node("type"); type_node ; type_node = type_node->next_sibling())
         {
            typeTemp->addNotEfficient(type_node->first_attribute("name")->value());
         }
         /* Set the current tag to <inefficientOn>  */
         xml_node<>* inefficient_node = types_node->first_node("inefficientOn");
         /* for each types inside <inefficientOn>  */
         for(xml_node<>* type_node = inefficient_node->first_node("type"); type_node ; type_node = type_node->next_sibling())
         {
            typeTemp->addInefficient(type_node->first_attribute("name")->value());
         }
			/*	We add the type created to the vector of type	*/
         _types.push_back(typeTemp);
      }
   }
   else
      cout << "FILE types.xml NULL" << endl;
   file.close();
}

/* parseAttacks method
*	This method parse the different attacks a pokemon can have from the file /xml/attacks.xml using the rapid-xml parser.
*	no parameters.
*	no return statement.
*/
void Factory::parseAttacks()
{
	/*	We create a xml document, a ifstream from a file, and we test the file if it exists	*/
   xml_document<> doc;
   ifstream file("./code/xml/attacks.xml");
   if(file)
   {
      vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
      buffer.push_back('\0');
        
      doc.parse<0>(&buffer[0]);

      xml_node<>* root_node = doc.first_node("attacks");
	/*	For each new line in the xml, we create a pointer on Attack and we construct its value from all the tags got from the xml	*/
      for(xml_node<>* attack_node = root_node->first_node("attack"); attack_node; attack_node = attack_node->next_sibling())
      {
         short temp;
			/*	we look for the type of the attack and when we found it, we construct the value	*/
         for(short i = 0; i < _types.size(); ++i)
            if(_types[i]->getName() == attack_node->first_attribute("type")->value())
               temp = i;
         shared_ptr<Attack> attack = shared_ptr<Attack>(new Attack(
            attack_node->first_attribute("name")->value(),
            attack_node->first_attribute("category")->value(), 
            atoi(attack_node->first_attribute("power")->value()), 
            atoi(attack_node->first_attribute("accuracy")->value()), 
            _types[temp], 
            atoi(attack_node->first_attribute("pp")->value()
            )
         ));
			/*	We add the new attack to the map of attacks	*/
         _attacks[attack_node->first_attribute("name")->value()] = attack;
      }
   }
   else
      cout << "FILE attacks.xml NULL" << endl;
   file.close();
}

/* parsePokedex method
*	This method parse the different attributes of each pokemon from the file /xml/pokedex.xml using the rapid-xml parser.
*	no parameters.
*	no return statement.
*/
void Factory::parsePokedex()
{
	/*	We create a xml document, a ifstream from a file, and we test the file if it exists	*/
   xml_document<> doc;
   ifstream file("./code/xml/pokedex.xml");
   if(file)
   {
      vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
      buffer.push_back('\0');
      doc.parse<0>(&buffer[0]);
      
		/*	For each line in the xml, we construct the new pokemon with the different xml tags	*/
      xml_node<>* root_node = doc.first_node("pokedex");
      for(xml_node<>* pokemon_node = root_node->first_node("pokemon"); pokemon_node; pokemon_node = pokemon_node->next_sibling())
      {
         shared_ptr<Pokemon> pok = shared_ptr<Pokemon>(new Pokemon(
            pokemon_node->first_attribute("name")->value(), 
            atoi(pokemon_node->first_attribute("number")->value()),
            1,
            ((strcmp(pokemon_node->first_attribute("base")->value(),"true") == 0)?true:false),
            atoi(pokemon_node->first_attribute("evolutionLvl")->value()),
            pokemon_node->first_attribute("evolutionName")->value(),
            atoi(pokemon_node->first_attribute("evolutionNb")->value()),
            pokemon_node->first_attribute("xpcat")->value(),
            atoi(pokemon_node->first_attribute("hp")->value()), 
            atoi(pokemon_node->first_attribute("attack")->value()), 
            atoi(pokemon_node->first_attribute("defense")->value()), 
            atoi(pokemon_node->first_attribute("speed")->value()), 
            atoi(pokemon_node->first_attribute("speattack")->value()), 
            atoi(pokemon_node->first_attribute("spedefense")->value()),
            atoi(pokemon_node->first_attribute("basexp")->value())
         ));
			/*	We test each types to see if it corresponds to one of the tag to the pokemon's types, and when it does, we add a new Type to the pokemon	*/
         for(short i = 0; i < _types.size(); ++i)
         {
            if(_types[i]->getName() == pokemon_node->first_attribute("type1")->value())
               pok->setType1(_types[i]);
            if(_types[i]->getName() == pokemon_node->first_attribute("type2")->value())
               pok->setType2(_types[i]);
         }
			/*	For each line in the <evs> tag, we add a new EV to the pokemon with the values corresponding to it	*/
         xml_node<>* evs_node = pokemon_node->first_node("evs");
         for(xml_node<>* ev_node = evs_node->first_node("ev"); ev_node; ev_node = ev_node->next_sibling())
            pok->addEVSToGive(ev_node->first_attribute("name")->value(), atoi(ev_node->first_attribute("nb")->value()));

			/*	For each line in the <attackList> tag in the xml, we add the attack to the pokemon with the level when he learns the attack	*/
         xml_node<>* attackList_node = pokemon_node->first_node("attackList");
         for(xml_node<>* attack_node = attackList_node->first_node("attack"); attack_node; attack_node = attack_node->next_sibling())
            pok->addAttack(atoi(attack_node->first_attribute("lvl")->value()), _attacks[attack_node->first_attribute("name")->value()]);
			/*	We add the pokemon to the pokemon databank	*/
         _pokemons.push_back(pok);

			/*	If the pokemon is a base pokemon, we add it to t he basePokemon list	*/
			if(pok->isBase())
				_basePokemons.push_back(pok);
      }
   }
   else
      cout << "FILE pokedex.xml NULL" << endl;
   file.close();
}

/*	printPokemons method
*	Print all pokemons contained in the pokemon vector
*/
void Factory::printPokemons()
{
   for(short i = 0; i < _pokemons.size();++i)
   {
      cout << _pokemons[i];
   }
}

/* returnEvolution method
* This method returns the evolution of the pokemon which possesses the number in parameter.
*	parameters
*		short evolutionNumber : number of the pokemon which asks to evolve.
*	return
*		a pointer on the evolution of the pokemon which asked the evolution.
*/
shared_ptr<Pokemon> Factory::returnEvolution(short evolutionNumber)
{
	/*	Request the evolution to the pokemon's number-1	*/
   shared_ptr<Pokemon> pok = createPokemon(evolutionNumber-1);
   cout << "after creation in return evolution " << endl;
   return pok;
}
