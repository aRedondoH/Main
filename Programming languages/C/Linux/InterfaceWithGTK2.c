#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

GtkWidget * entryUsb;
GtkWidget * entryAntivirus;
GtkWidget * entryFirewall;
GtkWidget * entryKeyboardAndMouse;
GtkWidget * entryAutomaticSoftwareUpdate;

typedef struct {
	GSList *windows;

/* etc... whatever application vars you need */
} MyApp;

void print_setup_agents(GtkWidget *widget, MyApp *app) {
	g_print("The agents has been created\n");
	printf("Hi");

}

void sendNewEventPolicy(GtkWidget *widget, MyApp *app) {
	g_print("Event policy sent\n");
	char * usbPolicy;
	char * antivirusPolicy;
	char * firewallPolicy;
	char * keyboardAndMousePolicy;
	char * automaticSoftwareUpdate;

	usbPolicy = gtk_entry_get_text(entryUsb);
	antivirusPolicy = gtk_entry_get_text(entryAntivirus);
	firewallPolicy = gtk_entry_get_text(entryFirewall);
	keyboardAndMousePolicy = gtk_entry_get_text(entryKeyboardAndMouse);
	automaticSoftwareUpdate = gtk_entry_get_text(entryAutomaticSoftwareUpdate);

	int usbPolicyInt= atoi(usbPolicy);
	int antivirusPolicyInt= atoi(antivirusPolicy);
	int firewallPolicyInt= atoi(firewallPolicy);
	int keyboardAndMousePolicyInt= atoi(keyboardAndMousePolicy);
	int automaticSoftwareUpdateInt= atoi(automaticSoftwareUpdate);

	printf("USB contains: %d\n", usbPolicyInt);
	printf("Antivirus contains: %d\n", antivirusPolicyInt);
	printf("Firewall contains %d\n", firewallPolicyInt);
	printf("Keyboard and mouse contains %d\n", keyboardAndMousePolicyInt);
	printf("Automatic software update constains %d\n", automaticSoftwareUpdateInt);
}

void on_window_destroy(GtkWidget *widget, MyApp *app) {
	app->windows = g_slist_remove(app->windows, widget);
	if (g_slist_length(app->windows) == 0) {
		/* last window was closed... exit */
		g_debug("Exiting...");
		g_slist_free(app->windows);
		gtk_main_quit();
	}
}

void securityPolicyWindow(GtkWidget *widget, MyApp *app) {
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget *button;
	GtkWidget *button_box;

	GtkWidget *entry1;
	gchar *title;

	/* add window to list */
	app->windows = g_slist_prepend(app->windows, window);

	/* setup window and pack a button into it */
	gtk_container_set_border_width(GTK_CONTAINER(window), 200);
	gtk_container_add(GTK_CONTAINER(window), button);
	title = g_strdup_printf("Security Policy Management",
			g_slist_length(app->windows));

	/* set window title */
	gtk_window_set_title(GTK_WINDOW(window), title);
	g_free(title);

	/* create a button container */
	button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_container_add(GTK_CONTAINER(window), button_box);
	button = gtk_button_new_with_label("Send agent policy configuration");

	/* Create entry 1 */
	entry1 = gtk_entry_new();

	//add the entry to the window.
	gtk_container_add(GTK_CONTAINER(window), entry1);

	/* connect callbacks to signals */
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(on_window_destroy),
			app);

	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(print_setup_agents), app);

	// add cointainer to the windows
	gtk_container_add(GTK_CONTAINER(button_box), button);

	// show window
	gtk_widget_show_all(window);
}

