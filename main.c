#include "raylib.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

bool running = true;

struct mainData {
    int action;
    Vector2 ballPosition;
    Vector2 ballSpeed;
    Vector2 paddle1Postion;
    Vector2 paddle2Postion;
};

int main() {
    clock_t startTime = clock();
    clock_t currentTime;
    double elapsedTime;
    const int screenWidth = 800;
    const int screenHeight = 600;
    SetConfigFlags(FLAG_MSAA_4X_HINT); 
    InitWindow(screenWidth, screenHeight, "Juan's RL");
    SetTargetFPS(60);

    // Variables
    Vector2 ballPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };
    Vector2 ballSpeed = { 5.0f, 4.0f };
    int ballRadius = 20;
    Vector2 paddle1Postion = { 10, (float)screenHeight / 2 };
    Vector2 paddle2Postion = { (float)screenWidth - 10, (float)screenHeight / 2 };
    int paddleWidth = 10;
    int paddleHeight = 100;

    while (!WindowShouldClose() && running == true) {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            // Draw the ball
            DrawCircleV(ballPosition, ballRadius, RED);

            // Draw the paddles
            DrawRectangleV(paddle1Postion, (Vector2){paddleWidth, paddleHeight}, BLACK);
            DrawRectangleV(paddle2Postion, (Vector2){paddleWidth, paddleHeight}, BLACK);

            // Move the ball
            ballPosition.x += ballSpeed.x;
            ballPosition.y += ballSpeed.y;

            // Bounce the ball
            if (ballPosition.y >= screenHeight - ballRadius || ballPosition.y <= ballRadius) {
                ballSpeed.y *= -1;
            }

            if (ballPosition.x >= screenWidth - ballRadius + 100 || ballPosition.x <= ballRadius - 100) {
                running = false;
            }

            // Bounce the ball off the paddles
            if (CheckCollisionCircleRec(ballPosition, ballRadius, (Rectangle){paddle1Postion.x, paddle1Postion.y, paddleWidth, paddleHeight})) {
                ballSpeed.x *= -1;
            }
            if (CheckCollisionCircleRec(ballPosition, ballRadius, (Rectangle){paddle2Postion.x, paddle2Postion.y, paddleWidth, paddleHeight})) {
                ballSpeed.x *= -1;
            }

            // Paddle Boundaries
            if (paddle1Postion.y <= 0) {
                paddle1Postion.y = 0;
            }
            if (paddle1Postion.y >= screenHeight - paddleHeight) {
                paddle1Postion.y = screenHeight - paddleHeight;
            }
            if (paddle2Postion.y <= 0) {
                paddle2Postion.y = 0;
            }
            if (paddle2Postion.y >= screenHeight - paddleHeight) {
                paddle2Postion.y = screenHeight - paddleHeight;
            }
 
            // Move the paddles based on key presses
            int action = 0; // Default to down
            if (IsKeyDown(KEY_W)) {
                paddle1Postion.y -= 5;  // Move up
            }
            if (IsKeyDown(KEY_S)) {
                paddle1Postion.y += 5;  // Move down
            }

            if (IsKeyDown(KEY_I)) {
                paddle2Postion.y -= 5;  // Move up
            }

            if (IsKeyDown(KEY_K)) {
                paddle2Postion.y += 5;  // Move down
            }

            // Draw FPS
            DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
