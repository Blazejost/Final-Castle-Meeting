#include "stdafx.h"
#include "Item.h"
#include "Player.h"

//Constructors
Item::Item() {

}
Item::Item(Texture texture)
{
    this->texture = texture;
    this->sprite = Sprite(texture);
    this->isOnMap = false;
    used = false;
    sprite.setTexture(texture);
    isOnMap = false;
}

//Copy cunstructors
Item::Item(const Item& other) {
    // Copy the members of the other object
    texture = other.texture;
    sprite = Sprite(texture); // Assign the texture to the sprite
    isOnMap = other.isOnMap;
    value = other.value;
}

//Destructor
Item::~Item() {

}

//sets sprites size
void Item::setScale(float x, float y) {
    sprite.setScale(x, y);
}

