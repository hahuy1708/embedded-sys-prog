import datetime
import os
import time
import cv2
import numpy as np
import RPi.GPIO as GPIO

LEDS = [17, 27, 22]  # Mảng 3 đèn LED báo số lượng người
BTN_SNAP = 23  # Nút bấm chụp ảnh
last_time = 0  # Biến chống rung nút nhấn (Debounce)

GPIO.setmode(GPIO.BCM)
GPIO.setup(LEDS, GPIO.OUT)
GPIO.setup(BTN_SNAP, GPIO.IN, pull_up_down=GPIO.PUD_UP)

cap = cv2.VideoCapture(0)
face_cascade = cv2.CascadeClassifier(
    cv2.data.haarcascades + 'haarcascade_frontalface_default.xml'
)

# --- 1 STICKER MẶC ĐỊNH ---
sticker = cv2.imread('sticker.png')

# --- NHIỀU STICKER ---
# filters = []
# for i in range(1, 5):
#     path = f'f{i}.png' # f1: Tai thỏ, f2: Kính, f3: Râu, f4: Mặt gấu
#     filters.append(cv2.imread(path) if os.path.exists(path) else None)

while True:
  ret, frame = cap.read()
  if not ret:
    break

  frame = cv2.flip(frame, 1)

  gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
  faces = face_cascade.detectMultiScale(gray, 1.1, 5)

  for i in range(3):
    GPIO.output(LEDS[i], i < len(faces))

  for x, y, w, h in faces:
    cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)  # Vẽ khung xanh quanh mặt

    if sticker is not None:
      st_resize = cv2.resize(sticker, (w, h))
      frame[y : y + h, x : x + w] = st_resize[:, :, :3]

    # --- HÀM DÁN NHIỀU BỘ PHẬN THEO TỶ LỆ ---
    # if 'filters' in locals() or 'filters' in globals():
    #     if filters[0] is not None:
    #         f0 = cv2.resize(filters[0], (w, int(h * 0.5)))
    #         frame[int(y - h * 0.5):y, x:x + w] = f0[:, :, :3]
    #
    #     if filters[1] is not None:
    #         f1 = cv2.resize(filters[1], (w, int(h * 0.4)))
    #         frame[int(y + h * 0.3):int(y + h * 0.7), x:x + w] = f1[:, :, :3]
    #
    #     # Filter 3: Cái râu (Nằm ở mũi miệng, co x vào 20%, dịch y xuống 0.6h)
    #     if filters[2] is not None:
    #         f2 = cv2.resize(filters[2], (int(w * 0.6), int(h * 0.3)))
    #         frame[int(y + h * 0.6):int(y + h * 0.9), int(x + w * 0.2):int(x + w * 0.8)] = f2[:, :, :3]
    #
    #     # Filter 4: Mặt gấu (Dán đè khít toàn bộ khuôn mặt gốc)
    #     if filters[3] is not None:
    #         f3 = cv2.resize(filters[3], (w, h))
    #         frame[y:y + h, x:x + w] = f3[:, :, :3]

  # 3. Thuật toán kiểm tra nút bấm Chụp ảnh & Giả lập Đèn Flash
  if GPIO.input(BTN_SNAP) == 0:
    name = f"snap.jpg"
    cv2.imwrite(name, frame)  # Chụp và lưu ảnh thành file

  cv2.imshow('PhotoBooth', frame)
  if cv2.waitKey(1) & 0xFF == ord('q'): break
  
cap.release()
cv2.destroyAllWindows()
GPIO.cleanup()