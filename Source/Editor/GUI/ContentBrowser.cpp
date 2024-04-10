#include "ContentBrowser.h"

ContentBrowser::ContentBrowser(const FString& _name, EngineWindow* _window) : ActiveWidget(_name, _window)
{
	updating = false;

	currentPath = fs::current_path().generic_string().c_str();
	currentPath.Replace("/Binaries", "");

	fileTexture = LoadTexture("File.png");
	folderTexture = LoadTexture("Folder.png");
	folders = vector<File*>();

	addDetailPopupOpened = true;
	lastAddResult = false;
	currentInput = "";

	bTInit = false;
	bTString = vector<string>();

	openTree = true;

	filters = map<string, bool>({ pair("folder", true) });

	search = ImGuiTextFilter();
	waitForUpdate = false;
	UpdateContent();
}

ContentBrowser::~ContentBrowser()
{
	ClearFolders();
}

void ContentBrowser::Draw()
{
	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	const ImVec2 _base_size = viewport->Size;
	ImGui::SetNextWindowPos(ImVec2(0, _base_size.y - 212), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(1200, 200), ImGuiCond_Once);

	ImGuiWindowFlags _window_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoCollapse;
	const char* _name = name.GetText().c_str();

	if (!ImGui::Begin(_name, &widgetStatus, _window_flags))
	{
		ImGui::End();
		return;
	}

	ImGuiStyle& _style = ImGui::GetStyle();
	_style.WindowBorderSize = 1.f;

	DrawMainBar();
	ImGui::Spacing();

	ImGui::Columns(3);
	ImGui::SetColumnWidth(0, 400.f);
	DrawTreeFolders(currentFolder);

	ImGui::NextColumn();
	ImGui::SetColumnWidth(1, 200.f);
	ImGui::Text("Filters");
	DrawFilters();

	ImGui::NextColumn();
	DrawSearchBar();
	ImGui::Spacing();
	DrawFiles(currentFolder);

	ImGui::End();
}

void ContentBrowser::Stop()
{
	ClearFolders();
}

void ContentBrowser::ClearFolders()
{
	const size_t _num = folders.size();

	for (size_t i = 0; i < _num; i++)
	{
		folders[i]->ClearFiles();
		delete folders[i];
	}

	folders.clear();
}

void ContentBrowser::UpdateContent()
{
	ClearFolders();
	ClearFilters();
	const size_t _subIndex = currentPath.FindLastChar('/');
	const FString& _fileName = currentPath.SubString(_subIndex + 1);
	currentFolder = new File(_fileName, currentPath, true);
	folders.push_back(currentFolder);
	RetrieveFiles(currentFolder);
	openTree = true;
	bTInit = updating = false;
}

void ContentBrowser::RetrieveFiles(File* _folder)
{
	const string _path = _folder->GetPath().GetText();

	for (const fs::directory_entry& _directoryEntry : fs::directory_iterator(_path))
	{
		FString _filePath = _directoryEntry.path().string().c_str();
		_filePath.Replace("\\", "/");
		_filePath.Append("\0");
		const size_t _subIndex = _filePath.FindLastChar('/');
		FString _fileName = _filePath.SubString(_subIndex + 1);

		if (_fileName.FindChar('.') == 0)
			continue;

		const bool _isFolder = _directoryEntry.is_directory();
		FString _ext = "";

		if (!_isFolder)
		{
			const size_t _pointIndex = _fileName.FindChar('.');
			_ext = _fileName.SubString(_pointIndex + 1);
		}

		File* _file = new File(_fileName, _filePath, _isFolder, _ext);

		if (_isFolder)
			folders.push_back(_file);
		else
		{
			if (_folder == currentFolder)
				UpdateFilters(_file);
		}

		_folder->AddFile(_file);
	}
}

