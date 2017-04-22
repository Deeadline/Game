#include "NPC.h"

void NPC::setMonster(int height,int width,Level& level)
{
	srand(time(NULL));
	NPCMap.resize(height);
	for (int y = 0;y < width;y++)
		NPCMap[y].resize(width);

	for (int i = 0;i < height;i++) {
		for (int j = 0;j < width;j++) {
			NPCMap[j][i].type = DEFAULT;
		}
	}
	NPCMap[10][10] = getNPC(0);
	NPCMap[29][16] = getNPC(2);
	int i = 0;
	while (i<30) {
		int x = rand() % height + 0;
		int y = rand() % width + 0;
		if (x != 3 && y != 2) {
			if (!level.map[y][x].collideable && (NPCMap[y][x].type != TRADER || NPCMap[y][x].type != BOSS)) {
				float c = (rand() % 101 + 0) / 100;
				if (c >= 1 - level.map[y][x].chance) {
					NPCMap[y][x] = getNPC(1);
					i++;
				}
			}
		}
	}
}
NPC::Npc NPC::getNPC(short code)
{
	Npc npcc;
	npcc.type = NPCType(code);
	switch (NPCType(code))
	{
	case NPC::MONSTER:
		npcc.interactable = true;
		break;
	case NPC::TRADER:
		npcc.interactable = true;
		break;
	case NPC::BOSS:
		npcc.interactable = true;
		break;
	default:
		npcc.interactable = false;
		break;


	}
	return npcc;
}
int NPC::check(Vector2i position)
{
	if (NPCMap[position.y][position.x].type == TRADER) return 0;
		if (NPCMap[position.y][position.x].type == MONSTER) return 1;
			if (NPCMap[position.y][position.x].type == BOSS) return 2;
}
void Trader::action()
{

}
void Monster::action()
{

}
void Boss::action()
{

}