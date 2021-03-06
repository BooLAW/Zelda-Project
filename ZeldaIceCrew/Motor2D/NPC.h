#ifndef _NPC_H_
#define _NPC_H_

#include "Entity.h"
#include "j1Input.h"
#include "j1PerfTimer.h"

enum NPC_TYPE
{
	NPC_UNCLE = 0,
	NPC_HIPPIE,
	NPC_FARM_KID,
	NPC_WOMAN,
	NPC_GRANDMA,
	NPC_TAVERN_OLD_MAN,
	NPC_LITTLE_KID,
	NPC_ZELDA
};



class Npc : public Entity
{
public:

	Npc();
	~Npc() {};

	NPC_TYPE npcType;
	
	bool Spawn(std::string file, fPoint pos, NPC_TYPE);
	void Update(float dt);
	void Draw();
	

public:

	int npcId;
	int dialogState;


private:
	//void Change_direction();

	//State Machine


};


class Npc_Zelda : public Npc
{
public:
	Npc_Zelda() : Npc() { npcType = NPC_ZELDA; };
};

class Npc_Farm_Kid : public Npc
{
public:
	Npc_Farm_Kid() : Npc() { npcType = NPC_FARM_KID; };
};

class Npc_Grandma : public Npc
{
public:
	Npc_Grandma() : Npc() { npcType = NPC_GRANDMA; };
};


class Npc_Hippie : public Npc
{
public:
	Npc_Hippie() : Npc() { npcType = NPC_HIPPIE; };
};

class Npc_Little_Kid : public Npc
{
public:
	Npc_Little_Kid() : Npc() { npcType = NPC_LITTLE_KID; };
};

class Npc_Tavern_Old_Man : public Npc
{
public:
	Npc_Tavern_Old_Man() : Npc() { npcType = NPC_TAVERN_OLD_MAN; };
};

class Npc_Uncle : public Npc
{
public:
	Npc_Uncle() : Npc() { npcType = NPC_UNCLE; };
};

class Npc_Woman : public Npc
{
public:
	Npc_Woman() : Npc() { npcType = NPC_WOMAN; };
};
#endif // !_PLAYER_H_