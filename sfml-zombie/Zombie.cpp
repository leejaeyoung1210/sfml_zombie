#include "stdafx.h"
#include "Zombie.h"
#include "Player.h"
#include "HitBox.h"

Zombie::Zombie(const std::string& name)
	: GameObject(name)
{
}

void Zombie::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Zombie::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Zombie::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Zombie::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Zombie::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Zombie::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	SetType(type);
}

void Zombie::Release()
{
}

void Zombie::Reset()
{
	player = (Player*)SCENE_MGR.GetCurrentScene()->FindGameObject("Player");

	body.setTexture(TEXTURE_MGR.Get(texId), true);
	SetOrigin(Origins::MC);
	SetPosition({ 0.f,0.f });
	SetRotation(0.f);
	SetScale({ 1.f, 1.f });

	hp = maxHp;
	attackTimer = 0.f;

}

void Zombie::Update(float dt)
{
	direction = Utils::GetNormal(player->GetPosition() - GetPosition()); //좀비에서 플레이어에게로 향하는 방향
	SetRotation(Utils::Angle(direction));
	SetPosition(GetPosition() + direction * speed * dt);

	hitBox.UpdateTransform(body, GetLocalBounds());

	attackTimer += dt;
	if (attackTimer > attackIntervale)
	{
		
		if (Utils::CheckCollision(hitBox.rect, player->GetHitBox().rect))
		{
			player->OnDamge(damage);
			attackTimer = 0.f;
		}
	}

}
void Zombie::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}

void Zombie::SetType(Types type)
{
	this->type = type;
	switch (this->type)
	{
	case Types::Bloater:
		texId = "graphics/bloater.png";
		maxHp = 100;
		speed = 50;
		damage = 30;
		attackIntervale = 1.f;
		break;
	case Types::Chaser:
		texId = "graphics/chaser.png";
		maxHp = 200;
		speed = 30;
		damage = 70;
		attackIntervale = 1.f;
		break;
	case Types::Crawler:
		texId = "graphics/crawler.png";
		maxHp = 50;
		speed = 80;
		damage = 20;
		attackIntervale = 1.f;
		break;
	}
}

void Zombie::OnDamge(int damge)
{
	hp = Utils::Clamp(hp - damage, 0, maxHp);
	if (hp == 0)
	{
		SetActive(false);
	}



}







