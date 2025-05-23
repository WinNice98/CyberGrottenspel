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
    void set_item(int input_id, int input_durability, int input_num, bool input_chosen){
        id = input_id;
        durability = input_durability;
        num = input_num;
        chosen = input_chosen;
    }
    int give_item_id(){
        return id;
    }
    int give_item_durability(){
        return durability;
    }
    int give_item_num(){
        return num;
    }
    int give_item_chosen(){
        if(chosen){
            return 1;
        } else {
            return 0;
        }
    }
    void add_from_db(QString db_name, int db_damage, int db_armour, int db_durability){
        name = db_name;
        damage = db_damage;
        armour = db_armour;
        max_durability = db_durability;
    }
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
    void minus_ammo(int input_id){
        if (id == input_id){
            num--;
        }
    }
    void break_item(){
        num--;
        if (num > 0){
            durability = max_durability;
        }
    }
    int use_item(int luck){
        if (luck < 30){
            luck = 0;
        } else {
            luck = -1;
        }
        durability = durability + luck;
        if (this->id >= 6 && this->id <= 10){
            return id;
        } else {
            return 0;
        }
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
    int whats_hp(){
        return hp;
    }
    int whats_sleep(){
        return sleep;
    }
    int whats_stamina(){
        return stamina;
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

class player:public health{
    QString name;
    int level = 1;
    int money = 200;
    item inventory[50];
    int place = 5;
    int attitude[15];
    int dialogs[15];
public:
    void load(QString input_name, int input_level, int input_money, item input_inventory[50], int input_hp, int input_stamina, int input_xp, int input_sleep, int input_place, int input_attitude[5], int input_dialogs[5]){
        name = input_name;
        money = input_money;
        level = input_level;
        for(int i = 0; i < 50; i++){
            inventory[i] = input_inventory[i];
        }
        change_hp(input_hp);
        change_sleep(input_sleep);
        change_stamina(input_stamina);
        change_xp(input_xp);
        place = input_place;
        for(int i = 0; i < 15; i++){
            attitude[i] = input_attitude[i];
            dialogs[i] = input_dialogs[i];
        }
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
    int whats_lvl(){
        return level;
    }
    int whats_money(){
        return money;
    }
    void recalc_after_lvlup(){
        change_hp(max_health(level));
        change_xp(max_health(level) * 3 - abs(whats_xp()));
    }
    QString stats(){
        return name;
    }
    int whats_place(){
        return place;
    }
    int whats_dialog(int id){
        return dialogs[id];
    }
    int whats_attitude(int id){
        return attitude[id];
    }
    void change_attitude(int id, int input){
        attitude[id] = attitude[id] + input;
    }
    void change_dialog(int id){
        dialogs[id] = dialogs[id] + 1;
    }
    void change_place(){
        if (place >= 5){
            place = 0;
        } else {
            place++;
        }
    }
    void change_place(int input){
        place = input;
    }
    item give_item(int id){
        return inventory[id];
    }
};

#endif // GAME_H
