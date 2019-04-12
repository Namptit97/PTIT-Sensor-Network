const express = require('express')
const app = express()
app.set('view engine', 'html');
app.set('views', __dirname ) 
app.engine('html', require('ejs').renderFile);
var jsonArray = [];
var name = [];
var temp = [];
var hum = [];

sql = require('mysql');

var con = sql.createConnection({
  host: "localhost",
  user: "root",
  password: "huynam",
  database: "thcsb3"
});

app.use((request, response, next) => {
  console.log(request.headers)
  next()

app.use((request, response, next) => {
  request.chance = Math.random()
  next()
})

app.get('/', (request, response) => {
  var name = 'hello 99999';

	    //Select all customers and return the result object:
		  con.query("SELECT * FROM sensors", function (err, result, fields) {
		  if (err) throw err;
  		  response.render( "./charjs_test.html", {name:JSON.stringify(result)});
		  console.log(JSON.stringify(result));
				  
		});
})

app.listen(3000)
console.log("localhost:3000");

