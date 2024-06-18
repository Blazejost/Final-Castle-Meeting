#include "stdafx.h"
#include "Map.h"
#include "Level.h"
#include "Game.h"
#include "Player.h"
#include "Tile.h"
#include "Item.h"
#include "Key.h"
#include "Coin.h"
#include "Heart.h"
#include "Enemy.h"
#include "Skeleton.h"
#include "Goblin.h"

Map::Map(Level *level)
{
	//Map
	this->location = level->location;
	this->level = level;
	this->currentLevel = level->currentLevel;
	this->player = level->player;
	this->target = level->target;

	//Load textures for tiles
	loadTileTextures();

	//Init variables
	itemAmount = 8; //Ammount items on the map
	enemiesAmount = 3;
}

Map::~Map()
{
}

void Map::generateMap(int width, int height, int tileSize)
{
	this->width = width;
	this->height = height;
	this->tileSize = tileSize;

	tiles.clear();
	tiles.resize(height);

	startY = height - 2;

	for (int i = 0; i < height; i++) {
		if (i < tiles.size()) {
			tiles[i].resize(width);
		}
		else {
			std::cerr << "Error: Out of range access in tiles vector." << std::endl;
			break;
		}

		for (int j = 0; j < width; ++j) {
			// Initialize each tile here...
			tiles[i][j].sprite = wallSprite;
			tiles[i][j].wall = true;
		}
	}

	//Lines
	int linia1X{};
	int linia2Y{};
	int linia3X{};

	//tworzenie drogi glownej
	{
		linia1X = rand() % (height - 2) + 1;
		startX = linia1X;

		for (int i = 0; i < height; i++) {
			tiles[i][linia1X].sprite = emptySprite;
			tiles[i][linia1X].wall = false;
		}

		//koncowa x
		endX = linia1X;

		//tworzenie drog bocznych
		int szerokosc_linii2{};
		linia2Y = rand() % (height - 2 - 2) + 2;
		if (linia1X <= width / 2) {
			for (int i = linia1X; i < width; i++) {
				tiles[linia2Y][i].sprite = emptySprite;
				tiles[linia2Y][i].wall = false;
				szerokosc_linii2++;
			}

			//tworzenie dodatkowych galedzi
			linia3X = rand() % (width - linia1X - 5) + linia1X + 4;
			if (linia2Y <= height / 2) {
				for (int i = linia2Y; i < height - 2; i++) {
					tiles[i][linia3X].sprite = emptySprite;
					tiles[i][linia3X].wall = false;
					secretY = height - 3;
				}
			}
			if (linia2Y > height / 2) {
				for (int i = 2; i < linia2Y; i++) {
					tiles[i][linia3X].sprite = emptySprite;
					tiles[i][linia3X].wall = false;
					secretY = 2;
				}
			}
		}
		else if (linia1X > width / 2) {
			for (int i = 0; i < linia1X; i++) {
				tiles[linia2Y][i].sprite = emptySprite;
				tiles[linia2Y][i].wall = false;
			}

			//tworzenie dodatkowych galedzi

			linia3X = rand() % (linia1X - 6 - 0) + 1;
			if (linia2Y <= height / 2) {
				for (int i = linia2Y; i < height - 2; i++) {
					tiles[i][linia3X].sprite = emptySprite;
					tiles[i][linia3X].wall = false;
					secretY = height - 3;
				}
			}
			if (linia2Y > height / 2) {
				for (int i = 2; i < linia2Y; i++) {
					tiles[i][linia3X].sprite = emptySprite;
					tiles[i][linia3X].wall = false;
					secretY = 2;
				}
			}
		}


		//Secret and lock
		secretX = linia3X;

		//tworzenie klucza
		key = new Key(level, keyTexture);

		secretX = secretX * tileSize + (tileSize / 2) - (key->sprite.getTexture()->getSize().x / 2);
		secretY = secretY * tileSize + (tileSize / 2) - (key->sprite.getTexture()->getSize().y / 2);
		key->sprite.setPosition(secretX, secretY);
		key->sprite.scale(1.5f, 1.5f);
		//tiles[secretY][secretX] = secret_icon;

		//koniec
		//tiles[endY][endX] = lock_icon;
		lockSprite.setPosition(endX * tileSize, 0);

		player->setPosition(startX * tileSize, startY * tileSize);

		//TEST

		player->positionXTile = startX;
		player->positionYTile = startY;
	}
}

void Map::generateItems(vector <Item*> mapItems)
{
	items.clear(); // Clear the existing items vector

	float randomNumber = 0.f;
	float chanceOfGenerating = 0.1f;
	bool willGenerateItem = false;

	while (itemAmount > 0) {
		// Go through the whole map
		for (int i = 1; i < height - 1; i++) {
			for (int j = 1; j < width - 1; j++) {

				randomNumber = (float)rand() / 101.f;
				if (randomNumber < chanceOfGenerating) {
					willGenerateItem = true;
				}
				else {
					willGenerateItem = false;
				}
				// If the tile is not a wall and it does not have an item

				if (tiles[i][j].wall == false && tiles[i][j].hasItem == false && willGenerateItem) {
					int randomID = rand() % mapItems.size(); // Generate a random index
					Item* item = mapItems[randomID]; // Get the item from the vector

					Coin* coin = dynamic_cast<Coin*>(item); // Cast to Coin*
					if (dynamic_cast<Coin*>(item)) {
						items.push_back(new Coin(*coin)); // Create a new Coin object
					}
					Heart* heart = dynamic_cast<Heart*>(item); // Cast to Coin*
					if (dynamic_cast<Heart*>(item)) {
						items.push_back(new Heart(*heart)); // Create a new Coin object
					}

					else {
						// Handle the case where the item is not a Coin
						// You can add more dynamic casts for other types of items
					}

					items.back()->isOnMap = true;

					// Calculate the position to center the item on the tile
					float itemX = j * tileSize + (tileSize / 2) - (items.back()->sprite.getTexture()->getSize().x / 2);
					float itemY = i * tileSize + (tileSize / 2) - (items.back()->sprite.getTexture()->getSize().y / 2);

					items.back()->sprite.setPosition(itemX, itemY);
					tiles[i][j].hasItem = true; // Mark the tile as having an item
					itemAmount--;
					break; // Break out of the inner loop once an item is placed
				}
			}
		}
	}
}


