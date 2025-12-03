#pragma once
#include "esphome.h"
#include "OpenTherm.h"

using namespace esphome;

class BrinkOpenTherm : public Component {
 public:
  OpenTherm* ot;

  // Sensory
  Sensor* vent_current = new Sensor();
  Sensor* temp_supply_in = new Sensor();
  Sensor* temp_supply_out = new Sensor();
  Sensor* temp_exhaust_in = new Sensor();
  Sensor* temp_exhaust_out = new Sensor();
  Sensor* rpm_supply = new Sensor();
  Sensor* rpm_exhaust = new Sensor();
  Sensor* fault_code = new Sensor();
  Sensor* tsp[73];  // TSP 0-72

  // Binary sensors
  BinarySensor* bypass_open = new BinarySensor();
  BinarySensor* bypass_auto = new BinarySensor();
  BinarySensor* vent_active = new BinarySensor();
  BinarySensor* filter_replace = new BinarySensor();

  // Number do ustawienia wentylacji
  Number* ventilation_set = new Number();

  void setup() override {
    // inicjalizacja OpenTherm
    ot = new OpenTherm(4, 5, false);
    ot->begin();

    // Inicjalizacja sensorów TSP
    for(int i=0; i<73; i++) {
      tsp[i] = new Sensor();
    }
  }

  void loop() override {
    // odczyt stanu wentylacji
    vent_current->publish_state(ot->getVentilation());

    // temperatury
    temp_supply_in->publish_state(ot->getVentSupplyInTemperature());
    temp_supply_out->publish_state(ot->getVentSupplyOutTemperature());
    temp_exhaust_in->publish_state(ot->getVentExhaustInTemperature());
    temp_exhaust_out->publish_state(ot->getVentExhaustOutTemperature());

    // RPM
    rpm_supply->publish_state(ot->getVentRPM(OpenThermMessageID::VentRPMsupply));
    rpm_exhaust->publish_state(ot->getVentRPM(OpenThermMessageID::VentRPMexhaust));

    // Fault
    fault_code->publish_state(ot->getVentFaultCode());

    // TSP 0-72
    for(int i=0; i<73; i++){
      tsp[i]->publish_state(ot->getBrinkTSP((BrinkTSPindex)i));
    }

    // binary sensors
    bypass_open->publish_state(ot->getBypassStatus());
    bypass_auto->publish_state(ot->getBypassAutomaticStatus());
    vent_active->publish_state(ot->getVentilationMode());
    filter_replace->publish_state(ot->getDiagnosticIndication());
  }

  void setVentilation(float value){
    ot->setVentilation((unsigned int)value);
  }

  void setTSP(uint8_t index, uint8_t value){
    ot->setBrinkTSP((BrinkTSPindex)index, value);
  }

  uint8_t getTSP(uint8_t index){
    return ot->getBrinkTSP((BrinkTSPindex)index);
  }
};
