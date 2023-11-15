# Terra_Incognita
Surely the start of a big new MMORPG

This project requires SFML to compile: https://www.sfml-dev.org/download.php
This project requires CMake to build. We currently use VS Code with the CMake extension to build the project. Run CMake: Build to build and then CMake: Debug to run in debug mode

Deprecated:
To compile this project, we currently run the following  commands:
1. To compile: "g++ -c main.cpp"
2. To link the relevant libraries: "g++ main.o -o kloenk -lsfml-graphics -lsfml-window -lsfml-system"
3. To then run the generated binary, run: "./kloenk"