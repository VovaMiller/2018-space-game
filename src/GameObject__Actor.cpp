#include <DiggerOffline/GameObject__Actor.h>
#include <DiggerOffline/Game.h>

GameObject__Actor::GameObject__Actor() {}

GameObject* GameObject__Actor::Clone() const {
	return new GameObject__Actor(*this);
}

bool GameObject__Actor::IsActor() const {
	return true;
}

void GameObject__Actor::InteractWith(GameObject* obj, int x, int y) {
	if (Distance(x, y) > kInteractionRange) {
		Game::Instance()->get_audio_player()->Play("actor/far.ogg", true);
	} else if (obj == nullptr) {
		Game::Instance()->get_audio_player()->Play("actor/miss.ogg", true);
	} else {
		GameObjectEventInfo_dCondition* event_info = new GameObjectEventInfo_dCondition(-30, this);
		obj->Event(kObjEventCondition, event_info);
		delete event_info;
	}
}
