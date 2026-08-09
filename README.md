# CameraTrap-Notify

> ESP32-CAM camera trap ที่ตรวจจับความเคลื่อนไหวด้วย PIR sensor แล้วส่งภาพแจ้งเตือนอัตโนมัติไปยัง **Discord** และ/หรือ **Telegram** ทันทีที่ถ่ายภาพ

> **หมายเหตุ:** คำอธิบายและ README นี้เขียนโดย AI (Claude) จากการอ่านซอร์สโค้ดของโปรเจกต์

---

## เกี่ยวกับโปรเจกต์

โปรเจกต์นี้ต่อยอดมาจาก [Dyspersja/CameraTrap](https://github.com/Dyspersja/CameraTrap) ซึ่งเป็นระบบ camera trap บน ESP32-CAM (AI Thinker) ที่ใช้ PIR sensor ตรวจจับความเคลื่อนไหว ถ่ายภาพ บันทึกลง microSD และดูภาพ/สตรีมสดผ่านเว็บเบราว์เซอร์

สิ่งที่เพิ่มเติมเข้ามาในเวอร์ชันนี้คือ **ระบบแจ้งเตือนอัตโนมัติ**: เมื่อกล้องตรวจพบความเคลื่อนไหวและถ่ายภาพสำเร็จ ระบบจะส่งภาพพร้อมวันเวลาที่ถ่ายไปยัง Discord (ผ่าน Webhook) และ/หรือ Telegram (ผ่าน Bot API) โดยอัตโนมัติ พร้อมระบบซิงค์เวลาแบบ NTP (ตั้งเป็นเวลาไทย UTC+7) เพื่อให้ timestamp ในภาพถูกต้อง

## ฟีเจอร์หลัก

- **ตรวจจับความเคลื่อนไหว** ด้วย PIR sensor แล้วถ่ายภาพทันที
- **บันทึกภาพ** ลงในการ์ด microSD
- **ดูรายการภาพย้อนหลัง** และเปิดดูภาพแต่ละรูปผ่านเว็บ (`/view`)
- **สตรีมภาพสด (Live Stream)** ผ่านเว็บเบราว์เซอร์ (`/stream`)
- **แจ้งเตือนอัตโนมัติผ่าน Discord** ทันทีที่ถ่ายภาพ (ผ่าน Webhook)
- **แจ้งเตือนอัตโนมัติผ่าน Telegram** ทันทีที่ถ่ายภาพ (ผ่าน Bot API)
- **ซิงค์เวลาอัตโนมัติผ่าน NTP** เพื่อประทับวันเวลาที่ถ่ายภาพให้ถูกต้อง (ตั้งค่าเป็นเขตเวลาไทย)
- เปิด/ปิดการแจ้งเตือนแต่ละช่องทางได้อิสระ

## โครงสร้างไฟล์

| ไฟล์ | หน้าที่ |
|---|---|
| `CameraTrap.ino` | ไฟล์หลัก: เชื่อมต่อ WiFi, ตั้งค่ากล้อง, วนลูปอ่านค่า PIR, ถ่าย/บันทึกภาพ แล้วเรียกส่งแจ้งเตือน |
| `NotifySender.h/.cpp` | โมดูลใหม่ที่เพิ่มเข้ามา — ส่งภาพไปยัง Discord/Telegram แบบ multipart form-data และจัดการซิงค์เวลา NTP |
| `WebHandlers.h/.cpp` | จัดการ request สำหรับดูรายการภาพและดูภาพรายรูป |
| `AsyncJpegStreamResponse.h/.cpp` | คลาสสำหรับสตรีมภาพสด (MJPEG) ผ่าน HTTP |
| `camera_pins.h` | กำหนดขาเชื่อมต่อ (pin mapping) ของโมดูลกล้อง OV2640 บนบอร์ด AI Thinker ESP32-CAM |

## การตั้งค่าก่อนใช้งาน

1. เปิดไฟล์ `CameraTrap.ino` แล้วใส่ชื่อ WiFi และรหัสผ่านของคุณแทนค่า placeholder:
   ```cpp
   const char *ssid = "ชื่อ WiFi ของคุณ";
   const char *password = "รหัสผ่าน WiFi ของคุณ";
   ```
2. เปิดไฟล์ `NotifySender.h` แล้วตั้งค่าตามช่องทางที่ต้องการใช้:
   - **Discord**: ใส่ Webhook URL ของช่องที่ต้องการแจ้งเตือนแทน `DISCORD_WEBHOOK_URL`
   - **Telegram**: ใส่ Bot Token และ Chat ID แทน `TELEGRAM_BOT_TOKEN` และ `TELEGRAM_CHAT_ID`
   - ปิดช่องทางที่ไม่ใช้ได้โดยตั้งค่า `ENABLE_DISCORD_NOTIFY` หรือ `ENABLE_TELEGRAM_NOTIFY` เป็น `false`
3. อัปโหลดโค้ดขึ้นบอร์ด **AI Thinker ESP32-CAM**

## เครดิต

- โปรเจกต์ต้นฉบับ: [Dyspersja/CameraTrap](https://github.com/Dyspersja/CameraTrap)
- ส่วนสตรีมภาพสดในต้นฉบับอ้างอิงจากโค้ดของ [me-no-dev](https://github.com/me-no-dev) และไลบรารี [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
