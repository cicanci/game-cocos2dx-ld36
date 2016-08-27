#include "Ship.h"

bool Ship::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    
    return true;
}