/*
stock IsModelHaveUpgrades(modelid)
stock IsModelUpgradeCompatible(modelid, componentid)
stock GetModelValidUpgrades(modelid, dest[], E_COMPONENT_TYPE:component_type=E_COMPONENT_TYPE:e_all_type, length = sizeof(dest))
stock GetCountTypeModel(modelid, E_COMPONENT_TYPE:component_type=E_COMPONENT_TYPE:e_all_type) 
stock E_COMPONENT_TYPE:GetComponentType(componentid) 
stock GetComponentName(componentid, name[], length = sizeof(name))
*/

#define MAX_VEHICLES_MODELS                 (212)

#define MAX_COMPONENT_NAME                  (33)

#define MAX_MODEL_COMPONENT_ID              (193)
#define MAX_MODEL_GENERAL_COMPONENTS        (22) 
#define MAX_MODEL_ADDITIONAL_COMPONENTS     (22) 
#define MAX_MODEL_COMPONENTS                (MAX_MODEL_GENERAL_COMPONENTS+MAX_MODEL_ADDITIONAL_COMPONENTS) // 44

#define INVALID_COMPONENT_ID                (0xFF)

enum E_COMPONENT_TYPE(<<=1) {
	e_nitro = 1, 
	e_wheels, 
	e_hydraulics,      
	e_stereo,         
	e_exhaust, 
	e_spoiler, 
	e_sideskirt, 
	e_roof, 
	e_lamps, 
	e_hood, 
	e_vents, 
	e_front_bumper, 
	e_rear_bumper, 
	e_front_bullbars, 
	e_rear_bullbars, 
	e_bullbars, 
	e_bullbar, 
    e_all_type = e_nitro | e_wheels | e_hydraulics | e_stereo | e_exhaust | e_spoiler | e_sideskirt | e_roof | e_lamps | e_hood | e_vents | e_front_bumper | e_rear_bumper | e_front_bullbars | e_rear_bullbars | e_bullbars | e_bullbar,
    e_none_type = INVALID_COMPONENT_ID
};

static stock const __componentsType[53] =
{
	0x5050505, 0x9090706, 0x9, 0x9080505, 0x5060404, 
	0x4040405, 0x8010606, 0x4040606, 0x7070407, 0x6040706, 
	0x6060604, 0x4040406, 0x6050506, 0x6070707, 0x6060504, 
	0x5070606, 0x4040407, 0x7060606, 0x6010101, 0x1010101, 
	0x1010101, 0x1010302, 0x7040607, 0x4060606, 0x1010106, 
	0x10060607, 0x4040606, 0x60e0eff, 0xff04040d, 0xd0b0606, 
	0x606060f, 0x60f0404, 0x7040707, 0x4060604, 0x4060505, 
	0xc0c0a0a, 0xa0a0505, 0xc0c0c0c, 0xb0b0c0b, 0xc0b050c, 
	0xb0c0505, 0x50b0b0c, 0xc0b0b0b, 0xb0b0b0b, 0xc0c0c0b, 
	0xc0b0b0c, 0xc0b0c0c, 0xb0b0b0b, 0xc0cffff  
};

