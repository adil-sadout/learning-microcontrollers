//Variables
var humidity= "25%";
var temperature= "47C"


//selecting the temperature & humidity

//temperature
var temp = document.querySelector(".temp p");


//humidity
var humid = document.querySelector(".humid p");



//changing the variable
temp.textContent = temperature;

humid.textContent = humidity;