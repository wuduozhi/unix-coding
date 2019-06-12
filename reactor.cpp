#include <sys/epoll.h>
#include <unistd.h>
#include <iostream>
#include <array>
#include <limits>
#include <functional>
#include <unordered_map>
#include <string>
#include <utility>

class Epoll {
 public:
    static const int NO_FLAGS = 0;
    static const int BLOCK_INDEFINITELY = -1;
    static const int MAX_EVENTS = 1;

    Epoll() {
        fileDescriptor = epoll_create1(NO_FLAGS);

        event.data.fd = STDIN_FILENO;
        event.events = EPOLLIN | EPOLLPRI;
    }

    int control() {
        return epoll_ctl(fileDescriptor, EPOLL_CTL_ADD, STDIN_FILENO, &event);
    }

    int wait() {
        return epoll_wait(
                fileDescriptor,
                events.begin(),
                MAX_EVENTS,
                BLOCK_INDEFINITELY);
    }

    ~Epoll() {
        close(fileDescriptor);
    }

 private:
    int fileDescriptor;

    struct epoll_event event;
    std::array<epoll_event, MAX_EVENTS> events{};
};

class Reactor {
 public:
    Reactor() {
        epoll.control();
    }

    void addHandler(std::string event, std::function<void()> callback) {
        handlers.emplace(std::move(event), std::move(callback));
    }

    void run() {
        while (true) {
            int numberOfEvents = wait();

            for (int i = 0; i < numberOfEvents; ++i) {
                std::string input;
                std::getline(std::cin, input);

                try {
                    handlers.at(input)();
                } catch (const std::out_of_range& e) {
                    std::cout << "no handler for " << input << '\n';
                }
            }
        }
    }

 private:
    std::unordered_map<std::string, std::function<void()>> handlers{};
    Epoll epoll;

    int wait() {
        int numberOfEvents = epoll.wait();
        return numberOfEvents;
    }
};

int main() {
    Reactor reactor;

    reactor.addHandler("one", [](){
        std::cout << "one handler called!" << '\n';
    });
    reactor.addHandler("two", [](){
        std::cout << "two handler called!" << '\n';
    });

    reactor.run();
}
