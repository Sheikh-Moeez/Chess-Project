#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <iostream>

class Button
{
public:
    RectangleShape shape;
    Text label;

    Button(const Vector2f &size, const Vector2f &position, const string &text, Font &font)
    {
        shape.setSize(size);
        shape.setPosition(position);
        shape.setFillColor(BUTTON_COLOR);

        label.setFont(font);
        label.setString(text);
        label.setCharacterSize(28);
        label.setFillColor(Color::White);

        FloatRect textBounds = label.getLocalBounds();
        label.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
        label.setPosition(position.x + size.x / 2.f, position.y + size.y / 2.f);
    }

    void draw(RenderWindow &window)
    {
        window.draw(shape);
        window.draw(label);
    }

    bool isHovered(Vector2f mousePos)
    {
        return shape.getGlobalBounds().contains(mousePos);
    }

    bool isClicked(Vector2f mousePos)
    {
        return isHovered(mousePos);
    }

    void update(Vector2f mousePos)
    {
        shape.setFillColor(isHovered(mousePos) ? BUTTON_HOVER_COLOR : BUTTON_COLOR);
    }
};