#ifndef LOADING_H
#define LOADING_H

#include <QString>
#include <QGLWidget>
#include <vector>

struct loading
{
    enum class eTexturesID
    {
        Wall
        ,Player
        ,Coin
        ,End
    };

    loading(const loading &) = delete;

    loading & operator=(const loading&) = delete;

    static loading &instance();

    void load();

    void setQGLWidget(QGLWidget &);

    QString  mapsPath() const;

    unsigned screenWidth() const;

    unsigned screenHeight() const;

    const std::vector<std::pair<int, bool>> &availablesLevels();

    unsigned int textureID(eTexturesID);

private:
    void _load_texture();

private:
    loading();

private:
    unsigned mScreenWidth{0};
    unsigned mScreenHeight{0};

    QGLWidget *mpGLContext{nullptr};

    std::vector<std::pair<int, bool>> mAvailableLevels;
};

#endif // LOADING_H
