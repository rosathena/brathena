/****************************************************************************!
*                _           _   _   _                                       *    
*               | |__  _ __ / \ | |_| |__   ___ _ __   __ _                  *  
*               | '_ \| '__/ _ \| __| '_ \ / _ \ '_ \ / _` |                 *   
*               | |_) | | / ___ \ |_| | | |  __/ | | | (_| |                 *    
*               |_.__/|_|/_/   \_\__|_| |_|\___|_| |_|\__,_|                 *    
*                                                                            *
*                                                                            *
* \file src/char/inter.h                                                     *
* Descri��o Prim�ria.                                                        *
* Descri��o mais elaborada sobre o arquivo.                                  *
* \author brAthena, Athena, eAthena                                          *
* \date ?                                                                    *
* \todo ?                                                                    *  
*****************************************************************************/ 

#ifndef _INTER_SQL_H_
#define _INTER_SQL_H_

struct accreg;
#include "../common/sql.h"
#include "char.h"

int inter_init_sql(const char* file);
void inter_final(void);
int inter_parse_frommap(int fd);
int inter_mapif_init(int fd);
int mapif_send_gmaccounts(void);
int mapif_disconnectplayer(int fd, int account_id, int char_id, int reason);
void mapif_parse_accinfo2(bool success, int map_fd, int u_fd, int u_aid, int account_id, const char *userid, const char *user_pass, const char *email, const char *last_ip, const char *lastlogin, const char *pin_code, const char *birthdate, int group_id, int logincount, int state);

int inter_log(char *fmt,...);
int inter_vlog(char *fmt, va_list ap);

#define inter_cfgName "conf/inter-server.conf"

extern unsigned int party_share_level;
extern unsigned int party_family_share_level;

extern Sql* sql_handle;
extern Sql* lsql_handle;

extern char tmp_db_name[32];

int inter_accreg_tosql(int account_id, int char_id, struct accreg *reg, int type);

#endif /* _INTER_SQL_H_ */
