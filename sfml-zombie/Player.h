#pragma once
#include "GameObject.h"
#include "HitBox.h"
class SceneGame;
class Bullet;

class Player : public GameObject
{

protected:
	sf::Sprite body;
	std::string texId = "graphics/player.png";

	sf::Vector2f direction;//이동
	sf::Vector2f look;//보는 방향

	float speed = 500.f;
	SceneGame* sceneGame = nullptr; //sceneGame에 진행중인 씬을 할당하기전 초기화 

	HitBox hitBox;

	std::list<Bullet*> bulletList;
	std::list<Bullet*> bulletPool;

	float shootInterval = 0.1f;
	float shootTimer = 0.1f;

	int hp = 0;
	int maxHp = 100;

	

public:
	bool IsAlive() const{ return hp > 0; }

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

	virtual sf::FloatRect GetLocalBounds()const override
	{
		return body.getLocalBounds();
	}

	virtual sf::FloatRect GetGlobalBounds()const override
	{
		return body.getGlobalBounds();
	}

	const HitBox& GetHitBox() const
	{
		return hitBox;
	}



	void Shoot();

	void OnDamge(int damge);
	
};

