#pragma once

namespace game
{

class TutorialManager;

class Tutorial
{
public:
    Tutorial();
    virtual ~Tutorial();

    bool IsDone() const;

    void Start();

    virtual void OnStart();
    virtual void OnEnd();

    void Update(float delta);

private:
    TutorialManager * mTutMan = nullptr;

    bool mDone = false;
};

inline bool Tutorial::IsDone() const { return mDone; }

} // namespace game
