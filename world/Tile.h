#pragma once

enum class TileType {
    Floor,
    Wall
};

class Tile {
public:
    TileType type;

    Tile(TileType t = TileType::Floor) : type(t) {}

    bool isWalkable() const {
        return type == TileType::Floor;
    }
};