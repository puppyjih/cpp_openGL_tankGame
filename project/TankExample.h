#pragma once
#include <iostream>
#include <time.h>
#include "Game2D.h"
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#define PI 3.14159265

namespace jm
{
	class Battleground
	{
	public:
		vec2 center = vec2(0.0f, -1.0f);

		Battleground()
		{}

		void draw()
		{
			beginTransformation();
			{
				translate(0.0f, -1.0f);
				drawFilledBox(Colors::olive, 5.0f, 0.6f);
			}
			endTransformation();
		}
	};

	class MyTank
	{
	public:
		vec2 center = vec2(-1.5f, -0.7f);
		double hp = 100;
		double angle = 0;
		//vec2 direction = vec2(1.0f, 0.0f, 0.0f);

		void draw()
		{
			beginTransformation();
			{
				translate(center);
				drawFilledBox(Colors::green, 0.25f, 0.1f); // body
				translate(0.0f, 0.25f);
				drawFilledBox(Colors::green, 0.25f * hp / 100, 0.05f);
				drawWiredBox(Colors::gray, 0.25f, 0.05f);
				translate(0.0f, -0.25f);
				translate(-0.05f, 0.08f);
				drawFilledCircle(Colors::blue, 0.06f); // turret
				rotate(angle);
				translate(0.135f, 0.0f);
				drawFilledBox(Colors::red, 0.15f, 0.03f);  // barrel
				rotate(-angle);
			}
			endTransformation();
		}
	};

	class EnemyTank
	{
	public:
		vec2 right_side = vec2(1.0f, -0.7f);
		double hp = 100;
		double e_angle = 0;
		vec2 velocity = vec2(0.0f, 0.0f);
		//vec2 direction = vec2(1.0f, 0.0f, 0.0f);

		void draw()
		{
			beginTransformation();
			{
				translate(right_side);
				drawFilledBox(Colors::red, 0.25f, 0.1f); // body
				translate(0.0f, 0.25f);
				drawFilledBox(Colors::red, 0.25f *(hp / 100), 0.05f);
				drawWiredBox(Colors::gray, 0.25f, 0.05f);
				translate(0.0f, -0.25f);
				translate(+0.05f, 0.08f);
				drawFilledCircle(Colors::red, 0.06f); // turret
				rotate(e_angle);
				translate(-0.135f, 0.0f);
				drawFilledBox(Colors::red, 0.15f, 0.03f);  // barrel
				rotate(-e_angle);
			}
			endTransformation();
		}

		/*void update(const float& dt)
		{
			srand(time(NULL));

			double random = rand() % 151;
			double i = 0;
			random = random / 0.01f + 0.25;

			velocity.x = random;

			if (i <= random)
			{
				right_side.x += velocity.x * dt;
				i++;
			}

		}*/
	};

	class MyBullet : public MyTank, EnemyTank
	{
	public:
		vec2 Bullet_center = vec2(0.0f, 0.0f);
		vec2 velocity = vec2(0.0f, 0.0f);
		double b_angle = 0;
		//double startTime = 0;
		//double endTime = 0;
		double gravity = 0;

		void draw()
		{
			beginTransformation();
			{
				//rotate(b_angle);
				translate(Bullet_center);
				translate(-0.05f, 0.08f);
				rotate(b_angle);
				translate(0.2f, 0.0f);
				drawFilledRegularConvexPolygon(Colors::yellow, 0.02f, 8);
				drawWiredRegularConvexPolygon(Colors::gray, 0.02f, 8);
				rotate(-b_angle);
			}
			endTransformation();
		}

		void update(const float& dt)
		{
			//startTime = glfwGetTime();
			//Bullet_center += velocity * dt;
			beginTransformation();
			{
				//std::cout << glfwGetTime() << " : glfwGetTime and " << startTime << " : startTime \nSo " << glfwGetTime() - startTime << " is the time" << std::endl;
				if (Bullet_center.y >= -0.8) //&& abs((Bullet_center.x - enemytank.right_side.x)))
				{

					//rotate(b_angle);
					Bullet_center.x += velocity.x * dt * cos(b_angle*PI / 180);
					Bullet_center.y += velocity.y * dt * sin(b_angle*PI / 180) - 0.000005f * 0.00005f * gravity * gravity;//(glfwGetTime()-startTime)*(glfwGetTime()-startTime);

				}


			}
			endTransformation();

			gravity++;
		}
	};

	class EnemyBullet : public EnemyTank
	{
	public:
		vec2 Bullet_center = vec2(0.0f, 0.0f);
		vec2 velocity = vec2(0.0f, 0.0f);
		double b_angle = 0;
		//double startTime = 0;
		//double endTime = 0;
		double gravity = 0;

