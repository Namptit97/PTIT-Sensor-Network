import paho.mqtt.client as mqtt
import my_lib_sql as ml 
import ast
from datetime import datetime

MQTT_Broker = "localhost"
MQTT_Port   = 1883
Keep_Alive_Interval = 45
MQTT_Topic2 = "temperature"
MQTT_Topic3 = "humidity"

temp = 0

def on_message(client, userdata, msg):
	global SensorID , Date_and_Time, Temperature, Humidity, temp
#	print ("MQTT Connect : "+ msg.topic)
	json_data =  msg.payload
	json_Dict = ast.literal_eval(json_data.decode('utf-8'))
	if ( msg.topic ==  MQTT_Topic2):
		Temperature = json_Dict	
		temp = temp + 1
	elif (msg.topic ==  MQTT_Topic3):
		Humidity = json_Dict
		temp = temp + 1
	else:
		print("incorrect topic")
	if( temp % 2 == 0):
		temp = 0	
		Date_and_Time = datetime.now()
		SensorID = "DHT11"
		print (SensorID , Date_and_Time, Temperature, Humidity)
		ml.insert_table_with_raw_data(SensorID , Date_and_Time, Temperature, Humidity)

def on_connect(client, userdata, flags, rc):
	if rc != 0: #ket noi thanh cong khi rc = 0
		pass
		print("Unable to connect to MQTT Broker...")
	else:
		print("Connected with MQTT Broker: " + str(MQTT_Broker))
	client.subscribe(MQTT_Topic2,0)
	client.subscribe(MQTT_Topic3,0)


ml.create_table()
client = mqtt.Client()
client.username_pw_set(username="huynam",password="huynam")
client.on_connect = on_connect
client.on_message = on_message

client.connect(MQTT_Broker, MQTT_Port, Keep_Alive_Interval)
client.loop_forever()
