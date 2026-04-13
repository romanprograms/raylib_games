#include <stdio.h>
#include "raylib.h"

#define SNAKE_SEGMENT_SIZE 20
#define INITIAL_SNAKE_SIZE 20;
#define SNAKE_ARBITRARY_SIZE_MAX 200
#define INITIAL_SPEED 1
#define SCREEN_WIDTH 2048
#define SCREEN_HEIGHT 1024
#define TARGET_FPS 60

// TODO: do you need that ?
const Vector2 UP_UNIT_VECTOR = {0.0f, -1.0f};
const Vector2 RIGHT_UNIT_VECTOR = {1.0f, 0.0f};
const Vector2 DOWN_UNIT_VECTOR = {0.0f, 1.0f};
const Vector2 LEFT_UNIT_VECTOR = {-1.0f, 0.0f};

typedef enum Direction
{
  UP,
  DOWN,
  LEFT,
  RIGHT
} Direction;

typedef struct SnakeSegment
{
  Vector2 position;
  Direction direction;
} SnakeSegment;

typedef struct Snake
{
  // to avoid using a vector or creating a singly/doubly
  // linked list, we're just gonna use a fixed size
  // array of sufficient length that we will make sure
  // to never exceed.
  SnakeSegment parts[SNAKE_ARBITRARY_SIZE_MAX];
  size_t size;
  size_t head_idx;
  size_t tail_idx;
  int speed;
} Snake;

void Snake__Init(Snake *s)
{
  int head_x = SCREEN_WIDTH / 2;

  s->size = INITIAL_SNAKE_SIZE;
  s->head_idx = s->size - 1;
  s->tail_idx = s->head_idx + 1 - s->size;
  s->speed = INITIAL_SPEED;

  int tail_x = head_x - (s->size - 1) * SNAKE_SEGMENT_SIZE;

  for (size_t i = 0; i <= s->head_idx; i++)
  {
    s->parts[i] = (SnakeSegment){(Vector2){tail_x + i * SNAKE_SEGMENT_SIZE, SCREEN_HEIGHT / 2}, (Direction)RIGHT};
  }
}

Vector2 GetUnitSpeedVector(Direction direction)
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

void Snake__ChangeHeadDirection(Snake *s, Direction direction)
{
  if (s->size <= 1 && direction != s->parts[s->head_idx].direction)
  {
    s->parts[s->head_idx].direction = direction;
    return;
  }

  SnakeSegment head = s->parts[s->head_idx];
  SnakeSegment neck = s->parts[s->head_idx - 1];

  bool hasHeadDirectionChanged = head.direction != direction;

  // only allow head to turn if the neck already
  // follows the head in the same direction
  if (head.direction == neck.direction && hasHeadDirectionChanged)
  {
    s->parts[s->head_idx].direction = direction;
  }
}

void Snake__ChangeBodyDirection(Snake *s)
{
  if (s->size > 1)
  {
    // iterate over body segments only (i < s-> head_idx)
    for (size_t i = s->tail_idx; i < s->head_idx; i++)
    {

      if (s->parts[i].direction == s->parts[i + 1].direction)
        continue;

      // determine if there's a direction change at the next segment
      // based on that direction determin whether the current segment
      // should be x or y  aligned with the next segment
      // if the current segment is already aligned, change direction to
      // the direction of the next segment.
      bool shouldTurnUpOrDown = (s->parts[i].direction == RIGHT || s->parts[i].direction == LEFT) &&
                                (s->parts[i].position.x == s->parts[i + 1].position.x);

      bool shouldTurnLeftOrRight = (s->parts[i].direction == UP || s->parts[i].direction == DOWN) &&
                                   (s->parts[i].position.y == s->parts[i + 1].position.y);

      bool shouldTurnInTheDirectionOfTheNextSegment = shouldTurnLeftOrRight || shouldTurnUpOrDown;

      if (shouldTurnInTheDirectionOfTheNextSegment)
      {
        s->parts[i].direction = s->parts[i + 1].direction;
      }
    }
  }
}

void Snake__Move(Snake *s)
{
  if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
  {
    Snake__ChangeHeadDirection(s, RIGHT);
  }

  if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
  {
    Snake__ChangeHeadDirection(s, UP);
  }

  if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
  {
    Snake__ChangeHeadDirection(s, DOWN);
  }

  if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
  {
    Snake__ChangeHeadDirection(s, LEFT);
  }

  Snake__ChangeBodyDirection(s);

  // move snake parts
  for (size_t i = 0; i <= s->head_idx; i++)
  {
    Vector2 segment_unit_speed_vector = GetUnitSpeedVector(s->parts[i].direction);
    s->parts[i].position.x += s->speed * segment_unit_speed_vector.x;
    s->parts[i].position.y += s->speed * segment_unit_speed_vector.y;
  }
}

void Snake__Draw(Snake *s)
{
  for (size_t i = 0; i <= s->head_idx; i++)
  {
    DrawRectangle(s->parts[i].position.x, s->parts[i].position.y, SNAKE_SEGMENT_SIZE, SNAKE_SEGMENT_SIZE, MAROON);
    // draws white border around a segment
    // DrawRectangleLines(s->parts[i].position.x + 1, s->parts[i].position.y + 1, SNAKE_SEGMENT_SIZE - 1, SNAKE_SEGMENT_SIZE - 1, RAYWHITE);
  }
}

void Update(Snake *s)
{
  Snake__Move(s);
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

void Snake__Log(Snake *s)
{
  printf("\nSnake Info ================\n");
  printf("Head Idx: %d, Tail Idx: %d, Size: %d, Speed: %d\n", s->head_idx, s->tail_idx, s->size, s->speed);
  for (size_t i = s->tail_idx; i <= s->head_idx; i++)
  {
    char *direction = DirectionToString(s->parts[i].direction);
    printf("\n Segment i: %d  x: %d y: %d direction: %s \n",
           i, s->parts[i].position.x, s->parts[i].position.y, direction);
  }
  printf("\n=================\n");
}

void Draw(Snake *s)
{
  ClearBackground(BLACK);
  BeginDrawing();

  Snake__Draw(s);

  EndDrawing();
}

int main()
{
  Snake s;

  Snake__Init(&s);

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake Game");
  SetTargetFPS(TARGET_FPS);

  while (!WindowShouldClose())
  {
    Update(&s);
    Draw(&s);
    Snake__Log(&s);
  }

  CloseWindow();
  return 0;
}