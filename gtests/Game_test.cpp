//Lichkovaha Daniil
//st129351@student.spbu.ru
//Lab_Work_2

#include <gtest/gtest.h>
#include "Game.h"
#include "Player.h"
#include "GameField.h"
#include "YardDragon.h"
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <memory>
#include <string>

// Класс-хелпер для имитации ввода с клавиатуры
class KeyboardInputSimulator {
private:
    int original_stdin;
    int pipe_fds[2]; // file descriptors для pipe
    
public:
    KeyboardInputSimulator() {
        // Сохраняем оригинальный stdin
        original_stdin = dup(STDIN_FILENO);
        
        // Создаем pipe
        if (pipe(pipe_fds) != 0) {
            throw std::runtime_error("Не удалось создать pipe");
        }
        
        // Перенаправляем stdin на чтение из pipe
        dup2(pipe_fds[0], STDIN_FILENO);
    }
    
    // Симулируем нажатие клавиши
    void simulateKeyPress(char key) {
        write(pipe_fds[1], &key, 1);
    }
    
    // Симулируем множественные нажатия клавиш
    void simulateKeyPresses(const std::string& keys) {
        write(pipe_fds[1], keys.c_str(), keys.length());
    }
    
    ~KeyboardInputSimulator() {
        // Восстанавливаем оригинальный stdin
        dup2(original_stdin, STDIN_FILENO);
        
        // Закрываем дескрипторы pipe
        close(pipe_fds[0]);
        close(pipe_fds[1]);
        close(original_stdin);
    }
};

class GameTest : public ::testing::Test {
protected:
    std::unique_ptr<Player> player;
    std::unique_ptr<Game> game;

    void SetUp() override {
        player = std::make_unique<Player>("TestPlayer");
        game = std::make_unique<Game>(*player);
    }

    void TearDown() override {
        // Smart pointers handle cleanup
    }
};

// Тестирование базовой инициализации игры
TEST_F(GameTest, BasicInitialization)
{
    // Проверяем, что игра была создана успешно
    EXPECT_NE(game.get(), nullptr);
    
    // Проверка, что игра содержит игрока с правильным именем
    EXPECT_EQ(player->getName(), "TestPlayer");
}

// Тестирование режимов терминала
TEST_F(GameTest, TerminalModes)
{
    // Проверка, что методы enableRawMode и disableRawMode не вызывают ошибок
    // Их нельзя полноценно протестировать без контроля за реальным терминалом,
    // но мы может проверить, что они выполняются без исключений
    EXPECT_NO_THROW({
        game->enableRawMode();
        game->disableRawMode();
    });
}

// Тестирование создания нескольких экземпляров игры
TEST_F(GameTest, MultipleInitialization)
{
    // Проверка создания нескольких экземпляров игры с одним игроком
    for (int i = 0; i < 5; i++) {
        game.reset(new Game(*player));
        EXPECT_NE(game.get(), nullptr);
    }
}