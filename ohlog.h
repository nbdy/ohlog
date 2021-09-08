//
// Created by Pascal Eberlein on 23.03.21.
//
/*
 * MIT License
 *
 * Copyright ohlog 2021 Pascal Eberlein
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef LOGGER_OHLOG_H
#define LOGGER_OHLOG_H

#include <ctime>
#include <string>
#include <fstream>
#include <iomanip>
#include <filesystem>
#include <utility>
#include <iostream>

#include "pubsupp.h"

#define DEFAULT_FORMAT "%Y.%m.%d %H:%M:%S"
#define GET_FILENAME std::filesystem::path(__FILE__).filename()
#define OHLOG ohlog::Logger::get()
#define DLOG(msg) OHLOG->d(GET_FILENAME, msg)
#define DLOGA(msg, args...) OHLOG->d(GET_FILENAME, msg, args)
#define ILOG(msg) OHLOG->i(GET_FILENAME, msg)
#define ILOGA(msg, args...) OHLOG->i(GET_FILENAME, msg, args)
#define WLOG(msg) OHLOG->w(GET_FILENAME, msg)
#define WLOGA(msg, args...) OHLOG->w(GET_FILENAME, msg, args)
#define ELOG(msg) OHLOG->e(GET_FILENAME, msg)
#define ELOGA(msg, args...) OHLOG->e(GET_FILENAME, msg, args)

namespace ohlog {
enum LogLevel {
  DEBUG = 0, INFO, WARNING, ERROR
};

class Logger {
 public:
  explicit Logger(std::string i_sLogFilePath): m_sLogFilePath(std::move(i_sLogFilePath)) {
    if(isLoggingToFile()) {
      m_LogFileStream = std::ofstream(m_sLogFilePath);
    }
    queue.subscribe("logMsg", [this](auto && PH1) { writeToLog(std::forward<decltype(PH1)>(PH1)); });
  }

  /*!
   * get a Logger instance
   * @return pointer to initialized Logger
   */
  [[maybe_unused]] static Logger* get(const std::string& filePath = "") {
    if (self == nullptr) self = new Logger(filePath);
    return self;
  }

  /*!
   * get the current timestamp
   * @param format std::string, the format to use
   * @return the current timestamp formatted as a string
   */
  static std::string getCurrentTimestamp(const std::string& format = DEFAULT_FORMAT) {
    std::stringstream o;
    const auto t = std::time(nullptr);
    const auto tm = *std::localtime(&t);
    o << std::put_time(&tm, format.c_str());
    return o.str();
  }

  /*!
   * log to cli
   * @tparam Args
   * @param tag std::string, the prefix for the line
   * @param msg std::string, the message to display
   * @param level LogLevel, the loglevel
   * @param arguments
   */
  template<typename... Args>
  void log(const std::string& tag, const std::string& msg, LogLevel level = INFO, Args... arguments) {
    std::stringstream o;
    switch (level) {
      case DEBUG:o << "D ";
        break;
      case INFO:o << "I ";
        break;
      case WARNING:o << "W ";
        break;
      case ERROR:o << "E ";
        break;
    }
    o << getCurrentTimestamp() << " " << tag << ": " << msg;
    std::string formatStr = o.str();
    int lineLength = snprintf(nullptr, 0, formatStr.c_str(), arguments...) + 1;
    char line[lineLength + 1];
    snprintf(line, lineLength, formatStr.c_str(), arguments...);
    std::string logLine(line);
    std::cout << logLine << std::endl;
    if(isLoggingToFile()) {
      queue.publish(m_sLogChannel, logLine);
    }
  }

  void writeToLog(const std::string& logLine) {
    m_LogFileStream << logLine << std::endl;
    m_LogFileStream.flush();
  }

  /*!
   * shorthand function for log
   * @tparam Args
   * @param tag
   * @param msg
   * @param arguments
   */
  template<typename... Args>
  [[maybe_unused]] void d(const std::string& tag, const std::string& msg, Args... arguments) {
    log(tag, msg, DEBUG, arguments...);
  }

  /*!
   * shorthand function for log
   * @tparam Args
   * @param tag
   * @param msg
   * @param arguments
   */
  template<typename... Args>
  [[maybe_unused]] void i(const std::string& tag, const std::string& msg, Args... arguments) {
    log(tag, msg, INFO, arguments...);
  }

  /*!
   * shorthand function for log
   * @tparam Args
   * @param tag
   * @param msg
   * @param arguments
   */
  template<typename... Args>
  [[maybe_unused]] void w(const std::string& tag, const std::string& msg, Args... arguments) {
    log(tag, msg, WARNING, arguments...);
  }

  /*!
   * shorthand function for log
   * @tparam Args
   * @param tag
   * @param msg
   * @param arguments
   */
  template<typename... Args>
  [[maybe_unused]] void e(const std::string& tag, const std::string& msg, Args... arguments) {
    log(tag, msg, ERROR, arguments...);
  }

  bool isLoggingToFile() {
    return !m_sLogFilePath.empty();
  }

 private:
  inline static std::string m_sLogChannel = "logMsg";
  inline static Logger* self = nullptr;

  std::string m_sLogFilePath;
  std::ofstream m_LogFileStream;
  StrPubSub queue;
};
}

#endif //LOGGER_OHLOG_H
