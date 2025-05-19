// Piece.h
#pragma once
#include "Position.h"
#include <vector>

using namespace std;

class Piece {
protected:
    bool white;
    Position pos;

public:
    Piece(Position p, bool isWhite) : pos(p), white(isWhite) {}
    virtual ~Piece() {}

    bool isWhite() const { return white; }
    Position getPosition() const { return pos; }
    void setPosition(Position p) { pos = p; }

    virtual char getSymbol() const = 0;
    virtual vector<Position> getLegalMoves(const Piece* board[8][8]) const = 0;
};

class Pawn : public Piece {
public:
    Pawn(Position p, bool isWhite) : Piece(p, isWhite) {}

    char getSymbol() const override { return 'P'; }

    vector<Position> getLegalMoves(const Piece* board[8][8]) const override {
        vector<Position> moves;
        int dir = white ? -1 : 1;
        int startRow = white ? 6 : 1;

        Position oneStep{ pos.row + dir, pos.col };
        if (oneStep.isValid() && board[oneStep.row][oneStep.col] == nullptr)
            moves.push_back(oneStep);

        Position twoSteps{ pos.row + 2 * dir, pos.col };
        if (pos.row == startRow && board[oneStep.row][oneStep.col] == nullptr && board[twoSteps.row][twoSteps.col] == nullptr)
            moves.push_back(twoSteps);

        for (int d = -1; d <= 1; d += 2) {
            Position diag{ pos.row + dir, pos.col + d };
            if (diag.isValid() && board[diag.row][diag.col] && board[diag.row][diag.col]->isWhite() != white)
                moves.push_back(diag);
        }

        return moves;
    }
};

class Knight : public Piece {
public:
    Knight(Position p, bool isWhite) : Piece(p, isWhite) {}

    char getSymbol() const override { return 'N'; }

    vector<Position> getLegalMoves(const Piece* board[8][8]) const override {
        vector<Position> moves;
        int d[8][2] = { {2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1} };
        for (auto& [dr, dc] : d) {
            Position newPos{ pos.row + dr, pos.col + dc };
            if (newPos.isValid() && (!board[newPos.row][newPos.col] || board[newPos.row][newPos.col]->isWhite() != white))
                moves.push_back(newPos);
        }
        return moves;
    }
};

class Rook : public Piece {
public:
    Rook(Position p, bool isWhite) : Piece(p, isWhite) {}

    char getSymbol() const override { return 'R'; }

    vector<Position> getLegalMoves(const Piece* board[8][8]) const override {
        vector<Position> moves;
        int d[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };

        for (auto& [dr, dc] : d) {
            for (int i = 1; i < 8; i++) {
                Position newPos{ pos.row + dr * i, pos.col + dc * i };
                if (!newPos.isValid()) break;
                if (!board[newPos.row][newPos.col])
                    moves.push_back(newPos);
                else {
                    if (board[newPos.row][newPos.col]->isWhite() != white)
                        moves.push_back(newPos);
                    break;
                }
            }
        }

        return moves;
    }
};

class Bishop : public Piece {
public:
    Bishop(Position p, bool isWhite) : Piece(p, isWhite) {}

    char getSymbol() const override { return 'B'; }

    vector<Position> getLegalMoves(const Piece* board[8][8]) const override {
        vector<Position> moves;
        int d[4][2] = { {1,1},{-1,-1},{-1,1},{1,-1} };

        for (auto& [dr, dc] : d) {
            for (int i = 1; i < 8; i++) {
                Position newPos{ pos.row + dr * i, pos.col + dc * i };
                if (!newPos.isValid()) break;
                if (!board[newPos.row][newPos.col])
                    moves.push_back(newPos);
                else {
                    if (board[newPos.row][newPos.col]->isWhite() != white)
                        moves.push_back(newPos);
                    break;
                }
            }
        }

        return moves;
    }
};

class Queen : public Piece {
public:
    Queen(Position p, bool isWhite) : Piece(p, isWhite) {}

    char getSymbol() const override { return 'Q'; }

    vector<Position> getLegalMoves(const Piece* board[8][8]) const override {
        vector<Position> moves;
        Rook r(pos, white);
        Bishop b(pos, white);
        auto rookMoves = r.getLegalMoves(board);
        auto bishopMoves = b.getLegalMoves(board);
        moves.insert(moves.end(), rookMoves.begin(), rookMoves.end());
        moves.insert(moves.end(), bishopMoves.begin(), bishopMoves.end());
        return moves;
    }
};

class King : public Piece {
public:
    King(Position p, bool isWhite) : Piece(p, isWhite) {}

    char getSymbol() const override { return 'K'; }

    virtual vector<Position> getLegalMoves(const array<array<Piece*, 8>, 8>& board) const = 0;
{        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                if (dr == 0 && dc == 0) continue;
                Position newPos{ pos.row + dr, pos.col + dc };
                if (newPos.isValid() && (!board[newPos.row][newPos.col] || board[newPos.row][newPos.col]->isWhite() != white))
                    moves.push_back(newPos);
            }
        }
        return moves;
    }}
};
