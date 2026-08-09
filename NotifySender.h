#ifndef NOTIFY_SENDER_H
#define NOTIFY_SENDER_H

#include "Arduino.h"

#define ENABLE_DISCORD_NOTIFY   true
#define ENABLE_TELEGRAM_NOTIFY  true

#define DISCORD_WEBHOOK_URL "https://discord.com/api/webhooks/XXXXXXXXXXXXX/XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx"

#define TELEGRAM_BOT_TOKEN "123456789:AAExampleTelegramBotTokenxxxxxxxxxxxxx"
#define TELEGRAM_CHAT_ID "123456789"

void syncTimeNTP();

String getTimestampString();

void sendPhotoNotifications(uint8_t *jpgBuf, size_t jpgLen, const String &caption);

#endif
