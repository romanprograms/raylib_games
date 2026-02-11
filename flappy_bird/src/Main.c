#include "raylib.h"
#include <stdio.h>

int main(void) {
  // Initialization
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Flappy Bird made with Raylib");
  SetTargetFPS(60);

  // Main game loop
  while (!WindowShouldClose()) {
    // Update
    // TODO: update your variable here

    // Draw
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("This is where Flappy Bird Game will be drawn", 190, 200, 20,
             LIGHTGRAY);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