static stock const gModelComponentsName[MAX_MODEL_COMPONENT_ID+1][MAX_COMPONENT_NAME] = {
    !"Pro Spoiler", 	                 !"Win Spoiler",
	!"Drag Spoiler", 	                 !"Alpha Spoiler",
	!"Champ Scoop Hood",                 !"Fury Scoop Hood",
	!"Roof Scoop",                       !"Right Sideskirt",
	!"5x Nitro",                         !"2x Nitro",
	!"10x Nitro",   	                 !"Race Scoop Hood",
	!"Worx Scoop Hood",	                 !"Round Fog Lamps",
	!"Champ Spoiler",                    !"Race Spoiler",
	!"Worx Spoiler",                     !"Left Sideskirt",
	!"Upswept Exhaust",	                 !"Twin Exhaust",
	!"Large Exhaust",	                 !"Medium Exhaust",
	!"Small Exhaust",	                 !"Fury Spoiler",
	!"Square Fog Lamps",	             !"Offroad Wheels",
	!"Right Alien Sideskirt",	         !"Left Alien Sideskirt",
	!"Alien Exhaust",       	         !"X-Flow Exhaust",
	!"Left X-Flow Sideskirt",	         !"Right X-Flow Sideskirt",
	!"Alien Roof Vent",	                 !"X-Flow Roof Vent",
	!"Alien Exhaust",	                 !"X-Flow Roof Vent",
	!"Right Alien Sideskirt",	         !"X-Flow Exhaust",
	!"Alien Roof Vent",     	         !"Right X-Flow Sideskirt",
	!"Left Alien Sideskirt",	         !"Right X-Flow Sideskirt",
	!"Right Chrome Sideskirt",	         !"Slamin Exhaust",
	!"Chrome Exhaust",      	         !"X-Flow Exhaust",
	!"Alien Exhaust",       	         !"Right Alien Sideskirt",
	!"Right X-Flow Sideskirt",	         !"Alien Spoiler",
	!"X-Flow Spoiler",      	         !"Left Alien Sideskirt",
	!"Left X-Flow Sideskirt",	         !"X-Flow Roof",
	!"Alien Roof",          	         !"Alien Roof",
	!"Right Alien Sideskirt",	         !"Right X-Flow Sideskirt",
	!"Alien Spoiler",       	         !"X-Flow Exhaust",
	!"X-Flow Spoiler",      	         !"X-Flow Roof",
	!"Left Alien Sideskirt",	         !"Left X-Flow Sideskirt",
	!"Alien Exhaust",       	         !"Alien Exhaust",
	!"X-Flow Exhaust",      	         !"Alien Roof",
	!"X-Flow Roof",         	         !"Right Alien Sideskirt",
	!"Right X-Flow Sideskirt",	         !"Left Alien Sideskirt",
	!"Left X-Flow Sideskirt",	         !"Shadow Wheels",
	!"Mega Wheels",         	         !"Rimshine Wheels",
	!"Wires Wheels",        	         !"Classic Wheels",
	!"Twist Wheels",        	         !"Cutter Wheels",
	!"Switch Wheels",       	         !"Grove Wheels",
	!"Import Wheels",       	         !"Dollar Wheels",
	!"Trance Wheels",       	         !"Atomic Wheels",
	!"Stereo Sound",        	         !"Hydraulics",
	!"Alien Roof",          	         !"X-Flow Exhaust",
	!"Right Alien Sideskirt",	         !"X-Flow Roof",
	!"Alien Exhaust",       	         !"Right X-Flow Sideskirt",
	!"Left Alien Sideskirt",             !"Right X-Flow Sideskirt",
	!"Ahab Wheels",         	         !"Virtual Wheels",
	!"Access Wheels",       	         !"Left Chrome Sideskirt",
	!"Chrome Grill Bullbar",	         !"Left \"Chrome Flames\" Sideskirt",
	!"Left \"Chrome Strip\" Sideskirt",	 !"Corvetible Roof",
	!"Chrome Exhaust",              	 !"Slamin Exhaust",
	!"Right \"Chrome Arches\" Sideskirt",!"Left \"Chrome Strip\" Sideskirt",
	!"Right \"Chrome Strip\" Sideskirt", !"Chrome Rear Bullbars",
	!"Slamin Rear Bullbars",             !"Little Front Sign?",
	!"Little Front Sign?",               !"Chrome Exhaust",
	!"Slamin Exhaust",                   !"Chrome Front Bullbars",
	!"Slamin Front Bullbars",            !"Chrome Front Bumper",
	!"Right \"Chrome Trim\" Sideskirt",  !"Right \"Wheelcovers\" Sideskirt",
	!"Left \"Chrome Trim\" Sideskirt",   !"Left \"Wheelcovers\" Sideskirt",
	!"Right \"Chrome Flames\" Sideskirt",!"Bullbar Chrome Bars",
	!"Left \"Chrome Arches\" Sideskirt", !"Bullbar Chrome Lights",
	!"Chrome Exhaust",                   !"Slamin Exhaust",
	!"Vinyl Hardtop",               	 !"Chrome Exhaust",
	!"Hardtop Roof",                	 !"Softtop Roof",
	!"Slamin Exhaust",              	 !"Right \"Chrome Strip\" Sideskirt",
	!"Right \"Chrome Strip\" Sideskirt", !"Slamin Exhaust",
	!"Chrome Exhaust",              	 !"Left \"Chrome Strip\" Sideskirt",
	!"Alien Spoiler",               	 !"X-Flow Spoiler",
	!"X-Flow Rear Bumper",          	 !"Alien Rear Bumper",
	!"Left Oval Vents",             	 !"Right Oval Vents",
	!"Left Square Vents",           	 !"Right Square Vents",
	!"X-Flow Spoiler",              	 !"Alien Spoiler",
	!"X-Flow Rear Bumper",          	 !"Alien Rear Bumper",
	!"Alien Rear Bumper",           	 !"X-Flow Rear Bumper",
	!"X-Flow Front Bumper",         	 !"Alien Front Bumper",
	!"Alien Rear Bumper",           	 !"Alien Front Bumper",
	!"X-Flow Rear Bumper",             	 !"X-Flow Front Bumper",
	!"X-Flow Spoiler",              	 !"Alien Rear Bumper",
	!"Alien Front Bumper",          	 !"X-Flow Rear Bumper",
	!"Alien Spoiler",               	 !"X-Flow Spoiler",
	!"Alien Spoiler",               	 !"X-Flow Front Bumper",
	!"Alien Front Bumper",          	 !"X-Flow Rear Bumper",
	!"Alien Rear Bumper",           	 !"Alien Front Bumper",
	!"X-Flow Front Bumper",         	 !"Alien Front Bumper",
	!"X-Flow Front Bumper",         	 !"X-Flow Front Bumper",
	!"Chrome Front Bumper",         	 !"Slamin Front Bumper",
	!"Chrome Rear Bumper",          	 !"Slamin Rear Bumper",
	!"Slamin Rear Bumper",               !"Chrome Front Bumper",
	!"Chrome Rear Bumper",          	 !"Slamin Front Bumper",
	!"Chrome Front Bumper",         	 !"Slamin Rear Bumper",
	!"Chrome Rear Bumper",          	 !"Slamin Front Bumper",
	!"Slamin Rear Bumper",          	 !"Chrome Rear Bumper",
	!"Slamin Front Bumper",         	 !"Chrome Front Bumper",
	!"Slamin Front Bumper",         	 !"Chrome Front Bumper",
	!"Chrome Rear Bumper",          	 !"Slamin Rear Bumper"
};

