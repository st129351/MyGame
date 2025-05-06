//Lichkovaha Daniil
//st129351@student.spbu.ru
//Lab_Work_2

#include <gtest/gtest.h>
#include "Player.h"
#include "GameField.h"
#include "YardDragon.h"
#include "Enemy.h"
#include <memory>
#include <string>
#include <vector>

class PlayerTest : public ::testing::Test {
protected:
    std::shared_ptr<Player> player;
    std::shared_ptr<YardDragon> dragon;
    std::shared_ptr<GameField> field;

    // Начальные значения для тестов
    const std::string player_name = "TestPlayer";
    const unsigned int initial_health = 100;
    const unsigned int initial_damage = 10;
    const unsigned int initial_gold = 100;
    const unsigned int expected_x_pos = 14; // Стандартная позиция по X в конструкторе Player
    const unsigned int expected_y_pos = 13; // Стандартная позиция по Y в конструкторе Player

    void SetUp() override {
        player = std::make_shared<Player>(player_name);
        dragon = std::make_shared<YardDragon>("TestDragon", 100, 20, 10, 30, player.get(), 3);
        field = std::make_shared<GameField>(*player, dragon);
    }

    void TearDown() override {
        // Smart pointers handle cleanup
    }
};

TEST_F(PlayerTest, Initialization)
{
    EXPECT_EQ(player->getHealth(), initial_health);
    EXPECT_EQ(player->getDamage(), initial_damage);
    EXPECT_EQ(player->getX_pos(), expected_x_pos);
    EXPECT_EQ(player->getY_pos(), expected_y_pos);
    EXPECT_EQ(player->getName(), player_name);
    EXPECT_EQ(player->getLevel(), 1);
    EXPECT_EQ(player->getExp(), 0);
    EXPECT_EQ(player->getGold(), initial_gold);
    EXPECT_EQ(player->getMaxLevel(), 3);
}

TEST_F(PlayerTest, LevelUp)
{
    // Запоминаем начальные значения
    unsigned int initial_level = player->getLevel();
    unsigned int initial_damage = player->getDamage();
    unsigned int initial_gold = player->getGold();
    unsigned int initial_health = player->getHealth();
    
    // Вызываем levelUp
    player->levelUp();
    
    // Проверяем изменения после levelUp
    EXPECT_EQ(player->getLevel(), initial_level + 1);
    EXPECT_EQ(player->getExp(), 0); // Опыт сбрасывается
    EXPECT_GT(player->getGold(), initial_gold); // Золото увеличивается
    EXPECT_GT(player->getDamage(), initial_damage); // Урон увеличивается
    EXPECT_GT(player->getHealth(), initial_health); // Здоровье увеличивается
}

TEST_F(PlayerTest, PositionManagement)
{
    // Тестирование установки и получения координат
    unsigned int new_x = 10, new_y = 15;
    player->setX_pos(new_x);
    player->setY_pos(new_y);
    EXPECT_EQ(player->getX_pos(), new_x);
    EXPECT_EQ(player->getY_pos(), new_y);
}

TEST_F(PlayerTest, ResourceManagement)
{
    // Тестирование управления ресурсами (опыт, золото)
    unsigned int new_exp = 50;
    unsigned int new_gold = 200;
    
    player->setExp(new_exp);
    player->setGold(new_gold);
    
    EXPECT_EQ(player->getExp(), new_exp);
    EXPECT_EQ(player->getGold(), new_gold);
}

TEST_F(PlayerTest, TakeDamage)
{
    // Тестирование урона и смерти
    unsigned int damage = 30;
    player->takeDamage(damage);
    EXPECT_EQ(player->getHealth(), initial_health - damage);
    
    // Нанесение смертельного урона
    player->takeDamage(initial_health);
    EXPECT_FALSE(player->isAlive());
    EXPECT_EQ(player->getHealth(), 0);
}

TEST_F(PlayerTest, AmuletFlags)
{
    EXPECT_FALSE(player->getPersevFlag());
    EXPECT_FALSE(player->getBestExpFlag());
    EXPECT_FALSE(player->getHealFlag());
    EXPECT_FALSE(player->getDashFlag());
    
    EXPECT_EQ(player->getPersev(), nullptr);
    EXPECT_EQ(player->getBestExp(), nullptr);
    EXPECT_EQ(player->getHeal(), nullptr);
    EXPECT_EQ(player->getDash(), nullptr);
    EXPECT_EQ(player->getKillerLook(), nullptr);
    EXPECT_EQ(player->getMadness(), nullptr);
    EXPECT_EQ(player->getFearOfDeath(), nullptr);
}

TEST_F(PlayerTest, AttackArea)
{
    // Тестирование атаки в области
    std::vector<std::shared_ptr<Enemy>> enemies;
    enemies.push_back(dragon);
    
    // Размещаем врага рядом с игроком
    dragon->setX_pos(player->getX_pos() + 1);
    dragon->setY_pos(player->getY_pos());
    
    // Обновляем символ на поле
    field->setSymbol(dragon->getX_pos(), dragon->getY_pos(), 'Y');
    
    // Запоминаем начальное здоровье врага
    unsigned int initial_dragon_health = dragon->getHealth();
    
    // Выполняем атаку
    player->attackArea(*field, enemies);
    
    // Проверяем, что дракон получил урон (если находится в зоне атаки)
    if (abs(dragon->getX_pos() - player->getX_pos()) <= 1 && 
        abs(dragon->getY_pos() - player->getY_pos()) <= 1) {
        EXPECT_LT(dragon->getHealth(), initial_dragon_health);
    }
}

TEST_F(PlayerTest, Inventory)
{
    // Тестирование инвентаря
    std::string inventory = player->showInventory();
    
    // Проверяем, что строка инвентаря не пуста и содержит ожидаемые части
    EXPECT_FALSE(inventory.empty());
    // Инвентарь обычно содержит упоминание о ячейках (Cells)
    EXPECT_NE(inventory.find("Cells"), std::string::npos);
}

TEST_F(PlayerTest, OnDeath)
{
    // Тестирование реакции на смерть
    player->onDeath();
    
    // После onDeath игрок должен быть мертв и иметь 0 здоровья
    EXPECT_FALSE(player->isAlive());
    EXPECT_EQ(player->getHealth(), 0);
} 