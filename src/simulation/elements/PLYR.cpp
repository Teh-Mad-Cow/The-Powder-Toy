#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);
static int graphics(GRAPHICS_FUNC_ARGS);
static bool createAllowed(ELEMENT_CREATE_ALLOWED_FUNC_ARGS);
static void changeType(ELEMENT_CHANGETYPE_FUNC_ARGS);
int Element_PLYR_entity_controller(entityst* entityp, UPDATE_FUNC_ARGS);

#define PLYR_RUNNING_VELOCITY		1
#define PLYR_RUNNING_ACCELERATION	0.5
#define PLYR_JUMPING_VELOCITY		2

void Element::Element_PLYR()
{
	Identifier = "DEFAULT_PT_PLYR";
	Name = "PLYR";
	Colour = PIXPACK(0x186795);
	MenuVisible = 1;
	MenuSection = SC_SPECIAL;
	Enabled = 1;

	// element properties here
	Advection = 0.7f;
	AirDrag = 0.02f * CFDS;
	AirLoss = 0.96f;
	Loss = 0.80f;
	Collision = 0.0f;
	Gravity = 0.1f;
	Diffusion = 0.00f;
	HotAir = 0.000f * CFDS;
	Falldown = 1;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 30;

	Weight = 85;

	HeatConduct = 70;
	Description = "Player for TPTerraria.";
	
	Properties = TYPE_PART;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &update;
	Graphics = &graphics;
	CreateAllowed = &createAllowed;
	ChangeType = &changeType;
}

static int update(UPDATE_FUNC_ARGS)
{
	// update code here
	Element_PLYR_entity_controller(&sim->terraria_player, UPDATE_FUNC_SUBCALL_ARGS);
	return 0;
}

#define INBOND(x, y) ((x)>=0 && (y)>=0 && (x)<XRES && (y)<YRES)

//lets keep it simple and not worry about different shaped players yet.
int Element_PLYR_entity_controller(entityst* playerp, UPDATE_FUNC_ARGS) {
	int t = parts[i].type;
	//TODO: gravity

	//left
	if (((playerp->comm & 0x01) == 0x01) && parts[i].vx > -PLYR_RUNNING_VELOCITY)
	{
		parts[i].vx -= PLYR_RUNNING_ACCELERATION;
	}

	//right
	if (((playerp->comm & 0x02) == 0x02) && parts[i].vx < PLYR_RUNNING_VELOCITY)
	{
		parts[i].vx += PLYR_RUNNING_ACCELERATION;
	}

	//down
	if ((playerp->comm & 0x08) == 0x08)
	{

	}

	//jump
	if ((playerp->comm & 0x04) == 0x04)
	{
		if (parts[i].vy > -PLYR_JUMPING_VELOCITY) {
			int r = pmap[y + 1][x];
			if (!r)
				r = sim->bmap[(y + 1) / CELL][(x) / CELL];
			if (r)
				parts[i].vy -= PLYR_JUMPING_VELOCITY;
		}
	}

	return 0;
}

static int graphics(GRAPHICS_FUNC_ARGS)
{
	// graphics code here
	if (cpart->ctype&0xFFFFFF)
	{
		*colr = (cpart->ctype >> 16) & 0xFF;
		*colg = (cpart->ctype >> 8) & 0xFF;
		*colb = (cpart->ctype) & 0xFF;
	}
	return 0;
}

static bool createAllowed(ELEMENT_CREATE_ALLOWED_FUNC_ARGS) // TODO: complete these
{
	return sim->elementCount[PT_PLYR] <= 0 && !sim->terraria_player.spwn;
}

static void changeType(ELEMENT_CHANGETYPE_FUNC_ARGS) // TODO: complete these
{
	if (to == PT_PLYR)
		sim->terraria_player.spwn = 1;
	else
		sim->terraria_player.spwn = 0;
}