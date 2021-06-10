#include <QGLWidget>
#include "loading.h"
#include "drawer.h"

drawer::drawer()
{
}
///Обобщённая прорисовка------------------------------------------------------
void drawer::draw(const level &aLevel, QGLWidget &aGLWidget)
{
    if(!aLevel.mIsLoad)
        return;

    _draw_grid(aLevel, aGLWidget);
    _draw_objects(aLevel, aGLWidget);
    _draw_statistic(aLevel, aGLWidget);
}
///Прорисовка сетки игры-------------------------------------------------------
void drawer::_draw_grid(const level &aLevel, QGLWidget &aGLWidget)
{
    static auto sw = loading::instance().screenHeight() - 100;

    auto &lines   = aLevel.mLines;
    auto &columns = aLevel.mColumns;

    float fw    = (float)sw / (float)columns;
    float map_w = sw;
    float map_h = fw*lines;

    float x{(loading::instance().screenWidth() - sw)/ 2.f};
    float y{100.f};

    aGLWidget.qglColor(Qt::darkGray);
    glBegin(GL_LINES);
    for(int r = 0; r <= lines; ++r)
    {
        glVertex2i(x,         y + fw*r);
        glVertex2i(x + map_w, y + fw*r);
    }

    for(int c = 0.f; c <= columns; ++c)
    {
        glVertex2i(x + fw*c, y );
        glVertex2i(x + fw*c, y + map_h);
    }
    glEnd();
}
///Прорисовка объектов---------------------------------------------------------
void drawer::_draw_objects(const level &aLevel, QGLWidget &aGLWidget)
{
    auto &app = loading::instance();
    static auto sw = app.screenHeight() - 100;

    auto &lines   = aLevel.mLines;
    auto &columns = aLevel.mColumns;

    float fw    = (float)sw / (float)columns;

    float x{(loading::instance().screenWidth() - sw)/ 2.f};
    float y{100.f};

    auto tplayer   = app.textureID(loading::eTexturesID::Player);
    auto twall     = app.textureID(loading::eTexturesID::Wall);
    auto tgoal     = app.textureID(loading::eTexturesID::Coin);

    const auto &map = aLevel.mRoom;

    glEnable(GL_TEXTURE_2D);
    aGLWidget.qglColor(Qt::white);
    for(int l = 0; l < lines; ++l)
        for(int c = 0; c < columns; ++c)
        {
            unsigned int textureID = 0;
            switch(map[l*columns + c])
            {
            case level::eField::PLAYER:
            {
                textureID = tplayer;
                break;
            }
            case level::eField::WALL:
            {
                textureID = twall;
                break;
            }
            case level::eField::COIN:
            {
                textureID = tgoal;
                break;
            }
            case level::eField::EMPTY:
            {
                break;
            }
            }
            if(textureID != 0)
                aGLWidget.drawTexture(QRectF{x + c*fw, y + l*fw, fw, fw}, textureID);
        }

    glDisable(GL_TEXTURE_2D);
}
///Ведём подсчёт количества шагов и показываем, сколько монет осталось собрать
///
void drawer::_draw_statistic(const level &aLevel, QGLWidget &aGLWidget)
{
    static auto small_font = QFont("Comic Sans MS", 15);
    static auto font = QFont("Comic Sans MS", 30);
    static auto big_font = QFont("Comic Sans MS", 40);
    aGLWidget.qglColor(Qt::yellow);

    QString str, asd, exit, ret;

    exit = "\"Esc\" - выйти в меню";
    ret = "\"Ctr\" + r - перезапустить";
    asd = "ВЫ ПОБЕДИЛИ!!!";
    str = "Осталось монет: ";
    str += QString::number(aLevel.coins());
    aGLWidget.renderText(15, 40, str, font);
    if(aLevel.coins() == 0)
    {

        aGLWidget.renderText(15, 90, asd, big_font);
        aGLWidget.renderText(15, 110, exit, small_font);
    //    aGLWidget.renderText(15, 130, ret, small_font);
    }
}




