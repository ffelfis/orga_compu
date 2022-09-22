./tp0 -h
echo -e "\n"

./tp0 -V
echo -e "\n"

for file in *.txt
do
	echo -e "CONTEO PARA $file\n"
	echo -e "CARACTERES:\n"
	time ./tp0 -c -i "$file"
	echo -e "\nPALABRAS:\n"
	time ./tp0 -w -i "$file"
	echo -e "\nLINEAS:\n"
	time ./tp0 -l -i "$file"
	echo -e "\n"
done
