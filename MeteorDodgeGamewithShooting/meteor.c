#include "meteor.h"

static Meteor meteors[MAX_METEORS];
static Color meteorColors[MAX_METEORS];
#define minBright 100

// ������ � ���� �Լ�
static Meteor CreateRandomMeteor(int index) {
    Meteor m;

    // ������: 10~40
    m.radius = (float)(rand() % 31 + 10);

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
    case 0: // Top
        m.position = (Vector2){ rand() % SCREEN_WIDTH, -m.radius };
        break;
    case 1: // Bottom
        m.position = (Vector2){ rand() % SCREEN_WIDTH, SCREEN_HEIGHT + m.radius };
        break;
    case 2: // Left
        m.position = (Vector2){ -m.radius, rand() % SCREEN_HEIGHT };
        break;
    case 3: // Right
        m.position = (Vector2){ SCREEN_WIDTH + m.radius, rand() % SCREEN_HEIGHT };
        break;
    }

    //ȭ�� �ܺο��� ���η� ������ ����
    float angle = ((float)(rand() % 360)) * DEG2RAD;
    Vector2 direction = (Vector2){
        cosf(angle),
        sinf(angle)
    };

    // �ӵ�
    float speed = 5;
    m.velocity = (Vector2){ direction.x * speed, direction.y * speed };

    return m;
}

// � �ʱ�ȭ
void InitMeteors() {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < MAX_METEORS; i++) {
        meteors[i] = CreateRandomMeteor(i);
    }
}

//� ��ġ ������Ʈ-17
void UpdateMeteors() {
    for (int i = 0; i < MAX_METEORS; i++) {
        meteors[i].position.x += meteors[i].velocity.x;
        meteors[i].position.y += meteors[i].velocity.y;

        // ȭ���� ����� �ٽ� ����
        if (meteors[i].position.x < -100 || meteors[i].position.x > SCREEN_WIDTH + 100 ||
            meteors[i].position.y < -100 || meteors[i].position.y > SCREEN_HEIGHT + 100) {
            meteors[i] = CreateRandomMeteor(i);
        }
    }
}

// � �׸���
void DrawMeteors() {
    for (int i = 0; i < MAX_METEORS; i++) {
        DrawCircleV(meteors[i].position, meteors[i].radius, meteorColors[i]);
    }
}
