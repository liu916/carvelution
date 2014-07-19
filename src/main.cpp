#include <SFML/Graphics.hpp>
#include <Box2d/Box2d.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include "../include/car.hpp"
#include "../include/ground.hpp"
#include "../include/randomgen.hpp"
#include "../include/configurations.hpp"

int main()
{
  srand(time(NULL));

  sf::RenderWindow window(sf::VideoMode(conf::windowHeight, conf::windowLength), "Carvelution");
  sf::View view(sf::FloatRect(-300.0, 0, conf::windowHeight, conf::windowLength));
  window.setVerticalSyncEnabled(true);
  window.setFramerateLimit(conf::fps);
  
  b2World world(conf::gravity);
  b2Vec2 center;
  Car car(&world);
  Ground ground(&world);

  int frames = 0;
  int seconds = -1;//gives the car more time in the start of the simulation
  float32 timeGoal = 0;//if the maxDist is not greater than timeGoal in conf::timeLimit, than end the car trial
  float32 maxDist = 0;
  int extensions = 0;
  float32 extensionUnit = conf::drawScale * ((float32)conf::extendNumber * conf::extendUnitLength);

  while (window.isOpen())
    {
      sf::Event event;
      while (window.pollEvent(event))
        {
          if (event.type == sf::Event::Closed)
            window.close();
        }

      center = car.getCenter();
      if (center.x > maxDist)
	{
	  maxDist = center.x;
	  if (maxDist >= extensions * extensionUnit + extensionUnit / 2)
	    {
	      extensions++;
	      ground.extend();
	    }
	}
      frames++;
      if (frames == conf::fps)
	{
	  frames = 0;
	  seconds++;
	  if (seconds == conf::timeLimit)
	    {
	      seconds = 0;
	      if (maxDist <= timeGoal + 10)
		{
		  seconds = -1;
		  maxDist = 0;
		  timeGoal = 0;
		  car.destroy();
		  car.reset();
		  center = car.getCenter();
		}
	      else
		{
		  timeGoal = maxDist;
		}
	    }
	}

      view.setCenter(center.x, center.y);
      window.setView(view);
      window.clear(sf::Color::White);
      world.Step(conf::timeStep, conf::velocityIterations, conf::positionIterations);
      car.draw(window);
      ground.draw(window);
      window.display();
    }

  return 0;
}