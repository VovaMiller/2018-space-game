#include <DiggerOffline/Box2D.h>
#include <DiggerOffline/GameObjectMotile.h>
#include <DiggerOffline/MapGenerator.h>
#include <DiggerOffline/Game.h>
#include <DiggerOffline/utils_double.h>

GameObjectMotile::GameObjectMotile() : mass_(50.0), weightless_(false) {}

const double GameObjectMotile::kAccelGravi = 9.8;
const int GameObjectMotile::kPixelsPerMeter = 64;
const int GameObjectMotile::kUpdateRadius = 768;

double GameObjectMotile::get_mass() const {
	return mass_;
}

bool GameObjectMotile::is_weightless() const {
	return weightless_;
}

const Point2D& GameObjectMotile::get_velocity() const {
	return velocity_;
}

void GameObjectMotile::AddForce(Force force) {
	forces_.push_back(force);
}

void GameObjectMotile::Jump() {
	if ((!weightless_) && is_zero(velocity_.y)) {
		Point2D new_velocity = velocity_;
		const double h = 0.75;  // метров
		// v = sqrt(2gh)
		new_velocity.y = -sqrt(2 * kAccelGravi * h);
		set_velocity(new_velocity);
	}
}

void GameObjectMotile::SetMovingDirection(const Point2DInt& dir) {
	moving_direction_ = dir;
}

void GameObjectMotile::Update(long long ms_delta, long long ms_cur) {
	Gameplay* gameplay = Game::Instance()->get_gameplay();
	if (Distance(gameplay->actor_) < kUpdateRadius) {
        Point2D new_velocity = velocity_;
        
		// Изменение скорости: Сила тяги (по направлению движения).
		if (!moving_direction_.IsZero()) {
			// Вычисление изменения скорости.
			Point2D dv(static_cast<double>(moving_direction_.x), static_cast<double>(moving_direction_.y));
			dv *= kDefaultForcePull;
			dv /= moving_direction_.len();  // dv есть сила.
			dv /= mass_;  // dv есть ускорение.
			dv *= static_cast<double>(ms_delta) / 1000.0;  // dv есть изменение скорости.

			// Определение предельной скорости.
			Point2D velocity_moving(static_cast<double>(moving_direction_.x), static_cast<double>(moving_direction_.y));
			velocity_moving *= kDefaultVelocity;
			velocity_moving /= moving_direction_.len();

			// Изменение скорости.
			for (int dim : {0, 1}) {
				if (velocity_moving[dim] > 0) {
					if (new_velocity[dim] < velocity_moving[dim])
						new_velocity[dim] = std::min(velocity_moving[dim], new_velocity[dim] + dv[dim]);
				} else if (velocity_moving[dim] < 0) {
					if (new_velocity[dim] > velocity_moving[dim])
						new_velocity[dim] = std::max(velocity_moving[dim], new_velocity[dim] + dv[dim]);
				}
			}
		}

		// Изменение скорости: Сила сопротивления (против направления скорости).
        double velocity_len = new_velocity.len();
        if (!is_zero(velocity_len)) {
            // Вычисление изменения скорости.
            Point2D dv = (new_velocity * kDefaultForceStop) / velocity_len;  // dv есть сила.
            dv /= mass_;  // dv есть ускорение.
            dv *= static_cast<double>(ms_delta) / (-1000.0);  // dv есть изменение скорости.

            // Изменение скорости по X.
            if (std::abs(dv.x) > std::abs(new_velocity.x))
                new_velocity.x = 0.0;
            else
                new_velocity.x += dv.x;
            
            // Изменение скорости по Y.
            if (weightless_) {
                if (std::abs(dv.y) > std::abs(new_velocity.y))
                    new_velocity.y = 0.0;
                else
                    new_velocity.y += dv.y;
            }
        }

		// Изменение скорости: Сила гравитации.
		if (!weightless_) {
			new_velocity.y += kAccelGravi * static_cast<double>(ms_delta) / 1000.0;
		}

		// Изменение скорости: Другие силы.
		for (Forces::iterator it = forces_.begin(); it != forces_.end(); ) {
			new_velocity += (it->force / mass_) * static_cast<double>(ms_delta) / 1000.0;
			if ((it->deadline > 0) && (it->deadline <= ms_cur))
				it = forces_.erase(it);
			else
				++it;
		}

		// Изменение позиции: Определение сдвига с учётом столкновения с другими объектами.
		Point2D dpos = new_velocity * static_cast<double>(kPixelsPerMeter) * static_cast<double>(ms_delta) / 1000.0;
		if (get_type() == kObjTypeImpenetrable) {
			std::list<int> dims;
			if (is_more_than(std::abs(dpos.y), std::abs(dpos.x))) {
				dims.push_back(1);
				dims.push_back(0);
			} else {
				dims.push_back(0);
				dims.push_back(1);
			}
			for (std::list<int>::iterator dim_it = dims.begin(); dim_it != dims.end(); ++dim_it) {
				int dim = *dim_it;
				Box2D box;
				if (is_more_than(dpos[dim], 0.0)) {
					box.pos_.x = pos_.x;
					box.pos_.y = pos_.y;
					box.size_[dim] = static_cast<double>(size_[dim]) + dpos[dim];
					box.size_[1 - dim] = static_cast<double>(size_[1 - dim]);
					for (ObjectsStorage::iterator it = gameplay->objects_.begin(); it != gameplay->objects_.end(); ++it) {
						if ((*it)->get_type() == kObjTypeImpenetrable) {
							Box2D box_other((*it)->get_posd(), Point2D((*it)->get_size()));
							if (box.IntersectsWith(box_other)) {
								dpos[dim] = std::min(dpos[dim], box_other.pos_[dim] - (pos_[dim] + static_cast<double>(size_[dim])));
								new_velocity[dim] = 0.0;
							}
						}
					}
				} else if (is_less_than(dpos[dim], 0.0)) {
					box.pos_[dim] = pos_[dim] + dpos[dim];
					box.pos_[1 - dim] = pos_[1 - dim];
					box.size_[dim] = static_cast<double>(size_[dim]) - dpos[dim];
					box.size_[1 - dim] = static_cast<double>(size_[1 - dim]);
					for (ObjectsStorage::iterator it = gameplay->objects_.begin(); it != gameplay->objects_.end(); ++it) {
						if ((*it)->get_type() == kObjTypeImpenetrable) {
							Box2D box_other((*it)->get_posd(), Point2D((*it)->get_size()));
							if (box.IntersectsWith(box_other)) {
								dpos[dim] = std::max(dpos[dim], (box_other.pos_[dim] + box_other.size_[dim]) - pos_[dim]);
								new_velocity[dim] = 0.0;
							}
						}
					}
				}
			}

		}
		pos_ += dpos;

		// Ограничения карты.
		if ((pos_.x + size_.x) > MapGenerator::kMapRadiusX) {
			pos_.x = MapGenerator::kMapRadiusX - size_.x;
			new_velocity.x = std::min(0.0, new_velocity.x);
		}
		if (pos_.x < -MapGenerator::kMapRadiusX) {
			pos_.x = -MapGenerator::kMapRadiusX;
			new_velocity.x = std::max(0.0, new_velocity.x);
		}
        
        set_velocity(new_velocity);
	}
}

