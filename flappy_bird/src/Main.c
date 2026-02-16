#include "raylib.h"
#include <stdio.h>

void InitGame(void);

// Initialization
#define MAX_TUBES 100
#define FLOPPY_RADIUS 24
#define TUBES_WIDTH 80

//-----------------------------------
// Types and Structures definitions
//-----------------------------------
typedef struct Bird
{
  Vector2 position;
  int radius;
  Color color;
} Bird;

//---------------------------------
// Global Variables Declaratin
//---------------------------------
static const int screenWidth = 800;
static const int screenHeight = 450;

static bool isGameOver = false;

static Bird bird = {0};

int main(void)
{
  // Initialization
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Flappy Bird made with Raylib");

  InitGame();

  SetTargetFPS(60);
  // Main game loop
  while (!WindowShouldClose())
  {
    // Update
    if (IsKeyDown(KEY_D))
      bird.position.x += 2.0f;
    if (IsKeyDown(KEY_A))
      bird.position.x -= 2.0f;
    if (IsKeyDown(KEY_W))
      bird.position.y -= 2.0f;
    if (IsKeyDown(KEY_S))
      bird.position.y += 2.0f;

    // Draw
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawCircleV(bird.position, 25, MAROON);
    DrawRectangle(200, 0, 50, 150, RED);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}

void InitGame(void)
{
  bird.position = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
}

void DrawGame(void)
{
}

void UpdateGame(void)
{
}

void UnloadGame(void)
{
  // TODO: Unload all dynamic data if it exists
}