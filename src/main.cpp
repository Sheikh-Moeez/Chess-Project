#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

void newBoard(Sprite pieces[8][8], float tileSize, float boardStartX, float boardStartY)
{
    // Static textures to keep them alive
    static Texture W_PAWN, W_ROOK, W_KNIGHT, W_BISHOP, W_QUEEN, W_KING;
    static Texture B_PAWN, B_ROOK, B_KNIGHT, B_BISHOP, B_QUEEN, B_KING;

    // Load white pieces
    W_PAWN.loadFromFile("Assets/White Pieces/Pawn.png");
    W_ROOK.loadFromFile("Assets/White Pieces/Rook.png");
    W_KNIGHT.loadFromFile("Assets/White Pieces/Knight.png");
    W_BISHOP.loadFromFile("Assets/White Pieces/Bishop.png");
    W_QUEEN.loadFromFile("Assets/White Pieces/Queen.png");
    W_KING.loadFromFile("Assets/White Pieces/King.png");

    // Load black pieces
    B_PAWN.loadFromFile("Assets/Black Pieces/Pawn.png");
    B_ROOK.loadFromFile("Assets/Black Pieces/Rook.png");
    B_KNIGHT.loadFromFile("Assets/Black Pieces/Knight.png");
    B_BISHOP.loadFromFile("Assets/Black Pieces/Bishop.png");
    B_QUEEN.loadFromFile("Assets/Black Pieces/Queen.png");
    B_KING.loadFromFile("Assets/Black Pieces/King.png");

    // Clear all pieces
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            pieces[row][col] = Sprite(); // Reset
        }
    }

    // Place pawns
    for (int col = 0; col < 8; col++)
    {
        pieces[6][col].setTexture(W_PAWN);
        pieces[1][col].setTexture(B_PAWN);
    }

    // Place back rows
    Texture* whiteBack[8] = { &W_ROOK, &W_KNIGHT, &W_BISHOP, &W_QUEEN, &W_KING, &W_BISHOP, &W_KNIGHT, &W_ROOK };
    Texture* blackBack[8] = { &B_ROOK, &B_KNIGHT, &B_BISHOP, &B_QUEEN, &B_KING, &B_BISHOP, &B_KNIGHT, &B_ROOK };

    for (int col = 0; col < 8; col++)
    {
        pieces[7][col].setTexture(*whiteBack[col]);
        pieces[0][col].setTexture(*blackBack[col]);
    }

    // Set position, origin, and scale
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            if (pieces[row][col].getTexture())
            {
                Vector2u size = pieces[row][col].getTexture()->getSize();

                // Scale down to fit nicely within the tile
                float scaleFactor = 0.8f;
                pieces[row][col].setScale(
                    scaleFactor * tileSize / size.x,
                    scaleFactor * tileSize / size.y
                );

                // Set origin to center of sprite
                pieces[row][col].setOrigin(size.x / 2.f, size.y / 2.f);

                // Position to center of tile
                pieces[row][col].setPosition(
                    boardStartX + col * tileSize + tileSize / 2.f,
                    boardStartY + row * tileSize + tileSize / 2.f
                );
            }
        }
    }
}

int main()
{
    RenderWindow window(VideoMode(1289, 720), "2D Chess Game");

    // Header bar
    RectangleShape Header(Vector2f(window.getSize().x, 100));
    Header.setFillColor(Color(230, 138, 53));
    Header.setPosition(0, 0);

    // Load fonts
    Font font, Player_font;
    if (!font.loadFromFile("Anton-Regular.ttf"))
        return -1;
    if (!Player_font.loadFromFile("Lora-Italic.ttf"))
        return -1;

    // Title text
    Text title("2D CHESS GAME", font, 44);
    title.setFillColor(Color(225, 255, 255));
    FloatRect textBounds = title.getLocalBounds();
    title.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
    title.setPosition(window.getSize().x / 2.f, 50);

    // Chessboard setup
    RectangleShape board[8][8];
    float tileSize = 70.f;
    float boardWidth = tileSize * 8;
    float boardHeight = tileSize * 8;
    float boardStartX = (window.getSize().x - boardWidth) / 2.f;
    float boardStartY = 150.f;

    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            board[row][col].setSize(Vector2f(tileSize, tileSize));
            board[row][col].setPosition(boardStartX + col * tileSize, boardStartY + row * tileSize);
            board[row][col].setFillColor((row + col) % 2 == 0 ? Color(59, 34, 12) : Color(214, 138, 71));
        }
    }

    // Player names
    Text Player1("Player 1", Player_font, 40);
    // Player1.setFillColor(Color::White);
    Player1.setPosition(boardStartX - 300, boardStartY);

    Text Player2("Player 2", Player_font, 40);
    Player2.setFillColor(Color::White);
    Player2.setPosition(boardStartX + boardWidth + 70, boardStartY);

    // Create chess pieces
    Sprite pieces[8][8];
    newBoard(pieces, tileSize, boardStartX, boardStartY);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color(128, 66, 8));
        window.draw(Header);
        window.draw(title);

        for (int row = 0; row < 8; row++)
            for (int col = 0; col < 8; col++)
                window.draw(board[row][col]);

        window.draw(Player1);
        window.draw(Player2);

        for (int row = 0; row < 8; row++)
            for (int col = 0; col < 8; col++)
                if (pieces[row][col].getTexture())
                    window.draw(pieces[row][col]);

        window.display();
    }

    return 0;
}