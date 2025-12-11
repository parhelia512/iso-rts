#pragma once

#include "GameObjectTypes.h"
#include "GameObjects/ObjectData.h"

#include <functional>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

namespace sgl
{
    namespace graphic { class ParticlesManager; }
}

namespace game
{

enum GameObjectActionType : unsigned int
{
    IDLE,

    // BASE
    BUILD_UNIT,

    // MINI UNIT
    SET_TARGET,

    // UNIT
    MOVE,
    CONQUER_CELL,
    CONQUER_STRUCTURE,
    ATTACK,
    BUILD_STRUCTURE,
    BUILD_WALL,
    HEAL,
    SPAWN,

    // WALL GATE
    TOGGLE_GATE,

    // GENERIC
    SELF_DESTRUCTION,

    NUM_OBJ_ACTIONS
};

class GameMap;
class GameObjectsGroup;
class IsoObject;
class Player;
class ScreenGame;
class Weapon;
struct GameMapCell;

enum PlayerFaction : unsigned int;

class GameObject
{
public:
    // -- OBJECT TYPE --
    static const GameObjectTypeId TYPE_NULL;

    static const GameObjectTypeId TYPE_BARRACKS;
    static const GameObjectTypeId TYPE_BASE;
    static const GameObjectTypeId TYPE_BASE_SPOT;
    static const GameObjectTypeId TYPE_BLOBS;
    static const GameObjectTypeId TYPE_BUNKER;
    static const GameObjectTypeId TYPE_DEFENSIVE_TOWER;
    static const GameObjectTypeId TYPE_DIAMONDS;
    static const GameObjectTypeId TYPE_HOSPITAL;
    static const GameObjectTypeId TYPE_LOOTBOX;
    static const GameObjectTypeId TYPE_MINI_UNIT1;
    static const GameObjectTypeId TYPE_MINI_UNIT2;
    static const GameObjectTypeId TYPE_MOUNTAINS;
    static const GameObjectTypeId TYPE_PRACTICE_TARGET;
    static const GameObjectTypeId TYPE_RADAR_STATION;
    static const GameObjectTypeId TYPE_RADAR_TOWER;
    static const GameObjectTypeId TYPE_RESEARCH_CENTER;
    static const GameObjectTypeId TYPE_RES_GEN_ENERGY;
    static const GameObjectTypeId TYPE_RES_GEN_ENERGY_SOLAR;
    static const GameObjectTypeId TYPE_RES_GEN_MATERIAL;
    static const GameObjectTypeId TYPE_RES_GEN_MATERIAL_EXTRACT;
    static const GameObjectTypeId TYPE_RES_STORAGE_BLOBS;
    static const GameObjectTypeId TYPE_RES_STORAGE_DIAMONDS;
    static const GameObjectTypeId TYPE_RES_STORAGE_ENERGY;
    static const GameObjectTypeId TYPE_RES_STORAGE_MATERIAL;
    static const GameObjectTypeId TYPE_ROCKS;
    static const GameObjectTypeId TYPE_SPAWN_TOWER;
    static const GameObjectTypeId TYPE_TEMPLE;
    static const GameObjectTypeId TYPE_TRADING_POST;
    static const GameObjectTypeId TYPE_TREES;
    static const GameObjectTypeId TYPE_UNIT_MEDIC1;
    static const GameObjectTypeId TYPE_UNIT_SCOUT1;
    static const GameObjectTypeId TYPE_UNIT_SOLDIER1;
    static const GameObjectTypeId TYPE_UNIT_SOLDIER2;
    static const GameObjectTypeId TYPE_UNIT_SPAWNER1;
    static const GameObjectTypeId TYPE_UNIT_SPAWNER2;
    static const GameObjectTypeId TYPE_UNIT_WORKER1;
    static const GameObjectTypeId TYPE_WALL;
    static const GameObjectTypeId TYPE_WALL_GATE;

    static const std::unordered_map<GameObjectTypeId, std::string> TITLES;
    static const std::unordered_map<GameObjectTypeId, std::string> DESCRIPTIONS;

    // -- OBJECT CATEGORY --
    static const GameObjectCategoryId CAT_NULL;

    static const GameObjectCategoryId CAT_COLLECTABLE;
    static const GameObjectCategoryId CAT_MINI_UNIT;
    static const GameObjectCategoryId CAT_RES_GENERATOR;
    static const GameObjectCategoryId CAT_RES_STORAGE;
    static const GameObjectCategoryId CAT_SCENE_OBJ;
    static const GameObjectCategoryId CAT_STRUCTURE;
    static const GameObjectCategoryId CAT_UNIT;

