#/bin/bash
rep="n"
while [[ $rep == "n" ]]; do
   read -p $'> What is the number of the xp lvl ?\n' nb 
   read -p $'> What is the xp gained for the fast group ?\n' fast
   read -p $'> What is the xp gained for the fast medium fast ?\n' mediumFast
   read -p $'> What is the xp gained for the medium slow group ?\n' mediumSlow
   read -p $'> What is the xp gained for the slow group ?\n' slow
   read -p $'Are you sure about this ?\n' rep
done
file=./xp.xml
footer=$(cat $file | tail -n1)
cat $file | head --lines=-1 > temp
cat temp > $file
text=$'<lvl nb=\"'$nb$'\" fast=\"'$fast$'\" mediumfast=\"'$mediumFast$'\" mediumslow=\"'$mediumSlow$'\" slow=\"'$slow$'\"/>'
echo -e "\t"$text >> $file
echo $footer >> $file
rm temp
cat $file | tail -n -2
echo "The xp level has successfully been added !"
