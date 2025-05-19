// Board.h
#pragma once
#include "Piece.h"
#include <array>

class Board
{
private:
    array<array<Piece *, 8>, 8> board;
    bool whiteTurn = true;

public:
    Board()
    {
        reset();
    }

    void reset()
    {
        for (auto &row : board)
            for (auto &cell : row)
                cell = nullptr;

        // Setup black pieces
        board[0][0] = new Rook({0, 0}, false);
        board[0][1] = new Knight({0, 1}, false);
        board[0][2] = new Bishop({0, 2}, false);
        board[0][3] = new Queen({0, 3}, false);
        board[0][4] = new King({0, 4}, false);
        board[0][5] = new Bishop({0, 5}, false);
        board[0][6] = new Knight({0, 6}, false);
        board[0][7] = new Rook({0, 7}, false);
        for (int i = 0; i < 8; ++i)
            board[1][i] = new Pawn({1, i}, false);

        // Setup white pieces
        for (int i = 0; i < 8; ++i)
            board[6][i] = new Pawn({6, i}, true);
        board[7][0] = new Rook({7, 0}, true);
        board[7][1] = new Knight({7, 1}, true);
        board[7][2] = new Bishop({7, 2}, true);
        board[7][3] = new Queen({7, 3}, true);
        board[7][4] = new King({7, 4}, true);
        board[7][5] = new Bishop({7, 5}, true);
        board[7][6] = new Knight({7, 6}, true);
        board[7][7] = new Rook({7, 7}, true);
    }

    const Piece *getPiece(Position p) const
    {
        return p.isValid() ? board[p.row][p.col] : nullptr;
    }

    Piece *getPiece(Position p)
    {
        return p.isValid() ? board[p.row][p.col] : nullptr;
    }

    bool move(Position from, Position to)
    {
        Piece *piece = getPiece(from);
        if (!piece || piece->isWhite() != whiteTurn)
            return false;

        auto legal = piece->getLegalMoves(reinterpret_cast<const Piece *(*)[8]>(&board));
        bool isLegal = false;
        for (auto m : legal)
            if (m == to)
            {
                isLegal = true;
                break;
            }

        if (!isLegal)
            return false;

        if (board[to.row][to.col])
            delete board[to.row][to.col]; // capture

        board[to.row][to.col] = piece;
        board[from.row][from.col] = nullptr;
        piece->setPosition(to);
        whiteTurn = !whiteTurn;
        return true;
    }

    vector<Position> getLegalMoves(Position p) const
    {
        const Piece* piece = getPiece(p);
        if (!piece || piece->isWhite() != whiteTurn)
            return {};
        return piece->getLegalMoves(board);  // pass the 2D std::array directly
    }
    
    bool isWhiteTurn() const
    {
        return whiteTurn;
    }

    ~Board()
    {
        for (auto &row : board)
            for (auto &cell : row)
                delete cell;
    }
};
