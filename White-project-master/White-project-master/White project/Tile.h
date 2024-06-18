#pragma once
class Tile
{
public:
	Sprite sprite;
	bool wall;
	bool hasItem;

	Tile();
	~Tile();

	Vector2f getItemPosition(int tileSize, const sf::Texture* itemTexture);
};

