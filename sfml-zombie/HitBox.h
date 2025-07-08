#pragma once
class HitBox
{
public:
	sf::RectangleShape rect;
	HitBox();
	

	void UpdateTransform(const sf::Transformable& tr, const sf::FloatRect& localBounds);//사이즈정의 하려고 
	void Draw(sf::RenderWindow& window);

};

