#include <SFML/Graphics.hpp>

char* toString(int a)
{
    char str[8] ={'0',0,0,0,0,0,0,0};

    int i = -1;
    int b = a;

    while (b)
    {
        ++i;
        b /= 10;
    }

    while(a)
    {
        str[i]='0'+a%10;
        i--;
        a /= 10;
    }

    return str;
}

void drawText(sf::RenderWindow* app, sf::Text* head, char text[], int x, int y)
{
    head->setPosition(x, y);
    head->setString(text);
    app->draw(*head);
    return;
}

void drawLine(sf::RenderWindow* app, int x1, int y1, int x2, int y2, char gray)
{
    sf::VertexArray lines(sf::Lines, 2);
    lines[0].position = sf::Vector2f(x1,y1);
    lines[1].position = sf::Vector2f(x2,y2);

    if (gray)
    {
    lines[1].color = sf::Color(20, 20, 20);
    lines[0].color = sf::Color(20, 20, 20);
    }

    app->draw(lines);
    return;
}

void mainLoop(sf::RenderWindow* app)
{
    while (app->isOpen())
    {
        // Process events
        sf::Event event;

        while (app->pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app->close();
        }
        // Update the window
        app->display();
    }
}
