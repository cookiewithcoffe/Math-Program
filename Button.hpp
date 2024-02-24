#pragma once

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include<SFML/Graphics.hpp>
#include<functional>
#include<iostream>

class Button {
public:
    Button(const std::string text, unsigned int fontSize, float x, float y, std::function<void()> callback)
        : callback(callback) {

        font.loadFromFile("./Resources/font.ttf"); // Önceden yüklenmiþ bir font dosyasý kullanabilirsiniz.

        shape.setSize(sf::Vector2f(120, 40)); // Düðme boyutu
        shape.setPosition(x, y); // Düðme konumu
        shape.setFillColor(sf::Color::Cyan); // Düðme rengi

        label.setFont(font);
        label.setString(text);
        label.setCharacterSize(fontSize);
        label.setFillColor(sf::Color::Black);
        label.setPosition(x + 20, y + 10);

        isMouseOver = false;
    }

    void update(sf::RenderWindow& window) {
        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
        isMouseOver = shape.getGlobalBounds().contains(mousePos);

        if (isMouseOver && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            callback();
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
        window.draw(label);
    }

    void setTexture(sf::Texture texture) {
        shape.setTexture(&texture);
    }

private:
    sf::RectangleShape shape;
    sf::Text label;
    sf::Font font;
    bool isMouseOver;
    std::function<void()> callback;
};

#endif