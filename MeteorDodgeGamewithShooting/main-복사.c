#include "raylib.h"
#include "game.h"
#include "player.h"
#include "meteor.h"
#include "bullet.h"

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Meteor Dodge Game With Shooting");
    SetTargetFPS(60);

    Player player;
    InitPlayer(&player);

    Meteor meteors[MAX_METEORS];
    InitMeteors();

    Bullet bullets[MAX_BULLETS] = { 0 };

    bool gameStarted = false;
    bool gameOver = false;
    int selectedMenu = 0;
    const char* menuItems[] = { "Start", "Score", "Credits", "Exit" };
    const int menuCount = 4;

    int score = 0;
    int highScore = 0;  // ���������� ���� �ʿ�, meteor.c�������� ���Ǹ� �ִ� �� ������

    while (!WindowShouldClose())
    {
        if (gameStarted && IsKeyPressed(KEY_BACKSPACE)) {
            gameStarted = false;
            continue;
        }
        //���� ���� ��
        if (!gameStarted) {     
            BeginDrawing();
            ClearBackground(BLACK);
            DrawUI(player, score, gameOver, gameStarted, selectedMenu, menuItems, menuCount);
            EndDrawing();

            if (IsKeyPressed(KEY_DOWN)) selectedMenu = (selectedMenu + 1) % menuCount;
            else if (IsKeyPressed(KEY_UP)) selectedMenu = (selectedMenu - 1 + menuCount) % menuCount;
            // �޴� �� �ϳ��� �� ���
            else if (IsKeyPressed(KEY_ENTER)) {
                // Start ��ư Enter
                if (selectedMenu == 0) {
                    // ���� ���� ��Ȳ
                    gameStarted = true;
                    // �÷��̾� �ʱ�ȭ
                    InitPlayer(&player);
                    // � �ʱ�ȭ
                    InitMeteors();
                    // �Ѿ� ���� ��Ȱ��ȭ
                    for (int i = 0; i < MAX_BULLETS; i++) bullets[i].active = false;
                    // �Ѿ� ��Ÿ��, ����, ������ ���� � �ӵ� �ʱ�ȭ (=0) �ʿ�
                    gameOver = false;
                }
                // Score ��ư ����
                else if (selectedMenu == 1) {
                    while (!WindowShouldClose()) {
                        BeginDrawing();
                        ClearBackground(BLACK);
                        // �ְ����� �����ֱ�
                        DrawText(TextFormat("High Score: %d", highScore), 450, 360, 30, YELLOW);
                        DrawText("Press ENTER to return", 430, 420, 20, LIGHTGRAY);
                        EndDrawing();
                        // ���� ġ�� ���� �޴��� ���ư���
                        if (IsKeyPressed(KEY_ENTER)) break;
                    }
                }
                // Credits ��ư ����
                else if (selectedMenu == 2) {
                    while (!WindowShouldClose()) {
                        BeginDrawing();
                        ClearBackground(BLACK);
                        DrawText("Created by Team", 430, 300, 30, YELLOW);
                        DrawText("22011848 Shin Hyewon", 430, 350, 20, WHITE);
                        DrawText("21011777 Im Wookyun", 430, 370, 20, WHITE);
                        DrawText("22011796 Woo Jiwon", 430, 390, 20, WHITE);
                        DrawText("22011813 Cha Seoyeung", 430, 410, 20, WHITE);
                        DrawText("Press ENTER to return", 430, 460, 20, LIGHTGRAY);
                        EndDrawing();
                        if (IsKeyPressed(KEY_ENTER)) break;
                    }
                }
                //Exit ��ư ����
                else if (selectedMenu == 3) {
                    CloseWindow();
                    return 0;
                }
            }
            continue;
        }
        // ������ ������ �ư�, game over �� �ƴ� ���
        if (!gameOver) {
            // update �Լ����� �� ����
            // �Ѿ� �߻絵 ���ʿ��� ����
            // ���� ���� �� ���� �Է��ϸ� �����
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawPlayer();
        DrawMeteors();
        DrawBullets();
        DrawUI(player, score, gameOver, gameStarted, selectedMenu, menuItems, menuCount);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
