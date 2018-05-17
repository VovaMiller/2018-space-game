#include <DiggerOffline/GameObjectEvent.h>

GameObjectEventInfo_dCondition::GameObjectEventInfo_dCondition(int delta, GameObject* who) : delta_(delta), who_(who) {}

int GameObjectEventInfo_dCondition::get_delta() const {
	return delta_;
}

GameObject* GameObjectEventInfo_dCondition::get_who() const {
	return who_;
}
