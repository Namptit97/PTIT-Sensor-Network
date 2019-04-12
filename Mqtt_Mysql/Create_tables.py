import pymysql as pl
import json

sql_create_table = """CREATE TABLE sensors(
		id INT(10) PRIMARY KEY  auto_increment , 
		Sensor_ID int(3) not null, 
		Date datetime not null, 
		Temperature int(3) not null,
		Humidity int(3) not null
		)
	  """

db = pl.connect("localhost", "root", "1" , "WSN")
cursor = db.cursor()

def create_table():

	
	cursor.execute("DROP TABLE IF EXISTS sensors" )
	cursor.execute(sql_create_table)

	db.close()


	
create_table()

