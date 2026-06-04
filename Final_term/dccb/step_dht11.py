import time
import board
import adafruit_dht
import RPi.GPIO as GPIO

# KHỞI TẠO CẤU HÌNH
PINS = [18, 23, 24, 25]
STEP_SEQUENCE = [
    [1,0,0,0], [1,1,0,0], [0,1,0,0], [0,1,1,0],
    [0,0,1,0], [0,0,1,1], [0,0,0,1], [1,0,0,1]
]
dht = adafruit_dht.DHT11(board.D4, use_pulseio=False)

GPIO.setmode(GPIO.BCM)
for pin in PINS: GPIO.setup(pin, GPIO.OUT)

# HÀM ĐIỀU KHIỂN QUAY THUẬN / NGƯỢC
def rotate_degrees(degrees, direction=True):
    steps = int(degrees / 360 * 512)
    # Nếu direction=True thì chạy xuôi mảng, ngược lại lật ngược mảng để đảo chiều
    sequence = STEP_SEQUENCE if direction else list(reversed(STEP_SEQUENCE))
    
    for _ in range(steps):
        for step in sequence:
            for pin, val in zip(PINS, step):
                GPIO.output(pin, val)
            time.sleep(0.001)
    for pin in PINS: GPIO.output(pin, False) # Ngắt điện chống nóng motor

# VÒNG LẶP LOGIC CHÍNH
try:
    while True:
        try:
            temp, humi = dht.temperature, dht.humidity
            if temp is not None and humi is not None:
                if temp > 30 or humi > 70:
                    rotate_degrees(180, direction=True)  # Nóng/Ẩm cao -> Quay THUẬN 180
                else:
                    rotate_degrees(90, direction=False)  # Bình thường -> Quay NGƯỢC 90
            time.sleep(2)
        except RuntimeError:
            time.sleep(2)
except KeyboardInterrupt:
    pass
finally:
    GPIO.cleanup()