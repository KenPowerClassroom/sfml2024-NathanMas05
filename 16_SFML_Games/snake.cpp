#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

// Replaced magic numbers with named constants
const int GRID_WIDTH = 30;
const int GRID_HEIGHT = 20;
const int TILE_SIZE = 16;

const float DELAY = 0.1f;

int windowWidth = TILE_SIZE * GRID_WIDTH;
int windowHeight = TILE_SIZE * GRID_HEIGHT;

int direction, snakeLength = 4;

// Renamed the dummy function to avoid confusion
int dummySnake()
{
    return 0;
}

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
        fruit.x = rand() % GRID_WIDTH;
        fruit.y = rand() % GRID_HEIGHT;
    }

    if (snake[0].x > GRID_WIDTH) snake[0].x = 0;
    if (snake[0].x < 0) snake[0].x = GRID_WIDTH;
    if (snake[0].y > GRID_HEIGHT) snake[0].y = 0;
    if (snake[0].y < 0) snake[0].y = GRID_HEIGHT;

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
    float timer = 0;

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

        if (timer > DELAY)
        {
            timer = 0;
            Tick();
        }

        ////// draw  ///////
        window.clear();

        for (int i = 0; i < GRID_WIDTH; i++)
            for (int j = 0; j < GRID_HEIGHT; j++)
            {
                sprite1.setPosition(i * TILE_SIZE, j * TILE_SIZE);
                window.draw(sprite1);
            }

        for (int i = 0; i < snakeLength; i++)
        {
            sprite2.setPosition(snake[i].x * TILE_SIZE, snake[i].y * TILE_SIZE);
            window.draw(sprite2);
        }

        sprite2.setPosition(fruit.x * TILE_SIZE, fruit.y * TILE_SIZE);
        window.draw(sprite2);

        window.display();
    }

    return 0;
}
