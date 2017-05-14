#include "EntityManager.h"

//Constructor and destructor
EntityManager::EntityManager() {

}

EntityManager::~EntityManager() {



}

Enemy * EntityManager::CreateEnemy(uint subtype)
{
	Enemy* ret = nullptr;
	//LOG("CREATE ENEMY");
	//LOG("SUBT: %d", subtype);
	switch (subtype) {
	case t_bluesoldier:
		ret = new BSoldier();
		break;
	case t_bluearcher:
		ret = new BlueArcher();
		break;
	case t_redsoldier:
		ret = new RSoldier();
		break;
	case t_greensoldier:
		ret = new GSoldier();
		break;
	case t_hinox:
		ret = new Hinox();
		break;
	case t_rope:
		ret = new Rope();
		break;
	case t_geldman:
		ret = new Geldman();
		break;
	case t_freezor:
		ret = new Freezor();
    break;
	case t_GBat:
		ret = new GreyBat();
		break;
	case t_beamos:
		ret = new Beamos();
		break;
	case t_boss_ballandchain:
		ret = new BossChainBall();
		break;
	case t_boss_agahnim:
		ret = new BossAgahnim();
		break;
	case t_boss_agahnimclone:
		ret = new AgahnimClones();
		break;
	default:
		LOG("Unknown Enemy Type: %d", subtype);
		break;
	}

	ret->type = enemy;

	ret->Start();

	App->entitymanager->PushEntity(ret);

	//LOG("CREATE ENEMY");

	return ret;
}

Item * EntityManager::CreateItem(uint subtype)
{
	Item* ret = nullptr;

	uint rnd_i = 0;

	switch (subtype) {
	case power_gauntlet:
		ret = new PowerGauntlet();
		ret->type = item;
		break;
	case pegasus_boots:
		ret = new PegasusBoots();
		ret->type = item;
		break;
	case heart_container:
		ret = new HeartContainer();
		ret->type = item;
		break;
	case gold_gauntlet:
		ret = new GoldenGauntlet();
		ret->type = item;
		break;
	case wind_cape:
		ret = new WindCape();
		ret->type = item;
		break;
	case magic_hammer:
		ret = new MagicHammer();
		ret->type = item;
		break;
	case small_shield:
		ret = new SmallShield();
		ret->type = item;
		break;
	case vanguard_emblem:
		ret = new VanguardEmblem();
		ret->type = item;
		break;
	case magic_sphere:
		ret = new MagicSphere();
		ret->type = item;
		break;
	case magic_mirror:
		ret = new MagicMirror();
		ret->type = item;
		break;
	case golden_shield:
		ret = new GoldenShield();
		ret->type = item;
		break;
	case mysterious_dust:
		ret = new MysteriousDust();
		ret->type = item;
		break;
	case odd_mushroom:
		ret = new OddMushroom();
		ret->type = item;
		break;
	case bag_of_rupees:
		ret = new BagOfRupees();
		ret->type = item;
		break;
	case icon_of_power:
		ret = new IconOfPower();
		ret->type = item;
		break;
	case icon_of_valor:
		ret = new IconOfValor();
		ret->type = item;
		break;
	case icon_of_wisdom:
		ret = new IconOfWisdom();
		ret->type = item;
		break;

	case boss_key:
		ret = new BossKey();
		ret->type = item;
		break;
	case drop_heart:
		ret = new DropHeart();
		ret->type = drop;
		break;
	case drop_potion:
		ret = new DropPotion();
		ret->type = drop;
		break;
	case drop_rupee:
		ret = new DropRupee();
		ret->type = drop;
		break;
	case drop_fiverupee:
		ret = new DropFiveRupee();
		ret->type = drop;
		break;
	case drop_tenrupee:
		ret = new DropTenRupee();
		ret->type = drop;
		break;
	case weapon_sword:
		ret = new ItemSword();
		ret->type = weapon;
	case weapon_bow:
		ret = new ItemBow();
		ret->type = weapon;
	case t_rand_item:
		rnd_i = rand() % 16;
		ret = CreateItem(rnd_i);
		break;
	default:
		LOG("Unknown Item Type: %d", subtype);
		break;
	}

	if (ret != nullptr) {
		
		ret->Start();

		App->entitymanager->PushEntity(ret);

	}

	return ret;
}

