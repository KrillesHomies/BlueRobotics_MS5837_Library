#include <iostream>
#include <thread>

#include "br_ms5837/MS5837.h"

using namespace std::chrono_literals;

MS5837 sensor(0); // UP board

int main()
{
  while (!sensor.init()) {
    std::cout << "Init failed!" << std::endl;
    std::this_thread::sleep_for(5s);
  }

  sensor.setModel(MS5837::MS5837_30BA);
  sensor.setFluidDensity(997); // kg/m^3 (freshwater, 1029 for seawater)

  for (int i = 0; i < 100; ++i) {
    sensor.read();

    std::cout << "Pressure: " << sensor.pressure() << " mbar" << std::endl;
    std::cout << "Temperature: "  << sensor.temperature() << " deg C" << std::endl;
    std::cout << "Depth: "  << sensor.depth() << " m" << std::endl;
    std::cout << "Altitude: "  << sensor.altitude() << " m above mean sea level" << std::endl;

    std::this_thread::sleep_for(1s);
  }

  return 0;
}
