#ifndef __DROP_H__
#define __DROP_H__

#include "EntityManager.h"
#include "Entity.h"

class Entity;

enum DROPTYPE {
	rupee = 0,
	heart
};

class Drop : public Entity {
public:
	Drop() {}
	Drop(uint subtype);
	virtual ~Drop() {};



public:
	Drop* CreateDrop(uint type);


};

#endif // !__DROP_H__