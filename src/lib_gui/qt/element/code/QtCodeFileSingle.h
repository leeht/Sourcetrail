#ifndef QT_CODE_FILE_SINGLE_H
#define QT_CODE_FILE_SINGLE_H

#include <deque>
#include <map>

#include <QFrame>

#include "FilePath.h"
#include "TimeStamp.h"

#include "QtCodeNavigateable.h"

class QLabel;
class QPushButton;
class QtCodeArea;
class QtCodeFileTitleBar;
class QtCodeNavigator;

class QtCodeFileSingle
	: public QFrame
	, public QtCodeNavigateable
{
	Q_OBJECT

public:
	QtCodeFileSingle(QtCodeNavigator* navigator, QWidget* parent = nullptr);
	virtual ~QtCodeFileSingle() = default;

	void clearFile();
	void clearCache();

	// QtCodeNavigateable implementation
	QAbstractScrollArea* getScrollArea() override;

	void addCodeSnippet(const CodeSnippetParams& params) override;
	void updateCodeSnippet(const CodeSnippetParams& params) override;

	void requestFileContent(const FilePath& filePath) override;
	bool requestScroll(
		const FilePath& filePath, size_t lineNumber, Id locationId, bool animated, ScrollTarget target) override;

	void updateFiles() override;
	void showContents() override;

	void onWindowFocus() override;

	void findScreenMatches(
		const std::wstring& query, std::vector<std::pair<QtCodeArea*, Id>>* screenMatches) override;

	std::vector<std::pair<FilePath, Id>> getLocationIdsForTokenIds(const std::set<Id>& tokenIds) const override;

	const FilePath& getCurrentFilePath() const;
	bool hasFileCached(const FilePath& filePath) const;

	Id getLocationIdOfFirstActiveLocationOfTokenId(Id tokenId) const;

public slots:
	void clickedSnippetButton();

private:
	struct FileData
	{
		FilePath filePath;
		TimeStamp modificationTime;
		bool isComplete = false;
		bool isIndexed = false;
		std::wstring title;

		QtCodeArea* area = nullptr;
	};

	FileData getFileData(const FilePath& filePath) const;
	void setFileData(const FileData& file);

	void updateRefCount(int refCount);

	QtCodeNavigator* m_navigator;

	QWidget* m_areaWrapper;
	FilePath m_currentFilePath;

	QtCodeFileTitleBar* m_titleBar;

	QtCodeArea* m_area;
	std::map<FilePath, FileData> m_fileDatas;
	std::deque<FilePath> m_filePaths;

	bool m_contentRequested;
	bool m_scrollRequested;
};

#endif // QT_CODE_FILE_SINGLE_H