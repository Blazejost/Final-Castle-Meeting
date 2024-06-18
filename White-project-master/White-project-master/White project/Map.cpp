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

//onstructor
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

//Destructor
Map::~Map()
{
}

//Generates map for level
void Map::generateMap(int width, int height, int tileSize)
{
	//parameters
	this->width = width;
	this->height = height;
	this->tileSize = tileSize;

	//Clears vector tile and sets its size
	tiles.clear();
	tiles.resize(height);

	//start position for player
	startY = height - 2;

	//sets walls on map
	for (int i = 0; i < height; i++) {
		//sets the size 
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

	//creating main route
	{
		linia1X = rand() % (height - 2) + 1;
		startX = linia1X;

		for (int i = 0; i < height; i++) {
			tiles[i][linia1X].sprite = emptySprite;
			tiles[i][linia1X].wall = false;
		}

		//end of level(x)
		endX = linia1X;

		//creating side routes
		int szerokosc_linii2{};
		linia2Y = rand() % (height - 2 - 2) + 2;
		if (linia1X <= width / 2) {
			for (int i = linia1X; i < width; i++) {
				tiles[linia2Y][i].sprite = emptySprite;
				tiles[linia2Y][i].wall = false;
				szerokosc_linii2++;
			}

			//creating additional routes
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

			//creating additional routes 

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


		//x key 
		secretX = linia3X;

		//creating key
		key = new Key(level, keyTexture);

		//calculates the key position
		secretX = secretX * tileSize + (tileSize / 2) - (key->sprite.getTexture()->getSize().x / 2);
		secretY = secretY * tileSize + (tileSize / 2) - (key->sprite.getTexture()->getSize().y / 2);
		//sets sprites and sets the size
		key->sprite.setPosition(secretX, secretY);
		key->sprite.scale(1.5f, 1.5f);
		
		//end
		//position of the door
		lockSprite.setPosition(endX * tileSize, 0);

		//start position of the player
		player->setPosition(startX * tileSize, startY * tileSize);


		player->positionXTile = startX;
		player->positionYTile = startY;
	}
}

//Generates items on map
void Map::generateItems(vector <Item*> mapItems)
{
	items.clear(); // Clear the existing items vector

	//chancces of generating items
	float randomNumber = 0.f;
	float chanceOfGenerating = 0.1f;
	bool willGenerateItem = false;

	//Generates items
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

//Generates enemies
void Map::generateEnemies(vector <Enemy*> mapEnemies)
{
	enemies.clear(); // Clear the existing items vector

	//chances of generating enemies
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

					else {
						
					}

					

					// Calculate the position to center the enemy on the tile
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

	//if player doesnt have key it shows on map
	if (player->hasKey == false){
		target->draw(key->sprite);
	}
	
	target->draw(lockSprite);


	//Render enemies
	for (auto& enemy: enemies) {
		target->draw(enemy->sprite);
	}
}

//Loads tile textures for map
void Map::loadTileTextures() {
	float tileScale = 12.f; //Scale for tiles textures
	
	//Load textures
	wallTexture.loadFromFile("Images/Map/Tiles/wall_2.png");
	wallSprite.setTexture(wallTexture);
	wallSprite.setScale(tileScale, tileScale);

	//Every location has different color
	if (level->location == Locations::CASTLE_MIDDLE) {
		wallSprite.setColor(Color::Yellow);
	}
	if (level->location == Locations::CASTLE_STAIRS) {
		wallSprite.setColor(Color::Red);
	}

	//load texture from file for floor
	emptyTexture.loadFromFile("Images/Map/Tiles/Floor.png", IntRect(0, 0, 20, 20));
	//sets texture and size for sprites
	emptySprite.setTexture(emptyTexture);
	emptySprite.setScale(tileScale, tileScale);

	//Loads key texture from file
	keyTexture.loadFromFile("Images/Map/Items/Golden Key.png");

	//Loads door texture from file
	lockTexture.loadFromFile("Images/Map/Tiles/door_closed.png");
	lockSprite.setTexture(lockTexture);
	lockSprite.setScale(5, 5);
}