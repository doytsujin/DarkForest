#pragma once
#include "types.h"
#include "types/vector.h"
#include "PS2MouseCommon.h"
#include "Vga.h"
#include "Geometry.h"

class Mouse final
{
public:
    Mouse(const int x, const int y);
    ~Mouse() = default;

    void draw(const RawMouseEvent&, VGA&);

    u16 x() const;
    u16 y() const;
    Point point() const;

private:
    static void init_sprite();

private:
    u16 m_x {0};
    u16 m_y {0};

    static constexpr u32 MOUSE_SPRITE_SIZE = 7;
    static u32 sprite_template[MOUSE_SPRITE_SIZE*MOUSE_SPRITE_SIZE];
    static u32 current_sprite[MOUSE_SPRITE_SIZE*MOUSE_SPRITE_SIZE];
    Vector<u32> m_hidden_by_mouse;

};