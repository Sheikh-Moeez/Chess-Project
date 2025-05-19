
// // // // main.cpp
// // // #include <SFML/Graphics.hpp>
// // // #include <memory>
// // // #include <vector>
// // // #include "Piece.h"
// // // #include "Board.h"
// // // using namespace sf;

// // // int main()
// // // {
// // //     RenderWindow window(VideoMode(720, 800), "Chess with Legal Moves");
// // //     float tileSize = 80.f;
// // //     float boardStartX = 40.f, boardStartY = 120.f;

// // //     RectangleShape boardTiles[8][8];
// // //     for (int row = 0; row < 8; row++)
// // //     {
// // //         for (int col = 0; col < 8; col++)
// // //         {
// // //             boardTiles[row][col].setSize(Vector2f(tileSize, tileSize));
// // //             boardTiles[row][col].setPosition(boardStartX + col * tileSize, boardStartY + row * tileSize);
// // //             boardTiles[row][col].setFillColor((row + col) % 2 == 0 ? Color(235, 235, 208) : Color(119, 148, 85));
// // //         }
// // //     }

// // //     sf::Sprite spritePieces[8][8];
// // //     Board board;
// // //     board.setSpriteBoard(spritePieces);

// // //     // Setup example piece
// // //     Texture wKnightTex;
// // //     wKnightTex.loadFromFile("Assets/White Pieces/Knight.png");
// // //     auto knight = std::make_shared<Knight>(Position{7, 1}, true);
// // //     knight->setTexture(wKnightTex, tileSize, boardStartX, boardStartY);
// // //     board.placePiece(knight);

// // //     Position selectedPos{-1, -1};
// // //     std::vector<Position> highlights;

// // //     while (window.isOpen())
// // //     {
// // //         Event event;
// // //         while (window.pollEvent(event))
// // //         {
// // //             if (event.type == Event::Closed)
// // //                 window.close();

// // //             if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
// // //             {
// // //                 Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
// // //                 int col = (mousePos.x - boardStartX) / tileSize;
// // //                 int row = (mousePos.y - boardStartY) / tileSize;
// // //                 if (row >= 0 && row < 8 && col >= 0 && col < 8)
// // //                 {
// // //                     Position clicked{row, col};
// // //                     auto piece = board.getPieceAt(clicked);
// // //                     if (piece)
// // //                     {
// // //                         selectedPos = clicked;
// // //                         highlights = board.getHighlights(clicked);
// // //                     }
// // //                 }
// // //             }
// // //         }

// // //         window.clear(Color::White);

// // //         for (int row = 0; row < 8; row++)
// // //         {
// // //             for (int col = 0; col < 8; col++)
// // //             {
// // //                 window.draw(boardTiles[row][col]);
// // //             }
// // //         }

// // //         for (const auto &pos : highlights)
// // //         {
// // //             RectangleShape highlight(Vector2f(tileSize, tileSize));
// // //             highlight.setPosition(boardStartX + pos.col * tileSize, boardStartY + pos.row * tileSize);
// // //             highlight.setFillColor(Color(0, 255, 0, 100));
// // //             window.draw(highlight);
// // //         }

// // //         for (int row = 0; row < 8; row++)
// // //         {
// // //             for (int col = 0; col < 8; col++)
// // //             {
// // //                 if (spritePieces[row][col].getTexture())
// // //                 {
// // //                     window.draw(spritePieces[row][col]);
// // //                 }
// // //             }
// // //         }

// // //         window.display();
// // //     }

// // //     return 0;
// // // }
// // #include <SFML/Graphics.hpp>
// // #include <vector>
// // #include "Piece.h"
// // #include "Board.h"

// // using namespace sf;
// // using namespace std;

// // int main()
// // {
// //     RenderWindow window(VideoMode(720, 800), "Chess with Legal Moves");
// //     float tileSize = 80.f;
// //     float boardStartX = 40.f, boardStartY = 120.f;

