#!/usr/bin/env python
import pygtk
pygtk.require('2.0')
import gtk
07
class MyProgram:
   def __init__(self):
      # create a new window
      app_window = gtk.Window(gtk.WINDOW_TOPLEVEL)
      app_window.set_size_request(500, 350)
      app_window.set_border_width(10)
      app_window.set_title("MyProgram title")
      app_window.connect("delete_event", lambda w,e: gtk.main_quit())

      vbox_app = gtk.VBox(False, 0)
      app_window.add(vbox_app)
      vbox_app.show()

      label_app = gtk.Label("Application name: ")
      label_app.show()
      vbox_app.pack_start(label_app, False, False, 6)

      # Draw Table() to layout text:
      table_layout = gtk.Table(rows=2, columns=2, homogeneous=True)
      label_a = gtk.Label("AAA")
      label_a.show()
      table_layout.attach(label_a, 0, 1, 0, 1, 0,0,0,0)
      label_b = gtk.Label("BBB")
      label_b.show()
      table_layout.attach(label_b, 0, 1, 1, 2, 0,0,0,0)
      label_c = gtk.Label("CCC")
      label_c.show()
      table_layout.attach(label_c, 1, 2, 0, 1, 0,0,0,0)
      label_d = gtk.Label("DDD")
      label_d.show()
      table_layout.attach(label_d, 1, 2, 1, 2, 0,0,0,0)
      table_layout.show()
      vbox_app.add(table_layout)

      # Use HBox() to layout text and button next to each other:
      hbox_close = gtk.HBox(False, 0)
      label_close = gtk.Label("Close aplication: ")
      hbox_close.pack_start(label_close, True, True, 0)
      label_close.show()

      button_close = gtk.Button(stock=gtk.STOCK_CLOSE)
      button_close.connect("clicked", lambda w: gtk.main_quit())
      button_close.set_flags(gtk.CAN_DEFAULT)
      hbox_close.pack_start(button_close, True, True, 0)
      button_close.show()

      hbox_close.show()
      vbox_app.add(hbox_close)
 
      # Place after association to hbox/vbox to avoid the following error:
      # GtkWarning: gtkwidget.c:5460: widget not within a GtkWindow
      button_close.grab_default()
      app_window.show()
      return

def main():
   gtk.main()
   return 0

if __name__ == "__main__":
   MyProgram()
   main()
