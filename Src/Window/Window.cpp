
/**
 * Window
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/6/14 22:49
 **/

#include "Window.hpp"


NS_STITCHES_BEGIN
void CallbackError(int32_t error, const char *description)
{
    Window::CheckGlfw(error);
//    Log::Error("GLFW error: ", description, ", ", error, '\n');
}

void CallbackMonitor(GLFWmonitor *monitor, int32_t event) {
    auto &monitors = Window::Get()->monitors;

    if (event == GLFW_CONNECTED) {
        auto &it = monitors.emplace_back(std::make_unique<Monitor>(monitor));
//        Window::Get()->onMonitorConnect(it.get(), true);
    } else if (event == GLFW_DISCONNECTED) {
        for (auto &m : monitors) {
            if (m->GetMonitor() == monitor) {
//                Window::Get()->onMonitorConnect(m.get(), false);
            }
        }

        monitors.erase(std::remove_if(monitors.begin(), monitors.end(), [monitor](const auto &m) {
            return monitor == m->GetMonitor();
        }));
    }
}

void CallbackWindowPosition(GLFWwindow *window, int32_t xpos, int32_t ypos)
{
    if (Window::Get()->fullscreen)
        return;
    Window::Get()->position = {xpos, ypos};
//    Window::Get()->onPosition(Window::Get()->position);
}

void CallbackWindowSize(GLFWwindow *window, int32_t width, int32_t height) {
    if (width <= 0 || height <= 0) {
        return;
    }

    if (Window::Get()->fullscreen) {
        Window::Get()->fullscreenSize = {width, height};
//        Window::Get()->onSize(Window::Get()->fullscreenSize);
    } else {
        Window::Get()->size = {width, height};
//        Window::Get()->onSize(Window::Get()->size);
    }
}

void CallbackWindowClose(GLFWwindow *window) {
    Window::Get()->closed = false;
//    Engine::Get()->RequestClose();
//    Window::Get()->onClose();
}

void CallbackWindowFocus(GLFWwindow *window, int32_t focused) {
    Window::Get()->focused = static_cast<bool>(focused);
//    Window::Get()->onFocus(focused == GLFW_TRUE);
}

void CallbackWindowIconify(GLFWwindow *window, int32_t iconified) {
    Window::Get()->iconified = iconified;
//    Window::Get()->onIconify(iconified);
}

void CallbackFramebufferSize(GLFWwindow *window, int32_t width, int32_t height) {
    if (Window::Get()->fullscreen)
        Window::Get()->fullscreenSize = {width, height};
    else
        Window::Get()->size = {width, height};
//    Graphics::Get()->SetFramebufferResized();
}

Window::Window() :
        size(1080, 720),
        title("Stitches Window"),
        resizable(true),
        focused(true) {
    // Set the error error callback
    glfwSetErrorCallback(CallbackError);

    // Initialize the GLFW library.
    if (glfwInit() == GLFW_FALSE) {
        throw std::runtime_error("GLFW failed to initialize");
    }

    // Checks Vulkan support on GLFW.
    if (glfwVulkanSupported() == GLFW_FALSE) {
        throw std::runtime_error("GLFW failed to find Vulkan support");
    }

    // Set the monitor callback
    glfwSetMonitorCallback(CallbackMonitor);

    // The window will stay hidden until after creation.
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    // Disable context creation.
//    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // Fixes 16 bit stencil bits in macOS.
    glfwWindowHint(GLFW_STENCIL_BITS, 8);
    // No stereo view!
    glfwWindowHint(GLFW_STEREO, GLFW_FALSE);

    // Get connected monitors.
    int32_t monitorCount;
    auto monitors = glfwGetMonitors(&monitorCount);

    for (uint32_t i = 0; i < static_cast<uint32_t>(monitorCount); i++) {
        this->monitors.emplace_back(std::make_unique<Monitor>(monitors[i]));
    }

    auto videoMode = this->monitors[0]->GetVideoMode();

    // Create a windowed mode window and its context.
    this->window = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);
    // Gets any window errors.
    if (!this->window) {
        glfwTerminate();
        throw std::runtime_error("GLFW failed to create the window");
    }
    glfwMakeContextCurrent(this->window);
    if (!gladLoadGLES2Loader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        throw std::runtime_error("GLFW failed to create the window");
    }

    // Sets the user pointer.
    glfwSetWindowUserPointer(window, this);

    // Window attributes that can change later.
    glfwSetWindowAttrib(window, GLFW_DECORATED, !borderless);
    glfwSetWindowAttrib(window, GLFW_RESIZABLE, resizable);
    glfwSetWindowAttrib(window, GLFW_FLOATING, floating);

    // Centre the window position.
    position.x = (videoMode.width - size.x) / 2;
    position.y = (videoMode.height - size.y) / 2;
    glfwSetWindowPos(window, position.x, position.y);

    // Sets fullscreen if enabled.
    if (fullscreen) {
        SetFullscreen(true);
    }

    // Shows the glfw window.
    glfwShowWindow(window);

    // Sets the displays callbacks.
    glfwSetWindowPosCallback(window, CallbackWindowPosition);
    glfwSetWindowSizeCallback(window, CallbackWindowSize);
    glfwSetWindowCloseCallback(window, CallbackWindowClose);
    glfwSetWindowFocusCallback(window, CallbackWindowFocus);
    glfwSetWindowIconifyCallback(window, CallbackWindowIconify);
    glfwSetFramebufferSizeCallback(window, CallbackFramebufferSize);
}

