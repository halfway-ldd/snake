#ifndef DATA_H
#define DATA_H
#include<QString>
class data
{
public:
    data();
    static QString data_user;
    static bool data_state;
    static bool data_visible;
    static int data_snake;
    static int data_wall;
    static int data_food;
    static int data_mapmode;
};

#endif // DATA_H
