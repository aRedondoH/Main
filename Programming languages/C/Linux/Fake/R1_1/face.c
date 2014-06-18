/*
 * face.c
 *
 *  Created on: Jun 18, 2014
 *      Author: secnok
 */

#include "snok_agent.h"
#include "audit.h"
#include "connection.h"
#include "cpu.h"
#include "firewall.h"
#include "processes.h"
#include "usb.h"

/* Run an Agent with Malformed event data */
void RunAgentWithMalformedEventData(){

	printf("Running agent with Malformed event data:\n");
	int i;
	for (i=0;i<5;i++){
	transferEvent(458448945684754, 99, "Sending malformed event data\n");
	transferEvent(8489454547848, 1234, "Sending malformed event data\n");
	transferEvent(154212454541541, 31313, "Sending malformed event data\n");
	transferEvent(84842545442, 4232, "Sending malformed event data\n");
	transferEvent(3215215454321, 454543, "Sending malformed event data\n");
	transferEvent(23132355454544, 34534, "Sending malformed event data\n");
	transferEvent(65415645545464, 23423, "Sending malformed event data\n");
	transferEvent(354534344454, 1233, "Sending malformed event data\n");
	transferEvent(684854555554541, 23423423, "Sending malformed event data\n");
	}

}

/* Run an Agent with event data that is correctly formed but contains invalid or out-of-range data */
void RunAgentContainsInvalidOrOutOfRangeData(){


}

/* Run an Agent with invalid certificates */
void RunAgentWithInvalidCertificates(){

}

/* Run an Agent with predefined event sequences (behaviour analysis) */
void RunAgentWithPredefinedEventSequences(){

}
