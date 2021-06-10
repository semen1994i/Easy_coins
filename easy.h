#ifndef EASY_H
#define EASY_H

#include <vector>
#include <QGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>

#include "maps.h"
#include "drawer.h"

struct easy : QGLWidget
{

    enum class eState
    {
        MENU
        ,SELECT_MAPS
        ,RULES
        ,PLAY
        ,EXIT
    };

    enum class eMenu
    {
        START = -1
        ,PLAY
        ,SELECT_MAPS
        ,RULES
        ,EXIT
        ,END
    };

    easy();


    void initializeGL()override;

    void resizeGL(int, int)override;

    void paintGL()override;

    void keyReleaseEvent(QKeyEvent *)override;

private:

    void _proccesing();

    void _draw();

    void _draw_rules();

    void _draw_menu();

    void _draw_menu_select_level();

    void _draw_play();


    void _key_released_menu(int);

    void _key_released_menu_select_level(int);

    void _key_rules(int);

    void _key_released_play(int);


private:

    int     mSelectLevelIndex{0};

    level   mLevel;

    drawer  mDrawer;

    eState  mState{eState::MENU};

    eMenu   mCurrentMenu;


    std::vector<std::pair<eMenu, std::string>> mvMenu;

    std::vector<std::pair<int , std::string>> rulRules;
};

#endif // EASY_H
