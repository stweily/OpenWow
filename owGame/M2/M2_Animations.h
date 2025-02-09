#pragma once


enum class EAnimationID : uint16
{
	Stand,
	Death,
	Spell,
	Stop,
	Walk,
	Run,
	Dead,
	Rise,
	StandWound,
	CombatWound,
	CombatCritical,
	ShuffleLeft,
	ShuffleRight,
	Walkbackwards,
	Stun,
	HandsClosed,
	AttackUnarmed,
	Attack1H,
	Attack2H,
	Attack2HL,
	ParryUnarmed,
	Parry1H,
	Parry2H,
	Parry2HL,
	ShieldBlock,
	ReadyUnarmed,
	Ready1H,
	Ready2H,
	Ready2HL,
	ReadyBow,
	Dodge,
	SpellPrecast,
	SpellCast,
	SpellCastArea,
	NPCWelcome,
	NPCGoodbye,
	Block,
	JumpStart,
	Jump,
	JumpEnd,
	Fall,
	SwimIdle,
	Swim,
	SwimLeft,
	SwimRight,
	SwimBackwards,
	AttackBow,
	FireBow,
	ReadyRifle,
	AttackRifle,
	Loot,
	ReadySpellDirected,
	ReadySpellOmni,
	SpellCastDirected,
	SpellCastOmni,
	BattleRoar,
	ReadyAbility,
	Special1H,
	Special2H,
	ShieldBash,
	EmoteTalk,
	EmoteEat,
	EmoteWork,
	EmoteUseStanding,
	EmoteTalkExclamation,
	EmoteTalkQuestion,
	EmoteBow,
	EmoteWave,
	EmoteCheer,
	EmoteDance,
	EmoteLaugh,
	EmoteSleep,
	EmoteSitGround,
	EmoteRude,
	EmoteRoar,
	EmoteKneel,
	EmoteKiss,
	EmoteCry,
	EmoteChicken,
	EmoteBeg,
	EmoteApplaud,
	EmoteShout,
	EmoteFlex,
	EmoteShy,
	EmotePoint,
	Attack1HPierce,
	Attack2HLoosePierce,
	AttackOff,
	AttackOffPierce,
	Sheath,
	HipSheath,
	Mount,
	RunRight,
	RunLeft,
	MountSpecial,
	Kick,
	SitGroundDown,
	SitGround,
	SitGroundUp,
	SleepDown,
	Sleep,
	SleepUp,
	SitChairLow,
	SitChairMed,
	SitChairHigh,
	LoadBow,
	LoadRifle,
	AttackThrown,
	ReadyThrown,
	HoldBow,
	HoldRifle,
	HoldThrown,
	LoadThrown,
	EmoteSalute,
	KneelStart,
	KneelLoop,
	KneelEnd,
	AttackUnarmedOff,
	SpecialUnarmed,
	StealthWalk,
	StealthStand,
	Knockdown,
	EatingLoop,
	UseStandingLoop,
	ChannelCastDirected,
	ChannelCastOmni,
	Whirlwind,
	Birth,
	UseStandingStart,
	UseStandingEnd,
	CreatureSpecial,
	Drown,
	Drowned,
	FishingCast,
	FishingLoop,
	Fly,
	EmoteWorkNoSheathe,
	EmoteStunNoSheathe,
	EmoteUseStandingNoSheathe,
	SpellSleepDown,
	SpellKneelStart,
	SpellKneelLoop,
	SpellKneelEnd,
	Sprint,
	InFlight,
	Spawn,
	Close,
	Closed,
	Open,
	Opened,
	Destroy,
	Destroyed,
	Rebuild,
	Custom0,
	Custom1,
	Custom2,
	Custom3,
	Despawn,
	Hold,
	Decay,
	BowPull,
	BowRelease,
	ShipStart,
	ShipMoving,
	ShipStop,
	GroupArrow,
	Arrow,
	CorpseArrow,
	GuideArrow,
	Sway,
	DruidCatPounce,
	DruidCatRip,
	DruidCatRake,
	DruidCatRavage,
	DruidCatClaw,
	DruidCatCower,
	DruidBearSwipe,
	DruidBearBite,
	DruidBearMaul,
	DruidBearBash,
	DragonTail,
	DragonStomp,
	DragonSpit,
	DragonSpitHover,
	DragonSpitFly,
	EmoteYes,
	EmoteNo,
	JumpLandRun,
	LootHold,
	LootUp,
	StandHigh,
	Impact,
	LiftOff,
	Hover,
	SuccubusEntice,
	EmoteTrain,
	EmoteDead,
	EmoteDanceOnce,
	Deflect,
	EmoteEatNoSheathe,
	Land,
	Submerge,
	Submerged,
	Cannibalize,
	ArrowBirth,
	GroupArrowBirth,
	CorpseArrowBirth,
	GuideArrowBirth,
	EmoteTalkNoSheathe,
	EmotePointNoSheathe,
	EmoteSaluteNoSheathe,
	EmoteDanceSpecial,
	Mutilate,
	CustomSpell01,
	CustomSpell02,
	CustomSpell03,
	CustomSpell04,
	CustomSpell05,
	CustomSpell06,
	CustomSpell07,
	CustomSpell08,
	CustomSpell09,
	CustomSpell10,
	StealthRun,
	Emerge,
	Cower,
	Grab,
	GrabClosed,
	GrabThrown,
	FlyStand,
	FlyDeath,
	FlySpell,
	FlyStop,
	FlyWalk,
	FlyRun,
	FlyDead,
	FlyRise,
	FlyStandWound,
	FlyCombatWound,
	FlyCombatCritical,
	FlyShuffleLeft,
	FlyShuffleRight,
	FlyWalkbackwards,
	FlyStun,
	FlyHandsClosed,
	FlyAttackUnarmed,
	FlyAttack1H,
	FlyAttack2H,
	FlyAttack2HL,
	FlyParryUnarmed,
	FlyParry1H,
	FlyParry2H,
	FlyParry2HL,
	FlyShieldBlock,
	FlyReadyUnarmed,
	FlyReady1H,
	FlyReady2H,
	FlyReady2HL,
	FlyReadyBow,
	FlyDodge,
	FlySpellPrecast,
	FlySpellCast,
	FlySpellCastArea,
	FlyNPCWelcome,
	FlyNPCGoodbye,
	FlyBlock,
	FlyJumpStart,
	FlyJump,
	FlyJumpEnd,
	FlyFall,
	FlySwimIdle,
	FlySwim,
	FlySwimLeft,
	FlySwimRight,
	FlySwimBackwards,
	FlyAttackBow,
	FlyFireBow,
	FlyReadyRifle,
	FlyAttackRifle,
	FlyLoot,
	FlyReadySpellDirected,
	FlyReadySpellOmni,
	FlySpellCastDirected,
	FlySpellCastOmni,
	FlyBattleRoar,
	FlyReadyAbility,
	FlySpecial1H,
	FlySpecial2H,
	FlyShieldBash,
	FlyEmoteTalk,
	FlyEmoteEat,
	FlyEmoteWork,
	FlyEmoteUseStanding,
	FlyEmoteTalkExclamation,
	FlyEmoteTalkQuestion,
	FlyEmoteBow,
	FlyEmoteWave,
	FlyEmoteCheer,
	FlyEmoteDance,
	FlyEmoteLaugh,
	FlyEmoteSleep,
	FlyEmoteSitGround,
	FlyEmoteRude,
	FlyEmoteRoar,
	FlyEmoteKneel,
	FlyEmoteKiss,
	FlyEmoteCry,
	FlyEmoteChicken,
	FlyEmoteBeg,
	FlyEmoteApplaud,
	FlyEmoteShout,
	FlyEmoteFlex,
	FlyEmoteShy,
	FlyEmotePoint,
	FlyAttack1HPierce,
	FlyAttack2HLoosePierce,
	FlyAttackOff,
	FlyAttackOffPierce,
	FlySheath,
	FlyHipSheath,
	FlyMount,
	FlyRunRight,
	FlyRunLeft,
	FlyMountSpecial,
	FlyKick,
	FlySitGroundDown,
	FlySitGround,
	FlySitGroundUp,
	FlySleepDown,
	FlySleep,
	FlySleepUp,
	FlySitChairLow,
	FlySitChairMed,
	FlySitChairHigh,
	FlyLoadBow,
	FlyLoadRifle,
	FlyAttackThrown,
	FlyReadyThrown,
	FlyHoldBow,
	FlyHoldRifle,
	FlyHoldThrown,
	FlyLoadThrown,
	FlyEmoteSalute,
	FlyKneelStart,
	FlyKneelLoop,
	FlyKneelEnd,
	FlyAttackUnarmedOff,
	FlySpecialUnarmed,
	FlyStealthWalk,
	FlyStealthStand,
	FlyKnockdown,
	FlyEatingLoop,
	FlyUseStandingLoop,
	FlyChannelCastDirected,
	FlyChannelCastOmni,
	FlyWhirlwind,
	FlyBirth,
	FlyUseStandingStart,
	FlyUseStandingEnd,
	FlyCreatureSpecial,
	FlyDrown,
	FlyDrowned,
	FlyFishingCast,
	FlyFishingLoop,
	FlyFly,
	FlyEmoteWorkNoSheathe,
	FlyEmoteStunNoSheathe,
	FlyEmoteUseStandingNoSheathe,
	FlySpellSleepDown,
	FlySpellKneelStart,
	FlySpellKneelLoop,
	FlySpellKneelEnd,
	FlySprint,
	FlyInFlight,
	FlySpawn,
	FlyClose,
	FlyClosed,
	FlyOpen,
	FlyOpened,
	FlyDestroy,
	FlyDestroyed,
	FlyRebuild,
	FlyCustom0,
	FlyCustom1,
	FlyCustom2,
	FlyCustom3,
	FlyDespawn,
	FlyHold,
	FlyDecay,
	FlyBowPull,
	FlyBowRelease,
	FlyShipStart,
	FlyShipMoving,
	FlyShipStop,
	FlyGroupArrow,
	FlyArrow,
	FlyCorpseArrow,
	FlyGuideArrow,
	FlySway,
	FlyDruidCatPounce,
	FlyDruidCatRip,
	FlyDruidCatRake,
	FlyDruidCatRavage,
	FlyDruidCatClaw,
	FlyDruidCatCower,
	FlyDruidBearSwipe,
	FlyDruidBearBite,
	FlyDruidBearMaul,
	FlyDruidBearBash,
	FlyDragonTail,
	FlyDragonStomp,
	FlyDragonSpit,
	FlyDragonSpitHover,
	FlyDragonSpitFly,
	FlyEmoteYes,
	FlyEmoteNo,
	FlyJumpLandRun,
	FlyLootHold,
	FlyLootUp,
	FlyStandHigh,
	FlyImpact,
	FlyLiftOff,
	FlyHover,
	FlySuccubusEntice,
	FlyEmoteTrain,
	FlyEmoteDead,
	FlyEmoteDanceOnce,
	FlyDeflect,
	FlyEmoteEatNoSheathe,
	FlyLand,
	FlySubmerge,
	FlySubmerged,
	FlyCannibalize,
	FlyArrowBirth,
	FlyGroupArrowBirth,
	FlyCorpseArrowBirth,
	FlyGuideArrowBirth,
	FlyEmoteTalkNoSheathe,
	FlyEmotePointNoSheathe,
	FlyEmoteSaluteNoSheathe,
	FlyEmoteDanceSpecial,
	FlyMutilate,
	FlyCustomSpell01,
	FlyCustomSpell02,
	FlyCustomSpell03,
	FlyCustomSpell04,
	FlyCustomSpell05,
	FlyCustomSpell06,
	FlyCustomSpell07,
	FlyCustomSpell08,
	FlyCustomSpell09,
	FlyCustomSpell10,
	FlyStealthRun,
	FlyEmerge,
	FlyCower,
	FlyGrab,
	FlyGrabClosed,
	FlyGrabThrown,
	ToFly,
	ToHover,
	ToGround,
	FlyToFly,
	FlyToHover,
	FlyToGround,
	Settle,
	FlySettle,
	DeathStart,
	DeathLoop,
	DeathEnd,
	FlyDeathStart,
	FlyDeathLoop,
	FlyDeathEnd,
	DeathEndHold,
	FlyDeathEndHold,
	Strangulate,
	FlyStrangulate,
	ReadyJoust,
	LoadJoust,
	HoldJoust,
	FlyReadyJoust,
	FlyLoadJoust,
	FlyHoldJoust,
	AttackJoust,
	FlyAttackJoust,
	ReclinedMount,
	FlyReclinedMount,
	ToAltered,
	FromAltered,
	FlyToAltered,
	FlyFromAltered,
	InStocks,
	FlyInStocks,
	VehicleGrab,
	VehicleThrow,
	FlyVehicleGrab,
	FlyVehicleThrow,
	ToAlteredPostSwap,
	FromAlteredPostSwap,
	FlyToAlteredPostSwap,
	FlyFromAlteredPostSwap,
	ReclinedMountPassenger,
	FlyReclinedMountPassenger,
	Carry2H,
	Carried2H,
	FlyCarry2H,
	FlyCarried2H,

};

