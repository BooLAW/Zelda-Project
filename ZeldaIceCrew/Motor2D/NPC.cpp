#include "NPC.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1FileSystem.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Map.h"
#include "j1Pathfinding.h"
#include "p2Log.h"
#include "Animation.h"
#include "j1PerfTimer.h"

Npc::Npc() : Entity(), dialogState(0) {}

bool Npc::Spawn(std::string file, fPoint pos, NPC_TYPE type)
{

	bool ret = true;

	// set position
	this->pos =  pos;

	// load xml attributes
	pugi::xml_document	attributesFile;
	char* buff;
	int size = App->fs->Load(file.c_str(), &buff);
	pugi::xml_parse_result result = attributesFile.load_buffer(buff, size);
	RELEASE_ARRAY(buff);

	if (result == NULL)
	{
		LOG("Could not load attributes xml file. Pugi error: %s", result.description());
		ret = false;
	}
	else
	{
		pugi::xml_node attributes;

		switch (type)
		{
		case NPC_ZELDA:
			attributes = attributesFile.child("attributes").child("zelda");
			break;
		case NPC_UNCLE:
			attributes = attributesFile.child("attributes").child("uncle");
			break;
		case NPC_HIPPIE:
			attributes = attributesFile.child("attributes").child("hippie");
			break;
		case NPC_FARM_KID:
			attributes = attributesFile.child("attributes").child("farm_kid");
			break;
		case NPC_WOMAN:
			attributes = attributesFile.child("attributes").child("woman");
			break;
		case NPC_GRANDMA:
			attributes = attributesFile.child("attributes").child("grandma");
			break;
		case NPC_TAVERN_OLD_MAN:
			attributes = attributesFile.child("attributes").child("tavern_old_man");
			break;
		case NPC_LITTLE_KID:
			attributes = attributesFile.child("attributes").child("little_kid");
			break;
		}

		//actionState = IDLE;
		LoadAttributes(attributes);
	}

	return ret;
}

void Npc::Update(float dt)
{

	Draw();
	
	
	}


void Npc::Draw()
{
	fPoint aux_pos = { pos.x - 16, pos.y - 14 };

	App->render->toDraw(GetTexture(), HitBox->rect.y + HitBox->rect.h, aux_pos.x, aux_pos.y, &this->rect);
}

