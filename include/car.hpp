#ifndef CAR_HPP
#define CAR_HPP

class Simulation;

#include <SFML/Graphics.hpp>
#include <Box2d/Box2d.h>
#include "genome.hpp"

class Car
{
  /*The generic genetic car class*/
  float32 legAngleWeight[8];//Weights are between 0.02 and 1.0, they determine how angle much a "leg" covers relative to other angles
  float32 legLength[8];
  int wheelLeg[2];
  float32 wheelLength[2];
  sf::Color color;
  b2Body* body;
  b2Body* wheelBody[2];
  b2RevoluteJoint* axis[2];
  b2World* world;
  sf::ConvexShape drawPolygon;
  sf::CircleShape drawWheel[2];

  void buildBody();//build the body in b2World
public:
  Car(b2World* setWorld);//initialize random Car
  Car(float32 setAngleWeight[8], float32 setLegLength[8], int setWheelLeg[2], float32 setWheelLength[2], sf::Color setColor, b2World* setWorld);
  Car(Genome& gene, b2World* setWorld);
  ~Car();
  void reset();
  void reset(float32 setAngleWeight[8], float32 setLegLength[8], int setWheelLeg[2], float32 wheelLength[2], sf::Color setColor);
  void reset(Genome& gene);
  void destroy();//destroy car parts from world
  void draw(sf::RenderWindow& window);
  void draw(Simulation& sim);
  b2Vec2 getCenter() const;
};

#endif
