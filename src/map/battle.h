/****************************************************************************!
*                _           _   _   _                                       *    
*               | |__  _ __ / \ | |_| |__   ___ _ __   __ _                  *  
*               | '_ \| '__/ _ \| __| '_ \ / _ \ '_ \ / _` |                 *   
*               | |_) | | / ___ \ |_| | | |  __/ | | | (_| |                 *    
*               |_.__/|_|/_/   \_\__|_| |_|\___|_| |_|\__,_|                 *    
*                                                                            *
*                                                                            *
* \file src/map/battle.h                                                     *
* Descri��o Prim�ria.                                                        *
* Descri��o mais elaborada sobre o arquivo.                                  *
* \author brAthena, Athena, eAthena                                          *
* \date ?                                                                    *
* \todo ?                                                                    *  
*****************************************************************************/

#ifndef _BATTLE_H_
#define _BATTLE_H_

#include "../common/cbasetypes.h"
#include "map.h" //ELE_MAX

/**
 * Declarations
 **/
struct map_session_data;
struct mob_data;
struct block_list;
struct weapon_atk;
struct status_change;
struct status_data;

/**
 * Defines
 **/
#define MIN_HAIR_STYLE  (battle_config.min_hair_style)
#define MAX_HAIR_STYLE  (battle_config.max_hair_style)
#define MIN_HAIR_COLOR  (battle_config.min_hair_color)
#define MAX_HAIR_COLOR  (battle_config.max_hair_color)
#define MIN_CLOTH_COLOR (battle_config.min_cloth_color)
#define MAX_CLOTH_COLOR (battle_config.max_cloth_color)

#define	is_boss(bl)	(status_get_mode(bl)&MD_BOSS)	// Can refine later [Aru]

/**
 * Enumerations
 **/

enum {  // Flag of the final calculation
    BF_WEAPON   = 0x0001,
    BF_MAGIC    = 0x0002,
    BF_MISC     = 0x0004,
    BF_SHORT    = 0x0010,
    BF_LONG     = 0x0040,
    BF_SKILL    = 0x0100,
    BF_NORMAL   = 0x0200,
    BF_WEAPONMASK=0x000f,
    BF_RANGEMASK= 0x00f0,
    BF_SKILLMASK= 0x0f00,
};

// state of a single attack attempt; used in flee/def penalty calculations when mobbed
typedef enum damage_lv {
    ATK_NONE,    // not an attack
    ATK_LUCKY,   // attack was lucky-dodged
    ATK_FLEE,    // attack was dodged
    ATK_MISS,    // attack missed because of element/race modifier.
    ATK_BLOCK,   // attack was blocked by some skills.
    ATK_DEF      // attack connected
} damage_lv;

enum e_battle_check_target { //New definitions [Skotlex]
    BCT_NOONE       =   0x000000,
    BCT_SELF        =   0x010000,
    BCT_ENEMY       =   0x020000,
    BCT_PARTY       =   0x040000,
    BCT_GUILDALLY   =   0x080000,	// Only allies, NOT guildmates
    BCT_NEUTRAL     =   0x100000,
    BCT_SAMEGUILD   =   0x200000,   // No Guild Allies

    BCT_GUILD       =   0x280000,	// Guild AND allies (BCT_SAMEGUILD|BCT_GUILDALLY)

    BCT_NOGUILD     =   0x170000,	// This should be (~BCT_GUILD&BCT_ALL)
    BCT_NOPARTY     =   0x3b0000,	// This should be (~BCT_PARTY&BCT_ALL)
    BCT_NOENEMY     =   0x3d0000,	// This should be (~BCT_ENEMY&BCT_ALL)

    BCT_ALL         =   0x3f0000,	// Sum of BCT_NOONE to BCT_SAMEGUILD
};

/**
 * Structures
 **/

// dammage structure
struct Damage {
	int64 damage,damage2; //right, left dmg
	int type,div_; //chk clif_damage for type @TODO add an enum ? ;  nb of hit
	int amotion,dmotion;
	int blewcount; //nb of knockback
	int flag; //chk BF_* flag, (enum below)
	enum damage_lv dmg_lv;  //ATK_LUCKY,ATK_FLEE,ATK_DEF
};

