#include <QGLWidget>
#include <QDirIterator>
#include <array>

#include "loading.h"

static const QString levels_path = "maps/";
static const QString pics_path   = "pics/";

static std::array<unsigned int, (int)loading::eTexturesID::End> lTextures;

loading &loading::instance()
{
    static loading res;
    return res;
}

loading::loading()
{

}
///Загружаем уровни и сортируем их----------------------------------------------
void loading::load()
{
    mAvailableLevels.clear();
    QDirIterator it(levels_path);
    while (it.hasNext())
    {
        it.next();
        QFileInfo info(it.fileInfo());
        if(info.completeSuffix() == "lvl")
            mAvailableLevels.push_back({info.baseName().toInt(), true});
    }

    std::sort(mAvailableLevels.begin(), mAvailableLevels.end(),
              [](const auto &a, const auto &b) -> bool
    {
        return a.first < b.first;
    });
    if(mAvailableLevels.size() == 0)
        return;
    mAvailableLevels[0].second = true;

    _load_texture();
}
//------------------------------------------------------------------------------
void loading::setQGLWidget(QGLWidget &aQGLWidget)
{
    mpGLContext = &aQGLWidget;
}
///Загружаем текстуры-----------------------------------------------------------
void loading::_load_texture()
{
    glEnable(GL_TEXTURE_2D);

    auto load_lexture = [this](QString aPath) -> unsigned int
    {
        QImage mPngImg;
        mPngImg.load(aPath);
        return mpGLContext->bindTexture(mPngImg);
    };

    lTextures[(int)eTexturesID::Player] = load_lexture(pics_path + "person.png");
    lTextures[(int)eTexturesID::Wall]   = load_lexture(pics_path + "wall.png");
    lTextures[(int)eTexturesID::Coin]   = load_lexture(pics_path + "coin.png");

    glDisable(GL_TEXTURE_2D);
}
///Для получения цифры текстуры--------------------------------------------------
unsigned int loading::textureID(eTexturesID aId)
{
    return lTextures[(int)aId];
}
///Для получения директории с картами--------------------------------------------
QString loading::mapsPath() const
{
    return levels_path;
}
///Ширина-------------------------------------------------------------------------
unsigned loading::screenWidth() const
{
    static unsigned res{800};
    return res;
}
///Высота-------------------------------------------------------------------------
unsigned loading::screenHeight() const
{
    static unsigned res{600};
    return res;
}
///-------------------------------------------------------------------------------
const std::vector<std::pair<int, bool>> &loading::availablesLevels()
{
    return mAvailableLevels;
}
