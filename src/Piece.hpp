#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

using namespace sf;
using namespace std;

// Abstract base class for all chess pieces
class Piece
{
protected:
    bool white; // true for white, false for black
    Sprite sprite;

public:
    Piece(bool isWhite, Texture &texture)
    {
        white = isWhite;
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
    }

    virtual ~Piece() {}

    bool isWhite() const { return white; }

    Sprite &getSprite() { return sprite; }

    void setPosition(Vector2f pos) { sprite.setPosition(pos); }

    virtual vector<Vector2i> getLegalMoves(Vector2i pos, Piece *board[8][8]) = 0;

    bool canCapture(Vector2i pos, Piece *board[8][8])
    {
        int row = pos.y;
        int col = pos.x;
        if (row < 0 || row >= 8 || col < 0 || col >= 8)
        {
            return false;
        }
        Piece *targetPiece = board[row][col];
        return targetPiece != NULL && targetPiece->isWhite() != this->isWhite();
    }
};

// Derived class for Pawn
class Pawn : public Piece
{
public:
    Pawn(bool isWhite, Texture &texture) : Piece(isWhite, texture) 
    {
        // Any Pawn-specific initialization can go here
    }

    vector<Vector2i> getLegalMoves(Vector2i pos, Piece *board[8][8]) override
    {
        vector<Vector2i> moves;
        int direction = (isWhite()) ? -1 : 1; // White moves up (-y), Black moves down (+y)

        // Move forward by 1 square
        if (pos.y + direction >= 0 && pos.y + direction < 8 && board[pos.y + direction][pos.x] == nullptr)
            moves.push_back(Vector2i(pos.x, pos.y + direction));

        // Initial two-square move
        int startRank = isWhite() ? 6 : 1; // Starting rank for white (6) and black (1) pawns
        if (pos.y == startRank && board[pos.y + direction][pos.x] == nullptr && 
            board[pos.y + 2*direction][pos.x] == nullptr) {
            moves.push_back(Vector2i(pos.x, pos.y + 2*direction));
        }

        // Capture diagonally
        if (pos.y + direction >= 0 && pos.y + direction < 8)
        {
            if (pos.x - 1 >= 0 && canCapture(Vector2i(pos.x - 1, pos.y + direction), board))
                moves.push_back(Vector2i(pos.x - 1, pos.y + direction));
            if (pos.x + 1 < 8 && canCapture(Vector2i(pos.x + 1, pos.y + direction), board))
                moves.push_back(Vector2i(pos.x + 1, pos.y + direction));
        }

        return moves;
    }
};

// Derived class for Rook
class Rook : public Piece
{
public:
    Rook(bool isWhite, Texture &texture) : Piece(isWhite, texture)
    {
        // Any Rook-specific initialization can go here
    }

    vector<Vector2i> getLegalMoves(Vector2i pos, Piece *board[8][8]) override
    {
        vector<Vector2i> moves;
        
        // Horizontal and vertical directions
        const int dx[] = {0, 0, 1, -1}; // up, down, right, left
        const int dy[] = {-1, 1, 0, 0};
        
        for (int dir = 0; dir < 4; ++dir) {
            for (int step = 1; step < 8; ++step) {
                int newX = pos.x + dx[dir] * step;
                int newY = pos.y + dy[dir] * step;
                
                // Check bounds
                if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8)
                    break;
                
                // Empty square - add move and continue
                if (board[newY][newX] == nullptr) {
                    moves.push_back(Vector2i(newX, newY));
                }
                // Capture - add move and stop in this direction
                else if (canCapture(Vector2i(newX, newY), board)) {
                    moves.push_back(Vector2i(newX, newY));
                    break;
                }
                // Blocked by friendly piece - stop in this direction
                else {
                    break;
                }
            }
        }
        
        return moves;
    }
};

// Derived class for Knight
class Knight : public Piece
{
public:
    Knight(bool isWhite, Texture &texture) : Piece(isWhite, texture)
    {
        // Any Knight-specific initialization can go here
    }

