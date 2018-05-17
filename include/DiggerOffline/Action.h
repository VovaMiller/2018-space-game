#pragma once
#include <string>
#include <vector>


class Action {
public:
	virtual ~Action() {}

	virtual void Act() = 0;
};

class ActionMacro : public Action {
public:
	virtual ~ActionMacro();

	virtual void Act();
	void AddAction(Action* action);
private:
	std::vector<Action*> actions_;
};


class Action_OpenMapMenu : public Action {
public:
	virtual void Act();
};

class Action_Exit : public Action {
public:
	virtual void Act();
};

class Action_LoadMap : public Action {
public:
	Action_LoadMap(const std::string& map_path);

	std::string map_path_;

	virtual void Act();
};

class Action_Back : public Action {
public:
	virtual void Act();
};

class Action_Save : public Action {
public:
	virtual void Act();
};

class Action_Continue : public Action {
public:
	virtual void Act();
};

class Action_Halt : public Action {
public:
	virtual void Act();
};

class Action_PlaySound : public Action {
public:
	Action_PlaySound(const std::string& sound_path, bool interrupt);

	std::string sound_path_;
	bool interrupt_;

	virtual void Act();
};

class Action_StopSound : public Action {
public:
	Action_StopSound(const std::string& sound_path);

	std::string sound_path_;

	virtual void Act();
};

class Action_NewMap : public Action {
public:
	virtual void Act();
};
