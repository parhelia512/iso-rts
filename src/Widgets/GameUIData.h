#pragma once

namespace game
{

// DIALOG END MISSION
extern const char SpriteFileDialogEndMission[];

enum SpriteIdDialogEndMission : unsigned int
{
    // BACKGROUND
    IND_DIA_EM_BG,

    // BUTTON
    IND_DIA_EM_BTN_NORMAL,
    IND_DIA_EM_BTN_DISABLED,
    IND_DIA_EM_BTN_OVER,
    IND_DIA_EM_BTN_PUSHED,
};

// DIALOG EXIT
extern const char SpriteFileDialogExit[];

enum SpriteIdDialogExit : unsigned int
{
    // BACKGROUND
    IND_DIA_EX_BG,

    // BUTTON 1
    IND_DIA_EX_BTN_NORMAL,
    IND_DIA_EX_BTN_DISABLED,
    IND_DIA_EX_BTN_OVER,
    IND_DIA_EX_BTN_PUSHED,
    // BUTTON 2
    IND_DIA_EX_BTN2_NORMAL,
    IND_DIA_EX_BTN2_DISABLED,
    IND_DIA_EX_BTN2_OVER,
    IND_DIA_EX_BTN2_PUSHED,
    // BUTTON CLOSE
    IND_DIA_EX_BTN_X_NORMAL,
    IND_DIA_EX_BTN_X_DISABLED,
    IND_DIA_EX_BTN_X_OVER,
    IND_DIA_EX_BTN_X_PUSHED,

    // ICONS
    IND_DIA_ICON_STEAM_NORMAL,
    IND_DIA_ICON_STEAM_DISABLED,
    IND_DIA_ICON_STEAM_OVER,
    IND_DIA_ICON_STEAM_PUSHED,
};

// DIALOG EXPLORE TEMPLE
extern const char SpriteFileDialogExploreTemple[];

enum SpriteIdDialogExploreTemple : unsigned int
{
    // BACKGROUND
    ID_DLG_EXTM_BACKGROUND,
    ID_DLG_EXTM_LINE_H,
    ID_DLG_EXTM_LINE_V,

    // BUTTON
    ID_DLG_EXTM_BTN_NORMAL,
    ID_DLG_EXTM_BTN_DISABLED,
    ID_DLG_EXTM_BTN_OVER,
    ID_DLG_EXTM_BTN_PUSHED,

    // ICONS
    ID_DLG_EXTM_ICON_MONEY,
    ID_DLG_EXTM_ICON_MATERIAL,
    ID_DLG_EXTM_ICON_BLOBS,
    ID_DLG_EXTM_ICON_DIAMONDS,

    // SLIDER
    ID_DLG_EXTM_SLIDER_BG,
    ID_DLG_EXTM_SLIDER_BAR,
    ID_DLG_EXTM_SLIDER_BTN,
};

// NEW ELEMENT DIALOG
extern const char SpriteFileDialogNewElement[];

enum SpriteIdDialogNewElement : unsigned int
{
    // PANELS
    IND_DLG_NEWE_ATT_ON,
    IND_DLG_NEWE_ATT_OFF,
    IND_DLG_NEWE_INFO,
    IND_DLG_NEWE_PANEL_NORMAL,
    IND_DLG_NEWE_PANEL_OVER,
    IND_DLG_NEWE_PANEL_SEL,
    IND_DLG_NEWE_PANEL_DISABLED,

    // ATTRIBUTES BAR
    IND_DLG_NEWE_BAR0,
    IND_DLG_NEWE_BAR1,
    IND_DLG_NEWE_BAR2,
    IND_DLG_NEWE_BAR3,
    IND_DLG_NEWE_BAR4,
    IND_DLG_NEWE_BAR5,
    IND_DLG_NEWE_BAR6,
    IND_DLG_NEWE_BAR7,
    IND_DLG_NEWE_BAR8,
    IND_DLG_NEWE_BAR9,
    IND_DLG_NEWE_BAR10,

