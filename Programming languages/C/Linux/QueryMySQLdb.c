/*
 * HostConfiguration.c
 *
 *  Created on: May 15, 2015
 *      Author: secnok
 */

#include "hostConfiguration.h"
#include "interface.h"

/* Global variables */
GtkWidget * windowHostConfiguration;
GtkWidget * gridHostConfiguration;

GtkWidget * textareaWidget;
GtkWidget * textArea;

GtkWidget * entryHostNodeToEdit;

GtkWidget * entryAgentId;
GtkWidget * entryName;
GtkWidget * entryDescription;
GtkWidget * entryDetectorId;
GtkWidget * entryRigId;

GtkWidget * entryAttentionThreshold;
GtkWidget * entryAlarmThreshold;

GtkWidget * entryUsbValue;
GtkWidget * entryMemoryValue;
GtkWidget * entryCpuValue;
GtkWidget * entryGracefulValue;
GtkWidget * entryDiskUsageValue;
GtkWidget * entryCriticalProcValue;
GtkWidget * entryNonCriticalProcValue;
GtkWidget * entryAntivirusValue;
GtkWidget * entryFirewallValue;
GtkWidget * entryPs2Value;

GtkWidget * checkButtonUsb;
GtkWidget * checkButtonCpu;
GtkWidget * checkButtonMemory;
GtkWidget * checkButtonGraceful;

GtkTextBuffer * ola;

char *db_host, *db_user, *db_pass, *db_name;

/**
 @desc   test to perform in mysql statement
 @param  *stmt is the mysql statement
 @param  status is the status of the query
 */
static int test_stmt_error(MYSQL_STMT *stmt, int status) {
	if (status) {
		fprintf(stderr, "Error: %s (errno: %d)\n", mysql_stmt_error(stmt),
				mysql_stmt_errno(stmt));
		return 1;
	}
	return 0;
}

/**
 @desc   Hanles database connection errors
 @param  con  Mysql connection context
 @return void
 */
void finish_with_error(MYSQL *con) {
	fprintf(stderr, "%s\n", mysql_error(con));
	mysql_close(con);
	exit(1);
}

/**
 @desc   Establishes connection to the database using registered parameters
 @param  con  Mysql connection context
 @return void
 @see    setDatabaseParameters
 */
void connect_to_database(MYSQL *con) {

	//db_host="localhost";
	//db_user="secnok";
	//db_pass="12345678";
	//db_name="SNOK_CONFIG";

	if (con == NULL ) {
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}

	/* Connect to the DB with username and password */
	//if (mysql_real_connect(con, db_host, db_user, db_pass, db_name, 0, NULL, 0) == NULL) {
	if (mysql_real_connect(con, "localhost", "secnok", "12345678",
			"SNOK_CONFIG", 0, NULL, 0) == NULL ) {
		finish_with_error(con);
	}
}