extern struct Battle_Config {
	int warp_point_debug;
	int enable_critical;
	int mob_critical_rate;
	int critical_rate;
	int enable_baseatk;
	int enable_perfect_flee;
	int cast_rate, delay_rate;
	int delay_dependon_dex, delay_dependon_agi;
	int sdelay_attack_enable;
	int left_cardfix_to_right;
	int skill_add_range;
	int skill_out_range_consume;
	int skill_amotion_leniency;
	int skillrange_by_distance; //[Skotlex]
	int use_weapon_skill_range; //[Skotlex]
	int pc_damage_delay_rate;
	int defnotenemy;
	int vs_traps_bctall;
	int vs_traps_bctall_ot;
	int traps_setting;
	int summon_flora; //[Skotlex]
	int clear_unit_ondeath; //[Skotlex]
	int clear_unit_onwarp; //[Skotlex]
	int random_monster_checklv;
	int attr_recover;
	int item_auto_get;
	int flooritem_lifetime;
	int item_first_get_time;
	int item_second_get_time;
	int item_third_get_time;
	int mvp_item_first_get_time;
	int mvp_item_second_get_time;
	int mvp_item_third_get_time;
	int base_exp_rate,job_exp_rate;
	int drop_rate0item;
	int death_penalty_type;
	int death_penalty_base,death_penalty_job;
	int pvp_exp;  // [MouseJstr]
	int gtb_sc_immunity;
	int zeny_penalty;
	int restart_hp_rate;
	int restart_sp_rate;
	int mvp_exp_rate;
	int mvp_hp_rate;
	int monster_hp_rate;
	int monster_max_aspd;
	int view_range_rate;
	int chase_range_rate;
	int atc_spawn_quantity_limit;
	int atc_slave_clone_limit;
	int partial_name_scan;
	int skillfree;
	int skillup_limit;
	int wp_rate;
	int pp_rate;
	int monster_active_enable;
	int monster_damage_delay_rate;
	int monster_loot_type;
	int mob_skill_rate; //[Skotlex]
	int mob_skill_delay;    //[Skotlex]
	int mob_count_rate;
	int no_spawn_on_player; //[Skotlex]
	int force_random_spawn; //[Skotlex]
	int mob_spawn_delay, plant_spawn_delay, boss_spawn_delay;   // [Skotlex]
	int slaves_inherit_mode;
	int slaves_inherit_speed;
	int summons_trigger_autospells;
	int pc_walk_delay_rate; //Adjusts can't walk delay after being hit for players. [Skotlex]
	int walk_delay_rate; //Adjusts can't walk delay after being hit. [Skotlex]
	int multihit_delay;  //Adjusts can't walk delay per hit on multi-hitting skills. [Skotlex]
	int quest_skill_learn;
	int quest_skill_reset;
	int basic_skill_check;
	int guild_emperium_check;
	int guild_exp_limit;
	int guild_max_castles;
	int guild_skill_relog_delay;
	int emergency_call;
	int guild_aura;
	int pc_invincible_time;

	int pet_catch_rate;
	int pet_rename;
	int pet_friendly_rate;
	int pet_hungry_delay_rate;
	int pet_hungry_friendly_decrease;
	int pet_status_support;
	int pet_attack_support;
	int pet_damage_support;
	int pet_support_min_friendly;   //[Skotlex]
	int pet_equip_min_friendly;
	int pet_support_rate;
	int pet_attack_exp_to_master;
	int pet_attack_exp_rate;
	int pet_lv_rate; //[Skotlex]
	int pet_max_stats; //[Skotlex]
	int pet_max_atk1; //[Skotlex]
	int pet_max_atk2; //[Skotlex]
	int pet_equip_required;

	int skill_min_damage;
	int finger_offensive_type;
	int heal_exp;
	int max_heal_lv;
	int max_heal; //Mitternacht
	int resurrection_exp;
	int shop_exp;
	int combo_delay_rate;
	int item_check;
	int item_use_interval;  //[Skotlex]
	int cashfood_use_interval;
	int wedding_modifydisplay;
	int wedding_ignorepalette;  //[Skotlex]
	int xmas_ignorepalette; // [Valaris]
	int summer_ignorepalette; // [Zephyrus]
	int natural_healhp_interval;
	int natural_healsp_interval;
	int natural_heal_skill_interval;
	int natural_heal_weight_rate;
	int arrow_decrement;
	int arrow_decrement_ot;
	int max_aspd;
	int max_walk_speed; //Maximum walking speed after buffs [Skotlex]
	int max_hp;
	int max_sp;
	int max_lv, aura_lv;
	int max_parameter, max_baby_parameter;
	int max_cart_weight;
	int skill_log;
	int battle_log;
	int etc_log;
	int save_clothcolor;
	int undead_detect_type;
	int auto_counter_type;
	int min_hitrate;    //[Skotlex]
	int max_hitrate;    //[Skotlex]
	int agi_penalty_target;
	int agi_penalty_type;
	int agi_penalty_count;
	int agi_penalty_num;
	int vit_penalty_target;
	int vit_penalty_type;
	int vit_penalty_count;
	int vit_penalty_num;
	int weapon_defense_type;
	int magic_defense_type;
	int skill_reiteration;
	int skill_nofootset;
	int pc_cloak_check_type;
	int monster_cloak_check_type;
	int estimation_type;
	int gvg_flee_penalty;
	int mob_changetarget_byskill;
	int attack_direction_change;
	int land_skill_limit;
	int monster_class_change_recover;
	int produce_item_name_input;
	int display_skill_fail;
	int chat_warpportal;
	int mob_warp;
	int dead_branch_active;
	int vending_max_value;
	int vending_max_value_ot;
	int vending_over_max;
	int vending_tax;
	int show_steal_in_same_party;
	int party_share_type;
	int party_hp_mode;
	int party_show_share_picker;
	int show_picker_item_type;
	int attack_attr_none;
	int item_rate_mvp, item_rate_common, item_rate_common_boss, item_rate_card, item_rate_card_boss,
	    item_rate_equip, item_rate_equip_boss, item_rate_heal, item_rate_heal_boss, item_rate_use,
	    item_rate_use_boss, item_rate_treasure, item_rate_adddrop;

	int logarithmic_drops;
	int item_drop_common_min,item_drop_common_max;  // Added by TyrNemesis^
	int item_drop_card_min,item_drop_card_max;
	int item_drop_equip_min,item_drop_equip_max;
	int item_drop_mvp_min,item_drop_mvp_max;    // End Addition
	int item_drop_heal_min,item_drop_heal_max;  // Added by Valatris
	int item_drop_use_min,item_drop_use_max;    //End
	int item_drop_treasure_min,item_drop_treasure_max; //by [Skotlex]
	int item_drop_adddrop_min,item_drop_adddrop_max; //[Skotlex]

	int prevent_logout; // Added by RoVeRT

	int alchemist_summon_reward;    // [Valaris]
	int drops_by_luk;
	int drops_by_luk2;
	int equip_natural_break_rate;   //Base Natural break rate for attacks.
	int equip_self_break_rate; //Natural & Penalty skills break rate
	int equip_skill_break_rate; //Offensive skills break rate
	int multi_level_up;
	int max_exp_gain_rate; //Max amount of exp bar % you can get in one go.
	int pk_mode;
	int pk_level_range;

	int manner_system; // end additions [Valaris]
	int show_mob_info;

	int gx_allhit;
	int gx_allhit_ot;
	int gx_disptype;
	int devotion_level_difference;
	int player_skill_partner_check;
	int invite_request_check;
	int skill_removetrap_type;
	int disp_experience;
	int disp_zeny;
	int castle_defense_rate;
	int backstab_bow_penalty;
	int backstab_bow_penalty_ot;
	int hp_rate;
	int sp_rate;
	int bone_drop;
	int buyer_name;
	int dancing_weaponswitch_fix;
	int dancing_weaponswitch_fix_ot;

// eAthena additions
	int night_at_start; // added by [Yor]
	int day_duration; // added by [Yor]
	int night_duration; // added by [Yor]
	int ban_hack_trade; // added by [Yor]

	int min_hair_style; // added by [MouseJstr]
	int max_hair_style; // added by [MouseJstr]
	int min_hair_color; // added by [MouseJstr]
	int max_hair_color; // added by [MouseJstr]
	int min_cloth_color; // added by [MouseJstr]
	int max_cloth_color; // added by [MouseJstr]
	int pet_hair_style; // added by [Skotlex]

	int castrate_dex_scale; // added by [MouseJstr]
	int area_size; // added by [MouseJstr]

	int max_def, over_def_bonus; //added by [Skotlex]
	int max_mdef;

	int zeny_from_mobs; // [Valaris]
	int mobs_level_up; // [Valaris]
	int mobs_level_up_exp_rate; // [Valaris]
	int pk_min_level; // [celest]
	int skill_steal_max_tries; //max steal skill tries on a mob. if 0, then w/o limit [Lupus]
	int motd_type; // [celest]
	int finding_ore_rate; // orn
	int exp_calc_type;
	int exp_bonus_attacker;
	int exp_bonus_max_attacker;
	int min_skill_delay_limit;
	int default_walk_delay;
	int no_skill_delay;
	int attack_walk_delay;
	int require_glory_guild;
	int idle_no_share;
	int party_update_interval;
	int party_even_share_bonus;
	int delay_battle_damage;
	int hide_woe_damage;
	int display_version;

	int display_hallucination;  // [Skotlex]
	int use_statpoint_table;    // [Skotlex]

	int ignore_items_gender; //[Lupus]

	int copyskill_restrict; // [Aru]
	int berserk_cancels_buffs; // [Aru]
	int mob_ai; //Configures various mob_ai settings to make them smarter or dumber(official). [Skotlex]
	int hom_setting; //Configures various homunc settings which make them behave unlike normal characters.. [Skotlex]
	int dynamic_mobs; // Dynamic Mobs [Wizputer] - battle_athena flag implemented by [random]
	int mob_remove_damaged; // Dynamic Mobs - Remove mobs even if damaged [Wizputer]
	int mob_remove_delay; // Dynamic Mobs - delay before removing mobs from a map [Skotlex]
	int mob_active_time; //Duration through which mobs execute their Hard AI after players leave their area of sight.
	int boss_active_time;

	int show_hp_sp_drain, show_hp_sp_gain;  //[Skotlex]

	int mob_npc_event_type; //Determines on who the npc_event is executed. [Skotlex]

	int character_size; // if riders have size=2, and baby class riders size=1 [Lupus]
	int rare_drop_announce; // chance <= to show rare drops global announces

	int retaliate_to_master;    //Whether when a mob is attacked by another mob, it will retaliate versus the mob or the mob's master. [Skotlex]

	int duel_allow_pvp; // [LuzZza]
	int duel_allow_gvg; // [LuzZza]
	int duel_allow_teleport; // [LuzZza]
	int duel_autoleave_when_die; // [LuzZza]
	int duel_time_interval; // [LuzZza]
	int duel_only_on_same_map; // [Toms]

	int skip_teleport_lv1_menu; // possibility to disable (skip) Teleport Lv1 menu, that have only two lines `Random` and `Cancel` [LuzZza]
	int mob_max_skilllvl; // Max possible skill level [Lupus]
	int allow_skill_without_day; // [Komurka]
	int allow_es_magic_pc; // [Skotlex]
	int skill_wall_check; // [Skotlex]
	int cell_stack_limit; // [Skotlex]
	int skill_caster_check; // [Skotlex]
	int sc_castcancel; // [Skotlex]
	int pc_sc_def_rate; // [Skotlex]
	int mob_sc_def_rate;
	int pc_luk_sc_def; 
	int mob_luk_sc_def; 
	int pc_max_sc_def;
	int mob_max_sc_def;

	int sg_angel_skill_ratio;
	int sg_miracle_skill_ratio;
	int sg_miracle_skill_duration;
	int autospell_stacking; //Enables autospell cards to stack. [Skotlex]
	int override_mob_names; //Enables overriding spawn mob names with the mob_db names. [Skotlex]
	int min_chat_delay; //Minimum time between client messages. [Skotlex]
	int friend_auto_add; //When accepting friends, both get friended. [Skotlex]
	int hvan_explosion_intimate;    // fix [albator]
	int hom_rename;
	int homunculus_show_growth ;    //[orn]
	int homunculus_friendly_rate;
	int quest_exp_rate;
	int autotrade_mapflag;
	int at_timeout;
	int homunculus_autoloot;
	int idle_no_autoloot;
	int max_guild_alliance;
	int ksprotection;
	int auction_feeperhour;
	int auction_maximumprice;
	int homunculus_auto_vapor;  //Keep Homunculus from Vaporizing when master dies. [L0ne_W0lf]
	int display_status_timers;  //Show or hide skill buff/delay timers in recent clients [Sara]
	int skill_add_heal_rate;    //skills that bHealPower has effect on [Inkfish]
	int eq_single_target_reflectable;
	int invincible_nodamage;
	int mob_slave_keep_target;
	int autospell_check_range;  //Enable range check for autospell bonus. [L0ne_W0lf]
	int client_reshuffle_dice;  // Reshuffle /dice
	int client_sort_storage;
	int feature_buying_store;
	int feature_search_stores;
	int searchstore_querydelay;
	int searchstore_maxresults;
	int display_party_name;
	int cashshop_show_points;
	int mail_show_status;
	int client_limit_unit_lv;
	int emblem_transparency_limit;
	int hom_max_level;
	int hom_S_max_level;

	// [BattleGround Settings]
	int bg_update_interval;
	int bg_flee_penalty;

	// [brAthena]
	int devotion_rdamage;
	int warp_no_ress;
	int mob_drop_identified;
	int bRO_Renewal;
	int alliance_in_woe;
	int use_item_in_status;
	int supports_castle_gvg;
	int max_atk;
	int hanbok_ignorepalette;
	int oktoberfest_ignorepalette;
	int edp_rate;
	int walk_speed_default;
	int official_rates;
	int ip_exp_bonus;
	int ip_exp_extra;
	int ip_exp_penalty;
	int ip_exp_drop;

	// rAthena
	int max_third_parameter;
	int max_baby_third_parameter;
	int max_extended_parameter;
	int atcommand_max_stat_bypass;
	int max_third_aspd;
	int vcast_stat_scale;

	int mvp_tomb_enabled;

	int atcommand_suggestions_enabled;
    	int min_npc_vendchat_distance;
	int atcommand_mobinfo_type;

	int mob_size_influence; // Enable modifications on earned experience, drop rates and monster status depending on monster size. [mkbu95]

	int skill_trap_type;
	int skill_trap_type_ot;
	int item_restricted_consumption_type;
	int max_walk_path;
	int item_enabled_npc;
	int packet_obfuscation;
	int idletime_criteria;

	int bowling_bash_area;
	int gm_ignore_warpable_area;

	int client_accept_chatdori; // [Ai4rei/Mirei]
	int snovice_call_type;
	int guild_notice_changemap;

	int feature_banking;
	int feature_auction;

	int mon_trans_disable_in_gvg;

	int case_sensitive_aegisnames;
} battle_config;

