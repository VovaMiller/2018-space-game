#pragma once
#include <DiggerOffline/GameObjectFactory.h>
#include <DiggerOffline/MapGenerator.h>
#include <DiggerOffline/Tools.h>
#include <set>

typedef std::list<GameObject*> ObjectsStorage;
typedef std::set<UserAction> PressedButtons;

class Gameplay {
	friend class GameObjectMotile;

public:
	Gameplay();
	~Gameplay();

	// Устанавливает момент последнего обновления.
	// Необходимо для инициализации и для реализации паузы.
	void set_last_update(long long ms_cur);
    // Получить имя текущей карты.
    const std::string& get_active_map() const;
    // Получить объект-игрока.
    GameObject__Actor* get_actor() const;
	// Создание новой карты с настройками из "spawn.json".
	// Состояние игры замещается на стартовое.
	void NewMap();
	// Загрузка карты по указанному пути.
	// Состояние игры замещается на загруженное.
	void LoadMap(const std::string& file_path);
	// Сохраняет карту с именем active_map_.
	void SaveMap();
	// Прерывает игру.
	void Halt();
	// Периодически вызываемый метод.
	void Update(long long ms_cur);
	// Отрисовка внутриигровой составляющей.
	void Draw(Window* window) const;
	// Обработка внутриигровых действий игрока.
	void ProcessUserAction(UserActionInfo uai);
    // Проверяет, находится ли объект на экране игрока.
	bool IsOnScreen(GameObject* game_object) const;
    // Обновляет позицию экрана (в зависимости от положения ГГ).
    // Вызывается автоматически в Update.
	void UpdateScreenPosition();

private:
    // Полный путь до файла с активной картой.
	std::string active_map_;
    // Время последнего обновления.
	long long last_update_;
	Point2DInt screen_position_;
	Point2DInt actor_spawn_position_;
	GameObject__Actor* actor_;
	ObjectsStorage objects_;
	MapGenerator* map_generator_;
	
	// Инициализирует actor_ по "spawn_actor.json".
	void SpawnActor();
	// Удаляет actor_ и всё из objects_.
	void ClearObjects();
	void DrawObject(Window* window, GameObject* game_object) const;
	// Возвращает первый объект, занимающий точку пространства (x, y).
	// Объект Actor игнорируется.
	// Если таких объектов нет, то nullptr.
	GameObject* GetObject(int x, int y);
	GameObject* GetObject(const Point2DInt& point);
	PressedButtons pressed_buttons_;
};
