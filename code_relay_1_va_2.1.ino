#include <Wire.h> // Nhập thư viện màn hình lcd vào
#include <LiquidCrystal_I2C.h> // Nhập thư viện lcd I2C vào
LiquidCrystal_I2C lcd(0x27, 16, 2); // Mã lcd và khai báo có 16 chân và 2 hàng

int relay1=7,relay2=8; // Quy ước relay 1 ở chân D7 và relay 2 ở chân D8 của arduino
int cambien = A0; // Quy ước cảm biến ở chân A0
void setup()
{
  lcd.init(); // Khởi tạo màn hình lcd
  lcd.backlight(); // Mở đèn màn hình lcd
  Serial.begin(9600); // Mở chạy màn hình serial ở mức 9600baud
  pinMode (cambien, INPUT); // Cảm biến gửi tín hiệu váo
  pinMode(relay1,OUTPUT); // Relay 1 nhận tín hiệu ra
  pinMode(relay2,OUTPUT); // Relay 2 nhận tín hiệu ra
}
void tathet() // Cả 2 relay đều về mức thấp -> tắt mạch
{
  digitalWrite(relay1,LOW); // Relay 1 ở mức thấp
  digitalWrite(relay2,LOW); // Relay 2 ở mức thấp
}
void mualon() // Chế độ gạt mưa nhanh khi mưa lớn
{
  digitalWrite(relay1,HIGH); // Relay 1 ở mức cao
  digitalWrite(relay2,LOW); // Relay 2 ở mức thấp
}
void muanho() // Chế độ gạt mưa chậm khi mưa nhỏ
{
  digitalWrite(relay1,LOW); // Relay 1 ở mức thấp
  digitalWrite(relay2,HIGH); // Relay 2 ở mức cao
}
void loop()
{
  int giatridoc = analogRead(cambien); // Quy ước giatridoc là tên gọi của tín hiệu analog do cảm biến gửi vào
  Serial.print("gia tri analog: "); // Quy ước gia tri analog ra serial
  Serial.println(giatridoc); // In ra màn hình serial giatridoc thsy cho giá trị quy ước
  delay(300); // Ngừng 3 giây
  
  if(giatridoc>650) // Nếu giatridoc là lớn hơn 650
  {
    lcd.setCursor(2, 1); // Bắt đầu con trỏ ở cột 2 hàng 
    lcd.print("Khong Co Mua  "); // In ra màn hình lcd là Khong Co Mua
    tathet(); // Tắt mạch
  }
  else if (giatridoc<650&&giatridoc>=350) // Ngược lại, nếu giatridoc lànhỏ hơn 650 và lớn hơn hoặc bằng 350
  {
    lcd.setCursor(2, 1); // Bắt đầu con trỏ ở cột 2 hàng 
    lcd.print("   Mua Nho   "); // In ra màn hình lcd là Mua Nho
    muanho(); // Mưa nhỏ -> Motor quay chậm
  }
  else if (giatridoc<350&&giatridoc>=0) // Ngược lại, nếu giatridoc là nhỏ hơn 350 và lớn hơn hoặc bằng 0
  {
    lcd.setCursor(2, 1); // Bắt đầu con trỏ ở cột 2 hàng 
    lcd.print("   Mua Lon    "); // In ra màn hình lcd là Mua Lon
    mualon(); // Mưa lớn -> Motor quay nhanh
  }
}