void setup_agent_window(GtkWidget *widget, MyApp *app) {
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget *button;
	GtkWidget *button_box;

	gchar *title;

	/* add window to list */
	app->windows = g_slist_prepend(app->windows, window);

	/* setup window and pack a button into it */
	gtk_container_set_border_width(GTK_CONTAINER(window), 200);
	gtk_container_add(GTK_CONTAINER(window), button);
	title = g_strdup_printf("Setup Agents", g_slist_length(app->windows));

	/* create a button container */
	button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_container_add(GTK_CONTAINER(window), button_box);
	button = gtk_button_new_with_label("Setup Agents");

	/* set window title */
	gtk_window_set_title(GTK_WINDOW(window), title);
	g_free(title);

	/* connect callbacks to signals */
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(on_window_destroy),
			app);

	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(print_setup_agents), app);

	// add cointainer to the windows
	gtk_container_add(GTK_CONTAINER(button_box), button);

	// show window
	gtk_widget_show_all(window);
}

void menu_installer(GtkWidget *widget, MyApp *app) {

	GtkWidget *window;
	GtkWidget *button;
	GtkWidget *table;
	GtkWidget *entry1;

	/* Create a new window */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	/* Set the window title */
	gtk_window_set_title(G_OBJECT(window), "Table");

	/* Set a handler for delete_event that immediately
	 * exits GTK. */
	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(on_window_destroy), NULL);
	/* Sets the border width of the window. */
	gtk_container_set_border_width(GTK_CONTAINER(window), 20);

	/* Create a 2x2 table */
	table = gtk_table_new(2, 2, TRUE);
	/* Put the table in the main window */
	gtk_container_add(G_OBJECT(window), table);

	/* Create first button */
	button = gtk_button_new_with_label("Set up Agents");

	/* When the button is clicked, we call the "callback" function
	 * with a pointer to "button 1" as its argument */
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(setup_agent_window), app);

	/* Insert button 1 into the upper left quadrant of the table */
	//gtk_table_attach_defaults(GTK_TABLE(table), button, 0, 1, 0, 1);
	gtk_table_attach(GTK_TABLE(table), button, 0, 1, 0, 1,
			GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND | GTK_SHRINK, 0, 0);

	gtk_widget_show(button);

	/* Create second button */
	button = gtk_button_new_with_label("SP Management");
	/* When the button is clicked, we call the "callback" function
	 * with a pointer to "button 2" as its argument */
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(securityPolicyWindow), app);

	/* Insert button 2 into the upper right quadrant of the table */
	//gtk_table_attach_defaults(GTK_TABLE(table), button, 1, 2, 0, 1);
	gtk_table_attach(GTK_TABLE(table), button, 0, 2, 0, 1,
			GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND | GTK_SHRINK, 0, 0);

	gtk_widget_show(button);

	/* Create "Quit" button */
	button = gtk_button_new_with_label("Quit");

	/* When the button is clicked, we call the "delete_event" function
	 * and the program exits */
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_window_destroy),
			app);
	/* Insert the quit button into the both
	 * lower quadrants of the table */
	//gtk_table_attach_defaults(GTK_TABLE(table), button, 0, 2, 1, 2);
	/* Create entry field */
	entry1 = gtk_entry_new();
	//gtk_table_attach_defaults(GTK_TABLE(table), entry1, 0, 2, 1, 2);
	gtk_table_attach(GTK_TABLE(table), entry1, 0, 2, 0, 2,
			GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND | GTK_SHRINK, 0, 0);

	gtk_widget_show(entry1);
	gtk_widget_show(button);
	gtk_widget_show(table);
	gtk_widget_show(window);

	gtk_main();

}

