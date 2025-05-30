#include <SFML/Graphics.hpp>
#include <vector>
#include "Piece.hpp"
#include <iostream>

using namespace sf;
using namespace std;

const Color HEADER_COLOR(230, 138, 53);
const Color BACKGROUND_COLOR(41, 23, 6);
const Color MOVE_HIGHLIGHT_COLOR(76, 175, 80, 150);
const Color SELECTED_HIGHLIGHT_COLOR(33, 150, 243, 150);
const Color WIN_MESSAGE_BG_COLOR(0, 0, 0, 180);

enum PieceID { W_P, W_R, W_N, W_B, W_Q, W_K, B_P, B_R, B_N, B_B, B_Q, B_K };

bool checkForWin(Piece* board[8][8], bool& whiteWins)
{
    bool whiteKing = false, blackKing = false;
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            if (board[r][c] && typeid(*board[r][c]) == typeid(King))
                board[r][c]->isWhite() ? whiteKing = true : blackKing = true;

    if (!whiteKing) { whiteWins = false; return true; }
    if (!blackKing) { whiteWins = true; return true; }
    return false;
}

void setupPieces(Piece* pieces[8][8], Texture textures[12], float startX, float startY, float tileSize)
{
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            pieces[r][c] = nullptr;

    for (int c = 0; c < 8; c++) {
        pieces[6][c] = new Pawn(true, textures[W_P]);
        pieces[1][c] = new Pawn(false, textures[B_P]);
    }

    pieces[7][0] = new Rook(true, textures[W_R]);
    pieces[7][1] = new Knight(true, textures[W_N]);
    pieces[7][2] = new Bishop(true, textures[W_B]);
    pieces[7][3] = new Queen(true, textures[W_Q]);
    pieces[7][4] = new King(true, textures[W_K]);
    pieces[7][5] = new Bishop(true, textures[W_B]);
    pieces[7][6] = new Knight(true, textures[W_N]);
    pieces[7][7] = new Rook(true, textures[W_R]);

    pieces[0][0] = new Rook(false, textures[B_R]);
    pieces[0][1] = new Knight(false, textures[B_N]);
    pieces[0][2] = new Bishop(false, textures[B_B]);
    pieces[0][3] = new Queen(false, textures[B_Q]);
    pieces[0][4] = new King(false, textures[B_K]);
    pieces[0][5] = new Bishop(false, textures[B_B]);
    pieces[0][6] = new Knight(false, textures[B_N]);
    pieces[0][7] = new Rook(false, textures[B_R]);

    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            if (pieces[r][c]) {
                pieces[r][c]->setPosition(Vector2f(startX + c * tileSize + tileSize / 2, startY + r * tileSize + tileSize / 2));
                Sprite& s = pieces[r][c]->getSprite();
                float scale = 0.9f * tileSize / s.getTexture()->getSize().x;
                s.setScale(scale, scale);
            }
}

void cleanupPieces(Piece* board[8][8]) {
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            if (board[r][c]) {
                delete board[r][c];
                board[r][c] = nullptr;
            }
}

Vector2i getBoardPos(Vector2f mouse, float startX, float startY, float tileSize) {
    int col = (mouse.x - startX) / tileSize;
    int row = (mouse.y - startY) / tileSize;
    return (col >= 0 && col < 8 && row >= 0 && row < 8) ? Vector2i(col, row) : Vector2i(-1, -1);
}

