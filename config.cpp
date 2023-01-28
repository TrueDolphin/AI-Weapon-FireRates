#define _ARMA_

class CfgPatches
{
	class AI_Weapon_FireRates_scripts
	{
		requiredAddons[] = {"DayZExpansion_AI_Scripts"};
	};
};
class CfgMods
{
	class AI_Weapon_FireRates
	{
		action = "";
		hideName = 0;
		hidePicture = 0;
		name = "AI Additional Scripts";
		credits = "DayZ Expansion and dolphin";
		author = "Dolphin";
		authorID = "";
		version = "0.1";
		extra = 0;
		type = "servermod";
		dependencies[] = {"World"};
		class defs
		{
			class worldScriptModule
			{
				value = "";
				files[] = {"dolphin/AI-Weapon-FireRates/Scripts/4_World"};
			};
		};
	};
};