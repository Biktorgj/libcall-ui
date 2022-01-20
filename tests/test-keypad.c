/*
 * Copyright (C) 2021 Purism SPC
 *
 * SPDX-License-Identifier: GPL-2.1-or-later
 *
 * based CuiKeypad which is
 * Copyright (C) 2019 Purism SPC
 */

#include <call-ui.h>
#include <glib.h>
#include <glib/gi18n.h>
#include <gtk/gtk.h>

gint notified;


static void
notify_cb (G_GNUC_UNUSED GtkWidget *widget,
           G_GNUC_UNUSED gpointer   data)
{
  notified++;
}


static void
test_cui_keypad_row_spacing (void)
{
  g_autoptr (CuiKeypad) keypad = NULL;
  guint row_spacing = 0;

  keypad = g_object_ref_sink (CUI_KEYPAD (cui_keypad_new (FALSE, TRUE)));

  notified = 0;
  g_signal_connect (keypad, "notify::row-spacing", G_CALLBACK (notify_cb), NULL);

  g_assert_cmpuint (cui_keypad_get_row_spacing (keypad), ==, 6);
  g_object_get (keypad, "row-spacing", &row_spacing, NULL);
  g_assert_cmpuint (row_spacing, ==, 6);

  cui_keypad_set_row_spacing (keypad, 0);
  g_assert_cmpint (notified, ==, 1);

  g_assert_cmpuint (cui_keypad_get_row_spacing (keypad), ==, 0);
  g_object_get (keypad, "row-spacing", &row_spacing, NULL);
  g_assert_cmpuint (row_spacing, ==, 0);

  g_object_set (keypad, "row-spacing", 12, NULL);
  g_assert_cmpint (notified, ==, 2);

  g_assert_cmpuint (cui_keypad_get_row_spacing (keypad), ==, 12);
  g_object_get (keypad, "row-spacing", &row_spacing, NULL);
  g_assert_cmpuint (row_spacing, ==, 12);

  g_assert_cmpint (notified, ==, 2);
}


static void
test_cui_keypad_column_spacing (void)
{
  g_autoptr (CuiKeypad) keypad = NULL;
  guint column_spacing = 0;

  keypad = g_object_ref_sink (CUI_KEYPAD (cui_keypad_new (FALSE, TRUE)));

  notified = 0;
  g_signal_connect (keypad, "notify::column-spacing", G_CALLBACK (notify_cb), NULL);

  g_assert_cmpuint (cui_keypad_get_column_spacing (keypad), ==, 6);
  g_object_get (keypad, "column-spacing", &column_spacing, NULL);
  g_assert_cmpuint (column_spacing, ==, 6);

  cui_keypad_set_column_spacing (keypad, 0);
  g_assert_cmpint (notified, ==, 1);

  g_assert_cmpuint (cui_keypad_get_column_spacing (keypad), ==, 0);
  g_object_get (keypad, "column-spacing", &column_spacing, NULL);
  g_assert_cmpuint (column_spacing, ==, 0);

  g_object_set (keypad, "column-spacing", 12, NULL);
  g_assert_cmpint (notified, ==, 2);

  g_assert_cmpuint (cui_keypad_get_column_spacing (keypad), ==, 12);
  g_object_get (keypad, "column-spacing", &column_spacing, NULL);
  g_assert_cmpuint (column_spacing, ==, 12);

  g_assert_cmpint (notified, ==, 2);
}


static void
test_cui_keypad_letters_visible (void)
{
  g_autoptr (CuiKeypad) keypad = NULL;
  gboolean letters_visible = FALSE;

  keypad = g_object_ref_sink (CUI_KEYPAD (cui_keypad_new (FALSE, TRUE)));

  notified = 0;
  g_signal_connect (keypad, "notify::letters-visible", G_CALLBACK (notify_cb), NULL);

  g_assert_true (cui_keypad_get_letters_visible (keypad));
  g_object_get (keypad, "letters-visible", &letters_visible, NULL);
  g_assert_true (letters_visible);

  cui_keypad_set_letters_visible (keypad, FALSE);
  g_assert_cmpint (notified, ==, 1);

  g_assert_false (cui_keypad_get_letters_visible (keypad));
  g_object_get (keypad, "letters-visible", &letters_visible, NULL);
  g_assert_false (letters_visible);

  g_object_set (keypad, "letters-visible", TRUE, NULL);
  g_assert_cmpint (notified, ==, 2);

  g_assert_true (cui_keypad_get_letters_visible (keypad));
  g_object_get (keypad, "letters-visible", &letters_visible, NULL);
  g_assert_true (letters_visible);

  g_assert_cmpint (notified, ==, 2);
}