int main()
{
    RenderWindow window(VideoMode(1000, 800), "SFML Chess");
    window.setFramerateLimit(60);

    // Set window icon
    Image icon;
    if (icon.loadFromFile("Assets/icon.png"))
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Font font;
    if (!font.loadFromFile("Anton-Regular.ttf")) return -1;

    float tileSize = 80.f;
    float boardWidth = tileSize * 8;
    float boardHeight = tileSize * 8;
    float boardStartX = (window.getSize().x - boardWidth) / 2.0f;
    float boardStartY = (window.getSize().y - boardHeight) / 2.0f;

    RectangleShape board[8][8];
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++) {
            board[r][c].setSize(Vector2f(tileSize, tileSize));
            board[r][c].setPosition(boardStartX + c * tileSize, boardStartY + r * tileSize);
            board[r][c].setFillColor((r + c) % 2 == 0 ? Color(122, 65, 15) : Color(219, 149, 88));
        }

    Texture textures[12];
    textures[W_P].loadFromFile("Assets/White Pieces/Pawn.png");
    textures[W_R].loadFromFile("Assets/White Pieces/Rook.png");
    textures[W_N].loadFromFile("Assets/White Pieces/Knight.png");
    textures[W_B].loadFromFile("Assets/White Pieces/Bishop.png");
    textures[W_Q].loadFromFile("Assets/White Pieces/Queen.png");
    textures[W_K].loadFromFile("Assets/White Pieces/King.png");
    textures[B_P].loadFromFile("Assets/Black Pieces/Pawn.png");
    textures[B_R].loadFromFile("Assets/Black Pieces/Rook.png");
    textures[B_N].loadFromFile("Assets/Black Pieces/Knight.png");
    textures[B_B].loadFromFile("Assets/Black Pieces/Bishop.png");
    textures[B_Q].loadFromFile("Assets/Black Pieces/Queen.png");
    textures[B_K].loadFromFile("Assets/Black Pieces/King.png");

    Piece* pieces[8][8] = { nullptr };
    setupPieces(pieces, textures, boardStartX, boardStartY, tileSize);

    bool whiteTurn = true, pieceSelected = false, gameOver = false, whiteWins = false;
    Vector2i selected(-1, -1);
    vector<Vector2i> moves;
    vector<RectangleShape> moveHints;

    RectangleShape selectionHighlight;
    selectionHighlight.setSize(Vector2f(tileSize, tileSize));
    selectionHighlight.setFillColor(SELECTED_HIGHLIGHT_COLOR);

    Text turnText("Turn: White", font, 28);
    turnText.setPosition(boardStartX, boardStartY + boardHeight + 20);
    turnText.setFillColor(Color::White);

    Text p1Text("Player 1 (White)", font, 24);
    Text p2Text("Player 2 (Black)", font, 24);
    p1Text.setPosition(boardStartX, boardStartY - 40);
    p2Text.setPosition(boardStartX + boardWidth - p2Text.getLocalBounds().width, boardStartY - 40);
    p1Text.setStyle(Text::Bold);
    p2Text.setStyle(Text::Regular);

    RectangleShape winMessageBg(Vector2f(600, 200));
    winMessageBg.setFillColor(WIN_MESSAGE_BG_COLOR);
    winMessageBg.setPosition((window.getSize().x - 600) / 2.f, (window.getSize().y - 200) / 2.f);

    Text winMessage("", font, 46);
    winMessage.setFillColor(Color::White);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::R) {
                cleanupPieces(pieces);
                setupPieces(pieces, textures, boardStartX, boardStartY, tileSize);
                whiteTurn = true;
                pieceSelected = false;
                gameOver = false;
                moves.clear(); moveHints.clear();
                selected = {-1, -1};
                turnText.setString("Turn: White");
                p1Text.setStyle(Text::Bold);
                p2Text.setStyle(Text::Regular);
            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && !gameOver) {
                Vector2i pos = getBoardPos(window.mapPixelToCoords(Mouse::getPosition(window)), boardStartX, boardStartY, tileSize);
                if (pos.x != -1) {
                    if (!pieceSelected) {
                        Piece* p = pieces[pos.y][pos.x];
                        if (p && p->isWhite() == whiteTurn) {
                            selected = pos;
                            pieceSelected = true;
                            moves = p->getLegalMoves(pos, pieces);
                            moveHints.clear();
                            for (auto& m : moves) {
                                RectangleShape h;
                                h.setSize(Vector2f(tileSize, tileSize));
                                h.setPosition(boardStartX + m.x * tileSize, boardStartY + m.y * tileSize);
                                h.setFillColor(MOVE_HIGHLIGHT_COLOR);
                                moveHints.push_back(h);
                            }
                            selectionHighlight.setPosition(boardStartX + pos.x * tileSize, boardStartY + pos.y * tileSize);
                        }
                    }
                    else
                    {
                        for (auto& m : moves)
                        {
                            if (m == pos)
                            {
                                if (pieces[pos.y][pos.x])
                                {
                                    delete pieces[pos.y][pos.x];
                                }
                                pieces[pos.y][pos.x] = pieces[selected.y][selected.x];
                                pieces[selected.y][selected.x] = nullptr;
                                pieces[pos.y][pos.x]->setPosition(Vector2f(boardStartX + pos.x * tileSize + tileSize / 2, boardStartY + pos.y * tileSize + tileSize / 2));

                                if (checkForWin(pieces, whiteWins)) {
                                    gameOver = true;
                                    string winner = whiteWins ? "White Wins!" : "Black Wins!";
                                    winMessage.setString(winner);
                                    FloatRect rect = winMessage.getLocalBounds();
                                    winMessage.setOrigin(rect.left + rect.width / 2.f, rect.top + rect.height / 2.f);
                                    winMessage.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
                                } else {
                                    whiteTurn = !whiteTurn;
                                    turnText.setString(whiteTurn ? "Turn: White" : "Turn: Black");
                                    p1Text.setStyle(whiteTurn ? Text::Bold : Text::Regular);
                                    p2Text.setStyle(whiteTurn ? Text::Regular : Text::Bold);
                                }
                                break;
                            }
                        }
                        pieceSelected = false;
                        moves.clear(); moveHints.clear();
                    }
                }
            }
        }

        window.clear(BACKGROUND_COLOR);
        for (auto& row : board)
            for (auto& tile : row)
                window.draw(tile);

        for (auto& h : moveHints) window.draw(h);
        if (pieceSelected) window.draw(selectionHighlight);

        for (int r = 0; r < 8; r++)
            for (int c = 0; c < 8; c++)
                if (pieces[r][c])
                    window.draw(pieces[r][c]->getSprite());

        window.draw(p1Text); window.draw(p2Text); window.draw(turnText);
        if (gameOver) { window.draw(winMessageBg); window.draw(winMessage); }
        window.display();
    }

    cleanupPieces(pieces);
    return 0;
}