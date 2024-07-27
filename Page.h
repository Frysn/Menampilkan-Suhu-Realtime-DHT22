const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>ESP32 DHT22</title>
    <script>
        setInterval(() => {
            fetch('/data')
                .then(response => response.json())
                .then(data => {
                    document.getElementById('temperature').innerText = data.temperature;
                    document.getElementById('humidity').innerText = data.humidity;
                });
        }, 500);
    </script>
</head>
<body>
    <h1>Data DHT22</h1>
    <p>Temperature: <span id="temperature"></span>°C</p>
    <p>Humidity: <span id="humidity"></span>%</p>
</body>
</html>
)rawliteral";