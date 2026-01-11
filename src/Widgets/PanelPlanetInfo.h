#pragma once

#include <sgl/sgui/Widget.h>
#include <sgl/utilities/StringsChangeListener.h>

namespace sgl
{
    namespace graphic { class Image; }

    namespace sgui { class Label; }
}

namespace game
{

enum MissionCategory : unsigned int;
enum PlayerFaction : unsigned int;
enum TerritoryStatus : unsigned int;

class PanelPlanetInfo : public sgl::sgui::Widget, public sgl::utilities::StringsChangeListener
{
public:
    PanelPlanetInfo();

    void ClearData();
    void SetData(unsigned int rows, unsigned int cols, TerritoryStatus status,
                 PlayerFaction faction, unsigned int value, MissionCategory mission);

private:
    void HandlePositionChanged() override;

    void HandleStateEnabled() override;
    void HandleStateDisabled() override;

    void UpdatePositions();

    void UpdateTerritorySize();
    void UpdateTerritoryStatus();
    void UpdateTerritoryOccupier();
    void UpdateTerritoryValue();
    void UpdateMissionType();

    void OnStringsChanged() override;

private:
    sgl::sgui::Label * mTitle = nullptr;

    sgl::sgui::Label * mHeaderSize = nullptr;
    sgl::sgui::Label * mHeaderStatus = nullptr;
    sgl::sgui::Label * mHeaderValue = nullptr;
    sgl::sgui::Label * mHeaderOccupier = nullptr;
    sgl::sgui::Label * mHeaderMission = nullptr;

    sgl::sgui::Label * mLabelSize = nullptr;
    sgl::sgui::Label * mLabelStatus = nullptr;
    sgl::sgui::Label * mLabelOccupier = nullptr;
    sgl::sgui::Label * mLabelMission = nullptr;

    sgl::graphic::Image * mBarValue = nullptr;

    sgl::graphic::Image * mBg = nullptr;

    unsigned int mRows = 0;
    unsigned int mCols = 0;
    int mValue = 0;
    PlayerFaction mOccupier;
    TerritoryStatus mStatus;
    MissionCategory mMission;
};

} // namespace game
