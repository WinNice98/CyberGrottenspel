#ifndef GAME_H
#define GAME_H
#include <QString>
class item{
    int id;
    QString name;
    int damage;
    int armour;
    int durability;
    int num;
    bool chosen;
    int max_durability;
public:
    bool is_chosen(void){
        return chosen;
    }
    int power_arm(void){
        return armour;
    }
    int power_dam(void){
        return damage;
    }
    int price(void){
        return (100000 * (id % 7)) / (100 + (durability * 100) / max_durability) * num;
    }

};
class health{
    int hp = 100;
    int stamina = 100;
    int xp;
    int sleep = 100;
public:
    int max_health(int level){
        int max_hp = 0;
        if (level >= 1) {
            max_hp = 100;
            if (level >= 4) {
                max_hp = max_hp + 100;
                if (level >= 7) {
                    max_hp = max_hp + 100;
                    if (level >= 10) {
                        max_hp = max_hp + 100;
                        if (level >= 13) {
                            max_hp = max_hp + ((level - 10) / 3) * 150;
                        }
                    }
                }
            }
        }
        return max_hp;
    }
    void change_health(int armour, int damage){
        if (armour <= damage){
            hp = hp - damage + armour;
        }
        stamina--;
        sleep--;
    }
    void change_xp (int count){
        xp = count;
    }
    int whats_xp(){
        return xp;
    }
    void change_hp(int health){
        hp = health;
    }
};

class enemy{
    QString name;

};

class player:health{
    QString name;
    int level = 1;
    int money = 200;
    item inventory[50];
public:
    void add_money(int mon){
        money = money + mon;
    }
    bool is_enough(int cost){
        if (money >= cost){
            return true;
        } else {
            return false;
        }
    }
    void recalc_after_lvlup(){
        change_hp(max_health(level));
        change_xp(max_health(level) * 3 - abs(whats_xp()));
    }

};

#endif // GAME_H
