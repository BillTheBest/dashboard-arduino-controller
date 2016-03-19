#!/usr/bin/env python

import time
import serial
import subprocess
from browser import BrowserController

# Assign each of the four pad buttons a URL to activate
dashboards = {1: 'http://dashboard.example.com:8000/main', 2: 'http://dashboard.example.com:8000/secondary',
              3: 'http://dashboard.example.com:8000/commute', 4: 'http://dashboard.example.com:8000/misc'}
browser = BrowserController()

last_button = None
last_button_time = None

def on_button_pressed(button_number):
    url = dashboards.get(button_number)
    print("Button %s was pressed!" % button_number)
    print("Navigating to %s" % url)

    browser.navigate_to(url)

    global last_button
    global last_button_time
    last_button = button_number
    last_button_time = time.time()

    time.sleep(0.1)

on_button_pressed(1)

port = '/dev/ttyUSB0'

ser = serial.Serial()
ser.port = port
ser.baudrate = 9600
ser.timeout = 1
ser.open()

try:
    while True:
        line = ser.readline().rstrip()

        print repr(line)

        if line == '' and last_button != 1 and (time.time() - last_button_time) > 300:
            on_button_pressed(1)

        if line == '1': on_button_pressed(1)
        if line == '2': on_button_pressed(2)
        if line == '3': on_button_pressed(3)
        if line == '4': on_button_pressed(4)
        if line == 'M':
            subprocess.call(['xdotool', 'mousemove', '0', '9999'], env={'DISPLAY': ':0'})
            subprocess.call(['xdotool', 'mousemove', '9999', '9999'], env={'DISPLAY': ':0'})
finally:
    ser.close()
