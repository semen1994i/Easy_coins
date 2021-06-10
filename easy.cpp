#include "easy.h"
#include "loading.h"

///Скролинг с появлением в начале из конца --------------------------------------
easy::eMenu operator++(easy::eMenu &aMenu)
{
    aMenu = easy::eMenu(int(aMenu) + 1);

    if(aMenu == easy::eMenu::END )
    {
        aMenu = easy::eMenu::SELECT_MAPS;
        return aMenu;
    }
    return aMenu;
}
///Скролинг с появлением в конце из начала --------------------------------------
easy::eMenu operator--(easy::eMenu &aMenu)
{
    aMenu = easy::eMenu(int(aMenu) - 1);

    if(aMenu == easy::eMenu::START || aMenu == easy::eMenu::PLAY)
    {
        aMenu = easy::eMenu::EXIT;
        return aMenu;
    }
    return aMenu;
}
///------------------------------------------------------------------------------
int menuStateToInt(const easy::eMenu &aMenu)
{
    switch(aMenu)
    {
    case easy::eMenu::START:        return (int)easy::eMenu::START;
    case easy::eMenu::END:          return (int)easy::eMenu::END;
    case easy::eMenu::SELECT_MAPS:  return (int)easy::eMenu::SELECT_MAPS;
    case easy::eMenu::PLAY:         return (int)easy::eMenu::PLAY;
    case easy::eMenu::RULES:        return (int)easy::eMenu::RULES;
    case easy::eMenu::EXIT:         return (int)easy::eMenu::EXIT;
    }
    return -1;
}
///------------------------------------------------------------------------------
easy::eState menuStateToGameState(const easy::eMenu &aMenu)
{
    switch(aMenu)
    {
    case easy::eMenu::START:
    case easy::eMenu::END:          return easy::eState::MENU;

    case easy::eMenu::SELECT_MAPS:  return easy::eState::SELECT_MAPS;
    case easy::eMenu::PLAY:         return easy::eState::PLAY;
    case easy::eMenu::RULES:        return easy::eState::RULES;
    case easy::eMenu::EXIT:         return easy::eState::EXIT;
    }
    return easy::eState::MENU;
}
///------------------------------------------------------------------------------
easy::easy()
    :mCurrentMenu(eMenu((int)eMenu::START + 2))
{
    loading::instance().setQGLWidget(*this);

    setFormat(QGLFormat(QGL::DoubleBuffer));
    glDepthFunc(GL_LEQUAL);
    mvMenu.push_back({eMenu::PLAY,""});


    //Элементы меню
    mvMenu.push_back({eMenu::SELECT_MAPS,     "Выбрать карту "});
    mvMenu.push_back({eMenu::RULES,           "Правила и управление"});
    mvMenu.push_back({eMenu::EXIT,            "Выход из игры"});

    rulRules.push_back({0, "Для передвижения по полю используйте стрелки"});
    rulRules.push_back({1, "клавиатуры. Вам необходимо собрать все монетки,"});
    rulRules.push_back({2, "которые лежат на карте. Для выхода в предыдущий"});
    rulRules.push_back({3, "пункт меню используйте \"Esc\". Хорошей игры!!!"});
}

///Отрисовка окна ------------------------------------------------------------
void easy::initializeGL()
{
    static auto app_w = loading::instance().screenWidth();
    static auto app_h = loading::instance().screenHeight();

    glOrtho(0, app_w, app_h, 0, 0, 1);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);

    loading::instance().load();
}
///Расширение окна
void easy::resizeGL(int w, int h)
{
    static auto app_w = loading::instance().screenWidth();
    static auto app_h = loading::instance().screenHeight();

    glLoadIdentity();
    glViewport(0, 0, (GLint)w, (GLint)h);
    glOrtho(0, app_w, app_h, 0, 0, 1);
}
///Отрисовка -------------------------------------------------
void easy::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    qglClearColor(Qt::darkCyan);

    _proccesing();

    _draw();
}
///Реакция на клавиши -----------------------------------------
void easy::keyReleaseEvent(QKeyEvent *apEvent)
{
    switch (mState)
    {
    case eState::MENU:
    {
        _key_released_menu(apEvent->key());
        break;
    }
    case eState::SELECT_MAPS:
    {
        _key_released_menu_select_level(apEvent->key());
        break;
    }
    case eState::RULES:
    {
        _key_rules(apEvent->key());
        break;
    }
    case eState::PLAY:
    {
        _key_released_play(apEvent->key());
        break;
    }
    case eState::EXIT:
    {
        break;
    }
    }
}

