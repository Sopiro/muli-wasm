#pragma once

#include "camera.h"
#include "common.h"
#include "demo.h"
#include "dynamic_renderer.h"
#include "input.h"
#include "options.h"
#include "rigidbody_renderer.h"
#include "window.h"

namespace muli
{

class Game final : public ColliderDestoryCallback
{
public:
    Game();
    ~Game() noexcept;

    Game(const Game&) noexcept = delete;
    Game& operator=(const Game&) noexcept = delete;

    Game(Game&&) noexcept = delete;
    Game& operator=(Game&&) noexcept = delete;

    void Update(float dt);
    void Render();

    Vec2 GetWorldCursorPosition() const;
    DebugOptions& GetDebugOptions();
    void RegisterRenderBody(RigidBody* b);
    const RigidBodyRenderer& GetRigidBodyRenderer() const;
    std::vector<Vec2>& GetPointList();
    std::vector<Vec2>& GetLineList();
    float GetTime() const;
    void RestartDemo();
    void NextDemo();
    void PrevDemo();

private:
    std::vector<Vec2> points;
    std::vector<Vec2> lines;
    RigidBodyRenderer rRenderer;
    DynamicRenderer dRenderer;

    float time = 0.0f;

    int32 newIndex;
    int32 demoIndex = -1;
    Demo* demo = nullptr;
    bool restart = false;
    DebugOptions options;

    void UpdateProjectionMatrix();
    void UpdateUI();
    void UpdateInput();
    void InitDemo(int32 demo);
    virtual void OnDestroy(Collider* me) override;
};

inline DebugOptions& Game::GetDebugOptions()
{
    return options;
}

inline std::vector<Vec2>& Game::GetPointList()
{
    return points;
}

inline std::vector<Vec2>& Game::GetLineList()
{
    return lines;
}

inline void Game::RegisterRenderBody(RigidBody* b)
{
    for (Collider* c = b->GetColliderList(); c; c = c->GetNext())
    {
        rRenderer.Register(c);
        c->OnDestroy = this;
    }
}

inline Vec2 Game::GetWorldCursorPosition() const
{
    return rRenderer.Pick(Input::GetMousePosition());
}

inline float Game::GetTime() const
{
    return time;
}

inline void Game::RestartDemo()
{
    restart = true;
    newIndex = demoIndex;
}

inline void Game::NextDemo()
{
    newIndex = (demoIndex + 1) % demo_count;
    restart = true;
}

inline void Game::PrevDemo()
{
    newIndex = (demoIndex - 1 + demo_count) % demo_count;
    restart = true;
}

inline const RigidBodyRenderer& Game::GetRigidBodyRenderer() const
{
    return rRenderer;
}

inline void Game::OnDestroy(Collider* me)
{
    rRenderer.Unregister(me);
}

} // namespace muli