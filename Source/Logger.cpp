#include "Levin/Logger.hpp"

#include <vector>

using namespace Levin;

std::wstring Levin::ToMultibyteCharacter(std::string_view source)
{
	std::vector<wchar_t> result(source.size());
	// Converts a multibyte character string from the array whose first element
	// is pointed to by src to its wide character representation. Converted
	// characters are stored in the successive elements of the array pointed to
	// by dst. No more than len wide characters are written to the destination
	// array.
	// The firm of method std::mbstowcs is (dst, src, len)
	std::size_t status = std::mbstowcs(result.data(), source.data(), source.size());
	// Return the conversion made to text (std::wstring)
	return { result.data(), status };
}

Logger::Logger() noexcept : writeLock()
{
}

std::wstring Logger::GetCurrentTime() const noexcept
{
	time_t now = std::time(nullptr);
	// Converts given time since epoch to a calendar local time and then to a
	// textual representation, the type of return is char*, should be convert
	// to std::string
	std::string text = std::ctime(&now);
	// required, since ctime (asctime) append a new-line
	text.erase(text.find_last_of('\n'), 1);

	return ToMultibyteCharacter(text);
}

std::wstring Logger::ToString(Level level) const noexcept
{
	switch (level)
	{
	case Level::DEBUG:
		return L"[D]";
	case Level::INFO:
		return L"[I]";
	case Level::WARNING:
		return L"[W]";
	case Level::ERROR:
		return L"[E]";
	case Level::SEVERE:
		return L"[S]";
	default:
		return L"[U]";
	}
}