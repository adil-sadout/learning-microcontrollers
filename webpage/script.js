//Variables
var humidity= "25%"; //the value should be a variable that stores the output of a sensor
var temperature= "47C" //the value should be a variable that stores the output of a sensor


//selecting the temperature & humidity

//temperature
var temp = document.querySelector(".temp p");


//humidity
var humid = document.querySelector(".humid p");



//changing the variable
temp.textContent = temperature;

humid.textContent = humidity;