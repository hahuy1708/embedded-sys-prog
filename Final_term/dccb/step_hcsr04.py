import time
import RPi.GPIO as GPIO

PINS = [18, 23, 24, 25]      # 4 chân IN1 -> IN4 điều khiển động cơ bước
TRIG, ECHO = 20, 21          # Chân phát và chân nhận của cảm biến siêu âm

STEP_SEQUENCE = [            # Chuỗi chạy nửa bước (Half-step) 8 bước cố định
    [1,0,0,0], [1,1,0,0], [0,1,0,0], [0,1,1,0],
    [0,0,1,0], [0,0,1,1], [0,0,0,1], [1,0,0,1]
]

GPIO.setmode(GPIO.BCM)
for pin in PINS: GPIO.setup(pin, GPIO.OUT)
GPIO.setup(TRIG, GPIO.OUT)
GPIO.setup(ECHO, GPIO.IN)

# HÀM ĐO KHOẢNG CÁCH SIÊU ÂM HC-SR04
def get_distance():
    GPIO.output(TRIG, True)   # Phát xung kích hoạt 10 micro-giây
    time.sleep(0.00001)
    GPIO.output(TRIG, False)
    
    while GPIO.input(ECHO) == 0: start = time.time() # Mốc thời gian phát sóng
    while GPIO.input(ECHO) == 1: end = time.time()   # Mốc thời gian nhận sóng dội về
    
    return ((end - start) * 34300) / 2 # Công thức tính khoảng cách (cm)

# HÀM ĐIỀU KHIỂN ĐỘNG CƠ BUỚC QUAY GÓC
def rotate_degrees(degrees):
    steps = int(degrees / 360 * 512) # Đổi từ độ sang số bước tương ứng
    for _ in range(steps):
        for step in STEP_SEQUENCE:
            for pin, val in zip(PINS, step):
                GPIO.output(pin, val)
            time.sleep(0.001)
    for pin in PINS: GPIO.output(pin, False) # BUỘC PHẢI CÓ: Ngắt điện chống cháy motor

# VÒNG LẶP LOGIC CHÍNH
try:
    while True:
        dist = get_distance()
        if dist is not None:
            if dist < 10:
                rotate_degrees(90)   # Dưới 10cm -> Quay 90 độ
            else:
                rotate_degrees(180)  # Từ 10cm trở lên -> Quay 180 độ
        time.sleep(0.1)
except KeyboardInterrupt:
    pass
finally:
    GPIO.cleanup()