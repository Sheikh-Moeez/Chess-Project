#include <SFML/Graphics.hpp>
#include <vector>
#include "Piece.hpp"
#include <iostream>
#include <string>

using namespace sf;
using namespace std;

const Color HEADER_COLOR(230, 138, 53);
const Color BACKGROUND_COLOR(38, 36, 35);
const Color MOVE_HIGHLIGHT_COLOR(67, 115, 115, 140);
const Color SELECTED_HIGHLIGHT_COLOR(33, 150, 243, 150);
const Color WIN_MESSAGE_BG_COLOR(0, 0, 0, 180);
const Color MENU_BG_COLOR(38, 36, 35);
const Color BUTTON_COLOR(70, 130, 180);
const Color BUTTON_HOVER_COLOR(100, 149, 237);
const Color INPUT_BOX_COLOR(60, 60, 60);
const Color INPUT_BOX_ACTIVE_COLOR(80, 80, 80);

enum PieceID
{
    W_P,
    W_R,
    W_N,
    W_B,
    W_Q,
    W_K,
    B_P,
    B_R,
    B_N,
    B_B,
    B_Q,
    B_K
};
enum GameState
{
    MAIN_MENU,
    NAME_INPUT,
    PLAYING
};

class Button
{
public:
    RectangleShape shape;
    Text text;
    bool isHovered;

    Button(Vector2f size, Vector2f position, string buttonText, Font &font)
    {
        shape.setSize(size);
        shape.setPosition(position);
        shape.setFillColor(BUTTON_COLOR);

        text.setFont(font);
        text.setString(buttonText);
        text.setCharacterSize(24);
        text.setFillColor(Color::White);

        FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        text.setPosition(position.x + size.x / 2.0f, position.y + size.y / 2.0f);

        isHovered = false;
    }

    void update(Vector2f mousePos)
    {
        isHovered = shape.getGlobalBounds().contains(mousePos);
        shape.setFillColor(isHovered ? BUTTON_HOVER_COLOR : BUTTON_COLOR);
    }

    bool isClicked(Vector2f mousePos)
    {
        return shape.getGlobalBounds().contains(mousePos);
    }

    void draw(RenderWindow &window)
    {
        window.draw(shape);
        window.draw(text);
    }
};

class InputBox
{

public:
    RectangleShape shape;
    Text text;
    Text label;
    string content;
    bool isActive;
    bool showCursor;
    Clock cursorClock;

    InputBox(Vector2f size, Vector2f position, string labelText, Font &font)
    {
        shape.setSize(size);
        shape.setPosition(position);
        shape.setFillColor(INPUT_BOX_COLOR);
        shape.setOutlineThickness(2);
        shape.setOutlineColor(Color::White);

        text.setFont(font);
        text.setCharacterSize(20);
        text.setFillColor(Color::White);
        text.setPosition(position.x + 10, position.y + size.y / 2 - 10);

        label.setFont(font);
        label.setString(labelText);
        label.setCharacterSize(18);
        label.setFillColor(Color::White);
        label.setPosition(position.x, position.y - 25);

        content = "";
        isActive = false;
        showCursor = true;
    }

    void update(Vector2f mousePos)
    {
        shape.setFillColor(isActive ? INPUT_BOX_ACTIVE_COLOR : INPUT_BOX_COLOR);

        if (cursorClock.getElapsedTime().asMilliseconds() > 500)
        {
            showCursor = !showCursor;
            cursorClock.restart();
        }

        string displayText = content;
        if (isActive && showCursor)
        {
            displayText += "|";
        }
        text.setString(displayText);
    }

    void setActive(bool active)
    {
        isActive = active;
        cursorClock.restart();
        showCursor = true;
    }

    bool isClicked(Vector2f mousePos)
    {
        return shape.getGlobalBounds().contains(mousePos);
    }

