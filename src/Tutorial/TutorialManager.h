#pragma once

#include <vector>

namespace game
{

class Screen;
class Tutorial;

enum TutorialId : unsigned int;
enum TutorialState : unsigned int;

class TutorialManager
{
public:
    TutorialManager();
    ~TutorialManager();

    TutorialState GetTutorialState(TutorialId tut);

    // -- ACTIVE TUTORIAL --
    bool CreateTutorial(TutorialId tutId, Screen * screen);
    void StartTutorial();
    void AbortTutorial();
    void SetTutorialPause(bool paused);

    const Tutorial * GetTutorial() const;
    bool HasActiveTutorial() const;

    void Update(float delta);

private:
    void SetTutorialState(TutorialId tut, TutorialState state);

private:
    std::vector<TutorialState> mTutorialsState;

    Tutorial * mActiveTutorial = nullptr;
};

inline const Tutorial * TutorialManager::GetTutorial() const { return mActiveTutorial; }

inline bool TutorialManager::HasActiveTutorial() const { return mActiveTutorial != nullptr; }

} // namespace game
