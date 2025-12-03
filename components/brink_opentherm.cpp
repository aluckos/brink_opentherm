#include "brink_opentherm.h"
#include "OpenTherm.h"

// Przykład: OpenTherm na pinach D4/D5
OpenTherm opentherm(GPIO4, GPIO5, false);

void BrinkOpenTherm::setup() {
  App.register_component(this);
  opentherm.begin();
}

void BrinkOpenTherm::loop() {
  // Odczyt wentylacji
  vent_current = opentherm.getVentilation();

  // Odczyt temperatur
  temp_supply_in = opentherm.getVentSupplyInTemperature();
  temp_supply_out = opentherm.getVentSupplyOutTemperature();
  temp_exhaust_in = opentherm.getVentExhaustInTemperature();
  temp_exhaust_out = opentherm.getVentExhaustOutTemperature();

  // RPM wentylatorów
  rpm_supply = opentherm.getVentRPM(VentRPMsupply);
  rpm_exhaust = opentherm.getVentRPM(VentRPMexhaust);

  // Kod błędu
  fault_code = opentherm.getVentFaultCode();

  // Statusy
  bypass_open = opentherm.getBypassStatus();
  bypass_auto = opentherm.getBypassAutomaticStatus();
  vent_active = opentherm.getVentilationMode();
  filter_replace = opentherm.getDiagnosticIndication();

  // TSP 0–72
  for(int i = 0; i <= 72; i++) {
    tsp[i] = opentherm.getBrinkTSP((BrinkTSPindex)i);
  }
}

void BrinkOpenTherm::setVentilation(float value) {
  if (value < 0) value = 0;
  if (value > 100) value = 100;
  opentherm.setVentilation((unsigned int)value);
}