		void draw()
		{
			beginTransformation();
			{
				//rotate(b_angle);
				translate(Bullet_center);
				translate(0.05f, 0.08f);
				rotate(b_angle);
				translate(-0.2f, 0.0f);
				drawFilledRegularConvexPolygon(Colors::red, 0.02f, 8);
				drawWiredRegularConvexPolygon(Colors::gray, 0.02f, 8);
				rotate(-b_angle);
			}
			endTransformation();
		}

		void update(const float& dt)
		{
			//startTime = glfwGetTime();
			//Bullet_center += velocity * dt;
			beginTransformation();
			{
				//std::cout << glfwGetTime() << " : glfwGetTime and " << startTime << " : startTime \nSo " << glfwGetTime() - startTime << " is the time" << std::endl;
				if (Bullet_center.y >= -0.8) //&& abs((Bullet_center.x - enemytank.right_side.x)))
				{

					//rotate(b_angle);
					Bullet_center.x -= velocity.x * dt * cos(b_angle*PI / 180);
					Bullet_center.y += velocity.y * dt * sin(b_angle*PI / 180) - 0.000005f * 0.00005f * gravity * gravity;//(glfwGetTime()-startTime)*(glfwGetTime()-startTime);

				}


			}
			endTransformation();

			gravity++;
		}
	};

	class TankExample : public Game2D
	{
	public:
		MyTank tank;
		EnemyTank enemytank;
		Battleground battleground;
		int turn = 0;
		int hp_indicator = 0;
		int isDeleted = 0;
		int isDeleted_E = 1;
		int isGetLaunched = 0;

		MyBullet *bullet = nullptr;
		EnemyBullet *bullet_E = nullptr;
		//TODO: allow multiple bullets
		//TODO: delete bullets when they go out of the screen

	public:
		TankExample()
			: Game2D("Fortress2", 1920, 1080, false, 1)
		{}

		~TankExample()
		{
			if (bullet != nullptr) delete bullet;
		}

