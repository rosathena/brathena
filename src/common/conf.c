/****************************************************************************!
*                _           _   _   _                                       *    
*               | |__  _ __ / \ | |_| |__   ___ _ __   __ _                  *  
*               | '_ \| '__/ _ \| __| '_ \ / _ \ '_ \ / _` |                 *   
*               | |_) | | / ___ \ |_| | | |  __/ | | | (_| |                 *    
*               |_.__/|_|/_/   \_\__|_| |_|\___|_| |_|\__,_|                 *    
*                                                                            *
*                                                                            *
* \file src/common/conf.c                                                    *
* Descri��o Prim�ria.                                                        *
* Descri��o mais elaborada sobre o arquivo.                                  *
* \author brAthena                                                           *
* \date ?                                                                    *
* \todo ?                                                                    *   
*****************************************************************************/ 

#include "conf.h"
#include "../../3rdparty/libconfig/libconfig.h"

#include "../common/showmsg.h" // ShowError
#include <string.h> // read_message

/* interface source */
struct libconfig_interface libconfig_s;

struct brathena_config bra_config;

int conf_read_file(config_t *config, const char *config_filename) {
	libconfig->init(config);
	if(!libconfig->read_file_src(config, config_filename)) {
		ShowError("%s:%d - %s\n", config_error_file(config),
		          config_error_line(config), config_error_text(config));
		libconfig->destroy(config);
		return 1;
	}
	return 0;
}

//
// Functions to copy settings from libconfig/contrib
//
void config_setting_copy_simple(config_setting_t *parent, const config_setting_t *src) {
	if(config_setting_is_aggregate(src)) {
		libconfig->setting_copy_aggregate(parent, src);
	} else {
		config_setting_t *set;

		if( libconfig->setting_get_member(parent, config_setting_name(src)) != NULL )
			return;

		if ((set = libconfig->setting_add(parent, config_setting_name(src), config_setting_type(src))) == NULL)
			return;

		if(CONFIG_TYPE_INT == config_setting_type(src)) {
			libconfig->setting_set_int(set, libconfig->setting_get_int(src));
			libconfig->setting_set_format(set, src->format);
		} else if(CONFIG_TYPE_INT64 == config_setting_type(src)) {
			libconfig->setting_set_int64(set, libconfig->setting_get_int64(src));
			libconfig->setting_set_format(set, src->format);
		} else if(CONFIG_TYPE_FLOAT == config_setting_type(src)) {
			libconfig->setting_set_float(set, libconfig->setting_get_float(src));
		} else if(CONFIG_TYPE_STRING == config_setting_type(src)) {
			libconfig->setting_set_string(set, libconfig->setting_get_string(src));
		} else if(CONFIG_TYPE_BOOL == config_setting_type(src)) {
			libconfig->setting_set_bool(set, libconfig->setting_get_bool(src));
		}
	}
}

void config_setting_copy_elem(config_setting_t *parent, const config_setting_t *src) {
	config_setting_t *set = NULL;

	if(config_setting_is_aggregate(src))
		libconfig->setting_copy_aggregate(parent, src);
	else if(CONFIG_TYPE_INT == config_setting_type(src)) {
		set = libconfig->setting_set_int_elem(parent, -1, libconfig->setting_get_int(src));
		libconfig->setting_set_format(set, src->format);
	} else if(CONFIG_TYPE_INT64 == config_setting_type(src)) {
		set = libconfig->setting_set_int64_elem(parent, -1, libconfig->setting_get_int64(src));
		libconfig->setting_set_format(set, src->format);
	} else if(CONFIG_TYPE_FLOAT == config_setting_type(src)) {
		libconfig->setting_set_float_elem(parent, -1, libconfig->setting_get_float(src));
	} else if(CONFIG_TYPE_STRING == config_setting_type(src)) {
		libconfig->setting_set_string_elem(parent, -1, libconfig->setting_get_string(src));
	} else if(CONFIG_TYPE_BOOL == config_setting_type(src)) {
		libconfig->setting_set_bool_elem(parent, -1, libconfig->setting_get_bool(src));
	}
}

void config_setting_copy_aggregate(config_setting_t *parent, const config_setting_t *src) {
	config_setting_t *newAgg;
	int i, n;

	if(libconfig->setting_get_member(parent, config_setting_name(src)) != NULL)
		return;

	newAgg = libconfig->setting_add(parent, config_setting_name(src), config_setting_type(src));

	if(newAgg == NULL)
		return;

	n = libconfig->setting_length(src);

	for(i = 0; i < n; i++) {
		if(config_setting_is_group(src)) {
			libconfig->setting_copy_simple(newAgg, libconfig->setting_get_elem(src, i));
		} else {
			libconfig->setting_copy_elem(newAgg, libconfig->setting_get_elem(src, i));
		}
	}
}

int config_setting_copy(config_setting_t *parent, const config_setting_t *src) {
	if(!config_setting_is_group(parent) && !config_setting_is_list(parent))
		return CONFIG_FALSE;

	if(config_setting_is_aggregate(src)) {
		libconfig->setting_copy_aggregate(parent, src);
	} else {
		libconfig->setting_copy_simple(parent, src);
	}
	return CONFIG_TRUE;
}

