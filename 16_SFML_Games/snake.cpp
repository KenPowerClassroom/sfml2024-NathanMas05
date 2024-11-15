#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

// Replaced magic numbers with named constants
const int GRID_WIDTH = 30;
const int GRID_HEIGHT = 20;
const int TILE_SIZE = 16;
const float DELAY = 0.1f;
const int INITIAL_SNAKE_LENGTH = 4; // New constant for initial snake length

int windowWidth = TILE_SIZE * GRID_WIDTH;
int windowHeight = TILE_SIZE * GRID_HEIGHT;

class Fruit {
public:
    int x, y;

    Fruit() {
        x = rand() % GRID_WIDTH;
        y = rand() % GRID_HEIGHT;
    }

    void respawn() {
        x = rand() % GRID_WIDTH;
        y = rand() % GRID_HEIGHT;
    }
};

class Snake {
public:
    struct Segment {
        int x, y;
    } segments[100];

    int length;
    int direction;

    Snake() {
        length = INITIAL_SNAKE_LENGTH;
        direction = 0;
        for (int i = 0; i < length; ++i) {
            segments[i].x = GRID_WIDTH / 2;
            segments[i].y = GRID_HEIGHT / 2;
        }
    }

    void move() {
        for (int i = length; i > 0; --i) {
            segments[i].x = segments[i - 1].x;
            segments[i].y = segments[i - 1].y;
        }

        if (direction == 0) segments[0].y += 1;
        if (direction == 1) segments[0].x -= 1;
        if (direction == 2) segments[0].x += 1;
        if (direction == 3) segments[0].y -= 1;

        if (segments[0].x > GRID_WIDTH) segments[0].x = 0;
        if (segments[0].x < 0) segments[0].x = GRID_WIDTH;
        if (segments[0].y > GRID_HEIGHT) segments[0].y = 0;
        if (segments[0].y < 0) segments[0].y = GRID_HEIGHT;
    }

    void grow() {
        length++;
    }

    bool checkCollision() {
        for (int i = 1; i < length; i++) {
            if (segments[0].x == segments[i].x && segments[0].y == segments[i].y)
                return true;
        }
        return false;
    }
};

void Tick(Snake& snake, Fruit& fruit) {
    snake.move();

    if (snake.segments[0].x == fruit.x && snake.segments[0].y == fruit.y) {
        snake.grow();
        fruit.respawn();
    }

    // Early return to simplify the game-over logic
    if (snake.checkCollision()) {
        snake.length = INITIAL_SNAKE_LENGTH;  // Use descriptive constant for reset
        return;
    }
}

void drawGrid(RenderWindow& window, Sprite& sprite) {
    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            sprite.setPosition(i * TILE_SIZE, j * TILE_SIZE);
            window.draw(sprite);
        }
    }
}

void drawSnake(RenderWindow& window, Snake& snake, Sprite& sprite) {
    for (int i = 0; i < snake.length; i++) {
        sprite.setPosition(snake.segments[i].x * TILE_SIZE, snake.segments[i].y * TILE_SIZE);
        window.draw(sprite);
    }
}

void drawFruit(RenderWindow& window, Fruit& fruit, Sprite& sprite) {
    sprite.setPosition(fruit.x * TILE_SIZE, fruit.y * TILE_SIZE);
    window.draw(sprite);
}

int snakeGame() {
    srand(time(0));

    RenderWindow window(VideoMode(windowWidth, windowHeight), "Snake Game!");

    Texture t1, t2;
    t1.loadFromFile("images/snake/white.png");
    t2.loadFromFile("images/snake/red.png");

    Sprite sprite1(t1);
    Sprite sprite2(t2);

    Clock clock;
    float timer = 0;

    Fruit fruit;
    Snake snake;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) snake.direction = 1;
        if (Keyboard::isKeyPressed(Keyboard::Right)) snake.direction = 2;
        if (Keyboard::isKeyPressed(Keyboard::Up)) snake.direction = 3;
        if (Keyboard::isKeyPressed(Keyboard::Down)) snake.direction = 0;

        if (timer > DELAY) {
            timer = 0;
            Tick(snake, fruit);
        }

        ////// draw  ///////
        window.clear();

        drawGrid(window, sprite1);
        drawSnake(window, snake, sprite2);
        drawFruit(window, fruit, sprite2);

        window.display();
    }

    return 0;
}
