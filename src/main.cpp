#include <bn_backdrop.h>
#include <bn_core.h>
#include <bn_keypad.h>
#include <bn_sprite_ptr.h>

#include "bn_sprite_items_bun.h"

#define FLOOR (80 - 8)

int main()
{
    bn::core::init();

    bn::backdrop::set_color(bn::color(15, 0, 0));

    auto dot = bn::sprite_items::bun.create_sprite(0, 0);

    bn::fixed speed = 1.5;

    bn::fixed dy = 0;
    bn::fixed gravity = .03;

    bn::fixed jump_strength = 1.3;

    bool is_jumping = false;

    while (true)
    {
        if (bn::keypad::left_held())
        {
            dot.set_x(dot.x() - speed);
        }
        if (bn::keypad::right_held())
        {
            dot.set_x(dot.x() + speed);
        }
        if (bn::keypad::a_pressed() && !is_jumping)
        {
            is_jumping = true;
            dy -= jump_strength;
        }

        // No jumping while jumping
        if (dot.y() >= FLOOR)
        {
            is_jumping = false;
        }

        dy += gravity;

        dot.set_y(dot.y() + dy);

        if (dot.y() > FLOOR)
        {
            dot.set_y(FLOOR);
            dy = 0;
        }
        bn::core::update();
    }
}