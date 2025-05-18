#ifndef GAME_H
#define GAME_H
#include <QString>
#include <QStringList>

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
    void change_stamina(int input_stamina){
        stamina = input_stamina;
    }
    void change_sleep(int input_sleep){
        sleep = input_sleep;
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
    void load(QString input_name, int input_level, int input_money, item input_inventory[50], int input_hp, int input_stamina, int input_xp, int input_sleep){
        name = input_name;
        money = input_money;
        level = input_level;
        for(int i = 0; i < 50; i++){
            //inventory[i] = input_inventory[i];
        }
        change_hp(input_hp);
        change_sleep(input_sleep);
        change_stamina(input_stamina);
        change_xp(input_xp);
    }
    void add_money(int mon){
        money = money + mon;
    }
    void set_name(QString input_name){
        name = input_name;
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
    QString stats(){
        return name;
    }
};

#endif // GAME_H