/* criteria for battle_config.idletime_critera */
enum e_battle_config_idletime {
	BCIDLE_WALK          = 0x001,
	BCIDLE_USESKILLTOID  = 0x002,
	BCIDLE_USESKILLTOPOS = 0x004,
	BCIDLE_USEITEM       = 0x008,
	BCIDLE_ATTACK        = 0x010,
	BCIDLE_CHAT          = 0x020,
	BCIDLE_SIT           = 0x040,
	BCIDLE_EMOTION       = 0x080,
	BCIDLE_DROPITEM      = 0x100,
	BCIDLE_ATCOMMAND     = 0x200,
};

// Dammage delayed info
struct delay_damage {
	int src_id;
	int target_id;
	int64 damage;
	int delay;
	unsigned short distance;
	uint16 skill_lv;
	uint16 skill_id;
	enum damage_lv dmg_lv;
	unsigned short attack_type;
	bool additional_effects;
	enum bl_type src_type;
};

/**
 * Vars
 **/
// (Used in read pc.c,) attribute table (battle_attr_fix)
extern int attr_fix_table[4][10][10];


// Damage Calculation

struct Damage battle_calc_attack(int attack_type,struct block_list *bl,struct block_list *target,uint16 skill_id,uint16 skill_lv,int count);
struct Damage battle_calc_weapon_attack(struct block_list *src,struct block_list *target,uint16 skill_id,uint16 skill_lv,int wflag);
struct Damage battle_calc_magic_attack(struct block_list *src,struct block_list *target,uint16 skill_id,uint16 skill_lv,int mflag);
struct Damage battle_calc_misc_attack(struct block_list *src,struct block_list *target,uint16 skill_id,uint16 skill_lv,int mflag);