static stock const __validModelsTable[53+1] = {
    0x1020000, 0x3040000, 0x500, 0x6, 
    0x700, 0x8090a00, 0xb00, 0xff00,
    0x0, 0xc00000d, 0x0, 0xff00, 
    0xffff0000, 0xffffff00, 0x0, 0xffffff, 
    0x0, 0xff000000, 0xffff0000, 0xe0f00, 
    0xff0000, 0xff000000, 0x100011, 0x12ff0000, 
    0x13000000, 0x14000000, 0x0, 0xffff00, 
    0x0, 0x15161700, 0xffffff, 0x18, 
    0x190000, 0x1a1b, 0x1cffff00, 0x1d001e00, 
    0x1f20, 0x212223, 0x0, 0x2425, 
    0x26272800, 0x29002a, 0xffff00, 0x2b, 
    0x2c000000, 0x2dff0000, 0x2eff00, 0x2fff00, 
    0xff, 0x0, 0x30000031, 0x0, 0x0
};

static stock const gAdditionalModelComponents[275] = {  
    0x8090a19, 0x494a4b4c, 0x4d4e4f50, 0x51525354, 0x55606162, 0x57561213, 
    0x14150d18, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x13140103, 
    0x711060d, 0x4058e8f, 0x9091ffff, 0xffffffff, 0xffff1314, 0x15000210, 
    0x7110dff, 0xffffffff, 0xffffffff, 0xffffffff, 0x12131415, 0x10e17, 
    0xffffffff, 0xffffffff, 0xffffffff, 0xffff1314, 0x15010317, 0x7110d18, 
    0xffffffff, 0xffffffff, 0xffffffff, 0x12130103, 0x170711ff, 0xffffffff, 
    0xffffffff, 0xffffffff, 0xffff1415, 0x21006ff, 0xffffffff, 0xffffffff, 
    0xffffffff, 0xffffffff, 0x13150103, 0x405ffff, 0xffffffff, 0xffffffff, 
    0xffffffff, 0xffff1213, 0x1415000e, 0x1017ffff, 0xffffffff, 0xffffffff, 
    0xffffffff, 0x13141507, 0x110dffff, 0xffffffff, 0xffffffff, 0xffffffff, 
    0xffff1315, 0x1030604, 0x5ffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
    0x13141516, 0x1030711, 0x60dffff, 0xffffffff, 0xffffffff, 0xffff0103, 
    0x1707110d, 0x8e8f9091, 0xffffffff, 0xffffffff, 0xffffffff, 0x12131415, 
    0x71106ff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffff1415, 0x160d1804, 
    0x50cffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x12131400, 0x210060d, 
    0x180405ff, 0xffffffff, 0xffffffff, 0xffff1213, 0x1415030e, 0x1707118e, 
    0x8f9091ff, 0xffffffff, 0xffffffff, 0x100604, 0x5ffffff, 0xffffffff, 
    0xffffffff, 0xffffffff, 0xffff1314, 0x1020317, 0x711060b, 0x8e8fffff, 
    0xffffffff, 0xffffffff, 0x1314150d, 0x18ffffff, 0xffffffff, 0xffffffff, 
    0xffffffff, 0xffff1213, 0x14150002, 0xf100711, 0x4ffffff, 0xffffffff, 
    0xffffffff, 0x12131402, 0x3101707, 0x118e8f90, 0x91ffffff, 0xffffffff, 
    0xffff1214, 0x1031707, 0x11060d05, 0x8e8f9091, 0xffffffff, 0xffffffff, 
    0x12141501, 0xe0f0711, 0xffffffff, 0xffffffff, 0xffffffff, 0xffff1213, 
    0x14010317, 0x711060b, 0xcffffff, 0xffffffff, 0xffffffff, 0x7e7f656a, 
    0x7a7cb3b9, 0xb2b47b7d, 0x64ffffff, 0xffffffff, 0xffff7172, 0x76777879, 
    0x7573746d, 0x6effffff, 0xffffffff, 0xffffffff, 0x68696b6c, 0x6780b5b6, 
    0xb7b8ffff, 0xffffffff, 0xffffffff, 0xffff1213, 0x14011707, 0x11061804, 
    0x8e8f9091, 0xffffffff, 0xffffffff, 0x12131415, 0xe0f9091, 0xffffffff, 
    0xffffffff, 0xffffffff, 0xffff1213, 0x1021707, 0x11061804, 0x8e8f9091, 
    0xffffffff, 0xffffffff, 0x12131415, 0x3108e, 0x8fffffff, 0xffffffff, 
    0xffffffff, 0xffff1213, 0x14010317, 0x7110b0c, 0x8e8f9091, 0xffffffff, 
    0xffffffff, 0x12131401, 0x3170604, 0x58e8f90, 0x91ffffff, 0xffffffff, 
    0xffff1213, 0x14150203, 0x10170605, 0xffffffff, 0xffffffff, 0xffffffff, 
    0x595ca3a4, 0x5a5d5e5f, 0x585ba5a6, 0xa7a8ffff, 0xffffffff, 0xffff4142, 
    0x9ea24546, 0x47484344, 0xa0ad9fa1, 0xffffffff, 0xffffffff, 0x1c1d8a8b, 
    0x1a1b1e1f, 0x2021a9aa, 0x8c8dffff, 0xffffffff, 0xffff3b40, 0x3a3c1a1b, 
    0x1e1f3839, 0x3e3f373d, 0x9b9d9a9c, 0xffffffff, 0x22259293, 0x24272829, 
    0x2326abac, 0x9495ffff, 0xffffffff, 0xffff2d2e, 0x31322f30, 0x33343536, 
    0x98999697, 0xffffffff, 0xffffffff, 0x81846685, 0x8283bcbd, 0xbabbffff, 
    0xffffffff, 0xffffffff, 0xffff2b2c, 0x2a63aeaf, 0xb0b1ffff, 0xffffffff, 
    0xffffffff, 0xffffffff, 0x87888689, 0xbebfc0c1, 0xffffffff, 0xffffffff, 
    0xffffffff, 0xffff1214, 0x1170711, 0x6ffffff, 0xffffffff, 0xffffffff, 
    0xffffffff, 0x12131415, 0x16000102, 0x30e0f10, 0x17071106, 0xd188e8f, 
    0x90911214, 0x100711, 0x60d1804, 0x59091ff, 0xffffffff, 0xffffffff, 
    0x12141607, 0x11060d04, 0x5ffffff, 0xffffffff, 0xffffffff, 0xffff1213, 
    0x14011707, 0x1106188e, 0x8f9091ff, 0xffffffff, 0xffffffff
}; 

