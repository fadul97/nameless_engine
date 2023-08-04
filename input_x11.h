#ifndef INPUT_X11_H
#define INPUT_X11_H

#include "defines.h"

#if PLATFORM_LINUX

#include "keys.h"
#include <string.h>

typedef struct Keyboard
{
	b8 keys[256];
} Keyboard;

typedef struct Mouse
{
	i16 x;
	i16 y;
    b8 buttons[MAX_BUTTONS];
} Mouse;

class InputX11
{
private:
    Keyboard keyboard_current;
	Keyboard keyboard_previous;
	Mouse mouse_current;
	Mouse mouse_previous;

public:
    InputX11();
    ~InputX11();

    /* KEYBOARD */
    // Return if key is/was pressed
    b8 is_key_down(Keys key);
    b8 was_key_down(Keys key);

    // Return if key is/was released
    b8 is_key_up(Keys key);
    b8 was_key_up(Keys key);

    /* MOUSE */
    // Return if button is/was pressed
    b8 is_button_down(Buttons button);
    b8 was_button_down(Buttons button);

    // Return if button is/was released
    b8 is_button_up(Buttons button);
    b8 was_button_up(Buttons button);

    // Return mouse position
    i16 get_mouse_x();
    i16 get_mouse_y();
    void get_mouse_position(i32* x, i32* y);
    void get_previous_mouse_position(i32* x, i32* y);

    // Handle keyboard input
    void process_key(Keys key, b8 pressed);

    // Handle mouse input
    void process_button(Buttons button, b8 pressed);
    void update_mouse_position(f32 x, f32 y);

    // Update input from previous cicle
    void update();

    // Translate keycode from XCB to custom keycode
    Keys translate_keycode(u32 x_keycode);
};

inline b8 InputX11::is_key_down(Keys key)
{ return keyboard_current.keys[key] == true; }

inline b8 InputX11::was_key_down(Keys key)
{ return keyboard_previous.keys[key] == true; }

inline b8 InputX11::is_key_up(Keys key)
{ return keyboard_current.keys[key] == false; }

inline b8 InputX11::was_key_up(Keys key)
{ return keyboard_previous.keys[key] == false; }

inline b8 InputX11::is_button_down(Buttons button)
{ return mouse_current.buttons[button] == true; }

inline b8 InputX11::was_button_down(Buttons button)
{ return mouse_previous.buttons[button] == true; }

inline b8 InputX11::is_button_up(Buttons button)
{ return mouse_current.buttons[button] == false; }

inline b8 InputX11::was_button_up(Buttons button)
{ return mouse_previous.buttons[button] == false; }

inline i16 InputX11::get_mouse_x()
{ return mouse_current.x; }

inline i16 InputX11::get_mouse_y()
{ return mouse_current.y; }

inline void InputX11::get_mouse_position(i32* x, i32* y)
{ *x = mouse_current.x; *y = mouse_current.y; }

inline void InputX11::get_previous_mouse_position(i32* x, i32* y)
{ *x = mouse_previous.x; *y = mouse_previous.y; }

inline void InputX11::process_key(Keys key, b8 pressed)
{
	if(keyboard_current.keys[key] != pressed)
		keyboard_current.keys[key] = pressed;
}

inline void InputX11::process_button(Buttons button, b8 pressed)
{
	if(mouse_current.buttons[button] != pressed)
		mouse_current.buttons[button] = pressed;
}

inline void InputX11::update_mouse_position(f32 x, f32 y)
{ 
    if(mouse_current.x != x || mouse_current.y != y)
    {
        mouse_previous.x = mouse_current.x;
        mouse_previous.y = mouse_current.y;

        mouse_current.x = x;
        mouse_current.y = y;
    }
}

inline void InputX11::update()
{
    memcpy(&keyboard_previous, &keyboard_current, sizeof(Keyboard));
    memcpy(&mouse_previous, &mouse_current, sizeof(Mouse));
}

#endif // PLATFORM_LINUX

#endif // INPUT_X11_H