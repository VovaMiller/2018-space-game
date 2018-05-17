#pragma once
#include <DiggerOffline/Point2DInt.h>
#include <DiggerOffline/Color.h>
#include <string>

enum AlignmentX { kLeftX, kCenterX, kRightX };
enum AlignmentY { kTopY, kCenterY, kBottomY };

enum UserAction {
	kUndefined,
	kCloseWindow,
	kMouseClickLeft, kMouseClickRight,
	kEsc, kLCtrl, kLShift, kLAlt, kRCtrl, kRShift, kRAlt,
	kSpace,
	kQ, kW, kE, kR, kT, kY, kU, kI, kO, kP, kA, kS, kD, kF, kG, kH, kJ, kK, kL, kZ, kX, kC, kV, kB, kN, kM
};

enum UserActionType {
	kUserActionPressed, kUserActionReleased
};

struct UserActionInfo {
	UserActionInfo() : ua(kUndefined), uat(kUserActionPressed), x(0), y(0) {}
	UserActionInfo(UserAction ua) : ua(ua), uat(kUserActionPressed), x(0), y(0) {}
	UserActionInfo(int x0, int y0) : ua(kUndefined), uat(kUserActionPressed), x(x0), y(y0) {}
	UserActionInfo(UserAction ua, int x0, int y0) : ua(ua), uat(kUserActionPressed), x(x0), y(y0) {}
	UserAction ua;
	UserActionType uat;
	int x, y;
};

class Window;
class AudioPlayer;

class Tools {
public:
	virtual Window* CreateWindow(int width, int height, const std::string& game_name) = 0;
	virtual AudioPlayer* CreateAudioPlayer() = 0;
};

class Window {
public:
	virtual ~Window() {}

	virtual void Close() = 0;
	virtual void Clear() = 0;
	virtual void Display() = 0;
	// ��������� �������� �� �������������� ���� � �����.
	void DrawTexture(const Point2DInt& pos, const Point2DInt& size, const std::string& texture_path);
	// ��������� ������ �� �������������� ���� � ����� ������.
	void DrawText(const std::string& text, const std::string& font_path, int size, const Color& color, const Point2DInt& pos,
		AlignmentX alignment_x = kLeftX, AlignmentY alignment_y = kTopY);
	// �������� ���������� � �������� ������������ (������� �������, ������ ����, ...).
	// ���� �������� �� ���� (��� ��� �� ��������������), �� ���������� false, ����� true.
	virtual bool GetAction(UserActionInfo& uai) = 0;

protected:
	// ��������� �������� �� ������� ���� � �����.
	// ���������� true <=> ��������� ��������� �������.
	virtual bool DrawTextureFullPath(const Point2DInt& pos, const Point2DInt& size, const std::string& texture_path) = 0;
	// ��������� ������ �� ������� ���� � ����� ������.
	// ���������� true <=> ��������� ��������� �������.
	virtual bool DrawTextFullPath(const std::string& text, const std::string& font_path, int size, const Color& color, const Point2DInt& pos,
		AlignmentX alignment_x, AlignmentY alignment_y) = 0;
};

class AudioPlayer {
public:
	virtual ~AudioPlayer() {}

	// ��������������� ����� �� �������������� ���� � �����.
	void Play(const std::string& sound_path, bool interrupt);
	// ���������� ��������������� ����������� �����.
	virtual void Stop(const std::string& sound_path) = 0;
	// ���������� ��������������� ���� ������.
	virtual void StopAll() = 0;

protected:
	// ��������������� ����� �� ������� ���� � �����.
	// ���������� true <=> ��������������� ��������� �������.
	virtual bool PlayFullPath(const std::string& sound_path, bool interrupt, float volume) = 0;
};
