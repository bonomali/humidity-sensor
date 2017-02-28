#!/usr/bin/env python
# -*- coding: utf-8 -*- 

import serial
import datetime
import json
import time
import urllib2

serial_speed = 9600

# Bluetooth shield HC-05
serial_port = '/dev/tty.HC-05-DevB'

class SensorData:

	number = 0
	value = 0
	percentage = None
    
    # This is posting to IFTTT Maker applet.
    # Replace xxxxxxxxx in the URL bellow by
    # your access token.
    
    # Check http://ifttt.com/maker for more information
    
	ifttt_token = 'xxxxxxxxxxxxxxxxxxxx'

	message = ''

	def __init__(self, data):
		self._parse_message(data)

	def _parse_message(self, data):
		self.sensor_number = data.split('|')[0]
		self.value = data.split('|')[1]
		self.percentage = data.split('|')[2]

	def _data_handle(self):
		if int(self.value) < 300:
			self.message = 'Estou morrendo de sede! Me regue por favor! (Sensor: {0} | Umidade: {1}%)'.format(self.sensor_number, self.percentage)
		elif int(self.value) >= 300 and int(self.value) <=700:
			self.message = 'Estou bem por enquanto! (Sensor: {0} | Umidade: {1}%)'.format(self.sensor_number, self.percentage)
		elif int(self.value) > 700:
			self.message = 'Que me matar afogada! Estou cheia de água! (Sensor: {0} | Umidade: {1}%)'.format(self.sensor_number, self.percentage)

	def send_to_twitter(self):
		ts = time.time()
		st = datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d %H:%M:%S')
		self._data_handle()

		data = {'value1': '{0}'.format(self.message)}

		req = urllib2.Request('https://maker.ifttt.com/trigger/humidity_sensor/with/key/{0}'.format(self.ifttt_token))
		req.add_header('Content-Type', 'application/json')

		print "[{0}] Sending data: {1}".format(st, self.message)

		try:
			response = urllib2.urlopen(req, json.dumps(data))
		except Exception as e:
			print "Error on send data to IFTTT [{0}]".format(e.message)


if __name__ == '__main__':
	print "Conectando com sensor ..."
	try:
		ser = serial.Serial(serial_port, serial_speed, timeout=1)
	except Exception as e:
			print "Error on connect to serial [{0}]".format(e.message)

	print "Iniciando recebimento de leituras ..."

	while 1:
		data = ser.readline()

		if (data != ""):

			reading = SensorData(data)
			reading.send_to_twitter()
