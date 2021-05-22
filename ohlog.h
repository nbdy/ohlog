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

#include <string>
#include <ctime>
#include <iomanip>

#define DEFAULT_FORMAT "%Y.%m.%d %H:%M:%S"

namespace ohlog {
    enum LogLevel {
        DEBUG = 0, INFO, WARNING, ERROR
    };

    class Logger {
    public:
        /*!
         * get a Logger instance
         * @return pointer to initialized Logger
         */
        [[maybe_unused]] static Logger* get() {
            if (self == nullptr) self = new Logger();
            return self;
        }

        /*!
         * get the current timestamp
         * @param format std::string, the format to use
         * @return the current timestamp formatted as a string
         */
        static std::string getCurrentTimestamp(const std::string& format=DEFAULT_FORMAT) {
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
                case DEBUG:
                    o << "{D}\t"; break;
                case INFO:
                    o << "{I}\t"; break;
                case WARNING:
                    o << "{W}\t"; break;
                case ERROR:
                    o << "{E}\t"; break;
            }
            o << "{" << getCurrentTimestamp() << "}\t{" << tag << "} > " << msg << "\n";
            printf(o.str().c_str(), arguments...);
            fflush(stdout);
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

    private:
        inline static Logger* self = nullptr;
    };
}

#endif //LOGGER_OHLOG_H
