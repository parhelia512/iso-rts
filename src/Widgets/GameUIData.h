#pragma once

namespace game
{

// NEW UNIT DIALOG
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
    IND_FSEL_PIP0,
    IND_FSEL_PIP1,
    IND_FSEL_PIP2,
    IND_FSEL_PIP3,
    IND_FSEL_PIP4,
    IND_FSEL_PIP5,
    IND_FSEL_PIP6,
    IND_FSEL_PIP7,
    IND_FSEL_PIP8,
    IND_FSEL_PIP9,

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
    IND_FSEL_CONTINUE_OVER,
    IND_FSEL_CONTINUE_PUSHED,

    // SPECIAL VALUES
    NUM_FSEL_PIPS = IND_FSEL_PIP9 - IND_FSEL_PIP0 + 1
};

// NEW UNIT DIALOG
extern const char SpriteFileNewUnitDialog[];

enum SpriteIdNewUnitDialog : unsigned int
{
    // BACKGROUND
    IND_NU_DIALOG_BG_LEFT,
    IND_NU_DIALOG_BG_SLOT,
    IND_NU_DIALOG_BG_RIGHT,

    // BUILD BUTTON
    IND_NU_BUTTON_NORMAL,
    IND_NU_BUTTON_DISABLED,
    IND_NU_BUTTON_MOUSE_OVER,
    IND_NU_BUTTON_PUSHED,
    IND_NU_BUTTON_CHECKED,

    // PANELS
    IND_NU_PANEL_HEADERS,
    IND_NU_PANEL_UNIT,
    IND_NU_PANEL_STATS,

    // ICONS
    IND_NU_BAR_ITEM,
    IND_NU_ICON_ENERGY,
    IND_NU_ICON_MATERIAL,
    IND_NU_ICON_CLOSE,

    NUM_IND_NEW_UNIT_DIALOG
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
    IND_BUTTON_ICON_CANCEL,

    NUM_IND_OBJ_ACT_BUTTON
};

// MAIN MENU BUTTONS
extern const char SpriteFileMainMenu[];

enum SpriteIdMainMenu : unsigned int
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

} // namespace game
