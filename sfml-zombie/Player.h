#pragma once
#include "GameObject.h"

class SceneGame;

class Player : public GameObject
{

protected:
	sf::Sprite body;
	std::string texId = "graphics/player.png";

	sf::Vector2f direction;//이동
	sf::Vector2f look;//보는 방향

	float speed = 500.f;
	SceneGame* sceneGame = nullptr; //sceneGame에 진행중인 씬을 할당하기전 초기화 


public:
	Player(const std::string& name);
	~Player() = default;


	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s)override;
	void SetOrigin(const sf::Vector2f& o)override;
	void SetOrigin(Origins preset)override;



	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

