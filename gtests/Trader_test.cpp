//Lichkovaha Daniil
//st129351@student.spbu.ru
//Lab_Work_2

#include <gtest/gtest.h>
#include "Trader.h"
#include "Player.h"
#include "GameField.h"
#include "YardDragon.h"
#include <memory>
#include <string>

class TraderTest : public ::testing::Test {
protected:
    std::shared_ptr<Player> player;
    std::shared_ptr<YardDragon> dragon;
    std::shared_ptr<GameField> field;
    std::shared_ptr<Trader> trader;

    void SetUp() override {
        // Создаем все необходимые объекты для тестирования Trader
        player = std::make_shared<Player>("TestPlayer");
        player->setX_pos(10);
        player->setY_pos(10);
        
        // Дракон нужен для создания GameField
        dragon = std::make_shared<YardDragon>("TestDragon", 100, 20, 10, 50, player.get(), 3);
        
        // GameField нужен для создания Trader
        field = std::make_shared<GameField>(*player, dragon);
        
        // Создаем Trader с правильными параметрами (Player& и GameField&)
        trader = std::make_shared<Trader>(*player, *field);
        
        // Устанавливаем позицию торговца на поле
        trader->setX_pos(15);
        trader->setY_pos(12);
        field->setSymbol(15, 12, 'T');
        
        // Добавляем немного золота игроку для тестирования покупок
        player->setGold(100);
    }

    void TearDown() override {
        // Smart pointers handle cleanup
    }
};

TEST_F(TraderTest, Initialization)
{
    // Проверяем, что Trader был инициализирован корректно
    EXPECT_EQ(trader->getName(), "Trader");
    EXPECT_EQ(trader->getDescription(), "Trader, who can sell you different interesting things.");
    EXPECT_FALSE(trader->getDialogueComplete()); // Должно быть false изначально
}

TEST_F(TraderTest, PositionManagement)
{
    // Проверка установки и получения координат
    int new_x = 8, new_y = 9;
    trader->setX_pos(new_x);
    trader->setY_pos(new_y);
    EXPECT_EQ(trader->getX_pos(), new_x);
    EXPECT_EQ(trader->getY_pos(), new_y);
}

TEST_F(TraderTest, Speak)
{
    // Метод speak() не возвращает значения, мы можем только убедиться, 
    // что он не вызывает исключений и устанавливает флаг диалога
    trader->speak();
    EXPECT_TRUE(trader->getDialogueComplete());
}

TEST_F(TraderTest, ShowStore)
{
    // Проверка метода showStore()
    std::string store_info = trader->showStore();
    
    // Проверяем, что строка магазина содержит ожидаемые части
    EXPECT_TRUE(store_info.find("OLD STORE") != std::string::npos);
    EXPECT_TRUE(store_info.find("Number:") != std::string::npos);
    EXPECT_TRUE(store_info.find("Amulet:") != std::string::npos);
    EXPECT_TRUE(store_info.find("Cost:") != std::string::npos);
    
    // После showStore() флаг диалога должен быть установлен
    EXPECT_TRUE(trader->getDialogueComplete());
} 