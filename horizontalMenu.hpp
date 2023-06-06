#include "directives.hpp"

#ifndef HORIZONTAL_MENU_HPP
#define HORIZONTAL_MENU_HPP

template <typename T>
class HorizontalMenu {

public:
    using FunctionType = std::function<void()>;
    HorizontalMenu(float width, float height, float border, sf::Color bgColor, sf::Color textColor);
    int getSelectedIndex() const;
    void addTextItem(const T& item);
    void staticDisplay(sf::RenderWindow& window);
    void setPosition(float x, float y);
    void addButton(const std::string& label, const FunctionType& function);
    void addButton(const std::string& label, const std::string& texturePath, const FunctionType& function);
    void handleButtons(sf::RenderWindow& window);
    void hide(sf::RenderWindow& window);
    void handleStaticHover(sf::RenderWindow& window);
    bool itemsClicked(const sf::RenderWindow& window);
    bool itemClicked(const sf::RenderWindow& window, int index);
    bool isMouseInside(sf::RenderWindow& window) const;
    sf::Vector2f getPosition() const;
    sf::RectangleShape getBackground() const;
    std::vector<FunctionType> getFunctions() const;

private:
    float m_width;
    float m_height;
    std::vector<sf::Text> m_labels;
    std::vector<sf::Sprite> m_icons;
    std::vector<FunctionType> m_functions;
    float m_border;
    sf::Color m_bgColor;
    sf::Color m_textColor;
    sf::Vector2f m_iconSize;
    sf::Font m_font;
    sf::Text m_text;
    std::vector<sf::Text> m_items;
    sf::RectangleShape m_background;
    sf::RectangleShape m_hoverRect;
    sf::Vector2f m_position;
    int m_selectedIndex;
};

//Initiate horizontal menu
template <typename T>
HorizontalMenu<T>::HorizontalMenu(float width, float height, float border, sf::Color bgColor, sf::Color textColor)
    : m_width(width), m_height(height), m_border(border), m_bgColor(bgColor), m_textColor(textColor)
{
    m_font.loadFromFile("assets/arial.ttf");
    m_text.setFont(m_font);
    m_text.setCharacterSize(16);
    m_text.setFillColor(m_textColor);

    m_background.setSize(sf::Vector2f(m_width, m_height));
    m_background.setFillColor(m_bgColor);
    m_background.setPosition(sf::Vector2f(0.f, 0.f));
}

//Add item to the menu
template <typename T>
void HorizontalMenu<T>::addTextItem(const T& item)
{
    sf::Text text;
    text.setFont(m_font);
    text.setCharacterSize(16);
    text.setFillColor(m_textColor);
    text.setString(item);
    m_items.push_back(text);
}

//Anchor menu
template <typename T>
void HorizontalMenu<T>::staticDisplay(sf::RenderWindow& window)
{
    sf::View originalView = window.getView();

    sf::View menuView = window.getDefaultView();
    menuView.setViewport(originalView.getViewport());

    window.setView(menuView);

    float totalWidth = 2 * m_border;
    for (const auto& item : m_items) {
        totalWidth += item.getLocalBounds().width + m_border;
    }
    for (const auto& icon : m_icons) {
        totalWidth += icon.getLocalBounds().width + m_border;
    }

    m_background.setFillColor(m_bgColor);
    m_background.setPosition(m_position);
    m_background.setSize(sf::Vector2f(totalWidth, m_height));
    window.draw(m_background);

    float startX = m_border + m_position.x;
    float startY = m_border + m_position.y;

    for (int i = 0; i < m_items.size(); i++) {
        auto& item = m_items[i];
        item.setPosition(startX, startY);

        if (i == m_selectedIndex) {
            float hoverXOffset = 0.f;
            float hoverRectStartX = startX - m_border / 2 - hoverXOffset;
            float hoverWidth = std::min(m_width - 2 * m_border, item.getLocalBounds().width + m_border);
            float hoverHeight = item.getLocalBounds().height + m_border;
            float hoverYOffset = (m_height - hoverHeight) / 2;
            m_hoverRect.setSize(sf::Vector2f(hoverWidth, hoverHeight));
            m_hoverRect.setPosition(sf::Vector2f(hoverRectStartX, m_position.y + m_border + hoverYOffset - 15.f));
            m_hoverRect.setFillColor(sf::Color(211, 211, 211));
            window.draw(m_hoverRect);
        }

        window.draw(item);
        startX += item.getLocalBounds().width + m_border;
    }

    for (int i = 0; i < m_icons.size(); i++) {
        auto& icon = m_icons[i];
        icon.setPosition(startX, startY);
        window.draw(icon);
        startX += icon.getLocalBounds().width + m_border;
    }

    window.setView(originalView);
}

