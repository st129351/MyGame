//Lichkovaha Daniil
//st129351@student.spbu.ru
//Lab_Work_2

#include "AmuletTemplateF.h"
#include "ADash.h"

typedef AmuletTest<ADash> DashTest;
// Тест инициализации
TEST_F(DashTest, Initialization) 
{
    EXPECT_EQ(amulet->getCost(), 25);
    EXPECT_EQ(amulet->getName(), "dash");
    EXPECT_EQ(amulet->getDescription(), "incredible speed, press 'k'");
    EXPECT_EQ(amulet->getSlots(), 8);
    EXPECT_EQ(amulet->getUsage(), false);
}

// Тест рывка вверх
TEST_F(DashTest, amuletUp) 
{
    // Устанавливаем начальную позицию игрока
    player->setX_pos(10);
    player->setY_pos(10);
    
    // Симулируем нажатие клавиши 'w'
    field->setInputSymb('w');
    
    // Выполняем рывок
    amulet->use(*player);
    
    // Проверяем новую позицию игрока
    EXPECT_EQ(player->getY_pos(), 8); // Должен переместиться на 2 клетки вверх
    EXPECT_EQ(player->getX_pos(), 10); // X координата не должна измениться
}

// Тест рывка вправо
TEST_F(DashTest, amuletRight) 
{
    player->setX_pos(10);
    player->setY_pos(10);
    
    field->setInputSymb('d');
    amulet->use(*player);
    
    EXPECT_EQ(player->getX_pos(), 12);
    EXPECT_EQ(player->getY_pos(), 10);
}

// Тест столкновения со стеной
TEST_F(DashTest, WallCollision) 
{
    player->setX_pos(10);
    player->setY_pos(10);
    
    // Создаем стену перед игроком
    field->setSymbol(10, 9, '#');
    
    field->setInputSymb('w');
    amulet->use(*player);
    
    // Игрок не должен переместиться
    EXPECT_EQ(player->getY_pos(), 10);
    EXPECT_EQ(player->getX_pos(), 10);
}

// Тест визуальных эффектов
TEST_F(DashTest, VisualEffects) 
{
    player->setX_pos(10);
    player->setY_pos(10);
    
    field->setInputSymb('w');
    amulet->use(*player);
    
    // Проверяем наличие визуальных эффектов
    EXPECT_EQ(field->getSymbol(10, 10), '|');
    EXPECT_EQ(field->getSymbol(10, 9), '|');
    
    // Проверяем очистку визуальных эффектов
    amulet->UpdateDashVisual();
    EXPECT_EQ(field->getSymbol(10, 10), ' ');
    EXPECT_EQ(field->getSymbol(10, 9), ' ');
}


