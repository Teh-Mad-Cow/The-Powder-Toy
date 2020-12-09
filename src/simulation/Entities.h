#ifndef ENTITIES_H_
#define ENTITIES_H_

#define MAX_ENTITIES 20
struct entityst //remodeled after stickmen
{
	char comm;           //command cell
	float accs[8];       //accelerations //?
	char spwn;           //if stick man was spawned // i don't think we use this, since we spawn directly. Hmm..
	unsigned int frames; //frames since last particle spawn - used when spawning LIGH
	int spawnID;         //id of the SPWN particle that spawns it //might be useful, but idk
	
	//now inject other entity data here
};

#endif
