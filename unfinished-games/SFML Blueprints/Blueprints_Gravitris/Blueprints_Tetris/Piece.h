#pragma once
#include <Box2D.h>
#include <SFML/Graphics.hpp>

class Board;
constexpr int BOX_SIZE = 32;
constexpr int BOX_SIZE_2 = BOX_SIZE / 2;
class Piece : public sf::Drawable
{
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    enum TetriminoTypes : int;
    b2Fixture* createPart(int pos_x, int pos_y, TetriminoTypes type); ///< position is relaive to the piece int the matric coordonate (0 to 3)

    b2Body* _body;
    b2World& _world;

public:
    Piece(const Piece&) = delete;
    Piece& operator=(const Piece&) = delete;

    enum TetriminoTypes { O = 0, I, S, Z, L, J, T, SIZE }; //< different kind of pieces            
    static const sf::Color TetriminoColors[TetriminoTypes::SIZE]; //< different colors for each kind of piece


    Piece(b2World& world, int pos_x, int pos_y, TetriminoTypes type, float rotation); //< constructor
    ~Piece();

    void update();

    void rotate(float angle);
    void moveX(int direction);

    b2Body* getBody()const;


};