stock GetComponentName(componentid, name[], length = sizeof(name))
{
	if (!(0 <= componentid - 1000 <= MAX_MODEL_COMPONENT_ID)) {
		return 0;
	}
	return strunpack(name, gModelComponentsName[componentid - 1000], length);
}

stock E_COMPONENT_TYPE:GetComponentType(componentid) 
{
    if (!(0 <= componentid-1000 <= MAX_MODEL_COMPONENT_ID)) {
		return E_COMPONENT_TYPE:e_none_type;
	}
    return E_COMPONENT_TYPE:(1 << __componentsType{componentid-1000});
}

stock GetCountTypeModel(modelid, E_COMPONENT_TYPE:component_type=E_COMPONENT_TYPE:e_all_type) 
{
    if (!(0 <= modelid-400 <= MAX_VEHICLES_MODELS)) {
		return 0;
	}
    new count = 0;
    for (new i = 0; i < MAX_MODEL_COMPONENTS; i++)
	{
        new _componentid = GETARRAYELEMENT(modelid-400, i);
        if(_componentid == INVALID_COMPONENT_ID) {
            break;
        }
        if(GetComponentType(_componentid+1000) & component_type) {
            count++;
		}

	}
    return count;
}

stock GetModelValidUpgrades(modelid, dest[], E_COMPONENT_TYPE:component_type=E_COMPONENT_TYPE:e_all_type, length = sizeof(dest))
{
    if (!(0 <= modelid-400 <= MAX_VEHICLES_MODELS)) {
		return 0;
	}
	new count = 0;

	for (new i = 0; i < MAX_MODEL_COMPONENTS && i < length; i++)
	{
        new _componentid = GETARRAYELEMENT(modelid-400, i);
        if(_componentid == INVALID_COMPONENT_ID) {
            break;
        }
        if(GetComponentType(_componentid+1000) & component_type)
            dest[count++] = _componentid+1000;
	}
	return count;
}

