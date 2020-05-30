#pragma once

namespace lib
{
namespace core
{

class EventDispatcher;
class EventListener;

class Application
{
public:
    Application(int argc, char * argv[]);
    virtual ~Application();

    void AddEventListener(EventListener * listener);
    void RemoveEventListener(EventListener * listener);

    void Run();

    void Exit();

private:
    virtual void ProcessArguments(int argc, char * argv[]);

    virtual void Update() = 0;

private:
    EventDispatcher * mEventDispatcher = nullptr;

    bool mRunning = false;

};

} // namespace core
} // namespace lib