    // -- OBJECT VARIANT --
    static const GameObjectVariantId VAR_0;

    static std::string GetObjectTypeStr(const GameObjectTypeId type);

public:
    GameObject(const ObjectData & data);
    virtual ~GameObject();

    // GROUP
    bool IsInGroup() const;
    GameObjectsGroup * GetGroup() const;
    void SetGroup(GameObjectsGroup * g);
    void ClearGroup();

    void SetGameMap(GameMap * map);
    void SetParticlesManager(const sgl::graphic::ParticlesManager * partMan);
    void SetScreen(ScreenGame * screen);
    void SetOwner(Player * p);

    unsigned int GetObjectId() const;

    IsoObject * GetIsoObject() const;
    virtual void OnPositionChanged();

    bool IsStructure() const;
    bool CanBeConquered() const;

    bool CanBeCollected() const;

    bool IsSelected() const;
    void SetSelected(bool val);

    bool IsBusy() const;

    bool IsVisited() const;
    void SetVisited();

    bool IsVisible() const;
    void SetVisible(bool val);

    bool IsLinked() const;
    void SetLinked(bool val);

    bool IsStatic() const;

    bool IsDestroyed() const;

    const GameMapCell * GetCell() const;
    void SetCell(const GameMapCell * cell);

    int GetVisibilityLevel() const;

    int GetRow0() const;
    int GetCol0() const;
    int GetRow1() const;
    int GetCol1() const;

    unsigned int GetRows() const;
    unsigned int GetCols() const;

    PlayerFaction GetFaction() const;
    bool SetFaction(PlayerFaction f);
    bool IsFactionLocal() const;

    GameObjectTypeId GetObjectType() const;
    std::string GetObjectTypeStr() const;
    GameObjectCategoryId GetObjectCategory() const;
    GameObjectVariantId GetObjectVariant() const;
    void SetObjectVariant(GameObjectVariantId var);

    bool IsHealthMax() const;
    float GetHealth() const;
    float GetMaxHealth() const;
    void SumHealth(float val);

    bool IsEnergyMax() const;
    float GetEnergy() const;
    void SumEnergy(float val);
    float GetMaxEnergy() const;

    float GetEnergyForActionStep(GameObjectActionType action) const;
    bool HasEnergyForActionStep(GameObjectActionType action) const;
    void ActionStepCompleted(GameObjectActionType action);

    int GetExperience() const;
    int GetExperienceToNextLevel() const;
    int GetExperienceLevel() const;
    int GetMaxExperienceLevel() const;
    void SetExperience(int val);
    void SumExperience(int val);

    unsigned int AddFunctionOnValueChanged(const std::function<void()> & f);
    void RemoveFunctionOnValueChanged(unsigned int fId);

    // ATTRIBUTES
    int GetAttribute(ObjAttId attID) const;

    float GetSpeed() const;

    // WEAPON
    const Weapon * GetWeapon() const;
    void SetWeapon(Weapon * w);

    void SetAttackMode(AttackMode am);

    void Hit(float damage, PlayerFaction attacker, bool fatal);
    void SelfDestroy();

    GameObjectActionType GetActiveAction() const;
    void SetActiveAction(GameObjectActionType action);
    virtual void SetActiveActionToDefault();
    GameObjectActionType GetCurrentAction() const;
    void SetCurrentAction(GameObjectActionType action);

    virtual void OnNewTurn(PlayerFaction faction);

    virtual void Update(float delta);

protected:
    virtual void UpdateGraphics() = 0;

    virtual void OnFactionChanged();
    virtual void OnLinkedChanged();

    GameMap * GetGameMap() const;
    const sgl::graphic::ParticlesManager * GetParticlesManager() const;
    ScreenGame * GetScreen() const;
    Player * GetOwner() const;

    void SetStructure(bool val);
    void SetCanBeConquered(bool val);
    void SetStatic(bool val);

    void SetSpeed(float speed);

    void NotifyValueChanged();

    float GetTime(float maxTime, float attribute) const;

    void UpdateVisibilityLevel(float maxVal, float maxValLinked);
    void UpdateMaxEnergy(float maxVal);
    void UpdateMaxHealth(float maxVal);
    void UpdateRegenerationPower();

protected:
    static const unsigned int COLOR_FOW;
    static const unsigned int COLOR_VIS;

    std::vector<unsigned int> mObjColors;

    GameObjectVariantId mVariant = VAR_0;

