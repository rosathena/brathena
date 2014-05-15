/****************************************************************************!
*                _           _   _   _                                       *    
*               | |__  _ __ / \ | |_| |__   ___ _ __   __ _                  *  
*               | '_ \| '__/ _ \| __| '_ \ / _ \ '_ \ / _` |                 *   
*               | |_) | | / ___ \ |_| | | |  __/ | | | (_| |                 *    
*               |_.__/|_|/_/   \_\__|_| |_|\___|_| |_|\__,_|                 *    
*                                                                            *
*                                                                            *
* \file src/char/int_storage.h                                               *
* Descri��o Prim�ria.                                                        *
* Descri��o mais elaborada sobre o arquivo.                                  *
* \author brAthena, Athena, eAthena                                          *
* \date ?                                                                    *
* \todo ?                                                                    *  
*****************************************************************************/ 

#ifndef _INT_STORAGE_SQL_H_
#define _INT_STORAGE_SQL_H_

struct storage_data;
struct guild_storage;

int inter_storage_sql_init(void);
void inter_storage_sql_final(void);
int inter_storage_delete(int account_id);
int inter_guild_storage_delete(int guild_id);

int inter_storage_parse_frommap(int fd);

//Exported for use in the TXT-SQL converter.
int storage_fromsql(int account_id, struct storage_data* p);
int storage_tosql(int account_id,struct storage_data *p);
int guild_storage_tosql(int guild_id, struct guild_storage *p);

#endif /* _INT_STORAGE_SQL_H_ */
