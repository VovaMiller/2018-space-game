#pragma once
#include <DiggerOffline/GameObject__Actor.h>
#include <DiggerOffline/GameObject__Block.h>
#include <list>

typedef std::list<GameObject__Block*> Prototypes;

class MapGenerator {
public:
	MapGenerator(int next_layer);
	~MapGenerator();

	// Карта будет генерироваться в пределах [-kMapRadiusX, kMapRadiusX].
	static const int kMapRadiusX;
	// Если расстояние от ГГ до слоя не превышает kGeneratorRadiusY, то слой должен быть сгенерирован.
	static const int kGeneratorRadiusY;

	int get_next_layer() const;
	void Tweak(GameObject__Actor* actor, std::list<GameObject*>& objects);

private:
	int next_layer_;
	Prototypes prototypes_;

	// Создаёт клон случайного прототипа в соответствии с их настройками генерации.
	// Возвращает nullptr при ошибке.
	GameObject* GetRandomBlock() const;
};