    // BUTTON CLOSE
    IND_DLG_NEWE_CLOSE_NORMAL,
    IND_DLG_NEWE_CLOSE_OVER,
    IND_DLG_NEWE_CLOSE_PUSHED,

    // BUTTON BUILD
    IND_DLG_NEWE_BUILD_NORMAL,
    IND_DLG_NEWE_BUILD_OVER,
    IND_DLG_NEWE_BUILD_PUSHED,
    IND_DLG_NEWE_BUILD_DISABLED,

    // ICONS
    IND_DLG_NEWE_ICON_ENERGY,
    IND_DLG_NEWE_ICON_MATERIAL,
    IND_DLG_NEWE_ICON_DIAMOND,
    IND_DLG_NEWE_ICON_BLOB,

    // BUTTON LEFT
    IND_DLG_NEWE_LEFT_NORMAL,
    IND_DLG_NEWE_LEFT_DISABLED,
    IND_DLG_NEWE_LEFT_OVER,
    IND_DLG_NEWE_LEFT_PUSHED,

    // BUTTON RIGHT
    IND_DLG_NEWE_RIGHT_NORMAL,
    IND_DLG_NEWE_RIGHT_DISABLED,
    IND_DLG_NEWE_RIGHT_OVER,
    IND_DLG_NEWE_RIGHT_PUSHED
};

// NEW ELEMENT DIALOG - EXPANDABLE TEXTURE
extern const char SpriteFileDialogNewElementExp[];

enum SpriteIdDialogNewElementExp : unsigned int
{
    // BACKGROUND
    IND_DLG_NEWE_BG_TOP,
    IND_DLG_NEWE_BG_MID,
    IND_DLG_NEWE_BG_BTM,
};

// FACTION SELECTION DIALOG
extern const char SpriteFileFactionSelection[];

enum SpriteIdFactionSelection : unsigned int
{
    // PANELS
    IND_FSEL_MAIN_BG,
    IND_FSEL_PANEL_F1,
    IND_FSEL_PANEL_F2,
    IND_FSEL_PANEL_F3,
    IND_FSEL_PANEL_TXT,
    IND_FSEL_PANEL_ATTR,

    // ATTRIBUTES BAR
    IND_FSEL_BAR0,
    IND_FSEL_BAR1,
    IND_FSEL_BAR2,
    IND_FSEL_BAR3,
    IND_FSEL_BAR4,
    IND_FSEL_BAR5,
    IND_FSEL_BAR6,
    IND_FSEL_BAR7,
    IND_FSEL_BAR8,
    IND_FSEL_BAR9,
    IND_FSEL_BAR10,

    // BACK BUTTON
    IND_FSEL_BACK_NORMAL,
    IND_FSEL_BACK_OVER,
    IND_FSEL_BACK_PUSHED,

    // SELECT BUTTON
    IND_FSEL_SEL_NORMAL,
    IND_FSEL_SEL_OVER,
    IND_FSEL_SEL_PUSHED,
    IND_FSEL_SEL_CHECKED,

    // CONTINUE BUTTON
    IND_FSEL_CONTINUE_NORMAL,
    IND_FSEL_CONTINUE_DISABLED,
    IND_FSEL_CONTINUE_OVER,
    IND_FSEL_CONTINUE_PUSHED,

    // SPECIAL VALUES
    NUM_FSEL_PIPS = IND_FSEL_BAR9 - IND_FSEL_BAR0 + 1
};

// OBJECT ACTION BUTTON
extern const char SpriteFileObjActionButton[];

enum SpriteIdObjActionButton : unsigned int
{
    // BUTTON
    IND_BUTTON_NORMAL,
    IND_BUTTON_DISABLED,
    IND_BUTTON_MOUSE_OVER,
    IND_BUTTON_PUSHED,
    IND_BUTTON_CHECKED,

