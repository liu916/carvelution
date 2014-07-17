#include <stdio.h>
#include <Box2d/Box2d.h>
#include "randomgen.hpp"
#include "configurations.hpp"

float32 randAngleWeight()
{
  /*Retrieves a random weight from 0.02 to 1.0
   */
  return conf::minAngleWeight + (static_cast <float> (rand()) / static_cast <float> (RAND_MAX / (1.0 - conf::minAngleWeight)));
}

float32 randLength()
{
  /*Retrieves a random length for either a "leg" or a wheel

    */

  return (static_cast <float> (rand()) / static_cast <float> (RAND_MAX / conf::maxLength));
}

float32 randWheelLength()
{
  return randLength() / 2.0f;
}

int randWheel()
{
  /*rand number from 0 to 7*/
  return rand() % 8;
}

int randHue()
{
  return 64 + (rand() % 192);
}
