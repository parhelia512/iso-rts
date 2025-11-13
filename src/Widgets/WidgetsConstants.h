#pragma once

namespace game
{

class WidgetsConstants
{
public:
    // COLORS
    static constexpr unsigned int colorPlanetMapHeader = 0xb0c5cfff;
    static constexpr unsigned int colorPlanetMapData = 0x80a2b3ff;
    static constexpr unsigned int colorPlanetMapEnoughRes = 0x85cc85ff;
    static constexpr unsigned int colorPlanetMapLackRes = 0xcc8b85ff;

    // FONT FILES
    static const char * FontFileButton;
    static const char * FontFileHeader;
    static const char * FontFileShortcut;
    static const char * FontFileText;
    static const char * FontFileTitle;

    // FONT SIZES
    static constexpr int FontSizePlanetMapTitle = 28;
    static constexpr int FontSizePlanetMapHeader = 24;
    static constexpr int FontSizePlanetMapText = 22;
};

} // namespace game