// //     RectangleShape boardTiles[8][8];
// //     for (int row = 0; row < 8; row++)
// //     {
// //         for (int col = 0; col < 8; col++)
// //         {
// //             boardTiles[row][col].setSize(Vector2f(tileSize, tileSize));
// //             boardTiles[row][col].setPosition(boardStartX + col * tileSize, boardStartY + row * tileSize);
// //             boardTiles[row][col].setFillColor((row + col) % 2 == 0 ? Color(235, 235, 208) : Color(119, 148, 85));
// //         }
// //     }

// //     Sprite spritePieces[8][8];
// //     Board board;
// //     board.setSpriteBoard(spritePieces);

// //     // Setup example piece
// //     Texture wKnightTex;
// //     wKnightTex.loadFromFile("Assets/White Pieces/Knight.png");
// //     Knight *knight = new Knight({7, 1}, true);
// //     knight->setTexture(wKnightTex, tileSize, boardStartX, boardStartY);
// //     board.placePiece(knight);

// //     Position selectedPos{-1, -1};
// //     vector<Position> highlights;

// //     while (window.isOpen())
// //     {
// //         Event event;
// //         while (window.pollEvent(event))
// //         {
// //             if (event.type == Event::Closed)
// //                 window.close();

// //             if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
// //             {
// //                 Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
// //                 int col = (mousePos.x - boardStartX) / tileSize;
// //                 int row = (mousePos.y - boardStartY) / tileSize;
// //                 if (row >= 0 && row < 8 && col >= 0 && col < 8)
// //                 {
// //                     Position clicked{row, col};
// //                     Piece *piece = board.getPieceAt(clicked);
// //                     if (piece)
// //                     {
// //                         selectedPos = clicked;
// //                         highlights = board.getHighlights(clicked);
// //                     }
// //                 }
// //             }
// //         }

// //         window.clear(Color::White);

// //         for (int row = 0; row < 8; row++)
// //         {
// //             for (int col = 0; col < 8; col++)
// //             {
// //                 window.draw(boardTiles[row][col]);
// //             }
// //         }

// //         for (const auto &pos : highlights)
// //         {
// //             RectangleShape highlight(Vector2f(tileSize, tileSize));
// //             highlight.setPosition(boardStartX + pos.col * tileSize, boardStartY + pos.row * tileSize);
// //             highlight.setFillColor(Color(0, 255, 0, 100));
// //             window.draw(highlight);
// //         }

// //         for (int row = 0; row < 8; row++)
// //         {
// //             for (int col = 0; col < 8; col++)
// //             {
// //                 if (spritePieces[row][col].getTexture())
// //                 {
// //                     window.draw(spritePieces[row][col]);
// //                 }
// //             }
// //         }

// //         window.display();
// //     }

// //     delete knight;
// //     return 0;
// // }
// // main.cpp
// #include <SFML/Graphics.hpp>
// #include "Board.h"

// using namespace sf;

// const float TILE_SIZE = 70.f;
// const Vector2f BOARD_ORIGIN(290.f, 150.f);

// RectangleShape createTile(int row, int col) {
//     RectangleShape tile(Vector2f(TILE_SIZE, TILE_SIZE));
//     tile.setPosition(BOARD_ORIGIN.x + col * TILE_SIZE, BOARD_ORIGIN.y + row * TILE_SIZE);
//     tile.setFillColor((row + col) % 2 == 0 ? Color(59, 34, 12) : Color(214, 138, 71));
//     return tile;
// }

// Vector2i getBoardCoords(Vector2f mousePos) {
//     int col = (mousePos.x - BOARD_ORIGIN.x) / TILE_SIZE;
//     int row = (mousePos.y - BOARD_ORIGIN.y) / TILE_SIZE;
//     return { row, col };
// }

// int main() {
//     RenderWindow window(VideoMode(1289, 720), "2D Chess Game");
//     window.setFramerateLimit(60);

//     Font font, playerFont;
//     font.loadFromFile("Anton-Regular.ttf");
//     playerFont.loadFromFile("Lora-Italic.ttf");

//     Text title("2D CHESS GAME", font, 44);
//     title.setFillColor(Color::White);
//     title.setOrigin(title.getLocalBounds().width / 2.f, title.getLocalBounds().height / 2.f);
//     title.setPosition(window.getSize().x / 2.f, 50.f);

