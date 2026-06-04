import time
import board
import adafruit_dht
import pigpio

pi = pigpio.pi()             
dht = adafruit_dht.DHT11(board.D4) # DHT11 cắm chân D4

def move_and_return(angle):
    pulse = 500 + (angle / 180.0) * 2000
    
    # 1. Quay đến góc chỉ định
    pi.set_servo_pulsewidth(18, pulse)
    time.sleep(0.5)
    
    # 2. Quay trả về góc 0 độ
    pi.set_servo_pulsewidth(18, 500)   # Góc 0 độ tương ứng với xung 500us
    time.sleep(0.5)

try:
    while True:
        try:
            temp = dht.temperature
            humi = dht.humidity
            
            if temp is not None and humi is not None:
                if temp > 30 or humi > 70:
                    move_and_return(180) # Quá nóng/ẩm -> Gạt 180 độ rồi về 0
                else:
                    move_and_return(90)  # Bình thường -> Gạt 90 độ rồi về 0
            time.sleep(2)
            
        except RuntimeError:
            time.sleep(2)
except KeyboardInterrupt:
    pass
finally:
    pi.set_servo_pulsewidth(18, 0) # Ngắt xung PWM (Tắt điện Servo để chống rung/nóng)
    pi.stop()                      # Ngắt kết nối pigpio
    dht.exit()