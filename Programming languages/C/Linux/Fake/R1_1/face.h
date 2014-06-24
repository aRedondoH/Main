/*
 * face.h
 *
 *  Created on: Jun 18, 2014
 *      Author: secnok
 */

#ifndef FACE_H_
#define FACE_H_

/* Run an Agent with Malformed event data */
void RunAgentWithMalformedEventData();
/* Run an Agent with Malformed event data (only send one event )*/
void RunAgentWithMalformedEventDataSendOneEvent();
/* Run an Agent with event data that is correctly formed but contains invalid or out-of-range data */
void RunAgentContainsInvalidOrOutOfRangeData();
/* Run an Agent with invalid cert */
void RunAgentWithInvalidCert();
/* Run an Agent with invalid key */
void RunAgentWithInvalidKey();
/* Run an Agent with invalid detector cert */
void RunAgentWithInvalidDetectorCert();
/* Run an Agent with predefined event sequences (behaviour analysis) */
void RunAgentWithPredefinedEventSequences();

#endif /* FACE_H_ */
