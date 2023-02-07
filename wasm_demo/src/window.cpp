#include "window.h"

namespace muli
{

static void glfw_error_callback(int32 error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

Window::Window(int32 _width, int32 _height, const std::string& _title)
    : width{ _width }
    , height{ _height }
{
    muliAssert(window == nullptr);
    window = this;

    puts("Initialize glfw");

    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit())
    {
#ifndef __EMSCRIPTEN__
        const char* description;
        glfwGetError(&description);
        printf("failed to initialize glfw: %s\n", description);
#else
        printf("failed to initialize glfw");
#endif
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_SAMPLES, 4); // 4xMSAA

    glfwWindow = glfwCreateWindow(width, height, _title.c_str(), nullptr, nullptr);
    if (!glfwWindow)
    {
        printf("%s\n", "failed to create glfw window");
        glfwTerminate();
        exit(1);
    }

    const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
#ifndef __EMSCRIPTEN__
    glfwSetWindowMonitor(glfwWindow, NULL, (vidmode->width / 2) - (width / 2), (vidmode->height / 2) - (height / 2), width,
                         height, GLFW_DONT_CARE);
#else
    glfwSetWindowSize(glfwWindow, width, height);
#endif

    glfwMakeContextCurrent(glfwWindow);
    glfwSwapInterval(0); // Disable vsync

#ifndef __EMSCRIPTEN__
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        puts("failed to initialize glad");
        glfwTerminate();
        exit(1);
    }
#endif

    const char* version = (const char*)glGetString(GL_VERSION);
    printf("OpenGL context version: %s\n", version);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    // ImGui::StyleColorsClassic();
    // ImGui::StyleColorsLight();
    ImGui::StyleColorsDark();

    // Rounded corner style
    float rounding = 5.0f;
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = rounding;
    style.ChildRounding = rounding;
    style.FrameRounding = rounding;
    style.GrabRounding = rounding;
    style.PopupRounding = rounding;
    style.ScrollbarRounding = rounding;

    ImGui_ImplGlfw_InitForOpenGL(glfwWindow, false);
#ifndef __EMSCRIPTEN__
    ImGui_ImplOpenGL3_Init("#version 330");
#else
    ImGui_ImplOpenGL3_Init("#version 100");
#endif

    // Setup font
    // io.Fonts->AddFontFromFileTTF("misc/Roboto-Medium.ttf", 13.0f);
    // io.Fonts->AddFontFromFileTTF("misc/NotoSans-Regular.ttf", 13.0f);

    // Register some window callbacks
    glfwSetFramebufferSizeCallback(glfwWindow, OnFramebufferSizeChange);
    glfwSetKeyCallback(glfwWindow, OnKeyEvent);
    glfwSetCharCallback(glfwWindow, OnCharEvent);
    glfwSetCursorPosCallback(glfwWindow, OnCursorPos);
    glfwSetMouseButtonCallback(glfwWindow, OnMouseButton);
    glfwSetScrollCallback(glfwWindow, OnScroll);

#ifndef __EMSCRIPTEN__
    refreshRate = glfwGetVideoMode(glfwGetPrimaryMonitor())->refreshRate;
#else
    refreshRate = 60;
#endif

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    Input::Init();
}

Window::~Window() noexcept
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(glfwWindow);
    glfwTerminate();
}

} // namespace muli