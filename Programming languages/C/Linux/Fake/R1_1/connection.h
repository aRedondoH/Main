/*
 * connection.h
 *
 *  Created on: May 27, 2014
 *      Author: secnok
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_

/* PolarSSL includes */
#include "polarssl/config.h"
#include "polarssl/entropy.h"
#include "polarssl/ctr_drbg.h"
#include "polarssl/certs.h"
#include "polarssl/x509.h"
#include "polarssl/ssl.h"
#include "polarssl/net.h"
#include "polarssl/error.h"

/* server listens port 5000 */
#define SERVER_PORT 5000

/* ssl key and certificate */
#define SSL_AGENT_RSA_CERT "/etc/snok/ssl/agent.crt" // if fails it shows -10496 exception

#define SSL_AGENT_RSA_KEY "/etc/snok/ssl/agent.key" // if fails it shows -11776 exception

/* detector ca certificate */
#define DETECTOR_CA_CERT  "/etc/snok/ssl/detectorsCA.pem" // if fails it shows -10496 exception


/* CONNECTION FUNCTION HEADERS */
/* Function to debug polarSSL connection */
static void my_debug(void *ctx, int level, const char *str);
/* Transfert events to SNOK_Detector */
int transferEvent(int agentId, int eventTypeId, char *description);



#endif /* CONNECTION_H_ */
