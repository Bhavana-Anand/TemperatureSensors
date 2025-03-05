// sensors.h
/*#ifndef LA1_22BCT0213_H
#define LA1_22BCT0213_H

#include <math.h>

#define STEFAN_BOLTZMANN 5.67e-8
#define FAN_THRESHOLD 35.0
#define HEATER_THRESHOLD 6.0

typedef struct {
    int id;
    double last_value;
    double accuracy;
    double drift_rate;
    union {
        struct { double ambient_temp; } te;
        struct { double resistance; } tr;
        struct {
            double emissivity;
            double surface_area;
            double responsivity;
        } to;
        struct {
            double base_sensitivity;
            double nonlinearity_coef;
            double gain;
        } ta;
    } params;
} Sensor;

Sensor create_thermoelectric(int id) {
    Sensor s = {
        .id = id,
        .last_value = 25.0,
        .accuracy = 2.5,
        .drift_rate = 0.006,
        .params.te.ambient_temp = 25.0
    };
    return s;
}

Sensor create_thermoresistive(int id) {
    Sensor s = {
        .id = id,
        .last_value = 25.0,
        .accuracy = 1.0,
        .drift_rate = 0.006,
        .params.tr.resistance = 100.0
    };
    return s;
}

Sensor create_thermooptical(int id) {
    Sensor s = {
        .id = id,
        .last_value = 25.0,
        .accuracy = 1.5,
        .drift_rate = 0.006,
        .params.to = {
            .emissivity = 0.9,
            .surface_area = 2.0,
            .responsivity = 0.7
        }
    };
    return s;
}

Sensor create_thermoacoustic(int id) {
    Sensor s = {
        .id = id,
        .last_value = 25.0,
        .accuracy = 2.0,
        .drift_rate = 0.006,
        .params.ta = {
            .base_sensitivity = 0.02,
            .nonlinearity_coef = 0.4,
            .gain = 30.0
        }
    };
    return s;
}

double get_thermoelectric_reading(Sensor* s) {
    double base_temp = 25.0 + ((double)rand() / RAND_MAX) * 20.0 - 10.0;
    double error = ((double)rand() / RAND_MAX) * 2 * s->accuracy - s->accuracy;
    s->last_value = base_temp + error;
    return s->last_value;
}

double get_thermoresistive_reading(Sensor* s) {
    double base_temp = 25.0 + ((double)rand() / RAND_MAX) * 20.0 - 10.0;
    double error = ((double)rand() / RAND_MAX) * 2 * s->accuracy - s->accuracy;
    s->last_value = base_temp + error;
    return s->last_value;
}

double get_thermooptical_reading(Sensor* s) {
    double ambient_temp = 25.0 + ((double)rand() / RAND_MAX) * 20.0 - 10.0;
    double temp_k = ambient_temp + 273.15;
    double radiated_power = STEFAN_BOLTZMANN * s->params.to.emissivity * 
                           s->params.to.surface_area * pow(temp_k, 4);
    double voltage = s->params.to.responsivity * radiated_power;
    double error = ((double)rand() / RAND_MAX) * 2 * s->accuracy - s->accuracy;
    s->last_value = (voltage / s->params.to.responsivity) * 0.01 + ambient_temp + error;
    return s->last_value;
}

double get_thermoacoustic_reading(Sensor* s) {
    double pressure = 0.3 + ((double)rand() / RAND_MAX) * 0.1;
    double v_out = (s->params.ta.base_sensitivity * pressure) + 
                   (s->params.ta.nonlinearity_coef * pressure * pressure);
    double v_amplified = s->params.ta.gain * v_out;
    double error = ((double)rand() / RAND_MAX) * 2 * s->accuracy - s->accuracy;
    s->last_value = 25.0 + (v_amplified * 0.1) + error;
    return s->last_value;
}

#endif*/

#ifndef LA1_22BCT0213_H
#define LA1_22BCT0213_H

#include <math.h>
#include <stdlib.h>
#include <time.h>

// Common Constants
#define STEFAN_BOLTZMANN 5.67e-8
#define FAN_THRESHOLD 35.0
#define HEATER_THRESHOLD 6.0

// RTD constants (PT100)
#define R0 100.0
#define ALPHA 0.045

// Thermistor constants (Steinhart-Hart coefficients)
#define A 1.009249522e-03
#define B 2.378405444e-04
#define C 2.019202697e-07

// Thermoelectric constant
#define SEEBECK_COEFFICIENT 41e-6  // V/°C for K-type thermocouple

// Sensor Structure
typedef struct {
    int id;
    double last_value;
    double accuracy;
    double drift_rate;
    union {
        struct { 
            double ambient_temp;
            double cold_junction_temp;
        } te;
        struct { 
            double resistance;
            double r0;
        } tr;
        struct {
            double emissivity;
            double surface_area;
            double responsivity;
        } to;
        struct {
            double base_sensitivity;
            double nonlinearity_coef;
            double gain;
        } ta;
    } params;
} Sensor;

// Sensor Creation Functions
Sensor create_thermoelectric(int id) {
    Sensor s = {
        .id = id,
        .last_value = 25.0,
        .accuracy = 2.5,
        .drift_rate = 0.006,
        .params.te = {
            .ambient_temp = 25.0,
            .cold_junction_temp = 25.0
        }
    };
    return s;
}