    vector<Vector2i> getLegalMoves(Vector2i pos, Piece *board[8][8]) override
    {
        vector<Vector2i> moves;
        // L-shaped moves
        vector<Vector2i> directions = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
        for (auto &dir : directions)
        {
            int newX = pos.x + dir.x;
            int newY = pos.y + dir.y;
            if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8)
            {
                if (board[newY][newX] == nullptr || canCapture(Vector2i(newX, newY), board))
                    moves.push_back(Vector2i(newX, newY));
            }
        }
        return moves;
    }
};

// Derived class for Bishop
class Bishop : public Piece
{
public:
    Bishop(bool isWhite, Texture &texture) : Piece(isWhite, texture){}


    vector<Vector2i> getLegalMoves(Vector2i pos, Piece *board[8][8]) override
    {
        vector<Vector2i> moves;
        
        const int dx[] = {1, 1, -1, -1}; 
        const int dy[] = {-1, 1, -1, 1};
        
        for (int dir = 0; dir < 4; ++dir) {
            for (int step = 1; step < 8; ++step) {
                int newX = pos.x + dx[dir] * step;
                int newY = pos.y + dy[dir] * step;
                
                // Check bounds
                if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8)
                    break;
                
                // Empty square - add move and continue
                if (board[newY][newX] == nullptr) {
                    moves.push_back(Vector2i(newX, newY));
                }
                // Capture - add move and stop in this direction
                else if (canCapture(Vector2i(newX, newY), board)) {
                    moves.push_back(Vector2i(newX, newY));
                    break;
                }
                // Blocked by friendly piece - stop in this direction
                else {
                    break;
                }
            }
        }
        
        return moves;
    }
};

// Derived class for Queen
class Queen : public Piece
{
public:
    Queen(bool isWhite, Texture &texture) : Piece(isWhite, texture)
    {
        // Any Queen-specific initialization can go here
    }

    vector<Vector2i> getLegalMoves(Vector2i pos, Piece *board[8][8]) override
    {
        vector<Vector2i> moves;
        
        // The Queen combines Rook and Bishop movements
        // First, let's add diagonal moves (Bishop-like)
        const int bishopDx[] = {1, 1, -1, -1}; // top-right, bottom-right, top-left, bottom-left
        const int bishopDy[] = {-1, 1, -1, 1};
        
        for (int dir = 0; dir < 4; ++dir) {
            for (int step = 1; step < 8; ++step) {
                int newX = pos.x + bishopDx[dir] * step;
                int newY = pos.y + bishopDy[dir] * step;
                
                if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8)
                    break;
                
                if (board[newY][newX] == nullptr) {
                    moves.push_back(Vector2i(newX, newY));
                }
                else if (canCapture(Vector2i(newX, newY), board)) {
                    moves.push_back(Vector2i(newX, newY));
                    break;
                }
                else {
                    break;
                }
            }
        }
        
        // Then add straight moves (Rook-like)
        const int rookDx[] = {0, 0, 1, -1}; // up, down, right, left
        const int rookDy[] = {-1, 1, 0, 0};
        
        for (int dir = 0; dir < 4; ++dir) {
            for (int step = 1; step < 8; ++step) {
                int newX = pos.x + rookDx[dir] * step;
                int newY = pos.y + rookDy[dir] * step;
                
                if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8)
                    break;
                
                if (board[newY][newX] == nullptr) {
                    moves.push_back(Vector2i(newX, newY));
                }
                else if (canCapture(Vector2i(newX, newY), board)) {
                    moves.push_back(Vector2i(newX, newY));
                    break;
                }
                else {
                    break;
                }
            }
        }
        
        return moves;
    }
};

// Derived class for King
class King : public Piece
{
public:
    King(bool isWhite, Texture &texture) : Piece(isWhite, texture)
    {
        // Any King-specific initialization can go here
    }

    vector<Vector2i> getLegalMoves(Vector2i pos, Piece *board[8][8]) override
    {
        vector<Vector2i> moves;
        // King's 8 possible moves
        vector<Vector2i> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
        for (auto &dir : directions)
        {
            int newX = pos.x + dir.x;
            int newY = pos.y + dir.y;
            if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8)
            {
                if (board[newY][newX] == nullptr || canCapture(Vector2i(newX, newY), board))
                    moves.push_back(Vector2i(newX, newY));
            }
        }
        return moves;
    }
};