/* check configuration in database */
void checkConfigurationInDB() {

	//ola = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textArea));
	/* Set the default buffer text. */
	//gtk_text_buffer_set_text(ola, "Here will be the current configuration", -1);
	MYSQL_BIND params[1];
	MYSQL_STMT *stmt;
	char *query;
	int index = -1;
	int updated = 0;
	int status;

	/* Init mysql */
	MYSQL *con = mysql_init(NULL );

	/* Connect with database */
	connect_to_database(con);

	query = "SELECT * FROM EventPolicyHostNode";

	stmt = mysql_stmt_init(con);

	if (!stmt) {
		fprintf(stderr, "\n (%d) mysql_stmt_init(): %s", __LINE__,
				mysql_stmt_error(stmt));

	}

	if (mysql_stmt_prepare(stmt, query, strlen(query))) {
		fprintf(stderr, "\n (%d) mysql_stmt_prepare(): %s", __LINE__,
				mysql_stmt_error(stmt));
	}

	/* Set up input buffers for params */
	//memset(params, 0, sizeof(params));
	//fflush(stdout);
	/* update */
	//params[++index].buffer_type = MYSQL_TYPE_LONG;
	//params[index].buffer = &updated;
	//fflush(stdout);
	/* Binding parameter to SQL statement */
	//if (mysql_stmt_bind_param(stmt, params)) {
	//	fprintf(stderr, "\n (%d) mysql_bind_param(): %s", __LINE__,
	//			mysql_stmt_error(stmt));
	//go to exit;
	//}
	//	fflush(stdout);
	/* Running the SQL query */
	if (mysql_stmt_execute(stmt)) {
		fprintf(stderr, "\n (%d) mysql_stmt_execute(): %s", __LINE__,
				mysql_stmt_error(stmt));
		//go to exit;
	}

	//fflush(stdout);
	/* Process results */
	do {
		int i;
		int num_fields; // number of columns in result
		MYSQL_FIELD *fields; // for result set metadata
		MYSQL_BIND *rs_bind; // for output buffers
		int int_data[26]; //output values
		my_bool is_null[26]; // output value nullability

		/* the column count is > 0 if there is a result set 0 otherwise */
		num_fields = mysql_stmt_field_count(stmt);

		printf("Number of fields %d\n", num_fields);
		fflush(stdout);

		if (num_fields > 0) {
			/* there is a result set to fetch */
			MYSQL_RES *rs_metadata = mysql_stmt_result_metadata(stmt);
			if (test_stmt_error(stmt, rs_metadata == NULL ) != 0) {
				printf("metadata stmt error\n");
			}

			fflush(stdout);
			/* Try to allocate output buffers */
			fields = mysql_fetch_fields(rs_metadata);
			rs_bind = (MYSQL_BIND *) malloc(sizeof(MYSQL_BIND) * num_fields);
			if (!rs_bind) {
				printf("Cannot allocate output buffers\n");
			}
			memset(rs_bind, 0, sizeof(MYSQL_BIND) * num_fields);

			/* set up and bind result set output buffers */
			for (i = 0; i < num_fields; i++) {
				rs_bind[i].buffer_type = fields[i].type;
				rs_bind[i].is_null = &is_null[i];

				switch (fields[i].type) {
				case MYSQL_TYPE_LONG:
					rs_bind[i].buffer = (char *) &(int_data[i]);
					rs_bind[i].buffer_length = sizeof(int_data);
					break;
				case MYSQL_TYPE_TINY:
					rs_bind[i].buffer = (signed char *) &(int_data[i]);
					rs_bind[i].buffer_length = sizeof(4);
					break;
				default:
					fprintf(stderr, "ERROR: unexpected type: %d\n",
							fields[i].type);
					break;
				}
			}

			status = mysql_stmt_bind_result(stmt, rs_bind);
			test_stmt_error(stmt, status);

			/* fetch and display result set rows */
			int cal;
			while (1) {
				status = mysql_stmt_fetch(stmt);
				if (status == 1 || status == MYSQL_NO_DATA)
					break;

				for (i = 0; i < num_fields; ++i) {
					switch (rs_bind[i].buffer_type) {

					case MYSQL_TYPE_LONG:
						if (*rs_bind[i].is_null)
							printf(" val[%d] = NULL\n;", i);
						else
							printf(" val[%d] = %ld\n;", i,
									(long) *((int *) rs_bind[i].buffer));
						break;

					case MYSQL_TYPE_TINY:
						if (*rs_bind[i].is_null)
							printf(" val[%d] = NULL\n;", i);
						else
							cal= (int)*((signed char *)rs_bind[i].buffer);
							printf(" val[%lu] = %d\n;", i, cal);
						break;

					default:
						printf("  unexpected type (%d)\n",
								rs_bind[i].buffer_type);
						break;
					}
				}
				printf("\n");

				//sprintf(test1, "hello");

				ola = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textArea));
				/* Set the default buffer text. */
				gtk_text_buffer_set_text(ola, "Hiiiii", -1);

			}
			/* free space bind result */
			mysql_free_result(rs_metadata); /* free metadata */
			free(rs_bind);
			/* more results? -1 = no, >0 = error, 0 = yes (keep looking) */
			status = mysql_stmt_next_result(stmt);
			if (status > 0)
				if (test_stmt_error(stmt, status) != 0)
					printf("exit");
		}

	} while (status == 0);
	mysql_stmt_close(stmt);
	mysql_close(con);

}

