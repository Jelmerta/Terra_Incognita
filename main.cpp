#include <SFML/Graphics.hpp>

// This project has dependencies on SDML
// This project requires SFML to compile: https://www.sfml-dev.org/download.php
// To compile this project, we currently run the following  commands: (We should add this to Github)
// 1. To compile: "g++ -c main.cpp"
// 2. To link the relevant libraries: "g++ main.o -o kloenk -lsfml-graphics -lsfml-window -lsfml-system"
// 3. To then run the generated binary, run: "./kloenk"
int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!", sf::Style::Fullscreen); // RenderWindow is een class/type binnen SFML, en die bevindt zich dan in een bepaald namespace, weet ik ook de ballen van joh. Zie dit gewoon als een Integer of whatever type
    sf::CircleShape shape(100.f); // dit rendert een cirkeltje die shape 
    shape.setFillColor(sf::Color::Green); //dit kleurt hem groen wat
    // wat is sf? Inderdaad vaag, dit is een "namespace". Dit geeft aan vanuit waar, bijvoorbeeld welke library een class (zoals RenderWindow) of functie aangeroepen wordt
 // niet Set Function ofzo? wat nou na sf doe jij een functie maken ofzo wat 
    while (window.isOpen()) //als window open is
    {
        sf::Event event; //Event is iets in c++?  en je noemt hem event? ok ik ga sfml installeren en dan het een day callen denk ik en wat dingen voor ideeën opschrijven verzinnen okokokookokok
        //Nee in SFML, dit is een library, alles wat sf/sfml heet heeft te maken met een library die bovenaan geimporteerd wordt, ja ok, we werken dus met de SFML library. Ja!!! voor nu, tenzij je klachten hebt. Nog niet. 
        // Ik zal de library installeren en een toertoerial kijken over C++ en SFML. Denk dat dat voor mij voldoende is voor nu. Ja dat is al heel wat om in je op te nemen, ik weet hier ook misschien 50% van hoor, ikm moet ook leren.
        // Het zou mooi zijn als ik morgen de code kan runnen :) Download SFML even!!! Bovenaan link en dan die dingen runnen eronder.
        // Tip: Installeer de extension C/C++ exntension pack voor highlighting als je da tnog niet had
        while (window.pollEvent(event))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	    {
		shape.move(-5.f, 0.f);
            }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            shape.move(5.f, 0.f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            shape.move(0.f, -5.f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            shape.move(0.f, 5.f);
        }

            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
