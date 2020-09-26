#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);
static int graphics(GRAPHICS_FUNC_ARGS);

void Element::Element_ENTY()
{
	Identifier = "DEFAULT_PT_ENTY";
	Name = "ENTY";
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

	Flammable = 10;
	Explosive = 0;
	Meltable = 0;
	Hardness = 30;

	Weight = 85;

	HeatConduct = 70;
	Description = "Entities for TPTerraria.";
	
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
}

static int update(UPDATE_FUNC_ARGS)
{
	// update code here

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