/* Send event to the detector */
void saveHostChanges() {

	char * nodeToEdit;

	char * agentId;
	char * name;
	char * description;
	char * detectorId;
	char * rigId;

	char * attentionThreshold;
	char * alarmThreshold;
	char * usbValue;
	char * memoryValue;
	char * cpuValue;
	char * gracefulValue;
	char * diskUsageValue;
	char * criticalProcValue;
	char * nonCriticalProcValue;
	char * antivirusValue;
	char * firewallValue;
	char * ps2Value;

	/* Get node to edit */
	nodeToEdit = gtk_entry_get_text(entryHostNodeToEdit);

	/* Get basic config from entry text fields */
	agentId = gtk_entry_get_text(entryAgentId);
	name = gtk_entry_get_text(entryName);
	description = gtk_entry_get_text(entryDescription);
	detectorId = gtk_entry_get_text(entryDetectorId);
	rigId = gtk_entry_get_text(entryRigId);

	/* Get Event Policy from entry text fields */
	attentionThreshold = gtk_entry_get_text(entryAttentionThreshold);
	alarmThreshold = gtk_entry_get_text(entryAlarmThreshold);
	usbValue = gtk_entry_get_text(entryUsbValue);
	memoryValue = gtk_entry_get_text(entryMemoryValue);
	cpuValue = gtk_entry_get_text(entryCpuValue);
	gracefulValue = gtk_entry_get_text(entryGracefulValue);
	diskUsageValue = gtk_entry_get_text(entryDiskUsageValue);
	criticalProcValue = gtk_entry_get_text(entryCriticalProcValue);
	nonCriticalProcValue = gtk_entry_get_text(entryNonCriticalProcValue);
	antivirusValue = gtk_entry_get_text(entryAntivirusValue);
	firewallValue = gtk_entry_get_text(entryFirewallValue);
	ps2Value = gtk_entry_get_text(entryPs2Value);

	/* Get Security Policy from checklist */
	int currentUsbState = gtk_toggle_button_get_active(checkButtonUsb);
	int currentCpuState = gtk_toggle_button_get_active(checkButtonCpu);
	int currentMemoryState = gtk_toggle_button_get_active(checkButtonMemory);
	int currentGracefulState = gtk_toggle_button_get_active(
			checkButtonGraceful);

	/* Convert char* to int */
	int nodeToEditInt = atoi(nodeToEdit);
	int agentIdInt = atoi(agentId);
	int detectorIdInt = atoi(detectorId);
	int rigIdInt = atoi(rigId);

	int attentionThresholdInt = atoi(attentionThreshold);
	int alarmThresholdInt = atoi(alarmThreshold);
	int usbValueInt = atoi(usbValue);
	int memoryValueInt = atoi(memoryValue);
	int cpuValueInt = atoi(cpuValue);
	int gracefulValueInt = atoi(gracefulValue);
	int diskUsageValueInt = atoi(diskUsageValue);
	int criticalProcValueInt = atoi(criticalProcValue);
	int nonCriticalProcValueInt = atoi(nonCriticalProcValue);
	int antivirusValueInt = atoi(antivirusValue);
	int firewallValueInt = atoi(firewallValue);
	int ps2ValueInt = atoi(ps2Value);

	/* Print integer from node to edit */
	printf("Node to edit: %d\n", nodeToEditInt);

	/* Print integers from basic config */
	printf("Agent id contains: %d\n", agentIdInt);
	printf("Name: %s\n", name);
	printf("Description: %s\n", description);
	printf("Detector id: %d\n", detectorIdInt);
	printf("Rig id: %d\n", rigIdInt);

	/* Print integers from Event Policy */
	printf("Attention threshold: %d\n", attentionThresholdInt);
	printf("Alarm threshold: %d\n", alarmThresholdInt);
	printf("Usb value: %d\n", usbValueInt);
	printf("Memory value: %d\n", memoryValueInt);
	printf("Cpu value: %d\n", cpuValueInt);
	printf("Graceful value: %d\n", gracefulValueInt);
	printf("Disk usage value: %d\n", diskUsageValueInt);
	printf("Critical proc value: %d\n", criticalProcValueInt);
	printf("Non critical proc value: %d\n", nonCriticalProcValueInt);
	printf("Antivirus value: %d\n", antivirusValueInt);
	printf("Firewall value: %d\n", firewallValueInt);
	printf("Ps2 value: %d\n", ps2ValueInt);

	/* Print integers from Security Policy */
	printf("The current usb value is: %d\n", currentUsbState);
	printf("The current cpu value is: %d\n", currentCpuState);
	printf("The current memory value is: %d\n", currentMemoryState);
	printf("The current graceful value is: %d\n", currentGracefulState);

}