stock IsModelUpgradeCompatible(modelid, componentid)
{
	if(!IsModelHaveUpgrades(modelid)) {
		return 0;
	}

	for (new i = 0; i < MAX_MODEL_COMPONENTS; i++)
	{  
        new _componentid = GETARRAYELEMENT(modelid-400, i);
        if(_componentid == INVALID_COMPONENT_ID) {
            break;
        }

		if (_componentid+1000 == componentid) {
			return 1;
		}
	}
	return 0;
}

stock IsModelHaveUpgrades(modelid)
{
	if (!(0 <= modelid-400 <= MAX_VEHICLES_MODELS)) {
		return 0;
	}
	return __validModelsTable{modelid-400} != INVALID_COMPONENT_ID;
}

stock GETARRAYELEMENT(model, idx) {
    return ((idx < MAX_MODEL_GENERAL_COMPONENTS)?gAdditionalModelComponents{idx} : 
				(idx >= MAX_MODEL_GENERAL_COMPONENTS && idx < MAX_MODEL_COMPONENTS) ? 
					gAdditionalModelComponents{(__validModelsTable{model}*MAX_MODEL_GENERAL_COMPONENTS)+(idx % MAX_MODEL_GENERAL_COMPONENTS)} : INVALID_COMPONENT_ID);
}