Window::~Window() {
    // Free the window callbacks and destroy the window.
    glfwDestroyWindow(window);

    // Terminate GLFW.
    glfwTerminate();

    closed = true;
}

void Window::Update() {
    // Polls for window events.
    glfwPollEvents();
    glfwSwapBuffers(this->window);
}

void Window::SetSize(const Vector2i &size) {
    this->size.x = size.x == -1 ? size.x : size.x;
    this->size.y = size.y == -1 ? size.y : size.y;
    glfwSetWindowSize(window, size.x, size.y);
}

void Window::SetPosition(const Vector2i &position) {
    this->position.x = position.x == -1 ? position.x : position.x;
    this->position.y = position.y == -1 ? position.y : position.y;
    glfwSetWindowPos(window, position.x, position.y);
}

void Window::SetTitle(const std::string &title) {
    this->title = title;
    glfwSetWindowTitle(window, title.c_str());
//    onTitle(title);
}

//void Window::SetIcons(const std::vector<std::filesystem::path> &filenames) {
//    std::vector<std::unique_ptr<Bitmap>> bitmaps;
//    std::vector<GLFWimage> icons;
//
//    for (const auto &filename : filenames) {
//        auto bitmap = std::make_unique<Bitmap>(filename);
//
//        if (!bitmap) continue;
//
//        GLFWimage icon = {};
//        icon.width = bitmap->GetSize().x;
//        icon.height = bitmap->GetSize().y;
//        icon.pixels = bitmap->GetData().get();
//        icons.emplace_back(icon);
//        bitmaps.emplace_back(std::move(bitmap));
//    }
//
//    glfwSetWindowIcon(window, static_cast<int32_t>(icons.size()), icons.data());
//}

void Window::SetBorderless(bool borderless)
{
    this->borderless = borderless;
    glfwSetWindowAttrib(window, GLFW_DECORATED, !borderless);
//    onBorderless(borderless);
}

void Window::SetResizable(bool resizable)
{
    this->resizable = resizable;
    glfwSetWindowAttrib(window, GLFW_RESIZABLE, resizable);
//    onResizable(resizable);
}

void Window::SetFloating(bool floating)
{
    this->floating = floating;
    glfwSetWindowAttrib(window, GLFW_FLOATING, floating);
//    onFloating(floating);
}

void Window::SetFullscreen(bool fullscreen, Monitor *monitor) {
    auto selected = monitor ? monitor : GetCurrentMonitor();
    auto videoMode = selected->GetVideoMode();

    this->fullscreen = fullscreen;

    if (fullscreen)
    {
        fullscreenSize = {videoMode.width, videoMode.height};
        glfwSetWindowMonitor(window, selected->GetMonitor(), 0, 0, fullscreenSize.x, fullscreenSize.y, GLFW_DONT_CARE);
    }
    else
    {
        position = ((Vector2i(videoMode.width, videoMode.height) - size) / 2) + selected->GetPosition();
        glfwSetWindowMonitor(window, nullptr, position.x, position.y, size.x, size.y, GLFW_DONT_CARE);
    }

//    onFullscreen(fullscreen);
}

void Window::SetIconified(bool iconify) {
    if (!iconified && iconify) {
        glfwIconifyWindow(window);
    } else if (iconified && !iconify) {
        glfwRestoreWindow(window);
    }
}

const Monitor *Window::GetPrimaryMonitor() const {
    for (const auto &monitor : monitors) {
        if (monitor->IsPrimary())
            return monitor.get();
    }
    return nullptr;
}

int32_t OverlappingArea(Vector2i l1, Vector2i r1, Vector2i l2, Vector2i r2) {
    int area1 = abs(l1.x - r1.x) *
                abs(l1.y - r1.y);

    int area2 = abs(l2.x - r2.x) *
                abs(l2.y - r2.y);

    int areaI = (std::min(r1.x, r2.x) -
                 std::max(l1.x, l2.x)) *
                (std::min(r1.y, r2.y) -
                 std::max(l1.y, l2.y));

    return (area1 + area2 - areaI);
}

const Monitor *Window::GetCurrentMonitor() const {
    if (fullscreen) {
        auto glfwMonitor = glfwGetWindowMonitor(window);
        for (const auto &monitor : monitors) {
            if (monitor->monitor == glfwMonitor)
                return monitor.get();
        }
        return nullptr;
    }
    std::multimap<int32_t, const Monitor *> rankedMonitor;

    for (const auto &monitor : monitors) {
        rankedMonitor.emplace(OverlappingArea(monitor->GetWorkareaPosition(), monitor->GetWorkareaPosition() + monitor->GetWorkareaSize(),
                                              position, position + size), monitor.get());
    }

    if (rankedMonitor.begin()->first > 0) {
        return rankedMonitor.begin()->second;
    }

    return nullptr;
}

