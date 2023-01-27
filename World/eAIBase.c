	modded class eAIBase {
	  //generic json template used for PoC
	  //yes this is garbage per bot
	  //ideally, each gun would have an rps value to read from.
	  private const static string WeaponProfilesFolder = "$profile:ExpansionMod\\AI\\Utils\\";
	  private const static string Weapon_Settings = WeaponProfilesFolder + "WeaponSettings.json";
	  ref CheckWeaponGroups m_CheckWeaponGroups;

	  override void TryFireWeapon() {
	    #ifdef EAI_TRACE
	    auto trace = CF_Trace_0(this, "TryFireWeapon");
	    #endif

	    if (GetGame().GetTime() < m_MinTimeTillNextFire)
	      return;

	    Weapon_Base weapon = Weapon_Base.Cast(GetHumanInventory().GetEntityInHands());
	    if (!weapon)
	      return;

	    DynamicFireModifier(weapon);

	    if (GetDayZPlayerInventory().IsProcessing())
	      return;
	    if (!IsRaised())
	      return;
	    if (!weapon.CanFire())
	      return;
	    if (GetWeaponManager().IsRunning())
	      return;

	    int muzzleIndex = weapon.GetCurrentMuzzle();
	    if (!weapon.CanFire(muzzleIndex))
	      return;

	    if (!eAI_HasLOS())
	      return;

	    GetWeaponManager().Fire(weapon);
	  }

	  void DynamicFireModifier(Weapon_Base weapon) {
	    if (!m_CheckWeaponGroups) loadCheckWeaponGroups();
	    string current = weapon.GetType();
	    if (current) {
	      foreach(CheckWeaponType group: m_CheckWeaponGroups.Group)
	      if (group.WeaponClassName == current) {
	        m_MinTimeTillNextFire = group.WeaponFireRate;
			//m_MinTimeTillNextFire = weapon.FireRate;
	        return;
	      }
	    }
		//current default if none found in config
	    m_MinTimeTillNextFire = GetGame().GetTime() + 250.0;
	  }
	

	void WeaponLoggerPrint(string msg) {
	  if (GetExpansionSettings().GetLog().AIGeneral)
	    GetExpansionSettings().GetLog().PrintLog("[WeaponDebug] " + msg);
	}

	void loadCheckWeaponGroups() {
	  if (!FileExist(Weapon_Settings)) {
	    if (!FileExist(WeaponProfilesFolder))
	      MakeDirectory(WeaponProfilesFolder);
	    DefaultWeaponSettings(m_CheckWeaponGroups);
	    JsonFileLoader < CheckWeaponGroups > .JsonSaveFile(Weapon_Settings, m_CheckWeaponGroups);
	  } else {
	    m_CheckWeaponGroups = new CheckWeaponGroups();
	    JsonFileLoader < CheckWeaponGroups > .JsonLoadFile(Weapon_Settings, m_CheckWeaponGroups);
	  }

	  if (m_CheckWeaponGroups.Version != 1) {}

	  foreach(CheckWeaponType group: m_CheckWeaponGroups.Group) {
	    if (group.WeaponClassName) {
	      if (group.WeaponFireRate) {
	        WeaponLoggerPrint("Linking :" + group.WeaponClassName + " TO: " + group.WeaponFireRate);
	      } else {
	        WeaponLoggerPrint("Invalid Data -" + group.WeaponFireRate);
	        continue;
	      }
	    } else {
	      WeaponLoggerPrint("Invalid Data -" + group.WeaponClassName);
	      continue;
	    }
	  }
	}
	  void DefaultWeaponSettings(out CheckWeaponGroups Data) {
	    Data = new CheckWeaponGroups();
		//im completely aware there's better data structures to use... and amount will cause long searches.
	    Data.Group.Insert(new CheckWeaponType("Expansion_Crossbow", 700));
	    Data.Group.Insert(new CheckWeaponType("ExpansionRPG7", 1400));
	    Data.Group.Insert(new CheckWeaponType("ExpansionLAW", 1400));
	    Data.Group.Insert(new CheckWeaponType("Expansion_M79", 400));
	    Data.Group.Insert(new CheckWeaponType("Expansion_M9", 300));
	    Data.Group.Insert(new CheckWeaponType("Expansion_G36", 50));
	    Data.Group.Insert(new CheckWeaponType("Expansion_MPX", 50));
	    Data.Group.Insert(new CheckWeaponType("Expansion_VityazSN", 80));
	    Data.Group.Insert(new CheckWeaponType("Expansion_MP5", 50));
	    Data.Group.Insert(new CheckWeaponType("Expansion_MP5SD", 50));
	    Data.Group.Insert(new CheckWeaponType("Expansion_MP7", 50));
	    Data.Group.Insert(new CheckWeaponType("Expansion_Kedr", 75));
	    Data.Group.Insert(new CheckWeaponType("Expansion_M14", 400));
	    Data.Group.Insert(new CheckWeaponType("Expansion_M16", 150));
	    Data.Group.Insert(new CheckWeaponType("Expansion_M1A", 400));
	    Data.Group.Insert(new CheckWeaponType("Expansion_Kar98", 700));
	    Data.Group.Insert(new CheckWeaponType("Expansion_BenelliM4", 150));
	    Data.Group.Insert(new CheckWeaponType("Expansion_AWM", 1400));
	    Data.Group.Insert(new CheckWeaponType("AK101", 50));
	    Data.Group.Insert(new CheckWeaponType("AK101_Black", 50));
	    Data.Group.Insert(new CheckWeaponType("AK101_Green", 75));
	    Data.Group.Insert(new CheckWeaponType("AK74", 400));
	    Data.Group.Insert(new CheckWeaponType("AK74_Black", 150));
	    Data.Group.Insert(new CheckWeaponType("AK74_Green", 400));
	    Data.Group.Insert(new CheckWeaponType("AKM", 50));
	    Data.Group.Insert(new CheckWeaponType("AKS74U", 50));
	    Data.Group.Insert(new CheckWeaponType("AKS74U_Black", 75));
	    Data.Group.Insert(new CheckWeaponType("AKS74U_Green", 400));
	    Data.Group.Insert(new CheckWeaponType("B95", 150));
	    Data.Group.Insert(new CheckWeaponType("B95_Black", 400));
	    Data.Group.Insert(new CheckWeaponType("B95_Green", 50));
	    Data.Group.Insert(new CheckWeaponType("CZ527", 50));
	    Data.Group.Insert(new CheckWeaponType("CZ527_Black", 75));
	    Data.Group.Insert(new CheckWeaponType("CZ527_Camo", 400));
	    Data.Group.Insert(new CheckWeaponType("CZ527_Green", 150));
	    Data.Group.Insert(new CheckWeaponType("CZ61", 400));
	    Data.Group.Insert(new CheckWeaponType("CZ75", 50));
	    Data.Group.Insert(new CheckWeaponType("SKS", 50));
	    Data.Group.Insert(new CheckWeaponType("FNX45", 75));
	    Data.Group.Insert(new CheckWeaponType("FNX45_arrow", 400));
	    Data.Group.Insert(new CheckWeaponType("Glock19", 150));
	    Data.Group.Insert(new CheckWeaponType("SKS_Black", 400));
	    Data.Group.Insert(new CheckWeaponType("SVD", 50));
	    Data.Group.Insert(new CheckWeaponType("LongHorn", 75));
	    Data.Group.Insert(new CheckWeaponType("M4A1", 400));
	    Data.Group.Insert(new CheckWeaponType("M4A1_Black", 150));
	    Data.Group.Insert(new CheckWeaponType("M4A1_Green", 400));
	    Data.Group.Insert(new CheckWeaponType("Saiga", 50));
	    Data.Group.Insert(new CheckWeaponType("MP5K", 50));
	    Data.Group.Insert(new CheckWeaponType("MakarovIJ70", 75));
	    Data.Group.Insert(new CheckWeaponType("Mosin9130", 400));
	    Data.Group.Insert(new CheckWeaponType("Mosin9130_Black", 150));
	    Data.Group.Insert(new CheckWeaponType("Mosin9130_Camo", 400));
	    Data.Group.Insert(new CheckWeaponType("Mosin9130_Green", 50));
	  }
	}
	class CheckWeaponType {
	  string WeaponClassName;
	  float WeaponFireRate;

	  void CheckWeaponType(string fac, float col) {
	    WeaponClassName = fac;
	    WeaponFireRate = col;
	  }
	}

	class CheckWeaponGroups {
	  int Version = 1;
	  int Enabled = 1;
	  ref array < ref CheckWeaponType > Group;
	  void CheckWeaponGroups() {
	    Group = new array < ref CheckWeaponType > ;
	  }

	};