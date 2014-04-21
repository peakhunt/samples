#!/usr/bin/env python
import pygtk
pygtk.require('2.0')
import gtk

class TextEntry:
   def enter_callback_b(self, widget, entry_b):
      entry_text_b = entry_b.get_text()
      print "Text entry: %s\n" % entry_text_b
      return

   # Main program to draw GUI
   def __init__(self):
      # create a new window
      app_window = gtk.Window(gtk.WINDOW_TOPLEVEL)
      app_window.set_size_request(500, 100)
      app_window.set_border_width(10)
      app_window.set_title("My program title")
      app_window.connect("delete_event", lambda w,e: gtk.main_quit())

      # Set default text in text entry box
      entry_checker_default_b = "abc def default text"

      # Text label
      hbox_b = gtk.HBox(False, 0)
      app_window.add(hbox_b) # attach HBox to window
      label_b = gtk.Label("Enter text: ")
      label_b.show()
      hbox_b.pack_start(label_b, False, False, 0) 

      # Generate text entry box
      entry_b = gtk.Entry()
      entry_b.set_max_length(80)
      entry_b.set_width_chars(50)
      entry_b.connect("changed", self.enter_callback_b, entry_b)
      entry_b.set_text(entry_checker_default_b)
      entry_b.select_region(0, len(entry_b.get_text()))
      entry_b.show()
      hbox_b.pack_start(entry_b, False, False, 0) 

      hbox_b.show()
      app_window.show()
      return

def main():
   gtk.main()
   return 0

if __name__ == "__main__":
   TextEntry()
   main()

