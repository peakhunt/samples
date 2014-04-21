#!/usr/bin/env python

import pygtk
pygtk.require('2.0')
import gtk

# Global variables
b_entry_checkbox = True

class Checkbox:
   def entry_checkbox(self, widget, checkbox):
      global b_entry_checkbox
      b_entry_checkbox = checkbox.get_active()
      if b_entry_checkbox:
         print "Box checked"
      else:
         print "Not checked"
      return

   # Main program to draw GUI
   def __init__(self):
      global b_entry_checkbox

      # create a new window
      app_window = gtk.Window(gtk.WINDOW_TOPLEVEL)
      app_window.set_size_request(500, 100)
      app_window.set_border_width(10)
      app_window.set_title("My program title")
      app_window.connect("delete_event", lambda w,e: gtk.main_quit())

      frame_checkbox = gtk.Frame("Check for true:")
      frame_checkbox.set_shadow_type(gtk.SHADOW_IN)

      app_window.add(frame_checkbox)

      check_box = gtk.CheckButton("Checkbox text string")
      check_box.connect("toggled", self.entry_checkbox, check_box)
      check_box.set_active(True)  # Set the defaut
      check_box.show()

      frame_checkbox.add(check_box)
      frame_checkbox.show()
      app_window.show()
      return

def main():
   gtk.main()
   return 0

if __name__ == "__main__":
   Checkbox()
   main()
