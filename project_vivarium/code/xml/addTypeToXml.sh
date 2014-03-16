#/bin/bash  addTypeToXml.sh
rep1="n"
rep3="y"
while [[ $rep1 == "n" ]]; do
   read -p $'> What is the name of the new Type ?\n' name

   # weakTo
   read -p $'> Is there any types to which it is weak to ? (y/n)' rep2
   if [[ $rep2 == "y"  ]]; then
      while [[ $rep2 == "y"  ]]; do
         read -p $'> What is the name of the weak to Type ?\n' typetemp
         typew=$typew" "$typetemp
         read -p $'> Is there another weak to type ? (y/n)' rep2
      done
   fi

   # resistantTo
   read -p $'> Is there any types to which it is resistant ? (y/n)' rep2
   if [[ $rep2 == "y"  ]]; then
      while [[ $rep2 == "y"  ]]; do
         read -p $'> What is the name of the resistant Type ?\n' typetemp
         typer=$typer" "$typetemp
         read -p $'> Is there another resistant type ? (y/n)' rep2
      done
   fi

   # resistantTo
   read -p $'> Is there any types to which it is immuned ? (y/n)' rep2
   if [[ $rep2 == "y"  ]]; then
      while [[ $rep2 == "y"  ]]; do
         read -p $'> What is the name of the immuned Type ?\n' typetemp
         typeim=$typeim" "$typetemp
         read -p $'> Is there another immuned type ? (y/n)' rep2
      done
   fi

   # efficientOn
   read -p $'> Is there any types to which it is efficient on ? (y/n)' rep2
   if [[ $rep2 == "y"  ]]; then
      while [[ $rep2 == "y"  ]]; do
         read -p $'> What is the name of the efficient on Type ?\n' typetemp
         typeef=$typeef" "$typetemp
         read -p $'> Is there another efficient on type ? (y/n)' rep2
      done
   fi

   # notefficientOn
   read -p $'> Is there any types to which it is not efficient on ? (y/n)' rep2
   if [[ $rep2 == "y"  ]]; then
      while [[ $rep2 == "y"  ]]; do
         read -p $'> What is the name of the not efficient on Type ?\n' typetemp
         typenef=$typenef" "$typetemp
         read -p $'> Is there another not efficient on type ? (y/n)' rep2
      done
   fi

   # inefficientOn
   read -p $'> Is there any types to which it is inefficient on ? (y/n)' rep2
   if [[ $rep2 == "y"  ]]; then
      while [[ $rep2 == "y"  ]]; do
         read -p $'> What is the name of the inefficient on Type ?\n' typetemp
         typeinef=$typeinef" "$typetemp
         read -p $'> Is there another inefficient on type ? (y/n)' rep2
      done
   fi

   typew=$(echo $typew | tail -c +1)
   typer=$(echo $typer | tail -c +1)
   typeim=$(echo $typeim | tail -c +1)
   typeef=$(echo $typeef | tail -c +1)
   typenef=$(echo $typenef | tail -c +1)
   typeinef=$(echo $typeinef | tail -c +1)

   echo -e "type : $name \nWeak To : $typew \nResistant to : $typer \nImmune to : $typeim \nEfficient on : $typeef \nNot efficient on : $typenef \nInefficient on : $typeinef"
   read -p $'Are you sure about this type ? (y/n)' rep1
done
file=./types.xml
footer=$(cat $file | tail -n1)
cat $file | head --lines=-1 > temp
cat temp > $file
text=$'<type name=\"'$name$'\">'
echo -e "\t"$text >> $file
echo -e "\t\t<weakTo>" >> $file
i=1
nb=$(echo $typew | wc -w)
while [ $i -lt $nb ]; do
   var=$(echo $typew | cut -d ' ' -f $i)
   text="<type name=\"$var\"/>"
   echo -e "\t\t\t"$text >> $file
   let i+=1
done
echo -e "\t\t</weakTo>\n\t\t<resistantTo>" >> $file
i=1
nb=$(echo $typer | wc -w)
while [ $i -le $nb ]; do
   var=$(echo $typer | cut -d ' ' -f $i)
   text="<type name=\"$var\"/>"
   echo -e "\t\t\t"$text >> $file
   let i+=1
done
echo -e "\t\t</resistantTo>\n\t\t<immuneTo>" >> $file
i=1
nb=$(echo $typeim | wc -w)
while [ $i -le $nb ]; do
   var=$(echo $typeim | cut -d ' ' -f $i)
   text="<type name=\"$var\"/>"
   echo -e "\t\t\t"$text >> $file
   let i+=1
done
echo -e "\t\t</immuneTo>\n\t\t<efficientOn>" >> $file
i=1
nb=$(echo $typeef | wc -w)
while [ $i -le $nb ]; do
   var=$(echo $typeef | cut -d ' ' -f $i)
   text="<type name=\"$var\"/>"
   echo -e "\t\t\t"$text >> $file
   let i+=1
done
echo -e "\t\t</efficientOn>\n\t\t<notEfficientOn>" >> $file
i=1
nb=$(echo $typenef | wc -w)
while [ $i -le $nb ]; do
   var=$(echo $typenef | cut -d ' ' -f $i)
   text="<type name=\"$var\"/>"
   echo -e "\t\t\t"$text >> $file
   let i+=1
done
echo -e "\t\t</notEfficientOn>\n\t\t<inefficientOn>" >> $file
i=1
nb=$(echo $typeinef | wc -w)
while [ $i -le $nb ]; do
   var=$(echo $typeinef | cut -d ' ' -f $i)
   text="<type name=\"$var\"/>"
   echo -e "\t\t\t"$text >> $file
   let i+=1
done
echo -e "\t\t</inefficientOn>" >> $file
echo -e "\t</type>" >> $file
echo $footer >> $file
rm temp
echo "The type has successfully been added !"