std::string Window::StringifyResultGlfw(int32_t result)
{
    switch (result)
    {
        case GLFW_TRUE:
            return "Success";
        case GLFW_NOT_INITIALIZED:
            return "GLFW has not been initialized";
        case GLFW_NO_CURRENT_CONTEXT:
            return "No context is current for this thread";
        case GLFW_INVALID_ENUM:
            return "One of the arguments to the function was an invalid enum value";
        case GLFW_INVALID_VALUE:
            return "One of the arguments to the function was an invalid value";
        case GLFW_OUT_OF_MEMORY:
            return "A memory allocation failed";
        case GLFW_API_UNAVAILABLE:
            return "GLFW could not find support for the requested API on the system";
        case GLFW_VERSION_UNAVAILABLE:
            return "The requested OpenGL or OpenGL ES version is not available";
        case GLFW_PLATFORM_ERROR:
            return "A platform-specific error occurred that does not match any of the more specific categories";
        case GLFW_FORMAT_UNAVAILABLE:
            return "The requested format is not supported or available";
        case GLFW_NO_WINDOW_CONTEXT:
            return "The specified window does not have an OpenGL or OpenGL ES context";
        default:
            return "ERROR: UNKNOWN GLFW ERROR";
    }
}

void Window::CheckGlfw(int32_t result)
{
    if (result)
    {
        return;
    }

    auto failure = StringifyResultGlfw(result);
//    Log::Error("GLFW error: ", failure, ", ", result, '\n');
    throw std::runtime_error("GLFW error: " + failure);
}

std::pair<const char **, uint32_t> Window::GetInstanceExtensions() const {
    uint32_t glfwExtensionCount;
    auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    return std::make_pair(glfwExtensions, glfwExtensionCount);
}


bool Window::BindSurface()
{

//    EGLNativeDisplayType eglNativeDisplay;
//
//    /// Window handle
//    EGLNativeWindowType eglNativeWindow;
//    /// EGL display
//    EGLDisplay eglDisplay;
//
//    /// EGL context
//    EGLContext eglContext;
//
//    /// EGL surface
//    EGLSurface eglSurface;
//
//    GLuint flags;
//    EGLConfig config;
//    EGLint majorVersion;
//    EGLint minorVersion;
//    EGLint contextAttribs[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
//
//
//    eglDisplay = eglGetDisplay(eglNativeDisplay);
//
//    if (eglDisplay == EGL_NO_DISPLAY) {
//        return GL_FALSE;
//    }
//
//    // Initialize EGL
//    if (!eglInitialize(eglDisplay, &majorVersion, &minorVersion)) {
//        return GL_FALSE;
//    }
//
//
//    {
//        EGLint numConfigs = 0;
//        EGLint attribList[] =
//                {
//                        EGL_RED_SIZE, 5,
//                        EGL_GREEN_SIZE, 6,
//                        EGL_BLUE_SIZE, 5,
//                        EGL_ALPHA_SIZE, (flags & ES_WINDOW_ALPHA) ? 8 : EGL_DONT_CARE,
//                        EGL_DEPTH_SIZE, (flags & ES_WINDOW_DEPTH) ? 8 : EGL_DONT_CARE,
//                        EGL_STENCIL_SIZE, (flags & ES_WINDOW_STENCIL) ? 8 : EGL_DONT_CARE,
//                        EGL_SAMPLE_BUFFERS, (flags & ES_WINDOW_MULTISAMPLE) ? 1 : 0,
//                        // if EGL_KHR_create_context extension is supported, then we will use
//                        // EGL_OPENGL_ES3_BIT_KHR instead of EGL_OPENGL_ES2_BIT in the attribute list
//                        EGL_RENDERABLE_TYPE, GetContextRenderableType(eglDisplay),
//                        EGL_NONE
//                };
//
//        // Choose config
//        if (!eglChooseConfig(eglDisplay, attribList, &config, 1, &numConfigs)) {
//            return GL_FALSE;
//        }
//
//        if (numConfigs < 1) {
//            return GL_FALSE;
//        }
//    }
//
//    eglSurface = eglCreateWindowSurface(eglDisplay, config, eglNativeWindow, NULL);
//
//    if (eglSurface == EGL_NO_SURFACE) {
//        return GL_FALSE;
//    }
//
//    // Create a GL context
//    eglContext = eglCreateContext(eglDisplay, config,
//                                             EGL_NO_CONTEXT, contextAttribs);
//
//    if (eglContext == EGL_NO_CONTEXT) {
//        return GL_FALSE;
//    }
//
//    // Make the context current
//    if (!eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext))
//    {
//        return GL_FALSE;
//    }
//
//
//    return GL_TRUE;
}

//VkResult Window::CreateSurface(const VkInstance &instance, const VkAllocationCallbacks *allocator, VkSurfaceKHR *surface) const {
//    return glfwCreateWindowSurface(instance, window, allocator, surface);
//}

NS_STITCHES_END