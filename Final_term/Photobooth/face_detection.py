import cv2
# import RPi.GPIO as GPIO

# LEDS = [17, 27, 22] # Mảng chứa 3 chân GPIO nối với 3 đèn LED
# GPIO.setmode(GPIO.BCM)
# for pin in LEDS:
#     GPIO.setup(pin, GPIO.OUT)

cap = cv2.VideoCapture(0)
face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')

# VÒNG LẶP CHÍNH
while True:
    # ĐỌC VÀ TIỀN XỬ LÝ ẢNH
    ret, frame = cap.read()
    if not ret: break
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    
    # QUÉT MẶT VÀ VẼ KHUNG
    faces = face_cascade.detectMultiScale(gray, 1.1, 5)
    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)

    
    # for i in range(3): # Duyệt qua 3 đèn LED
    #     if i < len(faces):
    #         GPIO.output(LEDS[i], GPIO.HIGH) # Bật đèn nếu số mặt lớn hơn chỉ số đèn
    #     else:
    #         GPIO.output(LEDS[i], GPIO.LOW)
        
    # HIỂN THỊ VÀ THOÁT
    cv2.imshow('Face Detection', frame)
    if cv2.waitKey(1) & 0xFF == ord('q'): break

cap.release()
cv2.destroyAllWindows()
# GPIO.cleanup()