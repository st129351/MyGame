#include "Game.h"
#include "Enemy.h"
#include "Slime.h"
#include "Fighter.h"
#include "Amulet.h"
#include "YardDragon.h"
#include "APerseverance.h"
#include "BestExp.h"
#include "AHeal.h"

Game::Game(Player& p) : player(p), field(player, dragon)
{
    dragon = std::make_shared<YardDragon>("Yard Dragon", 200, 30, 45, 100, &player, 5);
    flag = 0;
}

void Game::enableRawMode()
{
    struct termios raw; // struct for storage terminal settings
	tcgetattr(STDIN_FILENO, &raw); // get current terminal settings

	raw.c_lflag &= ~(ICANON | ECHO); // disable canon mode (now without 'enter')
	// disable echo (without repeat letters in the console)

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); // apply settings
	// TCSAFLUSH - apply settings after all input was read
}

void Game::disableRawMode()
{
	struct termios raw;
	tcgetattr(STDIN_FILENO, &raw);
	// return settings as it was
	raw.c_lflag |= (ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void Game::start_game()
{
	// field.slimeSpawn(28, 2);
	// field.banditSpawn(1, 9);
	// field.slimeSpawn(1, 1); // spawn slime
	// field.slimeSpawn(8, 8);
	// field.slimeSpawn(4, 10);
	// field.slimeSpawn(10, 1);
	// field.banditSpawn(3, 2); // spawn bandit
	field.yardDragonSpawn(14, 4); // BOSS (yard dragon) spawn
    field.traderSpawn(13, 13);
	// field.elderSpawn(10, 5);

    enableRawMode();

    while (true)
	{
		std::cout << R"(
 ▄▄▄    ████╗███████╗███╗   ███╗ █████╗     ▄▄▄ 
▐   ▐    ██╔╝╚══███╔╝████╗ ████║██╔══██╗   ▐   ▐
 ▐   ▀▀▄▀██║   ███╔╝ ██╔████╔██║███████║▀▄▀▀  ▐
◇   ██   ██║  ███╔╝  ██║╚██╔╝██║██╔══██║   ██  ◇
   ▐  ▐ ████╗███████╗██║ ╚═╝ ██║██║  ██║  ▐  ▐
  ▐    ▐╚═══╝╚══════╝╚═╝     ╚═╝╚═╝  ╚═╝ ▐    ▐
  ◇     ▐       ▐        ▐       ▐       ▐     ◇
       ◇  ◇      ▐      ▐       ▐       ◇  ◇
                 ◇       ◇      ◇
				   )" << std::endl;
		if (flag <= 1)
		{
			std::cout << "\033[2J\033[1;1H"; // clear the console
			std::cout << "hi, dear " << player.getName() << "!" << std::endl;
			std::cout << "use WASD to move" << std::endl;
			std::cout << "use J to attack, E to talk with NPC" << std::endl;
			std::cout << "use Q to quit" << std::endl;
			flag += 1; // start output message
		}

		// dragon->UpdateFireVisual(field, player);
		
		field.moveEnemies();
		field.combat();
		if (!dragon->getCanMove())
		{
			int new_fire_count = dragon->getFireCount() + 1;
			dragon->setFireCount(new_fire_count);
		}
		if (dragon->getFireCount() == 6)
		{
			int new_fire_count = 0;
			field.setPWasSeenD(false);
			dragon->setFireCount(new_fire_count);
			dragon->setCanMove(true);
		}
		field.draw(); // draw the field
		player.UpdateAttackVisual(field, field.getEnemies());
		
		for (auto& enemy : field.getEnemies())
		{
			std::cout << enemy->getName() << " HP:" << enemy->getHealth() <<std::endl;
		}
		std::cout << "your HP:" << player.getHealth() << "; your EXP: " << player.getExp() << "; your Gold: " << player.getGold() << std::endl;

		if (!player.isAlive())
		{
			break;
		}
		if (isdigit(input))
		{
			// std::cout << "\033[2J\033[1;1H"; // clear the console
			field.Buy(input);
		}
		input = getchar(); // get the input letter from keyboard
		if (input == 'q')
		{
			disableRawMode(); // return settings as it was
			break;
		}
		// for walking use only WASD
		if (input == 'w' || input == 'a' || input == 's' || input == 'd' || input == 'j' ||  input == 'e' || input == 'i')
		{
			std::cout << "\033[2J\033[1;1H"; // clear the console
			field.Movement(input); // processing the input value
		}
		else
		{
			std::cout << "\033[2J\033[1;1H"; // clear the console
		}

		if (player.getPersevFlag())
		{
			player.getPersev()->use(player);
		}
		if (player.getBestExpFlag())
		{
			player.getBestExp()->use(player);
		}
		if (player.getHealFlag())
		{
			player.getHeal()->use(player);
		}
	}
}