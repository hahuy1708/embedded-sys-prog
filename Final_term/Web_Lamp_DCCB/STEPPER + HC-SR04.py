import RPi.GPIO as GPIO
from flask import Flask, render_template
import time

app = Flask(__name__)
LED, TRIG, ECHO = 24, 2, 3
PINS = [18, 19, 20, 21]
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
GPIO.setup(TRIG, GPIO.OUT)
GPIO.setup(ECHO, GPIO.IN)
for p in PINS: 
    GPIO.setup(p, GPIO.OUT)
    GPIO.output(p, 0)

def distance():
    GPIO.output(TRIG, 1)
    time.sleep(0.00001)
    GPIO.output(TRIG, 0)
    while GPIO.input(ECHO) == 0: start = time.time()  # đợi sóng bắt đầu phát đi (ECHO == 0), ghi lại thời điểm start
    while GPIO.input(ECHO) == 1: end = time.time()  # đợi sóng dội ngược lại chạm vào cảm biến (ECHO == 1), ghi lại thời điểm end.
    return round((end - start) * 34300 / 2, 1)

def quay_buoc(so_buoc):
    for _ in range(so_buoc):
        for st in STEP:
            for chan, gt in zip(PINS, st): 
                GPIO.output(chan, gt)
            time.sleep(0.001)
    for p in PINS: 
        GPIO.output(p, 0)

@app.route("/")
def index():
    return render_template("main.html", led=GPIO.input(LED), d=distance())

@app.route("/<cmd>")
def control(cmd):
    if cmd == "on": GPIO.output(LED, 1)
    elif cmd == "off": GPIO.output(LED, 0)
    elif cmd == "run": quay_buoc(512)
    return render_template("main.html", led=GPIO.input(LED), d=distance())

if __name__ == "__main__": app.run(host="0.0.0.0", port=5002)