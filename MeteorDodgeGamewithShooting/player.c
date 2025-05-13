#include "player.h"
#include <stdio.h>
#include "raylib.h"


void InitPlayer(Player* playerRef) {

    playerRef->position = (Vector2){ 400, 300 };  // �ʱ� ��ġ
    playerRef->velocity = (Vector2){ 0, 0 };      // �ʱ� �ӵ�
    playerRef->angle = 0.0f;
}


void DrawPlayer(Player* playerRef) {

    // �÷��̾� ��ü
    DrawCircleV(playerRef->position, 5.0f, RED);

}



#define DEG2RAD (PI / 180.0f)
#define TURN_SPEED 400.0f // degree/sec
#define MAX_SPEED 0.1f

void UpdatePlayer(Player* playerRef) {
    float deltaTime = GetFrameTime();

    
    float rad = (PI / 180.0f);
    float turnspeed = 360.0;
    float maxspeed = 0.1f;

    // �÷��̾� ȸ��
    if (IsKeyDown(KEY_LEFT))  playerRef->angle -= turnspeed * deltaTime;
    if (IsKeyDown(KEY_RIGHT)) playerRef->angle += turnspeed * deltaTime;

    // �ӵ� ����
    float acceleration = 0.0f;
    if (IsKeyDown(KEY_UP)) {
        acceleration = PLAYER_ACCEL;
    }
    else {
        // ����
        playerRef->velocity.x *= PLAYER_FRICTION;
        playerRef->velocity.y *= PLAYER_FRICTION;
    }

    // �ٶ󺸴� �������� �ӵ� ����
    Vector2 direction = {
        cosf(playerRef->angle * rad),
        sinf(playerRef->angle * rad)
    };

    //�ӵ� ������Ʈ
    playerRef->velocity.x += direction.x * acceleration * deltaTime;
    playerRef->velocity.y += direction.y * acceleration * deltaTime;

    // �ӵ� ����
    float speed = Vector2Length(playerRef->velocity);
    if (speed > maxspeed) {
        playerRef->velocity = Vector2Scale(Vector2Normalize(playerRef->velocity), maxspeed);
    }

    // ��ġ ������Ʈ
    playerRef->position.x += playerRef->velocity.x;
    playerRef->position.y += playerRef->velocity.y;

}