    // ICONS
    IND_BUTTON_ICON_UNITS,
    IND_BUTTON_ICON_MOVE,
    IND_BUTTON_ICON_ATTACK,
    IND_BUTTON_ICON_CONQUER_CELL,
    IND_BUTTON_ICON_BUILD_WALL,
    IND_BUTTON_ICON_BUILD_STRUCT,
    IND_BUTTON_ICON_UPGRADE,
    IND_BUTTON_ICON_OPEN_GATE,
    IND_BUTTON_ICON_CLOSE_GATE,
    IND_BUTTON_ICON_CANCEL,
    IND_BUTTON_ICON_HEAL,

    NUM_IND_OBJ_ACT_BUTTON
};

// MAIN MENU
extern const char SpriteFileMainMenu[];

enum SpriteIdMainMenu : unsigned int
{
    // CHANGELOG DIALOG
    IND_MM_BTN_UPDATES,
    IND_MM_BTN_CLOSE,
    IND_MM_BTN_SCROLLBAR,
    IND_MM_DIALOG_UPDATES,
    IND_MM_SCROLLBAR,
};

// MAIN MENU BUTTONS
extern const char SpriteFileMainMenuButtons[];

enum SpriteIdMainMenuButtons : unsigned int
{
    // PRIMARY BUTTON
    IND_MM_BTN1_NORMAL,
    IND_MM_BTN1_DISABLED,
    IND_MM_BTN1_OVER,
    IND_MM_BTN1_PUSHED,
    IND_MM_BTN1_CHECKED,

    // WISHLIST BUTTON
    IND_MM_BTNW_NORMAL,
    IND_MM_BTNW_OVER,
    IND_MM_BTNW_PUSHED,

    // SOCIAL BUTTON
    IND_MM_BTNS_NORMAL,
    IND_MM_BTNS_OVER,
    IND_MM_BTNS_PUSHED,

    // ICONS
    IND_MM_ICON_STEAM,
    IND_MM_ICON_DISCORD,
    IND_MM_ICON_TWITTER,
    IND_MM_ICON_YOUTUBE,
    IND_MM_ICON_LINKEDIN,

    NUM_MAIN_MENU_SPRITES
};

// MAP PANELS
extern const char SpriteFileMapPanels[];

enum SpriteIdMapPanels : unsigned int
{
    // MINIMAP
    IND_MINIMAP_BG,
    IND_MINIMAP_MAP_BG,
    IND_MINIMAP_MAP_ELEM,
    IND_MINIMAP_BTN_CLOSE_NORMAL,
    IND_MINIMAP_BTN_CLOSE_OVER,
    IND_MINIMAP_BTN_CLOSE_PUSHED,
    IND_MINIMAP_BTN_U_NORMAL,
    IND_MINIMAP_BTN_U_DISABLED,
    IND_MINIMAP_BTN_U_OVER,
    IND_MINIMAP_BTN_U_PUSHED,
    IND_MINIMAP_BTN_D_NORMAL,
    IND_MINIMAP_BTN_D_DISABLED,
    IND_MINIMAP_BTN_D_OVER,
    IND_MINIMAP_BTN_D_PUSHED,
    IND_MINIMAP_BTN_R_NORMAL,
    IND_MINIMAP_BTN_R_DISABLED,
    IND_MINIMAP_BTN_R_OVER,
    IND_MINIMAP_BTN_R_PUSHED,
    IND_MINIMAP_BTN_L_NORMAL,
    IND_MINIMAP_BTN_L_DISABLED,
    IND_MINIMAP_BTN_L_OVER,
    IND_MINIMAP_BTN_L_PUSHED,
    IND_MINIMAP_CAMERA_BL,
    IND_MINIMAP_CAMERA_TR,
    IND_MINIMAP_CAMERA_TL,
    IND_MINIMAP_CAMERA_BR,
    // MINIMAP BUTTON
    IND_MINIMAP_BUTTON_NORMAL,
    IND_MINIMAP_BUTTON_OVER,
    IND_MINIMAP_BUTTON_PUSHED
};

// MAP UI
extern const char SpriteFileMapUI[];

enum SpriteIdMapUI : unsigned int
{
    // CELL PROGRESS BAR
    IND_CELL_BAR_BG,
    IND_CELL_BAR_F1,
    IND_CELL_BAR_F2,
    IND_CELL_BAR_F3,
    IND_CELL_BAR_F4,
    // ICON COSTS
    IND_ICON_CELL_ENERGY,
    IND_ICON_CELL_MATERIAL
};

// PLANET MAP
extern const char SpriteFilePlanetMap[];

enum SpriteIdPlanetMap : unsigned int
{
    // PLANET
    IND_PM_PLANET,
    IND_PM_CELL_UNEXPLORED,
    IND_PM_CELL_UNEXPLORED_SEL,
    IND_PM_CELL_EXPLORED,
    IND_PM_CELL_SELECTED,
    IND_PM_CELL_DISABLED,
    IND_PM_CELL_F1,
    IND_PM_CELL_F1_SEL,
    IND_PM_CELL_F2,
    IND_PM_CELL_F2_SEL,
    IND_PM_CELL_F3,
    IND_PM_CELL_F3_SEL,