/* Reset changes in the fields */
void resetChanges() {

	char * nodeToEdit;

	char * agentId;
	char * name;
	char * description;
	char * detectorId;
	char * rigId;

	char * attentionThreshold;
	char * alarmThreshold;
	char * usbValue;
	char * memoryValue;
	char * cpuValue;
	char * gracefulValue;
	char * diskUsageValue;
	char * criticalProcValue;
	char * nonCriticalProcValue;
	char * antivirusValue;
	char * firewallValue;
	char * ps2Value;

	/* Get node to edit */
	nodeToEdit = gtk_entry_get_text(entryHostNodeToEdit);

	/* Get basic config from entry text fields */
	agentId = gtk_entry_get_text(entryAgentId);
	name = gtk_entry_get_text(entryName);
	description = gtk_entry_get_text(entryDescription);
	detectorId = gtk_entry_get_text(entryDetectorId);
	rigId = gtk_entry_get_text(entryRigId);

	/* Get Event Policy from entry text fields */
	attentionThreshold = gtk_entry_get_text(entryAttentionThreshold);
	alarmThreshold = gtk_entry_get_text(entryAlarmThreshold);
	usbValue = gtk_entry_get_text(entryUsbValue);
	memoryValue = gtk_entry_get_text(entryMemoryValue);
	cpuValue = gtk_entry_get_text(entryCpuValue);
	gracefulValue = gtk_entry_get_text(entryGracefulValue);
	diskUsageValue = gtk_entry_get_text(entryDiskUsageValue);
	criticalProcValue = gtk_entry_get_text(entryCriticalProcValue);
	nonCriticalProcValue = gtk_entry_get_text(entryNonCriticalProcValue);
	antivirusValue = gtk_entry_get_text(entryAntivirusValue);
	firewallValue = gtk_entry_get_text(entryFirewallValue);
	ps2Value = gtk_entry_get_text(entryPs2Value);

	/* Reset fields */
	gtk_entry_set_text(entryHostNodeToEdit, "0");
	gtk_entry_set_text(entryAgentId, "0");
	gtk_entry_set_text(entryName, "0");
	gtk_entry_set_text(entryDescription, "0");
	gtk_entry_set_text(entryDetectorId, "0");
	gtk_entry_set_text(entryRigId, "0");
	gtk_entry_set_text(entryAttentionThreshold, "0");
	gtk_entry_set_text(entryAlarmThreshold, "0");
	gtk_entry_set_text(entryUsbValue, "0");
	gtk_entry_set_text(entryMemoryValue, "0");
	gtk_entry_set_text(entryCpuValue, "0");
	gtk_entry_set_text(entryGracefulValue, "0");
	gtk_entry_set_text(entryDiskUsageValue, "0");
	gtk_entry_set_text(entryCriticalProcValue, "0");
	gtk_entry_set_text(entryNonCriticalProcValue, "0");
	gtk_entry_set_text(entryAntivirusValue, "0");
	gtk_entry_set_text(entryFirewallValue, "0");
	gtk_entry_set_text(entryPs2Value, "0");

	gtk_toggle_button_set_active(checkButtonUsb, FALSE);
	gtk_toggle_button_set_active(checkButtonCpu, FALSE);
	gtk_toggle_button_set_active(checkButtonMemory, FALSE);
	gtk_toggle_button_set_active(checkButtonGraceful, FALSE);

}

