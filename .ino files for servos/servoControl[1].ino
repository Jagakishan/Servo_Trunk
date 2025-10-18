#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <Servo.h>
ESP8266WebServer server(80);
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
#define SERVO1_PIN D1
#define SERVO2_PIN D2
#define SERVO3_PIN D3
#define SERVO4_PIN D4
#define SERVO5_PIN D5
#define SERVO6_PIN D6
int prevAngle1 = 0;
int prevAngle2 = 90;
int prevAngle3 = 90;

void setup() {
  Serial.begin(115200);
  servo1.attach(SERVO1_PIN,500,2500);
  servo2.attach(SERVO2_PIN,500,2500);
  servo3.attach(SERVO3_PIN,500,2500);
  servo4.attach(SERVO4_PIN,500,2500);
  servo5.attach(SERVO5_PIN,500,2500);
  servo6.attach(SERVO6_PIN,500,2500);
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(90);
  servo5.write(90);
  servo6.write(90);
 WiFi.softAP("Elephant_trunk", "12345678");
Serial.println("Access Point started");
Serial.println(WiFi.softAPIP());
  server.on("/", HTTP_GET, handleRoot);
  server.on("/rotateServo", HTTP_POST, handleRotateServo);
  server.begin();
  Serial.print("Server IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String html = R"rawliteral(<!DOCTYPE html>
<html>
<head>
    <title>Elephant Trunk</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            text-align: center;
            background-color: #f4f4f4;
            margin: 0;
            padding: 20px;
        }

        h1 {
            color: #333;
        }

        .servo-container, .Delay {
            background-color: #fff;
            border-radius: 10px;
            padding: 30px;
            margin: 20px auto;
            width: 400px;
            box-shadow: 0 2px 5px rgba(0,0,0,0.2);
        }

        .button-group {
            display: flex;
            justify-content: space-around;
            margin-top: 15px;
            flex-wrap: wrap;
        }

        button {
            padding: 10px 15px;
            border: none;
            border-radius: 5px;
            background-color: #0c160c;
            color: white;
            font-size: 16px;
            cursor: pointer;
            transition: background-color 0.3s;
            margin: 5px;
        }

        button:hover {
            background-color: #343a35;
        }
        
        .queue-display {
            background: #e9ecef;
            padding: 15px;
            border-radius: 5px;
            margin: 10px auto;
            width: 350px;
            min-height: 50px;
            text-align: left;
        }
        
        .queue-item {
            padding: 8px 12px;
            margin: 5px 0;
            background: white;
            border-radius: 4px;
            border-left: 4px solid #0c160c;
            display: flex;
            justify-content: space-between;
            align-items: center;
        }
        
        .queue-item.delay {
            border-left-color: #17a2b8;
        }
        
        .queue-item.executing {
            background: #d4edda;
            border-left-color: #28a745;
            font-weight: bold;
        }
        
        .queue-item-number {
            background: #6c757d;
            color: white;
            border-radius: 50%;
            width: 25px;
            height: 25px;
            display: flex;
            align-items: center;
            justify-content: center;
            font-size: 14px;
            margin-right: 10px;
        }
        
        .queue-item-content {
            flex-grow: 1;
        }
        
        .remove-btn {
            background: #dc3545;
            color: white;
            border: none;
            border-radius: 3px;
            padding: 3px 8px;
            cursor: pointer;
            font-size: 12px;
        }
        
        .remove-btn:hover {
            background: #c82333;
        }
        
        .custom-angle {
            margin-top: 15px;
            padding: 10px;
            border-top: 1px solid #eee;
        }
        
        input[type="number"] {
            padding: 8px;
            width: 80px;
            margin: 0 5px;
            border: 1px solid #ddd;
            border-radius: 4px;
        }
        
        .empty-queue {
            text-align: center;
            color: #6c757d;
            font-style: italic;
            padding: 10px;
        }
    </style>
</head>
<body>

    <div class="servo-container">
        <h1>Servo 1</h1>
        <div class="button-group">
            <button onclick="addServo('servo1',0)">0°</button>
            <button onclick="addServo('servo1',90)">90°</button>
            <button onclick="addServo('servo1',180)">180°</button>
        </div>
        <div class="custom-angle">
            <h3>Custom Angle</h3>
            <input type="number" id="servo1Angle" min="0" max="180" placeholder="0-180">
            <button onclick="setCustomAngle('servo1')">Set Angle</button>
        </div>
    </div>

    <div class="servo-container">
        <h1>Servo 2</h1>
        <div class="button-group">
            <button onclick="addServo('servo2',0)">0°</button>
            <button onclick="addServo('servo2',90)">90°</button>
            <button onclick="addServo('servo2',180)">180°</button>
        </div>
        <div class="custom-angle">
            <h3>Custom Angle</h3>
            <input type="number" id="servo2Angle" min="0" max="180" placeholder="0-180">
            <button onclick="setCustomAngle('servo2')">Set Angle</button>
        </div>
    </div>

    <div class="servo-container">
        <h1>Servo 3</h1>
        <div class="button-group">
            <button onclick="addServo('servo3',0)">0°</button>
            <button onclick="addServo('servo3',90)">90°</button>
            <button onclick="addServo('servo3',180)">180°</button>
        </div>
        <div class="custom-angle">
            <h3>Custom Angle</h3>
            <input type="number" id="servo3Angle" min="0" max="180" placeholder="0-180">
            <button onclick="setCustomAngle('servo3')">Set Angle</button>
        </div>
    </div>

    </div>
         <div class="custom-angle">
            <h3>Custom Angle</h3>
            <input type="number" id="servo6Angle" min="0" max="180" placeholder="0-180">
            <button onclick="setCustomAngle('servo6')">Set Angle</button>
        </div>
    </div>
    
    <div class="Delay">
        <h1>Add Delays</h1>
        <div class="button-group">
            <button onclick="addDelay(500)">500ms</button>
            <button onclick="addDelay(1000)">1s</button>
            <button onclick="addDelay(2000)">2s</button>
        </div>
        <div class="custom-angle">
            <h3>Custom Delay</h3>
            <input type="number" id="customDelay" min="100" max="10000" value="1000" step="100">
            <span>ms</span>
            <button onclick="addCustomDelay()">Add Delay</button>
        </div>
    </div>
    
    <div class="queue-display" id="queueDisplay">
        <div class="empty-queue">Queue: Empty - Add commands above</div>
    </div>
    
    <div class="execute-container">
        <button onclick="rotateServo()" style="background-color: #28a745;">Execute</button>
        <button onclick="clearQueue()" style="background-color: #dc3545;">Clear Queue</button>
    </div>

    <script>
        let queue = [];
        let isExecuting = false;
        let currentExecutionIndex = -1;
        
        function addServo(servo, angle) {
            queue.push([servo, angle]);
            updateQueueDisplay();
        }
        
        function addDelay(duration) {
            queue.push(["delay", duration]);
            updateQueueDisplay();
        }
        
        function addCustomDelay() {
            const delayInput = document.getElementById('customDelay');
            const delay = parseInt(delayInput.value);
            if (delay >= 100 && delay <= 10000) {
                addDelay(delay);
            } else {
                alert('Please enter delay between 100-10000 ms');
            }
        }
        
        function setCustomAngle(servo) {
            const angleInput = document.getElementById(servo + 'Angle');
            const angle = parseInt(angleInput.value);
            
            if (angle >= 0 && angle <= 180) {
                addServo(servo, angle);
                angleInput.value = ''; // Clear input
            } else {
                alert('Please enter angle between 0-180');
            }
        }
        
        function removeQueueItem(index) {
            if (!isExecuting) {
                queue.splice(index, 1);
                updateQueueDisplay();
            }
        }
        
        function updateQueueDisplay() {
            const display = document.getElementById('queueDisplay');
            
            if (queue.length === 0) {
                display.innerHTML = '<div class="empty-queue">Queue: Empty - Add commands above</div>';
                return;
            }
            
            let html = '';
            queue.forEach((cmd, index) => {
                const isCurrent = (index === currentExecutionIndex && isExecuting);
                const itemClass = cmd[0] === 'delay' ? 'queue-item delay' : 'queue-item';
                const executingClass = isCurrent ? ' executing' : '';
                
                html += <div class="${itemClass}${executingClass}">;
                html += <div class="queue-item-number">${index + 1}</div>;
                html += <div class="queue-item-content">;
                
                if (cmd[0] === 'delay') {
                    html += Delay: ${cmd[1]}ms;
                } else {
                    html += ${cmd[0]} → ${cmd[1]}°;
                }
                
                html += </div>;
                
                if (!isExecuting) {
                    html += <button class="remove-btn" onclick="removeQueueItem(${index})">×</button>;
                }
                
                html += </div>;
            });
            
            display.innerHTML = html;
        }
        
        function clearQueue() {
            if (!isExecuting) {
                queue = [];
                currentExecutionIndex = -1;
                updateQueueDisplay();
            }
        }
        
        async function rotateServo() {
            if (isExecuting || queue.length === 0) return;
            
            isExecuting = true;
            const executeBtn = document.querySelector('button[onclick="rotateServo()"]');
            executeBtn.disabled = true;
            executeBtn.textContent = 'Executing...';
            executeBtn.style.backgroundColor = '#6c757d';
            
            for (let i = 0; i < queue.length; i++) {
                currentExecutionIndex = i;
                updateQueueDisplay();
                
                let cmd = queue[i];
                console.log(cmd);
                
                if(cmd[0] === "delay") {
                    // Update display during delay
                    await new Promise(resolve => setTimeout(resolve, cmd[1]));
                } else {
                    // Handle servo command
                    try {
                        let res = await fetch("/rotateServo", {
                            method: "POST",
                            headers: { 'Content-Type': 'application/json' },
                            body: JSON.stringify({ 
                                servoName: cmd[0], 
                                servoAngle: cmd[1] 
                            })
                        });
                    } catch(err) {
                        console.log("Error:" + err);
                        alert("Error sending command: " + err);
                        break;
                    }
                    await new Promise(resolve => setTimeout(resolve, 500));
                }
            }
            
            // Execution complete
            isExecuting = false;
            currentExecutionIndex = -1;
            queue = []; // Clear queue after execution
            updateQueueDisplay();
            
            executeBtn.disabled = false;
            executeBtn.textContent = 'Execute';
            executeBtn.style.backgroundColor = '#28a745';
        }
    </script>
</body>
</html>
  )rawliteral";
  
  server.send(200, "text/html", html);
}

