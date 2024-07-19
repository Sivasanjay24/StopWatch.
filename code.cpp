#include <iostream>
#include <chrono>
#include <iomanip>
#include <string>
class Stopwatch {
public:
    Stopwatch() : running(false), elapsedTime(0) {}
    void start() {
        if (!running) {
            startTime = std::chrono::steady_clock::now();
            running = true;
        }
    }
    void stop() {
        if (running) {
            auto endTime = std::chrono::steady_clock::now();
            elapsedTime += std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
            running = false;
        }
    }
    void reset() {
        running = false;
        elapsedTime = 0;
    }
    long long getElapsedTime() const {
        if (running) {
            auto endTime = std::chrono::steady_clock::now();
            return elapsedTime + std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        }
        return elapsedTime;
    }
    std::string getFormattedElapsedTime() const {
        long long milliseconds = getElapsedTime();
        long long seconds = milliseconds / 1000;
        milliseconds %= 1000;
        long long minutes = seconds / 60;
        seconds %= 60;
        long long hours = minutes / 60;
        minutes %= 60;

        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << hours << ":"
            << std::setw(2) << std::setfill('0') << minutes << ":"
            << std::setw(2) << std::setfill('0') << seconds << "."
            << std::setw(3) << std::setfill('0') << milliseconds;
        return oss.str();
    }

private:
    std::chrono::time_point<std::chrono::steady_clock> startTime;
    bool running;
    long long elapsedTime;
};
void displayMenu() {
    std::cout << "Stopwatch Application\n";
    std::cout << "Commands:\n";
    std::cout << "start  - Start the stopwatch\n";
    std::cout << "stop   - Stop the stopwatch\n";
    std::cout << "reset  - Reset the stopwatch\n";
    std::cout << "time   - Display elapsed time\n";
    std::cout << "exit   - Exit the application\n";
}

int main() {
    Stopwatch stopwatch;
    std::string command;

    displayMenu();

    while (true) {
        std::cout << "\nEnter command: ";
        std::cin >> command;

        if (command == "start") {
            stopwatch.start();
            std::cout << "Stopwatch started.\n";
        } else if (command == "stop") {
            stopwatch.stop();
            std::cout << "Stopwatch stopped.\n";
        } else if (command == "reset") {
            stopwatch.reset();
            std::cout << "Stopwatch reset.\n";
        } else if (command == "time") {
            std::cout << "Elapsed time: " << stopwatch.getFormattedElapsedTime() << "\n";
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "Invalid command. Please try again.\n";
            displayMenu();
        }
    }

    return 0;
}
