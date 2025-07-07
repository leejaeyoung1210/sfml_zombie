#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(const std::string& name)
	: GameObject(name)
{
}

void TileMap::Set(const sf::Vector2i& count, const sf::Vector2f& size)
{
	cellCount = count;
	cellSize = size;

	va.clear();	
	va.setPrimitiveType(sf::Quads);
	va.resize(count.x * count.y * 4);

	sf::Vector2f posOffset[4] =
	{
		{0.f,0.f},//1 사각형은 순서지키자.일그러진다.
		{size.x,0.f},//2
		{size.x,size.y},//3
		{0.f,size.y},//4
	};

	sf::Vector2f texCoords[4] =//텍스쳐좌표
	{
		{0.f,0.f},
		{50.f,0.f},
		{50.f,50.f},
		{0.f,50.f},
	};

	for (int i = 0; i < count.y; ++i)//타일깔기
	{
		for (int j = 0; j < count.x; ++j)
		{
			int texIndex = Utils::RandomRange(0,3);
			if (i == 0 || i == count.y - 1 || j == 0 || j == count.x-1)//외각검사(3)타일로 깔려고
			{
				texIndex = 3;
			}

			int quadIndex = i * count.x + j;
			sf::Vector2f quadPos(j*size.x,i*size.y);//(열,행)

			for (int k = 0; k < 4; ++k)//꼭지점 4개 순회용
			{
				int vertexIndex = quadIndex * 4 + k;
				va[vertexIndex].position = quadPos + posOffset[k];//첫번째 사각형의 위치 
				va[vertexIndex].texCoords = texCoords[k]; //텍스쳐 좌표를 넘겨줌 
				va[vertexIndex].texCoords.y += texIndex * 50.f;//다음타일로 넘어가기위함
			}
		}
	}

}

void TileMap::UpdateTransform()
{
	transform = sf::Transform::Identity;
	transform.translate(position);
	transform.rotate(rotation);
	transform.scale(scale);
	transform.translate(-origin);
}

void TileMap::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	UpdateTransform();
}

void TileMap::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	UpdateTransform();
}

void TileMap::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	UpdateTransform();
}

void TileMap::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	UpdateTransform();
	
}

void TileMap::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		sf::FloatRect rect;
		rect.width = cellCount.x * cellSize.x;
		rect.height = cellCount.y * cellSize.y;

		origin.x = rect.width * ((int)preset % 3) * 0.5f;
		origin.y = rect.height * ((int)preset / 3) * 0.5f;
	}
	UpdateTransform();
}

void TileMap::Init()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = 0;

	Set({ 50,50 }, { 50.f,50.f }); //250개 만들겟다.
}

void TileMap::Release()
{
}

void TileMap::Reset()
{
	texture = &TEXTURE_MGR.Get(spriteSheetId);
	
	SetOrigin(Origins::MC);
	SetScale({ 1.f,1.f });//크기 배수
	//SetRotation(45.f);// 맵 회전 
	SetPosition({ 0.f,0.f });
}

void TileMap::Update(float dt)
{
}

void TileMap::Draw(sf::RenderWindow& window)
{//텍스쳐 따로 넘겨야함 별개로 매개변수 
	sf::RenderStates state;
	state.texture = texture;
	state.transform = transform;
	window.draw(va, state);


}