    void handleTextInput(Uint32 unicode)
    {
        if (!isActive)
            return;

        if (unicode == 8 && content.length() > 0)
        { // Backspace
            content.pop_back();
        }
        else if (unicode >= 32 && unicode < 127 && content.length() < 20)
        { // Printable characters
            content += static_cast<char>(unicode);
        }
    }

    void draw(RenderWindow &window)
    {
        window.draw(shape);
        window.draw(label);
        window.draw(text);
    }
};

bool checkForWin(Piece *board[8][8], bool &whiteWins)
{
    bool whiteKing = false, blackKing = false;
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            if (board[r][c] && typeid(*board[r][c]) == typeid(King))
                board[r][c]->isWhite() ? whiteKing = true : blackKing = true;

    if (!whiteKing)
    {
        whiteWins = false;
        return true;
    }
    if (!blackKing)
    {
        whiteWins = true;
        return true;
    }
    return false;
}

void setupPieces(Piece *pieces[8][8], Texture textures[12], float startX, float startY, float tileSize)
{
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            pieces[r][c] = nullptr;

    for (int c = 0; c < 8; c++)
    {
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
            if (pieces[r][c])
            {
                pieces[r][c]->setPosition(Vector2f(startX + c * tileSize + tileSize / 2, startY + r * tileSize + tileSize / 2));
                Sprite &s = pieces[r][c]->getSprite();
                float scale = 0.9f * tileSize / s.getTexture()->getSize().x;
                s.setScale(scale, scale);
            }
}

void cleanupPieces(Piece *board[8][8])
{
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            if (board[r][c])
            {
                delete board[r][c];
                board[r][c] = nullptr;
            }
}

Vector2i getBoardPos(Vector2f mouse, float startX, float startY, float tileSize)
{
    int col = (mouse.x - startX) / tileSize;
    int row = (mouse.y - startY) / tileSize;
    return (col >= 0 && col < 8 && row >= 0 && row < 8) ? Vector2i(col, row) : Vector2i(-1, -1);
}

int main()
{
    RenderWindow window(VideoMode(1000, 800), "Chess");
    window.setFramerateLimit(60);

    // Set window icon
    Image icon;
    if (icon.loadFromFile("Assets/icon.png"))
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Font font;
    if (!font.loadFromFile("Anton-Regular.ttf"))
        return -1;

    // Game state variables
    GameState gameState = MAIN_MENU;
    string player1Name = "";
    string player2Name = "";

    float tileSize = 80.f;
    float boardWidth = tileSize * 8;
    float boardHeight = tileSize * 8;
    float boardStartX = (window.getSize().x - boardWidth) / 2.0f;
    float boardStartY = (window.getSize().y - boardHeight) / 2.0f;

    // Main Menu Elements
    Text titleText("CHESS GAME", font, 48);
    titleText.setFillColor(HEADER_COLOR);
    titleText.setStyle(Text::Bold);
    FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.left + titleBounds.width / 2.0f, titleBounds.top + titleBounds.height / 2.0f);
    titleText.setPosition(window.getSize().x / 2.0f, 150);

    Button newGameButton(Vector2f(200, 60), Vector2f(window.getSize().x / 2.0f - 100, 250), "New Game", font);
    Button exitButton(Vector2f(200, 60), Vector2f(window.getSize().x / 2.0f - 100, 330), "Exit", font);

    // Name Input Elements
    Text nameInputTitle("Enter Player Names", font, 36);
    nameInputTitle.setFillColor(Color::White);
    FloatRect nameInputBounds = nameInputTitle.getLocalBounds();
    nameInputTitle.setOrigin(nameInputBounds.left + nameInputBounds.width / 2.0f, nameInputBounds.top + nameInputBounds.height / 2.0f);
    nameInputTitle.setPosition(window.getSize().x / 2.0f, 200);

    InputBox player1Input(Vector2f(300, 40), Vector2f(window.getSize().x / 2.0f - 150, 280), "Player 1 (White):", font);
    InputBox player2Input(Vector2f(300, 40), Vector2f(window.getSize().x / 2.0f - 150, 360), "Player 2 (Black):", font);
    Button startGameButton(Vector2f(200, 60), Vector2f(window.getSize().x / 2.0f - 100, 450), "Start Game", font);
    Button backButton(Vector2f(200, 60), Vector2f(window.getSize().x / 2.0f - 100, 530), "Back", font);

    // Game Elements
    RectangleShape board[8][8];
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
        {
            board[r][c].setSize(Vector2f(tileSize, tileSize));
            board[r][c].setPosition(boardStartX + c * tileSize, boardStartY + r * tileSize);
            board[r][c].setFillColor((r + c) % 2 == 0 ? Color(118, 150, 86) : Color(238, 238, 210));
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

    Piece *pieces[8][8] = {nullptr};

    bool whiteTurn = true, pieceSelected = false, gameOver = false, whiteWins = false;
    Vector2i selected(-1, -1);
    vector<Vector2i> moves;
    vector<RectangleShape> moveHints;

    RectangleShape selectionHighlight;
    selectionHighlight.setSize(Vector2f(tileSize, tileSize));
    selectionHighlight.setFillColor(SELECTED_HIGHLIGHT_COLOR);

    Text turnText("", font, 28);
    turnText.setPosition(boardStartX, boardStartY + boardHeight + 20);
    turnText.setFillColor(Color::White);

    Text p1Text("", font, 24);
    Text p2Text("", font, 24);
    p1Text.setPosition(boardStartX, boardStartY - 40);
    p2Text.setPosition(boardStartX + boardWidth - 200, boardStartY - 40);

    Button menuButton(Vector2f(120, 40), Vector2f(boardStartX + boardWidth - 120, boardStartY + boardHeight + 20), "Main Menu", font);

    RectangleShape winMessageBg(Vector2f(600, 200));
    winMessageBg.setFillColor(WIN_MESSAGE_BG_COLOR);
    winMessageBg.setPosition((window.getSize().x - 600) / 2.f, (window.getSize().y - 200) / 2.f);

    Text winMessage("", font, 46);
    winMessage.setFillColor(Color::White);

    RectangleShape menuBackground(Vector2f(window.getSize().x, window.getSize().y));
    menuBackground.setFillColor(MENU_BG_COLOR);

    while (window.isOpen())
    {
        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (gameState == MAIN_MENU)
            {
                newGameButton.update(mousePos);
                exitButton.update(mousePos);

                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
                {
                    if (newGameButton.isClicked(mousePos))
                    {
                        gameState = NAME_INPUT;
                        player1Input.content = "";
                        player2Input.content = "";
                    }
                    else if (exitButton.isClicked(mousePos))
                    {
                        window.close();
                    }
                }
            }
            else if (gameState == NAME_INPUT)
            {
                player1Input.update(mousePos);
                player2Input.update(mousePos);
                startGameButton.update(mousePos);
                backButton.update(mousePos);

                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
                {
                    if (player1Input.isClicked(mousePos))
                    {
                        player1Input.setActive(true);
                        player2Input.setActive(false);
                    }
                    else if (player2Input.isClicked(mousePos))
                    {
                        player1Input.setActive(false);
                        player2Input.setActive(true);
                    }
                    else if (startGameButton.isClicked(mousePos))
                    {
                        if (!player1Input.content.empty() && !player2Input.content.empty())
                        {
                            player1Name = player1Input.content;
                            player2Name = player2Input.content;
                            gameState = PLAYING;

                            // Initialize game
                            setupPieces(pieces, textures, boardStartX, boardStartY, tileSize);
                            whiteTurn = true;
                            pieceSelected = false;
                            gameOver = false;
                            moves.clear();
                            moveHints.clear();
                            selected = {-1, -1};

                            // Update UI texts
                            turnText.setString("Turn: " + player1Name);
                            p1Text.setString(player1Name + " (White)");
                            p2Text.setString(player2Name + " (Black)");
                            p1Text.setStyle(Text::Bold);
                            p2Text.setStyle(Text::Regular);
                        }
                    }
                    else if (backButton.isClicked(mousePos))
                    {
                        gameState = MAIN_MENU;
                        player1Input.setActive(false);
                        player2Input.setActive(false);
                    }
                    else
                    {
                        player1Input.setActive(false);
                        player2Input.setActive(false);
                    }
                }

                if (event.type == Event::TextEntered)
                {
                    player1Input.handleTextInput(event.text.unicode);
                    player2Input.handleTextInput(event.text.unicode);
                }
            }
            else if (gameState == PLAYING)
            {
                menuButton.update(mousePos);

                if (event.type == Event::KeyPressed && event.key.code == Keyboard::R)
                {
                    cleanupPieces(pieces);
                    setupPieces(pieces, textures, boardStartX, boardStartY, tileSize);
                    whiteTurn = true;
                    pieceSelected = false;
                    gameOver = false;
                    moves.clear();
                    moveHints.clear();
                    selected = {-1, -1};
                    turnText.setString("Turn: " + player1Name);
                    p1Text.setStyle(Text::Bold);
                    p2Text.setStyle(Text::Regular);
                }

                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
                {
                    if (menuButton.isClicked(mousePos))
                    {
                        cleanupPieces(pieces);
                        gameState = MAIN_MENU;
                    }
                    else if (!gameOver)
                    {
                        Vector2i pos = getBoardPos(mousePos, boardStartX, boardStartY, tileSize);
                        if (pos.x != -1)
                        {
                            if (!pieceSelected)
                            {
                                Piece *p = pieces[pos.y][pos.x];
                                if (p && p->isWhite() == whiteTurn)
                                {
                                    selected = pos;
                                    pieceSelected = true;
                                    moves = p->getLegalMoves(pos, pieces);
                                    moveHints.clear();
                                    for (auto &m : moves)
                                    {
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
                                for (auto &m : moves)
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

                                        if (checkForWin(pieces, whiteWins))
                                        {
                                            gameOver = true;
                                            string winner = whiteWins ? player1Name + " Wins!" : player2Name + " Wins!";
                                            winMessage.setString(winner);
                                            FloatRect rect = winMessage.getLocalBounds();
                                            winMessage.setOrigin(rect.left + rect.width / 2.f, rect.top + rect.height / 2.f);
                                            winMessage.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
                                        }
                                        else
                                        {
                                            whiteTurn = !whiteTurn;
                                            turnText.setString("Turn: " + (whiteTurn ? player1Name : player2Name));
                                            p1Text.setStyle(whiteTurn ? Text::Bold : Text::Regular);
                                            p2Text.setStyle(whiteTurn ? Text::Regular : Text::Bold);
                                        }
                                        break;
                                    }
                                }
                                pieceSelected = false;
                                moves.clear();
                                moveHints.clear();
                            }
                        }
                    }
                }
            }
        }

        window.clear(BACKGROUND_COLOR);

        if (gameState == MAIN_MENU)
        {
            window.draw(menuBackground);
            window.draw(titleText);
            newGameButton.draw(window);
            exitButton.draw(window);
        }
        else if (gameState == NAME_INPUT)
        {
            window.draw(menuBackground);
            window.draw(nameInputTitle);
            player1Input.draw(window);
            player2Input.draw(window);
            startGameButton.draw(window);
            backButton.draw(window);
        }
        else if (gameState == PLAYING)
        {
            for (auto &row : board)
                for (auto &tile : row)
                    window.draw(tile);

            for (auto &h : moveHints)
                window.draw(h);
            if (pieceSelected)
                window.draw(selectionHighlight);

            for (int r = 0; r < 8; r++)
                for (int c = 0; c < 8; c++)
                    if (pieces[r][c])
                        window.draw(pieces[r][c]->getSprite());

            window.draw(p1Text);
            window.draw(p2Text);
            window.draw(turnText);
            menuButton.draw(window);

            if (gameOver)
            {
                window.draw(winMessageBg);
                window.draw(winMessage);
            }
        }

        window.display();
    }

    cleanupPieces(pieces);
    return 0;
}