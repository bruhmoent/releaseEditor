#include "directives.hpp"

#ifndef CAMERA_HPP
#define CAMERA_HPP

class 
Camera
{
public:
    sf::Vector2f m_cameraOffset;
    float m_zoomLevel;
    float m_minZoom;
    float m_maxZoom;

    Camera() : m_zoomLevel(1.0f), m_minZoom(0.5f), m_maxZoom(2.0f) {}

    //Follow a target
    void
    viewFollow(const sf::Vector2f& objectPos, sf::RenderWindow& window, float speed);

    //Zoom-in the camera
    void
    zoomIn(sf::RenderWindow& window, float zoomFactor);

    //Zoom-out the camera
    void
    zoomOut(sf::RenderWindow& window, float zoomFactor);

private:
    //Update and normalize camera
    void
        updateView(sf::RenderWindow& window);
};

#endif