void handleRotateServo() {
  if (server.hasArg("plain")) {
    String body = server.arg("plain");
    Serial.println("Received: " + body);
    
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, body);
    
    if (error) {
      server.send(400, "text/plain", "Invalid JSON");
      return;
    }
    
    String servoName = doc["servoName"];
    int servoAngle = doc["servoAngle"];

    // Control the appropriate servo
    if (servoName == "servo1") {
        int temp1=prevAngle1;
      if(servoAngle>prevAngle1){
        while(prevAngle1!=servoAngle){
          servo1.write(prevAngle1);
          servo2.write(prevAngle1);
          servo3.write(prevAngle1);
          prevAngle1++;
          delay(30);
        }
      }
      else{
        while(prevAngle1!=servoAngle){
          servo1.write(prevAngle1);
          servo2.write(prevAngle1);
          servo3.write(prevAngle1);
          prevAngle1--;
          delay(30);
        }        
      }
      Serial.println("Servo 1 set to: " + String(servoAngle) + ", from "+ String(temp1));
      delay(1000);
      prevAngle1=servoAngle;
    } else if (servoName == "servo2") {
        int temp2=prevAngle2;
      if(servoAngle>prevAngle2){
        while(prevAngle2!=servoAngle){
          servo4.write(prevAngle2);
          servo5.write(prevAngle2);
          prevAngle2++;
          delay(30);
        }
      }
      else{
        while(prevAngle2!=servoAngle){
          servo4.write(prevAngle2);
          servo5.write(prevAngle2);
          prevAngle2--;
          delay(30);
        }        
      }
      Serial.println("Servo 2 set to: " + String(servoAngle)+ ", from "+ String(temp2));
      delay(1000);
      prevAngle2=servoAngle;
    } else if (servoName == "servo3") {
        int temp3=prevAngle3;
      if(servoAngle>prevAngle3){
        while(prevAngle3!=servoAngle){
          servo6.write(prevAngle3);
          prevAngle3++;
          delay(30);
        }
      }
      else{
        while(prevAngle3!=servoAngle){
          servo6.write(prevAngle3);
          prevAngle3--;
          delay(30);
        }        
      }
      Serial.println("Servo 3 set to: " + String(servoAngle)+ ", from "+ String(temp3));
      delay(1000);
      prevAngle3=servoAngle;
    }
    else {
      server.send(400, "text/plain", "Invalid servo name");
      return;
    }
    
    server.send(200, "application/json", "{\"status\":\"success\"}");
  } else {
    server.send(400, "text/plain", "No data received");
  }
}