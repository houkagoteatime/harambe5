#include "Entity.h"
#include <cmath>
Entity::Entity(irr::IrrlichtDevice* dev, const std::string& mediaPath, 
	       irr::core::vector3df position, 
	       irr::core::vector3df rotation) : device(dev),
	       path(mediaPath), 
	       pos(position), 
	       rot(rotation)
{

}

void Entity::rotateTowardsPosition(irr::core::vector3df target)
{
  irr::core::vector3df distance = pos - target;
  distance.Y = distance.getHorizontalAngle().Y + 90;
  rot = irr::core::vector3df(0,distance.Y,0);
}
