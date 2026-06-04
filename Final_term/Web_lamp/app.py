import time
import RPi.GPIO as GPIO
from flask import Flask, render_template

app = Flask(__name__)

# CẤU HÌNH PHẦN CỨNG
LED, TRIG, ECHO = 24, 2, 3
GPIO.setmode(GPIO.BCM)
GPIO.setup(LED, GPIO.OUT)
GPIO.setup(TRIG, GPIO.OUT)
GPIO.setup(ECHO, GPIO.IN)

# HÀM ĐO KHOẢNG CÁCH SIÊU ÂM
def get_distance():
    GPIO.output(TRIG, True)
    time.sleep(0.00001)
    GPIO.output(TRIG, False)
    
    while GPIO.input(ECHO) == 0: start = time.time()
    while GPIO.input(ECHO) == 1: end = time.time()
    
    return round((end - start) * 34300 / 2, 1)

# HÀM ĐIỀU PHỐI CÁC ROUTE TRÊN WEB
@app.route("/")
@app.route("/<cmd>")
def index(cmd=None):
    if cmd == "on":   GPIO.output(LED, True)
    if cmd == "off":  GPIO.output(LED, False)
    
    # Đọc trạng thái hiện tại của LED và Khoảng cách để nạp vào giao diện HTML
    return render_template("main.html", led=GPIO.input(LED), d=get_distance())

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5002)