void Map::generateEnemies(vector <Enemy*> mapEnemies)
{
	enemies.clear(); // Clear the existing items vector

	float randomNumber = 0.f;
	float chanceOfGenerating = 0.1f;
	bool willGenerateItem = false;

	while (enemiesAmount > 0) {
		// Go through the whole map
		for (int i = 1; i < height - 1; i++) {
			for (int j = 1; j < width - 1; j++) {

				randomNumber = (float)rand() / 101.f;
				if (randomNumber < chanceOfGenerating) {
					willGenerateItem = true;
				}
				else {
					willGenerateItem = false;
				}
				// If the tile is not a wall and it does not have an item

				if (tiles[i][j].wall == false && tiles[i][j].hasItem == false && willGenerateItem) {
					int randomID = rand() % mapEnemies.size(); // Generate a random index
					Enemy* enemy = mapEnemies[randomID]; // Get the item from the vector

					Skeleton* skeleton = dynamic_cast<Skeleton*>(enemy); // Cast to Coin*
					if (dynamic_cast<Skeleton*>(skeleton)) {
						enemies.push_back(new Skeleton(*skeleton)); // Create a new Coin object
						
					}

					Goblin* goblin = dynamic_cast<Goblin*>(enemy); // Cast to Coin*
					if (dynamic_cast<Goblin*>(goblin)) {
						enemies.push_back(new Goblin(*goblin)); // Create a new Coin object
						
						cout << "goblin" << endl;
					}
					//Heart* heart = dynamic_cast<Heart*>(skeleton); // Cast to Coin*
					//if (dynamic_cast<Heart*>(item)) {
					//	items.push_back(new Heart(*heart)); // Create a new Coin object
					//}

					else {
						// Handle the case where the item is not a Coin
						// You can add more dynamic casts for other types of items
					}

					

					// Calculate the position to center the item on the tile
					if (!enemies.empty()) {
						float scaleFactor = 2.f; // or any other scale factor you want
						enemies.back()->sprite.setScale(scaleFactor, scaleFactor);

						float enemyWidth = enemies.back()->sprite.getTexture()->getSize().x * scaleFactor;
						float enemyHeight = enemies.back()->sprite.getTexture()->getSize().y * scaleFactor;

						float tileCenterX = j * tileSize + (tileSize / 2);
						float tileCenterY = i * tileSize + (tileSize / 2);

						float enemyX = tileCenterX - (enemyWidth / 2);
						float enemyY = tileCenterY - (enemyHeight / 2);

						enemies.back()->sprite.setPosition(enemyX, enemyY);
						enemies.back()->positionX = enemyX;
						enemies.back()->positionY = enemyY;

						tiles[i][j].hasItem = true; // Mark the tile as having an item
						enemiesAmount--;
						break; // Break out of the inner loop once an item is placed
					}
				}
			}
		}
	}
}


void Map::render() {
	// Clear the window

	// Render the map tiles
	for (int i = 1; i < height - 1; i++) {
		for (int j = 1; j < width - 1; j++) {
			tiles[i][j].sprite.setPosition(j * tileSize, i * tileSize);
			target->draw(tiles[i][j].sprite);
		}
	}

	// Render the items
	for (auto& item : items) {
		if (item->isOnMap) {
			target->draw(item->sprite);
		}
	}

	if (player->hasKey == false){
		target->draw(key->sprite);
	}
	
	target->draw(lockSprite);


	//Render enemies
	for (auto& enemy: enemies) {
		target->draw(enemy->sprite);
	}

	// Display the rendered frame
	//Test
}

void Map::loadTileTextures() {
	float tileScale = 12.f; //Scale for tiles textures
	
	//Load textures
	wallTexture.loadFromFile("Images/Map/Tiles/wall_2.png");
	wallSprite.setTexture(wallTexture);
	wallSprite.setScale(tileScale, tileScale);

	if (level->location == Locations::CASTLE_MIDDLE) {
		wallSprite.setColor(Color::Yellow);
	}
	if (level->location == Locations::CASTLE_STAIRS) {
		wallSprite.setColor(Color::Red);
	}

	emptyTexture.loadFromFile("Images/Map/Tiles/Floor.png", IntRect(0, 0, 20, 20));
	emptySprite.setTexture(emptyTexture);
	emptySprite.setScale(tileScale, tileScale);

	keyTexture.loadFromFile("Images/Map/Items/Golden Key.png");

	lockTexture.loadFromFile("Images/Map/Tiles/door_closed.png");
	lockSprite.setTexture(lockTexture);
	lockSprite.setScale(5, 5);
}