//Lichkovaha Daniil
//st129351@student.spbu.ru
//Lab_Work_2

#include <gtest/gtest.h>
#include "YardDragon.h"
#include "Player.h"
#include "GameField.h"
#include <memory>

class YardDragonTest : public ::testing::Test {
protected:
    std::shared_ptr<Player> player;
    std::shared_ptr<YardDragon> dragon;
    std::shared_ptr<GameField> field;

    // Параметры дракона для тестов
    const std::string dragon_name = "TestDragon";
    const unsigned int initial_health = 100;
    const unsigned int initial_damage = 20;
    const unsigned int initial_iq = 10;
    const unsigned int initial_exp = 30;
    const int attack_range = 4;

    void SetUp() override {
        player = std::make_shared<Player>("TestPlayer");
        player->setX_pos(10);
        player->setY_pos(10);
        
        dragon = std::make_shared<YardDragon>(
            dragon_name, initial_health, initial_damage, initial_iq, initial_exp, 
            player.get(), attack_range
        );
        
        field = std::make_shared<GameField>(*player, dragon);
        
        // Установим дракона на поле для тестирования
        dragon->setX_pos(5);
        dragon->setY_pos(5);
        field->setSymbol(5, 5, 'Y');
    }

    void TearDown() override {
        // Smart pointers handle cleanup
    }
};

TEST_F(YardDragonTest, Initialization)
{
    EXPECT_EQ(dragon->getName(), dragon_name);
    EXPECT_EQ(dragon->getHealth(), initial_health);
    EXPECT_EQ(dragon->getDamage(), initial_damage);
    EXPECT_EQ(dragon->getIQ(), initial_iq);
    EXPECT_EQ(dragon->getExp(), initial_exp);
    
    // Проверяем уникальные свойства дракона
    EXPECT_EQ(dragon->getAttackRange(), attack_range);
    EXPECT_TRUE(dragon->getCanMove());
    EXPECT_EQ(dragon->getFireCount(), 0);
}

TEST_F(YardDragonTest, PositionManagement)
{
    dragon->setX_pos(7);
    dragon->setY_pos(7);
    EXPECT_EQ(dragon->getX_pos(), 7);
    EXPECT_EQ(dragon->getY_pos(), 7);
}

TEST_F(YardDragonTest, AttackRangeManagement)
{
    int new_range = 5;
    dragon->setAttackRange(new_range);
    EXPECT_EQ(dragon->getAttackRange(), new_range);
}

TEST_F(YardDragonTest, FireCountManagement)
{
    int new_count = 3;
    dragon->setFireCount(new_count);
    EXPECT_EQ(dragon->getFireCount(), new_count);
}

TEST_F(YardDragonTest, CanMoveManagement)
{
    dragon->setCanMove(false);
    EXPECT_FALSE(dragon->getCanMove());
    dragon->setCanMove(true);
    EXPECT_TRUE(dragon->getCanMove());
}

TEST_F(YardDragonTest, Movement)
{
    // Изначально дракон находится в (5,5), а игрок в (10,10)
    // Дракон должен двигаться к игроку, учитывая что abs(dist_x) == abs(dist_y)
    // Согласно логике в move() в YardDragon.cpp, дракон должен двигаться по X
    int initial_x = dragon->getX_pos();
    int initial_y = dragon->getY_pos();
    
    dragon->move(*player, *field);
    
    // Проверяем, что дракон двинулся на 1 клетку в сторону игрока
    EXPECT_EQ(dragon->getX_pos(), initial_x + 1);
    EXPECT_EQ(dragon->getY_pos(), initial_y);
    
    // Проверяем, что старое место пусто, а новое содержит дракона
    EXPECT_EQ(field->getSymbol(initial_x, initial_y), ' ');
    EXPECT_EQ(field->getSymbol(initial_x + 1, initial_y), 'Y');
}

TEST_F(YardDragonTest, MovementWhenCantMove)
{
    int initial_x = dragon->getX_pos();
    int initial_y = dragon->getY_pos();
    
    // Запрещаем дракону двигаться
    dragon->setCanMove(false);
    
    dragon->move(*player, *field);
    
    // Проверяем, что дракон не двинулся
    EXPECT_EQ(dragon->getX_pos(), initial_x);
    EXPECT_EQ(dragon->getY_pos(), initial_y);
}

TEST_F(YardDragonTest, TakeDamage)
{
    unsigned int damage = 30;
    dragon->takeDamage(damage);
    EXPECT_EQ(dragon->getHealth(), initial_health - damage);
    
    // Убедимся, что дракон не умирает если у него остаётся здоровье
    EXPECT_TRUE(dragon->isAlive());
    
    // Нанесем смертельный урон
    dragon->takeDamage(initial_health);
    EXPECT_EQ(dragon->getHealth(), 0);
    EXPECT_FALSE(dragon->isAlive());
}

TEST_F(YardDragonTest, FireAttack)
{
    // Симулируем огненную атаку дракона
    // По логике FireAttack, дракон наносит урон игроку, если тот находится в области атаки
    
    // Помещаем игрока рядом с драконом (в зону атаки)
    player->setX_pos(6);
    player->setY_pos(5);
    field->setSymbol(6, 5, '@');
    
    // Запоминаем начальное здоровье игрока
    unsigned int initial_player_health = player->getHealth();
    
    // Вызываем огненную атаку
    dragon->FireAttack(*field, *player);
    
    // Проверяем, что игроку был нанесен урон
    EXPECT_LT(player->getHealth(), initial_player_health);
    
    // Также должны быть добавлены огненные визуалы (символы '~')
    bool found_fire = false;
    for (int i = -attack_range + 1; i < attack_range; i++) {
        for (int j = -attack_range + 1; j < attack_range; j++) {
            if (i == 0 && j == 0) continue; // не проверяем позицию дракона
            
            int x = dragon->getX_pos() + i;
            int y = dragon->getY_pos() + j;
            
            // Проверяем только позиции рядом с драконом (для fire_count == 0)
            if ((abs(i) == 1 || i == 0) && (abs(j) == 1 || j == 0)) {
                if (field->getSymbol(x, y) == '~') {
                    found_fire = true;
                    break;
                }
            }
        }
        if (found_fire) break;
    }
    
    EXPECT_TRUE(found_fire);
}

TEST_F(YardDragonTest, UpdateFireVisual)
{
    // Сначала создаем огненные эффекты
    dragon->FireAttack(*field, *player);
    
    // Запоминаем символы на поле
    char symbols[30][15];
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 15; j++) {
            symbols[i][j] = field->getSymbol(i, j);
        }
    }
    
    // Вызываем обновление визуальных эффектов огня, что должно очистить все символы '~'
    dragon->UpdateFireVisual(*field, *player);
    
    // Проверяем, что все огненные эффекты были удалены
    bool found_fire = false;
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 15; j++) {
            if (symbols[i][j] == '~' && field->getSymbol(i, j) == '~') {
                found_fire = true;
                break;
            }
        }
        if (found_fire) break;
    }
    
    EXPECT_FALSE(found_fire); // Все огненные эффекты должны исчезнуть
}

TEST_F(YardDragonTest, OnDeath)
{
    unsigned int initial_player_exp = player->getExp();
    unsigned int initial_player_gold = player->getGold();
    
    dragon->takeDamage(initial_health);
    EXPECT_FALSE(dragon->isAlive());

    EXPECT_EQ(player->getExp(), initial_player_exp + dragon->getExp());
    EXPECT_EQ(player->getGold(), initial_player_gold + dragon->getExp() * 2);
} 