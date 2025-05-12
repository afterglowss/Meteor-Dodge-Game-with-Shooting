#pragma once
#include "bullet.h"
#include "raylib.h"

static Bullet bullets[MAX_BULLETS];
static int shootCooldown = 0;

//�Ѿ� ����, �׳� ������ ��� ��ġ���� �����ǰ�
void FireBullet() {
	if (shootCooldown > 0) return;

	for (int i = 0; i < MAX_BULLETS; i++) {
		if (!bullets[i].active) {
			bullets[i].active = true;

			//�߾ӿ��� ����, ���� �÷��̾� ��ġ���� ����
			bullets[i].position = (Vector2){ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };

			//���� ����, ���� �÷��̾� �������� ����
			Vector2 direction = { 1,0 };
			bullets[i].velocity = (Vector2){ direction.x * BULLET_SPEED, direction.y * BULLET_SPEED };

			shootCooldown = SHOOT_COOLDOWN_FRAMES;
			break;
		}
	}
}

//�Ѿ� ��ġ ������Ʈ
void UpdateBullets() {}

//�Ѿ� �׸���
void DrawBullets() {
	for (int i = 0; i < MAX_BULLETS; i++) {
		if (bullets[i].active) {
			DrawCircleV(bullets[i].position, BULLET_RADIUS, RED);
		}
	}
}