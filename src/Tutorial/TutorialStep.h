#pragma once

namespace game
{

class TutorialStep
{
public:
    virtual ~TutorialStep() = default;

    bool IsDone() const;

    virtual void SetPause(bool paused);
    bool IsPaused() const;

    virtual void OnStart();
    virtual void OnEnd();

    virtual void Update(float delta);

protected:
    void SetDone();

private:
    bool mDone = false;
    bool mPaused = false;
};

inline bool TutorialStep::IsDone() const { return mDone; }
inline void TutorialStep::SetDone() { mDone = true; }

inline bool TutorialStep::IsPaused() const { return mPaused; }

} // namespace game
