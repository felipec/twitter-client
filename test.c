#include <twitter-glib/twitter-glib.h>

GMainLoop *loop;

static void
status_received (TwitterClient *client,
                 gulong handle,
                 TwitterStatus *status,
                 GError *error,
                 gpointer *data)
{
    if (error)
    {
        g_critical ("failed");
        g_main_loop_quit (loop);
        return;
    }

    g_message ("message posted");
    g_main_loop_quit (loop);
}

int
main (int argc,
      char *argv[])
{
    TwitterClient *client;

    if (argc < 3)
        g_error ("usage: %s user password message", argv[0]);

    g_type_init ();
    if (!g_thread_supported ())
        g_thread_init (NULL);
    loop = g_main_loop_new (NULL, FALSE);

    client = twitter_client_new_for_user (argv[1], argv[2]);
    g_signal_connect (client, "status-received", G_CALLBACK (status_received), NULL);
    twitter_client_verify_user (client);
    twitter_client_add_status (client, argv[3]);

    g_main_loop_run (loop);

    g_main_loop_unref (loop);
}
