#pragma once

namespace game
{

class Game;
class TutorialManager;
class TutorialStep;

enum TutorialId : unsigned int;

class Tutorial
{
public:
    Tutorial(TutorialId tutId, Game * game);
    virtual ~Tutorial();

    unsigned int GetId() const;

    void AddStep(TutorialStep * step);

    bool IsDone() const;

    void Start();

    void SetPause(bool paused);
    bool IsPaused() const;

    virtual void OnStart();
    virtual void OnEnd();

    const TutorialManager * GetManager() const;

    void Update(float delta);

private:
    TutorialManager * mTutMan = nullptr;
    Game * mGame = nullptr;

    TutorialId mId;

    bool mDone = false;
    bool mPaused = false;
};

inline unsigned int Tutorial::GetId() const { return mId; }

inline bool Tutorial::IsDone() const { return mDone; }

inline bool Tutorial::IsPaused() const { return mPaused; }

inline const TutorialManager * Tutorial::GetManager() const { return mTutMan; }

} // namespace game
