#pragma once

namespace game
{

class Game;
class TutorialManager;
class TutorialStep;

class Tutorial
{
public:
    Tutorial(Game * game);
    virtual ~Tutorial();

    void AddStep(TutorialStep * step);

    bool IsDone() const;

    void Start();

    virtual void OnStart();
    virtual void OnEnd();

    void Update(float delta);

private:
    TutorialManager * mTutMan = nullptr;
    Game * mGame = nullptr;

    bool mDone = false;
};

inline bool Tutorial::IsDone() const { return mDone; }

} // namespace game
