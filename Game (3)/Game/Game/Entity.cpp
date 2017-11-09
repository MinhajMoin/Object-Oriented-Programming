#include "Entity.h"

Entity::Entity(LTexture* image,Point pos)
{
    spriteSheetTexture = image;
    this->pos.x = pos.x;
    this->pos.y = pos.y;
    alive=true;
    width=0;
    height=0;
    dx=0;
    dy=0;
    expFrame=0;
    speedX=0;
    speedY=0;
    //width and height will be set in individual entities, same for the spriteclips
    /*
    this->width = spriteClips[ 0 ].w;
    this->height = spriteClips[ 0 ].h;*/
}

Entity::~Entity()
{
//    std::cout << "ENTITY DESTROYED" << std::endl;
    spriteSheetTexture=NULL;
}
int Entity::getWidth()
{
    return width;
}
int Entity::getHeight()
{
    return height;
}

bool Entity::insideBounds(int x, int y)
{
    return (x>=bounds.x && x<=(bounds.x + bounds.w) && y>=bounds.y && y<=(bounds.y + bounds.h));
}

void Entity::setAlive(bool alive)
{
    this->alive=alive;
}
bool Entity::getAlive()
{
    return alive;
}

SDL_Rect Entity::getBounds()
{
    return bounds;
}

int Entity::getType()
{
    return type;
}

Point Entity::getPos()
{
    return pos;
}

void Entity::setBounds()
{
    bounds.x=pos.x;
    bounds.y=pos.y;
    bounds.w=width;
    bounds.h=height;
}