void ContentBrowser::InitBreadcrumbTrail(FString _currentPath)
{
	if (bTInit)
		return;

	bTString.clear();
	FString _path = _currentPath;
	size_t _subIndex = _path.FindChar('/');
	string _toAdd = "";

	do
	{
		_toAdd = _path.SubString(0, _subIndex).GetText();
		bTString.push_back(_toAdd);
		_toAdd += '/';
		_path.Replace(_toAdd.c_str(), "");
		_subIndex = _path.FindChar('/');

	} while (_path.Contains("/"));

	bTString.push_back(_path.GetText());
	bTInit = true;
}

void ContentBrowser::UpdateFilters(File* _file)
{
	const string _ext = _file->GetExtension().GetText();

	if (!filters.contains(_ext))
		filters.emplace(pair(_ext, true));
}

void ContentBrowser::ClearFilters()
{
	filters.clear();
	filters = { pair("folder", true) };
}

bool ContentBrowser::CheckFilters(File* _file)
{
	for (pair<string, bool> _pair : filters)
	{
		if (_pair.second)
		{
			if (_pair.first == "folder")
			{
				if (_file->IsFolder())
					return true;
			}
			else if (_pair.first == _file->GetExtension().GetText())
				return true;
		}
	}

	return false;
}

void ContentBrowser::OpenPopupButton(const char* _buttonName, const char* _popupName)
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));

	if (ImGui::Button(_buttonName))
	{
		addDetailPopupOpened = true;
		currentInput = "";
		ImGui::OpenPopup(_popupName);
	}

	ImGui::PopStyleColor();
}

//Add
void ContentBrowser::AddPopup(const char* _popupName)
{
	if (ImGui::BeginPopup(_popupName))
	{
		const char* _addFolderPopupName = "AddFolderPopup";
		const char* _addFilePopupName = "AddFilePopup";

		OpenPopupButton("Add folder", _addFolderPopupName);
		AddDetailPopup(_addFolderPopupName, "folder name", [&](const string& currentInput) { return AddFolder(currentInput); });

		OpenPopupButton("Add file", _addFilePopupName);
		AddDetailPopup(_addFilePopupName, "file name", [&](const string& currentInput) { return AddFile(currentInput); });

		ImGui::EndPopup();
	}
}

void ContentBrowser::AddDetailPopup(const char* _popupName, const char* _inputTextLabel, const function<bool(const string&)>& _callback)
{
	if (ImGui::BeginPopup(_popupName))
	{
		ImGui::InputText(_inputTextLabel, &currentInput);
		ImGui::SeparatorText(addDetailPopupOpened ? "Result: ..." : lastAddResult ? "Result: Success" : "Result: Failed");
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));

		if (ImGui::Button("Add"))
		{
			addDetailPopupOpened = false;
			lastAddResult = _callback(currentInput);
			UpdateContent();
		}

		ImGui::PopStyleColor();

		ImGui::EndPopup();
	}
}

bool ContentBrowser::AddFolder(const string& _folderName)
{
	fs::path _directoryPath = currentPath.GetText() + "/" + _folderName;
	return fs::create_directory(_directoryPath);
}

bool ContentBrowser::AddFile(const string& _fileName)
{
	const string _path = currentPath.GetText() + "/" + _fileName;

	if (fs::exists(_path))
		return false;

	ofstream _newFile = ofstream(_path);

	if (_newFile.is_open())
	{
		_newFile.close();
		return true;
	}

	return false;
}

//Draw
void ContentBrowser::DrawMainBar()
{
	const char* _addPopupName = "AddPopup";

	if (ImGui::Button("Add"))
		ImGui::OpenPopup(_addPopupName);

	AddPopup(_addPopupName);

	ImGui::SameLine();
	DrawBreadcrumbTrail(currentPath);
}

