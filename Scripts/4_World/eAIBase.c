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

	    m_MinTimeTillNextFire = GetGame().GetTime() + weapon.FireRate();

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
	}