void GameObjectMotile::Event(GameObjectEventType event_type, GameObjectEventInfo* event_info) {}

void GameObjectMotile::Serialize(std::ofstream& file) const {
	BinaryFile::WriteDouble(file, velocity_.x);
	BinaryFile::WriteDouble(file, velocity_.y);
	BinaryFile::WriteInt(file, (int)forces_.size());
	for (std::list<Force>::const_iterator it = forces_.begin(); it != forces_.end(); ++it) {
		BinaryFile::WriteDouble(file, it->force.x);
		BinaryFile::WriteDouble(file, it->force.y);
		BinaryFile::WriteLongLong(file, it->deadline);
	}
}

void GameObjectMotile::Deserialize(std::ifstream& file) {
	velocity_.x = BinaryFile::ReadDouble(file);
	velocity_.y = BinaryFile::ReadDouble(file);
	int n = BinaryFile::ReadInt(file);
	forces_.clear();
	for (int i = 0; i < n; ++i) {
		Force force;
		force.force.x = BinaryFile::ReadDouble(file);
		force.force.y = BinaryFile::ReadDouble(file);
		force.deadline = BinaryFile::ReadLongLong(file);
		forces_.push_back(force);
	}
}

bool GameObjectMotile::SetStaticProperties(const std::string& section, const nlohmann::json& json) {
	// mass (mass_)
	const std::string mass_field = "mass";
	if (json.find(mass_field) == json.end()) {
		std::cerr << "[FATAL ERROR]" << std::endl;
		std::cerr << "    Object's section \"" << section << "\" doesn't have mandatory field \"" << mass_field << "\"." << std::endl;
		return false;
	}
	mass_ = json[mass_field].get<double>();

	// weightless (weightless_)
	const std::string weightless_field = "weightless";
	if (json.find(weightless_field) == json.end())
		weightless_ = false;
	else
		weightless_ = (json[weightless_field].get<int>() != 0);

	return true;
}

bool GameObjectMotile::SetDynamicProperties(const std::string& obj_id, const nlohmann::json& json) {
	// velocity (velocity_)
	const std::string velocity_field = "velocity";
	if (json.find(velocity_field) == json.end()) {
		velocity_.x = 0;
		velocity_.y = 0;
	} else {
		velocity_.x = json[velocity_field][0].get<double>();
		velocity_.y = json[velocity_field][1].get<double>();
	}

	// (forces_)
	forces_.clear();

	return true;
}

void GameObjectMotile::set_velocity(const Point2D& velocity) {
	velocity_ = velocity;
}
