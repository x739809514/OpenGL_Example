#include "test.h"

class ColorTest : public test
{
private:
    float m_Color[4];
public:
    ColorTest(/* args */);
    ~ColorTest();
    void onRender() override;
    void onUpdate(float deltaTime) override;
};
