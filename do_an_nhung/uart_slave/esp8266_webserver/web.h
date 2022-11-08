 const char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>

<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">

<script src="https://code.highcharts.com/highcharts.js"></script>
  <style>
    body {
      min-width: 310px;
     max-width: 1280px;
      height: 500px;
      margin: 0 auto;
    }
    h2 {
      font-family: Arial;
      font-size: 2.5rem;
      text-align: center;
    }
  </style>
</head>

<script>
function UpdateData()
{
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function ()
    {
        if (this.readyState == 4 && this.status == 200)
        {
            var DataVDK =  xhttp.responseText ;
            console.log("Dữ liệu VDK :" + DataVDK);

            var DataJson = JSON.parse(DataVDK);
           
  

        if(DataJson.ND1 != null)
            {
              document.getElementById("nhietdo1").innerHTML = DataJson.ND1 ;
            }
        if(DataJson.ND2 != null)
            {
              document.getElementById("nhietdo2").innerHTML = DataJson.ND2 ;
            }
        if(DataJson.DA != null)
            {
              if(DataJson.DA == 1)
               {

                 document.getElementById("TB1").innerHTML = "ON" ;
            
               }
              else if( DataJson.DA == 0)
               {
                 document.getElementById("TB1").innerHTML = "OFF" ;
               }

            
            }

            
        }
    }
    xhttp.open('GET','/Update',true);
    xhttp.send();


    setTimeout(function(){UpdateData()}, 1000);
    
}
function GetButtonData(data)
{
    switch (data)
    {
    case 1:
      console.log("Button thiet bi : ONCLICK");
      var thietbi1 = document.getElementById("TB1").innerHTML;
      console.log(thietbi1);
      
      if(thietbi1 == "ON")
      {
        var tx = "A0B";
        var xhttp = new XMLHttpRequest();
        xhttp.open("GET","/Button?Button="+tx,true);
        xhttp.send();
      }
      else if(thietbi1 == "OFF")
      {
        var tx = "A1B";
        var xhttp = new XMLHttpRequest();
        xhttp.open("GET","/Button?Button="+tx,true);
        xhttp.send();
      }
      
      //var xhttp = new XMLHttpRequest();
      //xhttp.open('GET','/Update',true);
      //xhttp.send();
      break;
      case 2:
      break;
      case 3:
      break;
    
    }
    
}
</script>
<body  onload="UpdateData()">
    
</body>
<body>
    <h2>ESP Weather Station</h2>
    <div id="chart-temperature" class="container"></div>
    <div id="chart-humidity" class="container"></div>
    <div id="chart-pressure" class="container"></div>
<script>

var value1 = DataJson.ND1 ;
var value2 = DataJson.ND2 ;
var value3 = DataJson.ND2 ;
var reading_time = 
//<?php echo $value1; ?>;
var chartT = new Highcharts.Chart({
  chart:{ renderTo : 'chart-temperature' },
  title: { text: 'BME280 Temperature' },
  series: [{
    showInLegend: false,
    data: value1
  }],
  plotOptions: {
    line: { animation: false,
      dataLabels: { enabled: true }
    },
    series: { color: '#059e8a' }
  },
  xAxis: { 
    type: 'datetime',
    categories: reading_time
  },
  yAxis: {
    title: { text: 'Temperature (Celsius)' }
    //title: { text: 'Temperature (Fahrenheit)' }
  },
  credits: { enabled: false }
});

var chartH = new Highcharts.Chart({
  chart:{ renderTo:'chart-humidity' },
  title: { text: 'BME280 Humidity' },
  series: [{
    showInLegend: false,
    data: value2
  }],
  plotOptions: {
    line: { animation: false,
      dataLabels: { enabled: true }
    }
  },
  xAxis: {
    type: 'datetime',
    //dateTimeLabelFormats: { second: '%H:%M:%S' },
    categories: reading_time
  },
  yAxis: {
    title: { text: 'Humidity (%)' }
  },
  credits: { enabled: false }
});


var chartP = new Highcharts.Chart({
  chart:{ renderTo:'chart-pressure' },
  title: { text: 'BME280 Pressure' },
  series: [{
    showInLegend: false,
    data: value3
  }],
  plotOptions: {
    line: { animation: false,
      dataLabels: { enabled: true }
    },
    series: { color: '#18009c' }
  },
  xAxis: {
    type: 'datetime',
    categories: reading_time
  },
  yAxis: {
    title: { text: 'Pressure (hPa)' }
  },
  credits: { enabled: false }
});

</script>
</body>
<h1>
Nhiệt độ 1
<label id="nhietdo1">21</label>
</h1>

<h1>
Nhiệt độ 2
<label id="nhietdo2">21</label>
</h1>

<h1>
Trạng thái thiết bị điều khiển 1
<label id="TB1">OFF</label>
</h1>
<br>
<br>
<br>
<button onclick = "GetButtonData(1)" >THIẾT BỊ 1 
  </button>

</html>




)=====";
