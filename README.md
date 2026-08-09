# CameraTrap-Notify

> ESP32-CAM motion-triggered camera trap with instant Discord/Telegram photo notifications.
>
> *This description and README were written with AI assistance (Claude). Demo photos/GIFs of the base hardware and web UI are reused from the original project — see credit below.*

Forked and extended from [Dyspersja/CameraTrap](https://github.com/Dyspersja/CameraTrap). All core hardware setup, motion detection, SD card storage, live streaming, and the photo browser web UI come from that project — see its README for setup photos and demo GIFs of those parts.

**What's new in this fork:** when the PIR sensor triggers a photo capture, the image is now also pushed instantly to **Discord** and/or **Telegram**, with a timestamp (synced via NTP) as the caption — so you get a live alert on your phone the moment motion is detected, without needing to open the web viewer.

## Features

Inherited from the original project:
1. PIR motion detection
2. Instant photo capture on motion
3. Photo storage on microSD card
4. Remote photo browsing (`/view`)
5. Full-resolution photo preview
6. Real-time camera stream (`/stream`)

Added in this fork:
7. **Instant push notifications** — captured photo + timestamp sent automatically to Discord and/or Telegram via webhook/bot API
8. **NTP time sync** — accurate local (Thailand, UTC+7) timestamp embedded in every notification caption
9. Each notification channel can be toggled independently (`ENABLE_DISCORD_NOTIFY`, `ENABLE_TELEGRAM_NOTIFY`)

## setup on a breadboard
![system](https://github.com/Dyspersja/CameraTrap/assets/146620220/ea7a1eb2-3133-4f78-b81c-57b5ea0341fa)

## Live View
Below is a demonstration of live video streaming and viewing it in a web browser at **/stream**.

![stream](https://github.com/Dyspersja/CameraTrap/assets/146620220/cf7a3a91-a1b2-4a3f-a9de-00f4efcd2bb1)

## List of Photos
A demonstration of the list of photos taken by the camera and saved on the microSD card at **/view**.

![photolist](https://github.com/Dyspersja/CameraTrap/assets/146620220/d5c540e5-979a-4881-98e3-0b6c0e868fe0)

## Motion Detection
When motion is detected by the PIR sensor, a photo is automatically taken.

![PIR](https://github.com/Dyspersja/CameraTrap/assets/146620220/ab5ae56d-8a8a-45d0-885a-23ee73589ce6)


## New files

| File | Purpose |
|---|---|
| `NotifySender.h` / `.cpp` | Builds a multipart HTTP POST and sends the captured JPEG + caption to Discord and/or Telegram; also handles NTP time sync and timestamp formatting |

## Setup

Follow the original repo's hardware wiring and Arduino IDE board setup first. Then, before flashing:

1. Open `NotifySender.h` and fill in your own:
   - `DISCORD_WEBHOOK_URL` — from your Discord channel's Integrations → Webhooks
   - `TELEGRAM_BOT_TOKEN` — from [@BotFather](https://t.me/BotFather)
   - `TELEGRAM_CHAT_ID` — the chat/user/group ID that should receive alerts
2. Set `ENABLE_DISCORD_NOTIFY` / `ENABLE_TELEGRAM_NOTIFY` to `true`/`false` depending on which channels you want.
3. Set your WiFi `ssid` / `password` in `CameraTrap.ino` as usual.

> ⚠️ **Don't commit real tokens/webhook URLs to a public repo.** Consider moving the values in `NotifySender.h` into a separate untracked config header (add it to `.gitignore`) before pushing, or use placeholder values in the version you publish.

## Credits

- Original hardware design, motion capture, storage, streaming, and web UI: [Dyspersja/CameraTrap](https://github.com/Dyspersja/CameraTrap)
- Live-stream implementation originally credited by Dyspersja to [me-no-dev](https://github.com/me-no-dev) ([gist](https://gist.github.com/me-no-dev/d34fba51a8f059ac559bf62002e61aa3), [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer))
- Discord/Telegram notification feature: added in this fork

---

# CameraTrap-Notify (ภาษาไทย)

> กล้องดักถ่ายภาพเคลื่อนไหวด้วย ESP32-CAM พร้อมส่งแจ้งเตือนภาพถ่ายไปยัง Discord/Telegram ทันทีที่ตรวจจับความเคลื่อนไหว
>
> *คำอธิบายและ README นี้เขียนโดย AI ช่วยเรียบเรียง (Claude) ส่วนภาพถ่าย/GIF สาธิตของฮาร์ดแวร์และหน้าเว็บพื้นฐาน นำมาจากโปรเจกต์ต้นฉบับ (ดูเครดิตด้านล่าง)*

โปรเจกต์นี้ดัดแปลงต่อยอดจาก [Dyspersja/CameraTrap](https://github.com/Dyspersja/CameraTrap) ส่วนของฮาร์ดแวร์, การตรวจจับความเคลื่อนไหว, การบันทึกลง SD card, การสตรีมภาพสด และหน้าเว็บดูรูปภาพ เป็นของต้นฉบับทั้งหมด — สามารถดูภาพและ GIF สาธิตของส่วนเหล่านี้ได้ใน README ของ repo ต้นฉบับ

**สิ่งที่เพิ่มเข้ามาใหม่ในเวอร์ชันนี้:** เมื่อเซนเซอร์ PIR ตรวจจับความเคลื่อนไหวและถ่ายภาพ ระบบจะส่งภาพนั้นไปยัง **Discord** และ/หรือ **Telegram** ทันที พร้อมประทับเวลา (ซิงค์ผ่าน NTP) กำกับไว้ในแคปชั่น ทำให้ได้รับการแจ้งเตือนขึ้นมือถือทันทีโดยไม่ต้องเปิดเว็บดูภาพเอง

## ฟีเจอร์

สืบทอดจากต้นฉบับ:
1. ตรวจจับความเคลื่อนไหวด้วยเซนเซอร์ PIR
2. ถ่ายภาพทันทีเมื่อตรวจพบความเคลื่อนไหว
3. บันทึกภาพลง microSD card
4. เรียกดูรายการภาพจากระยะไกล (`/view`)
5. ดูภาพความละเอียดเต็มแบบพรีวิว
6. สตรีมวิดีโอจากกล้องแบบเรียลไทม์ (`/stream`)

เพิ่มเข้ามาใหม่ในเวอร์ชันนี้:
7. **ส่งแจ้งเตือนทันที** — ภาพที่ถ่ายได้พร้อมเวลาถูกส่งไปยัง Discord และ/หรือ Telegram อัตโนมัติผ่าน webhook/bot API
8. **ซิงค์เวลาผ่าน NTP** — ประทับเวลาท้องถิ่น (ประเทศไทย UTC+7) ที่แม่นยำในทุกข้อความแจ้งเตือน
9. เปิด/ปิดแต่ละช่องทางแจ้งเตือนแยกกันได้ (`ENABLE_DISCORD_NOTIFY`, `ENABLE_TELEGRAM_NOTIFY`)

## การจัดวางบนบอร์ดทดลอง
![system](https://github.com/Dyspersja/CameraTrap/assets/146620220/ea7a1eb2-3133-4f78-b81c-57b5ea0341fa)

## การรับชมสด 
ด้านล่างนี้คือตัวอย่างการสตรีมวิดีโอสดและการรับชมในเว็บเบราว์เซอร์ที่ **/stream**

![stream](https://github.com/Dyspersja/CameraTrap/assets/146620220/cf7a3a91-a1b2-4a3f-a9de-00f4efcd2bb1)

## รายการรูปภาพ 
ตัวอย่างรายการรูปภาพที่ถ่ายด้วยกล้องและบันทึกไว้ใน microSD การ์ดที่ **/view**

![photolist](https://github.com/Dyspersja/CameraTrap/assets/146620220/d5c540e5-979a-4881-98e3-0b6c0e868fe0)

## การตรวจจับการเคลื่อนไหว
เมื่อเซ็นเซอร์ PIR ตรวจจับความเคลื่อนไหวได้ ระบบจะถ่ายภาพโดยอัตโนมัติ

![PIR](https://github.com/Dyspersja/CameraTrap/assets/146620220/ab5ae56d-8a8a-45d0-885a-23ee73589ce6)

## ไฟล์ที่เพิ่มใหม่

| ไฟล์ | หน้าที่ |
|---|---|
| `NotifySender.h` / `.cpp` | สร้าง HTTP POST แบบ multipart เพื่อส่งภาพ JPEG และแคปชั่นไปยัง Discord และ/หรือ Telegram รวมถึงจัดการซิงค์เวลา NTP และจัดรูปแบบ timestamp |

## วิธีตั้งค่า

ให้ต่อวงจรฮาร์ดแวร์และตั้งค่า Arduino IDE ตามต้นฉบับก่อน จากนั้นก่อน flash โค้ด:

1. เปิดไฟล์ `NotifySender.h` แล้วกรอกข้อมูลของคุณเอง:
   - `DISCORD_WEBHOOK_URL` — จากเมนู Integrations → Webhooks ของช่อง Discord
   - `TELEGRAM_BOT_TOKEN` — จาก [@BotFather](https://t.me/BotFather)
   - `TELEGRAM_CHAT_ID` — ไอดีแชท/ผู้ใช้/กลุ่มที่จะรับการแจ้งเตือน
2. ตั้งค่า `ENABLE_DISCORD_NOTIFY` / `ENABLE_TELEGRAM_NOTIFY` เป็น `true`/`false` ตามช่องทางที่ต้องการใช้
3. ตั้งค่า WiFi `ssid` / `password` ในไฟล์ `CameraTrap.ino` ตามปกติ

> ⚠️ **อย่า commit token/webhook URL จริงขึ้น repo สาธารณะ** ควรแยกค่าพวกนี้ใน `NotifySender.h` ไปไว้ในไฟล์ config แยกต่างหากที่ไม่ถูก track (ใส่ใน `.gitignore`) ก่อน push หรือใช้ค่าตัวอย่าง (placeholder) ในเวอร์ชันที่เผยแพร่

## เครดิต

- ฮาร์ดแวร์, การถ่ายภาพเมื่อตรวจจับความเคลื่อนไหว, การจัดเก็บข้อมูล, การสตรีม และหน้าเว็บ: [Dyspersja/CameraTrap](https://github.com/Dyspersja/CameraTrap)
- ฟีเจอร์สตรีมสดต้นฉบับให้เครดิตไว้ที่ [me-no-dev](https://github.com/me-no-dev) ([gist](https://gist.github.com/me-no-dev/d34fba51a8f059ac559bf62002e61aa3), [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer))
- ฟีเจอร์แจ้งเตือนผ่าน Discord/Telegram: เพิ่มขึ้นในเวอร์ชันนี้
