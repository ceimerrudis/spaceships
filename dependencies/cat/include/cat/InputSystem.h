#pragma once
#include "cat/Logger.h"
#include "cat/Keys.h"
#include <vector>

namespace cat
{
struct Input{
    unsigned int keyname;
    int keycode;
    int state;
    bool operator<(const Input& other) const { return keyname < other.keyname; }
};

#define MENU_INTERACT 0

struct Window;
class InputSystem
{
    std::vector<Input> inputs;

    float sensitivity;
    double lastX, lastY;
    double deltaX, deltaY;
    double xpos, ypos;
	int cursorReleased = 0;
public:
	
    InputSystem(Window* window);
    
    void Update(Window* window);

    //held is true if down is true
    bool IsKeyHeld(unsigned int keyName) const;

    bool IsKeyDown(unsigned int keyName) const;

    bool IsKeyUp(unsigned int keyName) const;

    void GetMouseDelta(float* x, float* y) const;

    void GetMouseAbsolute(float* x, float* y) const;
	
	void AddKey(Input inputKey);
	
	void CursorModeChanged();
};
}
