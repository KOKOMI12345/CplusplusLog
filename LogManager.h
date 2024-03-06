#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>

class LogManager {
public:
    static const int DEBG = 1;
    static const int INFO = 2;
    static const int WARN = 3;
    static const int ERRO = 4;
    static const int FATAL = 5;

    std::string name;
    std::ofstream logFile;

public:
    LogManager(const std::string& name, const std::string& filename) : name(name) {
        logFile.open(filename, std::ios::out | std::ios::app);
    }

    ~LogManager() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    void log(int level, const std::string& message) {
        std::string levelStr;
        std::string colorCode;

        switch (level) {
            case DEBG:
                levelStr = "DEBUG";
                colorCode = "\033[94m"; // 设置为浅蓝色
                break;
            case INFO:
                levelStr = "INFO";
                colorCode = "\033[96m"; // 设置为青色
                break;
            case WARN:
                levelStr = "WARN";
                colorCode = "\033[93m"; // 设置为黄色
                break;
            case ERRO:
                levelStr = "ERROR";
                colorCode = "\033[91m"; // 设置为红色
                break;
            case FATAL:
                levelStr = "FATAL";
                colorCode = "\033[1;91m"; // 设置为粗体红色
                break;
            default:
                levelStr = "UNKNOWN";
                colorCode = "\033[0m"; // 重置颜色
                break;
        }

        std::time_t now = std::time(nullptr);
        struct tm* timeinfo = std::localtime(&now);

        char buffer[80];
        strftime(buffer, 80, "%H:%M:%S", timeinfo); // 格式化时间为 HH:MM:SS

        std::ostringstream logStream;
        logStream << "[" << buffer << "]" << "[" << name << "/" << levelStr << "]" << ": " << message;

        // 输出到终端
        std::cout << colorCode << logStream.str() << "\033[0m" << std::endl; // 重置颜色

        // 输出到文件
        if (logFile.is_open()) {
            logFile << logStream.str() << std::endl;
        }
    }

    void info(const std::string& message) {
        log(INFO, message);
    }

    void warn(const std::string& message) {
        log(WARN, message);
    }

    void error(const std::string& message) {
        log(ERROR, message);
    }

    void fatal(const std::string& message) {
        log(FATAL, message);
    }

    void debug(const std::string& message) {
        log(DEBUG, message);
    }
};