Block * EntityManager::CreateBlock(uint type)
{
	Block* ret = nullptr;
	
		switch (type) {
		case bush:
			ret = new Bush();
			break;
		case pot:
			ret = new Pot();
			break;
		case statue:
			ret = new Statue();
			break;
		case torch_bowl:
			ret = new Torch_Bowl();
			break;
		/*case torch_pillar:
			ret = new Torch_Pillar();
			break;*/
		case slabs:
			ret = new Slab();
			break;
		case slabs_no_move :
			ret = new Slab_No_Move();
			break;
		case slabs_spikes:
			ret = new Slab_Spikes();
			break;
		case button_wall:
			ret = new Button_Wall();
			break;
		case pressure_plate:
			ret = new Pressure_Plate();
			break;
		default:
			LOG("Unknown Block Type: %d", type);
			break;
									
	}
	
	ret->type = block;
	
	ret->Start();
	
	App->entitymanager->PushEntity(ret);
	
	return ret;
}

Npc * EntityManager::CreateNPC(NPC_TYPE type, int id)
{
	Npc* ret = NULL;

	switch (type)
	{
	case NPC_ZELDA:
		ret = new Npc_Zelda();
		ret->type = type;
		ret->npcId = id;
		ret->pos = { 0,0 };
		ret->SetTexture(App->tex->Load("Sprites/Npc.png"));
		ret->SetRect({ 0,0,42,52 });
		ret->HitBox = App->collisions->AddCollider({ 0, 0, 40, 25 }, COLLIDER_NPC);

		break;
	case NPC_UNCLE:
		ret = new Npc_Uncle();
		ret->type = type;
		ret->npcId = id;
		ret->SetTexture(App->tex->Load("Sprites/Npc.png"));
		ret->SetRect({ 0,0,42,52 });
		ret->HitBox = App->collisions->AddCollider({ 0, 0, 32, 32 }, COLLIDER_NPC);

		break;
	case NPC_HIPPIE:
		ret = new Npc_Hippie();
		ret->type = type;
		ret->npcId = id;
		ret->SetTexture(App->tex->Load("Sprites/Npc.png"));
		ret->SetRect({ 0,0,42,52 });
		ret->HitBox = App->collisions->AddCollider({ 0, 0, 32, 32 }, COLLIDER_NPC);

		break;
	case NPC_FARM_KID:
		ret = new Npc_Farm_Kid();
		ret->type = type;
		ret->npcId = id;
		ret->SetTexture(App->tex->Load("Sprites/Npc.png"));
		ret->SetRect({ 0,0,42,52 });
		ret->HitBox = App->collisions->AddCollider({ 0, 0, 32, 32 }, COLLIDER_NPC);

		break;
	case NPC_WOMAN:
		ret = new Npc_Woman();
		ret->type = type;
		ret->npcId = id;
		ret->SetTexture(App->tex->Load("Sprites/Npc.png"));
		ret->SetRect({ 0,0,42,52 });
		ret->HitBox = App->collisions->AddCollider({ 0, 0, 32, 32 }, COLLIDER_NPC);

		break;
	case NPC_GRANDMA:
		ret = new Npc_Grandma();
		ret->type = type;
		ret->npcId = id;
		ret->SetTexture(App->tex->Load("Sprites/Npc.png"));
		ret->SetRect({ 0,0,42,52 });
		ret->HitBox = App->collisions->AddCollider({ 0, 0, 32, 32 }, COLLIDER_NPC);

		break;
	case NPC_TAVERN_OLD_MAN:
		ret = new Npc_Tavern_Old_Man();
		ret->type = type;
		ret->npcId = id;
		ret->SetTexture(App->tex->Load("Sprites/Npc.png"));
		ret->SetRect({ 0,0,42,52 });
		ret->HitBox = App->collisions->AddCollider({ 0, 0, 32, 32 }, COLLIDER_NPC);

		break;
	case NPC_LITTLE_KID:
		ret = new Npc_Little_Kid();
		ret->type = type;
		ret->npcId = id;
		ret->SetTexture(App->tex->Load("Sprites/Npc.png"));
		ret->SetRect({ 0,0,42,52 });
		ret->HitBox = App->collisions->AddCollider({ 0, 0, 32, 32 }, COLLIDER_NPC);

		break;

	default:
		return nullptr;
	}
	if (ret != nullptr) {

		App->entitymanager->PushEntity(ret);

	}
	/*ret->pos = { x,y };

	if (ret->Spawn(dir[npc], ret->pos, type))
	{
		ret->type = npc;
		entities.push_back(ret);		
		ret->id = entities.end();

		//For dialog purposes
		ret->npcId = id;
	}
	else
	{
		RELEASE(ret);
		ret = NULL;
	}
	*/
	return ret;
}




