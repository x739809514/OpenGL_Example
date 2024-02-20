#include "ColorTest.h"
#include <glfw/glfw3.h>

ColorTest::ColorTest() : m_Color{0.0f, 0.0f, 0.0f, 1.0f}
{
}

ColorTest::~ColorTest()
{
}

void ColorTest::onRender()
{
    glClearColor(m_Color[0],m_Color[1],m_Color[2],m_Color[3]);
    glClear(GL_COLOR_BUFFER_BIT);
}

void ColorTest::onUpdate(float deltaTime)
{
}
