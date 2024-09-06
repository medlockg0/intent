/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

For a C++ project simply rename the file to .cpp and re-run the build script 

-- Copyright (c) 2020-2024 Jeffery Myers
--
--This software is provided "as-is", without any express or implied warranty. In no event 
--will the authors be held liable for any damages arising from the use of this software.

--Permission is granted to anyone to use this software for any purpose, including commercial 
--applications, and to alter it and redistribute it freely, subject to the following restrictions:

--  1. The origin of this software must not be misrepresented; you must not claim that you 
--  wrote the original software. If you use this software in a product, an acknowledgment 
--  in the product documentation would be appreciated but is not required.
--
--  2. Altered source versions must be plainly marked as such, and must not be misrepresented
--  as being the original software.
--
--  3. This notice may not be removed or altered from any source distribution.

*/

#include <stdio.h>
#include "raylib.h"
#include "raymath.h"

typedef struct Player {
	Vector2 position;
	float speed;
} Player;

int main(void) {
	const int screenWidth = 1280;
	const int screenHeight = 720;

	InitWindow(screenWidth, screenHeight, "intent");

	Player player = { 0 };
	player.position = (Vector2){ (float)screenWidth/2, (float)screenHeight/2 };
	player.speed = 25.0f;

	Image image = LoadImage("resources/player.png");
	Texture texture = LoadTextureFromImage(image);
	UnloadImage(image);

	Camera2D camera = { 0 };
	camera.offset = (Vector2){ (float)screenWidth/2, (float)screenHeight/2 };
	camera.target = (Vector2){ player.position.x, player.position.y };
	camera.rotation = 0.0f;
	camera.zoom = 5.3f;

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		Vector2 inputDirection = { 0, 0 };
		float deltaTime = GetFrameTime();

		if (IsKeyDown(KEY_RIGHT)) inputDirection.x += 1.0f;
		if (IsKeyDown(KEY_LEFT)) inputDirection.x -= 1.0f;
		if (IsKeyDown(KEY_UP)) inputDirection.y -= 1.0f;
		if (IsKeyDown(KEY_DOWN)) inputDirection.y += 1.0f;
		
		inputDirection = Vector2Normalize(inputDirection);

		player.position = Vector2Add(player.position, Vector2Scale(inputDirection, player.speed*deltaTime));
		
		BeginDrawing();

			Color STEELGRAY = { 0x22, 0x20, 0x34, 0xff };

			ClearBackground(STEELGRAY);

			BeginMode2D(camera);

				DrawTexturePro(texture, (Rectangle){ 0, 0, texture.width, texture.height }, (Rectangle){ player.position.x, player.position.y, texture.width, texture.height }, (Vector2){ (float)texture.width/2, texture.height }, 0.0f, WHITE);

				//DrawLine((int)camera.target.x, 0, (int)camera.target.x, screenHeight, BLACK);
				//DrawLine(0, (int)camera.target.y, screenWidth, (int)camera.target.y, BLACK);
			
			EndMode2D();

		EndDrawing();
	}

	UnloadTexture(texture);

	CloseWindow();

	return 0;
}