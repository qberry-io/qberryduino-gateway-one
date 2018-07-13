class Modem
{
  private:
  byte rx, tx;
  int baudRate;
  Led ledManager;
  public:
    void init(byte rx, byte tx, int baudRate, Led ledManager) {
      rx = rx;
      tx = tx;
      baudRate = baudRate;
      ledManager = ledManager;
    }
};
