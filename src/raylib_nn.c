#include <stdio.h>
#include "raylib.h"

int main(void)
{
  const int screenWidth = 800;
  const int screenHeight = 600;

  InitWindow(screenWidth, screenHeight, "test");
  SetTargetFPS(60);

  while(!WindowShouldClose()) {
    BeginDrawing();
    {
      ClearBackground(RAYWHITE);
      DrawText("Hello", screenWidth/2, screenHeight/2, 69, BLUE);
    }
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
