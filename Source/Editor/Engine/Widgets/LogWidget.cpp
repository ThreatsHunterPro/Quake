#include "LogWidget.h"

LogWidget::LogWidget(const FString& _name, EngineWindow* _window) : PanelWidget(_name, _window)
{
    logs = vector<Log*>();
    buttons =
    {
        new Button("Clear", [this]
        {
            ClearLogs();
        }),
        new Button("Clear on Play", [this]
        {
            AddLog(Message, "Clear on Play");
        }),
        new Button("Collapse", [this]
        {
            collapse = !collapse;
        }),
        new Button("Error Pause", [this]
        {
            AddLog(Error, "Error Pause");
        }),
        new Button("Filters", [this]
        {
            ImGui::OpenPopup("SeverityFilter");
        })
    };

    collapse = false;
    showMessages = true;
    showWarnings = true;
    showErrors = true;
    autoScroll = true;
}

LogWidget::~LogWidget()
{
    for (int i = 0; i < buttons.size(); i++)
    {
        delete buttons[i];
        buttons[i] = nullptr;
    }
}

void LogWidget::Draw()
{
    ImGui::Begin("Output Log", &widgetStatus);

    const int _buttonsCount = buttons.size();
    for (int _buttonIndex = 0; _buttonIndex < _buttonsCount; _buttonIndex++)
    {
        Button* _button = buttons[_buttonIndex];
        if (!_button) continue;

        if (ImGui::Button(*(_button->GetTitle())))
        {
            _button->Callback();
        }
        ImGui::SameLine();
    }

    if (ImGui::BeginPopup("SeverityFilter", ImGuiPopupFlags_None))
    {
        ImGui::Checkbox("Messages", &showMessages);
        ImGui::Checkbox("Warnings", &showWarnings);
        ImGui::Checkbox("Errors", &showErrors);
        ImGui::EndPopup();
    }

    ImGui::SameLine();
    filter.Draw("Filter", 200.0f);

    ImGui::SameLine();
    ImGui::Checkbox("Auto-scroll", &autoScroll);

    ImGui::Separator();
    ShowLogs();

    ImGui::Separator();
    ImGui::End();
}

void LogWidget::Stop()
{
    ClearLogs();
}

void LogWidget::AddLog(ELogVerbosity _verbosity, const FString& _string, ...)
{
    Log* _log = new Log(ImGui::GetTime(), _verbosity, _string);
    logs.push_back(_log);
}

void LogWidget::ShowLogs()
{
    if (ImGui::BeginChild("Console", ImVec2(0.0f, 0.0f), false, ImGuiWindowFlags_HorizontalScrollbar))
    {
        vector<LogGroup*> _logGroups = GetLogs();
        const int _groupsCount = _logGroups.size();

        for (int _groupIndex = 0; _groupIndex < _groupsCount; _groupIndex++)
        {
            const LogGroup* _group = _logGroups[_groupIndex];
            ImGui::TextColored(_group->Color, _group->FullText.GetText().c_str());

            if (collapse)
            {
                ImGui::SameLine(350.0f);
                ImGui::Text(*FString::Format("{}", _group->Count));
            }
        }

        if (autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        {
            ImGui::SetScrollHereY(1.0f);
        }

        for (int i = 0; i < _logGroups.size(); i++)
        {
            delete _logGroups[i];
        }
    }

    ImGui::EndChild();
}

vector<LogGroup*> LogWidget::GetLogs()
{
    vector<LogGroup*> _logGroups = vector<LogGroup*>();

    const int _logsCount = logs.size();
    for (int _logIndex = 0; _logIndex < _logsCount; _logIndex++)
    {
        const Log* _log = logs[_logIndex];
        const FString& _text = _log->GetText();
        const FString& _fullText = _log->GetFullText();
        const ELogVerbosity& _severity = _log->GetVerbosity();
        const ImVec4& _color = _log->GetColor();

        if (IsFiltered(_severity, _text)) continue;

        if (_logGroups.size() <= 0 || !collapse)
        {
            _logGroups.push_back(new LogGroup(_text, _fullText, _color));
            continue;
        }

        bool _isEquals = false;
        for (int _groupIndex = 0; _groupIndex < _logGroups.size(); _groupIndex++)
        {
            LogGroup* _group = _logGroups[_groupIndex];

            if (_group->IsEquals(_text))
            {
                _group->Count += 1;
                _isEquals = true;
                break;
            }
        }

        if (!_isEquals)
        {
            _logGroups.push_back(new LogGroup(_text, _fullText, _color));
        }
    }

    return _logGroups;
}

void LogWidget::ClearLogs()
{
    for (int i = 0; i < logs.size(); i++)
    {
        delete logs[i];
    }

    logs.clear();
}

bool LogWidget::IsFiltered(const ELogVerbosity& _severity, const FString& _text)
{
    return IsSeverityFiltered(_severity) || filter.IsActive() && !filter.PassFilter(_text.GetText().c_str());
}

bool LogWidget::IsSeverityFiltered(ELogVerbosity _verbosity)
{
    switch (_verbosity)
    {
    case Message:
        return !showMessages;

    case Warning:
        return !showWarnings;

    case Error:
        return !showErrors;
    }

    return false;
}
