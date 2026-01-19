#include "PlayerAI.h"

#include "GameConstants.h"
#include "GameMap.h"
#include "Player.h"
#include "GameObjects/Base.h"
#include "GameObjects/ObjectsDataRegistry.h"
#include "GameObjects/ResourceGenerator.h"
#include "GameObjects/Structure.h"
#include "GameObjects/Unit.h"

#include <sgl/utilities/LoadedDie.h>

#include <algorithm>
#include <iostream>

namespace
{
constexpr int MAX_PRIORITY = 100;
}

namespace game
{

PlayerAI::PlayerAI(Player * player, const ObjectsDataRegistry * dataReg)
    : mPlayer(player)
    , mDataReg(dataReg)
{
}

PlayerAI::~PlayerAI()
{
    ClearActionsTodo();
    ClearActionsDone();
}

void PlayerAI::DecideNextAction()
{
    // TODO track time and keep it into consideration when defining priorities
    // TODO use memory pools for actions
    ClearActionsTodo();
    ClearActionsDone();

    PrepareData();

    UpdatePriorityRange();

    AddActions();
}

void PlayerAI::PrepareData()
{
    // clear data
    mCollectables.clear();
    mResGenerators.clear();
    mStructures.clear();
    mTrees.clear();
    mUnits.clear();

    // collect data
    const std::vector<GameObject *> & objects = mGm->GetObjects();

    for(GameObject * obj : objects)
    {
        const GameObjectCategoryId objCat = obj->GetObjectCategory();

        // store structures
        if(obj->IsStructure())
        {
            mStructures.push_back(obj);

            // store resource generators
            if(objCat == ObjectData::CAT_RES_GENERATOR)
                mResGenerators.push_back(obj);
        }
        else if(obj->GetObjectCategory() == ObjectData::CAT_UNIT)
            mUnits.push_back(obj);
        else if(obj->CanBeCollected())
            mCollectables.push_back(obj);
        else if(obj->GetObjectType() == ObjectData::TYPE_TREES)
            mTrees.push_back(obj);
    }
}

void PlayerAI::UpdatePriorityRange()
{
    // TODO define min priority based on current situation

    mMinPriority = 50;
}

void PlayerAI::AddActions()
{
    // STRUCTURES
    for(unsigned int i = 0; i < mPlayer->GetNumStructures(); ++i)
    {
        Structure * s = mPlayer->GetStructure(i);
        AddActionsStructure(s);
    }

    // UNITS
    for(unsigned int i = 0; i < mPlayer->GetNumUnits(); ++i)
    {
        Unit * u = mPlayer->GetUnit(i);
        AddActionsUnit(u);
    }

    // KEEP THIS LAST
    AddActionEndTurn();
}

const ActionAI * PlayerAI::GetNextActionTodo()
{
    // return NOP action if queue is empty
    if(mActionsTodo.empty())
        return nullptr;

    // return top action
    return PopAction();
}

void PlayerAI::HandleObjectDestroyed(GameObject * obj)
{
    HandleObjectDestroyedInTodo(obj);
    HandleObjectDestroyedInDoing(obj);
}

bool PlayerAI::IsActionHighestPriorityForObject(const ActionAI * action) const
{
    auto it = mActionsDoing.begin();

    while(it != mActionsDoing.end())
    {
        const ActionAI * a = *it;

        if(a->ObjSrc == action->ObjSrc)
            return action->priority > a->priority;
        else
            ++it;
    }

    return true;
}

void PlayerAI::CancelObjectAction(const GameObject * obj)
{
    auto it = mActionsDoing.begin();

    while(it != mActionsDoing.end())
    {
        const ActionAI * action = *it;

        if(obj == action->ObjSrc)
        {
            mActionsDoing.erase(it);

            PrintdActionDebug("PlayerAI::CancelObjectActions - ACTION CANCELLED", action);

            delete action;

            return ;
        }
        else
            ++it;
    }

    std::cout << "PlayerAI::CancelObjectActions - can't find any action for object "
              << obj->GetObjectId() << std::endl;
}

void PlayerAI::CancelAction(const ActionAI * action)
{
    auto it = mActionsDoing.begin();

    while(it != mActionsDoing.end())
    {
        if(action->actId == (*it)->actId)
        {
            mActionsDoing.erase(it);

            PrintdActionDebug("PlayerAI::CancelAction - ACTION CANCELLED", action);

            delete action;

            return ;
        }
        else
            ++it;
    }

    PrintdActionDebug("PlayerAI::CancelAction - can't find action", action);

    delete action;
}

void PlayerAI::SetActionDone(const ActionAI * action)
{
    auto it = mActionsDoing.begin();

    while(it != mActionsDoing.end())
    {
        if(action->actId == (*it)->actId)
        {
            mActionsDoing.erase(it);

            mActionsDone.push_back(action);

            PrintdActionDebug("PlayerAI::SetActionDone | ACTION DONE", action);

            return ;
        }
        else
            ++it;
    }

    std::cout << "PlayerAI::SetActionDone - ACTION DONE - can't find action" << std::endl;
}

void PlayerAI::ClearActionsDone()
{
    for(const ActionAI * a : mActionsDone)
        delete a;

    mActionsDone.clear();
}

void PlayerAI::ClearActionsTodo()
{
    for(ActionAI * a : mActionsTodo)
        delete a;

    mActionsTodo.clear();
}

void PlayerAI::HandleObjectDestroyedInTodo(GameObject * obj)
{
    auto it = mActionsTodo.begin();

    while(it != mActionsTodo.end())
    {
        const ActionAI * action = *it;

        if(action->ObjSrc == obj || action->ObjDst == obj)
        {
            delete action;
            mActionsTodo.erase(it);
            break;
        }
        else
            ++it;
    }
}

void PlayerAI::HandleObjectDestroyedInDoing(GameObject * obj)
{
    auto it = mActionsDoing.begin();

    while(it != mActionsDoing.end())
    {
        const ActionAI * action = *it;

        if(action->ObjSrc == obj || action->ObjDst == obj)
        {
            delete action;
            mActionsDoing.erase(it);
            break;
        }
        else
            ++it;
    }
}

void PlayerAI::PushAction(ActionAI * action)
{
    mActionsTodo.emplace_back(action);
    std::push_heap(mActionsTodo.begin(), mActionsTodo.end(), ActionAiComp{});
}

const ActionAI * PlayerAI::PopAction()
{
    std::pop_heap(mActionsTodo.begin(), mActionsTodo.end(), ActionAiComp{});

    ActionAI * elem = mActionsTodo.back();
    mActionsTodo.pop_back();

    return elem;
}

void PlayerAI::AddNewAction(ActionAI * action)
{
    // assign unique ID to action
    static unsigned int num = 0;

    action->actId = ++num;

    // clamp priority
    if(action->priority > MAX_PRIORITY)
        action->priority = MAX_PRIORITY;

    PrintdActionDebug("PlayerAI::AddNewAction | ADDED NEW ACTION", action);

    // NOTE not checking existing actions for now as all actions should be unique
    // as they are created by different objects (at least the ObjSrc is different)
    PushAction(action);
}

void PlayerAI::AddActionEndTurn()
{
    // create action
    auto action = new ActionAI;
    action->type = AIA_END_TURN;
    action->priority = MAX_PRIORITY;

    // immediately push action if there's nothing else to do
    if(mActionsTodo.empty())
    {
        PushAction(action);
        return ;
    }

    const float c = 100.f;

    // consider turn energy
    const float energyLeftTurn = mPlayer->GetTurnEnergy() * c / mPlayer->GetTurnMaxEnergy();

    // consider total units energy
    float totEnergy = 0.f;
    float totMaxEnergy = 0.f;

    for(GameObject * obj : mUnits)
    {
        totEnergy += obj->GetEnergy();
        totMaxEnergy += obj->GetMaxEnergy();
    }

    const float energyLeftUnits = totEnergy * c / totMaxEnergy;

    // consider total structures energy
    totEnergy = 0.f;
    totMaxEnergy = 0.f;

    for(GameObject * obj : mUnits)
    {
        // only consider structure that have AI actions
        if(obj->GetObjectType() == ObjectData::TYPE_BASE)
        {
            totEnergy += obj->GetEnergy();
            totMaxEnergy += obj->GetMaxEnergy();
        }
    }

    const float energyLeftStructs = totEnergy * c / totMaxEnergy;

    // combine units and structure energy left
    const unsigned int numUnits = mPlayer->GetNumUnits();
    const unsigned int maxUnits = mPlayer->GetMaxUnits();
    const float unitsProportion = (static_cast<float>(numUnits) / static_cast<float>(maxUnits));
    const float facUnits0 = 0.5f;
    const float facUnitsVar = 0.3f * unitsProportion;
    const float facUnits = facUnits0 + facUnitsVar;
    const float factStructs = 1.f - facUnits;
    const float energyLeftObjs = energyLeftUnits * facUnits + energyLeftStructs * factStructs;

    // decrease priority base on global energy left (turn + objects)
    const float facTurn = 0.5f;
    const float facObjs = 1.f - facTurn;
    const int decPriority = std::roundf(facTurn * energyLeftTurn + facObjs * energyLeftObjs);
    action->priority -= decPriority;

    // push action if above priority threshold
    if(action->priority >= mMinPriority)
        PushAction(action);
    // action not added
    else
        delete action;
}

void PlayerAI::AddActionsStructure(Structure * s)
{
    // upgrade when possible
    AddActionStructureUpgrade(s);

    // type specific actions
    const GameObjectTypeId objType = s->GetObjectType();

    if(objType == ObjectData::TYPE_BASE)
        AddActionBaseCreateUnit(s);
    else if (objType == ObjectData::TYPE_BARRACKS)
        AddActionBarrackCreateUnit(s);
}

void PlayerAI::AddActionBaseCreateUnit(Structure * base)
{
    const unsigned int numUnits = mPlayer->GetNumUnits();
    const unsigned int limitUnits = mPlayer->GetMaxUnits();

    // can't build more units -> exit
    if(numUnits >= limitUnits)
        return ;

    // DECIDE UNIT TYPE
    const auto availableUnits = mPlayer->GetAvailableUnits();

    std::vector<GameObjectTypeId> types;

    for(GameObjectTypeId t : availableUnits)
    {
        const ObjectData & data = mDataReg->GetObjectData(t);

        if(OCU_WORKER == data.GetClass())
            types.push_back(t);
    }

    // try to create one
    AddActionCreateUnit(base, types);
}

void PlayerAI::AddActionBarrackCreateUnit(Structure * barrack)
{
    const unsigned int numUnits = mPlayer->GetNumUnits();
    const unsigned int limitUnits = mPlayer->GetMaxUnits();

    // can't build more units -> exit
    if(numUnits >= limitUnits)
        return ;

    // DECIDE UNIT TYPE
    const auto availableUnits = mPlayer->GetAvailableUnits();

    std::vector<GameObjectTypeId> types;

    for(GameObjectTypeId t : availableUnits)
    {
        const ObjectData & data = mDataReg->GetObjectData(t);

        if(OCU_SOLDIER == data.GetClass())
            types.push_back(t);
    }

    // try to create one
    AddActionCreateUnit(barrack, types);
}

void PlayerAI::AddActionStructureUpgrade(Structure * s)
{
    if(!s->CanBeUpgraded())
        return ;

    // define importance of each attribute for this object
    const int weights[] =
    {
        8, 9, 0, 6, 8, 7, 0, 0, 0, 0, 0, 6, 9
    };

    static_assert(sizeof(weights) / sizeof(int) == NUM_BASIC_ATTRIBUTES);

    AddActionUpgrade(s, weights, AIA_UPGRADE_STRUCTURE);
}

void PlayerAI::AddActionsUnit(Unit * u)
{
    // upgrade immediatly when possible
    AddActionUnitUpgrade(u);

    // ATTACK
    if(u->CanAttack())
    {
        AddActionUnitAttackEnemyUnit(u);
        AddActionUnitAttackTrees(u);
    }

    if(u->CanConquer())
    {
        // CONNECT STRUCTURES
        AddActionUnitConnectStructure(u);

        // CONQUEST RESOURCE GENERATORS
        AddActionUnitConquerResGen(u, RES_ENERGY);
        AddActionUnitConquerResGen(u, RES_MATERIAL1);
    }

    // BUILD
    if(u->CanBuild())
    {
        AddActionUnitBuildStructure(u);
    }

    // COLLECTABLES
    AddActionUnitCollectBlobs(u);
    AddActionUnitCollectDiamonds(u);
    AddActionUnitCollectLootbox(u);
}

void PlayerAI::AddActionUnitAttackEnemyUnit(Unit * u)
{
    // nothing to do if there's no units on the map
    if(mUnits.empty())
        return ;

    const PlayerFaction faction = mPlayer->GetFaction();
    const unsigned int numUnits = mUnits.size();

    // check if there's any unit to shoot at
    const int maxDist = GetMaxDistanceForObject(u);

    unsigned int bestUnitInd = numUnits;
    int minDist = maxDist;
    int priority = MAX_PRIORITY;

    for(unsigned int i = 0; i < numUnits; ++i)
    {
        auto unit = static_cast<Unit *>(mUnits[i]);

        const PlayerFaction unitFaction = unit->GetFaction();

        // skip own faction units
        if(unitFaction == faction)
            continue;

        // skip targets out of range
        if(!u->IsTargetAttackInRange(unit))
            continue;

        // basic logic, attack closest one
        const int dist = mGm->ApproxDistance(u, unit);

        if(dist < minDist)
        {
            minDist = dist;
            bestUnitInd = i;
        }
    }

    // didn't find any
    if(bestUnitInd == numUnits)
        return ;

    // decrease priority based on unit's energy
    const float bonusEnergy = -5.f;
    priority += GetUnitPriorityBonusEnergy(u, bonusEnergy);

    // decrease priority based on unit's health
    const float bonusHealth = -10.f;
    priority += GetUnitPriorityBonusHealth(u, bonusHealth);

    // can't find something that's worth an action
    if(priority < mMinPriority)
        return ;

    auto action = new ActionAI;
    action->type = AIA_UNIT_ATTACK_ENEMY_UNIT;
    action->ObjSrc = u;
    action->ObjDst = mUnits[bestUnitInd];
    action->priority = priority;

    // push action to the queue
    AddNewAction(action);
}

void PlayerAI::AddActionUnitAttackTrees(Unit * u)
{
    // DEFINE INITIAL PRIORITY
    int priority = MAX_PRIORITY;

    // decrease priority based on unit's energy
    const float bonusEnergy = -40.f;
    priority += GetUnitPriorityBonusEnergy(u, bonusEnergy);

    // decrease priority based on unit's health
    const float bonusHealth = -5.f;
    priority += GetUnitPriorityBonusHealth(u, bonusHealth);

    // already below current priority threshold
    if(priority < mMinPriority)
        return ;

    // FIND TREE
    if(mTrees.empty())
        return ;

    const unsigned int numTrees = mTrees.size();
    const int maxDist = mGm->GetNumRows() * mGm->GetNumCols();
    const Base * base = mPlayer->GetBase();

    if(nullptr == base)
        return ;

    int minDist = maxDist;
    unsigned int bestInd = numTrees;

    for(unsigned int ind = 0; ind < numTrees; ++ind)
    {
        const GameObject * tree = mTrees[ind];

        int dist = mGm->ApproxDistance(base, tree);

        if(dist < minDist)
        {
            minDist = dist;
            bestInd = ind;
        }
    }

    // couldn't find any
    if(numTrees == bestInd)
        return ;

    // consider distance from base for priority
    const float bonusDistBase = -1.f;
    priority += std::roundf(bonusDistBase * minDist);

    // bonus distance from unit
    const bool inRange = u->IsTargetAttackInRange(mTrees[bestInd]);

    const float bonusDistUnit = inRange ? -10.f : -20.f;
    priority += GetUnitPriorityBonusDistance(u, minDist, bonusDistUnit);

    // can't find something that's worth an action
    if(priority < mMinPriority)
        return ;

    auto action = new ActionAI;
    action->type = AIA_UNIT_ATTACK_TREES;
    action->ObjSrc = u;
    action->ObjDst = mTrees[bestInd];
    action->priority = priority;

    // push action to the queue
    AddNewAction(action);
}

void PlayerAI::AddActionUnitBuildStructure(Unit * u)
{
    // DEFINE INITIAL PRIORITY
    int priority = MAX_PRIORITY;

    // decrease priority based on unit's energy
    const float bonusEnergy = -30.f;
    priority += GetUnitPriorityBonusEnergy(u, bonusEnergy);

    // decrease priority based on unit's health
    const float bonusHealth = -5.f;
    priority += GetUnitPriorityBonusHealth(u, bonusHealth);

    // decrease priority based on distance from Base
    const GameObject * base = mPlayer->GetBase();
    const int distBase = mGm->ApproxDistance(u, base);
    const int maxDist = GetMaxDistanceForObject(u);
    const float bonusDistBase = -15.f;
    priority += std::roundf(bonusDistBase * distBase / maxDist);

    // already below current priority threshold
    if(priority < mMinPriority)
        return ;

    // RESOURCE GENERATORS
    if(mPlayer->IsStructureAvailable(ObjectData::TYPE_RES_GEN_ENERGY_SOLAR))
        AddActionUnitBuildResourceGenerator(u, RES_ENERGY, priority);
    if(mPlayer->IsStructureAvailable(ObjectData::TYPE_RES_GEN_MATERIAL_EXTRACT))
        AddActionUnitBuildResourceGenerator(u, RES_MATERIAL1, priority);

    // RESOURCE STORAGE
    if(mPlayer->IsStructureAvailable(ObjectData::TYPE_RES_STORAGE_ENERGY))
        AddActionUnitBuildResourceStorage(u, RES_ENERGY, priority);
    if(mPlayer->IsStructureAvailable(ObjectData::TYPE_RES_STORAGE_MATERIAL))
        AddActionUnitBuildResourceStorage(u, RES_MATERIAL1, priority);
    if(mPlayer->IsStructureAvailable(ObjectData::TYPE_RES_STORAGE_BLOBS))
        AddActionUnitBuildResourceStorage(u, RES_BLOBS, priority);
    if(mPlayer->IsStructureAvailable(ObjectData::TYPE_RES_STORAGE_DIAMONDS))
        AddActionUnitBuildResourceStorage(u, RES_DIAMONDS, priority);

    // UNIT CREATION
    if(mPlayer->IsStructureAvailable(ObjectData::TYPE_BARRACKS))
        AddActionUnitBuildUnitCreator(u, ObjectData::TYPE_BARRACKS, priority);
    if(mPlayer->IsStructureAvailable(ObjectData::TYPE_HOSPITAL))
        AddActionUnitBuildUnitCreator(u, ObjectData::TYPE_HOSPITAL, priority);

    // TECH
    if(mPlayer->IsStructureAvailable(ObjectData::TYPE_RESEARCH_CENTER))
        AddActionUnitBuildResearchCenter(u, priority);
    if(mPlayer->IsStructureAvailable(ObjectData::TYPE_RADAR_STATION))
        AddActionUnitBuildRadarStructure(u, ObjectData::TYPE_RADAR_STATION, priority);
    if(mPlayer->IsStructureAvailable(ObjectData::TYPE_RADAR_TOWER))
        AddActionUnitBuildRadarStructure(u, ObjectData::TYPE_RADAR_TOWER, priority);

    // OTHER
    if(mPlayer->IsStructureAvailable(ObjectData::TYPE_PRACTICE_TARGET))
        AddActionUnitBuildPracticeTarget(u, priority);
}

void PlayerAI::AddActionUnitBuildUnitCreator(Unit * u, GameObjectTypeId structType, int priority0)
{
    // check object type is supported
    if(structType != ObjectData::TYPE_BARRACKS && structType != ObjectData::TYPE_HOSPITAL)
        return ;

    // no need to build these structures more than once
    if(mPlayer->HasStructure(structType))
        return ;

    // not enough resources to build
    if(!HasPlayerResourcesToBuild(structType))
        return ;

    // can't build more units -> exit
    const unsigned int numUnits = mPlayer->GetNumUnits();
    const unsigned int limitUnits = mPlayer->GetMaxUnits();

    if(numUnits >= limitUnits)
        return ;

    int priority = priority0;

    // the more units exist the higher the priority as no unit can be created yet
    const std::unordered_map<GameObjectTypeId, float> bonusUnits
    {
        {ObjectData::TYPE_BARRACKS , 30.f},
        {ObjectData::TYPE_HOSPITAL , 15.f},
    };

    priority += std::roundf(bonusUnits.at(structType) * numUnits / limitUnits);

    // reduce priority based on available resources
    const float bonusRes = -5.f;
    priority += GetPriorityBonusStructureBuildCost(structType, bonusRes);

    // check if below current priority threshold
    if(priority < mMinPriority)
        return ;

    // CREATE ACTION
    auto action = new ActionAIBuildStructure;
    action->type = AIA_UNIT_BUILD_STRUCTURE;
    action->ObjSrc = u;
    action->priority = priority;
    action->structType = structType;

    // push action to the queue
    AddNewAction(action);
}

void PlayerAI::AddActionUnitBuildResourceGenerator(Unit * u, ResourceType resType, int priority0)
{
    // resource not supported
    if(resType != RES_ENERGY && resType != RES_MATERIAL1)
        return ;

    const GameObjectTypeId structTypes[] =
    {
        ObjectData::TYPE_RES_GEN_ENERGY_SOLAR,
        ObjectData::TYPE_RES_GEN_MATERIAL_EXTRACT
    };

    const GameObjectTypeId structType = structTypes[resType];

    // not enough resources to build
    if(!HasPlayerResourcesToBuild(structType))
        return ;

    int priority = priority0;

    // decrease priority based on current resource level (high level -> lower priority)
    const Player::Stat ps[] =
    {
        Player::ENERGY,
        Player::MATERIAL,
    };

    const StatValue & res = mPlayer->GetStat(ps[resType]);

    const int resCur = res.GetValue();
    const int resMax = res.GetMax();

    const float bonusGen = -35.f;
    priority += std::roundf(bonusGen * resCur / resMax);

    // reduce priority based on available resources
    const float bonusRes = -5.f;
    priority += GetPriorityBonusStructureBuildCost(structType, bonusRes);

    // check if below current priority threshold
    if(priority < mMinPriority)
        return ;

    // CREATE ACTION
    auto action = new ActionAIBuildStructure;
    action->type = AIA_UNIT_BUILD_STRUCTURE;
    action->ObjSrc = u;
    action->priority = priority;
    action->structType = structType;

    // push action to the queue
    AddNewAction(action);
}

void PlayerAI::AddActionUnitBuildResourceStorage(Unit * u, ResourceType resType, int priority0)
{
    const GameObjectTypeId structTypes[] =
    {
        ObjectData::TYPE_RES_STORAGE_ENERGY,
        ObjectData::TYPE_RES_STORAGE_MATERIAL,
        ObjectData::TYPE_RES_STORAGE_DIAMONDS,
        ObjectData::TYPE_RES_STORAGE_BLOBS,
    };

    const GameObjectTypeId structType = structTypes[resType];

    // not enough resources to build
    if(!HasPlayerResourcesToBuild(structType))
        return ;

    int priority = priority0;

    // decrease priority based on current storage level
    const Player::Stat ps[] =
    {
        Player::ENERGY,
        Player::MATERIAL,
        Player::DIAMONDS,
        Player::BLOBS
    };

    const StatValue & res = mPlayer->GetStat(ps[resType]);

    const int resCur = res.GetValue();
    const int resMax = res.GetMax();
    const int resSto = resMax - resCur;

    const float bonusStorage = -30.f;
    priority += std::roundf(bonusStorage * resSto / resMax);

    // reduce priority based on available resources
    const float bonusRes = -5.f;
    priority += GetPriorityBonusStructureBuildCost(structType, bonusRes);

    // reduce priority based on same existing structures
    const float bonusSameStruct = -15.f;
    priority += GetPriorityBonusSameStructureCreated(structType, bonusSameStruct);

    // check if below current priority threshold
    if(priority < mMinPriority)
        return ;

    // CREATE ACTION
    auto action = new ActionAIBuildStructure;
    action->type = AIA_UNIT_BUILD_STRUCTURE;
    action->ObjSrc = u;
    action->priority = priority;
    action->structType = structType;

    // push action to the queue
    AddNewAction(action);
}

void PlayerAI::AddActionUnitBuildResearchCenter(Unit * u, int priority0)
{
    const GameObjectTypeId structType = ObjectData::TYPE_RESEARCH_CENTER;

    // no need to build these structures more than once
    if(mPlayer->HasStructure(structType))
        return ;

    // not enough resources to build
    if(!HasPlayerResourcesToBuild(structType))
        return ;

    int priority = priority0;

    // reduce priority based on available resources
    const float bonusRes = -10.f;
    priority += GetPriorityBonusStructureBuildCost(structType, bonusRes);

    // check if below current priority threshold
    if(priority < mMinPriority)
        return ;

    // CREATE ACTION
    auto action = new ActionAIBuildStructure;
    action->type = AIA_UNIT_BUILD_STRUCTURE;
    action->ObjSrc = u;
    action->priority = priority;
    action->structType = structType;

    // push action to the queue
    AddNewAction(action);
}

void PlayerAI::AddActionUnitBuildPracticeTarget(Unit * u, int priority0)
{
    const GameObjectTypeId structType = ObjectData::TYPE_PRACTICE_TARGET;

    // not enough resources to build
    if(!HasPlayerResourcesToBuild(structType))
        return ;

    int priority = priority0;

    // reduce priority based on available resources
    const float bonusRes = -15.f;
    priority += GetPriorityBonusStructureBuildCost(structType, bonusRes);

    // reduce priority based on number or existing structure
    const float bonusExist = -10.f;
    priority += bonusExist * mPlayer->GetNumStructuresByType(structType);

    // check if below current priority threshold
    if(priority < mMinPriority)
        return ;

    // CREATE ACTION
    auto action = new ActionAIBuildStructure;
    action->type = AIA_UNIT_BUILD_STRUCTURE;
    action->ObjSrc = u;
    action->priority = priority;
    action->structType = structType;

    // push action to the queue
    AddNewAction(action);
}

void PlayerAI::AddActionUnitBuildRadarStructure(Unit * u, GameObjectTypeId structType, int priority0)
{
    // check object type is supported
    if(structType != ObjectData::TYPE_RADAR_STATION &&
       structType != ObjectData::TYPE_RADAR_TOWER)
        return ;

    // no need to build these structures more than once
    if(ObjectData::TYPE_RADAR_STATION == structType && mPlayer->HasStructure(structType))
        return ;

    // not enough resources to build
    if(!HasPlayerResourcesToBuild(structType))
        return ;

    int priority = priority0;

    // reduce priority based on available resources
    const std::unordered_map<GameObjectTypeId, float> bonusRes
    {
        {ObjectData::TYPE_RADAR_STATION , -30.f},
        {ObjectData::TYPE_RADAR_TOWER , -35.f},
    };
    priority += GetPriorityBonusStructureBuildCost(structType, bonusRes.at(structType));

    // reduce priority based on number or existing structure
    if(ObjectData::TYPE_RADAR_TOWER == structType)
    {
        const float bonusExist = -10.f;
        priority += GetPriorityBonusSameStructureCreated(structType, bonusExist);
    }

    // check if below current priority threshold
    if(priority < mMinPriority)
        return ;

    // CREATE ACTION
    auto action = new ActionAIBuildStructure;
    action->type = AIA_UNIT_BUILD_STRUCTURE;
    action->ObjSrc = u;
    action->priority = priority;
    action->structType = structType;

    // push action to the queue
    AddNewAction(action);
}

void PlayerAI::AddActionUnitCollectBlobs(Unit * u)
{
    // DEFINE INITIAL PRIORITY
    int priority = MAX_PRIORITY;

    // decrease priority based on owned blobs
    const float decBlobs = -30.f;
    const StatValue & blobs = mPlayer->GetStat(Player::BLOBS);
    priority += std::roundf(decBlobs * blobs.GetValue() / blobs.GetMax());

    // decrease priority based on unit's energy
    const float bonusEnergy = -25.f;
    priority += GetUnitPriorityBonusEnergy(u, bonusEnergy);

    // decrease priority based on unit's health
    const float bonusHealth = -10.f;
    priority += GetUnitPriorityBonusHealth(u, bonusHealth);

    // already below current priority threshold
    if(priority < mMinPriority)
        return ;

    // FIND BEST CANDIDATE
    const unsigned int numCollectables = mCollectables.size();

    const int maxDist = GetMaxDistanceForObject(u);
    unsigned int bestInd = numCollectables;
    int minDist = maxDist;

    for(unsigned int i = 0; i < numCollectables; i++)
    {
        const GameObject * c = mCollectables[i];

        // no blobs
        if(c->GetObjectType() != ObjectData::TYPE_BLOBS)
            continue;

        // basic logic, collect closest one
        const int dist = mGm->ApproxDistance(u, c);

        if(dist < minDist)
        {
            minDist = dist;
            bestInd = i;
        }
    }

    // none found
    if(bestInd == numCollectables)
        return ;

    // bonus distance
    const float bonusDist = -25.f;
    priority += GetUnitPriorityBonusDistance(u, minDist, bonusDist);

    // can't find something that's worth an action
    if(priority < mMinPriority)
        return ;

    // CREATE ACTION
    auto action = new ActionAI;
    action->type = AIA_UNIT_COLLECT_BLOBS;
    action->ObjSrc = u;
    action->ObjDst = mCollectables[bestInd];
    action->priority = priority;

    // push action to the queue
    AddNewAction(action);
}

void PlayerAI::AddActionUnitCollectDiamonds(Unit * u)
{
    // DEFINE INITIAL PRIORITY
    int priority = MAX_PRIORITY;

    // decrease priority based on owned diamonds
    const float decDiamonds = -30.f;
    const StatValue & diamonds = mPlayer->GetStat(Player::DIAMONDS);
    priority += std::roundf(decDiamonds * diamonds.GetValue() / diamonds.GetMax());

    // decrease priority based on unit's energy
    const float bonusEnergy = -25.f;
    priority += GetUnitPriorityBonusEnergy(u, bonusEnergy);

    // decrease priority based on unit's health
    const float bonusHealth = -10.f;
    priority += GetUnitPriorityBonusHealth(u, bonusHealth);

    // already below current priority threshold
    if(priority < mMinPriority)
        return ;

    // FIND BEST CANDIDATE
    const unsigned int numCollectables = mCollectables.size();

    const int maxDist = GetMaxDistanceForObject(u);
    unsigned int bestInd = numCollectables;
    int minDist = maxDist;

    for(unsigned int i = 0; i < numCollectables; i++)
    {
        const GameObject * c = mCollectables[i];

        // no blobs
        if(c->GetObjectType() != ObjectData::TYPE_DIAMONDS)
            continue;

        // basic logic, collect closest one
        const int dist = mGm->ApproxDistance(u, c);

        if(dist < minDist)
        {
            minDist = dist;
            bestInd = i;
        }
    }

    // none found
    if(bestInd == numCollectables)
        return ;

    // bonus distance
    const float bonusDist = -25.f;
    priority += GetUnitPriorityBonusDistance(u, minDist, bonusDist);

    // can't find something that's worth an action
    if(priority < mMinPriority)
        return ;

    // CREATE ACTION
    auto action = new ActionAI;
    action->type = AIA_UNIT_COLLECT_DIAMONDS;
    action->ObjSrc = u;
    action->ObjDst = mCollectables[bestInd];
    action->priority = priority;

    // push action to the queue
    AddNewAction(action);
}

void PlayerAI::AddActionUnitCollectLootbox(Unit * u)
{
    // DEFINE INITIAL PRIORITY
    int priority = MAX_PRIORITY;

    // decrease priority based on unit's energy
    const float bonusEnergy = -25.f;
    priority += GetUnitPriorityBonusEnergy(u, bonusEnergy);

    // decrease priority based on unit's health
    const float bonusHealth = -10.f;
    priority += GetUnitPriorityBonusHealth(u, bonusHealth);

    // already below current priority threshold
    if(priority < mMinPriority)
        return ;

    // FIND BEST CANDIDATE
    const unsigned int numCollectables = mCollectables.size();

    unsigned int bestInd = numCollectables;
    int minDist = GetMaxDistanceForObject(u);

    for(unsigned int i = 0; i < numCollectables; i++)
    {
        const GameObject * c = mCollectables[i];

        // no lootbox
        if(c->GetObjectType() != ObjectData::TYPE_LOOTBOX)
            continue;

        // basic logic, collect closest one
        const int dist = mGm->ApproxDistance(u, c);

        if(dist < minDist)
        {
            minDist = dist;
            bestInd = i;
        }
    }

    // none found
    if(bestInd == numCollectables)
        return ;

    // bonus distance
    const float bonusDist = -25.f;
    priority += GetUnitPriorityBonusDistance(u, minDist, bonusDist);

    // can't find something that's worth an action
    if(priority < mMinPriority)
        return ;

    // CREATE ACTION
    auto action = new ActionAI;
    action->type = AIA_UNIT_COLLECT_LOOTBOX;
    action->ObjSrc = u;
    action->ObjDst = mCollectables[bestInd];
    action->priority = priority;

    // push action to the queue
    AddNewAction(action);
}

void PlayerAI::AddActionUnitConnectStructure(Unit * u)
{
    // DEFINE INITIAL PRIORITY
    int priority = MAX_PRIORITY;

    // decrease priority based on unit's energy
    const float bonusEnergy = -30.f;
    priority += GetUnitPriorityBonusEnergy(u, bonusEnergy);

    // decrease priority based on unit's health
    const float bonusHealth = -10.f;
    priority += GetUnitPriorityBonusHealth(u, bonusHealth);

    // already below current priority threshold
    if(priority < mMinPriority)
        return ;

    // check if there's any structure to connect
    const unsigned int numStructures = mStructures.size();

    unsigned int bestStructInd = numStructures;
    int minDist = GetMaxDistanceForObject(u);
    Cell2D startConquest;

    const PlayerFaction faction = mPlayer->GetFaction();

    const Cell2D posUnit(u->GetRow0(), u->GetCol0());

    for(unsigned int i = 0; i < numStructures; ++i)
    {
        auto s = static_cast<Structure *>(mStructures[i]);

        // own structure which is not linked
        if(s->GetFaction() == faction && !s->IsLinked())
        {
            Cell2D start;

            // SPECIAL CASE: unit is already next to structure -> best option
            if(mGm->AreObjectsOrthoAdjacent(u, s))
            {
                minDist = 0;
                bestStructInd = i;
                startConquest = posUnit;

                std::cout << "PlayerAI::AddActionUnitConnectStructure - ADJ - structure: " << s->GetObjectId()
                          << " - min dist: 0"
                          << " - dest/obj pos: " << startConquest.row << "," << startConquest.col
                          << " - obj: " << u->GetObjectId() << std::endl;

                break;
            }

            // check unit distance from structure
            const int dist = mGm->ApproxDistance(u, s);

            // unit is closer to structure
            if(dist < minDist)
            {
                start = mGm->GetOrthoAdjacentMoveTarget(posUnit, s);

                if(start.row != -1 && start.col != -1)
                {
                    minDist = dist;
                    bestStructInd = i;
                    startConquest = start;

                    std::cout << "PlayerAI::AddActionUnitConnectStructure - A - structure: " << s->GetObjectId()
                              << " - new min dist: " << dist
                              << " - dest: " << startConquest.row << "," << startConquest.col
                              << " - obj: " << u->GetObjectId()
                              << " - obj pos: " << posUnit.row << "," << posUnit.col << std::endl;
                }
            }

            // check distance to closest connected cell
            if(mGm->FindClosestCellConnectedToObject(s, posUnit, start))
            {
                const GameMapCell & gmc = mGm->GetCell(start.row, start.col);

                // connected cell is occupied and not by unit -> find adjacent
                if(gmc.objTop != nullptr && gmc.objTop != u)
                {
                    start = mGm->GetOrthoAdjacentMoveTarget(posUnit, s);

                    // can't find any
                    if(start.row == -1 || start.col == -1)
                        continue;
                }

                const int dist = mGm->ApproxDistance(posUnit, start);

                // found a closest cell
                if(dist < minDist)
                {
                    minDist = dist;
                    bestStructInd = i;
                    startConquest = start;

                    std::cout << "PlayerAI::AddActionUnitConnectStructure - B - structure: " << s->GetObjectId()
                              << " - new min dist: " << dist
                              << " - dest: " << startConquest.row << "," << startConquest.col
                              << " - obj: " << u->GetObjectId()
                              << " - obj pos: " << posUnit.row << "," << posUnit.col << std::endl;

                    // already found best option
                    if(0 == dist)
                        break;
                }
            }
        }
    }

    // can't find any structure to connect
    if(bestStructInd == numStructures)
        return ;

    // bonus distance
    const float bonusDist = -50.f;
    priority += GetUnitPriorityBonusDistance(u, minDist, bonusDist);

    // can't find something that's worth an action
    if(priority < mMinPriority)
        return ;

    auto action = new ActionAI;
    action->type = AIA_UNIT_CONNECT_STRUCTURE;
    action->ObjSrc = u;
    action->cellSrc = startConquest;
    action->ObjDst = mStructures[bestStructInd];
    action->priority = priority;

    // push action to the queue
    AddNewAction(action);
}

void PlayerAI::AddActionUnitConquerResGen(Unit * u, ResourceType type)
{
    // resource not supported
    if(type != RES_ENERGY && type != RES_MATERIAL1)
        return ;

    const int supportedRes = 2;

    const enum Player::Stat types[supportedRes] =
    {
        Player::Stat::ENERGY,
        Player::Stat::MATERIAL,
    };

    const enum Player::Stat ptype = types[type];
    const StatValue & stat = mPlayer->GetStat(ptype);

    int priority = MAX_PRIORITY;

    // decrease priority based on unit's energy
    const float bonusEnergy = -20.f;
    priority += GetUnitPriorityBonusEnergy(u, bonusEnergy);

    // decrease priority based on unit's health
    const float bonusHealth = -5.f;
    priority += GetUnitPriorityBonusHealth(u, bonusHealth);

    // bonus resource availability level
    const float bonusRes = -15.f;
    priority += std::roundf(bonusRes * stat.GetValue() / stat.GetMax());

    // action is already not doable
    if(priority < mMinPriority)
        return ;

    // visit all generators
    const int maxDist = GetMaxDistanceForObject(u);
    const unsigned int numGens = mResGenerators.size();

    unsigned int bestInd = numGens;
    int minDist = maxDist;

    int totGenerators = 0;
    int ownedGenerators = 0;

    const PlayerFaction playerFaction = mPlayer->GetFaction();

    // find best candidate
    for(unsigned int i = 0; i < numGens; ++i)
    {
        auto resGen = static_cast<ResourceGenerator *>(mResGenerators[i]);

        if(resGen->GetResourceType() != type)
            continue;

        ++totGenerators;

        // generator already owned by player
        if(playerFaction == resGen->GetFaction())
        {
            ++ownedGenerators;

            continue;
        }

        // basic logic, conquest closest one
        const int dist = mGm->ApproxDistance(u, resGen);

        if(dist < minDist)
        {
            minDist = dist;
            bestInd = i;
        }
    }

    // didn't find any
    if(bestInd == numGens)
        return ;

    // bonus distance
    const float bonusDist = -20.f;
    priority += GetUnitPriorityBonusDistance(u, minDist, bonusDist);

    // bonus unit conquest
    const float bonusConquest = 20.f;
    priority += std::roundf(bonusConquest *
                            u->GetAttribute(OBJ_ATT_CONQUEST) / ObjectData::MAX_STAT_VAL);

    // can't find something that's worth an action
    if(priority < mMinPriority)
        return ;

    auto action = new ActionAI;
    action->type = AIA_UNIT_CONQUER_GEN;
    action->ObjSrc = u;
    action->ObjDst = mResGenerators[bestInd];
    action->priority = priority;

    // push action to the queue
    AddNewAction(action);
}

void PlayerAI::AddActionUnitUpgrade(Unit * u)
{
    if(!u->CanBeUpgraded())
        return ;

    // define importance of each attribute for this object
    const int weights[] =
    {
        9, 8, 0, 6, 7, 6, 3, 3, 3, 6, 6, 3, 0
    };

    static_assert(sizeof(weights) / sizeof(int) == NUM_BASIC_ATTRIBUTES);

    AddActionUpgrade(u, weights, AIA_UPGRADE_UNIT);
}

void PlayerAI::AddActionCreateUnit(Structure * gen, const std::vector<GameObjectTypeId> & types)
{
    const unsigned int numUnits = mPlayer->GetNumUnits();
    const unsigned int limitUnits = mPlayer->GetMaxUnits();

    int priority = MAX_PRIORITY;

    // the more units exist the lower the priority
    const float bonusUnits = -25.f;
    priority += std::roundf(bonusUnits * numUnits / limitUnits);

    // decrease priority based on base's energy
    const float bonusEnergy = -20.f;
    priority += GetStructurePriorityBonusEnergy(gen, bonusEnergy);

    // priority already too low
    if(priority < mMinPriority)
        return ;

    const unsigned int numTypes = types.size();

    const int energy = mPlayer->GetStat(Player::ENERGY).GetValue();
    const int material = mPlayer->GetStat(Player::MATERIAL).GetValue();
    const int blobs = mPlayer->GetStat(Player::BLOBS).GetValue();
    const int diamonds = mPlayer->GetStat(Player::DIAMONDS).GetValue();

    unsigned int bestInd = numTypes;
    int bestPriority = mMinPriority;

    for(unsigned int i = 0; i < numTypes; ++i)
    {
        const GameObjectTypeId t = types[i];

        // can't create this unit -> next
        if(!mGm->CanCreateUnit(t, gen, mPlayer))
            continue;

        int typePriority = priority;

        // reduce priority for existing same type units
        const float bonusSameType = -25.f;
        typePriority += std::roundf(bonusSameType * mPlayer->GetNumUnitsByType(t));

        // reduce priority based on available resources
        // NOTE all costs are < current resources or CanCreateUnit would have returned false
        const ObjectData & data = mDataReg->GetObjectData(t);
        const auto & costs = data.GetCosts();

        const float bonusRes = -10.f;

        if(costs[RES_ENERGY] > 0)
            typePriority += std::roundf(bonusRes * costs[RES_ENERGY] / energy);

        if(costs[RES_MATERIAL1] > 0)
            typePriority += std::roundf(bonusRes * costs[RES_MATERIAL1] / material);

        if(costs[RES_BLOBS] > 0)
            typePriority += std::roundf(bonusRes * costs[RES_BLOBS] / blobs);

        if(costs[RES_DIAMONDS] > 0)
            typePriority += std::roundf(bonusRes * costs[RES_DIAMONDS] / diamonds);

        if(typePriority > bestPriority)
        {
            bestPriority = typePriority;
            bestInd = i;
        }
    }

    // couldn't find any good
    if(bestInd == numTypes)
        return;

    // create action
    auto action = new ActionAINewUnit;
    action->type = AIA_NEW_UNIT;
    action->ObjSrc = gen;
    action->priority = bestPriority;
    action->unitType = types[bestInd];

    // push action to the queue
    AddNewAction(action);
}

void PlayerAI::AddActionUpgrade(GameObject * obj, const int weights[],
                                AIActionType type)
{
    const int level = obj->GetExperienceLevel();
    const int pointsToAssign = GameObject::UPGRADE_POINTS[level];

    const auto attributes = obj->GetAttributes();

    // define points to assign to attributes
    std::vector<int> changes(NUM_BASIC_ATTRIBUTES, 0);

    ObjAttId attToInc = OBJ_ATT_NULL;
    int maxAttScore = 0;

    for(int i = 0; i < pointsToAssign; ++i)
    {
        for(auto it : attributes)
        {
            const ObjAttId attId = it.first;
            const int val = it.second + changes[attId];
            const int missingVal = MAX_STAT_IVAL - val;
            const int attScore = missingVal * weights[attId];

            if(attScore > maxAttScore)
            {
                attToInc = attId;
                maxAttScore = attScore;
            }
        }

        if(attToInc != OBJ_ATT_NULL)
            ++changes[attToInc];
    }

    // create action
    auto action = new ActionAIUpgradeObject;
    action->type = type;
    action->ObjSrc = obj;
    action->priority = MAX_PRIORITY;
    action->attChanges = std::move(changes);

    // push action to the queue
    AddNewAction(action);
}

int PlayerAI::GetMaxDistanceForObject(const GameObject * obj) const
{
    const int r = obj->GetRow0();
    const int c = obj->GetCol0();

    const int rows = mGm->GetNumRows();
    const int cols = mGm->GetNumCols();
    const int rowsH = rows / 2;
    const int colsH = cols / 2;

    const int distR = (r < rowsH) ? rows - r : r;
    const int distC = (c < colsH) ? cols - c : c;

    return distR + distC;
}

int PlayerAI::GetStructurePriorityBonusEnergy(const Structure * s, float bonus) const
{
    const float energyUnit = s->GetEnergy();
    const float energyUnitMax = s->GetMaxEnergy();
    const float energyTurn = mPlayer->GetTurnEnergy();
    const float energyTurnMax = mPlayer->GetTurnMaxEnergy();

    // bonuses
    const float bonusStruct = bonus * (energyUnitMax - energyUnit) / energyUnitMax;
    const float bonusTurn = bonus * (energyTurnMax - energyTurn) / energyTurnMax;

    // weights
    const float wStruct = 0.4f;
    const float wTurn = 1.f - wStruct;

    return std::roundf(bonusStruct * wStruct + bonusTurn * wTurn);
}

int PlayerAI::GetUnitPriorityBonusDistance(const Unit * u, int dist, float bonus) const
{
    const float energyStep = u->GetEnergyForActionStep(MOVE);
    const float energyTot = energyStep * dist;
    const float energyUnit = u->GetEnergy();
    const float maxDist = GetMaxDistanceForObject(u);

    // weights
    const float wRel = 0.7f;
    const float wAbs = 1.f - wRel;

    // bonuses
    const float bonusRelDist = bonus * energyTot / energyUnit;
    const float bonusAbsDist = bonus * dist / maxDist;

    return std::roundf(bonusRelDist * wRel + bonusAbsDist * wAbs);
}

int PlayerAI::GetUnitPriorityBonusEnergy(const Unit * u, float bonus) const
{
    const float energyUnit = u->GetEnergy();
    const float energyUnitMax = u->GetMaxEnergy();
    const float energyTurn = mPlayer->GetTurnEnergy();
    const float energyTurnMax = mPlayer->GetTurnMaxEnergy();

    // bonuses
    const float bonusUnit = bonus * (energyUnitMax - energyUnit) / energyUnitMax;
    const float bonusTurn = bonus * (energyTurnMax - energyTurn) / energyTurnMax;

    // weights
    const float wUnit = 0.6f;
    const float wTurn = 1.f - wUnit;

    return std::roundf(bonusUnit * wUnit + bonusTurn * wTurn);
}

int PlayerAI::GetUnitPriorityBonusHealth(const Unit * u, float bonus) const
{
    const float maxHealth = u->GetMaxHealth();
    return std::roundf(bonus * (maxHealth - u->GetHealth()) / maxHealth);
}

bool PlayerAI::HasPlayerResourcesToBuild(GameObjectTypeId t) const
{
    const ObjectData & data = mDataReg->GetObjectData(t);
    const auto & costs = data.GetCosts();

    const int energy = mPlayer->GetStat(Player::ENERGY).GetValue();
    const int material = mPlayer->GetStat(Player::MATERIAL).GetValue();
    const int blobs = mPlayer->GetStat(Player::BLOBS).GetValue();
    const int diamonds = mPlayer->GetStat(Player::DIAMONDS).GetValue();

    // not enough resources to build
    return energy >= costs[RES_ENERGY] && material >= costs[RES_MATERIAL1] &&
           diamonds >= costs[RES_DIAMONDS] && blobs >= costs[RES_BLOBS];
}

// NOTE this requires that HasPlayerResourcesToBuild is called before to stop execution
//      in case resources are not enough
int PlayerAI::GetPriorityBonusStructureBuildCost(GameObjectTypeId t, float bonus) const
{
    const ObjectData & data = mDataReg->GetObjectData(t);
    const auto & costs = data.GetCosts();

    const int energy = mPlayer->GetStat(Player::ENERGY).GetValue();
    const int material = mPlayer->GetStat(Player::MATERIAL).GetValue();
    const int blobs = mPlayer->GetStat(Player::BLOBS).GetValue();
    const int diamonds = mPlayer->GetStat(Player::DIAMONDS).GetValue();

    float b = 0.f;

    if(costs[RES_ENERGY] > 0)
        b += bonus * costs[RES_ENERGY] / energy;

    if(costs[RES_MATERIAL1] > 0)
        b += bonus * costs[RES_MATERIAL1] / material;

    if(costs[RES_BLOBS] > 0)
        b += bonus * costs[RES_BLOBS] / blobs;

    if(costs[RES_DIAMONDS] > 0)
        b += bonus * costs[RES_DIAMONDS] / diamonds;

    return std::roundf(b);
}

int PlayerAI::GetPriorityBonusSameStructureCreated(GameObjectTypeId t, float bonus) const
{
    const int numSame = mPlayer->GetNumStructuresByType(t);
    return std::roundf(numSame * bonus);
}

void PlayerAI::PrintdActionDebug(const char * title, const ActionAI * a)
{
    std::cout << title;

    std::cout << " - ID: " << a->actId
              << " - TYPE: " << a->GetTypeStr() << " - PRIO: " << a->priority;

    if(AIA_UNIT_BUILD_STRUCTURE == a->type)
    {
        auto ab = static_cast<const ActionAIBuildStructure *>(a);
        std::cout << " | STRUCT: " << ObjectData::TITLES.at(ab->structType);
    }
    else if(AIA_NEW_UNIT == a->type)
    {
        auto an = static_cast<const ActionAINewUnit *>(a);
        std::cout << " | UNIT: " << ObjectData::TITLES.at(an->unitType);
    }

    if(a->ObjSrc != nullptr)
    {
        auto obj = a->ObjSrc;

        // make sure obj is still valid (not destroyed)
        if(mGm->HasObject(obj))
        {
            std::cout << " | OBJ SRC - ID: " << obj->GetObjectId()
                      << " - FACT: " << obj->GetFaction()
                      << " - ENRG: " << obj->GetEnergy() << "/" << obj->GetMaxEnergy()
                      << " - HLTH: " << obj->GetHealth() << "/" << obj->GetMaxHealth();
        }
    }

    if(a->ObjDst != nullptr)
    {
        auto obj = a->ObjDst;

        // make sure obj is still valid (not destroyed)
        if(mGm->HasObject(obj))
        {
            std::cout << " | OBJ DST - ID: " << obj->GetObjectId()
                      << " - FACT: " << obj->GetFaction()
                      << " - ENRG: " << obj->GetEnergy() << "/" << obj->GetMaxEnergy()
                      << " - HLT: " << obj->GetHealth() << "/" << obj->GetMaxHealth();
        }
    }

    if(a->cellSrc.row != -1)
        std::cout << " | CELL SRC: " << a->cellSrc.row << "," << a->cellSrc.col;

    if(a->cellDst.row != -1)
        std::cout << " | CELL DST: " << a->cellDst.row << "," << a->cellDst.col;

    std::cout << " | TURN - ENRG: " << mPlayer->GetTurnEnergy() << "/" << mPlayer->GetTurnMaxEnergy()
              << std::endl;
}

} // namespace game
