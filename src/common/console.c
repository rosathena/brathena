/****************************************************************************!
*                _           _   _   _                                       *
*               | |__  _ __ / \ | |_| |__   ___ _ __   __ _                  *
*               | '_ \| '__/ _ \| __| '_ \ / _ \ '_ \ / _` |                 *
*               | |_) | | / ___ \ |_| | | |  __/ | | | (_| |                 *
*               |_.__/|_|/_/   \_\__|_| |_|\___|_| |_|\__,_|                 *
*                                                                            *
*                                                                            *
* \file src/common/console.c                                                 *
* Descri��o Prim�ria.                                                        *
* Descri��o mais elaborada sobre o arquivo.                                  *
* \author brAthena, Athena, eAthena                                          *
* \date ?                                                                    *
* \todo ?                                                                    *
*****************************************************************************/

#include "../common/cbasetypes.h"
#include "../common/showmsg.h"
#include "../common/core.h"
#include "../common/sysinfo.h"
#include "../config/core.h"
#include "console.h"

#ifndef MINICORE
	#include "../common/ers.h"
	#include "../common/malloc.h"
	#include "../common/atomic.h"
	#include "../common/spinlock.h"
	#include "../common/thread.h"
	#include "../common/mutex.h"
	#include "../common/timer.h"
	#include "../common/strlib.h"
	#include "../common/sql.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#if !defined(WIN32)
	#include <unistd.h>
	#include <sys/time.h>
#else
	#include "../common/winapi.h" // Console close event handling
#endif

#ifdef CONSOLE_INPUT
	#if defined(WIN32)
		#include <conio.h> /* _kbhit() */
	#endif
#endif

struct console_interface console_s;

/*======================================
 *	CORE : Display title
 *--------------------------------------*/
void display_title(void) {
	const char *vcstype = sysinfo->vcstype();

	ShowMessage("\n");
	ShowMessage(""CL_BG_GREEN""CL_BT_WHITE"                                                                      "CL_CLL""CL_NORMAL"\n");
	ShowMessage(""CL_BG_GREEN""CL_BT_WHITE"                        brA Dev.Team apresenta                        "CL_CLL""CL_NORMAL"\n");
	ShowMessage(""CL_BG_GREEN""CL_BT_WHITE"                                                                      "CL_CLL""CL_NORMAL"\n");
	ShowMessage(""CL_BG_GREEN""CL_BT_WHITE"                _           ___  _   _                                "CL_CLL""CL_NORMAL"\n");
	ShowMessage(""CL_BG_GREEN""CL_BT_WHITE"               | |         / _ \\| | | |                              "CL_CLL""CL_NORMAL"\n");
	ShowMessage(""CL_BG_GREEN""CL_BT_WHITE"               | |__  _ __/ /_\\ \\ |_| |__   ___ _ __   __ _         "CL_CLL""CL_NORMAL"\n");
	ShowMessage(""CL_BG_GREEN""CL_BT_WHITE"               | '_ \\| '__|  _  | __| '_ \\ / _ \\ '_ \\ / _` |      "CL_CLL""CL_NORMAL"\n");
	ShowMessage(""CL_BG_GREEN""CL_BT_WHITE"               | |_) | |  | | | | |_| | | |  __/ | | | (_| |          "CL_CLL""CL_NORMAL"\n");
	ShowMessage(""CL_BG_GREEN""CL_BT_WHITE"               |_.__/|_|  \\_| |_/\\__|_| |_|\\___|_| |_|\\__,_|      "CL_CLL""CL_NORMAL"\n");
	ShowMessage(""CL_BG_GREEN""CL_BT_WHITE"                                                                      "CL_CLL""CL_NORMAL"\n");
	ShowMessage(""CL_BG_GREEN""CL_BT_WHITE"                 Projeto brAthena (c) 2008 - 2014                     "CL_CLL""CL_NORMAL"\n");
	ShowMessage(""CL_BG_GREEN""CL_BT_WHITE"                          www.brathena.org                            "CL_CLL""CL_NORMAL"\n");
	ShowMessage(""CL_BG_GREEN""CL_BT_WHITE"                                                                      "CL_CLL""CL_NORMAL"\n");

	ShowInfo(read_message("Source.common.core_revision"), sysinfo->is64bit() ? 64 : 32, sysinfo->platform());
	ShowInfo(read_message("Source.common.core_revision1"), vcstype, CL_WHITE, sysinfo->vcsrevision_src(), CL_RESET);
	ShowInfo(read_message("Source.common.core_revision2"), vcstype, CL_WHITE, sysinfo->vcsrevision_scripts(), CL_RESET);
	ShowInfo(read_message("Source.common.core_revision3"), CL_WHITE, sysinfo->osversion(), CL_RESET, sysinfo->arch());
	ShowInfo(read_message("Source.common.core_revision4"), CL_WHITE, sysinfo->cpu(), sysinfo->cpucores(), CL_RESET);
	ShowInfo(read_message("Source.common.core_revision5"), sysinfo->compiler());
	ShowInfo(read_message("Source.common.core_revision5"), sysinfo->cflags());

	#if VERSION == -1
		ShowInfo(read_message("Source.common.emulator_mode_ot"), CL_RED, CL_RESET, CL_GREEN, CL_RESET);
	#elif VERSION == 0
		ShowInfo(read_message("Source.common.emulator_mode_pre"), CL_RED, CL_RESET, CL_GREEN, CL_RESET);
	#else
		ShowInfo(read_message("Source.common.emulator_mode_re"), CL_RED, CL_RESET, CL_GREEN, CL_RESET);
	#endif
	ShowInfo(read_message("Source.common.client_version1"), CL_RED, CL_RESET, CL_GREEN, PACKETVER, CL_RESET);
	ShowInfo(read_message("Source.common.client_version2"), CL_RED, CL_RESET);

}
#ifdef CONSOLE_INPUT
#if defined(WIN32)
int console_parse_key_pressed(void) {
	return _kbhit();
}
#else /* WIN32 */
int console_parse_key_pressed(void) {
	struct timeval tv;
	fd_set fds;
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	
	FD_ZERO(&fds);
	FD_SET(STDIN_FILENO, &fds);
	
	select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
	
	return FD_ISSET(STDIN_FILENO, &fds);
}
#endif /* _WIN32 */

