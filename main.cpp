#include "internal.hpp"
#include "user.hpp"

#include <raymath.h>
#include <raylib.h>

#include <algorithm>
#include <memory>
#include <vector>
#include <string>
#include <map>

int main() {
    Vector2 screen_size = {800, 600};
    InitWindow(screen_size.x, screen_size.y, "Some unnamed game");
    SetTargetFPS(60);

    Context ctx;
    ctx.camera_pos = {0, 0};
    ctx.time = 0;
    ctx.screen_size = screen_size;
    ctx.state = GameState::MAIN_MENU;
    ctx.textures_storage = std::map<TextureHash, Texture>();
    Render heart_render = Render(ctx, "Assets/heart.png", Vector2{30.0, 30.0});
    ctx.heart = std::make_unique<Render>(std::move(heart_render));

    std::map<std::string, std::vector<Object>> scenes;

    ReadScene(ctx, scenes["game"], "Assets/game.lvl");
    Object obj = Object();
    obj.gui_draw = DrawStatus;
    scenes["game"].push_back(std::move(obj));
    ConstructMenuScene(ctx, scenes["menu"]);
    obj = Object();
    obj.gui_draw = DrawMainScreen;
    scenes["menu"].push_back(std::move(obj));

    InitAudioDevice();

    ctx.scenes = scenes;

    ctx.current_scene = scenes["menu"];
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        ctx.time += uint64_t(dt * 1000);

        UpdateGameState(ctx);

        BeginDrawing();
        {
            ClearBackground(BLACK);

            for (auto &obj : ctx.current_scene) {
                if (obj.gui_draw) {
                    obj.gui_draw(ctx);
                }
                if (obj.render.visible) {
                    Vector2 pos = local_to_screen(&ctx, obj.position);
                    Vector2 img_size = {
                        float(obj.render.width),
                        float(obj.render.height),
                    };
                    pos -= img_size * 0.5f;
                    Texture texture = ctx.textures_storage[obj.render.hash];
                    DrawTextureV(texture, pos, WHITE);
                }
            }
            UpdateSceneState(ctx);
        }
        EndDrawing();

        if (ctx.state == GameState::MAIN_MENU) {
            continue;
        }

        Object &player = *find_player(ctx.current_scene);

        PlayerControl(ctx, player, dt);

        for (Object &obj : ctx.current_scene) {
            ApplyGravity(obj, dt);
            if (obj.enemy.enabled) {
                EnemyAI(obj, ctx.current_scene, dt);
            }
            if (obj.bullet.enabled) {
                UpdateBullet(ctx, obj, dt);
            }
        }

        FixCollisions(ctx.current_scene, dt);
        MoveCameraTowards(ctx, player, dt);
        KillEnemies(ctx);

        for (GameId id_to_destroy : ctx.to_destroy) {
            ctx.current_scene.erase(
                std::remove_if(
                    ctx.current_scene.begin(),
                    ctx.current_scene.end(),
                    [id_to_destroy](Object &c) { return c.id == id_to_destroy; }
                ),
                ctx.current_scene.end()
            );
        }
        ctx.to_destroy.clear();

        for (Object &obj : ctx.to_spawn) {
            ctx.current_scene.push_back(std::move(obj));
        }
        ctx.to_spawn.clear();
    }
    CloseWindow();

    return 0;
}
