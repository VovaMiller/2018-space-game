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

	// ������������� ������ ���������� ����������.
	// ���������� ��� ������������� � ��� ���������� �����.
	void set_last_update(long long ms_cur);
    // �������� ��� ������� �����.
    const std::string& get_active_map() const;
    // �������� ������-������.
    GameObject__Actor* get_actor() const;
	// �������� ����� ����� � ����������� �� "spawn.json".
	// ��������� ���� ���������� �� ���������.
	void NewMap();
	// �������� ����� �� ���������� ����.
	// ��������� ���� ���������� �� �����������.
	void LoadMap(const std::string& file_path);
	// ��������� ����� � ������ active_map_.
	void SaveMap();
	// ��������� ����.
	void Halt();
	// ������������ ���������� �����.
	void Update(long long ms_cur);
	// ��������� ������������� ������������.
	void Draw(Window* window) const;
	// ��������� ������������� �������� ������.
	void ProcessUserAction(UserActionInfo uai);
    // ���������, ��������� �� ������ �� ������ ������.
	bool IsOnScreen(GameObject* game_object) const;
    // ��������� ������� ������ (� ����������� �� ��������� ��).
    // ���������� ������������� � Update.
	void UpdateScreenPosition();

private:
    // ������ ���� �� ����� � �������� ������.
	std::string active_map_;
    // ����� ���������� ����������.
	long long last_update_;
	Point2DInt screen_position_;
	Point2DInt actor_spawn_position_;
	GameObject__Actor* actor_;
	ObjectsStorage objects_;
	MapGenerator* map_generator_;
	
	// �������������� actor_ �� "spawn_actor.json".
	void SpawnActor();
	// ������� actor_ � �� �� objects_.
	void ClearObjects();
	void DrawObject(Window* window, GameObject* game_object) const;
	// ���������� ������ ������, ���������� ����� ������������ (x, y).
	// ������ Actor ������������.
	// ���� ����� �������� ���, �� nullptr.
	GameObject* GetObject(int x, int y);
	GameObject* GetObject(const Point2DInt& point);
	PressedButtons pressed_buttons_;
};
