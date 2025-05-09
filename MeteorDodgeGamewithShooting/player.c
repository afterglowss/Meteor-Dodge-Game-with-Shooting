#include "player.h"
#include <stdio.h>
#include "raylib.h"


void InitPlayer(Player* playerRef) {

	playerRef->position = (Vector2){ 400, 300 };  // �ʱ� ��ġ
	playerRef->velocity = (Vector2){ 0, 0 };      // �ʱ� �ӵ�
}

void DrawPlayer(Player playerRef) {
	DrawCircleV(playerRef.position, 10.0f, RED);
}


void UpdatePlayer(Player* playerRef) {

	if (IsKeyDown(KEY_UP)) playerRef->position.y -= 1.0f;
	if (IsKeyDown(KEY_DOWN))  playerRef->position.y += 1.0f;
	if (IsKeyDown(KEY_LEFT))  playerRef->position.x -= 1.0f;
	if (IsKeyDown(KEY_RIGHT)) playerRef->position.x += 1.0f;

}
