#pragma once

namespace sgl
{
    namespace graphic { class ParticlesManager; }
}

namespace game
{

class Game;
class GameMap;
class Player;
class ScreenGame;

class ObjectInitData
{
public:
    ObjectInitData(const Game * game, GameMap * map,
                   const sgl::graphic::ParticlesManager * pm,
                   Player * p, ScreenGame * screen);

    const Game * GetGame() const;
    GameMap * GetGameMap() const;
    const sgl::graphic::ParticlesManager * GetParticlesManager() const;
    Player * GetPlayer() const;
    ScreenGame * GetScreen() const;

private:
    const Game * mGame;
    GameMap * mGameMap = nullptr;
    const sgl::graphic::ParticlesManager * mPartMan;
    Player * mPlayer = nullptr;
    ScreenGame * mScreen = nullptr;
};

inline ObjectInitData::ObjectInitData(const Game * game, GameMap * map,
                                      const sgl::graphic::ParticlesManager * pm,
                                      Player * p, ScreenGame * screen)
    : mGame(game)
    , mGameMap(map)
    , mPartMan(pm)
    , mPlayer(p)
    , mScreen(screen)
{
}

inline const Game * ObjectInitData::GetGame() const { return mGame; }

inline GameMap * ObjectInitData::GetGameMap() const { return mGameMap; }

inline const sgl::graphic::ParticlesManager * ObjectInitData::GetParticlesManager() const
{
    return mPartMan;
}

inline Player * ObjectInitData::GetPlayer() const { return mPlayer; }

inline ScreenGame * ObjectInitData::GetScreen() const { return mScreen; }

} // namespace game
