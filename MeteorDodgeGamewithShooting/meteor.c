#include "meteor.h"


static Color meteorColors[MAX_METEORS];
#define minBright 100

// ������ � ���� �Լ�
static void RespawnMeteor(Meteor* m, int index) {
    m->radius = (float)(rand() % 31 + 10);

    // ������ ���� ����(���)
    meteorColors[index] = (Color){
    minBright + rand() % (256 - minBright),
    minBright + rand() % (256 - minBright),
    minBright + rand() % (256 - minBright),
    255
    };

    // ȭ�� �� ������ ��ġ
    int edge = rand() % 4;
    switch (edge) {
    case 0: // TOP
        m->position = (Vector2){ rand() % SCREEN_WIDTH, -m->radius };
        break;
    case 1: // BOTTOM
        m->position = (Vector2){ rand() % SCREEN_WIDTH, SCREEN_HEIGHT + m->radius };
        break;
    case 2: // LEFT
        m->position = (Vector2){ -m->radius, rand() % SCREEN_HEIGHT };
        break;
    case 3: // RIGHT
        m->position = (Vector2){ SCREEN_WIDTH + m->radius, rand() % SCREEN_HEIGHT };
        break;
    }


    //ȭ�� �ܺο��� ���η� ������ ����
    float angle = ((float)(rand() % 360)) * DEG2RAD;
    Vector2 direction = (Vector2){
        cosf(angle),
        sinf(angle)
    };

    //�ӵ�
    float speed = 3;
    m->velocity = (Vector2){ direction.x * speed, direction.y * speed };
}


// � �ʱ�ȭ
void InitMeteors(Meteor* meteors) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < MAX_METEORS; i++) {
        RespawnMeteor(&meteors[i], i);
    }
}

//� ��ġ ������Ʈ-17
void UpdateMeteors(Meteor* meteors, Player* playerRef, Bullet* bullets) {
    for (int i = 0; i < MAX_METEORS; i++) {
        meteors[i].position.x += meteors[i].velocity.x;
        meteors[i].position.y += meteors[i].velocity.y;

        if (meteors[i].position.x < -100 || meteors[i].position.x > SCREEN_WIDTH + 100 ||
            meteors[i].position.y < -100 || meteors[i].position.y > SCREEN_HEIGHT + 100) {
            RespawnMeteor(&meteors[i], i);  // ������ meteor ����
        }
    }

    //�-�Ѿ� �浹 ó��: 20
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].active) continue;

        for (int j = 0; j < MAX_METEORS; j++) {
            float dist = Vector2Distance(bullets[i].position, meteors[j].position);
            if (dist < meteors[j].radius + BULLET_RADIUS) {
                bullets[i].active = false;
                RespawnMeteor(&meteors[j], j);
                break;
            }
        }
    }

    // ���� ������ ��� �浹 �˻� ����
    if (playerRef->isCollision) {
        double diffTime = GetTime() - playerRef->deathTime;
        if (diffTime < 2.0) return;  // ���� ���� ���¸� �浹 �˻� �ǳʶ�
        else playerRef->isCollision = false;  // ���� �ð� �������� �ʱ�ȭ
    }

    //�-�÷��̾� �浹 ó��: 19
    for (int i = 0; i < MAX_METEORS; i++) {
        float dist = Vector2Distance(playerRef->position, meteors[i].position);
        if (dist < meteors[i].radius + PLAYER_SIZE / 2.0f) {
            playerCollision(playerRef);
            playerRef->lives--;
            break;
        }
    }
}

// � �׸���
void DrawMeteors(Meteor* meteors) {
    for (int i = 0; i < MAX_METEORS; i++) {
        DrawCircleV(meteors[i].position, meteors[i].radius, meteorColors[i]);
    }
}