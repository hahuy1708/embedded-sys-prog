import RPi.GPIO as GPIO
from flask import Flask, render_template
import time, board, adafruit_dht

app = Flask(__name__)
LED = 24
PINS = [18, 19, 20, 21] # Chân của step
STEP = [[1,0,0,0],
        [1,1,0,0],
        [0,1,0,0],
        [0,1,1,0],
        [0,0,1,0],
        [0,0,1,1],
        [0,0,0,1],
        [1,0,0,1]]

GPIO.setmode(GPIO.BCM)
GPIO.setup(LED, GPIO.OUT)

for p in PINS: 
    GPIO.setup(p, GPIO.OUT)
    GPIO.output(p, 0)

dht = adafruit_dht.DHT11(board.D4, use_pulseio=False)

def doc_dht():
    return dht.temperature, dht.humidity

def quay_buoc(so_buoc):
    for _ in range(so_buoc):
        for st in STEP:
            for chan, gt in zip(PINS, st): 
                GPIO.output(chan, gt)
            time.sleep(0.001)
    for p in PINS: 
        GPIO.output(p, 0) # Tắt chân chống nóng động cơ

@app.route("/")
def index():
    t, h = doc_dht()
    return render_template("main.html", led=GPIO.input(LED), t=t, h=h)

@app.route("/<cmd>")
def control(cmd):
    if cmd == "on": GPIO.output(LED, 1)
    elif cmd == "off": GPIO.output(LED, 0)
    elif cmd == "run": quay_buoc(512) # Quay 1 vòng mẫu
    
    t, h = doc_dht()
    return render_template("main.html", led=GPIO.input(LED), t=t, h=h)

if __name__ == "__main__": app.run(host="0.0.0.0", port=5002)