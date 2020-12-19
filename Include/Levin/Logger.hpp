#ifndef LOGGER_H
#define LOGGER_H

#include "Level.hpp"

#include <chrono>
#include <fstream>
#include <mutex>

namespace Levin
{
	/**
	 * One of the primary benefits of using data loggers is the ability to
	 * automatically collect data on a 24-hour basis. Upon activation, data
	 * loggers are typically deployed and left unattended to measure and record
	 * information for the duration of the monitoring period.
	 */
	class Logger
	{

	public:

		Logger(const Logger&) = delete;

		Logger(Logger&&) = delete;

		virtual ~Logger() = default;

		Logger& operator=(const Logger&) = delete;

		Logger& operator=(Logger&&) = delete;

		/*
		 * @brief Writes the log to the output beneath
		 *
		 * @note: Implementations of this method need to be thread-safe, e.g.
		 * this method can be written to from multiple threads concurrently.
		 */
		virtual void Message(Level level, std::wstring_view local) = 0;

	protected:

		std::mutex writeLock;

		Logger() noexcept;

		[[nodiscard]] std::wstring GetCurrentTime() const noexcept;

		[[nodiscard]] std::wstring ToString(Level level) const noexcept;
	};

	/**
	 * Maps a character string to a UTF-16 (wide character) string.
	 * The character string is not necessarily from a multibyte character set.
	 *
	 * @note This function is Thread Safe, can be called simultaneously by two
	 * threads.
	 *
	 * @param source Pointer (string_view) to the character string to convert.
	 * @return The wide character representation of source.
	 */
	std::wstring MultiByteToWideChar(const char* source);
}

#endif /* LOGGER_H */