    // STARS BAR
    IND_PM_STARS_DIS,
    IND_PM_STARS_1,
    IND_PM_STARS_2,
    IND_PM_STARS_3,
    IND_PM_STARS_4,
    IND_PM_STARS_5,

    // PIPS BAR
    IND_PM_PIPS_BAR_DIS,
    IND_PM_PIPS_BAR_0,
    IND_PM_PIPS_BAR_1,
    IND_PM_PIPS_BAR_2,
    IND_PM_PIPS_BAR_3,
    IND_PM_PIPS_BAR_4,
    IND_PM_PIPS_BAR_5,
    IND_PM_PIPS_BAR_6,
    IND_PM_PIPS_BAR_7,
    IND_PM_PIPS_BAR_8,
    IND_PM_PIPS_BAR_9,
    IND_PM_PIPS_BAR_10,

    // BUTTON
    IND_PM_BTN_NORMAL,
    IND_PM_BTN_DISABLED,
    IND_PM_BTN_OVER,
    IND_PM_BTN_PRESSED,

    // BUTTON 2
    IND_PM_BTN2_NORMAL,
    IND_PM_BTN2_DISABLED,
    IND_PM_BTN2_OVER,
    IND_PM_BTN2_PRESSED,

    // ICONS
    IND_PM_ICON_MONEY_DIS,
    IND_PM_ICON_ENERGY_DIS,
    IND_PM_ICON_MATERIAL_DIS,
    IND_PM_ICON_DIAMONDS_DIS,
    IND_PM_ICON_BLOBS_DIS,
    IND_PM_ICON_MONEY,
    IND_PM_ICON_ENERGY,
    IND_PM_ICON_MATERIAL,
    IND_PM_ICON_DIAMONDS,
    IND_PM_ICON_BLOBS,

    // BUTTON LEAVE
    IND_PM_BTN3_NORMAL,
    IND_PM_BTN3_DISABLED,
    IND_PM_BTN3_OVER,
    IND_PM_BTN3_PRESSED,
};

// PLANET MAP 2
extern const char SpriteFilePlanetMap2[];

enum SpriteIdPlanetMap2 : unsigned int
{
    // PANELS
    IND_PM_PANEL_NAME,
    IND_PM_PANEL_DATE,
    IND_PM_PANEL_RESOURCES,
    IND_PM_PANEL_ACTIONS,
    IND_PM_PANEL_INFO,
    IND_PM_PANEL_LEAVE
};

// RESOURCES BAR
extern const char SpriteFileResourcesBar[];

enum SpriteIdResourcesBar : unsigned int
{
    // BAR
    IND_RESBAR_BG,

