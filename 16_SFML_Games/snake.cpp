#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

// Changed variable names for clarity
int gridWidth = 30, gridHeight = 20;
int tileSize = 16;
int windowWidth = tileSize * gridWidth;
int windowHeight = tileSize * gridHeight;

int direction, snakeLength = 4;

struct Snake
{
    int x, y;
} snake[100];

struct Fruit
{
    int x, y;
} fruit;

void Tick()
{
    for (int i = snakeLength; i > 0; --i)
    {
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
    }

    if (direction == 0) snake[0].y += 1;
    if (direction == 1) snake[0].x -= 1;
    if (direction == 2) snake[0].x += 1;
    if (direction == 3) snake[0].y -= 1;

    if ((snake[0].x == fruit.x) && (snake[0].y == fruit.y))
    {
        snakeLength++;
        fruit.x = rand() % gridWidth;
        fruit.y = rand() % gridHeight;
    }

    if (snake[0].x > gridWidth) snake[0].x = 0;
    if (snake[0].x < 0) snake[0].x = gridWidth;
    if (snake[0].y > gridHeight) snake[0].y = 0;
    if (snake[0].y < 0) snake[0].y = gridHeight;

    for (int i = 1; i < snakeLength; i++)
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
            snakeLength = i;
}

int snakeGame()
{
    srand(time(0));

    RenderWindow window(VideoMode(windowWidth, windowHeight), "Snake Game!");

    Texture t1, t2;
    t1.loadFromFile("images/snake/white.png");
    t2.loadFromFile("images/snake/red.png");

    Sprite sprite1(t1);
    Sprite sprite2(t2);

    Clock clock;
    float timer = 0, delay = 0.1;

    fruit.x = 10;
    fruit.y = 10;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) direction = 1;
        if (Keyboard::isKeyPressed(Keyboard::Right)) direction = 2;
        if (Keyboard::isKeyPressed(Keyboard::Up)) direction = 3;
        if (Keyboard::isKeyPressed(Keyboard::Down)) direction = 0;

        if (timer > delay)
        {
            timer = 0;
            Tick();
        }

        ////// draw  ///////
        window.clear();

        for (int i = 0; i < gridWidth; i++)
            for (int j = 0; j < gridHeight; j++)
            {
                sprite1.setPosition(i * tileSize, j * tileSize);
                window.draw(sprite1);
            }

        for (int i = 0; i < snakeLength; i++)
        {
            sprite2.setPosition(snake[i].x * tileSize, snake[i].y * tileSize);
            window.draw(sprite2);
        }

        sprite2.setPosition(fruit.x * tileSize, fruit.y * tileSize);
        window.draw(sprite2);

        window.display();
    }

    return 0;
}