		void update() override
		{
			srand(time(NULL));
			int random = rand() % 5 + 1;

			if (turn == 0) {
				// move tank
				if (isKeyPressed(GLFW_KEY_LEFT))
				{
					if (tank.center.x >= -1.75f)
					{
						tank.center.x -= 0.03f * getTimeStep();
					}
				}
				if (isKeyPressed(GLFW_KEY_RIGHT))
				{
					if (tank.center.x <= -0.25f)
					{
						tank.center.x += 0.03f * getTimeStep();
					}
				}
				if (isKeyPressed(GLFW_KEY_UP))
				{
					if (tank.angle <= 110) {
						tank.angle += 0.2f;
						//bullet->angle += 0.2f;
					}

				}
				if (isKeyPressed(GLFW_KEY_DOWN))
				{
					if (tank.angle >= 0) {
						tank.angle -= 0.2f;
						//bullet->angle -= 0.2f;
					}

				}

				switch (random)
				{
				case 1:
					if (enemytank.right_side.x <= 1.75f)
					{
						enemytank.right_side.x += 0.012f * getTimeStep();
					}
					break;
				case 2:
					if (enemytank.right_side.x >= 0.25f)
					{
						enemytank.right_side.x -= 0.012f * getTimeStep();
					}
					break;
				case 3:
					if (enemytank.e_angle >= -110) {
						enemytank.e_angle -= 0.003f;
						//bullet->angle += 0.2f;
					}
					break;
				case 4:
					if (enemytank.e_angle <= 0) {
						enemytank.e_angle += 0.003f;
						//bullet->angle -= 0.2f;
					}
					break;
				case 5:
					std::cout << "5 choosed" << std::endl;
					 
					if (bullet_E == nullptr && isDeleted_E-- == 1)
					{
						//int random2 = rand() % 8 + 1;
						//if (random2 == 5)
						{
							isDeleted_E = 0;
							bullet_E = new EnemyBullet;
							bullet_E->Bullet_center = enemytank.right_side;
							bullet_E->b_angle = enemytank.e_angle;
							bullet_E->velocity = vec2(0.6f, 0.6f);
						}
					}	
					break;
				default:
					break;
				}
				// shoot a cannon ball
				if (isKeyPressedAndReleased(GLFW_KEY_SPACE))
				{
					bullet = new MyBullet;
					hp_indicator = 0;
					isDeleted = 0;
					bullet->Bullet_center = tank.center;
					bullet->b_angle = tank.angle;
					//bullet->Bullet_center.x += 0.2f;
					//bullet->Bullet_center.y += 0.08f;
					bullet->velocity = vec2(0.6f, 0.6f);

				}

				if (bullet != nullptr)
				{
					if ((bullet->Bullet_center.y <= (enemytank.right_side.y) && (abs(bullet->Bullet_center.x + 0.15f - enemytank.right_side.x)) <= 0.15) && enemytank.hp > 0  && hp_indicator == 0 && isDeleted == 0)
					{
						std::cout << "Enemy Tank's hp : " << enemytank.hp - 10 << std::endl;
						enemytank.hp -= 10;
						hp_indicator = 1;
						isDeleted = 1;
						delete bullet;
					}
					else if (bullet->Bullet_center.y <= (tank.center.y) && (abs(bullet->Bullet_center.x + 0.15f - tank.center.x)) <= 0.1 && tank.hp > 0 && hp_indicator == 0 && bullet->gravity > 200 && isDeleted == 0)
					{
						std::cout << "Your Tank's hp : " << tank.hp - 10 << std::endl;
						tank.hp -= 10;
						hp_indicator = 1;
						isDeleted = 1;
						delete bullet;
					}
					else if ((bullet->Bullet_center.y >= -0.8) && isDeleted == 0) //&& abs((Bullet_center.x - enemytank.right_side.x)))
						bullet->update(0.1*getTimeStep());
					else if (bullet !=nullptr && isDeleted == 0)
					{
						isDeleted = 1;
						delete bullet;
					}
				}

				if (bullet_E != nullptr)
				{
					if ((bullet_E->Bullet_center.y <= (enemytank.right_side.y) && (abs(bullet_E->Bullet_center.x - 0.15f - enemytank.right_side.x)) <= 0.15) && enemytank.hp > 0 && bullet_E->gravity > 400 && hp_indicator == 0 && isDeleted_E == 0)
					{
						std::cout << "Enemy Tank's hp : " << enemytank.hp - 10 << std::endl;
						enemytank.hp -= 10;
						hp_indicator = 1;
						isDeleted = 1;
						bullet_E = nullptr;
						delete bullet_E;
					}
					else if (bullet_E->Bullet_center.y <= (tank.center.y) && (abs(bullet_E->Bullet_center.x - 0.15f - tank.center.x)) <= 0.1 && tank.hp > 0 && hp_indicator == 0 && bullet_E->gravity >400 && isDeleted_E == 0)
					{
						std::cout << "Your Tank's hp : " << tank.hp - 10 << std::endl;
						tank.hp -= 10;
						hp_indicator = 1;
						isDeleted = 1;
						bullet_E = nullptr;
						delete bullet_E;
					}
					else if ((bullet_E->Bullet_center.y >= -0.8) && isDeleted_E == 0) //&& abs((Bullet_center.x - enemytank.right_side.x)))
						bullet_E->update(0.1*getTimeStep());
					else if (bullet_E != nullptr && isDeleted_E == 0)
					{
						isDeleted_E = 1;
						bullet_E = nullptr;
						delete bullet_E;
					}
				}



				// rendering
				battleground.draw();
				tank.draw();
				enemytank.draw();
				//enemytank.update(0.1*getTimeStep());
				if (bullet != nullptr) //&& bullet->center.y >= -0.8)
					bullet->draw();
				if (bullet_E != nullptr && isDeleted_E == 0)
					bullet_E->draw();
			}
			/*else if (turn == 1) {
				// move tank
				if (isKeyPressed(GLFW_KEY_LEFT))	enemytank.right_side.x -= 0.1f * getTimeStep();
				if (isKeyPressed(GLFW_KEY_RIGHT))	enemytank.right_side.x += 0.1f * getTimeStep();
				if (isKeyPressed(GLFW_KEY_UP))
				{
					if (enemytank.e_angle <= 110)
						enemytank.e_angle += 0.2f;
				}
				if (isKeyPressed(GLFW_KEY_DOWN))
				{
					if (enemytank.e_angle >= 0)
						enemytank.e_angle -= 0.2f;
				}

				// shoot a cannon ball
				if (isKeyPressedAndReleased(GLFW_KEY_SPACE))
				{
					bullet = new MyBullet;
					bullet->Bullet_center = enemytank.right_side;
					bullet->Bullet_center.y += 0.08f;
					bullet->velocity = vec2(-2.0f, 0.0f);
					turn == 0;
				}

				if (bullet != nullptr) bullet->update(0.05*getTimeStep());

				// rendering
				tank.draw();
				enemytank.draw();
				if (bullet != nullptr) bullet->draw();
				if (bullet_E != nullptr) bullet_E->draw();
			}*/


		}
	};
};