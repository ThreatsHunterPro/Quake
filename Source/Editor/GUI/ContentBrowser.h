#pragma 
#include "ActiveWidget.h"
#include "../../ImGUI/misc/cpp/imgui_stdlib.h"
#include <fstream>
#include <map>

//TODO remove/move to Texture class
#define PATH_TEXTURES "/Content/Textures/"

class ContentBrowser : public ActiveWidget
{
	class File
	{
		bool isFolder;
		FString name;
		FString path;
		FString extension;
		vector<File*> files;

	public:
		FORCEINLINE bool IsFolder() const { return isFolder; }
		FORCEINLINE FString GetName() const { return name; }
		FORCEINLINE FString GetPath() const { return path; }
		FORCEINLINE FString GetExtension() const { return extension; }
		FORCEINLINE vector<File*> GetFiles() { return files; }
		FORCEINLINE void AddFile(File* _file) { files.push_back(_file); }

	public:
		File(const FString& _name, const FString& _path, const bool _isFolder, const FString& _extension = "")
		{
			isFolder = _isFolder;
			name = _name;
			path = _path;
			extension = _extension;
			files = vector<File*>();
		}
		File(const File* _other)
		{
			isFolder = _other->isFolder;
			name = _other->name;
			path = _other->path;
			extension = _other->extension;
			files = _other->files;
		}

	public:
		void ClearFiles()
		{
			if (!isFolder)
				return;

			const size_t _num = files.size();

			for (size_t i = 0; i < _num; i++)
				if (!files[i]->isFolder)
					delete files[i];

			files.clear();
		}

	public:
		File& operator=(const File* _other)
		{
			isFolder = _other->isFolder;
			name = _other->name;
			path = _other->path;
			extension = _other->extension;
			files = _other->files;
			return *this;
		}
	};

	bool updating;
	FString currentPath;
	GLuint folderTexture;
	GLuint fileTexture;
	File* currentFolder;
	vector<File*> folders;

	//Menu
	bool addDetailPopupOpened;
	bool lastAddResult;
	string currentInput;

	//BreadcrumbTrail
	bool bTInit;
	vector<string> bTString;

	//Tree
	bool openTree;

	//Filters
	map<string, bool> filters;

	//Files
	ImGuiTextFilter search;
	bool waitForUpdate;

public:
	ContentBrowser() = default;
	ContentBrowser(const FString& _name, EngineWindow* _window);
	~ContentBrowser();

public:
	void Draw() override;
	void Stop() override;

private:
	void ClearFolders();
	void UpdateContent();
	void RetrieveFiles(File* _folder);
	void InitBreadcrumbTrail(FString _currentPath);
	void UpdateFilters(File* _file);
	void ClearFilters();
	bool CheckFilters(File* _file);

	void OpenPopupButton(const char* _buttonName, const char* _popupName);

	//Add
	void AddPopup(const char* _popupName);
	void AddDetailPopup(const char* _popupName, const char* _inputTextLabel, const function<bool(const string&)>& _callback);
	bool AddFolder(const string& _folderName);
	bool AddFile(const string& _fileName);

	//Draw
	void DrawMainBar();
	void DrawBreadcrumbTrail(FString _currentPath);
	void DrawTreeFolders(File* _folder);
	void DrawFilters();
	void DrawSearchBar();
	void DrawFiles(File* _folder);

	//TODO remove/move to Texture class
	GLuint LoadTexture(const FString& _filename) const;
};