void ContentBrowser::DrawBreadcrumbTrail(FString _currentPath)
{
	InitBreadcrumbTrail(_currentPath);
	const size_t _btStringNum = bTString.size();
	bool _canStart = false;
	size_t _quakeIndex = 0;

	for (size_t i = 0; i < _btStringNum; i++)
	{
		const std::string& _folderName = bTString[i];

		if (!_canStart)
		{
			if (_folderName == "Quake")
			{
				_canStart = true;
				_quakeIndex = i;
			}
			else
				continue;
		}

		if (i != _quakeIndex)
		{
			ImGui::SameLine();
			ImGui::Text("/");
			ImGui::SameLine();
		}

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));

		if (ImGui::Button(_folderName.c_str()))
		{
			updating = true;
			currentPath = "";
			string _newPath = "";

			for (size_t y = 0; y <= i; y++)
			{
				_newPath += bTString[y].c_str();

				if (y != i)
					_newPath += "/";
			}

			currentPath = _newPath.c_str();
			UpdateContent();
		}

		ImGui::PopStyleColor();

		if (updating)
			break;
	}
}

void ContentBrowser::DrawTreeFolders(File* _folder)
{
	if (!_folder || updating)
		return;

	const vector<File*> _files = _folder->GetFiles();
	const size_t _filesNum = _files.size();
	FString _name = _folder->GetName();
	const char* _cname = _name.GetText().c_str();
	const bool _isFolder = _folder->IsFolder();

	if (_filesNum == 0 && _isFolder)
		RetrieveFiles(_folder);

	if (openTree && _folder == currentFolder)
	{
		ImGui::SetNextItemOpen(true);
		openTree = false;
	}

	if (ImGui::TreeNode(_cname))
	{
		for (size_t i = 0; i < _filesNum; i++)
		{
			if (!_files[i]->IsFolder())
				ImGui::Text(_files[i]->GetName().GetText().c_str());
			else
				DrawTreeFolders(_files[i]);
		}

		ImGui::TreePop();
	}
}

void ContentBrowser::DrawFilters()
{
	if (updating)
		return;

	for (pair<string, bool> _pair : filters)
	{
		if (_pair.first == "")
			continue;

		if (ImGui::Selectable(_pair.first.c_str(), _pair.second))
			filters[_pair.first] = !_pair.second;
	}
}

void ContentBrowser::DrawSearchBar()
{
	ImGui::Text("Search:");
	ImGui::SameLine();
	search.Draw(" xxx | xxx, yyy | -xxx", 300.f);
}

void ContentBrowser::DrawFiles(File* _folder)
{
	if (!_folder || updating)
		return;

	vector<File*> _files = _folder->GetFiles();
	const size_t _filesNum = _files.size();

	for (size_t i = 0; i < _filesNum; i++)
	{
		const FString& _fileName = _files[i]->GetName();

		if (!search.PassFilter(_fileName.GetText().c_str()) || !CheckFilters(_files[i]))
			continue;

		if (!_files[i]->IsFolder())
		{
			ImGui::Image(ImTextureID(fileTexture), ImVec2(15, 15));
			ImGui::SameLine();
			ImGui::Text(_fileName.GetText().c_str());
		}
		else
		{
			ImGui::Image(ImTextureID(folderTexture), ImVec2(15, 15));
			ImGui::SameLine();
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));

			if (ImGui::Button(_fileName.GetText().c_str()))
			{
				updating = true;
				waitForUpdate = true;
				const string _newPath = currentPath.GetText() + "/" + _fileName.GetText();
				currentPath = _newPath.c_str();
				UpdateContent();
			}

			ImGui::PopStyleColor();
		}

		if (waitForUpdate)
		{
			waitForUpdate = false;
			break;
		}
	}
}

//TODO remove/move to Texture class
GLuint ContentBrowser::LoadTexture(const FString& _filename) const
{
	int width, height, channels;
	FString _quakePath = (fs::current_path().generic_string()).c_str();
	_quakePath.Replace("/Binaries", "");
	const string _path = _quakePath.GetText() + PATH_TEXTURES + _filename.GetText();
	cout << _path << endl;
	unsigned char* data = stbi_load(_path.c_str(), &width, &height, &channels, 0);

	if (!data) {
		std::cerr << "Failed to load texture: " << _filename.GetText() << std::endl;
		return 0;
	}

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	const GLenum format = channels == 3 ? GL_RGB : GL_RGBA;
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
	return textureID;
}
