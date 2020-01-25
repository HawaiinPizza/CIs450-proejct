all:run
	printf "RUNNING\n"
	./run && printf "\nSuccess" || rm run
	rm run
run:
	g++ Main.cpp -o run || printf "\nAn error has occured"
