#include "camera.hpp"

void
Camera::viewFollow(const sf::Vector2f& objectPos, sf::RenderWindow& window, float speed)
{
	sf::View view = window.getView();
	sf::Vector2f currentPosition = view.getCenter();
	sf::Vector2f targetPosition = objectPos;

	sf::Vector2f newPosition = currentPosition + (targetPosition - currentPosition) * speed;
	view.setCenter(newPosition);
	window.setView(view);

	m_cameraOffset = newPosition - window.getView().getCenter();
}

void
Camera::zoomIn(sf::RenderWindow& window, float zoomFactor)
{
	float newZoomLevel = m_zoomLevel * zoomFactor;
	if (newZoomLevel <= m_maxZoom)
	{
		sf::Vector2f viewCenter = window.getView().getCenter();
		sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		m_zoomLevel = newZoomLevel;

		sf::Vector2f newMousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		sf::Vector2f delta = newMousePos - mousePos;

		m_cameraOffset -= delta;
		updateView(window);
	}
}

void
Camera::zoomOut(sf::RenderWindow& window, float zoomFactor)
{
	float newZoomLevel = m_zoomLevel / zoomFactor;
	if (newZoomLevel >= m_minZoom)
	{
		sf::Vector2f viewCenter = window.getView().getCenter();
		sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		m_zoomLevel = newZoomLevel;

		sf::Vector2f newMousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		sf::Vector2f delta = newMousePos - mousePos;

		m_cameraOffset -= delta;
		updateView(window);
	}
}

void
Camera::updateView(sf::RenderWindow& window)
{
	if (m_zoomLevel > m_maxZoom)
	{
		m_zoomLevel = m_maxZoom;
	}
	else if (m_zoomLevel < m_minZoom)
	{
		m_zoomLevel = m_minZoom;
	}

	sf::View view = window.getView();
	view.setCenter(view.getCenter() + m_cameraOffset);
	view.setSize(window.getDefaultView().getSize() / m_zoomLevel);
	window.setView(view);
}