#pragma once

#include "internal.hpp"

Collision CheckCollision(Object &obj1, Object &obj2);
void SolveCollision(Object &obj, Collision c, float dt);
void FixCollisions(Scene &scene, float dt);
void ApplyGravity(Object &obj, float dt);
void MakeJump(Object &obj, float dt);
void MoveCameraTowards(Context &ctx, Object &obj, float dt);
bool CheckPlayerDeath(Object &player, Scene &scene);
bool CheckFinish(Object &player, Scene &scene);
void EnemyAI(Object &crab, Scene &scene, float dt);
void PlayerControl(Context &, Object &player, float dt);
void ShootBullet(Context &, Object &player, float dt);
void UpdateBullet(Context &, Object &obj, float dt);
void KillEnemies(Context &);
void DrawDeathScreen(Context &);
void DrawFinishScreen(Context &);
void DrawMainScreen(Context &);
void DrawGameOverScreen(Context &);
void ApplyOnDeath(Context &, Object &);
void ApplyOnSpawn(Context &, Object &);
void DrawStatus(Context &);
void ConstructMenuScene(Context &ctx, Scene &game_scene);