Sensor create_thermoresistive(int id) {
    Sensor s = {
        .id = id,
        .last_value = 25.0,
        .accuracy = 1.0,
        .drift_rate = 0.006,
        .params.tr = {
            .resistance = 100.0,
            .r0 = R0
        }
    };
    return s;
}

Sensor create_thermooptical(int id) {
    Sensor s = {
        .id = id,
        .last_value = 25.0,
        .accuracy = 1.5,
        .drift_rate = 0.006,
        .params.to = {
            .emissivity = 0.9,
            .surface_area = 2.0,
            .responsivity = 0.7
        }
    };
    return s;
}

Sensor create_thermoacoustic(int id) {
    Sensor s = {
        .id = id,
        .last_value = 25.0,
        .accuracy = 2.0,
        .drift_rate = 0.006,
        .params.ta = {
            .base_sensitivity = 0.02,
            .nonlinearity_coef = 0.4,
            .gain = 30.0
        }
    };
    return s;
}

// Utility Functions
double add_sensor_noise(double value, double accuracy) {
    return value + ((double)rand() / RAND_MAX * 2 - 1) * accuracy;
}

double apply_sensor_drift(double value, double drift_rate) {
    double time_factor = 1.0; // This could be calculated based on sensor age
    return value * (1.0 + drift_rate * time_factor);
}

// Sensor Reading Functions
double get_thermoelectric_reading(Sensor* s) {
    // Generate base temperature with random variation
    double t_hot = 25.0 + ((double)rand() / RAND_MAX) * 20.0 - 10.0;
    
    // Calculate voltage using Seebeck effect
    double voltage = SEEBECK_COEFFICIENT * (t_hot - s->params.te.cold_junction_temp);
    
    // Convert voltage back to temperature and add noise
    double temperature = (voltage / SEEBECK_COEFFICIENT) + s->params.te.cold_junction_temp;
    temperature = add_sensor_noise(temperature, s->accuracy);
    temperature = apply_sensor_drift(temperature, s->drift_rate);
    
    s->last_value = temperature;
    return temperature;
}

double get_thermoresistive_rtd_reading(Sensor* s) {
    // Generate base temperature with random variation
    double base_temp = 25.0 + ((double)rand() / RAND_MAX) * 20.0 - 10.0;
    
    // Calculate RTD resistance
    double resistance = R0 * (1 + ALPHA * base_temp);
    resistance *= (1.0 + ((double)rand() / RAND_MAX * 0.02 - 0.01));
    
    // Convert resistance back to temperature
    double temperature = (resistance / R0 - 1) / ALPHA;
    temperature = add_sensor_noise(temperature, s->accuracy);
    temperature = apply_sensor_drift(temperature, s->drift_rate);
    
    s->last_value = temperature;
    return temperature;
}

double get_thermoresistive_thermistor_reading(Sensor* s) {
    // Generate base temperature with random variation
    double base_temp = 25.0 + ((double)rand() / RAND_MAX) * 20.0 - 10.0;
    
    // Calculate thermistor resistance using Steinhart-Hart
    double inv_T = 1.0 / (base_temp + 273.15);
    double R = (inv_T - A) / (B + C * pow((inv_T - A), 2));
    double resistance = exp(R);
    resistance *= (1.0 + ((double)rand() / RAND_MAX * 0.02 - 0.01));
    
    // Convert resistance back to temperature
    double log_R = log(resistance);
    double inv_temp = A + B * log_R + C * pow(log_R, 3);
    double temperature = (1.0 / inv_temp) - 273.15;
    temperature = add_sensor_noise(temperature, s->accuracy);
    temperature = apply_sensor_drift(temperature, s->drift_rate);
    
    s->last_value = temperature;
    return temperature;
}

double get_thermooptical_reading(Sensor* s) {
    double ambient_temp = 25.0 + ((double)rand() / RAND_MAX) * 20.0 - 10.0;
    double temp_k = ambient_temp + 273.15;
    
    // Calculate radiated power using Stefan-Boltzmann law
    double radiated_power = STEFAN_BOLTZMANN * s->params.to.emissivity * 
                           s->params.to.surface_area * pow(temp_k, 4);
    
    // Convert to sensor voltage and then temperature
    double voltage = s->params.to.responsivity * radiated_power;
    double temperature = (voltage / s->params.to.responsivity) * 0.01 + ambient_temp;
    temperature = add_sensor_noise(temperature, s->accuracy);
    temperature = apply_sensor_drift(temperature, s->drift_rate);
    
    s->last_value = temperature;
    return temperature;
}

double get_thermoacoustic_reading(Sensor* s) {
    double pressure = 0.3 + ((double)rand() / RAND_MAX) * 0.1;
    
    // Calculate output voltage
    double v_out = (s->params.ta.base_sensitivity * pressure) + 
                   (s->params.ta.nonlinearity_coef * pressure * pressure);
    double v_amplified = s->params.ta.gain * v_out;
    
    // Convert to temperature
    double temperature = 25.0 + (v_amplified * 0.1);
    temperature = add_sensor_noise(temperature, s->accuracy);
    temperature = apply_sensor_drift(temperature, s->drift_rate);
    
    s->last_value = temperature;
    return temperature;
}

// Threshold Check Functions
int needs_cooling(double temp) {
    return temp > FAN_THRESHOLD;
}

int needs_heating(double temp) {
    return temp < HEATER_THRESHOLD;
}

#endif // LA1_22BCT0213_H