void battle_reflect_damage(struct block_list *target, struct block_list *src, struct Damage *wd,uint16 skill_id);

void battle_drain(struct map_session_data *sd, struct block_list *tbl, int64 rdamage, int64 ldamage, int race, int boss);

int battle_attr_ratio(int atk_elem,int def_type, int def_lv);
int64 battle_attr_fix(struct block_list *src, struct block_list *target, int64 damage,int atk_elem,int def_type, int def_lv);
int64 battle_calc_cardfix(int attack_type, struct block_list *src, struct block_list *target, int nk, int s_ele, int s_ele_, int64 damage, int cflag, int wflag);


int64 battle_addmastery(struct map_session_data *sd,struct block_list *target,int64 dmg,int type);
int battle_calc_drain(int64 damage, int rate, int per);
int battle_range_type(struct block_list *src, struct block_list *target, uint16 skill_id, uint16 skill_lv);
int battle_adjust_skill_damage(int m, unsigned short skill_id);
int battle_blewcount_bonus(struct map_session_data *sd, uint16 skill_id);
int battle_delay_damage_sub(int tid, int64 tick, int id, intptr_t data);
int battle_getenemyarea_sub(struct block_list *bl, va_list ap);
int battle_getenemy_sub(struct block_list *bl, va_list ap);
int battle_gettargeted_sub(struct block_list *bl, va_list ap);


