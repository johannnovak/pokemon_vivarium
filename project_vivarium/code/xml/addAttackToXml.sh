#/bin/bash  addAttackToXml.sh
rep="n"
while [[ $rep == "n" ]]; do
   read -p $'> What is the name of the attack ?\n' name 
   read -p $'> What is the type of the attack ? (in CAPITAL LETTERS)\n' attackType
   read -p $'> What is the category of the attack ? (physical/special/status)\n' category
   read -p $'> What is the PP of the attack ? (number needed)\n' pp
   read -p $'> What is the power of the attack ? (number needed)\n' power
   read -p $'> What is the accuracy of the attack ? (number needed)\n' accuracy
   echo "attack : $name $attackType $category $pp $power $accuracy"
   read -p $'Are you sure about this attack ? (y/n)' rep
done
file=./attacks.xml
footer=$(cat $file | tail -n1)
cat file | head --lines=-1 > temp
cat temp > file
text=$'<attack name=\"'$name$'\" type=\"'$attackType$'\" category=\"'$category$'\" pp=\"'$pp$'\" power=\"'$power$'\" accuracy=\"'$accuracy$'\"/>'
echo -e "\t"$text >> file
echo $footer >> file
rm temp
cat file | head --lines=-5
echo "The attack has successfully been added !"
