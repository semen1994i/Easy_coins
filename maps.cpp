#include <QString>
#include <QDirIterator>
#include <QFile>
#include <QTextStream>

#include "loading.h"
#include "maps.h"

level::level()
{

}
/// Загрузка карты------------------------------------------------------------------------------
void level::load(int aNumber)
{
    const auto &level_path = loading::instance().mapsPath();

    QString lvl_path = level_path + QString::number(aNumber) + ".lvl";
    QFile   file(lvl_path);

    mIsLoad       = false;
    mIsComplete   = false;
    mCoinCount    = 0;

    file.open(QIODevice::ReadOnly);
    if(file.isOpen())
    {
        mRoom.clear();

        QTextStream in(&file);
        in >> mMap;
        in >> mColumns;
        in >> mLines;

        std::vector<eField> tmpRoom(mColumns * mLines, eField::EMPTY);

        in.readLine();
        for(int i = 0; i < mLines; ++i)
        {
            QString line;
            line = in.readLine();

            int  column = 0;
            int  end    = line.size();
            bool isIn   = false;
            while(column != end)
            {
                switch (line[column].toLatin1())
                {
                case '#': // Стена
                {
                    isIn = isIn ? false : true;
                    tmpRoom[mColumns * i + column] =  eField::WALL;
                    break;
                }
                case '@': // Игрок
                {
                    tmpRoom[mColumns * i + column] =  eField::PLAYER;
                    mPlayerPos.first  = i;
                    mPlayerPos.second = column;
                    break;
                }
                case '.': // Монета
                {
                    tmpRoom[mColumns * i + column] =  eField::COIN;
                    ++mCoinCount;
                    break;
                }
                case ' ': // Пустое пространство
                {
                    tmpRoom[mColumns * i + column] = eField::EMPTY;
                    break;
                }
                }
                ++column;
            }
        }
        mRoom.swap(tmpRoom);
        mIsLoad = true;
    }
    file.close();
}
//------------------------------------------------------------------------------
void level::load(std::string)
{
    mIsLoad = false;
}
//------------------------------------------------------------------------------
void level::reset()
{
    load(mMap);
}
//------------------------------------------------------------------------------
bool level::isLoad()
{
    return mIsLoad;
}
//------------------------------------------------------------------------------
bool level::isCompelte()
{
    return mIsComplete;
}
//------------------------------------------------------------------------------
void level::player_up()
{
    _move(-1, 0);
}
//------------------------------------------------------------------------------
void level::player_down()
{
    _move(1, 0);
}
//------------------------------------------------------------------------------
void level::player_left()
{
    _move(0, -1);
}
//------------------------------------------------------------------------------
void level::player_rigth()
{
    _move(0, 1);
}
//------------------------------------------------------------------------------
void level::_move(int aDl, int aDc)
{
    auto &[line, column] = mPlayerPos;

    auto nl  = line + aDl;                  // Следующая строка
    auto nc  = column + aDc;                // Следующий столбец

    auto coff  = mColumns * line + column;
    auto noff  = mColumns * nl + nc;

    auto &f   = mRoom[coff];
    auto &nf  = mRoom[noff];

    bool isMoving = false;
    switch(nf)
    {
        case eField::COIN:
        {
            f   = (f == eField::PLAYER) ? eField::EMPTY : eField::COIN;
            nf  = eField::PLAYER;
            mCoinCount--;
            isMoving = true;
            break;
        }
        case eField::EMPTY:
        {
            f  = (f == eField::PLAYER) ? eField::EMPTY : eField::COIN;
            nf = eField::PLAYER;
            isMoving = true;
            break;
        }
        case eField::WALL:
        case eField::PLAYER:
        break;
    }

    if(isMoving)
    {
        line   = nl;
        column = nc;
    }
}
//------------------------------------------------------------------------------
int level::coins() const
{
    return mCoinCount;
}

