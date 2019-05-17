for((i=1;;i++)); do
	echo $i
	./gen $i > int
	./f < int || break
done
