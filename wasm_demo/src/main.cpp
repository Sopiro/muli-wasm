#include "game.h"

static std::unique_ptr<muli::Window> window;
static std::unique_ptr<muli::Game> game;

static muli::Vec4 clearColor{ 190.0f / 255.0f, 220.0f / 255.0f, 230.0f / 255.0f, 1.0f };
static float maxDeltaTime = 1.0f / 60.0f;

void loop()
{
    static auto lastTime = std::chrono::steady_clock::now();

    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<float> duration = currentTime - lastTime;
    lastTime = currentTime;

    float dt = muli::Clamp(duration.count(), 0.0f, maxDeltaTime);

    window->BeginFrame(clearColor);
    {
        game->Update(dt);
        game->Render();
    }
    window->EndFrame();
}

int main(int argc, char** argv)
{
    window = std::make_unique<muli::Window>(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    game = std::make_unique<muli::Game>();

    emscripten_set_main_loop(loop, 0, 1);

    return 0;
}