/* Create the form of textarea inside */
GtkWidget* createConsoleBox() {
	textArea = gtk_text_view_new();
	GtkWidget* scrolledwindow = gtk_scrolled_window_new(NULL, NULL );
	GtkWidget* textEntry = gtk_entry_new();
	GtkWidget* console = gtk_table_new(3, 1, TRUE);

	gtk_container_add(GTK_CONTAINER(scrolledwindow), textArea);
	gtk_widget_set_size_request(textArea, 500, 500);
	gtk_table_attach_defaults(GTK_TABLE(console), scrolledwindow, 0, 1, 0, 1);

	return console;
}

/*Create check current configuration layout */
void createCheckCurrentConfiguration() {

	GtkLabel * labelCheckConfiguration;
	GtkWidget * buttonCheckConfiguration;

	labelCheckConfiguration = gtk_label_new("Check current configuration");
	gtk_label_set_markup(GTK_LABEL(labelCheckConfiguration),
			"<span foreground=\"blue\" size=\"x-large\">Check current configuration</span>");
	/* place event in grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), labelCheckConfiguration, 0,
			0, 1, 1);

	/* Create text area */
	textareaWidget = createConsoleBox();
	/* place event in grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), textareaWidget, 0, 1, 1,
			1);

	/* Create button check current configuration */
	buttonCheckConfiguration = gtk_button_new_with_label(
			"Check current configuration");
	g_signal_connect_swapped(buttonCheckConfiguration, "clicked",
			G_CALLBACK(checkConfigurationInDB), windowHostConfiguration);
	/* place button in the grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), buttonCheckConfiguration,
			1, 1, 1, 1);

}

/* Create node to edit */
void createNodetoEdit() {
	GtkLabel * labelHostNode;

	/* Create label host node */
	labelHostNode = gtk_label_new("Select host node to edit:");
	/* place event in grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), labelHostNode, 0, 2, 1, 1);
	/* Create and attach entry for host node to edit  */
	entryHostNodeToEdit = gtk_entry_new();
	/* Place entry in the grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), entryHostNodeToEdit, 1, 2,
			2, 1);
	gtk_entry_set_text(entryHostNodeToEdit, "0");

}

/* Create Basic config layout */
void createBasicConfigLayout() {

	GtkLabel * labelBasicConfig;
	GtkLabel * labelAgentId;
	GtkLabel * labelName;
	GtkLabel * labelDescription;
	GtkLabel * labelDetectorId;
	GtkLabel * labelRigId;

	/****************** LABELS AND ENTRY FIELDS FOR BASIC CONFIG ************************/
	/* Create label for basic configuration */
	labelBasicConfig = gtk_label_new("Basic config");
	gtk_label_set_markup(GTK_LABEL(labelBasicConfig),
			"<span foreground=\"blue\" size=\"x-large\">Basic config</span>");
	/* place basic config label in gridHostConfiguration */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), labelBasicConfig, 0, 3, 1,
			1);

	/* Create and attach label Agentid */
	labelAgentId = gtk_label_new("Agent id:");
	/* place gridHostConfiguration label in the grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), labelAgentId, 0, 4, 1, 1);
	/* Create and attach entry agentId */
	entryAgentId = gtk_entry_new();
	/* Place entry in the grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), entryAgentId, 1, 4, 2, 1);
	gtk_entry_set_text(entryAgentId, "0");

	/* Create and attach label Name */
	labelName = gtk_label_new("Name:");
	/* place grid label in the grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), labelName, 0, 6, 1, 1);
	/* Create and attach entry name */
	entryName = gtk_entry_new();
	/* Place entry in the grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), entryName, 1, 6, 2, 1);
	gtk_entry_set_text(entryName, "0");

	/* Create and attach label Detector ID */
	labelDetectorId = gtk_label_new("Detector id:");
	/* place grid label in the grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), labelDetectorId, 0, 7, 1,
			1);
	/* Create and attach entry detector id */
	entryDetectorId = gtk_entry_new();
	/* Place entry in the grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), entryDetectorId, 1, 7, 2,
			1);
	gtk_entry_set_text(entryDetectorId, "0");

	/* Create and attach label description */
	labelDescription = gtk_label_new("Description:");
	/* place grid label in the grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), labelDescription, 0, 8, 1,
			1);
	/* Create and attach entry description */
	entryDescription = gtk_entry_new();
	/* Place entry in the grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), entryDescription, 1, 8, 2,
			1);
	gtk_entry_set_text(entryDescription, "0");

	/* Create and attach label RigId */
	labelRigId = gtk_label_new("Rig id:");
	/* place grid label in the grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), labelRigId, 0, 9, 1, 1);
	/* Create and attach entry rig id */
	entryRigId = gtk_entry_new();
	/* Place entry in the grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), entryRigId, 1, 9, 2, 1);
	gtk_entry_set_text(entryRigId, "0");

}

/* Create Event Policy layout */
void createEventPolicyLayout() {

	GtkLabel * labelEventPolicy;
	GtkLabel * labelAttentionThreshold;
	GtkLabel * labelAlarmThreshold;

	GtkLabel * labelUsbValue;
	GtkLabel * labelMemoryValue;
	GtkLabel * labelCpuValue;
	GtkLabel * labelGracefulValue;
	GtkLabel * labelDiskUsageValue;
	GtkLabel * labelCriticalProcValue;
	GtkLabel * labelNonCriticalProcValue;
	GtkLabel * labelAntivirusValue;
	GtkLabel * labelFirewallValue;
	GtkLabel * labelPs2Value;

	/****************** LABELS AND ENTRY FIELDS FOR EVENT POLICY    ************************/
	labelEventPolicy = gtk_label_new("Event Policy");
	gtk_label_set_markup(GTK_LABEL(labelEventPolicy),
			"<span foreground=\"blue\" size=\"x-large\">Event Policy</span>");
	/* place event policy label in grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), labelEventPolicy, 0, 10, 1,
			1);

	/* Create label attention threshold */
	labelAttentionThreshold = gtk_label_new("Attention Threshold");
	/* place event in grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), labelAttentionThreshold, 0,
			11, 1, 1);
	/* Create and attach entry for attention  */
	entryAttentionThreshold = gtk_entry_new();
	/* Place entry in the grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), entryAttentionThreshold, 1,
			11, 2, 1);
	gtk_entry_set_text(entryAttentionThreshold, "0");

	/* Create label attention Alarm Threshold */
	labelAlarmThreshold = gtk_label_new("Alarm Threshold");
	/* place event in grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), labelAlarmThreshold, 0, 12,
			1, 1);
	/* Create and attach entry for alarm  */
	entryAlarmThreshold = gtk_entry_new();
	/* Place entry in the grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), entryAlarmThreshold, 1, 12,
			2, 1);
	gtk_entry_set_text(entryAlarmThreshold, "0");

	/* Create label attention Usb value */
	labelUsbValue = gtk_label_new("Usb value");
	/* place event in grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), labelUsbValue, 0, 13, 1,
			1);
	/* Create and attach entry for usb value  */
	entryUsbValue = gtk_entry_new();
	/* Place entry in the grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), entryUsbValue, 1, 13, 2,
			1);
	gtk_entry_set_text(entryUsbValue, "0");

	/* Create label attention Memory value */
	labelMemoryValue = gtk_label_new("Memory value");
	/* place event in grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), labelMemoryValue, 0, 14, 1,
			1);
	/* Create and attach entry for memory value  */
	entryMemoryValue = gtk_entry_new();
	/* Place entry in the grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), entryMemoryValue, 1, 14, 2,
			1);
	gtk_entry_set_text(entryMemoryValue, "0");

	/* Create label attention Cpu value */
	labelCpuValue = gtk_label_new("Cpu value");
	/* place event in grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), labelCpuValue, 0, 15, 1,
			1);
	/* Create and attach entry for Cpu value  */
	entryCpuValue = gtk_entry_new();
	/* Place entry in the grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), entryCpuValue, 1, 15, 2,
			1);
	gtk_entry_set_text(entryCpuValue, "0");

	/* Create label attention Grateful value */
	labelGracefulValue = gtk_label_new("Grateful value");
	/* place event in grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), labelGracefulValue, 0, 16,
			1, 1);
	/* Create and attach entry for Grateful value  */
	entryGracefulValue = gtk_entry_new();
	/* Place entry in the grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), entryGracefulValue, 1, 16,
			2, 1);
	gtk_entry_set_text(entryGracefulValue, "0");

	/* Create label attention Disk Usage value */
	labelDiskUsageValue = gtk_label_new("Disk Usage value");
	/* place event in grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), labelDiskUsageValue, 0, 17,
			1, 1);
	/* Create and attach entry for Disk Usage value  */
	entryDiskUsageValue = gtk_entry_new();
	/* Place entry in the grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), entryDiskUsageValue, 1, 17,
			2, 1);
	gtk_entry_set_text(entryDiskUsageValue, "0");

	/* Create label attention Critical proc value */
	labelCriticalProcValue = gtk_label_new("Critical proc");
	/* place event in grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), labelCriticalProcValue, 0,
			18, 1, 1);
	/* Create and attach entry for Critical proc value  */
	entryCriticalProcValue = gtk_entry_new();
	/* Place entry in the grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), entryCriticalProcValue, 1,
			18, 2, 1);
	gtk_entry_set_text(entryCriticalProcValue, "0");

	/* Create label attention Critical proc value */
	labelNonCriticalProcValue = gtk_label_new("Non Critical proc");
	/* place event in grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), labelNonCriticalProcValue,
			0, 19, 1, 1);
	/* Create and attach entry for Critical proc value  */
	entryNonCriticalProcValue = gtk_entry_new();
	/* Place entry in the grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), entryNonCriticalProcValue,
			1, 19, 2, 1);
	gtk_entry_set_text(entryNonCriticalProcValue, "0");

	/* Create label attention Antivirus value */
	labelAntivirusValue = gtk_label_new("Antivirus value");
	/* place event in grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), labelAntivirusValue, 0, 20,
			1, 1);
	/* Create and attach entry for Antivirus value  */
	entryAntivirusValue = gtk_entry_new();
	/* Place entry in the grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), entryAntivirusValue, 1, 20,
			2, 1);
	gtk_entry_set_text(entryAntivirusValue, "0");

	/* Create label attention Firewall value */
	labelFirewallValue = gtk_label_new("Firewall value");
	/* place event in grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), labelFirewallValue, 0, 21,
			1, 1);
	/* Create and attach entry for Firewall value  */
	entryFirewallValue = gtk_entry_new();
	/* Place entry in the grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), entryFirewallValue, 1, 21,
			2, 1);
	gtk_entry_set_text(entryFirewallValue, "0");

	/* Create label attention Ps2 value */
	labelPs2Value = gtk_label_new("Ps2 value");
	/* place event in grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), labelPs2Value, 0, 22, 1,
			1);
	/* Create and attach entry for Ps2 value  */
	entryPs2Value = gtk_entry_new();
	/* Place entry in the grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), entryPs2Value, 1, 22, 2,
			1);
	gtk_entry_set_text(entryPs2Value, "0");

}

/* Create security policy layout */
void createSecurityPolicyLayout() {

	GtkLabel * labelSecurityPolicy;

	GtkLabel * labelSelectIfPermitted;
	GtkLabel * labelUsbEvent;
	GtkLabel * labelCpuEvent;
	GtkLabel * labelMemoryEvent;
	GtkLabel * labelGracefulEvent;

	/****************** LABELS AND ENTRY FIELDS FOR SECURITY POLICY ************************/
	labelSecurityPolicy = gtk_label_new("Security Policy");
	gtk_label_set_markup(GTK_LABEL(labelSecurityPolicy),
			"<span foreground=\"blue\" size=\"x-large\">Security Policy</span>");
	/* place security policy label in grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), labelSecurityPolicy, 0, 23,
			1, 1);

	/* Create label attention usb value */
	labelUsbEvent = gtk_label_new("Usb event");
	/* place event in grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), labelUsbEvent, 0, 24, 1,
			1);
	checkButtonUsb = gtk_check_button_new();
	/* Place entry in the grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), checkButtonUsb, 1, 24, 2,
			1);

	/* Create label attention cpu value */
	labelCpuEvent = gtk_label_new("Cpu event");
	/* place event in grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), labelCpuEvent, 0, 25, 1,
			1);
	checkButtonCpu = gtk_check_button_new();
	/* Place entry in the grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), checkButtonCpu, 1, 25, 2,
			1);

	/* Create label attention memory value */
	labelMemoryEvent = gtk_label_new("Memory event");
	/* place event in grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), labelMemoryEvent, 0, 26, 1,
			1);
	checkButtonMemory = gtk_check_button_new();
	/* Place entry in the grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), checkButtonMemory, 1, 26,
			2, 1);

	/* Create label attention graceful value */
	labelGracefulEvent = gtk_label_new("Graceful event");
	/* place event in grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), labelGracefulEvent, 0, 27,
			1, 1);
	checkButtonGraceful = gtk_check_button_new();
	/* Place entry in the grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration), checkButtonGraceful, 1, 27,
			2, 1);

}

/* create buttons */
void createButtons() {

	GtkWidget * buttonSaveHostConfiguration;
	GtkWidget * buttonDiscardHostConfiguration;

	/****************** BUTTONS ***********************************************************/
	/* Create button send policy */
	buttonSaveHostConfiguration = gtk_button_new_with_label(
			"Saved host configuration");
	g_signal_connect_swapped(buttonSaveHostConfiguration, "clicked",
			G_CALLBACK(saveHostChanges), windowHostConfiguration);
	/* place button in the grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration),
			buttonSaveHostConfiguration, 0, 28, 1, 1);

	/* Create buttonDiscardHostConfiguration discard changes */
	buttonDiscardHostConfiguration = gtk_button_new_with_label("Reset");
	g_signal_connect_swapped(buttonDiscardHostConfiguration, "clicked",
			G_CALLBACK(resetChanges), windowHostConfiguration);
	/* place buttonDiscardHostConfiguration in the grid */
	gtk_grid_attach(GTK_GRID(gridHostConfiguration),
			buttonDiscardHostConfiguration, 1, 28, 1, 1);

}

/* Host Node (SNOK Agent) configuration menu */
void hostNodeConfigurationMenu() {

	/* Create a new windowHostConfiguration */
	windowHostConfiguration = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	/* Set the windowHostConfiguration title */
	gtk_window_set_title(G_OBJECT(windowHostConfiguration),
			"Host Node (SNOK Agent)");
	/* Here we construct the container that is going pack our buttons */
	gridHostConfiguration = gtk_grid_new();
	/* Pack the container in the windowHostConfiguration */
	gtk_container_add(GTK_CONTAINER(windowHostConfiguration),
			gridHostConfiguration);

	/* Create check configuration layout */
	createCheckCurrentConfiguration();

	/* Create node to edit layout */
	createNodetoEdit();

	/* Create basic config layout */
	createBasicConfigLayout();

	/* Create event policy layout */
	createEventPolicyLayout();

	/* Create security policy layout */
	createSecurityPolicyLayout();

	/* Create buttons */
	createButtons();

	/* Now that we are done packing our widgets, we show them all
	 * in one go, by calling gtk_widget_show_all() on the windowHostConfiguration.
	 * This call recursively calls gtk_widget_show() on all widgets
	 * that are contained in the windowHostConfiguration, directly or indirectly.
	 */
	gtk_widget_show_all(windowHostConfiguration);
	gtk_main();

}

