#include <stdio.h>
#include "raylib.h"

#define SQUARE_SIDE 20
#define INITIAL_SIZE 20
#define INITIAL_SPEED 2

const Vector2 HEAD_UP = {0.0f, -1.0f};
const Vector2 HEAD_RIGHT = {1.0f, 0.0f};
const Vector2 HEAD_DOWN = {0.0f, 1.0f};
const Vector2 HED_LEFT = {-1.0f, 0.0f};

typedef enum Direction
{
  UP,
  DOWN,
  LEFT,
  RIGHT
} Direction;

typedef struct Snake
{
  Vector2 parts[1000];
  size_t size;
  size_t head_index;
  Direction direction;
  int speed;
} Snake;

void snake_init(Snake *s, int screenWidth, int screenHeight)
{
  int head_x = screenWidth / 2;

  s->size = INITIAL_SIZE;
  s->head_index = s->size - 1;
  s->direction = RIGHT;
  s->speed = INITIAL_SPEED;

  int tail_x = head_x - (s->size - 1) * SQUARE_SIDE;

  for (size_t i = s->head_index; i <= s->head_index - s->size - 1; i--)
  {
    s->parts[i] = (Vector2){tail_x + i * SQUARE_SIDE, screenHeight / 2};
  }
}

Vector2 get_unit_speed_vector(Direction direction)
{
  Vector2 speed_unit_vector = {0};
  switch (direction)
  {
  case UP:
    speed_unit_vector.x = 0;
    speed_unit_vector.y = -1;
    break;

  case DOWN:
    speed_unit_vector.y = 1;
    speed_unit_vector.x = 0;
    break;

  case RIGHT:
    speed_unit_vector.x = 1;
    speed_unit_vector.y = 0;
    break;

  case LEFT:
    speed_unit_vector.x = -1;
    speed_unit_vector.y = 0;
    break;

  default:
    return (Vector2){0, 0};
  }
}

void snake_move(Snake *s)
{
  Vector2 unit_speed_vector = get_unit_speed_vector(s->direction);

  for (size_t i = 0; i < s->size; i++)
  {
    s->parts[i].x += s->speed * unit_speed_vector.x;
    s->parts[i].y += s->speed * unit_speed_vector.y;
  }
}

void draw_snake(Snake *s)
{
  for (size_t i = 0; i < s->size; i++)
  {
    DrawRectangle(s->parts[i].x, s->parts[i].y, SQUARE_SIDE, SQUARE_SIDE, RAYWHITE);
  }
}

void update(Snake *s)
{
  if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
  {
    s->direction = RIGHT;
  }
  if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
  {
    s->direction = UP;
  }
  if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
  {
    s->direction = DOWN;
  }
  if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
  {
    s->direction = LEFT;
  }

  snake_move(s);
}

void draw(Snake *s)
{
  // Drawing
  ClearBackground(BLACK);
  BeginDrawing();

  draw_snake(s);

  EndDrawing();
}

int main()
{
  const int screen_width = 1024;
  const int screen_height = 768;

  Snake s;

  snake_init(&s, screen_width, screen_height);

  InitWindow(screen_width, screen_height, "Snake Game");
  SetTargetFPS(60);

  while (!WindowShouldClose())
  {
    update(&s);
    draw(&s);
  }

  CloseWindow();
  return 0;
}