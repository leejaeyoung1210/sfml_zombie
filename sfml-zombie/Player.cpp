#include "stdafx.h"
#include "Player.h"
#include "SceneGame.h"

Player::Player(const std::string& name)
	:GameObject(name)
{
}

void Player::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}
void Player::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}
void Player::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}
void Player::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}
void Player::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, preset);
	}
}





void Player::Init() //초기값 
{
	sortingLayer = SortingLayers::Foreground; // 배경할당.
	sortingOrder = 0;
	SetOrigin(Origins::MC);

}

void Player::Release()
{
}

void Player::Reset()
{
	if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Game)
	{
		sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene(); //실행중인 씬을 가져오는 함수임. 
	}
	else
	{
		sceneGame = nullptr;
	}

	body.setTexture(TEXTURE_MGR.Get(texId), true);
	SetOrigin(Origins::MC);
	SetPosition({ 0.f,0.f });
	SetRotation(0.f);

	direction = { 0.f,0.f };
	look = { 1.0f,0.f };
}

void Player::Update(float dt)
{
	//이동위치 잡아주는거같은데 
	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);

	if (Utils::Magnitude(direction) > 1.f)
	{
		Utils::Normalize(direction);
	}
	SetPosition(position + direction * speed * dt);

	//마우스값 받아다가 보는방향 변경하는부분 머리돌아가는부분//마우스는 스크린좌푝{
	//후에 마우스를 월드좌표계를 쓸거임
	sf::Vector2i mousePos = InputMgr::GetMousePosition();
	sf::Vector2f mouseWorldPos = sceneGame->ScreenToWorld(mousePos);



	look = Utils::GetNormal(mouseWorldPos - GetPosition());
	SetRotation(Utils::Angle(look));


}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
