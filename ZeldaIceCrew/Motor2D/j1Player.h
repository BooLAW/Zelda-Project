#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "j1Module.h"
#include "j1App.h"

class j1Player : public j1Module {
private:
	struct {
		int x, y;
	}pos;

	// Animation -->  Make the Animation blit inside the Draw foo

public:
	j1Player();
	virtual ~j1Player();

private:
	bool Update(float dt);
	bool PostUpdate(float dt);
	
	void Draw();

};

#endif // !__PLAYER_H__
