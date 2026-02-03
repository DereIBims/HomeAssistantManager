#pragma once

namespace HA {

  struct SensorClass {
    const char *deviceClass;
    const char *defaultUnit;
  };

  // Sensor device classes with default units
  inline constexpr SensorClass Battery = {"battery", "%"};
  inline constexpr SensorClass Humidity = {"humidity", "%"};
  inline constexpr SensorClass Illuminance = {"illuminance", "lx"};
  inline constexpr SensorClass SignalStrength = {"signal_strength", "dBm"};
  inline constexpr SensorClass Temperature = {"temperature", "°C"};
  inline constexpr SensorClass Pressure = {"pressure", "hPa"};
  inline constexpr SensorClass Power = {"power", "W"};
  inline constexpr SensorClass Current = {"current", "A"};
  inline constexpr SensorClass Energy = {"energy", "kWh"};
  inline constexpr SensorClass PowerFactor = {"power_factor", ""};
  inline constexpr SensorClass Voltage = {"voltage", "V"};
  inline constexpr SensorClass Frequency = {"frequency", "Hz"};
  inline constexpr SensorClass Speed = {"speed", "km/h"};
  inline constexpr SensorClass Volume = {"volume", "L"};
  inline constexpr SensorClass VolumeFlow = {"volume_flow", "m³/h"};
  inline constexpr SensorClass CO2 = {"carbon_dioxide", "ppm"};
  inline constexpr SensorClass CO = {"carbon_monoxide", "ppm"};
  inline constexpr SensorClass PM1 = {"pm1", "µg/m³"};
  inline constexpr SensorClass PM25 = {"pm25", "µg/m³"};
  inline constexpr SensorClass PM10 = {"pm10", "µg/m³"};
  inline constexpr SensorClass VOC = {"volatile_organic_compounds", "µg/m³"};
  inline constexpr SensorClass NOx = {"nitrogen_dioxide", "µg/m³"};
  inline constexpr SensorClass NOxIndex = {"nitrogen_oxide", "µg/m³"};
  inline constexpr SensorClass SulphurDioxide = {"sulphur_dioxide", "µg/m³"};
  inline constexpr SensorClass Ozone = {"ozone", "µg/m³"};
  inline constexpr SensorClass Radiation = {"radiation", "Bq"};

  inline constexpr char MEASUREMENT[] = "measurement";
  inline constexpr char TOTAL[] = "total";
  inline constexpr char TOTAL_INCREASING[] = "total_increasing";
  inline constexpr char ANGLE[] = "measurement_angle";

  // Binary sensor device classes (no units needed)
  inline constexpr char BatteryLow[] = "battery";
  inline constexpr char BatteryCharging[] = "battery_charging";
  inline constexpr char CarbonMonoxide[] = "carbon_monoxide";
  inline constexpr char Cold[] = "cold";
  inline constexpr char Connectivity[] = "connectivity";
  inline constexpr char Door[] = "door";
  inline constexpr char GarageDoor[] = "garage_door";
  inline constexpr char Gas[] = "gas";
  inline constexpr char Heat[] = "heat";
  inline constexpr char LightBinary[] = "light";
  inline constexpr char Lock[] = "lock";
  inline constexpr char Moisture[] = "moisture";
  inline constexpr char Motion[] = "motion";
  inline constexpr char Moving[] = "moving";
  inline constexpr char Occupancy[] = "occupancy";
  inline constexpr char Opening[] = "opening";
  inline constexpr char Plug[] = "plug";
  inline constexpr char Presence[] = "presence";
  inline constexpr char Problem[] = "problem";
  inline constexpr char Running[] = "running";
  inline constexpr char Safety[] = "safety";
  inline constexpr char Smoke[] = "smoke";
  inline constexpr char Sound[] = "sound";
  inline constexpr char Tamper[] = "tamper";
  inline constexpr char Update[] = "update";
  inline constexpr char Vibration[] = "vibration";
  inline constexpr char Window[] = "window";
} // namespace HA