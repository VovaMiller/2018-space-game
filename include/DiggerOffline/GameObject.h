#pragma once
#include <string>
#include <fstream>
#include <DiggerOffline/GameObjectEvent.h>
#include <DiggerOffline/Point2DInt.h>
#include <DiggerOffline/Point2D.h>
#include <DiggerOffline/BinaryFile.h>
#include <json.hpp>

class GameObjectEventInfo;

enum GameObjectEventType {
	kObjEventDeath, kObjEventCondition
};

enum GameObjectState {
	kObjStateOnline,
	kObjStateOffline
};

enum GameObjectType {
	kObjTypeThrough,
	kObjTypeImpenetrable
};

class GameObject {
	friend class GameObjectFactory;

public:
	GameObject();
	virtual ~GameObject() {}

	virtual GameObject* Clone() const = 0;
	void set_pos(const Point2DInt& pos);
	void set_pos(const Point2D& pos);
	Point2DInt get_pos() const;
	const Point2D& get_posd() const;
	const Point2DInt& get_size() const;
	const std::string& get_section() const;
	const std::string& get_texture() const;
	GameObjectType get_type() const;
	GameObjectState get_state() const;
	double Distance(int x, int y) const;
	double Distance(const Point2DInt& point) const;
	double Distance(GameObject* other) const;
	void Remove();
	bool IsToBeRemoved() const;
	virtual bool IsActor() const;
	virtual void Update(long long ms_delta, long long ms_cur) {}
	virtual void Event(GameObjectEventType event_type, GameObjectEventInfo* event_info);
	virtual void Serialize(std::ofstream& file) const;

protected:
	Point2D pos_;
	Point2DInt size_;
	std::string texture_;
	GameObjectType type_;
	GameObjectState state_;

	virtual void Deserialize(std::ifstream& file);
	virtual bool SetStaticProperties(const std::string& section, const nlohmann::json& json);
	virtual bool SetDynamicProperties(const std::string& obj_id, const nlohmann::json& json);

private:
	std::string section_;
	bool to_be_removed_;
};
