#pragma once
#include "bullet.h"
#include "raylib.h"


static int shootCooldown = 0;

//�Ѿ� ����, �׳� ������ ��� ��ġ���� �����ǰ�
void FireBullet(Bullet *bullets) {
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
void UpdateBullets(Bullet* bullets) {
	if (shootCooldown > 0) shootCooldown--;

	for (int i = 0; i < MAX_BULLETS; i++) {
		if (bullets[i].active) {
			bullets[i].position.x += bullets[i].velocity.x;
			bullets[i].position.y += bullets[i].velocity.y;

			//ȭ�� ������ ������ ����
			if (bullets[i].position.x < 0 || bullets[i].position.x > GetScreenWidth()
				|| bullets[i].position.y < 0 || bullets[i].position.y > GetScreenHeight()) {
				bullets[i].active = false;
			}
		}
	}
}

//�Ѿ� �׸���
void DrawBullets(Bullet* bullets) {
	for (int i = 0; i < MAX_BULLETS; i++) {
		if (bullets[i].active) {
			DrawCircleV(bullets[i].position, BULLET_RADIUS, RED);
		}
	}
}