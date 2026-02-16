#include "raylib.h"
#include <stdio.h>

int main(void)
{
  // Initialization
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Flappy Bird made with Raylib");

  Vector2 ballPosition = {(float)screenWidth / 2.0f, (float)screenHeight / 2.0f};

  SetTargetFPS(60);
  // Main game loop
  while (!WindowShouldClose())
  {
    // Update
    if (IsKeyDown(KEY_D))
      ballPosition.x += 2.0f;
    if (IsKeyDown(KEY_A))
      ballPosition.x -= 2.0f;
    if (IsKeyDown(KEY_W))
      ballPosition.y -= 2.0f;
    if (IsKeyDown(KEY_S))
      ballPosition.y += 2.0f;

    // Draw
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("This is where Flappy Bird Game will be drawn", 10, 10, 20,
             DARKGRAY);
    DrawCircleV(ballPosition, 50, MAROON);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
