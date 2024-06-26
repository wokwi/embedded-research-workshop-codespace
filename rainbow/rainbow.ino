// Source: https://wokwi.com/projects/401790014738429953

#include <Adafruit_NeoPixel.h>
#include <mbedtls/md.h>

const char* password_hash = "AF1128692F84EF80C04215D152ECA27A87967622B93573009830436A6E155074";
Adafruit_NeoPixel pixels(1, 8, NEO_GRB | NEO_KHZ800);

void setup() {
  pixels.begin();
  Serial.begin(115200);
  Serial.setTimeout(3600000);
  Serial.println("Hello, BSidesTLV 2024 !\n");
  Serial.println("What's the magic word?");
}

void loop() {
  if (Serial.available() > 0) {
    String password = Serial.readStringUntil('\r');
    password.trim();

    // Buffer to hold the hash result
    unsigned char sha256_result[32];

    // Compute SHA-256 hash
    mbedtls_md_context_t ctx;
    mbedtls_md_type_t md_type = MBEDTLS_MD_SHA256;
    const size_t payload_len = password.length();

    mbedtls_md_init(&ctx);
    mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 0);
    mbedtls_md_starts(&ctx);
    mbedtls_md_update(&ctx, (const unsigned char*)password.c_str(), payload_len);
    mbedtls_md_finish(&ctx, sha256_result);
    mbedtls_md_free(&ctx);

    // Convert SHA-256 result to hex string
    char sha256_hex_str[65];
    for (int i = 0; i < 32; i++) {
      sprintf(&sha256_hex_str[i * 2], "%02X", sha256_result[i]);
    }
    sha256_hex_str[64] = '\0';
    Serial.println(password);
    Serial.flush();
    if (strcmp(sha256_hex_str, password_hash) == 0) {
      Serial.println("🎉 Bingo! You've cracked the code! 🌈");
      for (;;) rainbow();
    } else {
      Serial.println("🚫 Nope, try again! What's the magic word?");
    }
  }
  delay(10); // Speeds up the simulation
}

void rainbow() {
  uint16_t i, j;
  for (j = 0; j < 256; j++) {
    pixels.setPixelColor(0, Wheel(j));
    pixels.show();
    delay(20);
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