//Handle hover not altered by the camera
template <typename T>
void HorizontalMenu<T>::handleStaticHover(sf::RenderWindow& window)
{
    sf::View originalView = window.getView();

    sf::View menuView = window.getDefaultView();
    menuView.setViewport(originalView.getViewport());

    window.setView(menuView);

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosView = window.mapPixelToCoords(mousePos);

    int oldIndex = m_selectedIndex;
    m_selectedIndex = -1;

    for (int i = 0; i < m_items.size(); i++) {
        sf::FloatRect itemBounds = m_items[i].getGlobalBounds();
        itemBounds.left += m_position.x;
        itemBounds.top += m_position.y;

        if (itemBounds.contains(mousePosView)) {
            m_selectedIndex = i;
            break;
        }
    }

    window.setView(originalView);
}

//Get functions
template <typename T>
std::vector<typename HorizontalMenu<T>::FunctionType> HorizontalMenu<T>::getFunctions() const {
    return m_functions;
}

//Sets position of given menu
template <typename T>
void HorizontalMenu<T>::setPosition(float x, float y) {
    m_position.x = x;
    m_position.y = y;

    float offsetX = m_position.x;
    float offsetY = m_position.y;

    for (auto& icon : m_icons) {
        icon.setPosition(offsetX, offsetY);
        offsetX += icon.getLocalBounds().width + m_border;
    }

    offsetX = m_position.x;
    offsetY = m_position.y;

    for (auto& label : m_labels) {
        sf::FloatRect bounds = label.getLocalBounds();
        label.setPosition(offsetX + (m_iconSize.x - bounds.width) / 2.f, offsetY + (m_iconSize.y - bounds.height) / 2.f);
        offsetX += m_iconSize.x + m_border;
    }
}

//Hide the menu from visible view
template <typename T>
void HorizontalMenu<T>::hide(sf::RenderWindow& window)
{
    float startX = -10000.f;
    float startY = -10000.f;
    for (auto& item : m_items) {
        item.setPosition(startX, startY);
    }

    m_background.setFillColor(m_bgColor);
    m_background.setPosition(m_position);
    m_background.setSize(sf::Vector2f(0.f, m_height));
    window.draw(m_background);
}

//Get selected index
template <typename T>
int HorizontalMenu<T>::getSelectedIndex() const
{
    return m_selectedIndex;
}

//Get background
template <typename T>
sf::RectangleShape HorizontalMenu<T>::getBackground() const
{
    return m_background;
}

//Get position
template <typename T>
sf::Vector2f HorizontalMenu<T>::getPosition() const
{
    return m_position;
}

//Affects all items on click
template <typename T>
bool HorizontalMenu<T>::itemsClicked(const sf::RenderWindow& window)
{
    bool clicked = false;
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosView = window.mapPixelToCoords(mousePos);

    for (int i = 0; i < m_items.size(); i++) {
        sf::FloatRect itemBounds = m_items[i].getGlobalBounds();
        itemBounds.left += m_position.x;
        itemBounds.top += m_position.y;

        if (itemBounds.contains(mousePosView)) {
            m_functions[i]();
            clicked = true;
            break;
        }
    }

    return clicked;
}

