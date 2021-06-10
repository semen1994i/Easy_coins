#ifndef MAPS_H
#define MAPS_H

#include <vector>
#include <string>

class drawer;

class level
{
    friend class drawer;


    enum class eField
    {
        EMPTY
        ,WALL
        ,PLAYER
        ,COIN
    };

public:

    level();

    void reset();

    void load(std::string);

    bool isCompelte();

    bool isLoad();

    void load(int);


    void player_up();

    void player_down();

    void player_left();

    void player_rigth();

    int coins() const;

private:

    void _move(int, int);

private:

    int  mMap{-1};

    int  mColumns{0};

    int  mLines{0};

    int  mCoinCount{0};

    bool mIsComplete{false};

    bool mIsLoad{false};


    std::pair<int,int>  mPlayerPos;

    std::vector<eField> mRoom;
};

#endif // MAPS_H
