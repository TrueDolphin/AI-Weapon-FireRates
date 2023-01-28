	modded class eAIBase {

	  override void TryFireWeapon() {
	    #ifdef EAI_TRACE
	    auto trace = CF_Trace_0(this, "TryFireWeapon");
	    #endif

	    if (GetGame().GetTime() < m_MinTimeTillNextFire)
	      return;

	    Weapon_Base weapon = Weapon_Base.Cast(GetHumanInventory().GetEntityInHands());
	    if (!weapon) return;
		if (!weapon.FireRate()) weapon.InitFireRate();
	    int muzzleIndex = weapon.GetCurrentMuzzle();
	    m_MinTimeTillNextFire = GetGame().GetTime() + weapon.FireRate();

	    if (GetDayZPlayerInventory().IsProcessing() || !IsRaised() || !weapon.CanFire() || GetWeaponManager().IsRunning() || !eAI_HasLOS() || !weapon.CanFire(muzzleIndex))
	      return;

	    GetWeaponManager().Fire(weapon);
	  }
	}