//     Text player1("Player 1", playerFont, 40);
//     player1.setPosition(BOARD_ORIGIN.x - 250.f, BOARD_ORIGIN.y);
//     Text player2("Player 2", playerFont, 40);
//     player2.setPosition(BOARD_ORIGIN.x + 8 * TILE_SIZE + 50.f, BOARD_ORIGIN.y);

//     RectangleShape header(Vector2f(window.getSize().x, 100.f));
//     header.setFillColor(Color(230, 138, 53));

//     // Load piece textures
//     Texture textures[12];
//     textures[0].loadFromFile("Assets/White Pieces/Pawn.png");
//     textures[1].loadFromFile("Assets/White Pieces/Rook.png");
//     textures[2].loadFromFile("Assets/White Pieces/Knight.png");
//     textures[3].loadFromFile("Assets/White Pieces/Bishop.png");
//     textures[4].loadFromFile("Assets/White Pieces/Queen.png");
//     textures[5].loadFromFile("Assets/White Pieces/King.png");
//     textures[6].loadFromFile("Assets/Black Pieces/Pawn.png");
//     textures[7].loadFromFile("Assets/Black Pieces/Rook.png");
//     textures[8].loadFromFile("Assets/Black Pieces/Knight.png");
//     textures[9].loadFromFile("Assets/Black Pieces/Bishop.png");
//     textures[10].loadFromFile("Assets/Black Pieces/Queen.png");
//     textures[11].loadFromFile("Assets/Black Pieces/King.png");

//     Board board;
//     Position selected{-1, -1};
//     vector<Position> legalMoves;

//     while (window.isOpen()) {
//         Event event;
//         while (window.pollEvent(event)) {
//             if (event.type == Event::Closed)
//                 window.close();

//             if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
//                 Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
//                 Vector2i coords = getBoardCoords(mousePos);
//                 Position clicked{ coords.x, coords.y };

//                 if (!clicked.isValid()) continue;

//                 if (selected.row == -1) {
//                     const Piece* p = board.getPiece(clicked);
//                     if (p && p->isWhite() == board.isWhiteTurn()) {
//                         selected = clicked;
//                         legalMoves = board.getLegalMoves(selected);
//                     }
//                 } else {
//                     if (!board.move(selected, clicked)) {
//                         selected = { -1, -1 };
//                         legalMoves.clear();
//                     } else {
//                         selected = { -1, -1 };
//                         legalMoves.clear();
//                     }
//                 }
//             }
//         }

//         window.clear(Color(128, 66, 8));
//         window.draw(header);
//         window.draw(title);
//         window.draw(player1);
//         window.draw(player2);

//         // Draw board
//         for (int r = 0; r < 8; r++)
//             for (int c = 0; c < 8; c++)
//                 window.draw(createTile(r, c));

//         // Highlight legal moves
//         CircleShape circle(TILE_SIZE / 6.f);
//         circle.setFillColor(Color(0, 255, 0, 150));
//         circle.setOrigin(circle.getRadius(), circle.getRadius());

//         for (auto& m : legalMoves)
//             circle.setPosition(BOARD_ORIGIN.x + m.col * TILE_SIZE + TILE_SIZE / 2,
//                                BOARD_ORIGIN.y + m.row * TILE_SIZE + TILE_SIZE / 2), window.draw(circle);

//         // Draw pieces
//         for (int r = 0; r < 8; r++) {
//             for (int c = 0; c < 8; c++) {
//                 const Piece* piece = board.getPiece({r, c});
//                 if (!piece) continue;

//                 char sym = piece->getSymbol();
//                 int index = 0;
//                 if (sym == 'P') index = 0;
//                 else if (sym == 'R') index = 1;
//                 else if (sym == 'N') index = 2;
//                 else if (sym == 'B') index = 3;
//                 else if (sym == 'Q') index = 4;
//                 else if (sym == 'K') index = 5;
//                 if (!piece->isWhite()) index += 6;

