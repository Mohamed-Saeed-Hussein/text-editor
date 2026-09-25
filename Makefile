build/text-editor: main.cpp
	mkdir -p build
	g++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o build/text-editor