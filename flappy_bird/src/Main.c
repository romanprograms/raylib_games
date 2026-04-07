#include "raylib.h"
#include <stdio.h>

// Initialization
#define MAX_TUBES 100
#define BIRD_RADIUS 24
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
static float gravity = 1.0f;

static Bird bird = {0};

//------------------------------------------------------------------------------------
// Module Functions Declaration (local)
//------------------------------------------------------------------------------------
static void InitGame(void);        // Initialize game
static void UpdateGame(void);      // Update game (one frame)
static void DrawGame(void);        // Draw game (one frame)
static void UnloadGame(void);      // Unload game
static void UpdateDrawFrame(void); // Update and Draw (one frame)

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
    UpdateDrawFrame();
  }

  // De-Initialization
  UnloadGame(); // Close window and OpenGL context

  CloseWindow(); // Close window and OpenGL context

  return 0;
}

void InitGame(void)
{
  bird.position = (Vector2){150, screenHeight / 2.0f};
  bird.radius = BIRD_RADIUS;
  bird.color = DARKGRAY;
}

void UpdateDrawFrame(void)
{
  UpdateGame();
  DrawGame();
}

void DrawGame(void)
{
  BeginDrawing();
  ClearBackground(RAYWHITE);
  DrawCircleV(bird.position, bird.radius, bird.color);
  DrawRectangle(screenWidth - 50, 0, 50, 150, RED);
  EndDrawing();
}

void UpdateGame(void)
{

  if (IsKeyDown(KEY_SPACE))
    bird.position.y -= 2.0f;

  bird.position.y += gravity;
}

void UnloadGame(void)
{
  // TODO: Unload all dynamic data if it exists
}