//                 Sprite s(textures[index]);
//                 Vector2u texSize = textures[index].getSize();
//                 s.setOrigin(texSize.x / 2.f, texSize.y / 2.f);
//                 s.setScale(0.8f * TILE_SIZE / texSize.x, 0.8f * TILE_SIZE / texSize.y);
//                 s.setPosition(BOARD_ORIGIN.x + c * TILE_SIZE + TILE_SIZE / 2,
//                               BOARD_ORIGIN.y + r * TILE_SIZE + TILE_SIZE / 2);
//                 window.draw(s);
//             }
//         }

//         window.display();
//     }

//     return 0;
// }


// // #include <SFML/Graphics.hpp>
// // using namespace sf;
// // using namespace std;

// // void newBoard(Sprite pieces[8][8], float tileSize, float boardStartX, float boardStartY)
// // {
// //     // Static textures to keep them alive
// //     static Texture W_PAWN, W_ROOK, W_KNIGHT, W_BISHOP, W_QUEEN, W_KING;
// //     static Texture B_PAWN, B_ROOK, B_KNIGHT, B_BISHOP, B_QUEEN, B_KING;

// //     // Load white pieces
// //     W_PAWN.loadFromFile("Assets/White Pieces/Pawn.png");
// //     W_ROOK.loadFromFile("Assets/White Pieces/Rook.png");
// //     W_KNIGHT.loadFromFile("Assets/White Pieces/Knight.png");
// //     W_BISHOP.loadFromFile("Assets/White Pieces/Bishop.png");
// //     W_QUEEN.loadFromFile("Assets/White Pieces/Queen.png");
// //     W_KING.loadFromFile("Assets/White Pieces/King.png");

// //     // Load black pieces
// //     B_PAWN.loadFromFile("Assets/Black Pieces/Pawn.png");
// //     B_ROOK.loadFromFile("Assets/Black Pieces/Rook.png");
// //     B_KNIGHT.loadFromFile("Assets/Black Pieces/Knight.png");
// //     B_BISHOP.loadFromFile("Assets/Black Pieces/Bishop.png");
// //     B_QUEEN.loadFromFile("Assets/Black Pieces/Queen.png");
// //     B_KING.loadFromFile("Assets/Black Pieces/King.png");

// //     // Clear all pieces
// //     for (int row = 0; row < 8; row++)
// //     {
// //         for (int col = 0; col < 8; col++)
// //         {
// //             pieces[row][col] = Sprite(); // Reset
// //         }
// //     }

// //     // Place pawns
// //     for (int col = 0; col < 8; col++)
// //     {
// //         pieces[6][col].setTexture(W_PAWN);
// //         pieces[1][col].setTexture(B_PAWN);
// //     }

// //     // Place back rows
// //     Texture* whiteBack[8] = { &W_ROOK, &W_KNIGHT, &W_BISHOP, &W_QUEEN, &W_KING, &W_BISHOP, &W_KNIGHT, &W_ROOK };
// //     Texture* blackBack[8] = { &B_ROOK, &B_KNIGHT, &B_BISHOP, &B_QUEEN, &B_KING, &B_BISHOP, &B_KNIGHT, &B_ROOK };

// //     for (int col = 0; col < 8; col++)
// //     {
// //         pieces[7][col].setTexture(*whiteBack[col]);
// //         pieces[0][col].setTexture(*blackBack[col]);
// //     }

// //     // Set position, origin, and scale
// //     for (int row = 0; row < 8; row++)
// //     {
// //         for (int col = 0; col < 8; col++)
// //         {
// //             if (pieces[row][col].getTexture())
// //             {
// //                 Vector2u size = pieces[row][col].getTexture()->getSize();

// //                 // Scale down to fit nicely within the tile
// //                 float scaleFactor = 0.8f;
// //                 pieces[row][col].setScale(
// //                     scaleFactor * tileSize / size.x,
// //                     scaleFactor * tileSize / size.y
// //                 );

// //                 // Set origin to center of sprite
// //                 pieces[row][col].setOrigin(size.x / 2.f, size.y / 2.f);

// //                 // Position to center of tile
// //                 pieces[row][col].setPosition(
// //                     boardStartX + col * tileSize + tileSize / 2.f,
// //                     boardStartY + row * tileSize + tileSize / 2.f
// //                 );
// //             }
// //         }
// //     }
// // }
