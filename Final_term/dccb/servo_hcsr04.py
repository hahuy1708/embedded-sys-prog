import time
import RPi.GPIO as GPIO
import pigpio

TRIG, ECHO = 23, 24
GPIO.setmode(GPIO.BCM)
GPIO.setup(TRIG, GPIO.OUT)
GPIO.setup(ECHO, GPIO.IN)

pi = pigpio.pi() # Khởi tạo điều khiển Servo (Chân 18)

# HÀM ĐO KHOẢNG CÁCH BẰNG HC-SR04
def get_distance():
    # 1. Phát xung kích hoạt (mức CAO trong 10 micro-giây)
    GPIO.output(TRIG, True)
    time.sleep(0.00001)
    GPIO.output(TRIG, False)
    
    # 2. Đo thời gian xung phản hồi (ECHO)
    while GPIO.input(ECHO) == 0: start = time.time() # Lấy mốc thời gian bắt đầu phát sóng
    while GPIO.input(ECHO) == 1: end = time.time()   # Lấy mốc thời gian khi sóng quay về
    
    # 3. Tính khoảng cách (Vận tốc âm thanh: 34300 cm/s, chia 2 vì sóng đi và về)
    duration = end - start
    return (duration * 34300) / 2

# HÀM ĐIỀU KHIỂN SERVO
def move_and_return(angle):
    pulse = 500 + (angle / 180.0) * 2000
    pi.set_servo_pulsewidth(18, pulse) # Quay đến góc angle
    time.sleep(0.5)
    pi.set_servo_pulsewidth(18, 500)   # Ép lùi về góc 0 độ
    time.sleep(0.5)

# VÒNG LẶP XỬ LÝ LOGIC CHÍNH
try:
    while True:
        dist = get_distance()
        if dist is not None:
            if dist > 10:
                move_and_return(90)   # Vật ở xa > 10cm -> Gạt góc nhỏ 90
            else:
                move_and_return(180)  # Vật ở gần <= 10cm -> Gạt góc lớn 180
        time.sleep(0.2)
except KeyboardInterrupt:
    pass
finally:
    pi.set_servo_pulsewidth(18, 0)
    pi.stop()
    GPIO.cleanup()