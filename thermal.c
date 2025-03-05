/*#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LA1_22BCT0213.h"

#define NUM_READINGS 1200

int main() {
    srand(time(NULL));
    
    Sensor sensors[] = {
        create_thermoelectric(1),
        create_thermoresistive(2),
        create_thermooptical(3),
        create_thermoacoustic(4)
    };
    
    FILE *fp = fopen("C:\\Users\\Bhavana\\Desktop\\sensors_data.csv", "w");

    fprintf(fp, "Time,Thermoelectric,Thermoresistive,ThermoOptical,ThermoAcoustic,Average,Fan,Heater\n");
    
    for (int i = 0; i < NUM_READINGS; i++) {
        double temps[4] = {
            get_thermoelectric_reading(&sensors[0]),
            get_thermoresistive_reading(&sensors[1]),
            get_thermooptical_reading(&sensors[2]),
            get_thermoacoustic_reading(&sensors[3])
        };
        
        double avg_temp = (temps[0] + temps[1] + temps[2] + temps[3]) / 4.0;
        int fan_status = (avg_temp > FAN_THRESHOLD) ? 1:0;
        int heater_status = (avg_temp < HEATER_THRESHOLD) ? 1:0;
        
        fprintf(fp, "%d,%.2f,%.2f,%.2f,%.2f,%.2f,%d,%d\n", 
                i, temps[0], temps[1], temps[2], temps[3], avg_temp, 
                fan_status, heater_status);
    }
    
    fclose(fp);
    return 0;
}*/

#include <stdio.h>
#include<time.h>
#include "LA1_22BCT0213.h"
#include <unistd.h>  // for sleep function
// Function to calculate average temperature
double calculate_average(double te, double rtd, double therm, double to, double ta) {
    return (te + rtd + therm + to + ta) / 5.0;
}

// Function to get fan status (1 for ON, 0 for OFF)
int get_fan_status(double avg_temp) {
    return needs_cooling(avg_temp) ? 1 : 0;
}

// Function to get heater status (1 for ON, 0 for OFF)
int get_heater_status(double avg_temp) {
    return needs_heating(avg_temp) ? 1 : 0;
}

#define NUM_READINGS 1200
int main() {
    // Initialize random seed
    srand(time(NULL));
    
    // Create one sensor of each type
    Sensor te_sensor = create_thermoelectric(1);
    Sensor tr_sensor_rtd = create_thermoresistive(2);
    Sensor tr_sensor_thermistor = create_thermoresistive(3);
    Sensor to_sensor = create_thermooptical(4);
    Sensor ta_sensor = create_thermoacoustic(5);
    
    // Open CSV file
    FILE *fp = fopen("C:\\Users\\Bhavana\\Desktop\\test1.csv", "w");
    /*if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }*/
    
    // Write CSV header
    fprintf(fp, "Time,Thermoelectric,RTD,Thermistor,Thermooptical,Thermoacoustic,Average,Fan_Status,Heater_Status\n");
    
    // Sample for specified duration
    for (int t = 0; t < NUM_READINGS; t ++) {
        // Get readings from all sensors
        double te_temp = get_thermoelectric_reading(&te_sensor);
        double rtd_temp = get_thermoresistive_rtd_reading(&tr_sensor_rtd);
        double thermistor_temp = get_thermoresistive_thermistor_reading(&tr_sensor_thermistor);
        double to_temp = get_thermooptical_reading(&to_sensor);
        double ta_temp = get_thermoacoustic_reading(&ta_sensor);
        // Calculate average temperature
        double avg_temp = calculate_average(te_temp, rtd_temp, thermistor_temp, to_temp, ta_temp);
        
        // Get fan and heater status
        int fan_status = get_fan_status(avg_temp);
        int heater_status = get_heater_status(avg_temp);
        
        // Write to CSV
        fprintf(fp, "%d,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%d,%d\n",
                t, te_temp, rtd_temp, thermistor_temp, to_temp, ta_temp, 
                avg_temp, fan_status, heater_status);
        
        // Print to console for monitoring
        printf("Time: %ds | TE: %.2f°C | RTD: %.2f°C | Thermistor: %.2f°C | TO: %.2f°C | TA: %.2f°C\n",
               t, te_temp, rtd_temp, thermistor_temp, to_temp, ta_temp);
        
        // Check if any sensor indicates need for cooling or heating
        if (needs_cooling(te_temp) || needs_cooling(rtd_temp) || 
            needs_cooling(thermistor_temp) || needs_cooling(to_temp) || 
            needs_cooling(ta_temp)) {
            printf("WARNING: Temperature too high - cooling needed!\n");
        }
        
        if (needs_heating(te_temp) || needs_heating(rtd_temp) || 
            needs_heating(thermistor_temp) || needs_heating(to_temp) || 
            needs_heating(ta_temp)) {
            printf("WARNING: Temperature too low - heating needed!\n");
        }
        
        //sleep(SAMPLE_INTERVAL);  // Wait before next reading
    }
    
    fclose(fp);
    printf("Data collection complete. Results saved to temperature_data.csv\n");
    
    return 0;
}

