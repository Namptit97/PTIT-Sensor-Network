import paho.mqtt.client as mqtt
import random,json
from datetime import datetime
from time import sleep

MQTT_Broker = "localhost"	
MQTT_Port   = 1883 
Keep_Alive_Interval = 45
MQTT_Topic = "home/sensors"

#connect to mqtt server 
def on_connect(client, userdata, rc):
	if rc != 0:
		print ("Unable to connect to MQTT Broker")
	else :
		print("Connected with MQTT Broker: " + str(MQTT_Broker))

def on_publish(client, userdata, mid):
	pass
def on_disconnect(client, userdata, rc):
	if rc != 0:
		pass

mqttc = mqtt.Client()
mqttc.username_pw_set(username="long", password="1")
mqttc.on_connect = on_connect
mqttc.on_disconnect = on_disconnect
mqttc.publish = on_publish
mqttc.connect(MQTT_Broker, MQTT_Port, Keep_Alive_Interval)

def publish_To_Topic(topic, message):
	mqttc.publish(topic,message)
	print(("Published: " + str(message) + " " + "on MQTT Topic: " + str(topic)))
	print("")

#FAKE RANDOM SENSOR
def publish_fake_sensor_values_to_MQTT():
	Humidity_Fake_Value = int(random.uniform(50,100))	
	Temperature_Fake_Value = int(random.uniform(20,30))
	Sensor_data = {}  
	Sensor_data['Sensor_ID'] = "DHT-11"
	Sensor_data['Date'] = "DHT-11"
	Sensor_data['Sensor_ID'] = (datetime.today()).strftime("%d-%m-%Y %H:%M:%S")
	Sensor_data['Temperature'] = Temperature_Fake_Value
	sensor_json_data = json.dumps(Sensor_data)

	print("Publishing fake Sensor Value: ");
	publish_To_Topic(MQTT_Topic,sensor_json_data)
	sleep(3)
	
while True:
	publish_fake_sensor_values_to_MQTT()
	sleep(3)
