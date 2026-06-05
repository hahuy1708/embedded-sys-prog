import cv2
import RPi.GPIO as GPIO
import time

# CẤU HÌNH PHẦN CỨNG & KHỞI TẠO
GPIO.setmode(GPIO.BCM)
GPIO.setup(24, GPIO.IN, pull_up_down=GPIO.PUD_DOWN) # Cấu hình nút nhấn chân 24

cap = cv2.VideoCapture(0)
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + "haarcascade_frontalface_default.xml")
mustache = cv2.imread("mustache.png")

# VÒNG LẶP CHÍNH
while True:
    ret, frame = cap.read()
    if not ret: break
    frame = cv2.flip(frame, 1)
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    
    faces = face_cascade.detectMultiScale(gray, 1.1, 5)
    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
        
        rx1, rx2 = int(x + w * 0.25), int(x + w * 0.75)
        ry1, ry2 = int(y + h * 0.60), int(y + h * 0.80)
        
        r_resized = cv2.resize(mustache, (rx2 - rx1, ry2 - ry1))
        frame[ry1:ry2, rx1:rx2] = r_resized  # Dán đè trực tiếp râu lên ảnh gốc
        
    if GPIO.input(24) == GPIO.HIGH: # Nếu nút bị nhấn
        cv2.imwrite("photo.jpg", frame) # Lưu khung hình hiện tại thành file ảnh
        time.sleep(0.5)
        
    cv2.imshow("PhotoBooth", frame)
    if cv2.waitKey(1) & 0xFF == ord('q'): break

cap.release()
cv2.destroyAllWindows()
GPIO.cleanup()