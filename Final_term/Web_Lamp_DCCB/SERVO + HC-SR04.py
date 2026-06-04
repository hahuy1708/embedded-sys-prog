import RPi.GPIO as GPIO
from flask import Flask, render_template
import time, pigpio

app = Flask(__name__)
LED, SERVO_PIN, TRIG, ECHO = 24, 18, 2, 3

GPIO.setmode(GPIO.BCM)
GPIO.setup(LED, GPIO.OUT); GPIO.setup(TRIG, GPIO.OUT); GPIO.setup(ECHO, GPIO.IN)
pi = pigpio.pi()

def distance():
    GPIO.output(TRIG, 1); time.sleep(0.00001); GPIO.output(TRIG, 0)
    while GPIO.input(ECHO) == 0: start = time.time()
    while GPIO.input(ECHO) == 1: end = time.time()
    return round((end - start) * 34300 / 2, 1)

def set_servo(goc):
    pi.set_servo_pulsewidth(SERVO_PIN, 500 + (goc / 180.0) * 2000)

@app.route("/")
def index():
    return render_template("main.html", led=GPIO.input(LED), d=distance())

@app.route("/<cmd>")
def control(cmd):
    if cmd == "on": GPIO.output(LED, 1)
    elif cmd == "off": GPIO.output(LED, 0)
    elif cmd == "open": set_servo(90)
    elif cmd == "close": set_servo(0)
    return render_template("main.html", led=GPIO.input(LED), d=distance())

if __name__ == "__main__": app.run(host="0.0.0.0", port=5002)