bool EntityManager::CleanUp()
{
	App->tex->UnLoad(npc_tex);
	DestroyEntities();
	return true;
	
}

bool EntityManager::Start(){
	
	
	npc_tex = App->tex->Load("Sprites/Npc.png");
	
	return true;
}

bool EntityManager::Awake(pugi::xml_node & config)
{
	bool ret = true;


	pugi::xml_node entityAttributes = config.child("entityAttributes");
	std::string folder = entityAttributes.attribute("folder").as_string("/");
	pugi::xml_node entity = entityAttributes.first_child();

	for (int tmp = 0; !entity.empty(); tmp++)
	{
		dir.insert(std::pair<ENTITYTYPE, std::string >(ENTITYTYPE(tmp), (folder + entity.attribute("file").as_string(".xml"))));
		entity = entity.next_sibling();
	}

	return ret;
}

bool EntityManager::PreUpdate()
{

	for (uint i = 0; i < entities.size(); i++) {
		if (entities[i] != nullptr && entities[i]->to_delete == true) {
			entities[i]->to_delete = false;
			DestroyEnity(entities[i]);
		}
	}

	return true;
}

bool EntityManager::Update(float dt) {

	
	
		//LOG("ENTITY UPDT START");
		if (entities.empty() == false)
			for (int i = 0; i < entities.size(); i++) {
				if (entities[i] != nullptr) {
					if (!App->IsPaused()) {
						//LOG("ENTITY UPDATE %d", i);
						if (entities[i]->active == true)
							entities[i]->Update(dt);
					}
					else {
						if (entities[i]->active == true)
							entities[i]->Draw(dt);
					}
				}
			}
	
	


	//LOG("ENTITY UPDT END");


	return true;
}

void EntityManager::PushEntity(Entity * ent)
{
	if (ent != nullptr)
		entities.push_back(ent);
	else
		LOG("Error Pushing Entity to Entities List");
}


void EntityManager::DestroyEntities()
{
	for (uint i = 0; i < entities.size(); i++) {
		if (entities[i] != nullptr) {
			DestroyEnity(entities[i]);
			//RELEASE(entities[i]);
		}
	}
}

void EntityManager::DestroyEnity(Entity * ent)
{

	if (ent != nullptr) {

			LOG("ENTITY CLEAR");
			std::deque<Entity*>::iterator aux = std::find(entities.begin(), entities.end(), ent);
				if (aux != entities.end()) {
					entities.erase(aux);
				}
			LOG("ENTITY TYPE %d", ent->type);
			ent->CleanUp();
			LOG("ENT CLEAR");
			//std::deque<Entity*>::iterator aux = std::find(entities.begin(), entities.end(), ent);
			//if(ent != nullptr)
			//	RELEASE(ent);
			//
			//ent = nullptr;

	}

	LOG("ENTITY DESTROYED");
}

void EntityManager::OnCollision(Collider * c1, Collider * c2)
{
	
}

uint EntityManager::fromEntoPlDir(uint EnDir)
{
	uint ret = NULL;

	switch (EnDir) {
	case 0: // Up
		ret = 1;
		break;
	case 1: // Down
		ret = 4;
		break;
	case 2: // Right
		ret = 3;
		break;
	case 3: // Left
		ret = 2;
		break;
	}

	return ret;
}

