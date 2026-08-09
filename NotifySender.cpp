#include "NotifySender.h"
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <time.h>

static const char *BOUNDARY = "ESP32CamTrap";

static bool postMultipartPhoto( const String &url,
                                uint8_t *jpgBuf, size_t jpgLen,
                                const String &fileFieldName,
                                const String &fileName,
                                const String textFieldNames[],
                                const String textFieldValues[],
                                size_t textFieldCount) {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("[Notify] WiFi not connected, skip upload");
        return false;
    }

    String head = "";
    for (size_t i = 0; i < textFieldCount; i++) {
        head += "--" + String(BOUNDARY) + "\r\n";
        head += "Content-Disposition: form-data; name=\"" + textFieldNames[i] + "\"\r\n\r\n";
        head += textFieldValues[i] + "\r\n";
    }
    head += "--" + String(BOUNDARY) + "\r\n";
    head += "Content-Disposition: form-data; name=\"" + fileFieldName + "\"; filename=\"" + fileName + "\"\r\n";
    head += "Content-Type: image/jpeg\r\n\r\n";

    
    String tail = "\r\n--" + String(BOUNDARY) + "--\r\n";

    size_t totalLen = head.length() + jpgLen + tail.length();
    uint8_t *body = (uint8_t *)malloc(totalLen);
    if (!body) {
        Serial.println("[Notify] malloc failed for multipart body");
        return false;
    }

    size_t pos = 0;
    memcpy(body + pos, head.c_str(), head.length());
    pos += head.length();
    memcpy(body + pos, jpgBuf, jpgLen);
    pos += jpgLen;
    memcpy(body + pos, tail.c_str(), tail.length());
    pos += tail.length();

    WiFiClientSecure client;
    client.setInsecure();

    HTTPClient http;
    bool ok = false;
    if (http.begin(client, url)) {
        http.addHeader("Content-Type", "multipart/form-data; boundary=" + String(BOUNDARY));
        int httpCode = http.POST(body, totalLen);
        Serial.printf("[Notify] POST %s -> %d\n", url.c_str(), httpCode);
        ok = (httpCode > 0 && httpCode < 300);
        http.end();
    } else {
        Serial.println("[Notify] http.begin() failed");
    }

    free(body);
    return ok;
}

static bool sendToDiscord(uint8_t *jpgBuf, size_t jpgLen, const String &caption) {
    String textNames[]  = { "content" };
    String textValues[] = { caption };
    return postMultipartPhoto(DISCORD_WEBHOOK_URL, jpgBuf, jpgLen,
                               "file", "capture.jpg",
                               textNames, textValues, 1);
}

static bool sendToTelegram(uint8_t *jpgBuf, size_t jpgLen, const String &caption) {
    String url = "https://api.telegram.org/bot" + String(TELEGRAM_BOT_TOKEN) + "/sendPhoto";
    String textNames[]  = { "chat_id", "caption" };
    String textValues[] = { TELEGRAM_CHAT_ID, caption };
    return postMultipartPhoto(url, jpgBuf, jpgLen,
                               "photo", "capture.jpg",
                               textNames, textValues, 2);
}

void sendPhotoNotifications(uint8_t *jpgBuf, size_t jpgLen, const String &caption) {
    if (!jpgBuf || jpgLen == 0) {
        Serial.println("[Notify] Empty image buffer, skip");
        return;
    }

    #if ENABLE_DISCORD_NOTIFY
        if (sendToDiscord(jpgBuf, jpgLen, caption)) {
            Serial.println("[Notify] Sent to Discord");
        } else {
            Serial.println("[Notify] Failed to send to Discord");
        }
    #endif

    #if ENABLE_TELEGRAM_NOTIFY
        if (sendToTelegram(jpgBuf, jpgLen, caption)) {
            Serial.println("[Notify] Sent to Telegram");
        } else {
            Serial.println("[Notify] Failed to send to Telegram");
        }
    #endif
}

void syncTimeNTP() {
    // เวลาไทย UTC+7 ไม่มี daylight saving
    configTime(7 * 3600, 0, "pool.ntp.org", "time.nist.gov");
    Serial.print("[Notify] Syncing time");
    time_t now = time(nullptr);
    int retry = 0;
    while (now < 8 * 3600 * 2 && retry < 20) {
        delay(500);
        Serial.print(".");
        now = time(nullptr);
        retry++;
    }
    Serial.println();
    if (retry >= 20) {
        Serial.println("[Notify] NTP sync failed, timestamp may be inaccurate");
    } else {
        Serial.println("[Notify] Time synced: " + getTimestampString());
    }
}

String getTimestampString() {
    time_t now = time(nullptr);
    struct tm timeinfo;
    localtime_r(&now, &timeinfo);
    char buf[32];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &timeinfo);
    return String(buf);
}
