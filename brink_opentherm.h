class BrinkOpenTherm : public Component {
 public:
  void setup() override {
    // inicjalizacja OT
  }

  void loop() override {
    // odczyt temperatur, statusów, RPM
  }

  void setVentilation(float value) {
    // wywołanie OpenTherm::setVentilation(...)
  }

  float getVentilation() {
    // wywołanie OpenTherm::getVentilation()
  }

  // analogicznie TSP / bypass / diagnostyka
};