/*======================================
 *	CORE: Console commands
 *--------------------------------------*/

/**
 * Stops server
 **/
CPCMD_C(exit,server) {
	runflag = 0;
}

/**
 * Displays ERS-related statistics (Entry Reusage System)
 **/
CPCMD_C(ers_report,server) {
	ers_report();
}

/**
 * Displays memory usage
 **/
CPCMD_C(mem_report,server) {
	memmgr_report(line?atoi(line):0);
}

/**
 * Displays command list
 **/
CPCMD(help) {
	unsigned int i = 0;
	for ( i = 0; i < console->cmd_list_count; i++ ) {
		if( console->cmd_list[i]->next_count ) {
			ShowInfo("- '"CL_WHITE"%s"CL_RESET"' subs\n",console->cmd_list[i]->cmd);
			console->parse_list_subs(console->cmd_list[i],2);
		} else {
			ShowInfo("- '"CL_WHITE"%s"CL_RESET"'\n",console->cmd_list[i]->cmd);
		}
	}
}

/**
 * [Ind]
 * Displays current malloc usage
 */
CPCMD_C(malloc_usage,server) {
	unsigned int val = (unsigned int)iMalloc->usage();
	ShowInfo("malloc_usage: %.2f MB\n",(double)(val)/1024);
}
/**
 * Defines a main category
 * Categories can't be used as commands!
 * CP_DEF_C(category)
 **/
#define CP_DEF_C(x) { #x , NULL , NULL, NULL }
/**
 * Defines a sub-category
 * Sub-categories can't be used as commands!
 * CP_DEF_C2(command, category)
 **/
#define CP_DEF_C2(x,y) { #x , NULL , #y, NULL }
/**
 * Defines a command that is inside a category or sub-category
 * CP_DEF_S(command, category/sub-category)
 **/
