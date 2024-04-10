#pragma once
#include "PanelWidget.h"
#include <Source/Editor/Engine/Button.h>

enum ELogVerbosity
{
	Message,
	Warning,
	Error
};

class Log
{
public:
	double time;
	ELogVerbosity verbosity;
	FString text;

public:
	Log(double _time, ELogVerbosity _verbosity, const FString& _text)
	{
		time = _time;
		verbosity = _verbosity;
		text = _text;
	}

public:
	FORCEINLINE ELogVerbosity GetVerbosity() const { return verbosity; }
	FORCEINLINE FString GetText() const { return text; }
	FORCEINLINE FString GetFullText() const { return FString::Format("[ {} ] {}: {}", time, GetVerbosityString(verbosity).GetText(), text.GetText()); }

public:
	FORCEINLINE ImVec4 GetColor() const
	{
		switch (verbosity)
		{
		case Message:
			return ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
		case Warning:
			return ImVec4(1.0f, 0.35f, 0.0f, 1.0f);
		case Error:
			return ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
		}
		return ImVec4();
	}

private:
	FORCEINLINE FString GetVerbosityString(const ELogVerbosity& _verbosity) const
	{
		switch (_verbosity)
		{
		case Message:
			return "Message";

		case Warning:
			return "Warning";

		case Error:
			return "Error";
		}
		return "";
	}
};

class LogGroup
{
public:
	int Count;
	FString Text;
	FString FullText;
	ImVec4 Color;

public:
	LogGroup(const FString& _text, const FString& _fullText, ImVec4 _color)
	{
		Text = _text;
		FullText = _fullText;
		Color = _color;
		Count = 1;
	}

	bool IsEquals(const FString& _text)
	{
		return Text == _text;
	}
};

class LogWidget : public PanelWidget
{
	vector<Log*> logs;
	vector<Button*> buttons;
	bool collapse;
	bool showMessages;
	bool showWarnings;
	bool showErrors;
	bool autoScroll;
	ImGuiTextFilter filter;

public:
	LogWidget(const FString& _name, EngineWindow* _window);
	~LogWidget() override;

public:
	void Draw() override;
	void Stop() override;

private:
	void AddLog(ELogVerbosity severity, const FString& _string, ...);
	void ShowLogs();
	vector<LogGroup*> GetLogs();
	void ClearLogs();

	bool IsFiltered(const ELogVerbosity& _severity, const FString& _text);
	bool IsSeverityFiltered(ELogVerbosity severity);
};