// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    srand(time(0)); // seed random

    // Create a video mode object
    VideoMode vm(1920, 1080);
    // Create and open a window for the game
    RenderWindow window(vm, "Chaos Game!!", Style::Default);

    vector<Vector2f> vertices;
    vector<Vector2f> points;

    // FONT + TEXT (requirement)
    Font font;
    if (!font.loadFromFile("fonts/KOMIKAP_.ttf"))
    {
        cout << "Error loading font\n";
    }

    Text instructions;
    instructions.setFont(font);
    instructions.setCharacterSize(24);
    instructions.setFillColor(Color::White);
    instructions.setPosition(10, 10);

    while (window.isOpen())
    {
        /*
        ****************************************
        Handle the players input
        ****************************************
        */
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }

            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    cout << "mouse x: " << event.mouseButton.x << endl;
                    cout << "mouse y: " << event.mouseButton.y << endl;

                    if (vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if (points.size() == 0)
                    {
                        // fourth click → starting point
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        /*
        ****************************************
        Update
        ****************************************
        */

        if (points.size() > 0)
        {
            for (int i = 0; i < 200; i++) // more points = faster fractal
            {
                int index = rand() % 3;

                Vector2f lastPoint = points.back();
                Vector2f chosenVertex = vertices[index];

                Vector2f newPoint;
                newPoint.x = (lastPoint.x + chosenVertex.x) / 2.0f;
                newPoint.y = (lastPoint.y + chosenVertex.y) / 2.0f;

                points.push_back(newPoint);
            }
        }

        /*
        ****************************************
        Draw
        ****************************************
        */
        window.clear();

        // Update instruction text
        if (vertices.size() < 3)
        {
            instructions.setString("Click 3 points to create triangle");
        }
        else if (points.size() == 0)
        {
            instructions.setString("Click a 4th point to start");
        }
        else
        {
            instructions.setString("Chaos Game Running... Press ESC to quit");
        }

        window.draw(instructions);

        // Draw vertices (blue squares)
        for (int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(10, 10));
            rect.setPosition(vertices[i]);
            rect.setFillColor(Color::Blue);
            window.draw(rect);
        }

        // Draw triangle outline
        if (vertices.size() == 3)
        {
            Vertex line[] =
            {
                Vertex(vertices[0], Color::Green),
                Vertex(vertices[1], Color::Green),
                Vertex(vertices[2], Color::Green),
                Vertex(vertices[0], Color::Green)
            };
            window.draw(line, 4, LineStrip);
        }

        // Draw generated points
        for (int i = 0; i < points.size(); i++)
        {
            RectangleShape rect(Vector2f(2, 2));
            rect.setPosition(points[i]);
            rect.setFillColor(Color::White);
            window.draw(rect);
        }

        window.display();
    }
}
