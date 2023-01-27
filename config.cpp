#define _ARMA_

class CfgPatches
{
	class AI_Weapon_FireRates_scripts
	{
		requiredAddons[] = {"DZ_Data","DZ_Scripts","DayZExpansion_AI_Scripts"};
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
		dependencies[] = {"World","Mission"};
		class defs
		{
			class worldScriptModule
			{
				value = "";
				files[] = {"DayZExpansion/AI/Scripts/Common","DayZExpansion/AI/Scripts/4_World","dolphin/AI-Weapon-FireRates/World"};
			};
		};
	};
};