import RPi.GPIO as GPIO
from flask import Flask, render_template
import time, pigpio, board, adafruit_dht

app = Flask(__name__)
LED, SERVO_PIN = 24, 18

GPIO.setmode(GPIO.BCM)
GPIO.setup(LED, GPIO.OUT)
pi = pigpio.pi()
dht = adafruit_dht.DHT11(board.D4, use_pulseio=False)

def doc_dht():
    try:
        return dht.temperature, dht.humidity
    except RuntimeError:
        return None, None

def set_servo(goc):
    pi.set_servo_pulsewidth(SERVO_PIN, 500 + (goc / 180.0) * 2000)

@app.route("/")
def index():
    t, h = doc_dht()
    return render_template("main.html", led=GPIO.input(LED), t=t, h=h)

@app.route("/<cmd>")
def control(cmd):
    if cmd == "on": GPIO.output(LED, 1)
    elif cmd == "off": GPIO.output(LED, 0)
    elif cmd == "open": set_servo(90)
    elif cmd == "close": set_servo(0)
    
    t, h = doc_dht()
    return render_template("main.html", led=GPIO.input(LED), t=t, h=h)

if __name__ == "__main__": app.run(host="0.0.0.0", port=5002)