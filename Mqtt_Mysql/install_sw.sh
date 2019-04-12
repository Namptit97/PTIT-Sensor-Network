#! /bin/bash

sudo apt-get update 

echo "install mosquitto client" 
sudo apt install mosquitto mosquitto-clients

echo "test subcribe topic"
mosquitto_sub -h localhost -t test

echo "test publish topic"
mosquitto_pub -h localhost -t test -m "hello world"

echo "Create file config with : sudo vi  /etc/mosquitto/conf.d/default.conf"