#define CP_DEF_S(x,y) { #x, CPCMD_C_A(x,y), #y, NULL }
/**
 * Defines a command that is _not_ inside any category
 * CP_DEF_S(command)
 **/
#define CP_DEF(x) { #x , CPCMD_A(x), NULL, NULL }

/**
 * Loads console commands list
 * See CP_DEF_C, CP_DEF_C2, CP_DEF_S, CP_DEF
 **/
void console_load_defaults(void) {
	struct {
		char *name;
		CParseFunc func;
		char *connect;
		struct CParseEntry *self;
	} default_list[] = {
		CP_DEF(help),
		/**
		 * Server related commands
		 **/
		CP_DEF_C(server),
		CP_DEF_S(ers_report,server),
		CP_DEF_S(mem_report,server),
		CP_DEF_S(malloc_usage,server),
		CP_DEF_S(exit,server),
		/**
		 * Sql related commands
		 **/
		CP_DEF_C(sql),
		CP_DEF_C2(update,sql),
	};
	unsigned int i, len = ARRAYLENGTH(default_list);
	struct CParseEntry *cmd;
	
	RECREATE(console->cmds,struct CParseEntry *, len);
	
	for(i = 0; i < len; i++) {
		CREATE(cmd, struct CParseEntry, 1);
		
		safestrncpy(cmd->cmd, default_list[i].name, CP_CMD_LENGTH);
		
		if( default_list[i].func )
			cmd->u.func = default_list[i].func;
		else
			cmd->u.next = NULL;
		
		cmd->next_count = 0;
		
		console->cmd_count++;
		console->cmds[i] = cmd;
		default_list[i].self = cmd;
		if( !default_list[i].connect ) {
			RECREATE(console->cmd_list,struct CParseEntry *, ++console->cmd_list_count);
			console->cmd_list[console->cmd_list_count - 1] = cmd;
		}
	}
	
	for(i = 0; i < len; i++) {
		unsigned int k;
		if( !default_list[i].connect )
			continue;
		for(k = 0; k < console->cmd_count; k++) {
			if( strcmpi(default_list[i].connect,console->cmds[k]->cmd) == 0 ) {
				cmd = default_list[i].self;
				RECREATE(console->cmds[k]->u.next, struct CParseEntry *, ++console->cmds[k]->next_count);
				console->cmds[k]->u.next[console->cmds[k]->next_count - 1] = cmd;
				break;
			}
		}
	}
}
#undef CP_DEF_C
#undef CP_DEF_C2
#undef CP_DEF_S
#undef CP_DEF
void console_parse_create(char *name, CParseFunc func) {
	unsigned int i;
	char *tok;
	char sublist[CP_CMD_LENGTH * 5];
	struct CParseEntry *cmd;
	
	safestrncpy(sublist, name, CP_CMD_LENGTH * 5);
	tok = strtok(sublist,":");
	
	for ( i = 0; i < console->cmd_list_count; i++ ) {
		if( strcmpi(tok,console->cmd_list[i]->cmd) == 0 )
			break;
	}

	if( i == console->cmd_list_count ) {
		RECREATE(console->cmds,struct CParseEntry *, ++console->cmd_count);
		CREATE(cmd, struct CParseEntry, 1);
		safestrncpy(cmd->cmd, tok, CP_CMD_LENGTH);
		cmd->next_count = 0;
		console->cmds[console->cmd_count - 1] = cmd;
		RECREATE(console->cmd_list,struct CParseEntry *, ++console->cmd_list_count);
		console->cmd_list[console->cmd_list_count - 1] = cmd;
		i = console->cmd_list_count - 1;
	}

	cmd = console->cmd_list[i];
	while( ( tok = strtok(NULL, ":") ) != NULL ) {
		
		for(i = 0; i < cmd->next_count; i++) {
			if( strcmpi(cmd->u.next[i]->cmd,tok) == 0 )
				break;
		}
		
		if ( i == cmd->next_count ) {
			RECREATE(console->cmds,struct CParseEntry *, ++console->cmd_count);
			CREATE(console->cmds[console->cmd_count-1], struct CParseEntry, 1);
			safestrncpy(console->cmds[console->cmd_count-1]->cmd, tok, CP_CMD_LENGTH);
			console->cmds[console->cmd_count-1]->next_count = 0;
			RECREATE(cmd->u.next, struct CParseEntry *, ++cmd->next_count);
			cmd->u.next[cmd->next_count - 1] = console->cmds[console->cmd_count-1];
			cmd = console->cmds[console->cmd_count-1];
			continue;
		}
		
	}
	cmd->u.func = func;
}
void console_parse_list_subs(struct CParseEntry *cmd, unsigned char depth) {
	unsigned int i;
	char msg[CP_CMD_LENGTH * 2];
	for( i = 0; i < cmd->next_count; i++ ) {
		if( cmd->u.next[i]->next_count ) {
			memset(msg, '-', depth);
			snprintf(msg + depth,CP_CMD_LENGTH * 2, " '"CL_WHITE"%s"CL_RESET"'",cmd->u.next[i]->cmd);
			ShowInfo("%s subs\n",msg);
			console->parse_list_subs(cmd->u.next[i],depth + 1);
		} else {
			memset(msg, '-', depth);
			snprintf(msg + depth,CP_CMD_LENGTH * 2, " %s",cmd->u.next[i]->cmd);
			ShowInfo("%s\n",msg);
		}
	}
}
void console_parse_sub(char *line) {
	struct CParseEntry *cmd;
	char bline[200];
	char *tok;
	char sublist[CP_CMD_LENGTH * 5];
	unsigned int i, len = 0;
	
	memcpy(bline, line, 200);
	tok = strtok(line, " ");
	
	for ( i = 0; i < console->cmd_list_count; i++ ) {
		if( strcmpi(tok,console->cmd_list[i]->cmd) == 0 )
			break;
	}
	
	if( i == console->cmd_list_count ) {
		ShowError("'"CL_WHITE"%s"CL_RESET"' is not a known command, type '"CL_WHITE"help"CL_RESET"' to list all commands\n",line);
		return;
	}
	
	cmd = console->cmd_list[i];
	
	len += snprintf(sublist,CP_CMD_LENGTH * 5,"%s", cmd->cmd) + 1;
	
	if( cmd->next_count == 0 && console->cmd_list[i]->u.func ) {
		char *r = NULL;
		if( (tok = strtok(NULL, " ")) ) {
			r = bline;
			r += len + 1;
		}
		cmd->u.func(r);
	} else {
		while( ( tok = strtok(NULL, " ") ) != NULL ) {
			for( i = 0; i < cmd->next_count; i++ ) {
				if( strcmpi(cmd->u.next[i]->cmd,tok) == 0 )
					break;
			}
			if( i == cmd->next_count ) {
				if( strcmpi("help",tok) == 0 ) {
					if( cmd->next_count ) {
						ShowInfo("- '"CL_WHITE"%s"CL_RESET"' subs\n",sublist);
						console->parse_list_subs(cmd,2);
					} else {
						ShowError("'"CL_WHITE"%s"CL_RESET"' doesn't possess any subcommands\n",sublist);
					}
					return;
				}
				ShowError("'"CL_WHITE"%s"CL_RESET"' is not a known subcommand of '"CL_WHITE"%s"CL_RESET"'\n",tok,cmd->cmd);
				ShowError("type '"CL_WHITE"%s help"CL_RESET"' to list its subcommands\n",sublist);
				return;
			}
			if( cmd->u.next[i]->next_count == 0 && cmd->u.next[i]->u.func ) {
				char *r = NULL;
				if( (tok = strtok(NULL, " ")) ) {
					r = bline;
					r += len + strlen(cmd->u.next[i]->cmd) + 1;
				}
				cmd->u.next[i]->u.func(r);
				return;
			} else
				cmd = cmd->u.next[i];
			len += snprintf(sublist + len,CP_CMD_LENGTH * 5,":%s", cmd->cmd);
		}
		ShowError("Is only a category, type '"CL_WHITE"%s help"CL_RESET"' to list its subcommands\n",sublist);
	}
}
void console_parse(char* line) {
    int c, i = 0, len = MAX_CONSOLE_INPUT - 1;/* we leave room for the \0 :P */
	
	while( (c = fgetc(stdin)) != EOF ) {
		if( --len == 0 )
			break;
		if( (line[i++] = c) == '\n') {
			line[i-1] = '\0';/* clear, we skip the new line */
			break;/* new line~! we leave it for the next cycle */
		}
	}
	
	line[i++] = '\0';
}
void *cThread_main(void *x) {
		
	while( console->ptstate ) {/* loopx */
		if( console->key_pressed() ) {
			char input[MAX_CONSOLE_INPUT];
					
			console->parse(input);
			if( input[0] != '\0' ) {/* did we get something? */
				EnterSpinLock(&console->ptlock);
				
				if( cinput.count == CONSOLE_PARSE_SIZE ) {
					LeaveSpinLock(&console->ptlock);
					continue;/* drop */
				}
				
				safestrncpy(cinput.queue[cinput.count++],input,MAX_CONSOLE_INPUT);
				LeaveSpinLock(&console->ptlock);
			}
		}
		ramutex_lock( console->ptmutex );
		racond_wait( console->ptcond,	console->ptmutex,  -1 );
		ramutex_unlock( console->ptmutex );
	}
		
	return NULL;
}
int console_parse_timer(int tid, int64 tick, int id, intptr_t data) {
	int i;
	EnterSpinLock(&console->ptlock);
	for(i = 0; i < cinput.count; i++) {
		console->parse_sub(cinput.queue[i]);
	}
	cinput.count = 0;
	LeaveSpinLock(&console->ptlock);
	racond_signal(console->ptcond);
	return 0;
}
void console_parse_final(void) {
	if( console->ptstate ) {
		InterlockedDecrement(&console->ptstate);
		racond_signal(console->ptcond);
		
		/* wait for thread to close */
		rathread_wait(console->pthread, NULL);

		racond_destroy(console->ptcond);
		ramutex_destroy(console->ptmutex);
	}
}
void console_parse_init(void) {
	cinput.count = 0;
	
	console->ptstate = 1;

	InitializeSpinLock(&console->ptlock);
	
	console->ptmutex = ramutex_create();
	console->ptcond = racond_create();
	
	if( (console->pthread = rathread_create(console->pthread_main, NULL)) == NULL ){
		ShowFatalError("console_parse_init: failed to spawn console_parse thread.\n");
		exit(EXIT_FAILURE);
	}
	
	add_timer_func_list(console->parse_timer, "console_parse_timer");
	add_timer_interval(gettick() + 1000, console->parse_timer, 0, 0, 500);/* start listening in 1s; re-try every 0.5s */
	
}
void console_setSQL(Sql *SQL_handle) {
	console->SQL = SQL_handle;
}
#endif /* CONSOLE_INPUT */

void console_init (void) {
#ifdef CONSOLE_INPUT
	console->cmd_count = console->cmd_list_count = 0;
	console->load_defaults();
	console->parse_init();
#endif
}
void console_final(void) {
#ifdef CONSOLE_INPUT
	unsigned int i;
	console->parse_final();
	for( i = 0; i < console->cmd_count; i++ ) {
		if( console->cmds[i]->next_count )
			aFree(console->cmds[i]->u.next);
		aFree(console->cmds[i]);
	}
	aFree(console->cmds);
	aFree(console->cmd_list);
#endif
}
void console_defaults(void) {
	console = &console_s;
	console->init = console_init;
	console->final = console_final;
	console->display_title = display_title;
#ifdef CONSOLE_INPUT
	console->parse_init = console_parse_init;
	console->parse_final = console_parse_final;
	console->parse_timer = console_parse_timer;
	console->pthread_main = cThread_main;
	console->parse = console_parse;
	console->parse_sub = console_parse_sub;
	console->key_pressed = console_parse_key_pressed;
	console->load_defaults = console_load_defaults;
	console->parse_list_subs = console_parse_list_subs;
	console->addCommand = console_parse_create;
	console->setSQL = console_setSQL;
	console->SQL = NULL;
#endif
}
