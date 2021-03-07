#include <assert.h>
#include <iostream>
#include <string>
using namespace std;

const float TEMP_MIN_THRESHOLD =0.00f;
const float TEMP_MAX_THRESHOLD =45.00f;

const float SOC_MIN_THRESHOLD = 1;
const float SOC_MAX_THRESHOLD =100;

const float CHARGE_RATE_MIN_THRESHOLD = 0.00f;
const float CHARGE_RATE_MAX_THRESHOLD =0.80f;

bool checkValueInRange(float min, float max, const float &valueToCheck)
{
	if (valueToCheck >= min && valueToCheck <= max) 
		return true;
	else
	{
		std::cout << " out of range!" << endl;
		return false;
	}
}

bool TemperatureIsOk(const float temperature)
{
	return checkValueInRange(TEMP_MIN_THRESHOLD, TEMP_MAX_THRESHOLD, temperature);
}

bool SocIsOk(const float soc)
{
	return checkValueInRange(SOC_MIN_THRESHOLD, SOC_MAX_THRESHOLD, soc);
}

bool ChargeRateIsOk(const float chargeRate)
{
	return checkValueInRange(CHARGE_RATE_MIN_THRESHOLD, CHARGE_RATE_MAX_THRESHOLD, chargeRate);
}

bool batteryIsOk(const float temperature, const  float soc, const  float chargeRate) {
	bool temperatureOkIndicator, socOkIndicator, chargeRateOkIndicator = false;

	temperatureOkIndicator = TemperatureIsOk(temperature);
	socOkIndicator = SocIsOk(soc);
	chargeRateOkIndicator = ChargeRateIsOk(chargeRate);

	return (temperatureOkIndicator && socOkIndicator && chargeRateOkIndicator);
}

int main() {
	assert(batteryIsOk(25.0F, 70.0F, 0.7F) == true);  // all okay
	assert(batteryIsOk(50.0F, 85.0F, 0.0F) == false); // temp and soc high
	assert(batteryIsOk(50.0F, 65.0F, 0.0F) == false); // temp high
	assert(batteryIsOk(-50.0F, 80.0F, 0.0F) == false); // temp low
	assert(batteryIsOk(40.0F, 15.0F, 0.0F) == false); // soc low
	assert(batteryIsOk(40.0F, 85.0F, 0.0F) == false); // soc high
	assert(batteryIsOk(40.0F, 65.0F, 0.81F) == false); // charge rate high
}
