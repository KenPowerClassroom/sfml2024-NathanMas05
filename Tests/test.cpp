#include "pch.h"

const int HEIGHT = 25;
const int WIDTH = 40;
const int tileSize = 18;

#include"../16_SFML_Games/Grid.h"
#include"../16_SFML_Games/Player.h"
#include "../16_SFML_Games/snake.cpp"

TEST(Snake, MovesCorrectly)
{
    Snake snake;
    snake.direction = 2; // Move RIGHT
    snake.move();

    EXPECT_EQ(GRID_WIDTH / 2 + 1, snake.segments[0].x);
    EXPECT_EQ(GRID_HEIGHT / 2, snake.segments[0].y);
}

TEST(Snake, GrowsWhenEatingFood)
{
    Snake snake;
    Fruit fruit;
    fruit.x = snake.segments[0].x;
    fruit.y = snake.segments[0].y;

    snake.grow();

    EXPECT_EQ(INITIAL_SNAKE_LENGTH + 1, snake.length);
}

TEST(Snake, CollidesWithItself)
{
    Snake snake;
    snake.length = 5;

    for (int i = 1; i < 5; i++) {
        snake.segments[i].x = snake.segments[0].x;
        snake.segments[i].y = snake.segments[0].y;
    }

    EXPECT_TRUE(snake.checkCollision());
}

TEST(Snake, WrapsAroundGrid)
{
    Snake snake;
    snake.segments[0].x = GRID_WIDTH - 1;
    snake.direction = 2; // Move RIGHT
    snake.move();

    EXPECT_EQ(0, snake.segments[0].x);
    EXPECT_EQ(GRID_HEIGHT / 2, snake.segments[0].y);
}
