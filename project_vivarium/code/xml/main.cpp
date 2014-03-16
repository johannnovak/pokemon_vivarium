/*	main.cpp => parse html pokemon to pokedex	*/

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
	ifstream file("./pokemonToAdd.txt");
	if(!file)
	{
		return 1;
	}
	else
	{
		ofstream newfile;
		string finalString;
		string line;
		string evline;
		string word;
		long lineCount(1);
		short count = 0;
		bool addAttack = true;
		vector<string> attacks;
		string temp1;
		string temp2;

		string name;
		string number;
		
		stringstream ss;

		finalString ="\t<pokemon";
		while(getline(file,line))
		{
			if(lineCount == 4)
			{
				name = line;
				finalString += " name=\""+line+"\"";
			}
			if(line.find("National") != line.npos && lineCount < 20)
			{
				word = line.substr(line.size()-3,line.size());
				number = word;
				finalString += " number=\""+word+"\"";
			}
			if(line.find("Type") != line.npos && lineCount < 20)
			{
				ss << line;
				ss >> word;
				ss >> word;
				finalString += " type1=\""+word+"\"";
				ss >> word;
				finalString += " type2=\""+word+"\"";
			}
			if(line.find("EV yield") != line.npos)
			{
				evline = line;
			}
			if(line.find("Base EXP") != line.npos)
			{
				ss.str("");
				ss.clear();
				ss << line;
				ss >> word;
				ss >> word;
				ss >> word;
				finalString += " basexp=\""+word+"\"";
			}
			if(line.find("Growth Rate") != line.npos)
			{
				word = line.substr(12,line.size()-1);
				finalString += " xpcat=\""+word+"\"";
			}
			if(line.find("HP\t") != line.npos)
			{
				ss.str("");
				ss.clear();
				ss << line;
				ss >> word;
				ss >> word;
				finalString += " hp=\""+word+"\"";
			}
			if(line.find("Attack\t") != line.npos && lineCount < 60)
			{
				ss.str("");
				ss.clear();
				ss << line;
				ss >> word;
				ss >> word;
				finalString += " attack=\""+word+"\"";
			}
			if(line.find("Defense\t") != line.npos)
			{
				ss.str("");
				ss.clear();
				ss << line;
				ss >> word;
				ss >> word;
				finalString += " defense=\""+word+"\"";
			}
			if(line.find("Sp. Atk\t") != line.npos)
			{
				ss.str("");
				ss.clear();
				ss << line;
				ss >> word;
				ss >> word;
				ss >> word;
				finalString += " speattack=\""+word+"\"";
			}
			if(line.find("Sp. Def\t") != line.npos)
			{
				ss.str("");
				ss.clear();
				ss << line;
				ss >> word;
				ss >> word;
				ss >> word;
				finalString += " spedefense=\""+word+"\"";
			}
			if(line.find("Speed\t") != line.npos)
			{
				ss.str("");
				ss.clear();
				ss << line;
				ss >> word;
				ss >> word;
				finalString += " speed=\""+word+"\"";
			}
			if(line.find("Evolution chart") != line.npos && lineCount > 80)
			{
				getline(file,line);
				++lineCount;
				getline(file,line);
				++lineCount;
				getline(file,line);
				++lineCount;
				if(line.find(number) != line.npos)
				{
					finalString += " base=\"true\"";
					getline(file,line);
					++lineCount;
					getline(file,line);
					++lineCount;
					getline(file,line);
					++lineCount;
					if(line.find("Level") != line.npos)
					{
						ss.str("");
						ss.clear();
						ss << line;
						ss >> word;
						ss >> word;
						word.erase(word.end()-1);
						finalString += " evolutionLvl=\""+word+"\"";
						ss >> word;
						ss >> word;
						finalString += " evolutionName=\""+word+"\"";
						getline(file,line);
						++lineCount;
						word = line.substr(1,line.size()-1);
						finalString += " evolutionNb=\""+word+"\"";
					}
					else
					{
						finalString += " evolutionLvl=\"0\"";
						finalString += " evolutionName=\"none\"";
						finalString += " evolutionNb=\"0\"";
					}

				}
				else
				{
					finalString += " base=\"false\"";
					getline(file,line);
					++lineCount;
					getline(file,line);
					++lineCount;
					getline(file,line);
					++lineCount;
					if(line.find(number) != line.npos)
					{
						ss.str("");
						ss.clear();
						ss << line;
						ss >> word;
						ss >> word;
						ss >> word;
						word.erase(word.end()-1);
						finalString += " evolutionLvl=\""+word+"\"";
						ss >> word;
						ss >> word;
						finalString += " evolutionName=\""+word+"\"";
						getline(file,line);
						++lineCount;
						word = line.substr(1,line.size()-1);
						finalString += " evolutionNb=\""+word+"\"";
					}
					else
					{
						for(short z = 0; z < 5; ++z)
						{
							temp2 = line;
							getline(file,line);
							++lineCount;
						}
						cout << line << endl;
						if(line[0] == '#' && line.find(number) == line.npos)
						{
							if(temp2.find("Level") != temp2.npos)
							{
								ss.str("");
								ss.clear();
								ss << temp2;
								ss >> word;
								ss >> word;
								word.erase(word.end()-1);
								finalString += " evolutionLvl=\""+word+"\"";
								word=line.substr(1,line.size()-1);
								finalString += " evolutionNb=\""+word+"\"";
								getline(file,line);
								++lineCount;
								finalString += " evolutionName=\""+line+"\"";
							}
							else
							{
								word=line.substr(1,line.size()-1);
								finalString += " evolutionNb=\""+word+"\"";
								getline(file,line);
								++lineCount;
								finalString += " evolutionName=\""+line+"\"";
								finalString += " evolutionLvl=\"0\"";
							}
						}
						else
						{
							finalString += " evolutionLvl=\"0\"";
							finalString += " evolutionName=\"none\"";
							finalString += " evolutionNb=\"0\"";
						}
					}

				}
			}
			if(line.find("Red/Blue") != line.npos)
			{
				getline(file,line);
				++lineCount;
				if(line.find("Yellow") != line.npos)
				{
					for(short z = 0; z < 11; ++z)
					{
						getline(file,line);
						++lineCount;
					}
					while(line.find("Egg moves") == line.npos && line.find("Pre-evolution moves") == line.npos)
					{
						attacks.push_back(line);
						getline(file,line);
						++lineCount;
					}
				}
			}
			++lineCount;
		}

		finalString+=">\n\t\t<evs>\n";
		finalString+="\t\t\t<ev";
		evline = evline.substr(10,evline.size()-1);
		ss.str("");
		ss.clear();
		ss << evline;
		ss >> word;
		finalString+=" nb=\""+word+"\"";
		ss >> word;
		if(word.compare("Special") == 0)
		{
			ss >> temp1;
			word+=" "+temp1;
		}
		finalString+=" name=\""+word+"\"";

		if(evline.find(",") != line.npos)
		{
			finalString.erase(finalString.end()-2);
			finalString+="/>\n\t\t\t<ev";
			ss >> word;
			finalString+=" nb=\""+word+"\"";
			ss >> word;
			if(word.compare("Special") == 0)
			{
				ss >> temp1;
				word+=" "+temp1;
			}
			finalString+=" name=\""+word+"\"";
		}
		finalString+="/>";
		finalString+="\n\t\t</evs>\n";

		finalString+="\t\t<attackList>";
		while(!attacks.empty())
		{
			count = 0;
			finalString+="\n\t\t\t<attack";
			ss.str("");
			ss.clear();
			ss << attacks[0];
			while(ss >> temp2)
				++count;
			ss.str("");
			ss.clear();
			ss << attacks[0];
			ss >> word;
			finalString+=" lvl=\""+word+"\"";
			ss >> word;
			finalString+=" name=\""+word;
			if(count == 7)
			{
				ss >> word;
				finalString+=" "+word+"\"";
			}
			else
				finalString+="\"";

			finalString+="/>";
			attacks.erase(attacks.begin());
		}
		finalString+="\n\t\t</attackList>\n";

		finalString+="\t</pokemon>";
		file.close();
		attacks.clear();
		newfile.open("pok.txt");
		newfile << finalString;
		newfile.close();
		cout << finalString;
	}
	return 0;
}