// Final calculation Damage
int64 battle_calc_damage(struct block_list *src,struct block_list *bl,struct Damage *d,int64 damage,uint16 skill_id,uint16 skill_lv);
int64 battle_calc_gvg_damage(struct block_list *src,struct block_list *bl,int64 damage,int div_,uint16 skill_id,uint16 skill_lv,int flag);
int64 battle_calc_bg_damage(struct block_list *src, struct block_list *bl, int64 damage, int div_, uint16 skill_id, uint16 skill_lv, int flag);

int battle_delay_damage(int64 tick, int amotion, struct block_list *src, struct block_list *target, int attack_type, uint16 skill_id, uint16 skill_lv, int64 damage, enum damage_lv dmg_lv, int ddelay, bool additional_effects);

// Summary normal attack treatment (basic attack)
enum damage_lv battle_weapon_attack(struct block_list *bl,struct block_list *target,int64 tick,int flag);

// Accessors
struct block_list *battle_get_master(struct block_list *src);
struct block_list *battle_gettargeted(struct block_list *target);
struct block_list *battle_getenemy(struct block_list *target, int type, int range);
int battle_gettarget(struct block_list *bl);
int battle_getcurrentskill(struct block_list *bl);


bool battle_check_undead(int race,int element);
int battle_check_target(struct block_list *src, struct block_list *target,int flag);
bool battle_check_range(struct block_list *src,struct block_list *bl,int range);