    Weapon * mWeapon = nullptr;

private:
    // NOTE no boundary check, assuming valid action
    virtual float GetActionEnergyCost(GameObjectActionType action) const;
    // NOTE no boundary check, assuming valid action
    virtual float GetActionExperienceGain(GameObjectActionType action) const;

    void SetEnergy(float val);
    void SetMaxEnergy(float val);
    void SetRegenerationPower(float val);

    void SetMaxHealth(float max);
    void SetHealth(float val);

    void RestoreTurnEnergy();

    void SetDefaultColors();

private:
    static unsigned int counter;

    static const std::string TYPE_STR_BARRACKS;
    static const std::string TYPE_STR_BASE;
    static const std::string TYPE_STR_BASE_SPOT;
    static const std::string TYPE_STR_BLOBS;
    static const std::string TYPE_STR_BUNKER;
    static const std::string TYPE_STR_DEFENSIVE_TOWER;
    static const std::string TYPE_STR_DIAMONDS;
    static const std::string TYPE_STR_HOSPITAL;
    static const std::string TYPE_STR_LOOTBOX;
    static const std::string TYPE_STR_MINI_UNIT1;
    static const std::string TYPE_STR_MINI_UNIT2;
    static const std::string TYPE_STR_MOUNTAINS;
    static const std::string TYPE_STR_PRACTICE_TARGET;
    static const std::string TYPE_STR_RADAR_STATION;
    static const std::string TYPE_STR_RADAR_TOWER;
    static const std::string TYPE_STR_RESEARCH_CENTER;
    static const std::string TYPE_STR_RES_GEN_ENERGY;
    static const std::string TYPE_STR_RES_GEN_ENERGY_SOLAR;
    static const std::string TYPE_STR_RES_GEN_MATERIAL;
    static const std::string TYPE_STR_RES_GEN_MATERIAL_EXTRACT;
    static const std::string TYPE_STR_RES_STORAGE_BLOBS;
    static const std::string TYPE_STR_RES_STORAGE_DIAMONDS;
    static const std::string TYPE_STR_RES_STORAGE_ENERGY;
    static const std::string TYPE_STR_RES_STORAGE_MATERIAL;
    static const std::string TYPE_STR_ROCKS;
    static const std::string TYPE_STR_SPAWN_TOWER;
    static const std::string TYPE_STR_TEMPLE;
    static const std::string TYPE_STR_TRADING_POST;
    static const std::string TYPE_STR_TREES;
    static const std::string TYPE_STR_UNIT_MEDIC1;
    static const std::string TYPE_STR_UNIT_SCOUT1;
    static const std::string TYPE_STR_UNIT_SOLDIER1;
    static const std::string TYPE_STR_UNIT_SOLDIER2;
    static const std::string TYPE_STR_UNIT_SPAWNER1;
    static const std::string TYPE_STR_UNIT_SPAWNER2;
    static const std::string TYPE_STR_UNIT_WORKER1;
    static const std::string TYPE_STR_WALL;
    static const std::string TYPE_STR_WALL_GATE;

    static const std::unordered_map<GameObjectTypeId, std::string> TYPE_STR_MAP;

private:
    std::map<unsigned int, std::function<void()>> mOnValueChanged;

    std::unordered_map<ObjAttId, int> mAttributes;

    GameObjectsGroup * mGroup = nullptr;

    IsoObject * mIsoObj = nullptr;

    unsigned int mObjId;

    GameMap * mGameMap = nullptr;
    const sgl::graphic::ParticlesManager * mPartMan = nullptr;
    ScreenGame * mScreen = nullptr;
    Player * mOwner = nullptr;

    const GameMapCell * mCell = nullptr;

    GameObjectTypeId mType = TYPE_NULL;
    GameObjectCategoryId mCategory = CAT_NULL;

    GameObjectActionType mActiveAction = IDLE;
    GameObjectActionType mCurrAction = IDLE;

    PlayerFaction mFaction;

    unsigned int mRows = 1;
    unsigned int mCols = 1;

    int mVisLevel = 0;

    int mExpLevel = 0;
    int mExp = 0;
    int mExpToNextLvl = 1000;

    float mMaxEnergy = 100.f;
    float mEnergy = 100.f;
    float mEnergyRegPower = 1.f;
    float mMaxHealth = 100.f;
    float mHealth = 100.f;
    float mSpeed = 0.f;

    bool mStructure = false;
    // set to TRUE for elements that stay visible under FOGOW
    bool mStatic = false;

    bool mCanBeConq = false;