void menuInstallerGrid(GtkWidget *widget, MyApp *app) {

	GtkWidget * window;
	GtkWidget * grid;
	GtkWidget * button;

	GtkLabel * labelUsb;
	GtkLabel * labelAntivirus;
	GtkLabel * labelFirewall;
	GtkLabel * labelKeyboardAndMouse;
	GtkLabel * labelAutomaticSoftwareUpdate;

	/* Create a new window */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	/* Set the window title */
	gtk_window_set_title(G_OBJECT(window), "Security Policy Management");

	/* Here we construct the container that is going pack our buttons */
	grid = gtk_grid_new();

	/* Pack the container in the window */
	gtk_container_add(GTK_CONTAINER(window), grid);

	/* Create and attach label Usb */
	labelUsb = gtk_label_new("Usb");
	/* place grid label in the grid */
	gtk_grid_attach(GTK_GRID(grid), labelUsb, 0, 0, 1, 1);

	/* Create and attach label Antivirus */
	labelAntivirus = gtk_label_new("Antivirus");
	/* place grid label in the grid */
	gtk_grid_attach(GTK_GRID(grid), labelAntivirus, 0, 1, 1, 1);

	/* Create and attach label Firewall */
	labelFirewall = gtk_label_new("Firewall");
	/* place grid label in the grid */
	gtk_grid_attach(GTK_GRID(grid), labelFirewall, 0, 2, 1, 1);

	/* Create and attach label Usb */
	labelKeyboardAndMouse = gtk_label_new("Keyboard and Mouse");
	/* place grid label in the grid */
	gtk_grid_attach(GTK_GRID(grid), labelKeyboardAndMouse, 0, 3, 1, 1);

	/* Create and attach label Automatic Software Update */
	labelAutomaticSoftwareUpdate = gtk_label_new("Automatic Software update");
	/* place grid label in the grid */
	gtk_grid_attach(GTK_GRID(grid), labelAutomaticSoftwareUpdate, 0, 4, 1, 1);

	/* Create and attach entry usb */
	entryUsb = gtk_entry_new();
	/* Place entry in the grid */
	gtk_grid_attach(GTK_GRID(grid), entryUsb, 1, 0, 2, 1);
	gtk_entry_set_text(entryUsb, "0");

	/* Create and attach entry antivirus */
	entryAntivirus = gtk_entry_new();
	/* Place entry in the grid */
	gtk_grid_attach(GTK_GRID(grid), entryAntivirus, 1, 1, 2, 1);
	gtk_entry_set_text(entryAntivirus, "0");

	/* Create and attach entry firewall */
	entryFirewall = gtk_entry_new();
	/* Place entry in the grid */
	gtk_grid_attach(GTK_GRID(grid), entryFirewall, 1, 2, 2, 1);
	gtk_entry_set_text(entryFirewall, "0");

	/* Create and attach entry keyboard and mouse */
	entryKeyboardAndMouse = gtk_entry_new();
	/* Place entry in the grid */
	gtk_grid_attach(GTK_GRID(grid), entryKeyboardAndMouse, 1, 3, 2, 1);
	gtk_entry_set_text(entryKeyboardAndMouse, "0");

	/* Create and attach entry automatic software update */
	entryAutomaticSoftwareUpdate = gtk_entry_new();
	/* Place entry in the grid */
	gtk_grid_attach(GTK_GRID(grid), entryAutomaticSoftwareUpdate, 1, 4, 2, 1);
	gtk_entry_set_text(entryAutomaticSoftwareUpdate, "0");

	/* Create button send policy */
	button = gtk_button_new_with_label("Send agent SP");
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(sendNewEventPolicy),
			window);
	/* place button in the grid */
	gtk_grid_attach(GTK_GRID(grid), button, 0, 5, 1, 1);

	/* Now that we are done packing our widgets, we show them all
	 * in one go, by calling gtk_widget_show_all() on the window.
	 * This call recursively calls gtk_widget_show() on all widgets
	 * that are contained in the window, directly or indirectly.
	 */

	const gchar test1;

	//g_print("The value on entryUsb is:  \n", test1);

	gtk_widget_show_all(window);
	gtk_main();

}

int main(int argc, char *argv[]) {

	MyApp *app;

	gtk_init(&argc, &argv);
	app = g_slice_new(MyApp);
	app->windows = NULL;

	/* create first window menu */
	menuInstallerGrid(NULL, app);

	gtk_main();
	g_slice_free(MyApp, app);

	return 0;
}
