/*
 ============================================================================
 Name        : SslCertificationFromTheClient.c
 Author      : Alberto.R.
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

/* Common libraries */
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <time.h>
#include <dirent.h>

/* PolarSSL includes */
#include "polarssl/config.h"
#include "polarssl/entropy.h"
#include "polarssl/ctr_drbg.h"
#include "polarssl/certs.h"
#include "polarssl/x509.h"
#include "polarssl/ssl.h"
#include "polarssl/net.h"
#include "polarssl/error.h"

#define DEBUG_LEVEL 0
#define SERVER_PORT 5000
#define SSL_AGENT_RSA_CERT "/home/secnok/workspace/SslCertificationFromTheClient/ssl/agent.crt"
#define SSL_AGENT_RSA_KEY "/home/secnok/workspace/SslCertificationFromTheClient/ssl/agent.key"
char * detector_ip;

/* Event type
 * Can be extended once we define more events */
enum detection_type {
	SSL_HANDSHAKE = 1
} event_type;

/* Function to debug polarSSL connection */
static void my_debug(void *ctx, int level, const char *str) {
	if (level < DEBUG_LEVEL) {
		fprintf((FILE *) ctx, "%s", str);
		fflush((FILE *) ctx);
	}
}
/* Transfert events to SNOK_Detector */
int transferEvent(int agentId, int eventTypeId, char *description) {

	int ret;
	int server_fd;
	entropy_context entropy;
	ctr_drbg_context ctr_drbg;
	ssl_context ssl;
	char *pers = "ssl_example";

	time_t agent_time;
	char temp_string[256];

	/*
	 * 1. Load the certificates and private RSA key
	 */

	printf("\n  . Loading the client cert, and key...");
	fflush(stdout);

	x509_crt ssl_agent_crt;
	pk_context ssl_agent_key;

	x509_crt_init(&ssl_agent_crt);
	if ((ret = x509_crt_parse_file(&ssl_agent_crt, SSL_AGENT_RSA_CERT))!=0){
		printf("x509parse_crtfile AGENT CERT returned %d\n", ret);
		goto exit_transferEvent;
	}

	pk_init(&ssl_agent_key);
	if((ret = pk_parse_keyfile(&ssl_agent_key, SSL_AGENT_RSA_KEY, NULL))!=0){
		printf("pk_parse_keyfile AGENT KEY returned %d\n\n", ret);
		goto exit_transferEvent;
	}

	printf(" ok\n ");

	/*
	 * 2.Setup stuff
	 */

	printf(" .Setting up the SSL data.... ");
	fflush(stdout);

	entropy_init(&entropy);

	if ((ret = ctr_drbg_init(&ctr_drbg, entropy_func, &entropy,
			(unsigned char *) pers, strlen(pers))) != 0) {
		printf(" failed\n  ! ctr_drbg_init returned %d\n", ret);
		goto exit_transferEvent;
	}
	memset(&ssl, 0, sizeof(ssl_context));

	if ((ret = net_connect(&server_fd, detector_ip, SERVER_PORT)) != 0) {
		printf(" failed\n  ! net_connect returned %d\n\n", ret);
		goto exit_transferEvent;
	}

	if ((ret = ssl_init(&ssl)) != 0) {
		printf(" failed\n  ! ssl_init returned %d\n\n", ret);
		goto exit_transferEvent;
	}

	ssl_set_endpoint(&ssl, SSL_IS_CLIENT);
	ssl_set_authmode(&ssl, SSL_VERIFY_NONE);
	ssl_set_rng(&ssl, ctr_drbg_random, &ctr_drbg);
	ssl_set_dbg(&ssl, my_debug, stdout);
	ssl_set_bio(&ssl, net_recv, &server_fd, net_send, &server_fd);

	ssl_set_ca_chain(&ssl, ssl_agent_crt.next, NULL, NULL); // fixme should be root ca certicate
	ssl_set_own_cert(&ssl, &ssl_agent_crt, &ssl_agent_key);

	printf("  ok\n ");

	/*
	 * 3. Perform SSL-Handshake
	 */

	printf("   .Performing the SSL/TLS handshake...");
	fflush(stdout);
	while((ret = ssl_handshake(&ssl))!=0){
		if(ret != POLARSSL_ERR_NET_WANT_READ && ret != POLARSSL_ERR_NET_WANT_WRITE){
			printf(" failed\n ! ssl_handshake returned %d\n\n", ret);
			goto exit_transferEvent;
		}
	}

	printf(" ok\n ");

	/*
	 * 4. Verify the server certificate
	 */
	printf(" Veritying the server certificate ");
	fflush(stdout);
	while((ret = ssl_get_verify_result(&ssl))!=0){
		if (ret == BADCERT_EXPIRED){
			printf("failed\n ! server certificate expired %d\n\n",ret);
			goto exit_transferEvent;
		}
		if (ret == BADCERT_REVOKED){
			printf("failed\n !  server certificated revoked %d\n\n",ret);
		}
		if (ret == BADCERT_CN_MISMATCH){
			printf("failed\n !  server certificated cn mismatch %d\n\n",ret);
		}
		if (ret == BADCERT_NOT_TRUSTED){
			printf("failed\n ! server certificated not trusted %d\n\n",ret);
		}
	};

	printf(" ok\n");



	/*
	 * 5. Write data
	 */


	/* Event type */
	snprintf(temp_string, 256, "Event type: %d\n", eventTypeId);
	ssl_write(&ssl, (unsigned char *) temp_string, strlen(temp_string));

	/* AgentId */
	snprintf(temp_string, 256, "Agent id: %d\n", agentId);
	ssl_write(&ssl, (unsigned char *) temp_string, strlen(temp_string));

	/* Agent Time */
	agent_time = time(NULL );
	strftime(temp_string, 31, "Box time: %Y-%m-%d %H:%M:%S\n",
			localtime(&agent_time));
	ssl_write(&ssl, (unsigned char *) temp_string, strlen(temp_string));

	/* Description */
	ssl_write(&ssl, (unsigned char *) description, strlen(description));
	ssl_write(&ssl, (unsigned char *) "\n", 1);

	exit_transferEvent: net_close(server_fd);
	ssl_free(&ssl);



	return ret;
}

int main(int argc, char *argv[]) {
	puts("we are going to do a SSL certification from the client"); /* prints we are goint to do a SSL certification from the client */
	detector_ip=argv[1];
	printf("Detector ip %s\n", detector_ip);
	transferEvent(2,SSL_HANDSHAKE, "trying right handshake");
	return EXIT_SUCCESS;
}