    bool mSelected = false;

    bool mVisible = true;
    bool mVisited = false;
    bool mLinked = false;
};

inline bool GameObject::IsInGroup() const { return mGroup != nullptr; }
inline GameObjectsGroup * GameObject::GetGroup() const { return mGroup; }

inline void GameObject::SetGameMap(GameMap * map) { mGameMap = map; }
inline void GameObject::SetParticlesManager(const sgl::graphic::ParticlesManager * pm) { mPartMan = pm; }
inline void GameObject::SetScreen(ScreenGame * screen) { mScreen = screen; }

inline unsigned int GameObject::GetObjectId() const { return mObjId; }

inline IsoObject * GameObject::GetIsoObject() const { return mIsoObj; }

inline bool GameObject::IsStructure() const { return mStructure; }

inline bool GameObject::CanBeConquered() const { return mCanBeConq; }

inline bool GameObject::CanBeCollected() const { return GameObject::CAT_COLLECTABLE == mCategory; }

inline bool GameObject::IsSelected() const { return mSelected; }

inline bool GameObject::IsBusy() const { return mCurrAction != IDLE; }

inline bool GameObject::IsVisited() const { return mVisited; }
inline void GameObject::SetVisited() { mVisited = true; }

inline bool GameObject::IsVisible() const { return mVisible; }

inline bool GameObject::IsLinked() const { return mLinked; }

inline bool GameObject::IsStatic() const { return mStatic; }

inline bool GameObject::IsDestroyed() const
{
    const float minH = 0.01f;
    return mHealth < minH;
}

inline const GameMapCell * GameObject::GetCell() const { return mCell; }

inline int GameObject::GetVisibilityLevel() const { return mVisLevel; }

inline GameObjectTypeId GameObject::GetObjectType() const { return mType; }

inline std::string GameObject::GetObjectTypeStr() const
{
    return GetObjectTypeStr(mType);
}

inline GameObjectCategoryId GameObject::GetObjectCategory() const { return mCategory; }

inline GameObjectVariantId GameObject::GetObjectVariant() const { return mVariant; }

inline unsigned int GameObject::GetRows() const { return mRows; }
inline unsigned int GameObject::GetCols() const { return mCols; }

inline PlayerFaction GameObject::GetFaction() const { return mFaction; }

inline GameMap * GameObject::GetGameMap() const { return mGameMap; }
inline const sgl::graphic::ParticlesManager * GameObject::GetParticlesManager() const { return mPartMan; }
inline ScreenGame * GameObject::GetScreen() const { return mScreen; }
inline Player * GameObject::GetOwner() const { return mOwner; }

inline void GameObject::SetStructure(bool val) { mStructure = val; }
inline void GameObject::SetCanBeConquered(bool val) { mCanBeConq = val; }
inline void GameObject::SetStatic(bool val) { mStatic = val; }

inline float GameObject::GetHealth() const { return mHealth; }
inline float GameObject::GetMaxHealth() const { return mMaxHealth; }

inline float GameObject::GetEnergy() const { return mEnergy; }
inline float GameObject::GetMaxEnergy() const { return mMaxEnergy; }

inline float GameObject::GetEnergyForActionStep(GameObjectActionType action) const
{
    if(action < NUM_OBJ_ACTIONS)
        return GetActionEnergyCost(action);
    else
        return 0.f;
}

inline int GameObject::GetExperience() const { return mExp; }
inline int GameObject::GetExperienceToNextLevel() const { return mExpToNextLvl; }
inline int GameObject::GetExperienceLevel() const { return mExpLevel; }
inline int GameObject::GetMaxExperienceLevel() const { return 10; }

inline void GameObject::SetSpeed(float speed) { mSpeed = speed; }

inline const Weapon * GameObject::GetWeapon() const { return mWeapon; }

inline GameObjectActionType GameObject::GetActiveAction() const { return mActiveAction; }
inline void GameObject::SetActiveAction(GameObjectActionType action) { mActiveAction = action; }
inline GameObjectActionType GameObject::GetCurrentAction() const { return mCurrAction; }
inline void GameObject::SetCurrentAction(GameObjectActionType action) { mCurrAction = action; }

inline void GameObject::SetMaxEnergy(float val) { mMaxEnergy = val; }

inline void GameObject::SetMaxHealth(float max) { mMaxHealth = max; }

inline void GameObject::SetRegenerationPower(float val)
{
    const float maxVal = 1.f;

    mEnergyRegPower = val > maxVal ? maxVal : val;
}

} // namespace game
