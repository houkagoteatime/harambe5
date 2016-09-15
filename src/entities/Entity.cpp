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
  rot.Y = std::atan((pos.Z - target.Z) / (pos.X - target.X)) * 180.0f / irr::core::PI;
  
  if((target.X - pos.X) > 0) {
    rot.Y = 180 - rot.Y;
  } else if((target.X - pos.X) < 0) {
    rot.Y = -180 - rot.Y;
  }
  
}
