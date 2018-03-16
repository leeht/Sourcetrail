#include "data/indexer/IndexerCommandCxxEmpty.h"

IndexerCommandType IndexerCommandCxxEmpty::getStaticIndexerCommandType()
{
	return INDEXER_COMMAND_CXX_EMPTY;
}

IndexerCommandCxxEmpty::IndexerCommandCxxEmpty(
	const FilePath& sourceFilePath,
	const std::set<FilePath>& indexedPaths,
	const std::set<FilePathFilter>& excludeFilters,
	const FilePath& workingDirectory,
	const std::string& languageStandard,
	const std::vector<FilePath>& systemHeaderSearchPaths,
	const std::vector<FilePath>& frameworkSearchPaths,
	const std::vector<std::wstring>& compilerFlags
)
	: IndexerCommandCxx(sourceFilePath, indexedPaths, excludeFilters, workingDirectory, systemHeaderSearchPaths, frameworkSearchPaths, compilerFlags)
	, m_languageStandard(languageStandard)
{
}

IndexerCommandType IndexerCommandCxxEmpty::getIndexerCommandType() const
{
	return getStaticIndexerCommandType();
}

size_t IndexerCommandCxxEmpty::getByteSize(size_t stringSize) const
{
	return IndexerCommandCxx::getByteSize(stringSize) + m_languageStandard.size();
}

std::string IndexerCommandCxxEmpty::getLanguageStandard() const
{
	return m_languageStandard;
}