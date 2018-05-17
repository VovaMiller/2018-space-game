#pragma once
#include <DiggerOffline/GameObject.h>
#include <DiggerOffline/Point2D.h>
#include <list>

struct Force {
	Point2D force;
	long long deadline;
};

typedef std::list<Force> Forces;

class GameObjectMotile : virtual public GameObject {
	friend class GameObjectFactory;

public:
	GameObjectMotile();
	virtual ~GameObjectMotile() {}

	static const double kAccelGravi;
	static const int kPixelsPerMeter;
	static const int kUpdateRadius;
	const double kDefaultVelocity = 2.5;
	const double kDefaultForcePull = 1000;
    // Сила, всегда действующая против направления скорости.
    // Для объектов с "weightless_ == false" сила действует только на горизонтальную компоненту скорости.
	const double kDefaultForceStop = 500;

	double get_mass() const;
	bool is_weightless() const;
	const Point2D& get_velocity() const;
	void AddForce(Force force);
	void Jump();
	void SetMovingDirection(const Point2DInt& dir);
	virtual void Update(long long ms_delta, long long ms_cur);
	virtual void Event(GameObjectEventType event_type, GameObjectEventInfo* event_info);
	virtual void Serialize(std::ofstream& file) const;

protected:
	virtual void Deserialize(std::ifstream& file);
	virtual bool SetStaticProperties(const std::string& section, const nlohmann::json& json);
	virtual bool SetDynamicProperties(const std::string& obj_id, const nlohmann::json& json);
	virtual void set_velocity(const Point2D& velocity);

private:
	double mass_;
	bool weightless_;
	Point2D velocity_;
	Point2DInt moving_direction_;
	Forces forces_;
};
