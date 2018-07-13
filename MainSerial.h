class MainSerial
{
  private:
    int baudRate;
  public:
    void init(int baudRate) {
      baudRate = baudRate;
      Serial.begin(baudRate);
    }
    void println(String charsToPrint) {
      Serial.println(charsToPrint);
    }
};

