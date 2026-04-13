#include <stdio.h>
#include "raylib.h"

#define SNAKE_SEGMENT_SIZE 20
#define INITIAL_SNAKE_SIZE 200;
#define INITIAL_SPEED 5
#define SCREEN_WIDTH 2048
#define SCREEN_HEIGHT 1024
#define TARGET_FPS 60
#define ARBITRARY_SNAKE_SIZE_MAX 200

// TODO: do you need that ?
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

typedef struct SnakePart
{
  Vector2 coords;
  Direction direction;
} SnakePart;

typedef struct Snake
{
  SnakePart parts[ARBITRARY_SNAKE_SIZE_MAX];
  size_t size;
  size_t head_i;
  size_t tail_i;
  int speed;
} Snake;

void Snake_Init(Snake *s)
{
  int head_x = SCREEN_WIDTH / 2;

  s->size = INITIAL_SNAKE_SIZE;
  s->head_i = s->size - 1;
  s->tail_i = s->head_i + 1 - s->size;
  s->speed = INITIAL_SPEED;

  int tail_x = head_x - (s->size - 1) * SNAKE_SEGMENT_SIZE;

  for (size_t i = 0; i <= s->head_i; i++)
  {
    s->parts[i] = (SnakePart){(Vector2){tail_x + i * SNAKE_SEGMENT_SIZE, SCREEN_HEIGHT / 2}, (Direction)RIGHT};
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

  return speed_unit_vector;
}

void Snake_ChangeHeadDirection(Snake *s, Direction direction)
{
  if (s->size <= 1 && direction != s->parts[s->head_i].direction)
  {
    s->parts[s->head_i].direction = direction;
    return;
  }

  SnakePart head = s->parts[s->head_i];
  SnakePart body_first_segment = s->parts[s->head_i - 1];

  // only allow head to turn if the next segment already
  // follows the head in the same direction
  if (head.direction == body_first_segment.direction && head.direction != direction)
  {
    s->parts[s->head_i].direction = direction;
  }
}

void Snake_ChangeBodyDirection(Snake *s)
{

  if (s->size > 1)
  {
    for (size_t i = s->tail_i; i < s->head_i; i++)
    {

      if (s->parts[i].direction == s->parts[i + 1].direction)
        continue;

      // determine if there's a direction change at the next segment
      //  based on that direction determin whether the current segment
      // should be x or y  aligned with the next segment
      // if the current segment is already aligned, change direction to
      // the direction of the next segment.
      // if (s->parts[i].direction ->parts[i + 1])

      bool shouldTurnUpOrDown = (s->parts[i].direction == RIGHT || s->parts[i].direction == LEFT) &&
                                (s->parts[i].coords.x == s->parts[i + 1].coords.x);

      bool shouldTurnLeftOrRight = (s->parts[i].direction == UP || s->parts[i].direction == DOWN) &&
                                   (s->parts[i].coords.y == s->parts[i + 1].coords.y);

      bool shouldTurnInTheDirectionOfTheNextSegment = shouldTurnLeftOrRight || shouldTurnUpOrDown;

      if (shouldTurnInTheDirectionOfTheNextSegment)
      {
        s->parts[i].direction = s->parts[i + 1].direction;
      }
    }
  }
}

void Snake_Move(Snake *s)
{
  if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
  {
    Snake_ChangeHeadDirection(s, RIGHT);
  }

  if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
  {
    Snake_ChangeHeadDirection(s, UP);
  }

  if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
  {
    Snake_ChangeHeadDirection(s, DOWN);
  }

  if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
  {
    Snake_ChangeHeadDirection(s, LEFT);
  }

  // When the snake moves one the distance
  // equal to its segment size, reavaluate
  // directions of each segment
  Snake_ChangeBodyDirection(s);

  // move snake parts
  for (size_t i = 0; i <= s->head_i; i++)
  {
    Vector2 segment_unit_speed_vector = get_unit_speed_vector(s->parts[i].direction);
    s->parts[i].coords.x += s->speed * segment_unit_speed_vector.x;
    s->parts[i].coords.y += s->speed * segment_unit_speed_vector.y;
  }
}

void Snake_Draw(Snake *s)
{
  for (size_t i = 0; i <= s->head_i; i++)
  {
    DrawRectangle(s->parts[i].coords.x, s->parts[i].coords.y, SNAKE_SEGMENT_SIZE, SNAKE_SEGMENT_SIZE, MAROON);
    // DrawRectangleLines(s->parts[i].coords.x + 1, s->parts[i].coords.y + 1, SNAKE_SEGMENT_SIZE - 1, SNAKE_SEGMENT_SIZE - 1, RAYWHITE);
  }
}

void Update(Snake *s)
{
  Snake_Move(s);
}

const char *DirectionToString(Direction direction)
{
  switch (direction)
  {
  case UP:
    return "UP";
  case RIGHT:
    return "RIGHT";
  case DOWN:
    return "DOWN";
  case LEFT:
    return "LEFT";
  default:
    return "NO DIRECTION";
  }
}

void Snake_Stringify(Snake *s)
{
  printf("\nSnake Info ================\n");
  printf("Head Idx: %d, Tail Idx: %d, Size: %d, Speed: %d\n", s->head_i, s->tail_i, s->size, s->speed);
  for (size_t i = s->tail_i; i <= s->head_i; i++)
  {
    char *direction = DirectionToString(s->parts[i].direction);
    printf("\n Segment i: %d  x: %d y: %d direction: %s \n",
           i, s->parts[i].coords.x, s->parts[i].coords.y, direction);
  }
  printf("\n=================\n");
}

void Draw(Snake *s)
{
  ClearBackground(BLACK);
  BeginDrawing();

  Snake_Draw(s);

  EndDrawing();
}

int main()
{
  Snake s;

  Snake_Init(&s);

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake Game");
  SetTargetFPS(TARGET_FPS);

  while (!WindowShouldClose())
  {
    Update(&s);
    Draw(&s);
    Snake_Stringify(&s);
  }

  CloseWindow();
  return 0;
}