#pragma once
#include <DiggerOffline/GameObject__Actor.h>
#include <DiggerOffline/GameObject__Block.h>
#include <list>

typedef std::list<GameObject__Block*> Prototypes;

class MapGenerator {
public:
	MapGenerator(int next_layer);
	~MapGenerator();

	// ����� ����� �������������� � �������� [-kMapRadiusX, kMapRadiusX].
	static const int kMapRadiusX;
	// ���� ���������� �� �� �� ���� �� ��������� kGeneratorRadiusY, �� ���� ������ ���� ������������.
	static const int kGeneratorRadiusY;

	int get_next_layer() const;
	void Tweak(GameObject__Actor* actor, std::list<GameObject*>& objects);

private:
	int next_layer_;
	Prototypes prototypes_;

	// ������ ���� ���������� ��������� � ������������ � �� ����������� ���������.
	// ���������� nullptr ��� ������.
	GameObject* GetRandomBlock() const;
};