/* applies element modifiers */  
int64 battle_calc_elefix(struct block_list *src, struct block_list *target, uint16 skill_id, uint16 skill_lv, int64 damage, int nk, int n_ele, int s_ele, int s_ele_, bool left, int flag);
  /* applies mastery modifiers */  
int64 battle_calc_masteryfix(struct block_list *src, struct block_list *target, uint16 skill_id, uint16 skill_lv, int64 damage, int div, bool left, bool weapon);
int battle_calc_chorusbonus(struct map_session_data *sd);
  /* applies skill modifiers */  
int battle_calc_skillratio(int attack_type, struct block_list *src, struct block_list *target, uint16 skill_id, uint16 skill_lv, int skillratio, int flag);
  /* applies size modifiers */
int64 battle_calc_sizefix(struct map_session_data *sd, int64 damage, int type, int size,  bool ignore);
  /* get weapon damage */
int64 battle_calc_weapon_damage(struct block_list *src, struct block_list *bl, uint16 skill_id, uint16 skill_lv, struct weapon_atk *watk, int nk, bool n_ele, short s_ele, short s_ele_, int size, int type, int flag, int flag2);
  /* applies defense reductions */
int64 battle_calc_defense(int attack_type, struct block_list *src, struct block_list *target, uint16 skill_id, uint16 skill_lv, int64 damage, int flag, int pdef);

int64 battle_calc_base_damage(struct block_list *src, struct block_list *bl, uint16 skill_id, uint16 skill_lv, int nk, bool n_ele, short s_ele, short s_ele_, int type, int flag, int flag2);
int64 battle_calc_base_damage2(struct status_data *st, struct weapon_atk *wa, struct status_change *sc, unsigned short t_size, struct map_session_data *sd, int flag);

void battle_consume_ammo(struct map_session_data *sd, int skill, int lv);
// Settings


void do_init_battle(void);
void do_final_battle(void);
extern int battle_config_read(const char *cfgName);
extern void battle_validate_conf(void);
extern void battle_set_defaults(void);
int battle_set_value(const char *w1, const char *w2);
int battle_get_value(const char *w1);
//
struct block_list *battle_getenemyarea(struct block_list *src, int x, int y, int range, int type, int ignore_id);
/**
 * Royal Guard
 **/
int battle_damage_area(struct block_list *bl, va_list ap);

#endif /* _BATTLE_H_ */