// Leitura de configura��es exclusivas do brAthena.
void read_brathena_config(void)
{
	const char *tmpchar;
	int tmpint;
	config_t configbrA;
	
	memset(&bra_config, 0, sizeof(bra_config));
	config_init(&configbrA);
	
	if(!libconfig->read_file_src(&configbrA, "conf/battle/brathena.conf")) {
		ShowError("read_brathena_config erro: %s:%d - %s\n", config_error_file(&configbrA), config_error_line(&configbrA), config_error_text(&configbrA));
		libconfig->destroy(&configbrA);
	}	

	if(libconfig->lookup_int(&configbrA, "max_rename_char", &tmpint))	bra_config.max_rename_char = tmpint;
	if(libconfig->lookup_string(&configbrA, "lang_file", &tmpchar))		strncpy(bra_config.lang_file, tmpchar, sizeof(bra_config.lang_file));
	if(libconfig->lookup_int(&configbrA, "enable_system_vip", &tmpint))	bra_config.enable_system_vip = tmpint;
	if(libconfig->lookup_int(&configbrA, "level_vip", &tmpint))			bra_config.level_vip = tmpint;
	if(libconfig->lookup_int(&configbrA, "extra_exp_vip_base", &tmpint))bra_config.extra_exp_vip_base = tmpint;
	if(libconfig->lookup_int(&configbrA, "extra_exp_vip_job", &tmpint))bra_config.extra_exp_vip_job = tmpint;
	if(libconfig->lookup_int(&configbrA, "penalty_exp_vip_base", &tmpint))bra_config.penalty_exp_vip_base = tmpint;
	if(libconfig->lookup_int(&configbrA, "penalty_exp_vip_job", &tmpint))bra_config.penalty_exp_vip_job = tmpint;
	if(libconfig->lookup_int(&configbrA, "msg_maps_removed", &tmpint))	bra_config.msg_maps_removed = tmpint;
	if(libconfig->lookup_int(&configbrA, "show_message_exp", &tmpint))	bra_config.show_message_exp = tmpint;	

	libconfig->destroy(&configbrA);
}

void libconfig_defaults(void) {
	libconfig = &libconfig_s;

	libconfig->read = config_read;
	libconfig->write = config_write;
	/* */
	libconfig->set_auto_convert = config_set_auto_convert;
	libconfig->get_auto_convert = config_get_auto_convert;
	/* */
	libconfig->read_string = config_read_string;
	libconfig->read_file_src = config_read_file;
	libconfig->write_file = config_write_file;
	/* */
	libconfig->set_destructor = config_set_destructor;
	libconfig->set_include_dir = config_set_include_dir;
	/* */
	libconfig->init = config_init;
	libconfig->destroy = config_destroy;
	/* */
	libconfig->setting_get_int = config_setting_get_int;
	libconfig->setting_get_int64 = config_setting_get_int64;
	libconfig->setting_get_float = config_setting_get_float;
	libconfig->setting_get_bool = config_setting_get_bool;
	libconfig->setting_get_string = config_setting_get_string;
	/* */
	libconfig->setting_lookup_int = config_setting_lookup_int;
	libconfig->setting_lookup_int64 = config_setting_lookup_int64;
	libconfig->setting_lookup_float = config_setting_lookup_float;
	libconfig->setting_lookup_bool = config_setting_lookup_bool;
	libconfig->setting_lookup_string = config_setting_lookup_string;
	/* */
	libconfig->setting_set_int = config_setting_set_int;
	libconfig->setting_set_int64 = config_setting_set_int64;
	libconfig->setting_set_bool = config_setting_set_bool;
	libconfig->setting_set_string = config_setting_set_string;
	/* */
	libconfig->setting_set_format = config_setting_set_format;
	libconfig->setting_get_format = config_setting_get_format;
	/* */
	libconfig->setting_get_int_elem = config_setting_get_int_elem;
	libconfig->setting_get_int64_elem = config_setting_get_int64_elem;
	libconfig->setting_get_float_elem = config_setting_get_float_elem;
	libconfig->setting_get_bool_elem = config_setting_get_bool_elem;
	libconfig->setting_get_string_elem = config_setting_get_string_elem;
	/* */
	libconfig->setting_set_int_elem = config_setting_set_int_elem;
	libconfig->setting_set_int64_elem = config_setting_set_int64_elem;
	libconfig->setting_set_float_elem = config_setting_set_float_elem;
	libconfig->setting_set_bool_elem = config_setting_set_bool_elem;
	libconfig->setting_set_string_elem = config_setting_set_string_elem;
	/* */
	libconfig->setting_index = config_setting_index;
	libconfig->setting_length = config_setting_length;
	/* */
	libconfig->setting_get_elem = config_setting_get_elem;
	libconfig->setting_get_member = config_setting_get_member;
	/* */
	libconfig->setting_add = config_setting_add;
	libconfig->setting_remove = config_setting_remove;
	libconfig->setting_remove_elem = config_setting_remove_elem;
	/* */
	libconfig->setting_set_hook = config_setting_set_hook;
	/* */
	libconfig->lookup = config_lookup;
	libconfig->lookup_from = config_lookup_from;
	/* */
	libconfig->lookup_int = config_lookup_int;
	libconfig->lookup_int64 = config_lookup_int64;
	libconfig->lookup_float = config_lookup_float;
	libconfig->lookup_bool = config_lookup_bool;
	libconfig->lookup_string = config_lookup_string;
	/* those are custom and are from src/common/conf.c */
	libconfig->read_file = conf_read_file;
	libconfig->setting_copy_simple = config_setting_copy_simple;
	libconfig->setting_copy_elem = config_setting_copy_elem;
	libconfig->setting_copy_aggregate = config_setting_copy_aggregate;
	libconfig->setting_copy = config_setting_copy;
	libconfig->brathena_config = read_brathena_config;
}