///
void easy::_proccesing()
{
    switch (mState)
    {
    case eState::MENU:
    {
        break;
    }
    case eState::SELECT_MAPS:
    {
        break;
    }
    case eState::RULES:
    {
        break;
    }
    case eState::PLAY:
    {
        break;
    }
    case eState::EXIT:
    {
        close();
        break;
    }
  }
}
///Обобщённая отрисовка ---------------------------------------------
void easy::_draw()
{
    switch (mState)
    {
    case eState::MENU:
    {
        _draw_menu();
        break;
    }
    case eState::SELECT_MAPS:
    {
        _draw_menu_select_level();
        break;
    }
    case eState::RULES:
    {
        _draw_rules();
        break;
    }
    case eState::PLAY:
    {
        _draw_play();
        break;
    }
    case eState::EXIT:
    {
        break;
    }
    }
}
///Отрисовка правил -------------------------------------------------------
void easy::_draw_rules()
{
    static auto app_w = loading::instance().screenWidth() / 2.f;
    static auto app_h = loading::instance().screenHeight() / 3.f;
    static auto font = QFont("Sans", 40);
    font.setBold(true);

    auto x = app_w - 360;
    auto y = app_h + 50;
    auto dy = 80.f;
    int end = rulRules.size();

    for(int i = 0; i < end; ++i)
    {
        qglColor(Qt::yellow);
        renderText(x, y, rulRules[i].second.c_str(), font);
        y += dy;
    }

}
///Отрисовка меню -----------------------------------------------------------
void easy::_draw_menu()
{
    static auto app_w = loading::instance().screenWidth() / 2.f;
    static auto app_h = loading::instance().screenHeight() / 3.f;

    static auto font          = QFont("Sans", 50);
    static auto font_selected = QFont("Sans", 55);
    font_selected.setBold(true);

    auto x   = app_w - 100;
    auto y   = app_h;
    auto dy  = 90.f;
    int end = mvMenu.size();

    for(int i = 0; i < end; ++i)
    {
        if(i == menuStateToInt(mCurrentMenu))
        {
            qglColor(Qt::yellow);
            renderText(x, y, mvMenu[i].second.c_str(), font_selected);
        }
        else
        {
            qglColor(Qt::white);
            renderText(x, y, mvMenu[i].second.c_str(), font);
        }
        y += dy;
    }
}
///Отрисовка выбора карт -------------------------------------------------
void easy::_draw_menu_select_level()
{
    auto &app = loading::instance();
    static auto app_w = app.screenWidth() / 2.f;
    static auto app_h = app.screenHeight() / 3.f;

    auto &levels = app.availablesLevels();
    int  l_count = (int)levels.size();

    static auto font          = QFont("Sans", 50);
    static auto font_selected = QFont("Sans", 55);
    font_selected.setBold(true);

    if(levels.empty())
        return;

    int tmp = (mSelectLevelIndex - 6);
    int start = tmp < 0 ? 0 : tmp;

    tmp = (start + 6);
    int end = (tmp < l_count) ? tmp : l_count - 1;

    auto x   = app_w + 50;
    auto y   = app_h + 100;
    auto dy  = 90.f;

    for(int i = start; i <= end; ++i)
    {
        const auto &[lvl, isLock] = levels[i];

        QString item_str = "Карта " + QString::number(lvl);

        QFont  &rf = (i == mSelectLevelIndex) ? font_selected : font;

        Qt::GlobalColor color = Qt::gray;

        if(i == mSelectLevelIndex)
        {
            if(isLock == true)
            color = Qt::yellow;
        }
        else
        {
            if(isLock == true)
            color = Qt::white;
        }

        qglColor(color);
        renderText(x, y, item_str, rf);

        y += dy;
    }
}
///
void easy::_draw_play()
{
    mDrawer.draw(mLevel, *this);
}
///Клавиши меню -------------------------------------------------------
void easy::_key_released_menu(int aKey)
{
    switch(aKey)
    {
    case Qt::Key_Up:
    {
        --mCurrentMenu;
        break;
    }
    case Qt::Key_Down:
    {
        ++mCurrentMenu;
        break;
    }
    case Qt::Key_Return:
    case Qt::Key_Enter:
    {
        mState = menuStateToGameState(mCurrentMenu);
        if(mState == eState::PLAY)
            mLevel.load("save_file");
        break;
    }
    }
    updateGL();
}
///Клавиши меню-карт -----------------------------------------------------
void easy::_key_released_menu_select_level(int aKey)
{
    const auto &levels = loading::instance().availablesLevels();
    int levels_count = (int)levels.size();

    switch(aKey)
    {
    case Qt::Key_Up:
    {
        --mSelectLevelIndex;
        if(mSelectLevelIndex < 0)
            mSelectLevelIndex = levels_count - 1;
        break;
    }
    case Qt::Key_Down:
    {
        ++mSelectLevelIndex;
        if(mSelectLevelIndex >= levels_count)
            mSelectLevelIndex = 0;
        break;
    }
    case Qt::Key_Enter:
    case Qt::Key_Return:
    {
        if(mSelectLevelIndex >= 0)
        {
            if(mSelectLevelIndex >= levels_count)
            break;

            const auto & [lvl, isLock] = levels[mSelectLevelIndex];
            if(isLock)
            {
                mLevel.load(lvl);
                mState = eState::PLAY;
            }
        }
        break;
    }
    case Qt::Key_Escape:
    {
        mState = eState::MENU;
        break;
    }
    }
    updateGL();
}
///Клавиши в правилах-------------------------------------------------
void easy::_key_rules(int aKey)
{
    switch(aKey)
    {
    case Qt::Key_Escape:
    {
        mState = eState::MENU;
        break;
    }
    }
    updateGL();
}
///Клавиши при игре ---------------------------------------------------
void easy::_key_released_play(int aKey)
{
    switch(aKey)
    {
    case Qt::Key_Up:
    {
        mLevel.player_up();
        break;
    }
    case Qt::Key_Down:
    {
        mLevel.player_down();
        break;
    }
    case Qt::Key_Left:
    {
        mLevel.player_left();
        break;
    }
    case Qt::Key_Right:
    {
        mLevel.player_rigth();
        break;
    }
    case Qt::Key_Escape:
    {
        mState = eState::MENU;
        break;
    }
    case Qt::Key_R:
    {
        mLevel.reset();
        break;
    }
    }
    updateGL();
}

