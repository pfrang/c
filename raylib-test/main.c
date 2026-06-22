
#include <raylib.h>
#include <stdio.h>

int main() {

  SetConfigFlags(FLAG_VSYNC_HINT);
  InitWindow(800, 600, "hei");

  // SetTargetFPS(2000);
  Rectangle box = {100, 100, 200, 50};
  while (!WindowShouldClose()) {
    Vector2 mouse = GetMousePosition();
    bool hovered = CheckCollisionPointRec(mouse, box);
    bool clicked = hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    if (clicked) {
      printf("Clicked\n");
    }
    BeginDrawing();
    DrawFPS(20, 20);

    ClearBackground(RAYWHITE);
    DrawRectangleRec(box, hovered ? LIGHTGRAY : GRAY);
    DrawText("Hei", 10, 10, 20, RED);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
