/****************************************************************************!
*                _           _   _   _                                       *    
*               | |__  _ __ / \ | |_| |__   ___ _ __   __ _                  *  
*               | '_ \| '__/ _ \| __| '_ \ / _ \ '_ \ / _` |                 *   
*               | |_) | | / ___ \ |_| | | |  __/ | | | (_| |                 *    
*               |_.__/|_|/_/   \_\__|_| |_|\___|_| |_|\__,_|                 *    
*                                                                            *
*                                                                            *
* \file src/common/netbuffer.c                                               *
* Descri��o Prim�ria.                                                        *
* Descri��o mais elaborada sobre o arquivo.                                  *
* \author brAthena, rAthena                                                  *
* \date ?                                                                    *
* \todo ?                                                                    *  
*****************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../common/cbasetypes.h"
#include "../common/atomic.h"
#include "../common/mempool.h"
#include "../common/showmsg.h"
#include "../common/raconf.h"
#include "../common/thread.h"
#include "../common/malloc.h"
#include "../common/core.h"

#include "../common/netbuffer.h"


//
// Buffers are available in the following sizes:
//	48,      192,    2048,       8192
//	65536 (inter server connects may use it for charstatus struct..)
//


///
// Implementation:
//
static volatile int32 l_nEmergencyAllocations = 0; // stats.
static sysint l_nPools = 0;
static sysint *l_poolElemSize = NULL;
static mempool *l_pool = NULL;


void netbuffer_init()
{
	char localsection[32];
	raconf conf;
	sysint i;

	// Initialize Statistic counters:
	l_nEmergencyAllocations = 0;

	// Set localsection name according to running serverype.
	switch(SERVER_TYPE){
		case SERVER_TYPE_LOGIN:	        strcpy(localsection, "login-netbuffer");		break;
		case SERVER_TYPE_CHAR:	        strcpy(localsection, "char-netbuffer");			break;
		//case ATHENA_SERVER_INTER:	strcpy(localsection, "inter-netbuffer");		break;
		case SERVER_TYPE_MAP:		strcpy(localsection, "map-netbuffer");			break;
		default:			strcpy(localsection, "unsupported_type");		break;
	}


	conf = raconf_parse("conf/network.conf");
	if(conf == NULL) {
		ShowFatalError(read_message("Source.common.net_buffer_init"));
		exit(EXIT_FAILURE);
	}

	// Get Values from config file
	l_nPools = (sysint)raconf_getintEx(conf,  localsection,  "netbuffer", "num", 0);
	if(l_nPools == 0) {
		ShowFatalError(read_message("Source.common.net_buffer_init2"));
		exit(EXIT_FAILURE);
	}

	// Allocate arrays.
	l_poolElemSize = (sysint *)aCalloc(l_nPools, sizeof(sysint));
	l_pool = (mempool *)aCalloc(l_nPools, sizeof(mempool));


	for(i = 0; i < l_nPools; i++) {
		int64 num_prealloc, num_realloc;
		char key[32];

		sprintf(key, "pool_%u_size", (uint32)i+1);
		l_poolElemSize[i] = (sysint)raconf_getintEx(conf, localsection, "netbuffer", key, 4096);
		if(l_poolElemSize[i] < 32) {
			ShowWarning(read_message("Source.common.net_buffer_init3"));
			l_poolElemSize[i] = 32;
		}

		sprintf(key, "pool_%u_prealloc", (uint32)i+1);
		num_prealloc = raconf_getintEx(conf, localsection, "netbuffer", key, 150);

		sprintf(key, "pool_%u_realloc_step", (uint32)i+1);
		num_realloc = raconf_getintEx(conf, localsection, "netbuffer", key, 100);

		// Create Pool!
		sprintf(key, "Netbuffer %u", (uint32)l_poolElemSize[i]); // name.

		// Info
		ShowInfo(read_message("Source.net_buffer_init4"), l_poolElemSize[i], num_prealloc, num_realloc, (float)((sizeof(struct netbuf) + l_poolElemSize[i] - 32)* num_prealloc)/1024.0f/1024.0f);

		//
		// Size Calculation:
		//  struct netbuf  +  requested buffer size - 32 (because the struct already contains 32 byte buffer space at the end of struct)
		l_pool[i] = mempool_create(key, (sizeof(struct netbuf) + l_poolElemSize[i] - 32),  num_prealloc,  num_realloc, NULL, NULL);
		if(l_pool[i] == NULL) {
			ShowFatalError(read_message("Source.net_buffer_init5"), l_poolElemSize[i]);
			// @leak: clean everything :D
			exit(EXIT_FAILURE);
		}

	}//


	raconf_destroy(conf);

}//end: netbuffer_init()


void netbuffer_final() {
	sysint i;

	if(l_nPools > 0) {
		/// .. finalize mempools
		for(i = 0; i < l_nPools; i++) {
			mempool_stats stats = mempool_get_stats(l_pool[i]);

			ShowInfo(read_message("Source.net_buffer_final"), l_poolElemSize[i], stats.peak_nodes_used, stats.num_realloc_events);

			mempool_destroy(l_pool[i]);
		}

		if(l_nEmergencyAllocations > 0) {
			ShowWarning(read_message("Source.net_buffer-final2"), l_nEmergencyAllocations);
			l_nEmergencyAllocations = 0;
		}

		aFree(l_poolElemSize);  l_poolElemSize = NULL;
		aFree(l_pool);  l_pool = NULL;
		l_nPools = 0;
	}


}//end: netbuffer_final()


netbuf netbuffer_get(sysint sz) {
	sysint i;
	netbuf nb = NULL;

	// Search an appropriate pool
	for(i = 0; i < l_nPools; i++) {
		if(sz <= l_poolElemSize[i]) {
			// match

			nb = (netbuf)mempool_node_get(l_pool[i]);
			nb->pool = i;

			break;
		}
	}

	// No Bufferpool found that mets there quirements?.. (thats bad..)
	if(nb == NULL) {
		ShowWarning(read_message("Source.netbuffer_get"), sz);
		ShowWarning(read_message("Source.netbuffer_get2"));

		InterlockedIncrement(&l_nEmergencyAllocations);

		// .. better to check (netbuf struct provides 32 byte bufferspace itself.
		if(sz < 32) sz = 32;

		// allocate memory using malloc ..
		while(1) {
			nb = (netbuf) aMalloc((sizeof(struct netbuf) + sz - 32));
			if(nb != NULL) {
				memset(nb, 0x00, (sizeof(struct netbuf) + sz - 32));  // zero memory! (to enforce commit @ os.)
				nb->pool = -1; // emergency alloc.
				break;
			}

			rathread_yield();
		}// spin allocation.

	}


	nb->refcnt = 1;  // Initial refcount is 1

	return nb;
}//end: netbuffer_get()


void netbuffer_put(netbuf nb) {

	// Decrement reference counter, if > 0 do nothing :)
	if(InterlockedDecrement(&nb->refcnt) > 0)
		return;

	// Is this buffer an emergency allocated buffer?
	if(nb->pool == -1) {
		aFree(nb);
		return;
	}


	// Otherwise its a normal mempool based buffer
	// return it to the according mempool:
	mempool_node_put(l_pool[nb->pool], nb);


}//end: netbuffer_put()


void netbuffer_incref(netbuf nb) {

	InterlockedIncrement(&nb->refcnt);

}//end: netbuf_incref()
