#/bin/bash  addPokemonToXml.sh
rep1="n"
while [[ $rep1 == "n" ]]; do
   read -p $'> What is the name of the new Pokemon ?\n' name
   read -p $'> What is '$name$'\'s number ?\n' nb
   read -p $'> What are '$name$'\'s base HP ?\n' hp
   read -p $'> What is '$name$'\'s base attack ?\n' attack
   read -p $'> What is '$name$'\'s base defense ?\n' defense
   read -p $'> What is '$name$'\'s base speed ?\n' speed
   read -p $'> What is '$name$'\'s base speattack ?\n' speattack
   read -p $'> What is '$name$'\'s base spedefense ?\n' spedefense
   read -p $'> What is '$name$'\'s first type ?\n' type1
   read -p $'> What is '$name$'\'s second type ?\n(If the same as the first one, write the first one again)\n' type2
   read -p $'> What is '$name$'\'s first evolution level ?\n(0 if none)\n' lvlevo
   read -p $'> What is '$name$'\'s evolution number ?\n(0 if none)\n' nbevo
   read -p $'> What is '$name$'\'s evolution name ?\n("none" if none)\n' nameevo
   read -p $'> Is '$name$' a base Pokemon ?\n(true/false)\n' base
   read -p $'> What is '$name$'\'s xp category ?\n(fast / medium fast / medium slow / slow)\n' xpcat

   # evs
   rep2="y"
   echo "Concerning the EVs to give when defeated :"
   while [[ $rep2 == "y"  ]]; do
      read -p $'> What is the type of ev to give when '$name$' is defeated ?\n(hp/attack/defense/speed/speattack/spedefense)\n' evsnametemp
      evsname=$evsname" "$evsnametemp
      read -p $'> What is the number of evs to give when '$name$' is defeated ?\n' evsnbtemp
      evsnb=$evsnb" "$evsnbtemp
      read -p $'> Is there another ev to give ? (y/n)' rep2
   done

   # attackList
   rep2="y"
   echo "Concerning the the attack list of the pokemon :"
   while [[ $rep2 == "y"  ]]; do
      read -p $'> What is the level of the new acquired attack ?\n' lvlattacktemp
      lvlattack=$lvlattack" "$lvlattacktemp
      read -p $'> What is the name of the new attack ?\n' nameattacktemp
      nameattack=$nameattack"_"$nameattacktemp
      read -p $'> Is there another attack ? (y/n)' rep2
   done

   evsname=$(echo $evsname | tail -c +1)
   evsnb=$(echo $evsnb | tail -c +1)
   lvlattack=$(echo $lvlattack | tail -c +1)
   nameattack=$(echo $nameattack | tail -c +1)

   echo -e "Pokemon : $name $nb hp=$hp attack=$attack defense=$defense speed=$speed speattack=$speattack spedefense$spedefense type1=$type1 type2=$type2 evolvl=$evolvl evonb=$evonb evoname=$evoname base=$base xpcat=$xpcat\nevs : \n>$evsname\n>$evsnb \nAttacks : \n>$lvlattack \n>$nameattack"
   read -p $'Are you sure about this pokemon ? (y/n)' rep1
done
file=./pokedex.xml
footer=$(cat $file | tail -n1)
cat $file | head --lines=-1 > temp
cat temp > $file
text=$'<pokemon name=\"'$name$'\" number=\"'$nb$'\" hp=\"'$hp$'\" attack=\"'$attack$'\" defense=\"'$defense$'\" speed=\"'$speed$'\" speattack=\"'$speattack$'\" spedefense=\"'$spedefense$'\" type1=\"'$type1$'\" type2=\"'$type2$'\" evolutionLvl=\"'$lvlevo$'\" evolutionNb=\"'$nbevo$'\" evolutionName=\"'$nameevo$'\" base=\"'$base$'\" xpcat=\"'$xpcat$'\">'
echo -e "\t"$text >> $file
echo -e "\t\t<evs>" >> $file
i=1
nb=$(echo $evsname | wc -w)
while [ $i -le $nb ]; do
   var1=$(echo $evsname | cut -d ' ' -f $i)
   var2=$(echo $evsnb | cut -d ' ' -f $i)
   text=$'<ev name=\"'$var1$'\" nb=\"'$var2$'\"/>'
   echo -e "\t\t\t"$text >> $file
   let i+=1
done
echo -e "\t\t</evs>\n\t\t<attackList>" >> $file
i=1
nb=$(echo $lvlattack | wc -w)
while [ $i -le $nb ]; do
   var1=$(echo $lvlattack | cut -d ' ' -f $i)
   let j=$i+1
   var2=$(echo $nameattack | cut -d '_' -f $j)
   text=$'<attack lvl=\"'$var1$'\" name=\"'$var2$'"/>'
   echo -e "\t\t\t"$text >> $file
   let i+=1
done
echo -e "\t\t</attackList>" >> $file
echo -e "\t</pokemon>" >> $file
echo $footer >> $file
rm temp
echo "The pokemon has successfully been added !"
