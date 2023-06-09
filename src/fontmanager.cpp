#include "fontmanager.h"
#include <QFontDatabase>

FontManager::FontManager()
{
    int id = QFontDatabase::addApplicationFont(":/res/fonts/Juniory.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont behemianFont(family);
    m_fontMap[FontID::STRING] = behemianFont;

    id = QFontDatabase::addApplicationFont(":/res/fonts/Juniory.ttf");
    family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont numberFont(family);
    m_fontMap[FontID::NUMBER] = numberFont;
}

FontManager* FontManager::ptr = nullptr;

FontManager *FontManager::Instance()
{
    if(!ptr)
    {
        ptr = new FontManager();
    }
    return ptr;
}

QFont FontManager::getFont(FontID id) const
{
    return m_fontMap[id];
}
