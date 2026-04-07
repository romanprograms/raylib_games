#include <stdio.h>
#include "raylib.h"

#define SQUARE_SIDE 20

const Vector2 UP = {0.0f, -1.0f};
const Vector2 RIGHT = {1.0f, 0.0f};
const Vector2 DOWN = {0.0f, 1.0f};
const Vector2 LEFT = {-1.0f, 0.0f};

typedef struct Snake
{
  Vector2 parts[1000];
  size_t size;
  size_t head_index;
} Snake;

void snake_init(Snake *s, int screenWidth, int screenHeight)
{
  int head_x = screenWidth / 2;

  s->size = 5;
  s->head_index = s->size - 1;

  int tail_x = head_x - (s->size - 1) * SQUARE_SIDE;

  for (size_t i = 0; i < s->size; i++)
  {
    s->parts[i] = (Vector2){tail_x + i * SQUARE_SIDE, screenHeight / 2};
  }
}

void snake_move(Snake *s)
{
  s->head_index++;
}

void draw_snake(Snake *s)
{

  // DrawRectangle(s->x, square_position->y, SQUARE_SIDE, SQUARE_SIDE, RAYWHITE);
}

void update(int *speed, Vector2 *direction, Snake *s)
{
  if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
  {
    *direction = RIGHT;
  }
  if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
  {
    *direction = UP;
  }
  if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
  {
    *direction = DOWN;
  }
  if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
  {
    *direction = LEFT;
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
  const int speed = 2.0;

  Snake s;
  Vector2 direction = RIGHT;

  InitWindow(screen_width, screen_height, "Snake Game");
  SetTargetFPS(60);

  while (!WindowShouldClose())
  {
    update(&speed, &direction, &s);
    draw(&s);
  }

  CloseWindow();
  return 0;
}