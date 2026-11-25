#pragma once

namespace HA {

  struct SensorClass {
    const char *deviceClass;
    const char *defaultUnit;
  };

  // Sensor device classes with default units
  constexpr SensorClass Battery = {"battery", "%"};
  constexpr SensorClass Humidity = {"humidity", "%"};
  constexpr SensorClass Illuminance = {"illuminance", "lx"};
  constexpr SensorClass SignalStrength = {"signal_strength", "dBm"};
  constexpr SensorClass Temperature = {"temperature", "°C"};
  constexpr SensorClass Pressure = {"pressure", "hPa"};
  constexpr SensorClass Power = {"power", "W"};
  constexpr SensorClass Current = {"current", "A"};
  constexpr SensorClass Energy = {"energy", "kWh"};
  constexpr SensorClass PowerFactor = {"power_factor", ""};
  constexpr SensorClass Voltage = {"voltage", "V"};
  constexpr SensorClass Frequency = {"frequency", "Hz"};
  constexpr SensorClass Speed = {"speed", "km/h"};
  constexpr SensorClass Volume = {"volume", "L"};
  constexpr SensorClass VolumeFlow = {"volume_flow", "m³/h"};
  constexpr SensorClass CO2 = {"carbon_dioxide", "ppm"};
  constexpr SensorClass CO = {"carbon_monoxide", "ppm"};
  constexpr SensorClass PM1 = {"pm1", "µg/m³"};
  constexpr SensorClass PM25 = {"pm25", "µg/m³"};
  constexpr SensorClass PM10 = {"pm10", "µg/m³"};
  constexpr SensorClass VOC = {"volatile_organic_compounds", "µg/m³"};
  constexpr SensorClass NOx = {"nitrogen_dioxide", "µg/m³"};
  constexpr SensorClass NitrogenMonoxide = {"nitrogen_monoxide", "µg/m³"};
  constexpr SensorClass NOxIndex = {"", ""};
  constexpr SensorClass SulphurDioxide = {"", "µg/m³"};
  constexpr SensorClass Ozone = {"ozone", "µg/m³"};
  constexpr SensorClass Radiation = {"", "Bq"};

  constexpr char MEASUREMENT[] = "measurement";
  constexpr char TOTAL[] = "total";
  constexpr char TOTAL_INCREASING[] = "total_increasing";
  constexpr char ANGLE[] = "measurement_angle";

  // Binary sensor device classes (no units needed)
  constexpr char BatteryLow[] = "battery";
  constexpr char BatteryCharging[] = "battery_charging";
  constexpr char CarbonMonoxide[] = "carbon_monoxide";
  constexpr char Cold[] = "cold";
  constexpr char Connectivity[] = "connectivity";
  constexpr char Door[] = "door";
  constexpr char GarageDoor[] = "garage_door";
  constexpr char Gas[] = "gas";
  constexpr char Heat[] = "heat";
  constexpr char LightBinary[] = "light";
  constexpr char Lock[] = "lock";
  constexpr char Moisture[] = "moisture";
  constexpr char Motion[] = "motion";
  constexpr char Moving[] = "moving";
  constexpr char Occupancy[] = "occupancy";
  constexpr char Opening[] = "opening";
  constexpr char Plug[] = "plug";
  constexpr char Presence[] = "presence";
  constexpr char Problem[] = "problem";
  constexpr char Running[] = "running";
  constexpr char Safety[] = "safety";
  constexpr char Smoke[] = "smoke";
  constexpr char Sound[] = "sound";
  constexpr char Tamper[] = "tamper";
  constexpr char Update[] = "update";
  constexpr char Vibration[] = "vibration";
  constexpr char Window[] = "window";
} // namespace HA