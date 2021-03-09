#include "opengl_interface.hpp"

namespace GL {

auto previous_time = std::chrono::system_clock::now();

void handle_error(const std::string& prefix, const GLenum err)
{
    if (err != GL_NO_ERROR)
    {
        throw std::runtime_error { prefix + std::string { ": " } +
                                   std::string { reinterpret_cast<const char*>(gluErrorString(err)) } };
    }
}

void keyboard(unsigned char key, int, int)
{
    const auto iter = keystrokes.find(key);
    if (iter != keystrokes.end())
    {
        (iter->second)();
    }
}

void toggle_fullscreen()
{
    if (fullscreen)
    {
        glutPositionWindow(10, 10);
        glutReshapeWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
    }
    else
    {
        glutFullScreen();
    }

    handle_error("Toggle fullscreen");
    fullscreen = !fullscreen;
}

void change_zoom(const float factor)
{
    zoom *= factor;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-zoom, zoom, -zoom, zoom, 0.0f, 1.0f); // left, right, bottom, top, near, far
    handle_error("Zoom");
}

void reshape_window(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-zoom, zoom, -zoom, zoom, 0.0f, 1.0f); // left, right, bottom, top, near, far
    handle_error("Cannot reshape window");
}

void display(void)
{
    // sort the displayables by their z-coordinate
    std::sort(Displayable::display_queue.begin(), Displayable::display_queue.end(), disp_z_cmp {});
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-zoom, zoom, -zoom, zoom, 0.0f, 1.0f); // left, right, bottom, top, near, far
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    for (const auto& item : Displayable::display_queue)
    {
        item->display();
    }
    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();
}

void timer(const int step)
{
    if (!paused)
    {
        auto current_time = std::chrono::system_clock::now();
        auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - previous_time).count();
        previous_time = current_time;
        for (auto it = move_queue.begin(); it != move_queue.end();)
        {
            GL::DynamicObject* dynamic_obj = *it;
            dynamic_obj->move(dt);
            if (dynamic_obj->is_dead())
            {
                it = move_queue.erase(it);
                delete dynamic_obj;
            }
            else
            {
                it++;
            }
        }
        glutPostRedisplay();
    }
    glutTimerFunc(1000u / ticks_per_sec, timer, step + 1);
}

void up_frame_rate()
{
    ticks_per_sec++;
}
void down_frame_rate()
{
    if (ticks_per_sec > 1)
    {
        ticks_per_sec--;
    }
}

void pause()
{
    paused = !paused;
}

void init_gl(int argc, char** argv, const char* title)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
    glutCreateWindow(title);
    // glutFullScreen();
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    // glEnable(GL_DEPTH_TEST);
    // The following two lines enable semi transparent
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_FLAT);

    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape_window);

    handle_error("Cannot init OpenGL");
}

void loop()
{
    glutTimerFunc(100, timer, 0);
    glutMainLoop();
}

void exit_loop()
{
    glutLeaveMainLoop();
}

} // namespace GL