//Affects an item on a select index
template <typename T>
bool HorizontalMenu<T>::itemClicked(const sf::RenderWindow& window, int index)
{
    static bool wasMousePressed = false;

    if (index < 0 || index >= m_items.size()) {
        return false;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (!wasMousePressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosView = window.mapPixelToCoords(mousePos);

            sf::FloatRect itemBounds = m_items[index].getGlobalBounds();
            itemBounds.left += m_position.x;
            itemBounds.top += m_position.y;

            if (itemBounds.contains(mousePosView)) {
                wasMousePressed = true;
                m_functions[index]();
                return true;
            }
        }
    }
    else {
        wasMousePressed = false;
    }

    return false;
}

//Add label button
template <typename T>
void HorizontalMenu<T>::addButton(const std::string& label, const FunctionType& function)
{
    sf::Text text;
    text.setFont(m_font);
    text.setCharacterSize(16);
    text.setFillColor(m_textColor);
    text.setString(label);
    m_labels.push_back(text);
    m_icons.emplace_back();
    m_functions.push_back(function);
}

//Add a icon based button
template <typename T>
void HorizontalMenu<T>::addButton(const std::string& label, const std::string& texturePath, const FunctionType& function)
{
    sf::Texture* texture = new sf::Texture;
    if (!texture->loadFromFile(texturePath)) {
        delete texture;
        std::cout << "Failed to load texture: " << texturePath << std::endl;
        return;
    }

    sf::Sprite sprite;
    sprite.setTexture(*texture);
    sprite.setScale(32.0f / sprite.getLocalBounds().width, 32.0f / sprite.getLocalBounds().height);
    m_icons.push_back(sprite);

    sf::Text text;
    text.setFont(m_font);
    text.setCharacterSize(16);
    text.setFillColor(m_textColor);
    text.setString(label);
    m_labels.push_back(text);
    m_functions.push_back(function);

    float totalWidth = 0.0f;
    for (size_t i = 0; i < m_icons.size(); ++i) {
        totalWidth += m_icons[i].getLocalBounds().width;
        totalWidth += m_labels[i].getLocalBounds().width;
        totalWidth += m_border;
    }

    float startX = m_position.x + m_border;
    startX += (m_width - totalWidth) / 2.0f;

    sf::Vector2f position(startX, m_border + m_position.y);
    for (size_t i = 0; i < m_icons.size(); ++i) {
        m_icons[i].setPosition(position);
        position.x += m_icons[i].getLocalBounds().width + m_border;

        m_labels[i].setPosition(position);
        position.x += m_labels[i].getLocalBounds().width + m_border;
    }
}

//Check if the mouse is inside of the menu
template <typename T>
bool HorizontalMenu<T>::isMouseInside(sf::RenderWindow& window) const
{
    sf::View originalView = window.getView();

    sf::View menuView = window.getDefaultView();
    menuView.setViewport(originalView.getViewport());

    window.setView(menuView);

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosView = window.mapPixelToCoords(mousePos);

    sf::FloatRect backgroundBounds = m_background.getGlobalBounds();

    bool isInside = backgroundBounds.contains(mousePosView);

    window.setView(originalView);

    return isInside;
}

//Handle clicking on buttons
template <typename T>
void HorizontalMenu<T>::handleButtons(sf::RenderWindow& window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::View originalView = window.getView();

        sf::View menuView = window.getDefaultView();
        menuView.setViewport(originalView.getViewport());

        window.setView(menuView);

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosView = window.mapPixelToCoords(mousePos);

        int oldIndex = m_selectedIndex;
        m_selectedIndex = -1;

        for (int i = 0; i < m_icons.size(); i++)
        {
            sf::FloatRect iconBounds = m_icons[i].getGlobalBounds();

            if (iconBounds.contains(mousePosView))
            {
                m_selectedIndex = i;
                break;
            }
        }

        window.setView(originalView);

        if (m_selectedIndex != oldIndex)
        {
            m_functions[m_selectedIndex]();
        }

    }
}

#endif