    // MINI BAR
    IND_RESBAR_MINIBAR_BG,
    IND_RESBAR_MINIBAR_VAL,

    // ICONS
    IND_RESBAR_MONEY,
    IND_RESBAR_ENERGY,
    IND_RESBAR_MATERIAL,
    IND_RESBAR_DIAMOND,
    IND_RESBAR_BLOB
};

// SETTINGS
extern const char SpriteFileSettings[];

enum SpriteIdSettings : unsigned int
{
    // PANELS
    IND_SET_PANEL,

    // BUTTON BACK
    IND_SET_BTN_X_NORMAL,
    IND_SET_BTN_X_DISABLED,
    IND_SET_BTN_X_OVER,
    IND_SET_BTN_X_PUSHED,

    // SECONDARY BUTTON
    IND_SET_BTN2_LINE,

    // COMBO BOX
    IND_SET_CB_NORMAL,
    IND_SET_CB_DISABLED,
    IND_SET_CB_OVER,
    IND_SET_CB_PUSHED,
    IND_SET_CBI_NORMAL,
    IND_SET_CBI_DISABLED,
    IND_SET_CBI_OVER,
    IND_SET_CBI_PUSHED,

    // CHECK BOX
    IND_SET_CHB_NORMAL,
    IND_SET_CHB_DISABLED,
    IND_SET_CHB_OVER,
    IND_SET_CHB_PUSHED,
    IND_SET_CHB_CHECKED_NORMAL,
    IND_SET_CHB_CHECKED_DISABLED,
    IND_SET_CHB_CHECKED_OVER,
    IND_SET_CHB_CHECKED_PUSHED,
};

// SETTINGS - EXPANDABLE TEXTURES
extern const char SpriteFileSettingsExp[];

enum SpriteIdSettingsExp : unsigned int
{
    // PANELS
    IND_SET_PANEL2_TOP,
    IND_SET_PANEL2_MID,
    IND_SET_PANEL2_BOTTOM,

    // SLIDER H
    IND_SET_SLIDERH_BG,
    IND_SET_SLIDERH_BAR,
    IND_SET_SLIDERH_BUTTON
};

// UNIT QUICK SELECTION
extern const char SpriteFileTooltips[];

enum SpriteIdTooltips : unsigned int
{
    IND_TOOLTIP_SIMPLE_LEFT,
    IND_TOOLTIP_SIMPLE_CONT,
    IND_TOOLTIP_SIMPLE_RIGHT
};

// UNIT QUICK SELECTION
extern const char SpriteFileUnitQuickSel[];

enum SpriteIdUnitQuickSel : unsigned int
{
    // BUTTON BG
    IND_UQS_BG_NORMAL,
    IND_UQS_BG_DISABLED,
    IND_UQS_BG_MOUSE_OVER,
    IND_UQS_BG_PUSHED,
    IND_UQS_BG_CHECKED,

    // ICONS
    IND_UQS_ICON_ENERGY,
    IND_UQS_ICON_HEALTH,

    // UNITS
    IND_UQS_UNIT1_F1,
    IND_UQS_UNIT2_F1,
    IND_UQS_UNIT3_F1,
    IND_UQS_UNIT4_F1,
    IND_UQS_UNIT5_F1,
    IND_UQS_UNIT1_F2,
    IND_UQS_UNIT2_F2,
    IND_UQS_UNIT3_F2,
    IND_UQS_UNIT4_F2,
    IND_UQS_UNIT5_F2,
    IND_UQS_UNIT1_F3,
    IND_UQS_UNIT2_F3,
    IND_UQS_UNIT3_F3,
    IND_UQS_UNIT4_F3,
    IND_UQS_UNIT5_F3,

    NUM_UQS_UNIT_SPRITE_PER_FACTION = IND_UQS_UNIT1_F2 - IND_UQS_UNIT1_F1
};

} // namespace game