static void
test_cui_keypad_symbols_visible (void)
{
  g_autoptr (CuiKeypad) keypad = NULL;
  gboolean symbols_visible = TRUE;

  keypad = g_object_ref_sink (CUI_KEYPAD (cui_keypad_new (FALSE, TRUE)));

  notified = 0;
  g_signal_connect (keypad, "notify::symbols-visible", G_CALLBACK (notify_cb), NULL);

  g_assert_false (cui_keypad_get_symbols_visible (keypad));
  g_object_get (keypad, "symbols-visible", &symbols_visible, NULL);
  g_assert_false (symbols_visible);

  cui_keypad_set_symbols_visible (keypad, TRUE);
  g_assert_cmpint (notified, ==, 1);

  g_assert_true (cui_keypad_get_symbols_visible (keypad));
  g_object_get (keypad, "symbols-visible", &symbols_visible, NULL);
  g_assert_true (symbols_visible);

  g_object_set (keypad, "symbols-visible", FALSE, NULL);
  g_assert_cmpint (notified, ==, 2);

  g_assert_false (cui_keypad_get_symbols_visible (keypad));
  g_object_get (keypad, "symbols-visible", &symbols_visible, NULL);
  g_assert_false (symbols_visible);

  g_assert_cmpint (notified, ==, 2);
}


static void
test_cui_keypad_entry (void)
{
  g_autoptr (CuiKeypad) keypad = NULL;
  g_autoptr (GtkEntry) entry = NULL;

  keypad = g_object_ref_sink (CUI_KEYPAD (cui_keypad_new (FALSE, TRUE)));
  entry = g_object_ref_sink (GTK_ENTRY (gtk_entry_new ()));

  notified = 0;
  g_signal_connect (keypad, "notify::entry", G_CALLBACK (notify_cb), NULL);

  g_assert_null (cui_keypad_get_entry (keypad));

  cui_keypad_set_entry (keypad, entry);
  g_assert_cmpint (notified, ==, 1);

  g_assert_true (cui_keypad_get_entry (keypad) == entry);

  g_object_set (keypad, "entry", NULL, NULL);
  g_assert_cmpint (notified, ==, 2);

  g_assert_null (cui_keypad_get_entry (keypad));
}


static void
test_cui_keypad_start_action (void)
{
  g_autoptr (CuiKeypad) keypad = NULL;
  g_autoptr (GtkWidget) button = NULL;

  keypad = g_object_ref_sink (CUI_KEYPAD (cui_keypad_new (FALSE, TRUE)));
  button = g_object_ref_sink (gtk_button_new ());

  notified = 0;
  g_signal_connect (keypad, "notify::start-action", G_CALLBACK (notify_cb), NULL);

  g_assert_nonnull (cui_keypad_get_start_action (keypad));

  cui_keypad_set_start_action (keypad, button);
  g_assert_cmpint (notified, ==, 1);

  g_assert_true (cui_keypad_get_start_action (keypad) == button);

  g_object_set (keypad, "start-action", NULL, NULL);
  g_assert_cmpint (notified, ==, 2);

  g_assert_null (cui_keypad_get_start_action (keypad));
}


static void
test_cui_keypad_end_action (void)
{
  g_autoptr (CuiKeypad) keypad = NULL;
  g_autoptr (GtkWidget) button = NULL;

  keypad = g_object_ref_sink (CUI_KEYPAD (cui_keypad_new (FALSE, TRUE)));
  button = g_object_ref_sink (gtk_button_new ());

  notified = 0;
  g_signal_connect (keypad, "notify::end-action", G_CALLBACK (notify_cb), NULL);

  g_assert_nonnull (cui_keypad_get_end_action (keypad));

  cui_keypad_set_end_action (keypad, button);
  g_assert_cmpint (notified, ==, 1);

  g_assert_true (cui_keypad_get_end_action (keypad) == button);

  g_object_set (keypad, "end-action", NULL, NULL);
  g_assert_cmpint (notified, ==, 2);

  g_assert_null (cui_keypad_get_end_action (keypad));
}



gint
main (gint argc,
      gchar *argv[])
{
  gtk_test_init (&argc, &argv, NULL);
  cui_init (FALSE);

  g_test_add_func ("/CallUI/Keypad/row_spacing", test_cui_keypad_row_spacing);
  g_test_add_func ("/CallUI/Keypad/column_spacing", test_cui_keypad_column_spacing);
  g_test_add_func ("/CallUI/Keypad/letters_visible", test_cui_keypad_letters_visible);
  g_test_add_func ("/CallUI/Keypad/symbols_visible", test_cui_keypad_symbols_visible);
  g_test_add_func ("/CallUI/Keypad/entry", test_cui_keypad_entry);
  g_test_add_func ("/CallUI/Keypad/start_action", test_cui_keypad_start_action);
  g_test_add_func ("/CallUI/Keypad/end_action", test_cui_keypad_end_action);

  return g_test_run ();
}
