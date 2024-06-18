#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace sf;
using namespace std;

class stdafx
{
};

template <typename T>
constexpr T clamp(T value, T min, T max) {
    return std::max(min, std::min(value, max));
}

class Game;
enum class GameModes;

class Player;
class Inventory;
class Interface;

enum class Locations;
class Level;
class Map;
class Tile;

class Item;
class Coin;
class Heart;
class Key;

class Enemy;
class Skeleton;
class Goblin;

class Fight;



