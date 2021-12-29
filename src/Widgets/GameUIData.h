#pragma once

namespace game
{

// NEW ELEMENT DIALOG
extern const char SpriteFileNewElementDialog[];

enum SpriteIdNewElementDialog : unsigned int
{
    // BACKGROUND
    IND_NE_DIALOG_BG,

    // PANELS
    IND_NE_DIALOG_ATT_ON,
    IND_NE_DIALOG_ATT_OFF,
    IND_NE_DIALOG_INFO,
    IND_NE_DIALOG_PANEL_NORMAL,
    IND_NE_DIALOG_PANEL_OVER,
    IND_NE_DIALOG_PANEL_SEL,
    IND_NE_DIALOG_PANEL_DISABLED,
    IND_NE_DIALOG_ARROW_L,
    IND_NE_DIALOG_ARROW_L_DISABLED,
    IND_NE_DIALOG_ARROW_R,
    IND_NE_DIALOG_ARROW_R_DISABLED,

    // ATTRIBUTES BAR
    IND_NE_DIALOG_BAR0,
    IND_NE_DIALOG_BAR1,
    IND_NE_DIALOG_BAR2,
    IND_NE_DIALOG_BAR3,
    IND_NE_DIALOG_BAR4,
    IND_NE_DIALOG_BAR5,
    IND_NE_DIALOG_BAR6,
    IND_NE_DIALOG_BAR7,
    IND_NE_DIALOG_BAR8,
    IND_NE_DIALOG_BAR9,
    IND_NE_DIALOG_BAR10,

    // BUTTON CLOSE
    IND_NE_DIALOG_CLOSE_NORMAL,
    IND_NE_DIALOG_CLOSE_OVER,
    IND_NE_DIALOG_CLOSE_PUSHED,

    // BUTTON BUILD
    IND_NE_DIALOG_BUILD_NORMAL,
    IND_NE_DIALOG_BUILD_DISABLED,
    IND_NE_DIALOG_BUILD_OVER,
    IND_NE_DIALOG_BUILD_PUSHED,

    // ICONS
    IND_NE_DIALOG_ICON_ENERGY,
    IND_NE_DIALOG_ICON_MATERIAL
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

} // namespace game
