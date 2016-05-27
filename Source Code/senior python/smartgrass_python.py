__author__ = 'Succcess'
import serial
import time
import urllib2
import urllib
import sys
import json
import requests
import demjson

ser = serial.Serial('/dev/ttyACM0', 9600, timeout=0)

soil=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
state=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]

while 1:

	ser.write('S')
	time.sleep(1)
     sensor=ser.readline()
	print ("Updated sensor ")
	print sensor
	sensor_st=str(sensor)
	parse_sensor=sensor_st.split(":")
	temperature=parse_sensor[1]
	rain=parse_sensor[0]
	soil1=parse_sensor[2]
	soil2=parse_sensor[3]
	soil3=parse_sensor[4]
	status=1
	sensor={"SoilReadings": [{"SensorNumber": 1,"SoilMoisture": soil1}, {"SensorNumber": 2,"SoilMoisture": soil2},{"SensorNumber": 3,"SoilMoisture": soil3}],"ProductKey": "1234","Temperature": temperature,"Rain": rain}
	sensor_value=demjson.encode(sensor)
	encode=json.loads(sensor_value)

	try:
		req = urllib2.Request('http://smartgrass.azurewebsites.net/api/Sensors')
		req.add_header('Content-Type', 'application/json')
		response = urllib2.urlopen(req, json.dumps(encode)).read()
		print "Received response"

		data2= demjson.decode(response)

		print data2
		data4=json.loads(data2)
		
	
		for i in range(0,3):
			if (int(data4[str(i)])!=state[i]):
				state[i]=int(data4[str(i)])
				
				#print data4[str(i)]
				ser.write(chr(48+i))
				time.sleep(1)
	except: print("API call error")
   
	


