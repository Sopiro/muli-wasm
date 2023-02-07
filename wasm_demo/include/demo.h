#pragma once

#include "camera.h"
#include "common.h"
#include "input.h"
#include "options.h"

namespace muli
{

class Game;
struct DebugOptions;

class Demo : public JointDestoryCallback
{
public:
    Demo(Game& game);
    virtual ~Demo();

    virtual void UpdateInput();
    virtual void Step(float dt);
    virtual void UpdateUI() {}
    virtual void Render() {}

    // from JointDestoryCallback
    virtual void OnDestroy(Joint* me) override
    {
        gj = nullptr;
    }

    World& GetWorld()
    {
        return *world;
    }

    WorldSettings& GetWorldSettings()
    {
        return settings;
    }

    Camera& GetCamera()
    {
        return camera;
    }

    RigidBody* GetTargetBody()
    {
        return targetBody;
    }

    Collider* GetTargetCollider()
    {
        return targetCollider;
    }

protected:
    void FindTargetBody();
    void EnableKeyboardShortcut();
    void EnableBodyCreate();
    bool EnablePolygonCreate();
    void EnableBodyRemove();
    bool EnableAddForce();
    bool EnableBodyGrab();
    void EnableCameraControl();

    Game& game;
    DebugOptions& options;

    Camera camera;
    WorldSettings settings;
    World* world;

    Vec2 cursorPos;
    std::vector<Collider*> qr;

    RigidBody* targetBody;
    Collider* targetCollider;
    GrabJoint* gj;
};

typedef Demo* DemoCreateFunction(Game& game);

struct DemoFrame
{
    const char* name;
    DemoCreateFunction* createFunction;
};

#define MAX_DEMOS 100
extern int32 demo_count;
extern DemoFrame demos[MAX_DEMOS];

} // namespace muli